#include "testxw.h"
#include "LoginManagement.h"
#include <string>
#include <time.h>
#include "../PROJET PROG S1 2022/Fonctions/Def_id.h"
#include "../Sockets/tools.cpp"

wxIMPLEMENT_APP(App);
// On d�finit les ID suivants :
// 1:login
// 2:register
// 3:ajout compte
// 4:suppression compte
// 5:consultation compte
// 6:retour d'un cran
// 7:accueil
// >10: Pour l'affichage des comptes

string nom_agence_decentralise = "";
Client current_client;

// On définit le nécessaire pour l'envoi de sockets

boost::asio::io_service io_service;
tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 0123));
tcp::socket socket_(io_service);
string demande = {};
char retour[1000] = {};
boost::system::error_code error;


bool App::OnInit()
{
    Fenetre* frame = new Fenetre();
    frame->Show(true);
    return true;
}

ChoixBanque::ChoixBanque(wxWindow* parent, wxWindowID id, const wxString& title) : wxDialog(parent, id, title) {
    
    auto client_agence = new wxStaticText(this, -1, "Agence", wxPoint(10, 20), wxSize(50, 20));

    wxString tab[] = { "Lille", "Pekin", "Moscou"};

    edit_agence_ = new wxComboBox(this, -1, "", wxPoint(160, 20), wxSize(100, 100), sizeof(tab) / sizeof(wxString), tab);


    wxButton* ok = new wxButton(this, wxID_OK, _("OK"), wxPoint(10, 60), wxDefaultSize);
    wxButton* cancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(100, 60), wxDefaultSize);

}

wxString ChoixBanque::get_agence() {
    return edit_agence_->GetValue();
}

string ChoixBanque::get_nom_agence() {
    return this->nom_agence;
}

void ChoixBanque::edit_nom_agence(string new_nom_agence) {
    this->nom_agence = new_nom_agence;
}

Fenetre::Fenetre() : wxFrame(nullptr, wxID_ANY, "Test Banque", wxPoint(30, 30), wxSize(1000, 600))
{
    wxMenu* menu1 = new wxMenu;
    menu1->Append(3,"&Test_1\tCtrl A","Test 1");
    menu1->AppendSeparator();

    menu1->Append(4, "Test 3");
    menu1->AppendSeparator();

    menu1->Append(5, "Test 2");
    menu1->AppendSeparator();

    wxMenu* menu2 = new wxMenu;
    menu2->Append(1, "Login");

    wxMenu* menu3 = new wxMenu;
    menu3->Append(2, "Create");

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);


    wxMenuBar* menu = new wxMenuBar;
    menu->Append(menu1, "Test");
    menu->Append(menu2, "Login");
    menu->Append(menu3, "Create");
    menu->Append(menuHelp, "&Help");


    //vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);

    SetMenuBar(menu);

    CreateStatusBar();
    SetStatusText("Bienvenue dans le gestionnaire de votre banque!");

    Bind(wxEVT_MENU, &Fenetre::OnLogin, this, 1);
    Bind(wxEVT_MENU, &Fenetre::OnRegister, this, 2);

    ChoixBanque* choix = new ChoixBanque(this, wxID_ANY, "Choix de la Banque");
    choix->Show(true);
    if (choix->ShowModal() == wxID_OK) {
        nom_agence_decentralise = choix->get_agence();

        if (nom_agence_decentralise == "") {
            wxMessageBox("Vous devez choisir une agence",
                "Error ", wxOK | wxICON_INFORMATION);
            ChoixBanque* new_choix = new ChoixBanque(this, wxID_ANY, "ChoixBanque");
            new_choix->Show(true);
        }
        choix->edit_nom_agence(nom_agence_decentralise);
    }
}

//int login_num_client = 1;
string login_mdp_client = "";

/*string login_nom = "";
string login_prenom = "";
string login_adresse = "";
int taille_du_client = 65;

Client login_client(login_num_client, login_nom, login_prenom, login_adresse, nom_agence_decentralise, taille_du_client);
*/

