#include "../includer.h"
#include "../Compte/Compte.h"
#include "../Client/Client.h"

class Banque_Centrale {
private: 
	map <string, Banque_Decentralise> registre;
	int nb_banque_decentralise;
protected:
	void Set_nb_banque_decentralise(int incrementation);
public:
	int Get_nb_banque_decentralise();
	Banque_Centrale();
	int Chercher_num_compte(int num_compte);
	Client Chercher_infos_clients(int num_client);
	void Ajouter_au_registre(Banque_Decentralise ID);
	void Clear_registre();
};


class Banque_Decentralise : Banque_Centrale {
private:
	const int ID_agence;
	string nom_agence;
	map <int, Client> registre_local;
public:
	Banque_Decentralise();
	string Get_nom_agence();
	int Get_ID_agence();
	map <int, Client> Get_registre_local();
	void Ajouter_au_registre(Client new_client);
	void Supprimer_du_registre(Client Compte_client);
	//void Transaction(int num_compte_receveur);
	void Consulter();
};