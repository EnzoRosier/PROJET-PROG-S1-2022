#include "../PROJET PROG S1 2022/includer.h"
#include "../Compte/Compte.h"
#include "../Client/Client.h"

#ifndef __BANQUE_H
#define __BANQUE_H


class Banque_Centrale {
private: 
	map <int, Client> registre;
	int nb_banque_decentralise;
protected:
	void Set_nb_banque_decentralise(int incrementation);
public:
	Banque_Centrale();
	int Get_nb_banque_decentralise();
	Client Chercher_infos_clients(int num_client);
	void Ajouter_au_registre(Client ID);
	void Clear_registre();
};


class Banque_Decentralise : Banque_Centrale {
private:
	int ID_agence;
	string nom_agence;
	map <int, Client> registre_local;
public:
	Banque_Decentralise();
	string Get_nom_agence();
	int Get_ID_agence();
	map <int, Client> Get_registre_local();
	void Ajouter_au_registre(Client new_client);
	void Supprimer_du_registre(Client Compte_client);
	//void Transaction(int num_compte_receveur);
	void Consulter();
};

#endif // !__BANQUE_H