void Fenetre::OnLogin(wxCommandEvent& event) {

    LoginClient* login = new LoginClient(this, wxID_ANY, "Test");
    login->Show(true);
    if (login->ShowModal() == wxID_OK)
    {
        auto customer_number = login->get_customer_number();
        auto customer_password = login->get_customer_password();

        long number;

        long account_numbers; 

        if (!customer_number.ToLong(&number))
        {
            wxMessageBox("Error number",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }

        if (!customer_number.ToLong(&account_numbers))
        {
            wxMessageBox("Account numbers",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }
        if (customer_password == "")
        {
            wxMessageBox("Veuillez entrer un mot de passe",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }

        /*
        // Ici il faut mettre le traitement du login
        */

        socket_.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 0123));
        string id_client = customer_number.ToStdString();

        demande = "Login";
        demande.append(id_client);  // La requête est de la forme "LoginId_client"

        boost::asio::write(socket_, boost::asio::buffer(demande), error);

        // Maintenant on doit attendre la réponse de la BD

        size_t length = socket_.read_some(boost::asio::buffer(retour), error);

        bool connected;

        if (string(retour) == "Fail") { // La réponse de la BD est soit fail soit un client 
            connected = false;
        }
        else { // Si ce n'est pas fail, la connexion à réussie et on peut connecter le client
            current_client = get_data_from_string<Client>(retour);
            connected = true;
        }


        string new_password = customer_password.ToStdString();
        int new_login = customer_number.ToInt(&new_login);
        
        map <int, string, greater<>> m;

        /*
        * Il faut prendre les numéros de comptes et les mots de passe du regsitre
        * et les insérer dans la map
            m.insert(pair <int, string>(user, psw));
        */


        if (connected == true) {
            //login_num_client = new_login;
            login_mdp_client = new_password;
            FenetreEspacePerso* frame_espace_perso = new FenetreEspacePerso(NULL, wxID_ANY);
            frame_espace_perso->SetBackgroundColour(wxColour(*wxWHITE));
            frame_espace_perso->Show(true);
            return;
        }
        else {
            wxMessageBox("Numéro de compte ou mot de passe invalide",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }
    }
}

void Fenetre::OnRegister(wxCommandEvent& event) {
    CreationClient* nouveau_client = new CreationClient(this, wxID_ANY, "Test");
    nouveau_client->Show(true);

    if (nouveau_client->ShowModal() == wxID_OK)
    {
        auto prenom = nouveau_client->get_firstname();
        auto nom = nouveau_client->get_name();
        auto adresse = nouveau_client->get_adresse();
        /*
        * Problème en dessous :
        * Il faut trouver un moyen d'envoyer l'information prise dans le premier 
        * menu (le nom de l'agence)
        * pour la mettre en paramètre en dessous
        */

        auto taille = nouveau_client->get_taille();
        //auto account_number = nouveau_client->get_account_numbers();

        string new_prenom = prenom.ToStdString();
        string new_nom = nom.ToStdString();
        string new_adresse = adresse.ToStdString();
        string new_taille_str = taille.ToStdString();

        int new_taille = stoi(new_taille_str);

        long number;

        long account_numbers;

        wxString string_agence;

        /*if (!customer_number.ToLong(&number))
        {
            wxMessageBox("Error number",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }*/

       /* if (!account_number.ToLong(&account_numbers))
        {
            wxMessageBox("Account numbers",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }*/

        if (prenom == "")
        {
            wxMessageBox("Veuillez remplir votre prenom",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }

        if (nom == "")
        {
            wxMessageBox("Veuillez remplir votre nom",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }

        if (adresse == "")
        {
            wxMessageBox("Veuillez remplir votre adresse",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }

        if (taille == ""&& !taille.ToLong(&number))
        {
            wxMessageBox("Veuillez entrer une taille valide",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }

        const int ID = 0;
        Client new_client(ID, new_nom, new_prenom, new_adresse, nom_agence_decentralise, new_taille);

        socket_.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 0123));

        // On a le nouveau client, il faut l'envoyer à la BD pour qu'elle se mette à jour
        demande = get_string_from_data(new_client);
        boost::asio::write(socket_, boost::asio::buffer(demande), error);

        // Maintenant on doit attendre la réponse de la BD

        size_t length = socket_.read_some(boost::asio::buffer(retour), error);
        current_client = get_data_from_string<Client>(retour);


        map <int, Client> registre_local;
        registre_local.emplace(1,new_client);

        wxMessageBox("Votre compte a bien été créé", "Error ", wxOK | wxICON_INFORMATION);
        return;

    }
}

void Fenetre::OnAddAccount(wxCommandEvent& event) {

}

void Fenetre::OnDelAccount(wxCommandEvent& event) {

}

void Fenetre::OnAccount(wxCommandEvent& event) {

}

void Fenetre::OnReturn(wxCommandEvent& event) {

}

void Fenetre::OnHome(wxCommandEvent& event) {

}

void Fenetre::OnExit(wxCommandEvent& event)
{
    // On doit prévenir la BD de l'exit
    socket_.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 0123));
    demande = "Exit";
    boost::asio::write(socket_, boost::asio::buffer(demande), error);
    Close(true);
}

void Fenetre::OnHelp(wxCommandEvent& event) {

}


CreationClient::CreationClient(wxWindow* parent, wxWindowID id, const wxString& title) : wxDialog(parent, id, title) //, position, size, style)
{
    auto client_firstname = new wxStaticText(this, -1, "Firstname : ", wxPoint(10, 20), wxSize(120, 20));
    auto client_name = new wxStaticText(this, -1, "Name", wxPoint(10, 50), wxSize(120, 20));
    auto client_adresse = new wxStaticText(this, -1, "Adresse", wxPoint(10, 80), wxSize(120, 20));
    auto client_taille = new wxStaticText(this, -1, "Taille (en pouce)", wxPoint(10, 110), wxSize(120, 20));


    edit_firstname_ = new wxTextCtrl(this, -1, "", wxPoint(160, 20), wxSize(100, 20));
    edit_name_ = new wxTextCtrl(this, -1, "", wxPoint(160, 50), wxSize(100, 20));
    edit_adresse_ = new wxTextCtrl(this, -1, "", wxPoint(160, 80), wxSize(100, 20));
    edit_taille_ = new wxTextCtrl(this, -1, "", wxPoint(160, 110), wxSize(100, 20));



    wxButton* ok = new wxButton(this, wxID_OK, _("OK"), wxPoint(10, 160), wxDefaultSize);
    wxButton* cancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(100, 160), wxDefaultSize);

}

void Fenetre::OnAbout(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser("https://www.google.com/search?q=qu%27est-ce+qu%27une+banque&oq=qu%27est-ce+qu%27une+banque&aqs=chrome..69i57j0i512l9.9756j0j7&sourceid=chrome&ie=UTF-8");
}


LoginClient::LoginClient(wxWindow* parent, wxWindowID id, const wxString& title) : wxDialog(parent, id, title)
{
    auto text_customer_number = new wxStaticText(this, -1, "Customer Number: ", wxPoint(10, 20), wxSize(110, 20));
    auto text_customer_password = new wxStaticText(this, -1, "Password: ", wxPoint(10, 50), wxSize(110, 20));

    edit_customer_number_ = new wxTextCtrl(this, -1, "", wxPoint(160, 20), wxSize(100, 20));
    edit_customer_password_ = new wxTextCtrl(this, -1, "", wxPoint(160, 50), wxSize(100, 20));

    wxButton* ok = new wxButton(this, wxID_OK, _("OK"), wxPoint(10, 90), wxDefaultSize);
    wxButton* cancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(100, 90), wxDefaultSize);

}

