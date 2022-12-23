#include "../PROJET PROG S1 2022/includer.h"
#include "Compte.h"

Compte::Compte(const string& id,int id_Prop, int solde) : identifiant_Compte(id), id_Proprietaire(id_Prop), solde_Compte(solde) {
	cout << "Nouveau compte cree id : '" << id << "', solde : " << solde << "\n";
}

Compte::~Compte() {
	cout << "Compte '" << this->identifiant_Compte << "' detruit\n";
}

string Compte::get_Identifiant_Compte() const {
	cout << "Demande identifiant compte : '" << this->identifiant_Compte << "'\n";
	return this->identifiant_Compte;
}

double Compte::get_Solde_Compte() const {
	cout << "Demande solde compte : '" << this->identifiant_Compte << "'\n";
	return this->solde_Compte;
}

int Compte::set_Solde_Compte(double newSolde) {
	this->solde_Compte = newSolde;
	cout << "Solde du compte : '" << this->identifiant_Compte << "' modifie avec la nouvelle valeur : " << this->solde_Compte << "\n";
	return 1;
}

ostream& operator<<(ostream& os, Compte& c) {
	return os << c.identifiant_Compte << " -> " << c.solde_Compte;
}

ptree Compte::generate_Ptree_Compte() {
	ptree result;
	result.put("Id", this->identifiant_Compte);
	result.put("Id_Proprietaire", id_Proprietaire);
	result.put("Solde", this->solde_Compte);
	return result;
}

int Compte::get_Id_proprietaire() {
	return this->id_Proprietaire;
}


Compte_Epargnes::Compte_Epargnes(const string& id, int id_Prop, double solde, double taux) {
	identifiant_Compte = id;
	id_Proprietaire = id_Prop;
	solde_Compte = solde;
	taux_Epargne = taux;
}

string Compte_Epargnes::get_Identifiant_Compte() const {
	cout << "Demande identifiant compte : '" << this->identifiant_Compte << "'\n";
	return this->identifiant_Compte;
}

int Compte_Epargnes::get_Id_proprietaire() {
	return this->id_Proprietaire;
}

double Compte_Epargnes::get_Solde_Compte() const {
	cout << "Demande solde compte : '" << this->identifiant_Compte << "'\n";
	return this->solde_Compte;
}

double Compte_Epargnes::get_taux() {
	return this->taux_Epargne;
}


int Compte_Epargnes::set_Solde_Compte(double newSolde) {
	this->solde_Compte = newSolde;
	cout << "Solde du compte : '" << this->identifiant_Compte << "' modifie avec la nouvelle valeur : " << this->solde_Compte << "\n";
	return 1;
}

void Compte_Epargnes::set_taux_compte(double taux) {
	taux_Epargne = taux;
}

ostream& operator<<(ostream& os, Compte_Epargnes& c) {
	return os << c.identifiant_Compte << " -> " << c.solde_Compte << " (" << c.taux_Epargne << "%)"<<endl;
}

ptree Compte_Epargnes::generate_Ptree_Compte() {
	ptree result;
	result.put("Id", this->identifiant_Compte);
	result.put("Id_Proprietaire", id_Proprietaire);
	result.put("Solde", this->solde_Compte);
	result.put("Taux_Epargne", this->taux_Epargne);
	return result;
}

