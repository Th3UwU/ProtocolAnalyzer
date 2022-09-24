#include <data.hpp>

#include <cstdio>
#include <cstdlib>

Data::Data(void)
{
	this->raw = nullptr;
}

Data::~Data(void)
{
	operator delete(this->raw);
}

void Data::print(uint16_t size, uint16_t line_length)
{
	uint16_t l = 0;

	for (uint16_t i = 0; i < size; i++)
	{
		if ((this->raw[i] >= 32) and (this->raw[i] <= 126))
			printf("%c ", this->raw[i]);
		else
			printf(". ");

		l++;
		if (l == line_length)
			{printf("\n"); l = 0;}
	}
}

uint16_t Data::randomize(uint16_t min, uint16_t max)
{
	this->~Data();

	uint16_t size = (rand() % (max - min + 1)) + min;
	this->raw = (uint8_t*)operator new(size);

	for (uint16_t i = 0; i < size; i++)
		this->raw[i] = rand() % 256;

	return size;
}
