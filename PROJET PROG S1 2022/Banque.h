#include "Banque.h"

class Banque_Centrale {
private: 
	map <int, Clients> registre;
public:
	int Chercher_client(int num_client);
	Clients Chercher_infos_clients(int num_client);
};