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

vector< map<int,Client>> init_BD(map<int, Client>){}


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
    vector<map<int,Client>> all_BD = init_BD(temp_registre);

    return EXIT_SUCCESS;
}

