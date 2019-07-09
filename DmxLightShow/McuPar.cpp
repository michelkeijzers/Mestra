#include "McuPar.h"
#include "MestraTypes.h"


McuPar::McuPar()
{
}


McuPar::~McuPar()
{
}


/* override */ dmx_value_t McuPar::GetRed2GammaCorrectedDmx(dmx_value_t red) const
{
	return red;
}


/* override */dmx_value_t McuPar::GetGreen2GammaCorrectedDmx(dmx_value_t green) const
{
	return green;
}


/* override */ dmx_value_t  McuPar::GetBlue2GammaCorrectedDmx(dmx_value_t blue) const
{
	return blue;
}


/* override */ dmx_value_t McuPar::GetWhite2GammaCorrectedDmx(dmx_value_t white) const
{
	return white;
}


/* override */ dmx_value_t McuPar::Value2WindowsIntensity(uint8_t value) const
{
	return value;
};


#ifdef COLOR_CHANGE_CHECKING
/* override */ void McuPar::CheckColorChanged(ParRgb& par, dmx_channel_t dmxOffsetChannel, Irgbw& irgbw)
{
	(void)par;
	(void)dmxOffsetChannel;
	(void)irgbw;
}
#endif // #ifdef COLOR_CHANGE_CHECKING