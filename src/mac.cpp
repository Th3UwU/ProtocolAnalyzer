#include "mac.hpp"

#include <fmt/core.h>
#include <fmt/color.h>

Mac::Mac(void)
{
	memset(this->address, 0, 6);
}

std::string Mac::getString(bool color)
{
	std::string str;

	if (color)
	{
		for (uint8_t i = 0; i < 5; i++)
			str += fmt::format(fmt::fg(fmt::color::salmon), "{0:02X}:", this->address[i]);
		str += fmt::format(fmt::fg(fmt::color::salmon), "{0:02X}", this->address[5]);
	}
	else
	{
		for (uint8_t i = 0; i < 5; i++)
			str += fmt::format("{0:02X}:", this->address[i]);
		str += fmt::format("{0:02X}", this->address[5]);
	}

	return str;
}

void Mac::randomize(void)
{
	for (uint8_t i = 0; i < 6; i++)
		this->address[i] = rand() % 256;
}