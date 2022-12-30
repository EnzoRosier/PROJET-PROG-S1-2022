#pragma once
#include <cstdlib>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/serialization/map.hpp>
#include "../Client/Client.h"
#include "../Banque/Banque.h"
#include "../Compte/Compte.h"
#include "../Json/load_save_Json.h"
#include "../PROJET PROG S1 2022/Fonctions/Threadfonctions.h"
#include <thread>

using namespace std;
using boost::asio::ip::tcp;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

std::string to_string(boost::asio::streambuf& buffer)
{
    boost::asio::streambuf::const_buffers_type data = buffer.data();
    return { boost::asio::buffers_begin(data), boost::asio::buffers_end(data) };
}

template <typename _Data_type>
_Data_type get_data_from_string(const char* s)
{
    _Data_type data;
    boost::asio::streambuf buf;
    std::ostream output(&buf);
    output << s;
    std::istream is(&buf);
    boost::archive::text_iarchive ia(is);
    ia >> data;
    return std::move(data);
}

template <typename _Data_type>
std::string get_string_from_data(const _Data_type& data)
{
    boost::asio::streambuf buf;
    std::ostream os(&buf);
    boost::archive::text_oarchive ar(os);
    ar << data;
    auto s = to_string(buf);
    return std::move(s);
}

map<int, Client> registre_exit(map<string, Banque_Decentralise> all_BD) {
    map<int, Client> registre;
    for (auto it=all_BD.begin();it!=all_BD.end();it++){
        for (auto it2 = it->second.Get_registre_local().begin(); it2 != it->second.Get_registre_local().end(); it2++) {
            registre.emplace(pair<int, Client>(it2->first, it2->second));
        }
    }
    return registre;
}

void update_BC(Banque_Centrale& BC) {
	boost::asio::io_service io_service;
	tcp::socket socket(io_service);
	string demande = {};
	char retour[1000] = {};
	boost::system::error_code error;

	demande = "Update";
	socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
	boost::asio::write(socket, boost::asio::buffer(demande), error);
	cout << "Update request sent to BD" << endl;

	// On attend la réponse de BD
	size_t length = socket.read_some(boost::asio::buffer(retour), error);
	cout << "BC updated" << endl;
	BC.Set_registre(get_data_from_string<map<int, Client>>(retour));
}


void updateThread(Banque_Centrale& bq)
{
	while (true) {
		int n = 30;
		time_t start, end;
		start = time(0);
		while (1)
		{

			if (time(0) - start >= n)
			{
				update_BC(bq);
			}
		}
	}
}

void updateThread_BD(map<string, Banque_Decentralise>& all_BD) {
	while (true) {
		update_BD(ref(all_BD));
	}
}

void update_BD(map<string, Banque_Decentralise>& all_BD) {
	boost::asio::io_service io_service;
	tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234));
	tcp::socket socket(io_service);
	string demande = {};
	char retour[1000] = {};
	boost::system::error_code error;

	acceptor_.accept(socket);

	while (true) {
		size_t length = socket.read_some(boost::asio::buffer(retour), error);

		if (string(retour) == "Update") {
			cout << "Update received from BC" << endl;
			map<int, Client> registre = registre_exit(all_BD);
			demande = get_string_from_data(registre);
			boost::asio::write(socket, boost::asio::buffer(demande), error);
			cout << "Update sent to BC" << endl;
		}
	}
}