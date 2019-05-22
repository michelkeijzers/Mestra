#include "McuPar.h"
#include "MestraTypes.h"


McuPar::McuPar()
{
}


McuPar::~McuPar()
{
}


/* override */ dmx_value_t McuPar::GetRed2Dmx(dmx_value_t red)
{
	return red;
}


/* override */dmx_value_t McuPar::GetGreen2Dmx(dmx_value_t green)
{
	return green;
}


/* override */ dmx_value_t  McuPar::GetBlue2Dmx(dmx_value_t blue)
{
	return blue;
}


/* override */ dmx_value_t McuPar::GetWhite2Dmx(dmx_value_t white)
{
	return white;
}


/* override */ dmx_value_t McuPar::Value2WindowsIntensity(uint8_t value)
{
	return value;
};


/* override */ void McuPar::CheckColorChanged(Par& par, dmx_channel_t dmxOffsetChannel, Irgbw& irgbw)
{
	(void)par;
	(void)dmxOffsetChannel;
	(void)irgbw;
}