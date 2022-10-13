#include "sniffer.hpp"

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/color.h>
#include <pcpp/PcapFileDevice.h>
#include <pcpp/Packet.h>
#include <pcpp/Logger.h>

#ifdef _WIN32
	#include <winsock.h>
	static void clear(void) {system("cls");}
#endif

#ifdef unix
	#include <netinet/in.h>
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

	fmt::print("\x1b[38;2;250;128;114m");
	std::getline(std::cin, string);
	fmt::print("\x1b[0m\n");
}

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
		fmt::print(fmt::fg(fmt::color::crimson), "0- Salir\n");

		if (not readInt(opc))
			opc = -1;

		clear();
		switch (opc)
		{
			case 0: return;
			case 1: protocolType = pcpp::Ethernet; protocolMenu(); break;
			default: fmt::print(fmt::fg(fmt::color::red), "Ingrese una opción valida!!\n\n"); break;
		}
			
	}
}

void Sniffer::protocolMenu(void)
{
	std::string protocolStr;

	switch (protocolType)
	{
		case pcpp::Ethernet: protocolStr = "Ethernet"; break;
		case pcpp::UnknownProtocol: protocolStr = "Default"; break;
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
			printPacketEth(parsedPacket.getLayerOfType<pcpp::EthLayer>());

			if (parsedPacket.isPacketOfType(pcpp::IPv4))
				printPacketIpv4(parsedPacket.getLayerOfType<pcpp::IPv4Layer>());


			//
			for (int i = 0; i < 64; i++) fmt::print(fmt::fg(fmt::color::crimson), "-");
			fmt::print("\n");
		}
	}

	reader->close();
}

void Sniffer::printPacketEth(pcpp::EthLayer* layer)
{
	// Source MAC address
	std::string macSrc = layer->getSourceMac().toString();
	fmt::print(fmt::fg(fmt::color::cyan), "Dirección MAC Fuente: ");
	fmt::print(fmt::fg(fmt::color::green_yellow), "{0:s}\n", macSrc);

	// Destination MAC address
	std::string macDst = layer->getDestMac().toString();
	fmt::print(fmt::fg(fmt::color::cyan), "Dirección MAC Destino: ");
	fmt::print(fmt::fg(fmt::color::green_yellow), "{0:s}\n", macDst);
	
	// Type
	fmt::color color = fmt::color::green_yellow;
	std::string type;

	switch (layer->getEthHeader()->etherType)
	{
		case 8: type = "IPv4"; break;
		default: type = "Desconocido"; color = fmt::color::red; break;
	}
	fmt::print(fmt::fg(fmt::color::cyan), "Tipo: ");
	fmt::print(fmt::fg(color), "{0:s}\n", type);

	// Length
	size_t length = layer->getDataLen();
	fmt::print(fmt::fg(fmt::color::cyan), "Tamaño total: ");
	fmt::print(fmt::fg(fmt::color::green_yellow), "{0:d}\n", length);
}

void Sniffer::printPacketIpv4(pcpp::IPv4Layer* layer)
{
	// IHL
	uint8_t ihl = layer->getIPv4Header()->internetHeaderLength;
	fmt::print("IHL: ");
	fmt::print("{0:d}\n", ihl);

	// TOS
	uint8_t tos = layer->getIPv4Header()->typeOfService;
	fmt::print("TOS: ");
	fmt::print("{0:d}\n", tos);

	// LEN
	uint16_t totalLength = ntohs(layer->getIPv4Header()->totalLength);
	fmt::print("Tamaño total: ");
	fmt::print("{0:d}\n", totalLength);

	// ID
	uint16_t id = ntohs(layer->getIPv4Header()->ipId);
	fmt::print("Identificación: ");
	fmt::print("{0:d}\n", id);

	// Flags
	uint8_t flags = layer->getFragmentFlags();
	fmt::print("Flags: ");

	/* [1][2][3][ ][ ][ ][ ][ ] -> [ ][ ][ ][ ][ ][1][2][3] */  
	/* Extraer los primeros 3 bits del byte */
	flags >>= 5;
	
	fmt::print("{:c}{:c}{:c}",
	flags & 0x04 ? '1':'0',
	flags & 0x02 ? '1':'0',
	flags & 0x01 ? '1':'0');
	
	fmt::print(" ({0:#x})\n", flags);

	// Fragment offset
	uint16_t fragmentOffset = layer->getFragmentOffset();
	fmt::print("Fragment offset: ");
	fmt::print("{0:d}\n", fragmentOffset);

	// TTL
	uint8_t ttl = layer->getIPv4Header()->timeToLive;
	fmt::print("Tiempo de vida: ");
	fmt::print("{0:d}\n", ttl);

	// Protocol
	uint8_t protocol = layer->getIPv4Header()->protocol;
	fmt::print("Protocolo: ");
	fmt::print("{0:d}\n", protocol);

	// Checksum
	uint16_t checksum = ntohs(layer->getIPv4Header()->headerChecksum);
	fmt::print("Checksum: ");
	fmt::print("{0:d}\n", checksum);

	// Source IP address
	std::string IPSrc = layer->getSrcIPv4Address().toString();
	fmt::print("Dirección IP Fuente: ");
	fmt::print("{0:s}\n", IPSrc);

	// Destination IP address
	std::string IPDst = layer->getDstIPv4Address().toString();
	fmt::print("Dirección IP Destino: ");
	fmt::print("{0:s}\n", IPDst	);

	// Options
}
