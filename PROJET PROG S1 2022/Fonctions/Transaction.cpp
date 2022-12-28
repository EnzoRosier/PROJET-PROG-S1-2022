#include "../includer.h"
#include "../../Client/Client.h"
#include "../../Banque/Banque.h"

#ifndef __TRANSACTION
#define __TRANSACTION


Transaction doTransaction(string date, string debiteur, string crediteur, int montant, Banque_Decentralise& B_debiteur, Banque_Decentralise& B_crediteur) {
	Transaction transac = {date,montant,debiteur,crediteur};

	Compte Debit = B_debiteur.Chercher_compte_clients(debiteur);
	Compte Credit = B_crediteur.Chercher_compte_clients(crediteur);

	double solde_debit = Debit.get_Solde_Compte();
	Debit.set_Solde_Compte(solde_debit - montant);

	double solde_credit = Credit.get_Solde_Compte();
	Debit.set_Solde_Compte(solde_credit + montant);
	B_debiteur.Chercher_infos_clients(Debit.get_Id_proprietaire()).Ajouter_transaction(transac);
	B_crediteur.Chercher_infos_clients(Credit.get_Id_proprietaire()).Ajouter_transaction(transac);

	return transac;
}

#endif