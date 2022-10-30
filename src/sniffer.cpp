#include "sniffer.hpp"

#include "utils.hpp"
#include "printable_packet.hpp"

#include <string>
#include <limits>
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/color.h>
#include <pcpp/PcapFileDevice.h>
#include <pcpp/Packet.h>
#include <pcpp/Logger.h>

Sniffer::Sniffer(void)
{
	protocolType = pcpp::UnknownProtocol;
	pcpp::Logger::getInstance().suppressLogs();
}

void Sniffer::init(void)
{
	int opc = -1;

	while (true)
	{
		fmt::print(fmt::fg(fmt::color::aquamarine), "Elija el tipo de protocolo que desea analizar\n");
		fmt::print(fmt::fg(fmt::color::crimson), "1- Ethernet\n");
		fmt::print(fmt::fg(fmt::color::crimson), "2- IPv4\n");
		fmt::print(fmt::fg(fmt::color::crimson), "3- ARP\n");
		fmt::print(fmt::fg(fmt::color::crimson), "4- ICMP\n");
		fmt::print(fmt::fg(fmt::color::crimson), "0- Salir\n");

		if (not readInt(opc))
			opc = -1;

		clear();
		switch (opc)
		{
			case 0: return;
			case 1: protocolType = pcpp::Ethernet; protocolMenu(); break;
			case 2: protocolType = pcpp::IPv4; protocolMenu(); break;
			case 3: protocolType = pcpp::ARP; protocolMenu(); break;
			case 4: protocolType = pcpp::ICMP; protocolMenu(); break;
			default: fmt::print(fmt::fg(fmt::color::red), "Ingrese una opción valida!!\n\n"); break;
		}
			
	}
}

void Sniffer::protocolMenu(void)
{
	std::string protocolStr = getProtocolString(protocolType);

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
		fmt::print(fmt::fg(fmt::color::red), "Error al leer el archivo!!\n\n");
		return;
	}

	pcpp::RawPacket rawPacket;

	while (reader->getNextPacket(rawPacket))
	{
		pcpp::Packet parsedPacket(&rawPacket);
		pcpp::Layer* layer = parsedPacket.getFirstLayer();

		while (layer)
		{
			if (layer->getProtocol() == protocolType)
			{
				std::unique_ptr<PrintablePacket> pPacket = createPpacketFromLayer(*layer);
				fmt::print(pPacket->toString());
				for (int i = 0; i < 64; i++) fmt::print(fmt::fg(fmt::color::crimson), "-");
				fmt::print("\n");
				break;
			}
			else
				layer = layer->getNextLayer();
		}

	}

	reader->close();
}
