#include "sniffer.hpp"

#include <windows.h>

int main(void)
{
	SetConsoleOutputCP(65001);
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD lpMode = 0;
	GetConsoleMode(out, &lpMode);
	SetConsoleMode(out, lpMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	Sniffer sniffer = Sniffer();
	sniffer.init();
	return 0;
}