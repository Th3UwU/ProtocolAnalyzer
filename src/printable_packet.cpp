#include "printable_packet.hpp"

#include "utils.hpp"

#include <fmt/core.h>
#include <fmt/color.h>
#include <pcpp/Packet.h>

PpacketEthernet::PpacketEthernet(pcpp::EthLayer& layer)
: layer(layer)
{}

std::string PpacketEthernet::toString(void)
{
	std::string string;

	// Source MAC address
	std::string macSrc = layer.getSourceMac().toString();
	string += fmt::format(fmt::fg(fmt::color::cyan), "Dirección MAC Fuente: ");
	string += fmt::format(fmt::fg(fmt::color::green_yellow), "{0:s}\n", macSrc);

	// Destination MAC address
	std::string macDst = layer.getDestMac().toString();
	string += fmt::format(fmt::fg(fmt::color::cyan), "Dirección MAC Destino: ");
	string += fmt::format(fmt::fg(fmt::color::green_yellow), "{0:s}\n", macDst);
	
	// Type
	fmt::color color = fmt::color::green_yellow;
	std::string type = getProtocolString(layer.getNextLayer()->getProtocol());
	if (type == "Desconocido")
		color = fmt::color::red;

	string += fmt::format(fmt::fg(fmt::color::cyan), "Tipo: ");
	string += fmt::format(fmt::fg(color), "{0:s}\n", type);

	// Length
	size_t length = layer.getDataLen();
	string += fmt::format(fmt::fg(fmt::color::cyan), "Tamaño total: ");
	string += fmt::format(fmt::fg(fmt::color::green_yellow), "{0:d}\n", length);

	return string;
}

std::unique_ptr<PrintablePacket> PpacketEthernet::getNextLayer(void)
{
	return (createPpacketFromLayer(*layer.getNextLayer()));
}

PpacketIPv4::PpacketIPv4(pcpp::IPv4Layer& layer)
: layer(layer)
{}

std::string PpacketIPv4::toString(void)
{
	std::string string;

	// IHL
	uint8_t ihl = layer.getIPv4Header()->internetHeaderLength;
	string += fmt::format(fmt::fg(fmt::color::light_pink), "IHL: ");
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:d}\n", ihl);

	// TOS
	uint8_t tos = layer.getIPv4Header()->typeOfService;
	string += fmt::format(fmt::fg(fmt::color::light_pink), "TOS: ");
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:d}\n", tos);

	// LEN
	uint16_t totalLength = ntohs(layer.getIPv4Header()->totalLength);
	string += fmt::format(fmt::fg(fmt::color::light_pink), "Tamaño total: ");
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:d}\n", totalLength);

	// ID
	uint16_t id = ntohs(layer.getIPv4Header()->ipId);
	string += fmt::format(fmt::fg(fmt::color::light_pink), "Identificación: ");
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:d}\n", id);

	// Flags
	uint8_t flags = layer.getFragmentFlags();
	string += fmt::format(fmt::fg(fmt::color::light_pink), "Flags: ");

	/* [1][2][3][ ][ ][ ][ ][ ] -> [ ][ ][ ][ ][ ][1][2][3] */  
	/* Extraer los primeros 3 bits del byte */
	flags >>= 5;
	
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{:c}{:c}{:c}",
	flags & 0x04 ? '1':'0',
	flags & 0x02 ? '1':'0',
	flags & 0x01 ? '1':'0');
	
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), " ({0:#x})\n", flags);

	// Fragment offset
	uint16_t fragmentOffset = layer.getFragmentOffset();
	string += fmt::format(fmt::fg(fmt::color::light_pink), "Fragment offset: ");
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:d}\n", fragmentOffset);

	// TTL
	uint8_t ttl = layer.getIPv4Header()->timeToLive;
	string += fmt::format(fmt::fg(fmt::color::light_pink), "Tiempo de vida: ");
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:d}\n", ttl);

	// Protocol
	uint8_t protocol = layer.getIPv4Header()->protocol;
	std::string protocolString = getProtocolString(layer.getNextLayer()->getProtocol());
	string += fmt::format(fmt::fg(fmt::color::light_pink), "Protocolo: ");
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:s} ({1:d})\n", protocolString, protocol);

	// Checksum
	uint16_t checksum = ntohs(layer.getIPv4Header()->headerChecksum);
	string += fmt::format(fmt::fg(fmt::color::light_pink), "Checksum: ");
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:d}\n", checksum);

	// Source IP address
	std::string IPSrc = layer.getSrcIPv4Address().toString();
	string += fmt::format(fmt::fg(fmt::color::light_pink), "Dirección IP Fuente: ");
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:s}\n", IPSrc);

	// Destination IP address
	std::string IPDst = layer.getDstIPv4Address().toString();
	string += fmt::format(fmt::fg(fmt::color::light_pink), "Dirección IP Destino: ");
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:s}\n", IPDst);
	
	// Options
	bool even = false;

	string += fmt::format(fmt::fg(fmt::color::light_pink), "Opciones:\n");
	for (pcpp::IPv4Option option = layer.getFirstOption();
	(option.getIPv4OptionType() != pcpp::IPV4OPT_EndOfOptionsList) and (option.getIPv4OptionType() != pcpp::IPV4OPT_Unknown);
	option = layer.getNextOption(option))
	{
		even = true;
		std::string optionString = getIPv4OptionName(option.getIPv4OptionType());
		string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:s}\n", optionString);
	}

	if (!even)
		string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "Ninguna\n");

	return string;
}

