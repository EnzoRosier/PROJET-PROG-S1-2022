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
    Client cl1(2, "John", "McClain", "3 Rue de la paix", "Lille",68.8);
    Compte c1("1", 2, 334);
    Compte c2("2", 2, 323);
    Compte_Epargnes c3("3", 2, 100, 5);
    vector<Compte> liste_comptes;
    vector<Compte_Epargnes> liste_comptes_epargnes;
    liste_comptes.push_back(c1);
    liste_comptes.push_back(c2);
    liste_comptes_epargnes.push_back(c3);

    cl1.Set_liste_comptes(liste_comptes);
    cl1.Set_liste_comptes_epargnes(liste_comptes_epargnes);
    cl1.affiche_client();

    const string msg = get_string_from_data(cl1);
    cout << cl1.Get_liste_comptes()[0] << endl;
    cout << cl1.Get_liste_comptes()[1] << endl;
    cout << cl1.Get_liste_comptes_epargnes()[0].get_taux() << endl;


    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(msg), error);
    if (!error) {
        cout << "Client sent McClain!" << endl;
    }
    else {
        cout << "send failed: " << error.message() << endl;
    }

    int i=0;
    cin >> i;
    return EXIT_SUCCESS;
}

