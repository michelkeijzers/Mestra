// TestPar.h
// Properties of a single RGBW par.
// Only for Windows.

#pragma once


#include "Par.h"
#include "MestraTypes.h"


class TestPar : public Par
{
public:
	TestPar();

	~TestPar();


	dmx_value_t GetRed2Dmx(dmx_value_t red);

	dmx_value_t GetGreen2Dmx(dmx_value_t green);

	dmx_value_t GetBlue2Dmx(dmx_value_t blue);

	dmx_value_t GetWhite2Dmx(dmx_value_t white);

	dmx_value_t Value2WindowsIntensity(uint8_t x);
};

