#include "Compte.h"

Compte::Compte(const string& id const, int solde = 0) : identifiant_Compte(id), solde_Compte(solde) {
	cout << "Nouveau compte cr�� id : " << id << ", solde : " << solde;
}