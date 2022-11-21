#include "../PROJET PROG S1 2022/includer.h"
#include "../Compte/Compte.h"

#ifndef __CLIENT_H
#define __CLIENT_H



typedef struct transaction {
	int montant;
	string id_debiteur;
	string id_crediteur;
}Transaction;


class Client {
private:
	int id;
	string nom;
	string prenom;
	string adresse;
	string agence;
	float taille_en_pouces;
	multimap<string,Transaction> archive_transaction; // Transaction de la forme <date, Transaction>
	vector<Compte*> liste_comptes;

public:
	Client(int id, string& nom, string& prenom, string& adresse, string& agence, float& taille_en_pouces, vector<Compte*>& liste_compte);
	int Get_id() const;
	string Get_nom();
	string Get_prenom();
	string Get_adresse();
	string Get_agence();
	float Get_taille_en_pouces();
	multimap<string, Transaction>
	Get_archive_transaction();
	vector<Compte*> Get_liste_comptes();
	void Set_nom(string& nouv_nom);
	void Set_prenom(string& nouv_prenom);
	void Set_adresse(string& nouv_adresse);
	void Set_agence(string& nouv_agence);
	void Set_taille_en_pouces(float& nouv_taille_en_pouces);
	void Set_archive_transaction(multimap<string, Transaction>& nouv_archive_transaction);
	void Set_liste_comptes(vector<Compte*>& nouv_liste_comptes);
	void Ajouter_transaction(Transaction& transaction, string& date);
	void Ajouter_compte(Compte* compte);
	void affiche_client();

}; 

#endif __CLIENT_H