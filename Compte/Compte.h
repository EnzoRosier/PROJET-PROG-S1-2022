#pragma once
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "../PROJET PROG S1 2022/includer.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

#ifndef __COMPTE_H
#define __COMPTE_H

class Compte {
protected:
	string identifiant_Compte;
	int id_Proprietaire;
	double solde_Compte;
public:
	Compte(const string& id="", int id_Prop = 0, int solde = 0); // Constructeur
	~Compte(); // Desctructeur
	double get_Solde_Compte() const; // Permet de récupérer le solde du compte
	string get_Identifiant_Compte() const; // Permet de récupérer l'identifiant du compte
	int set_Solde_Compte(double newSolde); // Permet de modifier le solde du compte
	ptree generate_Ptree_Compte();
	int get_Id_proprietaire();
	friend ostream& operator<<(ostream& os, Compte& c);


	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar& identifiant_Compte &id_Proprietaire &solde_Compte;
	}
};


class Compte_Epargnes {
private:
	string identifiant_Compte;
	int id_Proprietaire;
	double solde_Compte;
	double taux_Epargne;
public:
	Compte_Epargnes(const string& id="", int id_Prop=0, double solde=0, double taux=0);
	double get_taux();
	double get_Solde_Compte() const; // Permet de récupérer le solde du compte
	string get_Identifiant_Compte() const; // Permet de récupérer l'identifiant du compte
	int set_Solde_Compte(double newSolde); // Permet de modifier le solde du compte
	void set_taux_compte(double taux);
	ptree generate_Ptree_Compte();
	int get_Id_proprietaire();

	friend ostream& operator<<(ostream& os, Compte_Epargnes& c);


	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar& identifiant_Compte& id_Proprietaire& solde_Compte& taux_Epargne;
	}

};


#endif