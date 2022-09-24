#include <utils.hpp>

uint32_t check_sum(uint8_t* bytes, uint16_t size)
{
	uint32_t res = 0;

	for (uint16_t i = 0; i < size; i++)
		res += bytes[i];

	res % 0xFFFFFFFF;
	return res;
}