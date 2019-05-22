#pragma once

#include "PlatformFixture.h"
#include "MestraTypes.h"
#include "Irgbw.h"

class Par;

/* abstract */ class PlatformPar
{
public:
	PlatformPar();
	~PlatformPar();

	virtual dmx_value_t GetRed2Dmx(dmx_value_t red) = 0;
	virtual dmx_value_t GetGreen2Dmx(dmx_value_t green) = 0;
	virtual dmx_value_t GetBlue2Dmx(dmx_value_t blue) = 0;
	virtual dmx_value_t GetWhite2Dmx(dmx_value_t white) = 0;

	virtual dmx_value_t Value2WindowsIntensity(uint8_t x) = 0;

	virtual void CheckColorChanged(Par& par, dmx_channel_t dmxOffsetChannel, Irgbw& irgbw) = 0;
};

