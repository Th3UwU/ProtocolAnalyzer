#ifndef _PRINTABLE_PACKET_HPP
#define _PRINTABLE_PACKET_HPP

#include <pcpp/Layer.h>
#include <pcpp/EthLayer.h>
#include <pcpp/IPv4Layer.h>
#include <pcpp/IPv6Layer.h>
#include <pcpp/ArpLayer.h>
#include <pcpp/IcmpLayer.h>
#include <pcpp/TcpLayer.h>
#include <pcpp/UdpLayer.h>
#include <pcpp/DnsLayer.h>
#include <pcpp/DhcpLayer.h>
#include <string>
#include <memory>

class PrintablePacket
{
public:
	PrintablePacket(void) = default;
	virtual ~PrintablePacket(void) = default;

	virtual std::string toString(void) = 0;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) = 0;
	virtual std::string protocolToString(void) = 0;
};

class PpacketEthernet : public PrintablePacket
{
public:
	PpacketEthernet(pcpp::EthLayer& layer);
	virtual ~PpacketEthernet(void) = default;

	virtual std::string toString(void) override;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) override;
	virtual std::string protocolToString(void) override;

	pcpp::EthLayer& layer;
};

class PpacketIPv4 : public PrintablePacket
{
public:
	PpacketIPv4(pcpp::IPv4Layer& layer);
	virtual ~PpacketIPv4(void) = default;

	virtual std::string toString(void) override;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) override;
	virtual std::string protocolToString(void) override;

	pcpp::IPv4Layer& layer;
};

class PpacketARP : public PrintablePacket
{
public:
	PpacketARP(pcpp::ArpLayer& layer);
	virtual ~PpacketARP(void) = default;

	virtual std::string toString(void) override;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) override;
	virtual std::string protocolToString(void) override;

	pcpp::ArpLayer& layer;
};

class PpacketICMP : public PrintablePacket
{
public:
	PpacketICMP(pcpp::IcmpLayer& layer);
	virtual ~PpacketICMP(void) = default;

	virtual std::string toString(void) override;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) override;
	virtual std::string protocolToString(void) override;

	pcpp::IcmpLayer& layer;
};

class PpacketIPv6 : public PrintablePacket
{
public:
	PpacketIPv6(pcpp::IPv6Layer& layer);
	virtual ~PpacketIPv6(void) = default;

	virtual std::string toString(void) override;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) override;
	virtual std::string protocolToString(void) override;

	pcpp::IPv6Layer& layer;
};

class PpacketTCP : public PrintablePacket
{
public:
	PpacketTCP(pcpp::TcpLayer& layer);
	virtual ~PpacketTCP(void) = default;

	virtual std::string toString(void) override;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) override;
	virtual std::string protocolToString(void) override;

	pcpp::TcpLayer& layer;
};

class PpacketUDP : public PrintablePacket
{
public:
	PpacketUDP(pcpp::UdpLayer& layer);
	virtual ~PpacketUDP(void) = default;

	virtual std::string toString(void) override;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) override;
	virtual std::string protocolToString(void) override;

	pcpp::UdpLayer& layer;
};

class PpacketDNS : public PrintablePacket
{
public:
	PpacketDNS(pcpp::DnsLayer& layer);
	virtual ~PpacketDNS(void) = default;

	virtual std::string toString(void) override;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) override;
	virtual std::string protocolToString(void) override;

	pcpp::DnsLayer& layer;
};

class PpacketDHCP : public PrintablePacket
{
public:
	PpacketDHCP(pcpp::DhcpLayer& layer);
	virtual ~PpacketDHCP(void) = default;

	virtual std::string toString(void) override;
	virtual std::unique_ptr<PrintablePacket> getNextLayer(void) override;
	virtual std::string protocolToString(void) override;

	pcpp::DhcpLayer& layer;
};

std::unique_ptr<PrintablePacket> createPpacketFromLayer(pcpp::Layer& layer);

#endif
