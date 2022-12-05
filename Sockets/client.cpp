#include "tools.cpp"


// Entre la banque centrale et les banques décentralisées on a 2 types de requêtes :
// La mise à jour du registre
// Les transactions

// Entre les banques décentralisées et le client il y a :
// La création d'un compte client
// La création d'un compte
// La demande d'une transaction


string read_(tcp::socket& socket) { // La réception du socket met ledit socket dans une chaine de caractère qui pourra être traitée plus tard
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}


void send_(tcp::socket& socket, const string& message) { // On crée le socket avec une chaine de caractères
    const string msg = message + "\n";
    boost::asio::write(socket, boost::asio::buffer(message));
}



int main() {
    boost::asio::io_service io_service;
    //socket creation
    tcp::socket socket(io_service);
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    // request/message from client
    Client cl1 = Client(0, "John", "McClain", "3 Rue de la paix", "Lille",68.8);
    const string msg = get_string_from_data(cl1);
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(msg), error);
    if (!error) {
        cout << "Client sent McClain!" << endl;
    }
    else {
        cout << "send failed: " << error.message() << endl;
    }
    // getting response from server
    boost::asio::streambuf receive_buffer;
    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        cout << "receive failed: " << error.message() << endl;
    }
    else {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        int i = 0;
        cout << data << endl;
        cin >> i;
    }
    return EXIT_SUCCESS;
}

