#ifndef TABLE_HPP
#define TABLE_HPP

#include <wx/grid.h>

#include <array>

class Table : public wxGrid
{
public:
	Table(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxWANTS_CHARS, const wxString &name=wxGridNameStr);

	void OnSize(wxSizeEvent& event);

	std::array<unsigned int, 3> columnSize;
};

#endif
