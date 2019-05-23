// TestPar.cpp
// Properties of a single RGBW par.
// Only for Windows.

#ifdef _WINDOWS


#include <math.h>
#include "TestPar.h"
#include "MestraTypes.h"


TestPar::TestPar()
{
	// srand((unsigned int) time(NULL));
}


TestPar::~TestPar()
{
}


dmx_value_t TestPar::GetRed2Dmx(dmx_value_t red)
{
	return Value2WindowsIntensity(red);
}



dmx_value_t TestPar::GetGreen2Dmx(dmx_value_t green)
{
	return Value2WindowsIntensity(green);
}


dmx_value_t TestPar::GetBlue2Dmx(dmx_value_t blue)
{
	return Value2WindowsIntensity(blue);
}


dmx_value_t TestPar::GetWhite2Dmx(dmx_value_t white)
{
	return Value2WindowsIntensity(white);
}


/* value to better looking value (f(0)=0, f(128=180, f(255)=255, using gamma correction
See https://math.stackexchange.com/questions/3227585/what-formula-to-chose-a-nonlinear-formula/3227607?noredirect=1#comment6640358_3227607
*/
dmx_value_t TestPar::Value2WindowsIntensity(uint8_t x)
{
	return  (dmx_value_t)(255 * powf((float)x / MAX_PAR_INTENSITIES, 0.4f));
}


#endif