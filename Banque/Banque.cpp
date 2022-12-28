#include "../PROJET PROG S1 2022/includer.h"
#include "../Compte/Compte.h"
#include "../Client/Client.h"
#include "Banque.h"




Banque_Centrale::Banque_Centrale() {
	map <int, Client, greater<>> registre;
	nb_banque_decentralise = 0;
}

map<int, Client> Banque_Centrale::Get_registre() {
	return this->registre;
}

void Banque_Centrale::Set_nb_banque_decentralise(int incrementation) {
	nb_banque_decentralise += incrementation;
}

int Banque_Centrale::Get_nb_banque_decentralise() {
	return nb_banque_decentralise;
}

void Banque_Centrale::Set_registre(map<int, Client> nouv_registre) {
	this->registre = nouv_registre;
}

Compte Banque_Centrale::Chercher_compte_clients(string num_compte) {
	try {
		for (auto itr = registre.begin(); itr != registre.end(); ++itr) {
			auto id = itr->second.Get_liste_comptes();
			for (int i = 0; i < id.size(); i++) {
				if (id.at(i).get_Identifiant_Compte() == num_compte) {
					return (id.at(i));
				}
			}
		}
		throw string("Pas de numero de compte trouve.");
	}
	catch (string const& chaine) //On rattrape les strings lanc�s
	{
		cerr << chaine << endl;
	}
}

Client& Banque_Centrale::Chercher_infos_clients(int num_client) {
	try {
		for (auto itr = registre.begin(); itr != registre.end(); ++itr) {
			auto id = itr->second.Get_id();
			if (id == num_client) {
				return (itr->second);
			}

		}
		throw string("Pas de numero client. Contactez un administrateur");
	}
	catch (string const& chaine) //On rattrape les strings lanc�s
	{
		cerr << chaine << endl;
	}
	return Client(-1); // Si on ne trouve rien on renvoie un client avec un ID de -1, pour signifier une erreur
}

void Banque_Centrale::Ajouter_au_registre(Client ID) {
	registre.emplace(ID.Get_id(), ID);
}

void Banque_Centrale::Clear_registre() {
	registre.clear();
}

ptree Banque_Centrale::GeneratePtreeBanque() {
	ptree result;
	result.put("Id_Banque_Centrale", this->nb_banque_decentralise);
	ptree ptreeRegistre;
	
	for (auto value : this->registre)
	{
		ptree _tmp;
		_tmp.put("Id_Client", value.first);
		_tmp.push_back({ "Client_Info", value.second.generate_Ptree_Client() });
		ptreeRegistre.push_back({ "", _tmp });
	}
	result.push_back({ "Registre", ptreeRegistre });

	return result;
}



/***********************************************************
* 
* 
* D�finition Banque_Decentralise
* 
* 
***********************************************************/

Banque_Decentralise::Banque_Decentralise() {
	this->nom_agence = "Lille";
	this->ID_agence = 0;
	map<int, Client> registre;
	cout << "COnstructeur" << registre.size() << endl;
	this->registre_local = registre;
}

Banque_Decentralise::Banque_Decentralise(int id, string agence, map <int, Client> registre) {
	this->ID_agence = id;
	this->nom_agence = agence;
	this->registre_local;
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
			<< '\t'; 
		itr->second.affiche_client(); 
		cout << '\n';
	}
	cout << endl;
}

void Banque_Decentralise::Ajouter_au_registre(Client new_client) {
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
}

Client& Banque_Decentralise::Chercher_infos_clients(int num_client) {
	for (auto itr = registre_local.begin(); itr != registre_local.end(); ++itr) {
		auto id = itr->second.Get_id();
		if (id == num_client) {
			return (itr->second);
		}
	}
	return Client(-1);
}

Compte Banque_Decentralise::Chercher_compte_clients(string num_compte) {
	for (auto itr = registre_local.begin(); itr != registre_local.end(); ++itr) {
		auto id = itr->second.Get_liste_comptes();
		for (int i = 0; i < id.size(); i++) {
			if (id.at(i).get_Identifiant_Compte() == num_compte) {
				return (id.at(i));
			}
		}
	}
	return Compte("-1"); // On renvoie un compte erreur si la recherche n'aboutit pas
}