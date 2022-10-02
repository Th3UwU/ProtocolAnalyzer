#include "mac.hpp"

#include <fmt/core.h>
#include <fmt/color.h>

Mac::Mac(void)
{
	memset(this->address, 0, 6);
}

void Mac::print(void)
{
	for (uint8_t i = 0; i < 5; i++)
		fmt::print(fmt::fg(fmt::color::salmon), "{0:02X}:", this->address[i]);
	fmt::print(fmt::fg(fmt::color::salmon), "{0:02X}", this->address[5]);
}

void Mac::randomize(void)
{
	for (uint8_t i = 0; i < 6; i++)
		this->address[i] = rand() % 256;
}