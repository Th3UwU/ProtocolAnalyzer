#ifndef WINDOW_MAIN_HPP
#define WINDOW_MAIN_HPP

#include "gui/table.hpp"
#include "packet.hpp"

#include <wx/frame.h>
#include <vector>
#include <memory>

class WindowMain : public wxFrame
{
public:
	WindowMain();

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnOpenFile(wxCommandEvent& event);
	void OnHello(wxCommandEvent& event);

	void refreshItems(void);
	void appendItem(const std::shared_ptr<Packet>& packet);

	Table* table;
	std::vector<std::shared_ptr<Packet>> items;
};

#endif
