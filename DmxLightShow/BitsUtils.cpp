// BitsUtils.cpp
// Utilities for bits and bytes.

#include "BitsUtils.h"


BitsUtils::BitsUtils()
{
}


BitsUtils::~BitsUtils()
{
}


/* static */ uint8_t BitsUtils::GetNrOfHighBits(uint32_t value)
{
	uint8_t nrOfHighBits = 0;
	while (value > 0)
	{
		nrOfHighBits += value & 1; // If right bit set, add 1
		value >>= 1; // Shift right
	}

	return nrOfHighBits;
}



/* static */ uint32_t BitsUtils::ChangeBit(uint32_t value, uint8_t bitNumber, bool set)
{
	return (value & ~(1 << bitNumber)) | (set ? 1 : 0) << bitNumber;
}