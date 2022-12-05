#include "testxw.h"

wxIMPLEMENT_APP(App);

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
    SetStatusText("Bienvenue dans le gestionnaire de votre banque!");

    Bind(wxEVT_MENU, &Fenetre::OnAbout, this, wxID_ABOUT);

}

void Fenetre::OnAbout(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser("https://www.google.com/search?q=qu%27est-ce+qu%27une+banque&oq=qu%27est-ce+qu%27une+banque&aqs=chrome..69i57j0i512l9.9756j0j7&sourceid=chrome&ie=UTF-8");
}