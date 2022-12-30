#include "Threadfonctions.h"

void epargneCalcule(Banque_Centrale& bq) {
    for (auto& itr : bq.registre)
    {
        auto tmp = itr.second.Get_liste_comptes_epargnes();
        for (auto& itr2 : tmp) {
            itr2.set_Solde_Compte(itr2.get_taux() * itr2.get_Solde_Compte());
        }
        itr.second.Set_liste_comptes_epargnes(tmp);
    }
}

void epargneThread(Banque_Centrale& bq) 
{
    while (true) {
        int n = 100;
        time_t start, end;
        start = time(0);
        while (1)
        {

            if (time(0) - start >= n)
            {
                
                epargneCalcule(bq);
                start = time(0);
                
            }
        }
    }
}

