#include "gui/table.hpp"
#include <fmt/core.h>

#include "gui/window_main.hpp"

Table::Table(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
: wxGrid(parent, id, pos, size, style, name)
{
	// Column size
	columnSize = {1, 1, 2};

	Bind(wxEVT_SIZE, &Table::OnSize, this);
	Bind(wxEVT_GRID_SELECT_CELL, &Table::OnSelectedRow, this);
}

void Table::OnSize(wxSizeEvent& event)
{
	int tableWidth = GetSize().GetWidth();

	int totalSize = 0;
	for (unsigned int i = 0; i < columnSize.size(); i++)
		totalSize += columnSize[i];

	int proportion = tableWidth / totalSize;

	for (int i = 0; i < GetNumberCols(); i++)
		SetColSize(i, columnSize[i] * proportion);

	event.Skip();
}

void Table::OnSelectedRow(wxGridEvent& event)
{
	fmt::print("SELECTED ROW: {0:d}\n", event.GetRow());

	WindowMain* parent = (WindowMain*)GetParent();

	// Clear widgets
	parent->sizerPanel->Clear(false);
	parent->panel->DestroyChildren();
	
	// Add data
	parent->items[event.GetRow()]->appendInfo(parent);

	/*
	parent->sizerPanel->Add(new wxStaticText(parent->panel, wxID_ANY, L"Hola!!"), 0, wxALIGN_CENTER_HORIZONTAL, 0);
	parent->sizerPanel->Add(new wxStaticText(parent->panel, wxID_ANY, L"Como!!"), 0, wxALIGN_CENTER_HORIZONTAL, 0);
	parent->sizerPanel->Add(new wxStaticText(parent->panel, wxID_ANY, L"estas!!"), 0, wxALIGN_CENTER_HORIZONTAL, 0);
	parent->sizerPanel->Layout();
	*/
}
