#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <ethernet.hpp>
#include <mac.hpp>

int main(void)
{
	srand(time(nullptr));

	Mac a;
	a.randomize();
	a.print();

	return 0;
}