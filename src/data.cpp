#include "data.hpp"

#include <fmt/core.h>
#include <fmt/color.h>
#include <cstdlib>

Data::Data(void)
{
	this->raw = nullptr;
	this->length = 0;
}

Data::~Data(void)
{
	operator delete(this->raw);
}

void Data::print(unsigned short line_length, bool hex)
{
	unsigned short l = 0;

	for (unsigned short i = 0; i < length; i++)
	{
		if (hex)
		{
			fmt::print(fmt::fg(fmt::color::light_pink), "{0:02X} ", this->raw[i]);
		}
		else
		{
			if ((this->raw[i] >= 32) and (this->raw[i] <= 126))
				fmt::print(fmt::fg(fmt::color::light_pink), "{0:c} ", this->raw[i]);
			else
				fmt::print(fmt::fg(fmt::color::light_pink), ". ");
		}

		l++;
		if ((l == line_length) and (i < length - 1))
			{fmt::print("\n"); l = 0;}
	}
}

void Data::randomize(unsigned short min, unsigned short max)
{
	this->~Data();

	this->length = (rand() % (max - min + 1)) + min;
	this->raw = (unsigned char*)operator new(this->length);

	for (unsigned short i = 0; i < length; i++)
		this->raw[i] = rand() % 256;
}

void Data::alloc(unsigned int bytes)
{
	this->raw = (unsigned char*)operator new(bytes);
	this->length = bytes;
}
