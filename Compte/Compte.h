#include "../PROJET PROG S1 2022/includer.h"

#ifndef __COMPTE_H
#define __COMPTE_H

class Compte {
private:
	const string identifiant_Compte;
	double solde_Compte;
public:
	Compte(const string& id=0, int solde = 0); // Constructeur
	~Compte(); // Desctructeur
	double get_Solde_Compte() const; // Permet de récupérer le solde du compte
	string get_Identifiant_Compte() const; // Permet de récupérer l'identifiant du compte
	int set_Solde_Compte(double newSolde); // Permet de modifier le solde du compte
	friend ostream& operator<<(ostream& os, Compte& c);
};


class Compte_Epargnes : Compte {
private:
	double taux_Epargne;
};


#endif