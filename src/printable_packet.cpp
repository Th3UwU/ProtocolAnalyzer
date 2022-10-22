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
	string += fmt::format(fmt::fg(fmt::color::cornflower_blue), "{0:s}\n", IPDst	);
	
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

std::unique_ptr<PrintablePacket> createPpacketFromLayer(pcpp::Layer& layer)
{
	if (layer.getProtocol() == pcpp::Ethernet)
		return std::make_unique<PpacketEthernet>((pcpp::EthLayer&)layer);
	
	if (layer.getProtocol() == pcpp::IPv4)
		return std::make_unique<PpacketIPv4>((pcpp::IPv4Layer&)layer);

	return nullptr;
}