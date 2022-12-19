#include "tools.cpp"


// Entre la banque centrale et les banques d�centralis�es on a 2 types de requ�tes :
// La mise � jour du registre
// Les transactions

// Entre les banques d�centralis�es et le client il y a :
// La cr�ation d'un compte client
// La cr�ation d'un compte
// La demande d'une transaction




int main() {
    boost::asio::io_service io_service;
    //socket creation
    tcp::socket socket(io_service);
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    // request/message from client
    Client cl1(0, "John", "McClain", "3 Rue de la paix", "Lille",68.8);
    Compte c1("1", 334);
    Compte c2("2", 323);
    vector<Compte> liste_comptes;
    liste_comptes.push_back(c1);
    liste_comptes.push_back(c2);
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

