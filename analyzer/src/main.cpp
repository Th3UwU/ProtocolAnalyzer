#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <ethernet.hpp>
#include <mac.hpp>
#include <data.hpp>

int main(void)
{
	srand(time(nullptr));

	Data data;
	uint16_t size = data.randomize(256, 256);
	printf("\n\n");
	data.print(size, 16);
	printf("\n\n");

	printf("SIZE: %lu\n", sizeof(Ethernet));


	return 0;
}