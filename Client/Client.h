#pragma once
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "../PROJET PROG S1 2022/includer.h"
#include "../Compte/Compte.h"

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


#ifndef __CLIENT_H
#define __CLIENT_H

typedef struct transaction {
	string date;
	int montant;
	string id_debiteur;
	string id_crediteur;

	template <class Archive>
		void serialize(Archive& ar, unsigned int version)
		{
			ar &date &montant &id_debiteur &id_crediteur;
		}
}Transaction;


class Client {
private:
	int id;
	string nom;
	string prenom;
	string adresse;
	string agence;
	float taille_en_pouces;
	vector<Transaction> archive_transaction; // Transaction de la forme <date, Transaction>
	vector<Compte> liste_comptes;

public:
	Client(const int& id=0,const string& nom="Pierre", const string& prenom = "Jacques", const string& adresse = "", const string& agence = "Paris", const float& taille_en_pouces = 65.5);
	int Get_id() const;
	string Get_nom();
	string Get_prenom();
	string Get_adresse();
	string Get_agence();
	float Get_taille_en_pouces();
	vector<Transaction> Get_archive_transaction();
	vector<Compte> Get_liste_comptes();
	void Set_nom(string& nouv_nom);
	void Set_prenom(string& nouv_prenom);
	void Set_adresse(string& nouv_adresse);
	void Set_agence(string& nouv_agence);
	void Set_taille_en_pouces(float& nouv_taille_en_pouces);
	void Set_archive_transaction(vector<Transaction>& nouv_archive_transaction);
	void Set_liste_comptes(vector<Compte>& nouv_liste_comptes);
	void Ajouter_transaction(Transaction& transaction);
	void Ajouter_compte(Compte compte);
	void affiche_client();
	ptree generate_Ptree_Client();

	template <class Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar& id& nom& prenom& adresse& agence& archive_transaction &liste_comptes;
	}

}; 

#endif 