#include "testxw.h"

wxIMPLEMENT_APP(App);

bool App::Init()
{
    Fenetre* frame = new Fenetre();
    frame->Show(true);
    SetTopWindow(frame);

    return true;
}

Fenetre::Fenetre() : wxFrame(nullptr, wxID_ANY, "Test Banque", wxPoint(30, 100), wxSize(1920, 1080))
{
    wxMenu* menu1 = new wxMenu;
    menu1->Append(1,"&Test_1\tCtrl A","Test 1");
    menu1->AppendSeparator();

    menu1->Append(3, "Test 3");
    menu1->AppendSeparator();

    menu1->Append(2, "Test 2");
    menu1->AppendSeparator();

    wxMenu* menu2 = new wxMenu;
    menu2->Append(1, "https://www.google.com/search?q=qu%27est-ce+qu%27une+banque&oq=qu%27est-ce+qu%27une+banque&aqs=chrome..69i57j0i512l9.9756j0j7&sourceid=chrome&ie=UTF-8", "Aide");
    menu2->AppendSeparator();

    wxMenuBar* menu = new wxMenuBar;
    menu->Append(menu1, "Test");
    menu->Append(menu2, "&Aide");

    Bind(wxEVT_MENU, &Fenetre::OnExit, this, wxID_EXIT);
}