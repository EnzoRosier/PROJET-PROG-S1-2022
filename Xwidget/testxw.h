#pragma once
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <wx/event.h>
#include <wx/valnum.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "../Client/Client.h"

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
	wxString get_firstname();
	wxString get_name();
	wxString get_adresse();
	wxString get_agence();
	wxString get_account_numbers();
	wxString get_taille();

private:

	void OnOk(wxCommandEvent& event);
	wxTextCtrl* edit_firstname_;
	wxTextCtrl* edit_name_;
	wxTextCtrl* edit_adresse_;
	wxComboBox* edit_agence_;
	wxTextCtrl* edit_account_numbers_;
	wxTextCtrl* edit_customer_number_;
	wxTextCtrl* edit_taille_;
};


class LoginClient : public wxDialog
{
public:
	LoginClient(wxWindow* parent, wxWindowID id, const wxString& title);

	wxString get_customer_number();
	wxString get_customer_password();

private:

	void OnOk(wxCommandEvent& event);
	wxTextCtrl* edit_customer_number_;
	wxTextCtrl* edit_customer_password_;
};

class FenetreEspacePerso : public wxFrame
{
public:
	FenetreEspacePerso(wxWindow* parent, wxWindowID id);
	void OnAbout(wxCommandEvent& event);
private:
	void OnConsulterCourant(wxCommandEvent& event);
	void OnConsulterEpargne(wxCommandEvent& event);
	void OnTransaction(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnHelp(wxCommandEvent& event);
};

class Transactionwx : public wxDialog {
public:
	Transactionwx(wxWindow* parent, wxWindowID id, const wxString& title);

	wxString get_receveur_number();
	wxString get_somme_transaction();

private:

	void OnOk(wxCommandEvent& event);
	wxTextCtrl* edit_receveur_number_;
	wxTextCtrl* edit_somme_transaction_;
};