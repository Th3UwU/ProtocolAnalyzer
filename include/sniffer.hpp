#ifndef _SNIFFER_HPP
#define _SNIFFER_HPP

class Sniffer
{
public:
	Sniffer(void);
	~Sniffer(void) = default;

	void init(void);
	void protocolMenu(void);
	void readMenu(void);

	enum class Protocol : int
	{
		Default = 0,
		Ethernet
	}protocolType;
};

#endif
