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
	void loadFromFile(const char* path);

	Mac dst;
	Mac src;
	unsigned short type;
	Data data;
};

#endif
