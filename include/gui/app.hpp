#ifndef APP_HPP
#define APP_HPP

#include <wx/app.h>

class AnalyserApp : public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit();
};

#endif
