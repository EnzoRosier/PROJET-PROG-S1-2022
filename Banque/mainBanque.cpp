#include "Banque.h"

using namespace std;

int main()
{
	Banque_Centrale test;

	Banque_Decentralise truc;
	Banque_Decentralise truc2;

	Compte jesaispas("FR3", 100);
	//Client Toto(2, "Tata", "Toto", "Rue machin", "Lille", 42, jesaispas);


	cout << "ID agence : " << truc.Get_ID_agence() << " Nom agence : " << truc.Get_nom_agence() << endl;
	cout << "ID agence : " << truc2.Get_ID_agence() << " Nom agence : " << truc2.Get_nom_agence() << endl;
	return 0;
}