#include "packet.hpp"
#include "gui/window_main.hpp"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/font.h>
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
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	font.SetFaceName(wxString("Consolas"));

	// Destination address
	wxStaticText* destAddLabel = new wxStaticText(windowMain->panel, wxID_ANY, L"Dirección destino: ");
	destAddLabel->SetForegroundColour(wxColour(173, 255, 47));
	destAddLabel->SetFont(font.Bold());

	wxStaticText* destAddInfo = new wxStaticText(windowMain->panel, wxID_ANY, dst.getString());
	destAddInfo->SetForegroundColour(wxColour(250, 128, 114));
	destAddInfo->SetFont(font);

	wxBoxSizer* destAddBox = new wxBoxSizer(wxHORIZONTAL);
	destAddBox->Add(destAddLabel);
	destAddBox->Add(destAddInfo);
	windowMain->sizerPanel->Add(destAddBox, 0, wxALIGN_CENTER_HORIZONTAL, 0);

	// Destination address
	wxStaticText* srcAddLabel = new wxStaticText(windowMain->panel, wxID_ANY, L"Dirección fuente: ");
	srcAddLabel->SetForegroundColour(wxColour(173, 255, 47));
	srcAddLabel->SetFont(font.Bold());

	wxStaticText* srcAddInfo = new wxStaticText(windowMain->panel, wxID_ANY, src.getString());
	srcAddInfo->SetForegroundColour(wxColour(250, 128, 114));
	srcAddInfo->SetFont(font);

	wxBoxSizer* srcAddBox = new wxBoxSizer(wxHORIZONTAL);
	srcAddBox->Add(srcAddLabel);
	srcAddBox->Add(srcAddInfo);
	windowMain->sizerPanel->Add(srcAddBox, 0, wxALIGN_CENTER_HORIZONTAL, 0);

	// Type
	std::string protocolType;
	wxColour color(127, 255, 212);

	switch (this->type)
	{
		case 8: protocolType = "IPV4"; break;
		default: protocolType = "Desconocido"; color.Set(255, 0, 0); break;
	}

	wxStaticText* typeLabel = new wxStaticText(windowMain->panel, wxID_ANY, L"Tipo de protocolo: ");
	typeLabel->SetForegroundColour(wxColour(173, 255, 47));
	typeLabel->SetFont(font.Bold());

	wxStaticText* typeInfo = new wxStaticText(windowMain->panel, wxID_ANY, protocolType);
	typeInfo->SetForegroundColour(color);
	typeInfo->SetFont(font);
	
	wxBoxSizer* typeBox = new wxBoxSizer(wxHORIZONTAL);
	typeBox->Add(typeLabel);
	typeBox->Add(typeInfo);
	windowMain->sizerPanel->Add(typeBox, 0, wxALIGN_CENTER_HORIZONTAL, 0);

	// Data
	wxStaticText* dataLabel = new wxStaticText(windowMain->panel, wxID_ANY, L"Datos (RAW): ");
	dataLabel->SetForegroundColour(wxColour(173, 255, 47));
	dataLabel->SetFont(font.Bold());

	wxStaticText* dataInfo = new wxStaticText(windowMain->panel, wxID_ANY, data.getString(16, true));
	dataInfo->SetForegroundColour(wxColour(250, 128, 114));
	dataInfo->SetFont(font);

	wxBoxSizer* dataBox = new wxBoxSizer(wxVERTICAL);
	dataBox->Add(dataLabel);
	dataBox->Add(dataInfo);
	windowMain->sizerPanel->Add(dataBox, 0, wxALIGN_CENTER_HORIZONTAL, 0);
	
	//
	windowMain->sizerPanel->Layout();
}
