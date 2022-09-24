#include <mac.hpp>
#include <cstdio>
#include <cstdlib>

void Mac::print(void)
{
	for (uint8_t i = 0; i < 5; i++)
		printf("%02X:", this->address[i]);
	printf("%02X:", this->address[5]);
}

void Mac::randomize(void)
{
	for (uint8_t i = 0; i < 6; i++)
		this->address[i] = rand() % 256;
}