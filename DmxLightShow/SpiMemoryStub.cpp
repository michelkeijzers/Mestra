#include "SpiMemoryStub.h"


SPIFlash::SPIFlash()
{

}


SPIFlash::~SPIFlash()
{

}


void SPIFlash::begin()
{

}


bool SPIFlash::readByteArray(uint32_t address, uint8_t* pageBuffer, uint16_t spiPageSize)
{
	(void) address;
	(void) pageBuffer;
	(void) spiPageSize;

	return true;
}


bool SPIFlash::writeByteArray(uint32_t address, uint8_t* pageBuffer, uint16_t spiPageSize)
{
	(void) address;
	(void) pageBuffer;
	(void) spiPageSize;

	return true;
}