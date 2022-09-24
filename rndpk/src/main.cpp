#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

void error(void);
void createHeader(int type, unsigned short count);
unsigned int generate(int type, int maxBytes);

char buffer[65536];
char temp[65536];

FILE* f = nullptr;

int main(int argc, char* argv[])
{
	srand(time(nullptr));

	if (argc != 5)
		error();

	const int maxBytes = atoi(argv[1]);
	const unsigned short count = atoi(argv[2]);

	auto typeToInt = [argv]()
	{
		if (strcmp(argv[3], "eth") == 0)
			return 1;
		else
			return 0;
	};

	const int type = typeToInt();
	const char* filename = argv[4];

	f = fopen(filename, "w+");

	createHeader(type, count);
	for (int i = 0; i < count; i++)
	{
		int size = generate(type, maxBytes);
		fwrite(buffer, 1, size, f);
	}

	fclose(f);
	return 0;
}

void error(void)
{
	printf("Wrong number of arguments\n");
}

void createHeader(int type, unsigned short count)
{
	memset(buffer, 0, 8);
	memcpy(&buffer[1], (void*)(&count), 2);
	fwrite(buffer, 1, 8, f);

	switch (type)
	{
		case 0:
			buffer[0] = 1;

		default:
			break;
	}
}

unsigned int generate(int type, int maxBytes)
{
	switch (type)
	{
		case 1:
		{
			// preamble
			memset(buffer, 0, 8);

			// mac dst / src
			for (unsigned int i = 8; i < 20; i++)
				buffer[i] = rand() % 256;

			// type
			for (unsigned int i = 20; i < 22; i++)
				buffer[i] = rand() % 256;

			// random data
			unsigned int dataSize = (rand() % (maxBytes - 46 + 1)) + 46;
			for (unsigned int i = 22; i < (22 + dataSize); i++)
				buffer[i] = rand() % 256;

			// fcs
			unsigned int checkSum = 0;
			for (unsigned int i = 8; i < (22 + dataSize); i++)
				checkSum += (unsigned char)buffer[i];

			//checkSum %= 0xFFFFFFFF;
			//printf("CHECKSUM: %u\n", checkSum);

			memcpy(&buffer[22 + dataSize], (void*)(&checkSum), 4);

			return dataSize + 26;
		}

		default:
			return 0;
	}
}