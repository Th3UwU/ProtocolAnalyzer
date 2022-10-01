#include "gui/window_open.hpp"
#include "gui/window_main.hpp"

#include "ethernet.hpp"

#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/filedlg.h>

enum
{
	ID_BROWSE = 1,
	ID_IMPORT
};

WindowOpen::WindowOpen(wxWindow* parent) :
wxFrame(parent, wxID_ANY, L"Hello World", wxDefaultPosition, wxDefaultSize)
{
	wxMenu* menuFile = new wxMenu();
	menuFile->Append(wxID_EXIT);

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(menuFile, L"&File");

	SetMenuBar(menuBar);
	//
	wxBoxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	wxPanel* panelMain = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 300));
	panelMain->SetBackgroundColour(*wxWHITE);
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	//
	wxStaticBoxSizer* box = new wxStaticBoxSizer(wxVERTICAL, panelMain, L"Importar paquete");

	wxArrayString choices;
	choices.Add(L"Ethernet");
	choices.Add(L"Otro");
	choices.Add(L"Etc");
	selector = new wxChoice(box->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
	selector->SetSelection(0);

	wxBoxSizer* sizerPathWidgets = new wxBoxSizer(wxHORIZONTAL);
	inPath = new wxTextCtrl(box->GetStaticBox(), wxID_ANY);
	wxButton* btnBrowse = new wxButton(box->GetStaticBox(), ID_BROWSE, L"Seleccionar...");
	wxButton* btnOk = new wxButton(box->GetStaticBox(), ID_IMPORT, L"Importar");

	box->Add(selector, 1, wxALIGN_CENTER | wxALL, 6);
	sizerPathWidgets->Add(inPath, 4, wxEXPAND | wxALL, 6);
	sizerPathWidgets->Add(btnBrowse, 1, wxEXPAND | wxALL, 6);
	box->Add(sizerPathWidgets, 1, wxEXPAND | wxALL);
	box->Add(btnOk, 1, wxALIGN_CENTER | wxALL, 6);
	sizer->Add(box, 1, wxEXPAND | wxALL, 4);
	//
	panelMain->SetSizerAndFit(sizer);
	sizerMain->Add(panelMain, 1, wxEXPAND | wxALL, 0);
	this->SetSizerAndFit(sizerMain);	

	// Bind
	Bind(wxEVT_MENU, &WindowOpen::OnExit, this, wxID_EXIT);
	Bind(wxEVT_CLOSE_WINDOW, &WindowOpen::OnClose, this);
	Bind(wxEVT_BUTTON, &WindowOpen::OnBrowse, this, ID_BROWSE);
	Bind(wxEVT_BUTTON, &WindowOpen::OnImport, this, ID_IMPORT);
}

void WindowOpen::OnExit(wxCommandEvent& event) {Close(true);}

void WindowOpen::OnClose(wxCloseEvent& event)
{
	GetParent()->Enable(true);
	Destroy();
}

void WindowOpen::OnBrowse(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, L"Importar un archivo", wxEmptyString, wxEmptyString, "All files (*.*)|*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	inPath->SetValue(openFileDialog.GetPath());
}

void WindowOpen::OnImport(wxCommandEvent& event)
{
	if (selector->GetSelection() == 0)
	{
		printf("ETHERNET\n");
		Ethernet eth;
		eth.loadFromFile(inPath->GetValue());
		eth.print(true);
	}
	else
		printf("NO es ethernet\n");
}
