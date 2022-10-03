#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data
{
	Data(void);
	~Data(void);

	unsigned char* raw;
	unsigned short length;
	
	std::string getString(unsigned short line_length, bool hex, bool color = false);
	void randomize(unsigned short min, unsigned short max);
	void alloc(unsigned int bytes);
};

#endif
