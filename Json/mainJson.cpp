#include "load_save_Json.h"
#include "../PROJET PROG S1 2022/Fonctions/Threadfonctions.h"


using namespace std;



int main()
{
	Banque_Centrale bq;
	Banque_Decentralise BD;

	Client cl1 = Client(0, "John", "McClain", "3 Rue de la paix", "Lille", 68.8);
	Compte cl11("FR00068800", 0, 3334);
	Compte cl12("FR00168800", 0, 13323);
	Compte_Epargnes cl13("FR10068800",0, 10, 50);
	vector<Compte> liste_comptes;
	vector<Compte_Epargnes> liste_comptes2;
	liste_comptes.push_back(cl11);
	liste_comptes.push_back(cl12);
	liste_comptes2.push_back(cl13);
	cl1.Set_liste_comptes(liste_comptes);
	cl1.Set_liste_comptes_epargnes(liste_comptes2);
	
	Client cl2 = Client(1, "Jane", "McClain", "3 Rue de la paix", "Lille", 60.7);
	cl2.Set_liste_comptes(vector<Compte> {Compte("FR00060701", 1, 315)});

	Client cl3 = Client(2, "Jude", "McClain", "67 Rue Vlad", "Moscou", 64.5);
	cl3.Set_liste_comptes(vector<Compte> {Compte("RU00064502", 2, 167)});
	cl3.Set_liste_comptes_epargnes(vector<Compte_Epargnes> {Compte_Epargnes("RU10064502", 2, 1000, 3)});

	Client cl4 = Client(3, "Jim", "McClain", "46 Rue du partage", "Pekin", 69.9);
	cl3.Set_liste_comptes(vector<Compte> {Compte("CH00069903", 3, 257),Compte("CH001699",3,148)});
	cl3.Set_liste_comptes_epargnes(vector<Compte_Epargnes> {Compte_Epargnes("CH10069903", 3, 678, 3)});

	BD.Ajouter_au_registre(cl1);
	BD.Ajouter_au_registre(cl2);
	BD.Ajouter_au_registre(cl3);
	BD.Ajouter_au_registre(cl4);

	doTransaction("25/12/2020","FR00068800", "RU00064502", 250, BD, BD);

	bq.Set_registre(BD.Get_registre_local());
	
	std::ofstream file_out("Registre.json");
	write_json(file_out, bq.GeneratePtreeBanque());
	file_out.close();

	std::ifstream file_in("registre_BC.json");
	ptree in;
	read_json(file_in, in);
	auto test = Banque_from_ptree(in);
	file_out.close();

}