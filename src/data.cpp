#include "data.hpp"

#include <fmt/core.h>
#include <fmt/color.h>

Data::Data(void)
{
	this->raw = nullptr;
	this->length = 0;
}

Data::~Data(void)
{
	operator delete(this->raw);
}

std::string Data::getString(unsigned short line_length, bool hex, bool color)
{
	std::string str;
	unsigned short l = 0;

	for (unsigned short i = 0; i < length; i++)
	{
		if (color)
		{
			if (hex)
				str += fmt::format(fmt::fg(fmt::color::light_pink), "{0:02X} ", this->raw[i]);
			else
			{
				if ((this->raw[i] >= 32) and (this->raw[i] <= 126))
					str += fmt::format(fmt::fg(fmt::color::light_pink), "{0:c} ", this->raw[i]);
				else
					str += fmt::format(fmt::fg(fmt::color::light_pink), ". ");
			}
		}
		else
		{
			if (hex)
				str += fmt::format("{0:02X} ", this->raw[i]);
			else
			{
				if ((this->raw[i] >= 32) and (this->raw[i] <= 126))
					str += fmt::format("{0:c} ", this->raw[i]);
				else
					str += fmt::format(". ");
			}
		}

		l++;
		if ((l == line_length) and (i < length - 1))
			{str += fmt::format("\n"); l = 0;}
	}

	return str;
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
