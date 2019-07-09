// Par.h
// Properties of a single RGBW par.

#include "Par.h"
#include "Fixture.h"
#include "MestraTypes.h"


Par::Par(fixture_number_t fixtureNumber)
	: 
	Fixture(fixtureNumber),
	_platformPar(nullptr)
{
}


Par::~Par()
{
}


PlatformPar& Par::GetPlatformPar() const
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


void Par::SetDefaultColorIrgb(Irgbw& color)
{
	_defaultColor.SetIrgb(color);
}


void Par::SetDefaultColorIrgbw(Irgbw& color)
{
	_defaultColor.SetIrgbw(color);
}


Irgbw& Par::GetAlternateColor()
{
	return _alternateColor;
}


void Par::SetAlternateColorIrgb(Irgbw& color)
{
	_alternateColor.SetIrgb(color);
}


void Par::SetAlternateColorIrgbw(Irgbw& color)
{
	_alternateColor.SetIrgbw(color);
}
