#include "data.hpp"

#include <cstdio>
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

void Data::print(uint16_t line_length, bool hex)
{
	uint16_t l = 0;

	for (uint16_t i = 0; i < length; i++)
	{
		if (hex)
		{
			printf("%02X ", this->raw[i]);
		}
		else
		{
			if ((this->raw[i] >= 32) and (this->raw[i] <= 126))
				printf("%c ", this->raw[i]);
			else
				printf(". ");
		}

		l++;
		if ((l == line_length) and (i < length - 1))
			{printf("\n"); l = 0;}
	}
}

void Data::randomize(uint16_t min, uint16_t max)
{
	this->~Data();

	this->length = (rand() % (max - min + 1)) + min;
	this->raw = (uint8_t*)operator new(this->length);

	for (uint16_t i = 0; i < length; i++)
		this->raw[i] = rand() % 256;
}

void Data::alloc(unsigned int bytes)
{
	this->raw = (unsigned char*)operator new(bytes);
	this->length = bytes;
}
