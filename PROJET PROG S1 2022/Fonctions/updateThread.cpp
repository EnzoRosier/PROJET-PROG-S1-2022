#pragma once
#include "Threadfonctions.h"

void update_BC((Banque_Centrale& BC, boost::asio::io_service io_service)) {
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
	BC.Set_registre();

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
				update_BC(bq, boost::asio::io_service io_service);
			}
		}
	}
}