wxString LoginClient::get_customer_number() {
    return edit_customer_number_->GetValue();
}

wxString LoginClient::get_customer_password() {
    return edit_customer_password_->GetValue();
}

wxString CreationClient::get_customer_number() {
    return edit_customer_number_->GetValue();
}

wxString CreationClient::get_name() {
    return edit_name_->GetValue();
}

wxString CreationClient::get_firstname() {
    return edit_firstname_->GetValue();
}

wxString CreationClient::get_adresse() {
    return edit_adresse_->GetValue();
}

string CreationClient::get_agence(ChoixBanque name_of_banque) {
    return name_of_banque.get_nom_agence();
}

wxString CreationClient::get_account_numbers() {
    return edit_account_numbers_->GetValue();
}

wxString CreationClient::get_taille() {
    return edit_taille_->GetValue();
}

void FenetreEspacePerso::OnConsulterCourant(wxCommandEvent& event) {
    /*
    //
    *
    * Si on recupere le client a la connexion on peut y acceder directement
    * Sinon : requete serveur correspondant au nom du client
    * 
    //
    */
    // Tableau rempli par le retour de la requete faite precedemment
    int numero_compte[] = { 32,112,114 };
    int nb_comptes = sizeof(numero_compte) / sizeof(int);
    string final_str;
    for (int i = 0; i < nb_comptes; i++) {
        int montant = 100 + i;
        string montant_str = std::to_string(montant);
        string str1 = "Le montant de votre compte courant numéro ";

        string numero_compte_str = std::to_string(numero_compte[i]);
        str1 += numero_compte_str;

        string str2 = " est : ";

        str1 += str2;

        str1 += montant_str;
        str1 += "\n";
        final_str += str1;
    }

    wxMessageBox(final_str,
        "Consulter compte courant ", wxOK | wxICON_INFORMATION);
    return;
}

