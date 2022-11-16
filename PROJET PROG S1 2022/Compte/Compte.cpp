#include "../includer.h"
#include "Compte.h"

Compte::Compte(const string& id, int solde) : identifiant_Compte(id), solde_Compte(solde) {
	cout << "Nouveau compte créé id : " << id << ", solde : " << solde << "\n";
}

Compte::~Compte() {
	cout << "Compte " << this->identifiant_Compte << "detruit\n";
}

string Compte::get_Identifiant_Compte() const {
	cout << "Demande identifiant compte : " << this->identifiant_Compte << "\n";
	return this->identifiant_Compte;
}

double Compte::get_Solde_Compte() const {
	cout << "Demande solde compte : " << this->identifiant_Compte << "\n";
	return this->solde_Compte;
}

int Compte::set_Solde_Compte(double& newSolde) {
	this->solde_Compte = newSolde;
	cout << "Solde du compte : " << this->identifiant_Compte << "modifié avec la nouvelle valeur : " << this->solde_Compte << "\n";
	return 1;
}

ostream& operator<<(ostream& os, Compte c) {
	return os << c.identifiant_Compte << " -> " << c.solde_Compte << "\n";
}