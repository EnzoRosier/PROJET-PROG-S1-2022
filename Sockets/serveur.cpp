#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
using ip::tcp;


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
    //listen for new connection
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234));
    //socket creation 
    tcp::socket socket_(io_service);
    //waiting for connection
    acceptor_.accept(socket_);
    //read operation
    string message = read_(socket_);
    cout << message << endl;
    //write operation
    send_(socket_, "Salut a toi!");
    cout << "Server sent Hello message to Client!" << endl;
    int i = 0;
    cin >> i;
    return 0;
}