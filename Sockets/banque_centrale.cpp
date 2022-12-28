#include "tools.cpp"


/*
Types de requ�tes :
    - Init : la banque centrale fait un premier envoi pour intialiser les BD, envoie un registre
    - Update : la banque centrale met � jour sa base de donn�e en collectant la base de donn�e de la banque d�centralis�e
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

    // On initialise le registre � partir d'un .Json sauvegard� au pr�alable

    std::ifstream file_in("registre_BC.json");
    Banque_Centrale BC;
    if (file_in.is_open()) {
        cout << "Registre loaded sucessfully" << endl;
        ptree in;
        cout << "Hello" << endl;
        read_json(file_in, in);
        Banque_Centrale BC = Banque_from_ptree(in);
    }
    else {
        cout << "Registre load failed" << endl;
    }

    // On initialise les banques d�centralis�es


    demande = get_string_from_data(BC.Get_registre()); // On cr�e une demande pour l'initialisation
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    boost::asio::write(socket, boost::asio::buffer(demande), error);
    cout << "Init sent to BD" << endl;

    //thread threadEparne(epargneThread, BC); //Lancement thread Epargne

    bool exit = false;
    while (exit == false) {  // Tant que l'utilisateur ne quitte pas l'interface
        cout << "Enter the BC while" << endl;

        // On commence par se mettre en attente de reception d'un socket

        acceptor_.accept(socket);
        size_t length = socket.read_some(boost::asio::buffer(retour), error);

        cout << "Request received : " << retour << endl;

        // Hourra on a re�u un socket, il faut maintenant analyser la demande
   
        if (retour == "Exit") { // Si c'est pour finir
            cout << "Received Exit" << endl;
            exit = true;
        }
        if (string(retour).substr(0, 4) == "Find") { // Si la premi�re partie de la requ�te est Find alors
            cout << "Received a Find request" << endl;

            string id_compte = demande.substr(5, string(retour).size() - 4); // On prend la partie de la requ�te qui nous int�resse
            Compte compte = BC.Chercher_compte_clients(id_compte);
            Client c = BC.Chercher_infos_clients(compte.get_Id_proprietaire());

            if (c.Get_id() != -1) {

                // On a le client, maintenant il faut le renvoyer

                demande = get_string_from_data(c); // On convertit le client en cha�ne de caract�res

                // On connecte le socket avec la banque_decentralisee
                socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
                boost::asio::write(socket, boost::asio::buffer(demande), error); // On l'envoie avec la reponse
                cout << "Client sent to BD" << endl;
            }
            else {
                demande = "Fail";
                socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
                boost::asio::write(socket, boost::asio::buffer(demande), error);
                cout << "Client search failed" << endl;
            }
        }

        
    }
    // On met � jour le registre avant de quitter
    
    demande = "Update";
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    boost::asio::write(socket, boost::asio::buffer(demande), error);
    cout << "Final Update request sent" << endl;

    // On attend la r�ponse
    acceptor_.accept(socket);
    size_t length = socket.read_some(boost::asio::buffer(retour), error);
    map<int, Client> temp_registre = get_data_from_string<map<int,Client>>(retour);
    BC.Set_registre(temp_registre);
    cout << "Final update complete, ready to save" << endl;

    //Sauvegarde du registre

    std::ofstream file_out("registre_BC.json");
    write_json(file_out, BC.GeneratePtreeBanque());
    file_out.close();
    cout << "File saved" << endl;
    return EXIT_SUCCESS;
}