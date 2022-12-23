#include "tools.cpp"


/*
Types de requêtes :
    - Update : la banque centrale met à jour sa base de donnée en collectant la base de donnée de la banque décentralisée
               envoie un string ("Update") et recoit une banque_decentralisee
    - Find : Pour retrouver un compte,recoit un id de compte, renvoie un client
             La reception est de la forme "Find Id_compte_recherche"
    - Exit : Pour fermer l'executable et sauvegarder le registre, recoit un string ("Exit") et ne renvoie rien

*/



int main() {
    boost::asio::io_service io_service;
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234));
    tcp::socket socket(io_service);
    string demande = {};
    string renvoi = {};
    boost::system::error_code error;

    // On initialise le registre à partir d'un .Json sauvegarder au préalable
    // Et on actualise également le ragistre pour mettre à jour les éventuelles modifications non enregistrées

    std::ifstream file_in("registre_BC.json");
    ptree in;
    read_json(file_in, in);
    Banque_Centrale BC = Banque_from_ptree(in);

    demande = "Update"; // On créer une demande de mise à jour à l'initialisation
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    boost::asio::write(socket, boost::asio::buffer(demande), error);

    // On attend la réponse de la BD
    acceptor_.accept(socket);
    size_t length = socket.read_some(boost::asio::buffer(renvoi), error);



    bool exit = false;
    while (exit == false) {

        // On commence par se mettre en attente de reception d'un socket

        acceptor_.accept(socket);
        size_t length = socket.read_some(boost::asio::buffer(demande), error);

        // Hourra on a reçu un socket, il faut maintenant analyser la demande
   
        if (demande == string("Exit")) { // Si c'est pour finir
            exit = true;
        }
        if (demande.substr(0, 4) == "Find") { // Si la première partie de la requête est Find alors

            string id_compte = demande.substr(6, demande.size() - 4); // On prend la partie de la requête qui nous intéresse
            Compte compte = BC.Chercher_compte_clients(id_compte);
            Client c = BC.Chercher_infos_clients(compte.get_Id_proprietaire());

            // On a le client, maintenant il faut le renvoyer

            renvoi = get_string_from_data(c); // On convertit le client en chaîne de caractères

            // On connecte le socket avec la banque_decentralisee
            socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
            boost::asio::write(socket, boost::asio::buffer(renvoi), error); // On l'envoie avec la reponse
        }

        
    }
    //Sauvegarde du registre
    return 0;
}