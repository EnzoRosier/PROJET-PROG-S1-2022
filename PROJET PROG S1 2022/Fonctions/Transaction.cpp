#include "../includer.h"
#include "../../Client/Client.h"
#include "../../Banque/Banque.h"

#ifndef __TRANSACTION
#define __TRANSACTION


pair<string, Transaction> transaction(string date, string debiteur, string crediteur, int montant, Banque_Centrale Banque) {
	Transaction transac = {montant,debiteur,crediteur};

	Compte Debit = Banque.Chercher_compte_clients(debiteur);
	Compte Credit = Banque.Chercher_compte_clients(crediteur);

	double solde_debit = Debit.get_Solde_Compte();
	Debit.set_Solde_Compte(solde_debit - montant);

	double solde_credit = Credit.get_Solde_Compte();
	Debit.set_Solde_Compte(solde_credit + montant);

	return make_pair(date, transac);
}

#endif