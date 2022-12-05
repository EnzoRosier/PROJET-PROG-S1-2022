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
	virtual bool OnInit();
};

class Fenetre : public wxFrame
{
public:
	Fenetre();
	void OnAbout(wxCommandEvent& event);
private:
	void OnLogin(wxCommandEvent& event);
	void OnRegister(wxCommandEvent& event);
	void OnAddAccount(wxCommandEvent& event);
	void OnDelAccount(wxCommandEvent& event);
	void OnAccount(wxCommandEvent& event);
	void OnReturn(wxCommandEvent& event);
	void OnHome(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnHelp(wxCommandEvent& event);
};


class CreationClient : public wxDialog
{
public:
	CreationClient(wxWindow* parent, wxWindowID id, const wxString& title);

	wxString get_customer_number();
	wxString get_name();
	wxString get_account_numbers();

private:

	void OnOk(wxCommandEvent& event);
	wxTextCtrl* edit_firstname_;
	wxTextCtrl* edit_name_;
	wxTextCtrl* edit_account_numbers_;
};