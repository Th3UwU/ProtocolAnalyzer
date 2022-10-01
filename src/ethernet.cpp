#include "ethernet.hpp"
#include "utils.hpp"

#include <cstdio>
#include <cstring>
#include <cstdlib>

Ethernet::Ethernet(void)
: dst(), src(), data()
{
	memset(this->preamble, 0, 8);
	memset(this->type, 0, 2);
	this->fcs = 0;
}

void Ethernet::print(bool hex)
{
	printf("Preamble\n");
	for (uint8_t i = 0; i < 8; i++)
		printf("%02X ", preamble[i]);
	printf("\n\n");

	printf("Destination Address\n");
	dst.print();
	printf("\n\n");

	printf("Source Address\n");
	src.print();
	printf("\n\n");

	printf("Type\n");
	printf("%02X ", type[0]);
	printf("%02X", type[1]);
	printf("\n\n");

	printf("Data\n");
	data.print(16, hex);
	printf("\n\n");

	printf("Checksum\n");

	for (uint8_t i = 0; i < 4; i++)
		printf("%02X ", ((uint8_t*)&fcs)[i]);

	printf("(%u)", fcs);
	printf("\n\n");
}

void Ethernet::randomize(uint16_t min, uint16_t max)
{
	dst.randomize();
	src.randomize();
	this->data.randomize(min, max);
	this->type[0] = rand() % 256;
	this->type[1] = rand() % 256;
	
	// Calc checksum
	uint8_t* bytes = (uint8_t*)operator new(this->data.length + 14);

	memcpy((void*)&bytes[0], (void*)this->dst.address, 6);
	memcpy((void*)&bytes[6], (void*)this->src.address, 6);
	bytes[12] = this->type[0];
	bytes[13] = this->type[1];
	memcpy((void*)&bytes[14], (void*)this->data.raw, this->data.length);

	this->fcs = 0;
	for (uint16_t i = 0; i < (14 + this->data.length); i++)
		this->fcs += (unsigned char)bytes[i];

	/*
	printf("\n\n%02X\n\n", this->data.raw[this->data.length - 1]);
	printf("\n\n%02X\n\n", bytes[14 + this->data.length - 1]);
	*/

	operator delete(bytes);
}
