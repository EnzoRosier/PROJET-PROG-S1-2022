// PROJET PROG S1 2022.cpp : définit le point d'entrée de l'application.
//

#include "PROJET PROG S1 2022.h"
#include "Compte/Compte.h"
using namespace std;

int main()
{
	Compte A = Compte("AZE");
	cout << A << "\n";
	cout << A.get_Solde_Compte() << "\n";
	cout << A.get_Identifiant_Compte() << "\n";
	A.set_Solde_Compte(345.65);
	cout << A << "\n";
	return 0;
}
