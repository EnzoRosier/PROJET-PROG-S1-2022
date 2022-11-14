#include "../includer.h"
#include "../Client/Client.h"
#include "../Compte/Compte.h"

class Banque_Centrale {
private: 
	map <int, Client> registre;
public:
	int Chercher_client(int num_client);
	int Chercher_num_compte(int num_compte);
	Client Chercher_infos_clients(int num_client);
};


class Banque_Decentralise : Banque_Centrale {
private:
	int num_banque;
	map <int, Client> registre_local;
public:
	void Transaction(int num_compte_receveur);
	Client Consulter;
};