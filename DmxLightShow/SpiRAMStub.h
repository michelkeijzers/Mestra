#pragma once

#include <stdint.h>

// Assuming 32K256
#define SRAM_SIZE      32768


class SpiRAM
{
public:
	SpiRAM(int8_t clock, int8_t ssPin);

	void enable();
	void disable();
	char read_byte(int address);
	char write_byte(int address, char data_byte);
	void read_page(int address, char* buffer);
	void write_page(int address, char* buffer);
	void read_stream(int address, char* buffer, int length);
	void write_stream(int address, char* buffer, int length);

private:

	// Win only
	char _sram[SRAM_SIZE];
	bool _enabled;
};

