#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <array>
#include <string>
#include <pcpp/IPv4Layer.h>

#ifdef _WIN32
	#include <winsock.h>
#endif

#ifdef unix
	#include <netinet/in.h>
#endif

void clear(void);
bool readInt(int& n);
void readString(std::string& string);
std::string getIPv4OptionName(pcpp::IPv4OptionTypes optionType);
std::string getProtocolString(pcpp::ProtocolType protocolType);
std::array<uint8_t, 3> secondsToTime(uint32_t seconds);

#endif
