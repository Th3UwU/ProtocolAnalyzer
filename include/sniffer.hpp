#ifndef _SNIFFER_HPP
#define _SNIFFER_HPP

#include <pcpp/ProtocolType.h>
#include <pcpp/IPv4Layer.h>
#include <pcpp/EthLayer.h>

class Sniffer
{
public:
	Sniffer(void);
	~Sniffer(void) = default;

	void init(void);
	void protocolMenu(void);
	void readMenu(void);

	void printPacketEth(pcpp::EthLayer* layer);
	void printPacketIpv4(pcpp::IPv4Layer* layer);

	pcpp::ProtocolType protocolType;
};

#endif
