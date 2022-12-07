#pragma once
#include "tools.cpp"


// Entre la banque centrale et les banques décentralisées on a 2 types de requêtes :
// La mise à jour du registre
// Les transactions

// Entre les banques décentralisées et le client il y a :
// La création d'un compte client
// La création d'un compte
// La demande d'une transaction




int main() {
    boost::asio::io_service io_service;
    //socket creation
    tcp::socket socket(io_service);
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    // request/message from client
    Client cl1 = Client(0, "John", "McClain", "3 Rue de la paix", "Lille",68.8);
    Compte* c1 = new Compte("1", 334);
    Compte* c2 = new Compte("2", 323);
    Compte_Epargnes* c3 = new Compte_Epargnes("3", 10, 50);
    vector<Compte*> liste_comptes;
    liste_comptes.push_back(c1);
    liste_comptes.push_back(c2);
    liste_comptes.push_back(c3);
    cl1.Set_liste_comptes(liste_comptes);
    const string msg = get_string_from_data(cl1);


    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(msg), error);
    if (!error) {
        cout << "Client sent McClain!" << endl;
    }
    else {
        cout << "send failed: " << error.message() << endl;
    }
    return EXIT_SUCCESS;
}