void FenetreEspacePerso::OnConsulterEpargne(wxCommandEvent& event) {
    /*
    //
    *
    * Si on r�cup�re le client � la connexion on peut y acc�der directement
    * Sinon : requ�te serveur correspondant au nom du client
    *
    //
    */
    // Tableau rempli par le retour de la requ�te faite pr�c�demment
    int numero_compte[] = {35,14};
    int nb_comptes = sizeof(numero_compte)/sizeof(int);
    string final_str;
    for (int i = 0; i < nb_comptes; i++) {
        int montant = 100+i;
        string montant_str = std::to_string(montant);
        string str1 = "Le montant de votre compte epargne numéro ";

        string numero_compte_str = std::to_string(numero_compte[i]);
        str1 += numero_compte_str;

        string str2 = " est : ";

        str1 += str2;

        str1 += montant_str;
        str1 += "\n";
        final_str += str1;
    }

    wxMessageBox(final_str,
        "Consulter compte épargne ", wxOK | wxICON_INFORMATION);
    return;
}

void FenetreEspacePerso::OnTransaction(wxCommandEvent& event) {
    Transactionwx* transac = new Transactionwx(this, wxID_ANY, "Test");
    transac->Show(true);
    if (transac->ShowModal() == wxID_OK)
    {
        auto receveur_number = transac->get_receveur_number();
        auto somme_transaction = transac->get_somme_transaction();
        auto envoyeur_number = transac->get_envoyeur_number();

        long number;

        long account_numbers;

        int new_somme_transaction;

        if (!receveur_number.ToLong(&number))
        {
            wxMessageBox("Error number receveur",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }

        if (!receveur_number.ToLong(&account_numbers))
        {
            wxMessageBox("Account receveur numbers",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }

        if (!somme_transaction.ToInt(&new_somme_transaction))
        {
            wxMessageBox("Error number transaction",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }

        time_t now = time(NULL);
        struct tm* tm = localtime(&now);
        

        transaction new_transaction;

        new_transaction.date = now;
        new_transaction.id_crediteur = receveur_number;
        new_transaction.id_debiteur = current_client.Get_id();
        new_transaction.montant = new_somme_transaction;

        /*
        // Ici il faut mettre l'envoi de la requ�te au serveur
        */
        socket_.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 0123));

        string id_debiteur = envoyeur_number;
        string id_crediteur = receveur_number;
        int montant = new_somme_transaction;


        demande = "Transaction";
        demande.append(id_debiteur);
        demande.append(id_crediteur);
        stringstream ss;
        ss << montant;
        demande.append(ss.str());

        boost::asio::write(socket_, boost::asio::buffer(demande), error);

        // Maintenant on doit se mettre en attente de la réponse de la BD
        size_t length = socket_.read_some(boost::asio::buffer(retour), error);
        Client current_user = get_data_from_string<Client>(retour);

    }
}

void FenetreEspacePerso::OnCreateAccount(wxCommandEvent& event) {
    creation_compte* nouveau_compte = new creation_compte(this, wxID_ANY, "Creation de compte");
    nouveau_compte->Show(true);
    if (nouveau_compte->ShowModal() == wxID_OK) {
        auto type_compte = nouveau_compte->get_type_de_compte();

        if (type_compte == "") {
            wxMessageBox("Il faut remplir le champ",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }
        else {
            if (type_compte == "Compte courant") {
                string generation_ID = generateIDCompte(nom_agence_decentralise, current_client, false);
                Compte new_compte(generation_ID, current_client.Get_id(), 0);
                current_client.Ajouter_compte(new_compte);
            }
            else if (type_compte == "Compte epargne") {
                string generation_ID = generateIDCompte(nom_agence_decentralise, current_client, true);
                Compte_Epargnes new_compte(generation_ID, current_client.Get_id(), 0, 3);
                current_client.Ajouter_compte_epargnes(new_compte);
            }
        }
        

        /*
        * Il faut créer un ID de compte
        * Il faut créer le nouveau compte dans le registre
        */

        // On doit prévenir la BD de cette modification
        socket_.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 0123));

        demande = "Add_acc";
        demande.append(get_string_from_data(current_client));
        boost::asio::write(socket_, boost::asio::buffer(demande), error);
        
    }
}

