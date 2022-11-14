#include "../includer.h"
#include "../Compte/Compte.h"

class Client {
private:
	const int id;
	string nom;
	string prenom;
	string adresse;
	string agence;
	float taille_en_pouces;

	vector<Compte*> liste_compte;
};
public:
