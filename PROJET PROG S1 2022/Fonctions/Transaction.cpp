#include "../includer.h"
#include "../../Client/Client.h"
#include "../../Banque/Banque.h"

#ifndef __TRANSACTION
#define __TRANSACTION


Transaction doTransaction(string date, string debiteur, string crediteur, int montant, Banque_Decentralise& B_debiteur, Banque_Decentralise& B_crediteur) {
	Transaction transac = {date,montant,debiteur,crediteur};

	Compte& Debit = Compte();
	Compte& Credit = Compte();
	Client& clDebit = Client();

	for (auto itr1 = B_debiteur.Get_registre_local().begin(); itr1 != B_debiteur.Get_registre_local().end(); ++itr1) {
		Client& clDebit = (*itr1).second;
		for (auto itr2 = clDebit.Get_liste_comptes().begin(); itr2 != clDebit.Get_liste_comptes().end(); itr2++)
		{
			if (itr2->get_Identifiant_Compte() == debiteur)
			{
				itr1->second.Ajouter_transaction(transac);
				itr2->set_Solde_Compte(itr2->get_Solde_Compte() - montant);
				Debit = *itr2;
			}
		}
	}

	for (auto itr1 = B_crediteur.Get_registre_local().begin(); itr1 != B_crediteur.Get_registre_local().end(); ++itr1) {
		Client& cl = itr1->second;
		for (auto itr2 = cl.Get_liste_comptes().begin(); itr2 != cl.Get_liste_comptes().end(); itr2++)
		{
			if (itr2->get_Identifiant_Compte() == crediteur)
			{
				itr1->second.Ajouter_transaction(transac);
				itr2->set_Solde_Compte(itr2->get_Solde_Compte() + montant);
				Debit = *itr2;
			}
		}
	}

	double solde_debit = Debit.get_Solde_Compte();
	Debit.set_Solde_Compte(solde_debit - montant);

	double solde_credit = Credit.get_Solde_Compte();
	Credit.set_Solde_Compte(solde_credit + montant);

	clDebit.Ajouter_transaction(transac);
	B_crediteur.Chercher_infos_clients(Credit.get_Id_proprietaire()).Ajouter_transaction(transac);

	return transac;
}

#endif