#ifndef DATA_HPP
#define DATA_HPP

#include <cstdint>

struct Data
{
	Data(void);
	~Data(void);

	unsigned char* raw;
	unsigned short length;
	
	void print(unsigned short line_length, bool hex);
	void randomize(unsigned short min, unsigned short max);
	void alloc(unsigned int bytes);
};

#endif
