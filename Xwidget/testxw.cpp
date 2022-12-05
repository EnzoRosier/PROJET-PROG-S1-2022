#include "testxw.h"

wxIMPLEMENT_APP(App);
// On définit les ID suivants :
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
    menu1->Append(1,"&Test_1\tCtrl A","Test 1");
    menu1->AppendSeparator();

    menu1->Append(3, "Test 3");
    menu1->AppendSeparator();

    menu1->Append(2, "Test 2");
    menu1->AppendSeparator();

    wxMenu* menu2 = new wxMenu;
    menu2->Append(1, "Login");

    wxMenu* menu3 = new wxMenu;
    menu3->Append(1, "Create");

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
}

void Fenetre::OnLogin(wxCommandEvent& event) {

}

void Fenetre::OnRegister(wxCommandEvent& event) {

}

void Fenetre::OnAddAccount(wxCommandEvent& event) {

}

void Fenetre::OnDelAccount(wxCommandEvent& event) {

}

void Fenetre::OnAccount(wxCommandEvent& event) {

}
    SetStatusText("Bienvenue dans le gestionnaire de votre banque!");

    Bind(wxEVT_MENU, &Fenetre::OnAbout, this, wxID_ABOUT);

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
    auto text_customer_number = new wxStaticText(this, -1, "Customer Number: ", wxPoint(10, 20), wxSize(180, 20));
    auto client_firstname = new wxStaticText(this, -1, "Firstname : ", wxPoint(10, 50), wxSize(180, 20));
    auto client_name = new wxStaticText(this, -1, "Name", wxPoint(10, 80), wxSize(180, 20));


    edit_firstname_ = new wxTextCtrl(this, -1, "", wxPoint(160, 50), wxSize(100, 20));
    edit_name_= new wxTextCtrl(this, -1, "", wxPoint(160, 50), wxSize(100, 20));



    wxButton* ok = new wxButton(this, wxID_OK, _("OK"), wxPoint(10, 120), wxDefaultSize);
    wxButton* cancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(100, 120), wxDefaultSize);
void Fenetre::OnAbout(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser("https://www.google.com/search?q=qu%27est-ce+qu%27une+banque&oq=qu%27est-ce+qu%27une+banque&aqs=chrome..69i57j0i512l9.9756j0j7&sourceid=chrome&ie=UTF-8");
}