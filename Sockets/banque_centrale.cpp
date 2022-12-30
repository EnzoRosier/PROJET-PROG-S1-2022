#include "tools.cpp"


/*
Types de requêtes :
    - Init : la banque centrale fait un premier envoi pour intialiser les BD, envoie un registre
    - Update : la banque centrale met à jour sa base de donnée en collectant la base de donnée de la banque décentralisée
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
    char retour[1000] = {};
    boost::system::error_code error;
    

    // On initialise le registre à partir d'un .Json sauvegardé au préalable

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

    // On initialise les banques décentralisées

    demande = get_string_from_data(BC.Get_registre()); // On crée une demande pour l'initialisation
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    boost::asio::write(socket, boost::asio::buffer(demande), error);
    cout << "Init sent to BD" << endl;

    
    //thread threadEparne(epargneThread, ref(BC)); //Lancement thread Epargne
    thread threadSave(saveThread, ref(BC)); //Lancement thread Epargne
    //thread threadUpdate(updateThread, ref(BC)); //Lancement thread update
    
    bool exit = false;
    while (exit == false) {  // Tant que l'utilisateur ne quitte pas l'interface
        cout << "Enter BC while" << endl;

        // On commence par se mettre en attente de reception d'un socket
        size_t length = socket.read_some(boost::asio::buffer(retour), error);
        cout << retour << endl;

        // Hourra on a reçu un socket, il faut maintenant analyser la demande

        if (string(retour).substr(0,4) == "Exit") { // Si c'est pour finir
            cout << "Received Exit" << endl;
            map<int, Client> registre_maj = get_data_from_string<map<int, Client>>(string(retour).substr(4, string(retour).size() - 4).c_str());
            BC.Set_registre(registre_maj);
            exit = true;
        }

        if (string(retour).substr(0, 4) == "Find") { // Si la première partie de la requête est Find alors
            cout << "Received a Find request" << endl;

            string id_compte = demande.substr(5, string(retour).size() - 4); // On prend la partie de la requête qui nous intéresse
            auto compte = BC.Chercher_compte_clients(id_compte);
            Client c = BC.Chercher_infos_clients(compte.get_Id_proprietaire());

            if (c.Get_id() != -1) {

                // On a le client, maintenant il faut le renvoyer

                demande = get_string_from_data(c); // On convertit le client en chaîne de caractères

                // On connecte le socket avec la banque_decentralisee
                boost::asio::write(socket, boost::asio::buffer(demande), error); // On l'envoie avec la reponse
                cout << "Client sent to BD" << endl;
            }
            else {
                demande = "Fail";
                boost::asio::write(socket, boost::asio::buffer(demande), error);
                cout << "Client search failed" << endl;
            }
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