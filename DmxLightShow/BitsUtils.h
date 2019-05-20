// BitsUtils.h
// Utilities for bits and bytes.

#pragma once

#include <stdint.h>

class BitsUtils
{
private:
	BitsUtils();
	~BitsUtils();

public:
	static uint8_t GetNrOfHighBits(uint32_t value);
	
	//static uint8_t indexOfBit(uint32_t value, uint8_t bit); // bit 0..31
};

