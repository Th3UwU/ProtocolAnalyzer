#include "gui/table.hpp"

#include <wx/menu.h>
#include <fmt/core.h>

#include "gui/window_main.hpp"

enum
{
	ID_Remove_Item = 1
};

Table::Table(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
: wxGrid(parent, id, pos, size, style, name)
{
	// Column size
	columnSize = {1, 1, 2};
	selectedRow = -1;

	Bind(wxEVT_SIZE, &Table::OnSize, this);
	Bind(wxEVT_GRID_SELECT_CELL, &Table::OnSelectedRow, this);
	Bind(wxEVT_GRID_CELL_RIGHT_CLICK, &Table::OnRightClickedRow, this);

	Bind(wxEVT_MENU,
	[&, this](wxCommandEvent& event)
	{
		WindowMain* parent = (WindowMain*)GetParent();
		parent->removeItem(selectedRow);
	},
	ID_Remove_Item);
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
}

void Table::OnRightClickedRow(wxGridEvent& event)
{
	SelectRow(event.GetRow());
	selectedRow = event.GetRow();

	wxMenu* menu = new wxMenu();
	menu->Append(ID_Remove_Item, L"Eliminar");
	PopupMenu(menu);
}
