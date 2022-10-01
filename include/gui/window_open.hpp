#ifndef WINDOW_OPEN_HPP
#define WINDOW_OPEN_HPP

#include <wx/frame.h>

class WindowOpen : public wxFrame
{
public:
	WindowOpen(wxWindow* parent);

	void OnExit(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};

#endif
