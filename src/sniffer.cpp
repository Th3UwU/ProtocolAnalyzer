#include "sniffer.hpp"

#include <iostream>
#include <limits>
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/color.h>

Sniffer::Sniffer(void)
{
	std::cout << fmt::format(fmt::fg(fmt::color::aqua), "UWU\n");
}

static bool readInt(int& n)
{
	std::cin >> n;
	bool fail = std::cin.fail();

	if (fail)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return not fail;
}

void Sniffer::init(void)
{
	int opc = -1;

	while (opc != 0)
	{
		std::cout
		<< "Elija el tipo de protocolo que desea analizar\n"
		<< "1- Ethernet\n"
		<< "0- Salir\n";

		if (readInt(opc))
		{
			switch (opc)
			{
				case 1: std::cout << "UWU\n";
				case 0: break;
				default: std::cout << "Ingrese una opción valida\n"; break;
			}
		}
		else
		{
			system("cls");
			std::cout << "Ingrese una opción valida\n";
			opc = -1;
		}
			
	}
}