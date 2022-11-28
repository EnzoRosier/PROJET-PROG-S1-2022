#include "Client.h"

int main() {
	Compte* c1 = new Compte("1", 334);
	Compte* c2 = new Compte("2", 323);
	Compte_Epargnes* c3 = new Compte_Epargnes("3", 10, 50);
	vector<Compte*> liste_comptes;
	liste_comptes.push_back(c1);
	liste_comptes.push_back(c2);
	liste_comptes.push_back(c3);

	Client cl1 = Client(0, "John", "McClain", "3 Rue de la paix", "Lille", 68.8, liste_comptes);
	cl1.affiche_client();

	std::ofstream file_out("Compte.json");
	write_json(file_out, cl1.generate_Ptree_Client());
	file_out.close();

}