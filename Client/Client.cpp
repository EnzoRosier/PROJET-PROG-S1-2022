#include "Client.h"
#include "../Compte/Compte.h"


Client::Client(const int& id, const string& nom, const string& prenom, const string& adresse, const string&, const float& taille_en_pouces) {
	this->id = id;
	this->nom = nom;
	this->prenom = prenom;
	this->adresse = adresse;
	this->agence = agence;
	this->taille_en_pouces = taille_en_pouces;
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

vector<Compte> Client::Get_liste_comptes() {
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

void Client::Set_liste_comptes(vector<Compte>& nouv_liste_comptes) {
	liste_comptes = nouv_liste_comptes;
}

void Client::Ajouter_transaction(Transaction& transaction) {
	this->archive_transaction.push_back(transaction);
}

void Client::Ajouter_compte(Compte compte) {
	liste_comptes.push_back(compte);
}

void Client::affiche_client() {
	cout << "Numero de client : " << this->id << endl << "Informations personelles :" << endl << "  Bonjour Madame/Monsieur " << this->nom << " "
		<< this->prenom << endl << "  " << this->adresse << endl << "  Mesurant : " << this->taille_en_pouces << " pouces"
		<< endl << "Vous avez " << this->liste_comptes.size() << " comptes actuellement" << endl;
}

ptree Client::generate_Ptree_Client() {
	ptree result;

	result.put("Id", this->id);
	result.put("Nom", this->nom);
	result.put("Prenom", this->prenom);
	result.put("Adresse", this->adresse);
	result.put("Agence", this->agence);
	result.put("Taille", this->taille_en_pouces);
	ptree ptreeCompte;
	for (auto value : this->liste_comptes)
	{
		ptreeCompte.push_back({ "", value.generate_Ptree_Compte()});
	}
	result.push_back({ "Compte", ptreeCompte});

	ptree ptreeTransaction;
	for (auto value : this->archive_transaction)
	{
		ptree transInfo;
		transInfo.put("Date", value.date);
		ptree transInfo2;
		transInfo2.put("Crediteur", value.id_crediteur);
		transInfo2.put("Debiteur", value.id_debiteur);
		transInfo2.put("Montant", value.montant);
		transInfo.push_back({ "Info", transInfo2 });
		ptreeTransaction.push_back({ "", transInfo });
	}
	result.push_back({ "Trasactions", ptreeTransaction });

	return result;
}




