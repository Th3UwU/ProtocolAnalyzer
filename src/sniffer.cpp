#include "sniffer.hpp"

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/color.h>
#include <pcpp/PcapFileDevice.h>
#include <pcpp/Packet.h>
#include <pcpp/EthLayer.h>
#include <pcpp/Logger.h>

#ifdef _WIN32
	static void clear(void) {system("cls");}
#endif

#ifdef unix
	static void clear(void) {system("clear");}
#endif

static bool readInt(int& n)
{
	fmt::print(fmt::fg(fmt::color::blue_violet), "--> ");
	std::cin >> n;
	bool fail = std::cin.fail();

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return not fail;
}

static void readString(std::string& string)
{
	fmt::print(fmt::fg(fmt::color::hot_pink), "--> ");
	std::getline(std::cin, string);
}

Sniffer::Sniffer(void)
{
	protocolType = Protocol::Default;
	pcpp::Logger::getInstance().suppressLogs();
}

void Sniffer::init(void)
{
	int opc = -1;

	while (true)
	{
		fmt::print(fmt::fg(fmt::color::aquamarine), "Elija el tipo de protocolo que desea analizar\n");
		fmt::print(fmt::fg(fmt::color::crimson), "1- Ethernet\n");
		fmt::print(fmt::fg(fmt::color::crimson), "0- Salir\n");

		if (not readInt(opc))
			opc = -1;

		clear();
		switch (opc)
		{
			case 0: return;
			case 1: protocolType = (Protocol)opc; protocolMenu(); break;
			default: fmt::print(fmt::fg(fmt::color::red), "Ingrese una opción valida!!\n\n"); break;
		}
			
	}
}

void Sniffer::protocolMenu(void)
{
	std::string protocolStr;

	switch (protocolType)
	{
		case Protocol::Ethernet: protocolStr = "Ethernet"; break;
		case Protocol::Default: protocolStr = "Default"; break;
	}

	//
	int opc = -1;

	while (true)
	{
		fmt::print(fmt::fg(fmt::color::orange), "Protocolo: ");
		fmt::print(fmt::fg(fmt::color::lime), "{0:s}\n", protocolStr);

		fmt::print(fmt::fg(fmt::color::aquamarine), "Elija una opción\n");
		fmt::print(fmt::fg(fmt::color::crimson), "1- Leer un archivo '.pcap'\n");
		fmt::print(fmt::fg(fmt::color::crimson), "2- Capturar en vivo\n");
		fmt::print(fmt::fg(fmt::color::crimson), "0- Volver al menú inicial\n");

		if (not readInt(opc))
			opc = -1;

		clear();
		switch (opc)
		{
			case 0: return;
			case 1: readMenu(); break;
			case 2: break;
			default: fmt::print(fmt::fg(fmt::color::red), "Ingrese una opción valida!!\n\n"); break;
		}
			
	}
}

void Sniffer::readMenu(void)
{
	std::string fileName;
	fmt::print(fmt::fg(fmt::color::olive), "Ingrese el nombre del archivo\n");
	readString(fileName);

	pcpp::IFileReaderDevice* reader = pcpp::IFileReaderDevice::getReader(fileName);

	if (!reader->open())
	{
		fmt::print(fmt::fg(fmt::color::red), "Archivo no encontrado!!\n\n");
		return;
	}

	pcpp::RawPacket rawPacket;

	while (reader->getNextPacket(rawPacket))
	{
		pcpp::Packet parsedPacket(&rawPacket);

		if (parsedPacket.isPacketOfType(pcpp::Ethernet))
		{
			std::string macSrc = parsedPacket.getLayerOfType<pcpp::EthLayer>()->getSourceMac().toString();
			std::string macDst = parsedPacket.getLayerOfType<pcpp::EthLayer>()->getDestMac().toString();

			fmt::print(fmt::fg(fmt::color::cyan), "Dirección MAC Fuente: ");
			fmt::print(fmt::fg(fmt::color::green_yellow), "{0:s}\n", macSrc);

			fmt::print(fmt::fg(fmt::color::cyan), "Dirección MAC Destino: ");
			fmt::print(fmt::fg(fmt::color::green_yellow), "{0:s}\n", macDst);
		}
	}

	reader->close();
}
