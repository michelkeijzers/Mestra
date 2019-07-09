#pragma once

#include "MestraTypes.h"
#include "PlatformPar.h"


class McuPar : public PlatformPar
{
public:
	McuPar();
	virtual ~McuPar();

	dmx_value_t GetRed2GammaCorrectedDmx(dmx_value_t red) const override;
	dmx_value_t GetGreen2GammaCorrectedDmx(dmx_value_t green) const override;
	dmx_value_t GetBlue2GammaCorrectedDmx(dmx_value_t blue) const override;
	dmx_value_t GetWhite2GammaCorrectedDmx(dmx_value_t white) const override;

	dmx_value_t Value2WindowsIntensity(uint8_t value) const override;

#ifdef COLOR_CHANGE_CHECKING
	void CheckColorChanged(ParRgb& par, dmx_channel_t dmxOffsetChannel, Irgbw& irgbw) override;
#endif // COLOR_CHANGE_CHECKING
};

