#include "../includer.h"
#include "../../Compte/Compte.h"
#include <optional>

typedef struct transaction {
	int montant;
	string id_debiteur;
	string id_crediteur;
}Transaction;

class Client {
private:
	const int id;
	string nom;
	string prenom;
	string adresse;
	string agence;
	float taille_en_pouces;
	optional<multimap<string,Transaction>> archive_transaction; // Transaction de la forme <date, Transaction>
	vector<Compte*> liste_comptes;

public:
	Client(const int& id, string& nom, string& prenom, string& adresse, string& agence, float& taille_en_pouces, vector<Compte*>& liste_compte);
	~Client();
	int Get_id() const;
	string Get_nom();
	string Get_prenom();
	string Get_adresse();
	string Get_agence();
	float Get_taille_en_pouces();
	vector<Transaction> Get_archive_transaction();
	vector<Compte*> Get_liste_comptes();
	void Set_nom(string& nouv_nom);
	void Set_prenom(string& nouv_prenom);
	void Set_adresse(string& nouv_adresse);
	void Set_agence(string& nouv_agence);
	void Set_taille_en_pouces(float& nouv_taille_en_pouces);
	void Set_archive_transaction(vector<Transaction>& nouv_archive_transaction);
	void Set_liste_comptes(vector<Compte*>& nouv_liste_comptes);
	void Ajouter_transaction(Transaction& transaction, string& date);
	void Ajouter_compte(Compte* compte);
	void affiche_client();
};
