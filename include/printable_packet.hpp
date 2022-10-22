#ifndef _PRINTABLE_PACKET_HPP
#define _PRINTABLE_PACKET_HPP

#include <pcpp/Layer.h>
#include <pcpp/EthLayer.h>
#include <pcpp/IPv4Layer.h>
#include <pcpp/IPv6Layer.h>
#include <string>
#include <memory>

class PrintablePacket
{
public:
	PrintablePacket(void) = default;
	virtual ~PrintablePacket(void) = default;

	virtual std::string toString(void) = 0;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) = 0;
};

class PpacketEthernet : public PrintablePacket
{
public:
	PpacketEthernet(pcpp::EthLayer& layer);
	virtual ~PpacketEthernet(void) = default;

	virtual std::string toString(void) override;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) override;

	pcpp::EthLayer& layer;
};

class PpacketIPv4 : public PrintablePacket
{
public:
	PpacketIPv4(pcpp::IPv4Layer& layer);
	virtual ~PpacketIPv4(void) = default;

	virtual std::string toString(void) override;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) override;

	pcpp::IPv4Layer& layer;
};

std::unique_ptr<PrintablePacket> createPpacketFromLayer(pcpp::Layer& layer);

#endif
