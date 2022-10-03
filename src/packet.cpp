#include "packet.hpp"
#include "gui/window_main.hpp"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <fmt/core.h>
#include <fmt/color.h>

Ethernet::Ethernet(void)
: dst(), src(), data()
{
	this->type = 0;
}

void Ethernet::print(bool hex)
{
	fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::green_yellow), "Destination Address\n");
	fmt::print(dst.getString(true));
	fmt::print("\n\n");

	fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::green_yellow), "Source Address\n");
	fmt::print("{0:s}\n\n", src.getString(true));

	fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::green_yellow), "Type\n");
	std::string protocolType;
	switch (this->type)
	{
		case 8: protocolType = "IPV4"; break;
		default: protocolType = "Unknown"; break;
	}

	fmt::print
	(
		fmt::fg(fmt::color::aquamarine), "{0:02X} {1:02X} ({2:d}) {3:s}\n\n",
		((unsigned char*)&this->type)[0], ((unsigned char*)&this->type)[1], this->type, protocolType
	);

	fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::green_yellow), "Data\n");
	fmt::print("{0:s}\n\n", data.getString(16, hex, true));
}

void Ethernet::randomize(uint16_t min, uint16_t max)
{
	dst.randomize();
	src.randomize();
	this->data.randomize(min, max);
	this->type = rand() % 0xFFFF;
}

void Ethernet::loadFromFile(const char* path)
{
	FILE* file = fopen(path, "rb");

	fseek(file, 0L, SEEK_END);
	unsigned int dataSize = ftell(file) - 14;
	fseek(file, 0L, SEEK_SET);

	fread((void*)dst.address, 1, 6, file);
	fread((void*)src.address, 1, 6, file);
	fread((void*)&type, 1, 2, file);

	data.alloc(dataSize);
	fread((void*)data.raw, 1, dataSize, file);

	fclose(file);
}

unsigned int Ethernet::getSize(void)
{
	return this->data.length + 14;
}

std::string Ethernet::getType(void)
{
	return std::string("Ethernet");
}

void Ethernet::appendInfo(WindowMain* windowMain)
{
	// Destination address
	wxStaticText* destinationAddress = new wxStaticText(windowMain->panel, wxID_ANY, dst.getString());
	destinationAddress->SetForegroundColour(wxColour(255, 0, 0));
	windowMain->sizerPanel->Add(destinationAddress, 0, wxALIGN_CENTER_HORIZONTAL, 0);

	windowMain->sizerPanel->Layout();
	/*
	fmt::print(fmt::fg(fmt::color::green_yellow), "Destination Address\n");
	dst.print();
	fmt::print("\n\n");
	*/
}
