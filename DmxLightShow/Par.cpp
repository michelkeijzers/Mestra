// Par.h
// Properties of a single RGBW par.

#include <assert.h>
#include <stdint.h>

#include "MathUtils.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(DMX_SIMPLE_CLASS)
#include "Fixture.h"
#include "Par.h"
#include "MestraTypes.h"


// MAX_PAR_INTENSITIES:                                              0  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47   48
static const dmx_value_t _red2Dmx  [MAX_PAR_INTENSITIES] PROGMEM = { 0, 9, 10, 12, 13, 15, 17, 18, 20, 21, 23, 25, 26, 27, 28, 29, 30, 31, 32, 34, 36, 38, 40, 44, 48, 52, 56, 58, 62, 69, 75, 82, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 255 };
static const dmx_value_t _green2Dmx[MAX_PAR_INTENSITIES] PROGMEM = { 0, 1,  1,  1,  1,  2,  2,  3,  3,  4,  5,  6,  6,  7,  7,  7,  8,  9, 10, 10, 10, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15, 16, 17,  20,  25,  30,  35,  40,  50,  60,  80, 100, 120, 140, 160, 180, 200, 220, 255 };
static const dmx_value_t _blue2Dmx [MAX_PAR_INTENSITIES] PROGMEM = { 0, 1,  1,  2,  2,  3,  3,  4,  4,  5,  5,  6,  7,  7,  8,  9, 10, 11, 12, 13, 14, 16, 18, 20, 22, 24, 28, 32, 36, 40, 44, 50, 60,  70,  80,  90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 220, 240, 255 };


Par::Par()
	:  
	_platformPar(0),
	_defaultColor(),
	_alternateColor(),
	_activeColor(true)
{
}


Par::~Par()
{
}


PlatformPar& Par::GetPlatformPar()
{
	return *_platformPar;
}


void Par::SetPlatform(PlatformFixture* platformFixture, PlatformPar* platformPar)
{
	SetPlatformFixture(platformFixture);
	_platformPar = platformPar;
}


Irgbw& Par::GetDefaultColor()
{
	return _defaultColor;
}


Irgbw& Par::GetAlternateColor()
{
	return _alternateColor;
}


/* virtual */ dmx_value_t Par::GetRed2Dmx(intensity_t red)
{
	return GetPlatformPar().GetRed2GammaCorrectedDmx(red);
}


/* virtual */ dmx_value_t Par::GetGreen2Dmx(intensity_t green)
{
	return GetPlatformPar().GetGreen2GammaCorrectedDmx(green);
}


/* virtual */ dmx_value_t Par::GetBlue2Dmx(intensity_t blue)
{
	return GetPlatformPar().GetBlue2GammaCorrectedDmx(blue);
}


/* virtual */ dmx_value_t Par::GetWhite2Dmx(intensity_t white)
{
	(void)white;

	assert(false);

	return 0;
}
