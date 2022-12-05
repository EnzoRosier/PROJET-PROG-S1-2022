#pragma once
#include "tools.cpp"



int main() {
    boost::asio::io_service io_service;
    //listen for new connection
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234));
    //socket creation 
    socket_ptr socket(new tcp::socket (io_service));
    //waiting for connection
    acceptor_.accept(*socket);

    char data[10000] = {};

    boost::system::error_code error;
    size_t length = socket->read_some(boost::asio::buffer(data), error);


    //read operation
    Client client = get_data_from_string<Client>(data);
    client.affiche_client();
    //write operation
    cout << "Server sent Hello message to Client!" << endl;
    int i = 0;
    cin >> i;
    return 0;
}