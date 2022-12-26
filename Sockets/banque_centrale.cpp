#include "tools.cpp"


/*
Types de requ�tes :
    - Init : la banque centrale fait un premier envoi pour intialiser les BD, envoie un registre
    - Update : la banque centrale met � jour sa base de donn�e en collectant la base de donn�e de la banque d�centralis�e
               envoie un string ("Update") et recoit un registe map<int,Client>
    - Find : Pour retrouver un compte,recoit un id de compte, renvoie un client
             La reception est de la forme "Find Id_compte_recherche"
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
    ptree in;
    read_json(file_in, in);
    Banque_Centrale BC = Banque_from_ptree(in);

    // On initialise les banques d�centralis�es

    demande = get_string_from_data(BC.Get_registre()); // On cr�e une demande pour l'initialisation
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    boost::asio::write(socket, boost::asio::buffer(demande), error);

    bool exit = false;
    while (exit == false) {  // Tant que l'utilisateur ne quitte pas l'interface

        // On commence par se mettre en attente de reception d'un socket

        acceptor_.accept(socket);
        size_t length = socket.read_some(boost::asio::buffer(retour), error);

        // Hourra on a re�u un socket, il faut maintenant analyser la demande
   
        if (retour == "Exit") { // Si c'est pour finir
            exit = true;
        }
        if (string(retour).substr(0, 4) == "Find") { // Si la premi�re partie de la requ�te est Find alors

            string id_compte = demande.substr(6, string(retour).size() - 4); // On prend la partie de la requ�te qui nous int�resse
            Compte compte = BC.Chercher_compte_clients(id_compte);
            Client c = BC.Chercher_infos_clients(compte.get_Id_proprietaire());

            // On a le client, maintenant il faut le renvoyer

            demande = get_string_from_data(c); // On convertit le client en cha�ne de caract�res

            // On connecte le socket avec la banque_decentralisee
            socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
            boost::asio::write(socket, boost::asio::buffer(demande), error); // On l'envoie avec la reponse
        }

        
    }
    // On met � jour le registre avant de quitter
    
    demande = "Update";
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    boost::asio::write(socket, boost::asio::buffer(demande), error);

    // On attend la r�ponse
    acceptor_.accept(socket);
    size_t length = socket.read_some(boost::asio::buffer(retour), error);
    map<int, Client> temp_registre = get_data_from_string<map<int,Client>>(retour);
    BC.Set_registre(temp_registre);

    //Sauvegarde du registre

    std::ofstream file_out("registre_BC.json");
    write_json(file_out, BC.GeneratePtreeBanque());
    file_out.close();
    return 0;
}