std::unique_ptr<PrintablePacket> PpacketIPv4::getNextLayer(void)
{
	return nullptr;
}

PpacketARP::PpacketARP(pcpp::ArpLayer& layer)
: layer(layer)
{}

std::string PpacketARP::toString(void)
{
	std::string string;

	// Tamaño de los datos
	string += fmt::format(fmt::fg(fmt::color::orange), "Tamaño total: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getDataLen());

	// Hardware type
	string += fmt::format(fmt::fg(fmt::color::orange), "Hardware type: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", ntohs(layer.getArpHeader()->hardwareType));

	// Protocol type
	string += fmt::format(fmt::fg(fmt::color::orange), "Protocol type: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getArpHeader()->protocolType);

	// Hardware size
	string += fmt::format(fmt::fg(fmt::color::orange), "Hardware size: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getArpHeader()->hardwareSize);

	// Protocol size
	string += fmt::format(fmt::fg(fmt::color::orange), "Protocol size: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getArpHeader()->protocolSize);

	// Operation code
	string += fmt::format(fmt::fg(fmt::color::orange), "Operation code: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", ntohs(layer.getArpHeader()->opcode));

	// Source MAC
	string += fmt::format(fmt::fg(fmt::color::orange), "Source MAC: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:s}\n", layer.getSenderMacAddress().toString());

	// Source protocol address
	string += fmt::format(fmt::fg(fmt::color::orange), "Source protocol address: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:s}\n", layer.getSenderIpAddr().toString());

	// Target MAC
	string += fmt::format(fmt::fg(fmt::color::orange), "Target MAC: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:s}\n", layer.getTargetMacAddress().toString());

	// Target protocol address
	string += fmt::format(fmt::fg(fmt::color::orange), "Target protocol address: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:s}\n", layer.getTargetIpAddr().toString());

	return string;
}

std::unique_ptr<PrintablePacket> PpacketARP::getNextLayer(void)
{
	return nullptr;
}

PpacketICMP::PpacketICMP(pcpp::IcmpLayer& layer)
: layer(layer)
{}

std::string PpacketICMP::toString(void)
{
	std::string string;

	// Tipo
	string += fmt::format(fmt::fg(fmt::color::orange), "Type: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getIcmpHeader()->type);

	// Code
	string += fmt::format(fmt::fg(fmt::color::orange), "Code: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getIcmpHeader()->code);
	
	// Checksum
	string += fmt::format(fmt::fg(fmt::color::orange), "Checksum: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:#x}\n", htons(layer.getIcmpHeader()->checksum));

	// Identifier
	string += fmt::format(fmt::fg(fmt::color::orange), "Identifier (BE): ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} ({0:#06x})\n", htons(*(uint16_t*)(layer.getDataPtr() + 4)));
	string += fmt::format(fmt::fg(fmt::color::orange), "Identifier (LE): ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} ({0:#06x})\n", *(uint16_t*)(layer.getDataPtr() + 4));

	// Sequence Number
	string += fmt::format(fmt::fg(fmt::color::orange), "Sequence Number (BE): ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} ({0:#06x})\n", htons(*(uint16_t*)(layer.getDataPtr() + 6)));
	string += fmt::format(fmt::fg(fmt::color::orange), "Sequence Number (LE): ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} ({0:#06x})\n", *(uint16_t*)(layer.getDataPtr() + 6));

	return string;
}

std::unique_ptr<PrintablePacket> PpacketICMP::getNextLayer(void)
{
	return nullptr;
}

PpacketIPv6::PpacketIPv6(pcpp::IPv6Layer& layer)
: layer(layer)
{}

std::string PpacketIPv6::toString(void)
{
	std::string string;

	// Version
	string += fmt::format(fmt::fg(fmt::color::orange), "Versión: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getIPv6Header()->ipVersion);

	// Traffic class
	string += fmt::format(fmt::fg(fmt::color::orange), "Traffic class: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getIPv6Header()->trafficClass);

	// Flow label
	string += fmt::format(fmt::fg(fmt::color::orange), "Flow label: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:08b} {1:08b} {2:08b} ({0:#04x}{1:02x}{2:02x})\n",
	layer.getIPv6Header()->flowLabel[0], layer.getIPv6Header()->flowLabel[1], layer.getIPv6Header()->flowLabel[2]);

	// Payload length
	string += fmt::format(fmt::fg(fmt::color::orange), "Payload length: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getLayerPayloadSize());

	// Next header
	string += fmt::format(fmt::fg(fmt::color::orange), "Next header: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getIPv6Header()->nextHeader);

	// Hop limit
	string += fmt::format(fmt::fg(fmt::color::orange), "Hop limit: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getIPv6Header()->hopLimit);

	// Source address
	string += fmt::format(fmt::fg(fmt::color::orange), "Source address: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:s}\n", layer.getSrcIPv6Address().toString());

	// Destination address
	string += fmt::format(fmt::fg(fmt::color::orange), "Destination address: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:s}\n", layer.getDstIPv6Address().toString());

	return string;
}

std::unique_ptr<PrintablePacket> PpacketIPv6::getNextLayer(void)
{
	return nullptr;
}

PpacketTCP::PpacketTCP(pcpp::TcpLayer& layer)
: layer(layer)
{}

std::string PpacketTCP::toString(void)
{
	std::string string;

	// Source port
	string += fmt::format(fmt::fg(fmt::color::orange), "Source port: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getSrcPort());

	// Destination port
	string += fmt::format(fmt::fg(fmt::color::orange), "Destination port: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getDstPort());

	// Sequence number
	string += fmt::format(fmt::fg(fmt::color::orange), "Sequence number: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", htonl(layer.getTcpHeader()->sequenceNumber));

	// Acknowledgement number
	string += fmt::format(fmt::fg(fmt::color::orange), "Acknowledgement number: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", htonl(layer.getTcpHeader()->ackNumber));

	// Data offset
	string += fmt::format(fmt::fg(fmt::color::orange), "Data offset: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", layer.getTcpHeader()->dataOffset);

	// Flags
	string += fmt::format(fmt::fg(fmt::color::orange), "Flags:\n");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} (Congestion window reduced)\n", layer.getTcpHeader()->cwrFlag);
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} (ECN-Echo)\n", layer.getTcpHeader()->eceFlag);
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} (Urgent)\n", layer.getTcpHeader()->urgFlag);
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} (Acknowledgment)\n", layer.getTcpHeader()->ackFlag);
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} (Push)\n", layer.getTcpHeader()->pshFlag);
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} (Reset)\n", layer.getTcpHeader()->rstFlag);
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} (Syn)\n", layer.getTcpHeader()->synFlag);
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} (Fin)\n", layer.getTcpHeader()->finFlag);

	// Window
	string += fmt::format(fmt::fg(fmt::color::orange), "Window: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", htons(layer.getTcpHeader()->windowSize));

	// Checksum
	string += fmt::format(fmt::fg(fmt::color::orange), "Checksum: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", htons(layer.getTcpHeader()->headerChecksum));

	// Urgent pointer
	string += fmt::format(fmt::fg(fmt::color::orange), "Urgent pointer: ");
	string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d}\n", htons(layer.getTcpHeader()->urgentPointer));

	// Options
	bool space = false;
	string += fmt::format(fmt::fg(fmt::color::orange), "Options:\n");

	pcpp::TcpOption option = layer.getFirstTcpOption();
	while (option.getTcpOptionType() != pcpp::TCPOPT_Unknown)
	{
		space = true;
		string += fmt::format(fmt::fg(fmt::color::medium_purple), "{0:d} ", (unsigned char)option.getTcpOptionType());
		option = layer.getNextTcpOption(option);
	}
	if (space)
		string += '\n';

	return string;
}

std::unique_ptr<PrintablePacket> PpacketTCP::getNextLayer(void)
{
	return nullptr;
}

std::unique_ptr<PrintablePacket> createPpacketFromLayer(pcpp::Layer& layer)
{
	if (layer.getProtocol() == pcpp::Ethernet)
		return std::make_unique<PpacketEthernet>((pcpp::EthLayer&)layer);
	
	if (layer.getProtocol() == pcpp::IPv4)
		return std::make_unique<PpacketIPv4>((pcpp::IPv4Layer&)layer);

	if (layer.getProtocol() == pcpp::ARP)
		return std::make_unique<PpacketARP>((pcpp::ArpLayer&)layer);

	if (layer.getProtocol() == pcpp::ICMP)
		return std::make_unique<PpacketICMP>((pcpp::IcmpLayer&)layer);

	if (layer.getProtocol() == pcpp::IPv6)
		return std::make_unique<PpacketIPv6>((pcpp::IPv6Layer&)layer);

	if (layer.getProtocol() == pcpp::TCP)
		return std::make_unique<PpacketTCP>((pcpp::TcpLayer&)layer);

	return nullptr;
}