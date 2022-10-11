#include <iostream>
#include <fmt/core.h>

int main(void)
{
	std::cout << "Hello world\n" << fmt::format("NUMBER: {0:d}\n", 87);
	return 0;
}