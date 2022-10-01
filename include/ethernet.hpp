#ifndef ETHERNET_HPP
#define ETHERNET_HPP

#include "mac.hpp"
#include "data.hpp"

#include <cstdint>
#include <iostream>

struct Ethernet
{
	Ethernet(void);
	~Ethernet(void) = default;

	void print(bool hex = false);
	void randomize(unsigned short min, unsigned short max);

	unsigned char preamble[8];
	Mac dst;
	Mac src;
	unsigned char type[2];
	Data data;
	unsigned int fcs;
};

#endif
