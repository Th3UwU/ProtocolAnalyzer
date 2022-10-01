#include "gui/table.hpp"

Table::Table(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
: wxGrid(parent, id, pos, size, style, name)
{
	// Column size
	columnSize = {1, 1, 2};

	Bind(wxEVT_SIZE, &Table::OnSize, this);
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
