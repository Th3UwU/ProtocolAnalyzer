#include "packet.hpp"

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <fmt/core.h>
#include <fmt/color.h>

Ethernet::Ethernet(void)
: dst(), src(), data()
{
	this->type = 0;
}

void Ethernet::print(bool hex)
{
	fmt::print(fmt::fg(fmt::color::green_yellow), "Destination Address\n");
	dst.print();
	fmt::print("\n\n");

	fmt::print(fmt::fg(fmt::color::green_yellow), "Source Address\n");
	src.print();
	fmt::print("\n\n");

	fmt::print(fmt::fg(fmt::color::green_yellow), "Type\n");
	fmt::print("{0:02X} ", ((unsigned char*)&type)[0]);
	fmt::print("{0:02X}", ((unsigned char*)&type)[1]);
	fmt::print(" ({0:d})", this->type);
	if (this->type == 8)
		fmt::print(fmt::fg(fmt::color::aquamarine), " IPV4");
	fmt::print("\n\n");

	fmt::print(fmt::fg(fmt::color::green_yellow), "Data\n");
	data.print(16, hex);
	fmt::print("\n\n");
}

void Ethernet::randomize(uint16_t min, uint16_t max)
{
	dst.randomize();
	src.randomize();
	this->data.randomize(min, max);
	this->type = rand() % 0xFFFF;
}

void Ethernet::loadFromFile(const char* path)
{
	FILE* file = fopen(path, "rb");

	fseek(file, 0L, SEEK_END);
	unsigned int dataSize = ftell(file) - 14;
	fseek(file, 0L, SEEK_SET);

	fread((void*)dst.address, 1, 6, file);
	fread((void*)src.address, 1, 6, file);
	fread((void*)&type, 1, 2, file);

	data.alloc(dataSize);
	fread((void*)data.raw, 1, dataSize, file);

	fclose(file);
}

unsigned int Ethernet::getSize(void)
{
	return this->data.length + 14;
}

std::string Ethernet::getType(void)
{
	return std::string("Ethernet");
}
