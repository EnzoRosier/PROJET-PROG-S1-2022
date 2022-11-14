#pragma once
#include "../includer.h"
#include "Banque.h"

Banque_Decentralise::Banque_Decentralise() {
	Afficher_banque_decentralise();
	cout << "Entrez le numéro de la banque decentralise : " << endl;
	cin >> num_banque_temp;

	num_banque = num_banque_temp;
	map <int, Client> registre_local;
}