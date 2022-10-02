#ifndef PACKET_HPP
#define PACKET_HPP

#include "mac.hpp"
#include "data.hpp"

#include <string>

struct Packet
{
	Packet(void) = default;
	virtual ~Packet(void) = default;

	virtual void print(bool hex = false) = 0;
	virtual void randomize(unsigned short min, unsigned short max) = 0;
	virtual void loadFromFile(const char* path) = 0;
	virtual unsigned int getSize(void) = 0;
	virtual std::string getType(void) = 0;
};

struct Ethernet : public Packet
{
	Ethernet(void);
	virtual ~Ethernet(void) = default;

	virtual void print(bool hex = false) override;
	virtual void randomize(unsigned short min, unsigned short max) override;
	virtual void loadFromFile(const char* path) override;
	virtual unsigned int getSize(void) override;
	virtual std::string getType(void) override;

	Mac dst;
	Mac src;
	unsigned short type;
	Data data;
};

#endif
