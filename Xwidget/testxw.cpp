#include "testxw.h"
#include <string>

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



bool App::OnInit()
{
    Fenetre* frame = new Fenetre();
    frame->Show(true);
    return true;
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
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &Fenetre::OnLogin, this, 1);
    Bind(wxEVT_MENU, &Fenetre::OnRegister, this, 2);
}

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
        // Ici il faut mettre le traitement du login (r�cup�rer le registre)
        */

        bool connected = true;

        if (connected == true) {
            FenetreEspacePerso* frame_espace_perso = new FenetreEspacePerso(NULL, wxID_ANY);
            frame_espace_perso->SetBackgroundColour(wxColour(*wxWHITE));
            frame_espace_perso->Show(true);
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
        auto agence = nouveau_client->get_agence();
        auto taille = nouveau_client->get_taille();
        //auto account_number = nouveau_client->get_account_numbers();

        string new_prenom = prenom.ToStdString();
        string new_nom = nom.ToStdString();
        string new_adresse = adresse.ToStdString();
        string new_agence = agence.ToStdString();
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

        if (agence == "")
        {
            wxMessageBox("Veuillez entrer une agence valide",
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
        Client new_client(ID, new_nom, new_prenom, new_adresse, new_agence, new_taille);

        map <int, Client> registre_local;
        registre_local.emplace(1,new_client);

        wxMessageBox("Y'a pas d'erreur", "Error ", wxOK | wxICON_INFORMATION);
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
    Close(true);
}

void Fenetre::OnHelp(wxCommandEvent& event) {

}

CreationClient::CreationClient(wxWindow* parent, wxWindowID id, const wxString& title) : wxDialog(parent, id, title) //, position, size, style)
{
    auto client_firstname = new wxStaticText(this, -1, "Firstname : ", wxPoint(10, 20), wxSize(120, 20));
    auto client_name = new wxStaticText(this, -1, "Name", wxPoint(10, 50), wxSize(120, 20));
    auto client_adresse = new wxStaticText(this, -1, "Adresse", wxPoint(10, 80), wxSize(120, 20));
    auto client_agence = new wxStaticText(this, -1, "Agence", wxPoint(10, 110), wxSize(120, 20));
    auto client_taille = new wxStaticText(this, -1, "Taille (en pouce)", wxPoint(10, 140), wxSize(120, 20));

    wxString tab[] = { "Test", "Test2" };

    edit_firstname_ = new wxTextCtrl(this, -1, "", wxPoint(160, 20), wxSize(100, 20));
    edit_name_ = new wxTextCtrl(this, -1, "", wxPoint(160, 50), wxSize(100, 20));
    edit_adresse_ = new wxTextCtrl(this, -1, "", wxPoint(160, 80), wxSize(100, 20));
    edit_agence_ = new wxComboBox(this, -1, "", wxPoint(160, 110), wxSize(100, 100), sizeof(tab)/sizeof(wxString), tab);
    edit_taille_ = new wxTextCtrl(this, -1, "", wxPoint(160, 140), wxSize(100, 20));



    wxButton* ok = new wxButton(this, wxID_OK, _("OK"), wxPoint(10, 180), wxDefaultSize);
    wxButton* cancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(100, 180), wxDefaultSize);


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

wxString CreationClient::get_agence() {
    return edit_agence_->GetValue();
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
    * Si on r�cup�re le client � la connexion on peut y acc�der directement
    * Sinon : requ�te serveur correspondant au nom du client
    * 
    //
    */
    // Tableau rempli par le retour de la requ�te faite pr�c�demment
    int numero_compte[] = { 32,112,114 };
    int nb_comptes = sizeof(numero_compte) / sizeof(int);
    string final_str;
    for (int i = 0; i < nb_comptes; i++) {
        int montant = 100 + i;
        string montant_str = std::to_string(montant);
        string str1 = "Le montant de votre compte courant num�ro ";

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
        string str1 = "Le montant de votre compte epargne num�ro ";

        string numero_compte_str = std::to_string(numero_compte[i]);
        str1 += numero_compte_str;

        string str2 = " est : ";

        str1 += str2;

        str1 += montant_str;
        str1 += "\n";
        final_str += str1;
    }

    wxMessageBox(final_str,
        "Consulter compte epargne ", wxOK | wxICON_INFORMATION);
    return;
}

void FenetreEspacePerso::OnTransaction(wxCommandEvent& event) {
    Transactionwx* transac = new Transactionwx(this, wxID_ANY, "Test");
    transac->Show(true);
    if (transac->ShowModal() == wxID_OK)
    {
        auto receveur_number = transac->get_receveur_number();
        auto somme_transaction = transac->get_somme_transaction();

        long number;

        long account_numbers;

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

        if (!somme_transaction.ToLong(&number))
        {
            wxMessageBox("Error number transaction",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }

        if (!somme_transaction.ToLong(&account_numbers))
        {
            wxMessageBox("Transaction numbers",
                "Error ", wxOK | wxICON_INFORMATION);
            return;
        }

        /*
        // Ici il faut mettre l'envoie de la requ�te au serveur
        */


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
    menuComptes->Append(7, "Voir ses comptes �pargnes");

    wxMenu* menuEnvoyer = new wxMenu;
    menuEnvoyer->Append(8, "Envoyer");

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(9, "Besoin d'aide ?");


    wxMenuBar* menu = new wxMenuBar;
    //menu->Append(menuTest, "Test");
    menu->Append(menuComptes, "Consulter");
    menu->Append(menuEnvoyer, "Transaction");
    menu->Append(menuHelp, "&Help");


    //vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);

    SetMenuBar(menu);

    CreateStatusBar();
    SetStatusText("Bienvenue dans votre espace personnel !");

    Bind(wxEVT_MENU, &FenetreEspacePerso::OnConsulterCourant, this, 6);
    Bind(wxEVT_MENU, &FenetreEspacePerso::OnConsulterEpargne, this, 7);
    Bind(wxEVT_MENU, &FenetreEspacePerso::OnTransaction, this, 8);
    Bind(wxEVT_MENU, &FenetreEspacePerso::OnAbout, this, 9);
}

wxString Transactionwx::get_receveur_number() {
    return edit_receveur_number_->GetValue();
}

wxString Transactionwx::get_somme_transaction() {
    return edit_somme_transaction_->GetValue();
}

Transactionwx::Transactionwx(wxWindow* parent, wxWindowID id, const wxString& title) : wxDialog(parent, id, title) {
    auto text_receveur_number = new wxStaticText(this, -1, "Num�ro de compte cr�diteur: ", wxPoint(20, 20), wxSize(130, 30));
    auto text_somme_transaction = new wxStaticText(this, -1, "Somme � transmettre: ", wxPoint(20, 60), wxSize(130, 30));

    edit_receveur_number_ = new wxTextCtrl(this, -1, "", wxPoint(180, 20), wxSize(100, 20));
    edit_somme_transaction_ = new wxTextCtrl(this, -1, "", wxPoint(180, 60), wxSize(100, 20));

    wxButton* ok = new wxButton(this, wxID_OK, _("OK"), wxPoint(10, 90), wxDefaultSize);
    wxButton* cancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(100, 90), wxDefaultSize);
}