void FenetreEspacePerso::OnHelp(wxCommandEvent& event) {
    // Normal que ce soit vide 
}

void FenetreEspacePerso::OnAbout(wxCommandEvent& event) {
    wxLaunchDefaultBrowser("https://www.google.fr/search?q=comment+utiliser+internet&source=hp&ei=SUWQY9juJrmDkdUPxdqxiAs&iflsig=AJiK0e8AAAAAY5BTWZZlBgmJa1M0nTMU1DkxN9oQd66K&oq=Comment+utiliser+i+tern&gs_lcp=Cgdnd3Mtd2l6EAMYADIHCAAQgAQQDTIHCAAQgAQQDTIHCAAQgAQQDTIHCAAQgAQQDTIHCAAQgAQQDTIHCAAQgAQQDTIHCAAQgAQQDTIHCAAQgAQQDTIHCAAQgAQQDTIHCAAQgAQQDToECAAQQzoICC4QgwEQsQM6EQguEIAEELEDEIMBEMcBENEDOgsIABCABBCxAxCDAToOCC4QgAQQsQMQxwEQ0QM6CwguEIAEELEDEIMBOggIABCxAxCDAToICAAQgAQQsQM6BAgAEAM6BQguEIAEOgsILhCABBDHARDRAzoFCAAQgAQ6CwguEIAEELEDENQCOgoILhDHARDRAxBDOgUIABCxAzoHCAAQgAQQCjoGCAAQFhAeUABYtBhg4h9oAHAAeACAAUiIAZkJkgECMjOYAQCgAQE&sclient=gws-wiz");
}

void FenetreEspacePerso::OnExit(wxCommandEvent& event) {
    Close(true);
}

