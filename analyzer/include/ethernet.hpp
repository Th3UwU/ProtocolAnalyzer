#ifndef ETHERNET_HPP
#define ETHERNET_HPP

#include <cstdint>

#include <mac.hpp>

struct Ethernet
{
	uint8_t preamble[8];
	Mac dst;
	Mac src;
	uint8_t length[2];
	uint8_t* data;
	uint8_t fcs[4];
};

#endif
