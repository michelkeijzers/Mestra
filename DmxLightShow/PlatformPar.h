#pragma once

#include "MestraTypes.h"

// #define COLOR_CHANGE_CHECKING

class Par;

/* abstract */ class PlatformPar
{
public:
	PlatformPar();
	virtual ~PlatformPar();

	virtual dmx_value_t GetRed2GammaCorrectedDmx(dmx_value_t red) const = 0;
	virtual dmx_value_t GetGreen2GammaCorrectedDmx(dmx_value_t green) const = 0;
	virtual dmx_value_t GetBlue2GammaCorrectedDmx(dmx_value_t blue) const = 0;
	virtual dmx_value_t GetWhite2GammaCorrectedDmx(dmx_value_t white) const = 0;

	virtual dmx_value_t Value2WindowsIntensity(uint8_t x) const = 0;

#ifdef COLOR_CHANGE_CHECKING
	virtual void CheckColorChanged(ParRgb& par, dmx_channel_t dmxOffsetChannel, Irgbw& irgbw) = 0;
#endif // COLOR_CHANGE_CHECKING
};