FenetreEspacePerso::FenetreEspacePerso(wxWindow* parent, wxWindowID id) : wxFrame(nullptr, wxID_ANY, "Espace personnel", wxPoint(30, 30), wxSize(1000, 600))
{
    /*wxMenu* menuTest = new wxMenu;
    menuTest->Append(11, "&Test_1\tCtrl A", "Test 1");
    menuTest->AppendSeparator();

    menuTest->Append(10, "Test 3");
    menuTest->AppendSeparator();

    menuTest->Append(9, "Test 2");*/

    wxMenu* menuComptes = new wxMenu;
    menuComptes->Append(6, "Voir ses comptes courants");
    menuComptes->AppendSeparator();
    menuComptes->Append(7, "Voir ses comptes épargnes");

    wxMenu* menuEnvoyer = new wxMenu;
    menuEnvoyer->Append(8, "Envoyer");

    wxMenu* menuCreerCompte = new wxMenu;
    menuCreerCompte->Append(10, "Creer un compte");

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(9, "Besoin d'aide ?");


    wxMenuBar* menu = new wxMenuBar;
    //menu->Append(menuTest, "Test");
    menu->Append(menuComptes, "Consulter");
    menu->Append(menuEnvoyer, "Transaction");
    menu->Append(menuCreerCompte, "Creer un compte");
    menu->Append(menuHelp, "&Help");


    //vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);

    SetMenuBar(menu);

    CreateStatusBar();
    SetStatusText("Bienvenue dans votre espace personnel !");

    Bind(wxEVT_MENU, &FenetreEspacePerso::OnConsulterCourant, this, 6);
    Bind(wxEVT_MENU, &FenetreEspacePerso::OnConsulterEpargne, this, 7);
    Bind(wxEVT_MENU, &FenetreEspacePerso::OnTransaction, this, 8);
    Bind(wxEVT_MENU, &FenetreEspacePerso::OnAbout, this, 9);
    Bind(wxEVT_MENU, &FenetreEspacePerso::OnCreateAccount, this, 10);
}

wxString Transactionwx::get_receveur_number() {
    return edit_receveur_number_->GetValue();
}

wxString Transactionwx::get_somme_transaction() {
    return edit_somme_transaction_->GetValue();
}

wxString Transactionwx::get_envoyeur_number() {
    return edit_envoyeur_number_->GetValue();
}

Transactionwx::Transactionwx(wxWindow* parent, wxWindowID id, const wxString& title) : wxDialog(parent, id, title) {
    auto text_receveur_number = new wxStaticText(this, -1, "Numero de compte crediteur: ", wxPoint(20, 20), wxSize(130, 30));
    auto text_somme_transaction = new wxStaticText(this, -1, "Somme a transmettre: ", wxPoint(20, 60), wxSize(130, 30));
    auto text_envoyeur_number = new wxStaticText(this, -1, "Numero de votre compte: ", wxPoint(20, 100), wxSize(130, 30));

    edit_receveur_number_ = new wxTextCtrl(this, -1, "", wxPoint(180, 20), wxSize(100, 20));
    edit_somme_transaction_ = new wxTextCtrl(this, -1, "", wxPoint(180, 60), wxSize(100, 20));
    edit_envoyeur_number_ = new wxTextCtrl(this, -1, "", wxPoint(180, 100), wxSize(100, 20));

    wxButton* ok = new wxButton(this, wxID_OK, _("OK"), wxPoint(10, 150), wxDefaultSize);
    wxButton* cancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(100, 150), wxDefaultSize);
}

wxString creation_compte::get_type_de_compte() {
    return edit_type_de_compte_->GetValue();
}

creation_compte::creation_compte(wxWindow* parent, wxWindowID id, const wxString& title) : wxDialog(parent, id, title) {
    auto type_de_compte = new wxStaticText(this, -1, "Type de compte: ", wxPoint(20, 20), wxSize(130, 30));

    wxString tab[] = { "Compte courant", "Compte epargne" };

    edit_type_de_compte_ = new wxComboBox(this, -1, "", wxPoint(160, 20), wxSize(100, 100), sizeof(tab) / sizeof(wxString), tab);

    wxButton* ok = new wxButton(this, wxID_OK, _("OK"), wxPoint(10, 50), wxDefaultSize);
    wxButton* cancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(100, 50), wxDefaultSize);
}