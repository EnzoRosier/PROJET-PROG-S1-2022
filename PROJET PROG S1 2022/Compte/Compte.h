#include "includer.h"

class Compte {
private:
	const string identifiant_Compte;
	double solde_Compte;
public:
	Compte(const string& id const, int solde = 0);
	Compte~;
};

class Compte_Courant : Compte {

};

class Compte_Epargnes : Compte {

};