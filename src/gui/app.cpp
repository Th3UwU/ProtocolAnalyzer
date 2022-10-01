#include "gui/app.hpp"
#include "gui/window_main.hpp"

#include "ethernet.hpp"

#include <iostream>

// Main
wxIMPLEMENT_APP(AnalyserApp);

bool AnalyserApp::OnInit()
{
	WindowMain* frame = new WindowMain();
	frame->Show(true);

	//
	Ethernet et;
	et.randomize(64, 128);
	et.print(true);
	//
	return true;
}

int AnalyserApp::OnExit()
{
	printf("EXIT\n");
	return wxApp::OnExit();
}
