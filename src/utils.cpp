#include "utils.hpp"

#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>

#ifdef _WIN32
	void clear(void) {system("cls");}
#endif

#ifdef unix
	void clear(void) {system("clear");}
#endif

bool readInt(int& n)
{
	fmt::print(fmt::fg(fmt::color::blue_violet), "--> ");
	std::cin >> n;
	bool fail = std::cin.fail();

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return not fail;
}

void readString(std::string& string)
{
	fmt::print(fmt::fg(fmt::color::hot_pink), "--> ");

	fmt::print("\x1b[38;2;250;128;114m");
	std::getline(std::cin, string);
	fmt::print("\x1b[0m\n");
}

std::string getIPv4OptionName(pcpp::IPv4OptionTypes optionType)
{
	std::string optionName;

	switch (optionType)
	{
		case pcpp::IPv4OptionTypes::IPV4OPT_EndOfOptionsList: optionName = "End of Option List"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_NOP: optionName = "No Operation"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_RecordRoute: optionName = "Record Route"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_MTUProbe: optionName = "MTU Probe"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_MTUReply: optionName = "MTU Reply"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_QuickStart: optionName = "Quick-Start"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_Timestamp: optionName = "Time Stamp"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_Traceroute: optionName = "Traceroute"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_Security: optionName = "Security (RIPSO)"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_LooseSourceRoute: optionName = "Loose Source Route"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_ExtendedSecurity: optionName = "E-Extended Security (RIPSO)"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_CommercialSecurity: optionName = "Commercial IP Security Option"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_StreamID: optionName = "Stream ID"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_StrictSourceRoute: optionName = "Strict Source Route"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_ExtendedInternetProtocol: optionName = "Extended Internet Protocol"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_AddressExtension: optionName = "Address Extension"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_RouterAlert: optionName = "Router Alert"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_SelectiveDirectedBroadcast: optionName = "Selective Directed Broadcast"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_DynamicPacketState: optionName = "Dynamic Packet State"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_UpstreamMulticastPkt: optionName = "Upstream Multicast Packet"; break;
		case pcpp::IPv4OptionTypes::IPV4OPT_Unknown: optionName = "Unknown"; break;
	}

	return optionName;
}

std::string getProtocolString(pcpp::ProtocolType protocolType)
{
	std::string protocolStr;

	switch (protocolType)
	{
		case pcpp::Ethernet: protocolStr = "Ethernet"; break;
		case pcpp::IPv4: protocolStr = "IPv4"; break;
		case pcpp::IPv6: protocolStr = "IPv6"; break;
		case pcpp::ARP: protocolStr = "ARP"; break;
		case pcpp::ICMP: protocolStr = "ICMP"; break;
		case pcpp::TCP: protocolStr = "TCP"; break;
		case pcpp::UDP: protocolStr = "UDP"; break;
		case pcpp::DNS: protocolStr = "DNS"; break;
		case pcpp::DHCP: protocolStr = "DHCP"; break;
		case pcpp::UnknownProtocol: protocolStr = "Desconocido"; break;
	}

	return protocolStr;
}

std::array<uint8_t, 3> secondsToTime(uint32_t seconds)
{
	std::array<uint8_t, 3> time;
	time[0] = seconds / 3600;
	seconds %= 3600;
	time[1] = seconds / 60;
	seconds %= 60;
	time[2] = seconds;

	return time;
}
