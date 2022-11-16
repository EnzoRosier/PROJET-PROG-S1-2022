#pragma once
#include "../includer.h"
#include "Banque.h"

Banque_Decentralise::Banque_Decentralise() {
	Afficher_banque_decentralise();
	string nom_agence_temp;
	cout << "Entrez le nom de la banque decentralise : " << endl;
	cin >> nom_agence_temp;
	
	nom_agence = nom_agence_temp;
	map <int, Client> registre_local;
}

void Banque_Decentralise::Consulter() {
	cout << "\nLe \"registre\" local est : \n";
	cout << "\tCle\tElement\n";
	for (auto itr = registre_local.begin(); itr != registre_local.end(); ++itr) {
		cout << '\t' << itr->first
			<< '\t' << itr->second << '\n';
	}
	cout << endl;
}

void Banque_Decentralise::Ajouter_au_registre(Client new_client) {
	
}