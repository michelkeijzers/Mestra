// WinPar.h
// Properties of a single RGBW par.
// Only for Windows.

#pragma once

#include "Par.h"
#include "MestraTypes.h"
#include "PlatformPar.h"

class WinPar : public PlatformPar
{
public:
	WinPar();
	~WinPar();

	/* override */ dmx_value_t GetRed2Dmx(dmx_value_t red);
	/* override */ dmx_value_t GetGreen2Dmx(dmx_value_t green);
	/* override */ dmx_value_t GetBlue2Dmx(dmx_value_t blue);
	/* override */ dmx_value_t GetWhite2Dmx(dmx_value_t white);

	/* override */ dmx_value_t Value2WindowsIntensity(uint8_t x);

	/* override */ void CheckColorChanged(Par& par, dmx_channel_t dmxOffsetChannel, Irgbw& irgbw);
};

