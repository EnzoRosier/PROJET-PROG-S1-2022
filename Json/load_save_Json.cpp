#include "load_save_Json.h"


int save_json_registre(Banque_Centrale& bq) {
    std::ofstream file_out("RegistrePrincipale.json");
    write_json(file_out, bq.GeneratePtreeBanque());
    file_out.close();
    return 1;
}

Compte Compte_from_ptree(ptree &pt) {

    string id = pt.get<string>("Id");
    int id_prop = pt.get<int>("Id_Proprietaire", 0);
    float solde = pt.get<float>("Solde", 0.);

    Compte tmp(id, id_prop, solde);
    return tmp;
    
}

Client Client_from_ptree(ptree& pt) {

    int id = pt.get<int>("Id");
    string prenom = pt.get<string>("Prenom");
    string nom = pt.get<string>("Nom");
    string adresse = pt.get<string>("Adresse");
    float taille = pt.get<float>("Taille");
    string agence = pt.get<string>("Agence");

    Client tmp(move(id), move(nom), move(prenom), move(adresse), move(agence), move(taille));
    
    for (ptree::value_type& compte : pt.get_child("Compte")) {
        Compte* tmpCompte = new Compte(Compte_from_ptree(compte.second));
        tmp.Ajouter_compte(tmpCompte);
    }

    return tmp;

}

Banque_Centrale Banque_from_ptree(ptree& pt) {


    Banque_Centrale tmp = Banque_Centrale();
    for (ptree::value_type& client : pt.get_child("Registre")) {
        ofstream file_out("testeze.json");
        write_json(file_out, client.second.get_child("Client_Info"));
        file_out.close();
        tmp.Ajouter_au_registre(Client_from_ptree(client.second.get_child("Client_Info")));
    }

    return tmp;

}