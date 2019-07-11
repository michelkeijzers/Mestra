// LightSetup.cpp
// Set of pars/LED bars.

#include "AssertUtils.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "LightSetup.h"
#include "MestraTypes.h"
#include "ChinesePar.h"
#include "LedBarSegment.h"


// Singleton instance.
LightSetupClass LightSetup;


LightSetupClass::LightSetupClass()
:
	_pars {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
	_platformLightSetup()
{
}


LightSetupClass::~LightSetupClass()
{
}


PlatformLightSetup* LightSetupClass::GetPlatform() const
{
	return _platformLightSetup; 
}


void LightSetupClass::SetPlatformLightSetup(PlatformLightSetup* platformLightSetup)
{
	_platformLightSetup = platformLightSetup;
	_platformLightSetup->SetPars(_pars);
}


Strobo& LightSetupClass::GetStrobo()
{
	return _strobo;
}


void LightSetupClass::CreateFixtures()
{
	for (fixture_number_t fixtureNumber = 0; fixtureNumber < NR_OF_CHINESE_PARS; fixtureNumber++)
	{
		_pars[fixtureNumber] = new ChinesePar(fixtureNumber);
	}

	for (fixture_number_t fixtureNumber = NR_OF_CHINESE_PARS; fixtureNumber < NR_OF_PARS; fixtureNumber++)
	{
		_pars[fixtureNumber] = new LedBarSegment(fixtureNumber);
		static_cast<LedBarSegment&>(GetPar(fixtureNumber)).SetSegmentNumber((fixtureNumber - NR_OF_CHINESE_PARS) % 3U);
	}

	// Do not use PROGMEM, this results in segmentation faults in Arduino IDE when unrelated code changes
	static const dmx_channel_t dmxOffsetChannels[NR_OF_PARS] =
	  { 1, 9, 17, 25, 33, 41, 49, 57, 65, 73, 81, 89, 97, 105, 113, 113, 113 };

	for (fixture_number_t fixture_number = 0; fixture_number < NR_OF_PARS; fixture_number++)
	{ 
		Par& par = LightSetup.GetPar(fixture_number);
		par.SetDmxOffsetChannel(dmxOffsetChannels[fixture_number]);
		static_cast<LedBarSegment&>(par).SetInitialMode();
	}
}


Par& LightSetupClass::GetPar(fixture_number_t parNumber) const
{
	AssertUtils::MyAssert(parNumber < NR_OF_PARS);
	return *_pars[parNumber];
}


/* static */ void LightSetupClass::AllOff()
{
	for (fixture_number_t parNumber = 0U; parNumber < NR_OF_PARS; parNumber++)
	{
		Par& par = LightSetup.GetPar(parNumber);

		Irgbw actualColor;
		par.GetActualColor(actualColor);
		actualColor.SetWhite(0);
		par.WriteIrgbw(actualColor);
		par.StroboChanged();
	}
}
