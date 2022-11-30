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
    menu2->Append(1, "Aide");
    menu2->AppendSeparator();

    wxMenuBar* menu = new wxMenuBar;
    menu->Append(menu1, "Test");
    menu->Append(menu2, "&Aide");

    SetMenuBar(menu);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

}