#include "mac.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

Mac::Mac(void)
{
	memset(this->address, 0, 6);
}

void Mac::print(void)
{
	for (uint8_t i = 0; i < 5; i++)
		printf("\033[1;32m%02X:\033[0m", this->address[i]);
	printf("\033[1;32m%02X\033[0m", this->address[5]);
}

void Mac::randomize(void)
{
	for (uint8_t i = 0; i < 6; i++)
		this->address[i] = rand() % 256;
}