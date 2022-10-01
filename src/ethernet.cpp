#include "ethernet.hpp"
#include "utils.hpp"

#include <cstdio>
#include <cstring>
#include <cstdlib>

Ethernet::Ethernet(void)
: dst(), src(), data()
{
	this->type = 0;
}

void Ethernet::print(bool hex)
{
	printf("Destination Address\n");
	dst.print();
	printf("\n\n");

	printf("Source Address\n");
	src.print();
	printf("\n\n");

	printf("Type\n");
	printf("%02X ", ((unsigned char*)&type)[0]);
	printf("%02X", ((unsigned char*)&type)[1]);
	printf(" (%u)", this->type);
	if (this->type == 8)
		printf(" IPV4");
	printf("\n\n");

	printf("Data\n");
	data.print(16, hex);
	printf("\n\n");
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
