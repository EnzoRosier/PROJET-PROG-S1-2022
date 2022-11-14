#pragma once
#include "../includer.h"
#include "../Compte/Compte.h"
#include "../Client/Client.h"

class Banque_Centrale {
private: 
	map <int, Client> registre;
	int nb_banque_decentralise;
public:
	int Chercher_client(int num_client);
	int Chercher_num_compte(int num_compte);
	Client Chercher_infos_clients(int num_client);
	void Afficher_banque_decentralise();
	void Update_registre();
};


class Banque_Decentralise : Banque_Centrale {
private:
	int num_banque;
	map <int, Client> registre_local;
public:
	Banque_Decentralise();
	void Transaction(int num_compte_receveur);
	Client Consulter();
};