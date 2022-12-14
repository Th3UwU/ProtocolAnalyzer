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
#include <pcpp/PcapLiveDevice.h>
#include <pcpp/PcapLiveDeviceList.h>

Sniffer::Sniffer(void)
{
	protocolType = pcpp::UnknownProtocol;
	pcpp::Logger::getInstance().suppressLogs();
	all = false;
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
		fmt::print(fmt::fg(fmt::color::crimson), "5- IPv6\n");
		fmt::print(fmt::fg(fmt::color::crimson), "6- TCP\n");
		fmt::print(fmt::fg(fmt::color::crimson), "7- UDP\n");
		fmt::print(fmt::fg(fmt::color::crimson), "8- DNS\n");
		fmt::print(fmt::fg(fmt::color::crimson), "9- DHCP\n");
		fmt::print(fmt::fg(fmt::color::crimson), "10- Todos\n");
		fmt::print(fmt::fg(fmt::color::crimson), "0- Salir\n");

		if (not readInt(opc))
			opc = -1;

		clear();
		all = false;
		switch (opc)
		{
			case 0: return;
			case 1: protocolType = pcpp::Ethernet; protocolMenu(); break;
			case 2: protocolType = pcpp::IPv4; protocolMenu(); break;
			case 3: protocolType = pcpp::ARP; protocolMenu(); break;
			case 4: protocolType = pcpp::ICMP; protocolMenu(); break;
			case 5: protocolType = pcpp::IPv6; protocolMenu(); break;
			case 6: protocolType = pcpp::TCP; protocolMenu(); break;
			case 7: protocolType = pcpp::UDP; protocolMenu(); break;
			case 8: protocolType = pcpp::DNS; protocolMenu(); break;
			case 9: protocolType = pcpp::DHCP; protocolMenu(); break;
			case 10: all = true; protocolMenu(); break;
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

		if (all)
			fmt::print(fmt::fg(fmt::color::lime), "Todos\n");
		else
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
			case 1: (all ? readAllMenu() : readMenu()); break;
			case 2: captureMenu(); break;
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
			//fmt::print("Type: {:d}", layer->getProtocol());
			if (layer->getProtocol() == protocolType)
			{
				std::unique_ptr<PrintablePacket> pPacket = createPpacketFromLayer(*layer);
				fmt::print(pPacket->toString());
				for (int i = 0; i < 64; i++) fmt::print(fmt::fg(fmt::color::crimson), "-");
				fmt::print("\n");
				break;
			}
			// Caso especial: es ICMPv6
			else if ((layer->getProtocol() == pcpp::GenericPayload) and (protocolType == pcpp::ICMP))
			{
				std::unique_ptr<PrintablePacket> pPacket = std::make_unique<PpacketICMP>((pcpp::IcmpLayer&)(*layer));
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

void Sniffer::readAllMenu(void)
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
				std::unique_ptr<PrintablePacket> pPacket = createPpacketFromLayer(*layer);

				if (pPacket)
				{
					fmt::print("-- Protocolo: {:s}\n", pPacket->protocolToString());
					fmt::print(pPacket->toString());
					for (int i = 0; i < 64; i++) fmt::print(fmt::fg(fmt::color::crimson), "-");
					fmt::print("\n");
				}

				layer = layer->getNextLayer();
		}
		fmt::print("\n");
		for (int i = 0; i < 32; i++) fmt::print(fmt::fg(fmt::color::cyan), "*");
		fmt::print("\n\n");
	}

	reader->close();
}

void Sniffer::captureMenu(void)
{
	std::vector<pcpp::PcapLiveDevice*> devices = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();
	uint8_t size = (uint8_t)devices.size();

	if (size == 0)
		return;

	for (uint8_t i = 0; i < size; i++)
	{
		fmt::print(fmt::fg(fmt::color::crimson), "{:d}: ", i);
		fmt::print(fmt::fg(fmt::color::lime), "{:s}\n", devices[i]->getDesc());
	}

	int deviceIndex = -1;
	while (deviceIndex < 0 || deviceIndex >= size)
	{
		fmt::print(fmt::fg(fmt::color::aquamarine), "Seleccione un dispositivo\n");
		if (!readInt(deviceIndex))
			deviceIndex = -1;
	}
	pcpp::PcapLiveDevice* dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(devices[deviceIndex]->getIPv4Address());

	int captureTime = 0;
	while (captureTime <= 0 || captureTime > 20)
	{
		fmt::print(fmt::fg(fmt::color::aquamarine), "Tiempo de captura (Segundos)\n");
		if (!readInt(captureTime))
			captureTime = 0;
	}

	if (!dev->open())
		return;

	////////
	pcpp::RawPacketVector packetVec;
	dev->startCapture(packetVec);
	Sleep(captureTime * 1000);
	dev->stopCapture();

	for (pcpp::RawPacketVector::VectorIterator iter = packetVec.begin(); iter != packetVec.end(); iter++)
	{
		pcpp::Packet parsedPacket(*iter);
		pcpp::Layer* layer = parsedPacket.getFirstLayer();

		while (layer)
		{
				std::unique_ptr<PrintablePacket> pPacket = createPpacketFromLayer(*layer);

				if (pPacket)
				{
					if ((all) or (layer->getProtocol() == protocolType))
					{
						if (all)
							fmt::print("-- Protocolo: {:s}\n", pPacket->protocolToString());
							
						fmt::print(pPacket->toString());
						for (int i = 0; i < 64; i++) fmt::print(fmt::fg(fmt::color::crimson), "-");
						fmt::print("\n");
					}
				}

				layer = layer->getNextLayer();
		}

		if (all)
		{
			fmt::print("\n");
			for (int i = 0; i < 32; i++) fmt::print(fmt::fg(fmt::color::cyan), "*");
			fmt::print("\n\n");
		}
	}


}