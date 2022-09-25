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
	eth.randomize();
	//eth.length = eth.data.randomize(64, 128);
	eth.print(true);

	return 0;
}