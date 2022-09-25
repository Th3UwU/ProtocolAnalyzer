#ifndef DATA_HPP
#define DATA_HPP

#include <cstdint>

struct Data
{
	Data(void);
	~Data(void);

	uint8_t* raw;
	uint16_t length;
	
	void print(uint16_t line_length, bool hex);
	void randomize(uint16_t min, uint16_t max);
};

#endif
