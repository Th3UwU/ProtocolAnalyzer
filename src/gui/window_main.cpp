#include "gui/window_main.hpp"
#include "gui/window_open.hpp"

#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/filedlg.h>
#include <fmt/core.h>

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
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	sizerPanel = new wxBoxSizer(wxVERTICAL);
	panel = new wxScrolled<wxPanel>(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	panel->SetBackgroundColour(*wxBLACK);
	panel->ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_DEFAULT);
	panel->EnableScrolling(true, true);
	panel->SetScrollRate(5, 10);
	//panel->SetVirtualSize(wxSize(1000, 2000));
	table = new Table(this, wxID_ANY, wxDefaultPosition, wxSize(300, 200));
	table->CreateGrid(0, 3);
	table->SetUseNativeColLabels(true);
	table->EnableEditing(false);
	table->SetSelectionMode(wxGrid::wxGridSelectRows);
	table->DisableDragRowSize();
	table->DisableDragColSize();
	table->SetRowLabelSize(0);
	table->SetColLabelValue(0, L"ID");
	table->SetColLabelValue(1, L"Tamaño");
	table->SetColLabelValue(2, L"Protocolo");

	panel->SetSizerAndFit(sizerPanel);
	sizer->Add(table, 0, wxEXPAND | wxVERTICAL, 0);
	sizer->Add(panel, 3, wxEXPAND | wxALL, 0);
	this->SetSizerAndFit(sizer);

	// Bind
	Bind(wxEVT_MENU, &WindowMain::OnOpenFile, this, ID_Open_File);
	Bind(wxEVT_MENU, &WindowMain::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &WindowMain::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &WindowMain::OnExit, this, wxID_EXIT);
	Bind(wxEVT_SIZE, &WindowMain::OnSize, this);
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
	refreshItems();
}

void WindowMain::refreshItems(void)
{
	table->ClearGrid();
	int rows = table->GetNumberRows();
	if (rows) table->DeleteRows(0, rows);

	for (auto& packet : items)
		appendItem(packet);
}


void WindowMain::appendItem(const std::shared_ptr<Packet>& packet)
{
	table->AppendRows(1);
	int index = table->GetNumberRows() - 1;

	table->SetCellValue(index, 0, fmt::format("{0:d}", index));
	table->SetCellValue(index, 1, fmt::format("{0:d}", packet->getSize()));
	table->SetCellValue(index, 2, packet->getType());
}

void WindowMain::removeItem(const int row)
{
	items.erase(items.begin() + row);
	table->DeleteRows(row);

	// Clear widgets
	sizerPanel->Clear(false);
	panel->DestroyChildren();

	// Update id's
	for (int i = 0; i < table->GetNumberRows(); i++)
		table->SetCellValue(i, 0, fmt::format("{0:d}", i));

	panel->FitInside();

	//refreshItems();
}
