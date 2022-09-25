#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <ethernet.hpp>
#include <mac.hpp>
#include <data.hpp>

int main(void)
{
	srand(time(nullptr));

	Ethernet eth;
	eth.randomize(64, 64);
	eth.print(true);

	printf("SIZE: %u\n", eth.data.length);

	return 0;
}