#ifndef WINDOW_OPEN_HPP
#define WINDOW_OPEN_HPP

#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/choice.h>

class WindowOpen : public wxFrame
{
public:
	WindowOpen(wxWindow* parent);

	void OnExit(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
	void OnBrowse(wxCommandEvent& event);
	void OnImport(wxCommandEvent& event);

	wxChoice* selector;
	wxTextCtrl* inPath;
};

#endif
