// WinPar.cpp
// Properties of a single RGBW par.
// Only for Windows.

#ifdef _WINDOWS


#include <math.h>
#include "WinPar.h"
#include "MestraTypes.h"
#include "ArduinoStub.h"

WinPar::WinPar()
{
	// srand((unsigned int) time(NULL));
}


WinPar::~WinPar()
{
}


dmx_value_t WinPar::GetRed2GammaCorrectedDmx(dmx_value_t red)
{
	return Value2WindowsIntensity(red);
}


dmx_value_t WinPar::GetGreen2GammaCorrectedDmx(dmx_value_t green)
{
	return Value2WindowsIntensity(green);
}


dmx_value_t WinPar::GetBlue2GammaCorrectedDmx(dmx_value_t blue)
{
	return Value2WindowsIntensity(blue);
}


dmx_value_t WinPar::GetWhite2GammaCorrectedDmx(dmx_value_t white)
{
	return Value2WindowsIntensity(white);
}


/* value to better looking value (f(0)=0, f(128=180, f(255)=255, using gamma correction
See https://math.stackexchange.com/questions/3227585/what-formula-to-chose-a-nonlinear-formula/3227607?noredirect=1#comment6640358_3227607
*/
dmx_value_t WinPar::Value2WindowsIntensity(uint8_t x)
{
	return  (dmx_value_t)(255 * powf((float)x / MAX_PAR_INTENSITIES, 0.4f));
}


#ifdef COLOR_CHANGE_CHECKING
/* override */ void WinPar::CheckColorChanged(ParRgb& par, dmx_channel_t dmxOffsetChannel, Irgbw& irgbw)
{
	PlatformPar& platformPar = par.GetPlatformPar();

	bool colorHasChanged = (
		(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_INTENSITY) != 
			irgbw.GetIntensity()) ||
		(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_RED) != 
			platformPar.GetRed2GammaCorrectedDmx(irgbw.GetRed())) ||
		(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_GREEN) != 
			platformPar.GetGreen2GammaCorrectedDmx(irgbw.GetGreen())) ||
		(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_BLUE) != 
			platformPar.GetBlue2GammaCorrectedDmx(irgbw.GetBlue())));

	if (colorHasChanged)
	{
		par.GetPlatformFixture().SetColorChanged(true);
	}
}
#endif // COLOR_CHANGE_CHECKING


#endif
