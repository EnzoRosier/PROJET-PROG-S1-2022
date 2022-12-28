#pragma once
#include "Def_id.h"
#include <string>

// Afin d'avoir des id uniques on va en créer à partir des informations du client 
// La structure de l'id sera : id_banque_decentralise 

string generateIDCompte(string pays, Client& cl, bool isEpargne) {

	string result = "XX";


	result[0] = (char)toupper(pays[0]);
	result[1] = (char)toupper(pays[1]);

	if (isEpargne) {
		result = result + "1";
	}
	else {
		result = result + "0";
	}

	int numCompte = cl.Get_liste_comptes().size() + cl.Get_liste_comptes_epargnes().size();

	if (numCompte < 10)
	{
		result = result + "0" + to_string(numCompte);
	}
	else {
		result = result + to_string(numCompte);
	}

	result = result + to_string(cl.Get_id());

	return result;

}
