#include "tools.cpp"

/*
Types de requêtes avec la banque centrale (IP : 1234):
    - Init : la banque centrale fait un premier envoi pour intialiser les BD, reçoit un registre
    - Update : la banque centrale met à jour sa base de donnée en collectant la base de donnée de la banque décentralisée
               reçoit un string ("Update") et envoie un registe map<int,Client>
    - Find : Pour retrouver un compte,envoie un id de compte, reçoit un client
             La reception est de la forme "Find Id_compte_recherche"
    - Exit : Pour fermer l'executable et sauvegarder le registre, envoie un string ("Exit") et ne reçoit rien

Types de requêtes avec l'interface (IP : 0123):
    - Login : L'interface tente de se connecter, reçoit un string "LoginId_client", renvoie un client ou une réponse négative
    - Add_cust : L'interface crée un nouveau client, reçoit un client et le renvoie
    - Transaction : L'interface crée une demande de transaction, reçoit un string ("Transactionid_debiteurid_crediteurmontant") et renvoie un client
*/

map<string,Banque_Decentralise> init_BD(map<int, Client> g_registre) {
    // On recoit un registre complet et on va le compartimenter en un vector contenant chaque BD

    map<string,Banque_Decentralise> all_BD;
    vector<string> agences = { "Lille","Pekin","Moscou" }; // Les noms des agences
    map<int, Client> temp; // Registre temporaire
    int id = 0;
    for (string& name:agences) {
        for (pair<int, Client> elem : g_registre) {
            
            if (name == elem.second.Get_agence()) {
                temp.emplace(elem);
            }
        }
        all_BD.emplace(pair<string,Banque_Decentralise> (name,Banque_Decentralise (id, name,temp)));
        id++; // On incrèmente l'id pour le suivant
        temp.clear(); // On vide temp
    }
    return all_BD;
}




