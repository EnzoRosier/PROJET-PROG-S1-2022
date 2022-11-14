#include "../includer.h"

class Banque_Centrale {
private: 
	map <int, Clients> registre;
public:
	int Chercher_client(int num_client);
	int Chercher_num_compte(int num_compte);
	Clients Chercher_infos_clients(int num_client);
};


class Banque_Decentralise : Banque_Centrale {
private:
	int num_banque;
	map <int, Clients> registre_local;
public:
	void Transaction(int num_compte_receveur);
	Clients Consulter;
};