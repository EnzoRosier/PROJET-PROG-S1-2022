#include "../includer.h"
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

int Banque_Centrale::Chercher_num_compte(int num_compte) {
	auto result = 0;
	for (auto itr = registre.begin(); itr != registre.end(); ++itr) {
		if (itr->second.Get_liste_comptes().begin() == num_compte)
		auto result = itr->second.find(num_compte);
	}
	if (result != registre.end()) {
		cout << "Numero de client trouve :" << endl;
		cout << result << endl;
		return result;
	}
	else {
		cout << "Num client not found" << endl;
		return 0;
	}
}

Client Banque_Centrale::Chercher_infos_clients(int num_client) {
	auto result;
	for (auto itr = registre.begin(); itr != registre.end(); ++itr) {
		auto result = itr->first.find(num_client);
	}
	if (result != registre.end()) {
		cout << "Numero de client trouve :" << endl;
		cout << result << endl;
		return result;
	}
	else {
		cout << "Num client not found" << endl;
		return 0;
	}
}

void Banque_Centrale::Ajouter_au_registre(Client ID) {
	registre.emplace(ID.Get_id, ID);
}

void Banque_Centrale::Clear_registre() {
	registre.clear();
}

/***********************************************************
* 
* 
* Définition Banque_Decentralise
* 
* 
***********************************************************/

Banque_Decentralise::Banque_Decentralise() {
	Afficher_banque_decentralise();
	string nom_agence_temp;
	cout << "Entrez le nom de la banque decentralise : " << endl;
	cin >> nom_agence_temp;
	
	nom_agence = nom_agence_temp;

	map <int, Client> registre_local;

	registre.insert(pair<string, Banque_Decentralise>(nom_agence, registre_local));

	int nb_banque = Get_nb_banque_decentralise() + 1;
	ID_agence = nb_banque;

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
	registre_local.insert(pair <int, Client>(new_client.Get_id(), new_client);
}


void Banque_Decentralise::Supprimer_du_registre(Client Compte_client) {
	auto result = registre_local.find(Compte_client);
	if (result != registre_local.end()) {
		registre_local.erase(result);
		cout << "Suppression reussie" << endl;
	}
	else {
		cout << "Error registre_local erase" << endl;
	}
	/*auto itr = registre_local.begin();
	while (itr->second != Compte_client && itr != registre_local.end()) {
		itr++;
	}
	if (itr->second == Compte_client) {

	}*/
}