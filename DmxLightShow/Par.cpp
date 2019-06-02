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
#include "LightSetup.h"


Par::Par(fixture_number_t fixtureNumber)
	: 
	Fixture(fixtureNumber),
	_platformPar(0)
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


void Par::GetDefaultColor(Irgbw& color)
{
	return LightSetup.GetFixtureData().ReadIrgbw(DATA_START_DEFAULT_COLOR, color);
}


void Par::SetDefaultColorIrgb(Irgbw& color)
{
	LightSetup.GetFixtureData().WriteIrgb(DATA_START_DEFAULT_COLOR, color);
}


void Par::SetDefaultColorIrgbw(Irgbw& color)
{
	LightSetup.GetFixtureData().WriteIrgbw(DATA_START_DEFAULT_COLOR, color);
}


void Par::GetAlternateColor(Irgbw& color)
{
	return LightSetup.GetFixtureData().ReadIrgbw(DATA_START_ALTERNATE_COLOR, color);
}


void Par::SetAlternateColorIrgb(Irgbw& color)
{
	LightSetup.GetFixtureData().WriteIrgb(DATA_START_ALTERNATE_COLOR, color);
}


void Par::SetAlternateColorIrgbw(Irgbw& color)
{
	LightSetup.GetFixtureData().WriteIrgbw(DATA_START_ALTERNATE_COLOR, color);
}
