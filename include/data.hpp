#ifndef DATA_HPP
#define DATA_HPP

#include <cstdint>

struct Data
{
	Data(void);
	~Data(void);

	uint8_t* raw;
	
	void print(uint16_t size, uint16_t line_length);
	uint16_t randomize(uint16_t min, uint16_t max);
};

#endif
