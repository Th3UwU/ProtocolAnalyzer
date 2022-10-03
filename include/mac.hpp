#ifndef MAC_HPP
#define MAC_HPP

#include <string>

struct Mac
{
	Mac(void);
	~Mac(void) = default;

	unsigned char address[6];

	std::string getString(bool color = false);
	void randomize(void);
};

#endif
