#pragma once
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <wx/event.h>
#include <wx/valnum.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class App : public wxApp
{
public:
	virtual bool Init();
};

class Fenetre : public wxFrame
{
public:
	Fenetre();
private:
	void OnExit(wxCommandEvent& event);
};

void Fenetre::OnExit(wxCommandEvent& event)
{
	Close(true);
}