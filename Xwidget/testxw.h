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
	void OnClose(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnHelp(wxCommandEvent& event);
};

class ChoixBanque : public wxDialog {
public:
	ChoixBanque(wxWindow* parent, wxWindowID id, const wxString& title);
	wxString get_agence();
	string get_nom_agence();
	void edit_nom_agence(string nom_agence);
private:
	wxComboBox* edit_agence_;
	string nom_agence;
};

class CreationClient : public wxDialog
{
public:
	CreationClient(wxWindow* parent, wxWindowID id, const wxString& title);

	wxString get_customer_number();
	wxString get_firstname();
	wxString get_name();
	wxString get_adresse();
	string get_agence(ChoixBanque name_of_banque);
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
	wxTextCtrl* edit_customer_password_;
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
	void OnCreateAccount(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnHelp(wxCommandEvent& event);
};

class Transactionwx : public wxDialog {
public:
	Transactionwx(wxWindow* parent, wxWindowID id, const wxString& title);

	wxString get_receveur_number();
	wxString get_somme_transaction();
	wxString get_envoyeur_number();

private:

	void OnOk(wxCommandEvent& event);
	wxTextCtrl* edit_receveur_number_;
	wxTextCtrl* edit_somme_transaction_;
	wxTextCtrl*  edit_envoyeur_number_;
	//wxComboBox* edit_envoyeur_number_;
};

class creation_compte : public wxDialog {
public:
	creation_compte(wxWindow* parent, wxWindowID id, const wxString& title);
	wxString get_type_de_compte();
private:
	void OnOk(wxCommandEvent& event);
	wxComboBox* edit_type_de_compte_;
};