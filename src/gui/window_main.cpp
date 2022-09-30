#include "gui/window_main.hpp"

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

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, L"Hello World", wxDefaultPosition, wxDefaultSize)
{
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_Open_File, L"&Abrir...\tCtrl-O", L"Abrir un archivo");
	menuFile->Append(ID_Hello, L"&Hello...\tCtrl-H", L"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar *menuBar = new wxMenuBar;
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
	table->CreateGrid(12, 4);
	table->SetUseNativeColLabels(true);
	table->EnableEditing(false);
	table->SetRowLabelSize(1);
	//table->SetDefaultCellFitMode(wxGridFitMode::Overflow());

	sizer->Add(panel, 1, wxEXPAND | wxALL, 32);
	sizer->Add(table, 1, wxEXPAND | wxALL, 32);
	panelMain->SetSizerAndFit(sizer);
	sizerMain->Add(panelMain, 1, wxEXPAND | wxALL, 8);
	this->SetSizerAndFit(sizerMain);

	// Bind
	Bind(wxEVT_MENU, &MainFrame::OnOpenFile, this, ID_Open_File);
	Bind(wxEVT_MENU, &MainFrame::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_SIZE, &MainFrame::OnSize, this);
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(L"This is a wxWidgets Hello World example", L"About Hello World", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnOpenFile(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, L"Abrir un archivo", wxEmptyString, wxEmptyString, "All files (*.*)|*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	std::cout << openFileDialog.GetPath();
}

void MainFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage(L"Hello world from wxWidgets!");
}

