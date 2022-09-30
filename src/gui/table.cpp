#include "gui/table.hpp"

Table::Table(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
: wxGrid(parent, id, pos, size, style, name)
{
	// Column size
	columnSize = {1, 1, 2, 4};

	Bind(wxEVT_SIZE, &Table::OnSize, this);
}

void Table::OnSize(wxSizeEvent& event)
{
	unsigned int tableWidth = GetSize().GetWidth() - 1;

	unsigned int totalSize = 0;
	for (unsigned int i = 0; i < 4; i++)
		totalSize += columnSize[i];

	unsigned int proportion = tableWidth / totalSize;

	for (unsigned int i = 0; i < 4; i++)
		SetColSize(i, columnSize[i] * proportion);

	event.Skip();
}
