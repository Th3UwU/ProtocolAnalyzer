#include "gui/window_main.hpp"
#include "gui/window_open.hpp"

#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>

#include <iostream>

//
enum
{
	ID_Hello = wxID_HIGHEST,
	ID_Open_File
};

WindowMain::WindowMain() :
wxFrame(nullptr, wxID_ANY, L"Hello World", wxDefaultPosition, wxDefaultSize)
{
	wxMenu* menuFile = new wxMenu();
	menuFile->Append(ID_Open_File, L"&Abrir...\tCtrl-O", L"Abrir un archivo");
	menuFile->Append(ID_Hello, L"&Hello...\tCtrl-H", L"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu* menuHelp = new wxMenu();
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(menuFile, L"&File");
	menuBar->Append(menuHelp, L"&Help");

	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");

	//
	wxBoxSizer* sizerMain = new wxBoxSizer(wxVERTICAL);
	wxPanel* panelMain = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(900, 200));
	panelMain->SetBackgroundColour(wxColour(100, 100, 200));
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* panel = new wxPanel(panelMain, wxID_ANY, wxDefaultPosition, wxSize(900, 200));
	panel->SetBackgroundColour(wxColour(100, 200, 100));
	table = new Table(panelMain, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	table->CreateGrid(3, 3);
	table->SetUseNativeColLabels(true);
	table->EnableEditing(false);
	table->DisableDragRowSize();
	table->DisableDragColSize();
	table->SetRowLabelSize(0);
	table->SetColLabelValue(0, L"ID");
	table->SetColLabelValue(1, L"Tamaño");
	table->SetColLabelValue(2, L"Protocolo");

	sizer->Add(panel, 1, wxEXPAND | wxALL, 32);
	sizer->Add(table, 1, wxEXPAND | wxALL, 32);
	panelMain->SetSizerAndFit(sizer);
	sizerMain->Add(panelMain, 1, wxEXPAND | wxALL, 8);
	this->SetSizerAndFit(sizerMain);

	// Bind
	Bind(wxEVT_MENU, &WindowMain::OnOpenFile, this, ID_Open_File);
	Bind(wxEVT_MENU, &WindowMain::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &WindowMain::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &WindowMain::OnExit, this, wxID_EXIT);
	Bind(wxEVT_SIZE, &WindowMain::OnSize, this);
}

void WindowMain::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void WindowMain::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(L"This is a wxWidgets Hello World example", L"About Hello World", wxOK | wxICON_INFORMATION);
}

void WindowMain::OnOpenFile(wxCommandEvent& event)
{
	/*
	wxFileDialog openFileDialog(this, L"Abrir un archivo", wxEmptyString, wxEmptyString, "All files (*.*)|*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	std::cout << openFileDialog.GetPath();
	*/
	WindowOpen* wo = new WindowOpen(this);
	wo->Show(true);
	Enable(false);
}

void WindowMain::OnHello(wxCommandEvent& event)
{
	wxLogMessage(L"Hello world from wxWidgets!");
}

