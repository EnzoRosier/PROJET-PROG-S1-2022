#include "tools.cpp"

/*
Types de requêtes avec la banque centrale (IP : 1234):
    - Init : la banque centrale fait un premier envoi pour intialiser les BD, reçoit un registre
    - Update : la banque centrale met à jour sa base de donnée en collectant la base de donnée de la banque décentralisée
               reçoit un string ("Update") et envoie un registe map<int,Client>
    - Find : Pour retrouver un compte,envoie un id de compte, reçoit un client
             La reception est de la forme "Find Id_compte_recherche"
    - Exit : Pour fermer l'executable et sauvegarder le registre, envoie un string ("Exit") et ne reçoit rien

Types de requêtes avec l'interface (IP : 0123):
    - Login : L'interface tente de se connecter, reçoit un string "Login Id_client", renvoie un client ou une réponse négativex 
    - Add_cust : L'interface crée un nouveau client, reçoit un client et le renvoie
    - Transaction : L'interface crée une demande de transaction
*/

map<string,map<int, Client>> init_BD(map<int, Client> g_registre) {
    // On recoit un registre complet et on va le compartimenter en un map contenant les registres de chaque BD
    map<string, map<int, Client>> liste_registre;
    vector<map<int, Client>> temp; // On fait un vecteur temporaire

    auto it = g_registre.begin();
    map<int, Client> temp_map;
    
    for (it; it != g_registre.end(); it++) {

    }
}


int main() {
    boost::asio::io_service io_service;
    tcp::acceptor acceptor_BC(io_service, tcp::endpoint(tcp::v4(), 1234));
    tcp::acceptor acceptor_CL(io_service, tcp::endpoint(tcp::v4(), 0123));
    tcp::socket socket(io_service);
    string demande = {};
    char retour[1000] = {};
    boost::system::error_code error;


    // Au lancement il faut attendre le INIT de la BC
    acceptor_BC.accept(socket);
    size_t length = socket.read_some(boost::asio::buffer(retour), error);

    // On récupère le registre de la BC
    map<int, Client> temp_registre = get_data_from_string<map<int, Client>>(retour);
    map<string,map<int,Client>> all_BD = init_BD(temp_registre);
    // map de la forme <nom_agence,registre_agence>

    bool exit = false;
    while (!exit) {
        // On se met en attente d'une requête de l'interface
        acceptor_CL.accept(socket);
        size_t length = socket.read_some(boost::asio::buffer(retour), error);

        // Une fois qu'on a la requête, on l'analyse

        if (retour == "Exit") {
            // On doit prévenir la BC de l'exit
            demande = "Exit";
            socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
            boost::asio::write(socket, boost::asio::buffer(demande), error);

        }
        if (string(retour).substr(0, 5) == "Login") { // L'interface tente de se connecter à un compte
            int id_client = atoi(string(retour).substr(6, string(retour).size() - 5).c_str());
        }
    }

    return EXIT_SUCCESS;
}

