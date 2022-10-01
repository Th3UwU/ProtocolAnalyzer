#include "gui/window_open.hpp"

#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>

WindowOpen::WindowOpen(wxWindow* parent) :
wxFrame(parent, wxID_ANY, L"Hello World", wxDefaultPosition, wxSize(400, 400))
{
	wxMenu* menuFile = new wxMenu();
	menuFile->Append(wxID_EXIT);

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(menuFile, L"&File");

	SetMenuBar(menuBar);

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