int main() {
    boost::asio::io_service io_service;
    tcp::acceptor acceptor_BC(io_service, tcp::endpoint(tcp::v4(), 1234)); // Banque centrale
    tcp::acceptor acceptor_CL(io_service, tcp::endpoint(tcp::v4(), 0123)); // Interface
    tcp::socket socket_CL(io_service);
    tcp::socket socket_BC(io_service);
    string demande = {};
    char retour[1000] = {};
    boost::system::error_code error;
    string date;

    
    acceptor_BC.accept(socket_BC);
    

    // Au lancement il faut attendre le INIT de la BC
    size_t length = socket_BC.read_some(boost::asio::buffer(retour), error);
    cout << "Init received" << endl;

    // On récupère le registre de la BC
    map<int, Client> temp_registre = get_data_from_string<map<int, Client>>(retour);

    map<string,Banque_Decentralise> all_BD = init_BD(temp_registre);
    cout << "Init complete" << endl;

    cout << temp_registre.size() << endl;

    //thread updateThread_BD(update_BD, ref(all_BD));


    Banque_Decentralise current_BD=all_BD["Lille"]; // On prend Lille comme étant la banque actuelle par défaut
    
    acceptor_CL.accept(socket_CL);
    
    int updator = 0;
    bool exit = false;
    while (!exit) {
        cout << "Enter BD while" << endl;
        // On se met en attente d'une requête de l'interface
        
        size_t length = socket_CL.read_some(boost::asio::buffer(retour), error);
        updator++; // On ajoute un à l'updator, toutes les 5 requêtes on fait une mise à jour à la BC

        // Une fois qu'on a la requête, on l'analyse

        if (string(retour).substr(0,4) == "Exit") {
            exit = true;
            // On va remettre tous les registres des BD en un registre complet à renvoyer à la BC
            map<int, Client> registre_complet = registre_exit(all_BD);
            cout << "Exit received from user" << endl;

            
            // On doit prévenir la BC de l'exit
            demande = "Exit";
            demande.append(get_string_from_data(registre_complet));
            boost::asio::write(socket_BC, boost::asio::buffer(demande), error);
            
            
            cout << "Exit sent to BC" << endl;

            
        }


        if (string(retour).substr(0, 5) == "Login") { // L'interface tente de se connecter à un compte
            cout << "Login received from user" << endl;
            int id_client = atoi(string(retour).substr(5, string(retour).size() - 5).c_str());
            bool match = false;
            auto it = all_BD.begin();
            while (it != all_BD.end() && !match) { // On va chercher le client dans l'ensemble des BD
                it->second.Chercher_infos_clients(id_client).affiche_client();
                if (id_client == it->second.Chercher_infos_clients(id_client).Get_id()) { // Si on trouve un match
                    current_BD = it->second; // On se met sur la bonne BD
                    match = true;


                    // On peut donc renvoyer le client à l'interface
                    demande = get_string_from_data(current_BD.Chercher_infos_clients(id_client));
                    boost::asio::write(socket_CL, boost::asio::buffer(demande), error);
                    cout << "Client connected sucessfuly" << endl;
                }
                it++;
            }
            if (!match) {
                demande = "Fail";
                boost::asio::write(socket_CL, boost::asio::buffer(demande), error);
                cout << "Client connection failed" << endl;
            }
        }


        if (string(retour).substr(0, 8) == "Add_cust") {
            cout << "New customer received" << endl;
            Client nouv_client = get_data_from_string<Client>(string(retour).substr(8, string(retour).size() - 8).c_str());

            // On doit maintenant ajouter le client au registre
            // Pour cela on va d'abord trouver la BD dans laquelle ajouter le client
            string agence = nouv_client.Get_agence();
            for (auto it = all_BD.begin(); it != all_BD.end();it++) {
                if (agence == it->second.Get_nom_agence()) {
                    current_BD = it->second;
                    current_BD.Ajouter_au_registre(nouv_client);
                }
            }

            // Le client à été ajouté il faut le renvoyer pour que l'interface puisse le connecter

            
            demande = get_string_from_data(nouv_client);
            boost::asio::write(socket_CL, boost::asio::buffer(demande), error);
            cout << "New client connected succesfully" << endl;
            nouv_client.affiche_client();
            
        }

        if (string(retour).substr(0, 7) == "Add_acc") { // Si c'est pour une mise à jour d'un client suite à un ajout de compte
            cout << "Received Add account request" << endl;
            Client client_maj = get_data_from_string<Client>(string(retour).substr(7, string(retour).size() - 7).c_str());
            current_BD.Supprimer_du_registre(current_BD.Chercher_infos_clients(client_maj.Get_id())); // On enlève l'ancien
            cout << "New Account sucessfully added" << endl;
            current_BD.Ajouter_au_registre(client_maj); // Pour le remplacer par sa mise à jour
            cout << "New Account sucessfully added" << endl;
        }

        if (string(retour).substr(0, 11) == "Transaction") {  
            cout << "Transaction request received" << endl;
            // Requête de transaction de la forme "Transactionid_débiteurid_crediteurmontant"
            string id_debiteur = string(retour).substr(12, 10); // L'id d'un compte à une longueur de 10
            string id_crediteur = string(retour).substr(22, 10);
            int montant = atoi(string(retour).substr(32, string(retour).size() - 31).c_str());

            // On doit trouver la BD à laquelle appartient le crediteur de la transaction
            
            if (current_BD.Chercher_compte_clients(id_crediteur).get_Identifiant_Compte() == "-1") { // Si le client n'est pas dans la BD actuelle
                
                Banque_Decentralise B_crediteur;
                // On doit donc interroger la BC pour trouver la banque du crediteur
                
                demande = "Find";
                demande.append(id_crediteur);
                boost::asio::write(socket_BC, boost::asio::buffer(demande), error);
                cout << "Asking the BC for creditor informations" << endl;

                // On attend ensuite la réponse de la BC

                size_t length = socket_BC.read_some(boost::asio::buffer(retour), error);
                cout << "Creditor received from BC" << endl;
                B_crediteur = all_BD[get_data_from_string<Client>(retour).Get_agence()];
 
                doTransaction(date,id_debiteur,id_crediteur,montant,current_BD, all_BD[B_crediteur.Get_nom_agence()]);


                
            }
            else { // Sinon c'est que notre client est dans la banque acutelle
                doTransaction(date,id_debiteur,id_crediteur,montant,current_BD, current_BD);
            }
            // Maintenant que la transaction a été effectuée on doit mettre à jour all_BD
            all_BD[current_BD.Get_nom_agence()] = current_BD;

            // On doit renvoyer le client mis à jour à l'interface

            Client client_maj = current_BD.Chercher_infos_clients(current_BD.Chercher_compte_clients(id_debiteur).get_Id_proprietaire());
            demande = get_string_from_data(client_maj);
            boost::asio::write(socket_CL, boost::asio::buffer(demande), error);
            cout << "Updated client sent to user" << endl;
        }

        if (updator == 5) {
            updator = 0;

            
            demande = "Update";
            demande+=get_string_from_data(registre_exit(all_BD));
            boost::asio::write(socket_BC, boost::asio::buffer(demande), error);
            
            
        }
    }

    int i;
    cin >> i;
    return EXIT_SUCCESS;
}

