#ifndef WINDOW_MAIN_HPP
#define WINDOW_MAIN_HPP

#include "gui/table.hpp"

#include <wx/frame.h>

class MainFrame : public wxFrame
{
public:
	MainFrame();

	void OnOpenFile(wxCommandEvent& event);
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	Table* table;
};

#endif
