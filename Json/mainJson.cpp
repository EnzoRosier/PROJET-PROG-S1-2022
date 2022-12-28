#include "load_save_Json.h"
#include "../PROJET PROG S1 2022/Fonctions/Threadfonctions.h"


using namespace std;



int main()
{
	Compte c1("TESTINGO", 0, 334);
	Compte c2("2", 1, 323);
	Compte_Epargnes c3("3",2, 10, 50);
	vector<Compte> liste_comptes;
	vector<Compte_Epargnes> liste_comptes2;
	liste_comptes.push_back(c1);
	liste_comptes.push_back(c2);
	liste_comptes2.push_back(c3);
	Banque_Centrale bq;
	

	Client cl1 = Client(0, "John", "McClain", "3 Rue de la paix", "Lille", 68.8);
	Client cl2 = Client(1, "Joh2", "McClai2", "3 Rue de la paix", "Lille", 68.8);
	cl1.Set_liste_comptes(liste_comptes);
	cl2.Set_liste_comptes_epargnes(liste_comptes2);
	cl1.affiche_client();

	bq.Ajouter_au_registre(cl1);
	bq.Ajouter_au_registre(cl2);

	doTransaction("202", "TESTINGO", "2", 2, bq);
	
	std::ofstream file_out("test.json");
	write_json(file_out, bq.GeneratePtreeBanque());
	file_out.close();

	std::ifstream file_in("test.json");
	ptree in;
	read_json(file_in, in);
	auto test = Banque_from_ptree(in);
	file_out.close();

	saveThread(bq);

}