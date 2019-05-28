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


