#include "../PROJET PROG S1 2022/includer.h"
#include "../Compte/Compte.h"
#include "../Client/Client.h"
#include "Banque.h"


Banque_Centrale::Banque_Centrale() {
	map <int, Client, greater<>> registre;
	nb_banque_decentralise = 0;
}

void Banque_Centrale::Set_nb_banque_decentralise(int incrementation) {
	nb_banque_decentralise += incrementation;
}

int Banque_Centrale::Get_nb_banque_decentralise() {
	return nb_banque_decentralise;
}



Client Banque_Centrale::Chercher_infos_clients(int num_client) {
	for (auto itr = registre.begin(); itr != registre.end(); ++itr) {
		auto id = itr->second.Get_id();
		if (id == num_client) {
			return (itr->second);
		}
	}
	return;
}

void Banque_Centrale::Ajouter_au_registre(Client ID) {
	registre.emplace(ID.Get_id(), ID);
}

void Banque_Centrale::Clear_registre() {
	registre.clear();
}

/***********************************************************
* 
* 
* D�finition Banque_Decentralise
* 
* 
***********************************************************/

Banque_Decentralise::Banque_Decentralise() {
	string nom_agence_temp;
	cout << "Entrez le nom de la banque decentralise : " << endl;
	cin >> nom_agence_temp;
	
	nom_agence = nom_agence_temp;

	map <int, Client> registre_local;

	ID_agence = Get_nb_banque_decentralise() + 1;

	Set_nb_banque_decentralise(1);
}

int Banque_Decentralise:: Get_ID_agence() {
	return ID_agence;
}

string Banque_Decentralise:: Get_nom_agence() {
	string nom_agence_temp = nom_agence;
	return nom_agence_temp;
}

map <int, Client> Banque_Decentralise::Get_registre_local(){
	return registre_local;
}

void Banque_Decentralise::Consulter() {
	cout << "\nLe \"registre\" local est : \n";
	cout << "\tCle\tElement\n";
	for (auto itr = registre_local.begin(); itr != registre_local.end(); ++itr) {
		cout << '\t' << itr->first
			<< '\t' << itr->second << '\n';
	}
	cout << endl;
}

void Banque_Decentralise::Ajouter_au_registre(Client new_client) {
	if (registre_local.size() != 0) {
		auto itr = registre_local.end();
		auto last_ind = itr->first;
		last_ind++;
	}
	else {
		auto last_ind = 1;
	}
	registre_local.insert(pair <int, Client>(new_client.Get_id(), new_client));
}


void Banque_Decentralise::Supprimer_du_registre(Client Compte_client) {
	for (auto itr = registre_local.begin(); itr != registre_local.end(); ++itr) {
		if (itr->second.Get_id() == Compte_client.Get_id()) {
			registre_local.erase(itr);
			cout << "Suppression reussie" << endl;
		}
		else {
			cout << "Error registre_local erase" << endl;
		}
	}
	/*auto itr = registre_local.begin();
	while (itr->second != Compte_client && itr != registre_local.end()) {
		itr++;
	}
	if (itr->second == Compte_client) {

	}*/
}