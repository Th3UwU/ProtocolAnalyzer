#include "sniffer.hpp"

#ifdef _WIN32
	#include <windows.h>
#endif

int main(void)
{
	#ifdef _WIN32
		SetConsoleOutputCP(65001);
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD lpMode = 0;
		GetConsoleMode(out, &lpMode);
		SetConsoleMode(out, lpMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	#endif

	Sniffer sniffer = Sniffer();
	sniffer.init();
	return 0;
}