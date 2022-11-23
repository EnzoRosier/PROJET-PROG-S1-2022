#include "Client.h"
#include "../Compte/Compte.h"

int main() {
	Compte* c1 = new Compte("1", 334);
	Compte* c2 = new Compte("2", 323);
	Compte_Epargnes* c3 = new Compte_Epargnes("3", 10, 50);
	vector<Compte*> liste_comptes = {c1,c2,c3};
	cout << liste_comptes.size() << endl;
	

}