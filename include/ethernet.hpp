#include <cstdint>

struct ethernet
{
	uint8_t preamble[8];
	uint8_t destination_mac_address[6];
	uint8_t source_mac_address[6];
	uint8_t length[2];
	uint8_t* data;
	uint8_t fcs[4];
};
