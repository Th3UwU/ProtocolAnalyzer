#include <ethernet.hpp>
#include <utils.hpp>

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
	printf("\033[1;31mPreamble\033[0m\n");
	for (uint8_t i = 0; i < 8; i++)
		printf("\033[1;32m%02X \033[0m", this->preamble[i]);
	printf("\n\n");

	printf("\033[1;31mDestination Address\033[0m\n");
	dst.print();
	printf("\n\n");

	printf("\033[1;31mSource Address\033[0m\n");
	src.print();
	printf("\n\n");

	printf("\033[1;31mType\033[0m\n");
	printf("\033[1;32m%02X \033[0m", this->type[0]);
	printf("\033[1;32m%02X\033[0m", this->type[1]);
	printf("\n\n");

	printf("\033[1;31mData\033[0m\n");
	this->data.print(16, hex);
	printf("\n\n");

	printf("\033[1;31mChecksum\033[0m\n");

	for (uint8_t i = 0; i < 4; i++)
		printf("\033[1;32m%02X \033[0m", ((uint8_t*)&this->fcs)[i]);

	printf("\033[1;36m(%u)\033[0m", this->fcs);
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
