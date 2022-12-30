#include "load_save_Json.h"
#include "../PROJET PROG S1 2022/Fonctions/Threadfonctions.h"
#include "../PROJET PROG S1 2022/Fonctions/Def_id.h"


using namespace std;



int main()
{
	Banque_Centrale bq;
	Banque_Decentralise BD;

	Client cl1 = Client(1, "John", "McClain", "3 Rue de la paix", "Lille", 68.8);
	Compte cl11("FR00068801", 1, 3334);
	Compte cl12("FR00168801", 1, 13323);
	Compte_Epargnes cl13("FR10068801",1, 10, 1);
	vector<Compte> liste_comptes;
	vector<Compte_Epargnes> liste_comptes2;
	liste_comptes.push_back(cl11);
	liste_comptes.push_back(cl12);
	liste_comptes2.push_back(cl13);
	cl1.Set_liste_comptes(liste_comptes);
	cl1.Set_liste_comptes_epargnes(liste_comptes2);
	
	cout << generateIDCompte("FR", cl1, false);

	Client cl2 = Client(2, "Jane", "McClain", "3 Rue de la paix", "Lille", 60.7);
	cl2.Set_liste_comptes(vector<Compte> {Compte("FR00060702",2,0)});

	Client cl3 = Client(3, "Jude", "McClain", "67 Rue Vlad", "Moscou", 64.5);
	cl3.Set_liste_comptes(vector<Compte> {Compte("RU00064503", 3, 167)});
	cl3.Set_liste_comptes_epargnes(vector<Compte_Epargnes> {Compte_Epargnes("RU10064503", 3, 1000, 1)});

	Client cl4 = Client(4, "Jim", "McClain", "46 Rue du partage", "Pekin", 69.9);
	cl4.Set_liste_comptes(vector<Compte> {Compte("CH00069904", 4, 257),Compte("CH00169904",4,148)});
	cl4.Set_liste_comptes_epargnes(vector<Compte_Epargnes> {Compte_Epargnes("CH10069904", 4, 678, 1)});

	BD.Ajouter_au_registre(cl1);
	BD.Ajouter_au_registre(cl2);
	BD.Ajouter_au_registre(cl3);
	BD.Ajouter_au_registre(cl4);

	doTransaction("25/12/2020","FR00068801", "RU00064503", 250, BD, BD);

	bq.Set_registre(BD.Get_registre_local());
	
	std::ofstream file_out("registre_BC.json");
	write_json(file_out, bq.GeneratePtreeBanque());
	file_out.close();

	std::ifstream file_in("registre_BC.json");
	ptree in;
	read_json(file_in, in);
	auto test = Banque_from_ptree(in);
	file_out.close();



}