#pragma once
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "../PROJET PROG S1 2022/includer.h"
#include "../Compte/Compte.h"
#include "../Client/Client.h"

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

#ifdef _WIN32
#include <SDKDDKVer.h>
#endif

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
	map<int, Client> Get_registre();
	int Get_nb_banque_decentralise();
	void Set_registre(map<int, Client> nouv_registre);
	Client& Chercher_infos_clients(int num_client);
	Compte Chercher_compte_clients(string num_compte);
	void Ajouter_au_registre(Client ID);
	void Clear_registre();
	ptree GeneratePtreeBanque();
	friend void epargneCalcule(Banque_Centrale& bq);

	template<class Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar& registre& nb_banque_decentralise;
	}
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
	void Consulter();

	template<class Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar& ID_agence& nom_agence& registre_local;
	}
};

#endif // !__BANQUE_H