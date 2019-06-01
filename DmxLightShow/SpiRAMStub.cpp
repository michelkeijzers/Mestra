#ifdef _WINDOWS

#include "SpiRAMStub.h"
#include "assert.h"
#include "string.h"


#define SRAM_PAGE_SIZE                32


SpiRAM::SpiRAM(int8_t clock, int8_t ssPin)
	: _sram { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						' ', ' ' },
	_enabled(true)
{
	(void)clock;
	(void)ssPin;

	for (int n = 0; n < SRAM_SIZE; n++)
	{
		_sram[n] = n % 256; // Pattern
	}
}


void SpiRAM::enable()
{
	_enabled = true;
}


void SpiRAM::disable()
{
	_enabled = false;
}


char SpiRAM::read_byte(int address)
{
	assert(address >= 0);
	assert(address < SRAM_SIZE);

	return _sram[address];
}



char SpiRAM::write_byte(int address, char data_byte)
{
	assert(address >= 0);
	assert(address < SRAM_SIZE);

	_sram[address] = data_byte;

	return data_byte;
}


void SpiRAM::read_page(int address, char* buffer)
{
	assert(address >= 0);
	assert(address < SRAM_SIZE - SRAM_PAGE_SIZE);

	memcpy(buffer, &(_sram[address]), SRAM_PAGE_SIZE);
}

void SpiRAM::write_page(int address, char* buffer)
{
	assert(address >= 0);
	assert(address < SRAM_SIZE - SRAM_PAGE_SIZE);

	memcpy(&(_sram[address]), buffer, SRAM_PAGE_SIZE);
}


void SpiRAM::read_stream(int address, char* buffer, int length)
{
	assert(address >= 0);
	assert(address < SRAM_SIZE - length);

	memcpy(buffer, &(_sram[address]), length);
}


void SpiRAM::write_stream(int address, char* buffer, int length)
{
	assert(address >= 0);
	assert(address < SRAM_SIZE - length);

	memcpy(&(_sram[address]), buffer, length);
}

#endif // WINDOWS