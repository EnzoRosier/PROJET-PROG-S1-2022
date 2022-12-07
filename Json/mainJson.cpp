#include "load_save_Json.h"
#include "../PROJET PROG S1 2022/Fonctions/Transaction.h"

using namespace std;



int main()
{
	Compte* c1 = new Compte("TESTINGO", 0, 334);
	Compte* c2 = new Compte("2", 1, 323);
	Compte_Epargnes* c3 = new Compte_Epargnes("3", 10, 50);
	vector<Compte*> liste_comptes;
	vector<Compte*> liste_comptes2;
	liste_comptes.push_back(c1);
	liste_comptes2.push_back(c2);
	liste_comptes2.push_back(c3);
	Banque_Centrale bq;
	

	Client cl1 = Client(0, "John", "McClain", "3 Rue de la paix", "Lille", 68.8);
	Client cl2 = Client(1, "Joh2", "McClai2", "3 Rue de la paix", "Lille", 68.8);
	cl1.Set_liste_comptes(liste_comptes);
	cl2.Set_liste_comptes(liste_comptes2);
	cl1.affiche_client();

	bq.Ajouter_au_registre(cl1);
	bq.Ajouter_au_registre(cl2);

	doTransaction("202", "TESTINGO", "2", 2, bq);
	
	std::ofstream file_out("test.json");
	write_json(file_out, bq.Chercher_infos_clients(0).generate_Ptree_Client());
	file_out.close();

	std::ifstream file_in("test.json");
	ptree in;
	read_json(file_in, in);
	auto test = Client_from_ptree(in);
	file_out.close();

}