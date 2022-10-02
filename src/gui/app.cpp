#include "gui/app.hpp"
#include "gui/window_main.hpp"

#include <iostream>
#include <windows.h>

// Main
wxIMPLEMENT_APP(AnalyserApp);

bool AnalyserApp::OnInit()
{
	// Enable ANSI color escape codes
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	// Create main window
	WindowMain* frame = new WindowMain();
	frame->Show(true);

	return true;
}

int AnalyserApp::OnExit()
{
	return wxApp::OnExit();
}
