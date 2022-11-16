#include "../includer.h"

Client::Client(const int& id, string& nom, string& prenom, string& adresse, string& agence, float& taille_en_pouces, vector<Compte*>& liste_compte) {
	this->id = id;
	this->nom = nom;
	this->prenom = prenom;
	this->adresse = adresse;
	this->agence = agence;
	this->taille_en_pouces;
	this->liste_compte = liste_compte;
}

int Client::Get_id() const {
	return this->id;
}

string Client::Get_nom() {
	return this->nom;
}

string Client::Get_prenom() {
	return this->prenom;
}

string Client::Get_adresse() {
	return this->adresse;
}

string Client::Get_agence() {
	return this->agence;
}

float Client::Get_taille_en_pouces() {
	return this->taille_en_pouces;
}

vector<Transaction> Client::Get_archive_transaction() {
	return this->archive_transaction;
}

vector<Compte*> Client::Get_liste_comptes() {
	return this->liste_comptes;
}

void Client::Set_nom(string& nouv_nom) {
	nom = nouv_nom;
}

void Client::Set_prenom(string& nouv_prenom) {
	prenom = nouv_prenom;
}

void Client::Set_adresse(string& nouv_adresse) {
	adresse = nouv_adresse;
}

void Client::Set_agence(string& nouv_agence) {
	agence = nouv_agence;
}

void Client::Set_taille_en_pouces(float& nouv_taille_en_pouces) {
	taille_en_pouces = nouv_taille_en_pouces;
}

void Client::Set_archive_transaction(vector<Transaction>& nouv_archive_transaction) {
	archive_transaction = nouv_archive_transaction;
}

void Client::Set_liste_comptes(vector<Compte*>& nouv_liste_comptes) {
	liste_comptes = nouv_liste_comptes;
}

void Client::Ajouter_transaction(Transaction& transaction, string& date) {
	archive_transaction.emplace(date, Transaction);
}