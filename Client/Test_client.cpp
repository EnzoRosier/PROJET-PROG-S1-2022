#include "Client.h"

int main() {
	Compte c1("1", 334);
	Compte c2("2", 323);
	Compte_Epargnes c3("3",0, 10, 50);
	vector<Compte> liste_comptes;
	vector<Compte_Epargnes> liste_comptes2;
	liste_comptes.push_back(c1);
	liste_comptes.push_back(c2);
	liste_comptes2.push_back(c3);

	Client cl1 = Client(0, "John", "McClain", "3 Rue de la paix", "Lille", 68.8);
	cl1.Set_liste_comptes(liste_comptes);
	cl1.Set_liste_comptes_epargnes(liste_comptes2);
	cl1.affiche_client();

	std::ofstream file_out("Compte.json");
	write_json(file_out, cl1.generate_Ptree_Client());
	file_out.close();

}