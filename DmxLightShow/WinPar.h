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
	virtual ~WinPar();

	/* override */ dmx_value_t GetRed2GammaCorrectedDmx(dmx_value_t red);
	/* override */ dmx_value_t GetGreen2GammaCorrectedDmx(dmx_value_t green);
	/* override */ dmx_value_t GetBlue2GammaCorrectedDmx(dmx_value_t blue);
	/* override */ dmx_value_t GetWhite2GammaCorrectedDmx(dmx_value_t white);

	/* override */ dmx_value_t Value2WindowsIntensity(uint8_t x);

#ifdef COLOR_CHANGE_CHECKING
	/* override */ void CheckColorChanged(ParRgb& par, dmx_channel_t dmxOffsetChannel, Irgbw& irgbw);
#endif // COLOR_CHANGE_CHECKING
};

