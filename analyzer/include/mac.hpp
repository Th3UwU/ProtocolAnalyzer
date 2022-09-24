#ifndef MAC_HPP
#define MAC_HPP

#include <cstdint>

struct Mac
{
	uint8_t address[6];

	void print(void);
	void randomize(void);
};

#endif
