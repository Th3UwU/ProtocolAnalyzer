#ifndef _SNIFFER_HPP
#define _SNIFFER_HPP

#include <pcpp/ProtocolType.h>

class Sniffer
{
public:
	Sniffer(void);
	~Sniffer(void) = default;

	void init(void);
	void protocolMenu(void);
	void readMenu(void);

	pcpp::ProtocolType protocolType;
};

#endif
