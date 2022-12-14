#include "tools.cpp"


/*
Types de requ?tes :
    - Init : la banque centrale fait un premier envoi pour intialiser les BD, envoie un registre
    - Update : la banque centrale met ? jour sa base de donn?e en collectant la base de donn?e de la banque d?centralis?e
               envoie un string ("Update") et recoit un registe map<int,Client>
    - Find : Pour retrouver un compte,recoit un id de compte, renvoie un client
             La reception est de la forme "FindId_compte_recherche"
    - Exit : Pour fermer l'executable et sauvegarder le registre, recoit un string ("Exit") et ne renvoie rien

*/



int main() {
    boost::asio::io_service io_service;
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234));
    tcp::socket socket(io_service);
    string demande = {};
    char retour[10000] = {};
    boost::system::error_code error;
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));

    // On initialise le registre ? partir d'un .Json sauvegard? au pr?alable

    std::ifstream file_in("registre_BC.json");
    Banque_Centrale BC;
    if (file_in.is_open()) {
        cout << "Registre loaded sucessfully" << endl;
        ptree in;
        read_json(file_in, in);
        BC = Banque_from_ptree(in);
    }
    else {
        cout << "Registre load failed" << endl;
    }

    // On initialise les banques d?centralis?es

    demande = get_string_from_data(BC.Get_registre()); // On cr?e une demande pour l'initialisation
    
    boost::asio::write(socket, boost::asio::buffer(demande), error);
    cout << "Init sent to BD" << endl;

    
    thread threadEparne(epargneThread, ref(BC)); //Lancement thread Epargne
    thread threadSave(saveThread, ref(BC)); //Lancement thread Autosave

    
    bool exit = false;
    while (exit == false) {  // Tant que l'utilisateur ne quitte pas l'interface
        cout << "Enter BC while" << endl;

        demande.clear();
        char retour[10000] = {};

        // On commence par se mettre en attente de reception d'un socket
        size_t length = socket.read_some(boost::asio::buffer(retour), error);
        

        // Hourra on a re?u un socket, il faut maintenant analyser la demande

        if (string(retour).substr(0,4) == "Exit") { // Si c'est pour finir
            cout << "Received Exit" << endl;
            map<int, Client> registre_maj = get_data_from_string<map<int, Client>>(string(retour).substr(4, string(retour).size() - 4).c_str());
            BC.Set_registre(registre_maj);
            exit = true;
        }

        if (string(retour).substr(0, 4) == "Find") { // Si la premi?re partie de la requ?te est Find alors
            cout << "Received a Find request" << endl;

            string id_compte = string(retour).substr(4, 10); // On prend la partie de la requ?te qui nous int?resse
            cout << id_compte << endl;
            auto compte = BC.Chercher_compte_clients(id_compte);

            if (compte.get_Identifiant_Compte() != "-1") {
                Client c = BC.Chercher_infos_clients(compte.get_Id_proprietaire());
                cout << "Found a client" << endl;
                // On a le client, maintenant il faut le renvoyer

                c.affiche_client();
                demande = get_string_from_data(c); // On convertit le client en cha?ne de caract?res

                
                boost::asio::write(socket, boost::asio::buffer(demande), error); // On l'envoie avec la reponse
                cout << "Client sent to BD" << endl;
            }
            else {
                cout << "Account search failed" << endl;
                demande = "Fail";
                boost::asio::write(socket, boost::asio::buffer(demande), error);
                
            }
        }

        if (string(retour).substr(0, 6) == "Update") {
            cout << "Update received from BD" << endl;
            map<int, Client> registre_maj = get_data_from_string<map<int, Client>>(string(retour).substr(6, string(retour).size() - 6).c_str());
            BC.Set_registre(registre_maj);
        }

    }

    //Sauvegarde du registre

    std::ofstream file_out("registre_BC.json");
    write_json(file_out, BC.GeneratePtreeBanque());
    file_out.close();
    cout << "File saved" << endl;
    int i;
    cin >> i;
    return EXIT_SUCCESS;
}