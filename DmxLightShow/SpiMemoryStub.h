#pragma once


#include "MestraTypes.h"


#define SPI_PAGESIZE 256


class SPIFlash
{
public:
	SPIFlash();
	~SPIFlash();

	void begin();

	bool readByteArray(uint32_t address, uint8_t* pageBuffer, uint16_t spiPageSize);

	bool writeByteArray(uint32_t address, uint8_t* pageBuffer, uint16_t spiPageSize);
};

