// On cr�e ici toutes les fonctions d'envoi/reception pour les sockets
#include "../PROJET PROG S1 2022/includer.h"
#include "boost/asio.hpp"


using namespace boost::asio;
using ip::tcp;


string read_(tcp::socket& socket) { // La r�ception du socket met ledit socket dans une chaine de caract�re qui pourra �tre trait�e plus tard
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}


void send_(tcp::socket& socket, const string& message) { // On cr�e le socket avec une chaine de caract�res
    const string msg = message + "\n";
    boost::asio::write(socket, boost::asio::buffer(message));
}