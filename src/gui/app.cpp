#include "gui/app.hpp"
#include "gui/window_main.hpp"

// Main
wxIMPLEMENT_APP(AnalyserApp);

bool AnalyserApp::OnInit()
{
	MainFrame* frame = new MainFrame();
	frame->Show(true);
	return true;
}

int AnalyserApp::OnExit()
{
	printf("EXIT\n");
	return wxApp::OnExit();
}
