#include "gui/window_open.hpp"

#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/button.h>

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
	wxStaticBoxSizer* box = new wxStaticBoxSizer(wxVERTICAL, panelMain, "StaticBox");
	wxButton* buttonBrowseFile = new wxButton(box->GetStaticBox(), wxID_ANY, L"Seleccionar archivo");

	box->Add(buttonBrowseFile, 1, wxEXPAND | wxALL);
	sizer->Add(box, 1, wxEXPAND | wxALL, 4);
	panelMain->SetSizerAndFit(sizer);
	sizerMain->Add(panelMain, 1, wxEXPAND | wxALL, 0);
	this->SetSizerAndFit(sizerMain);

	//new wxStaticText(box, wxID_ANY, "This window is a child of the staticbox");

	

	// Bind
	Bind(wxEVT_MENU, &WindowOpen::OnExit, this, wxID_EXIT);
	Bind(wxEVT_CLOSE_WINDOW, &WindowOpen::OnClose, this);
}

void WindowOpen::OnExit(wxCommandEvent& event) {Close(true);}

void WindowOpen::OnClose(wxCloseEvent& event)
{
	GetParent()->Enable(true);
	Destroy();
}
