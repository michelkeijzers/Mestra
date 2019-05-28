// LightSetup.cpp
// Set of pars/LED bars.

#include <assert.h>
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
	_platformLightSetup(0)
{
}


LightSetupClass::~LightSetupClass()
{
}


PlatformLightSetup* LightSetupClass::GetPlatform() 
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
		_pars[fixtureNumber] = new ChinesePar();
	}

	for (fixture_number_t fixtureNumber = NR_OF_CHINESE_PARS; fixtureNumber < NR_OF_PARS; fixtureNumber++)
	{
		_pars[fixtureNumber] = new LedBarSegment();
		((LedBarSegment&)(_pars[fixtureNumber])).SetSegmentNumber((fixtureNumber - NR_OF_CHINESE_PARS) % 3);
	}

	// Do not use PROGMEM, this results in segmentation faults in Arduino IDE when unrelated code changes
	static const dmx_channel_t dmxOffsetChannels[NR_OF_PARS] =
	  { 1, 9, 17, 25, 33, 41, 49, 57, 65, 73, 81, 89, 97, 105, 113, 113, 113 };

	for (fixture_number_t fixture_number = 0; fixture_number < NR_OF_PARS; fixture_number++)
	{ 
		GetPar(fixture_number).SetDmxOffsetChannel(dmxOffsetChannels[fixture_number]);
	}

	((LedBarSegment&) GetPar(NR_OF_CHINESE_PARS + 0)).SetSegmentNumber(0);
	((LedBarSegment&) GetPar(NR_OF_CHINESE_PARS + 1)).SetSegmentNumber(1);
	((LedBarSegment&) GetPar(NR_OF_CHINESE_PARS + 2)).SetSegmentNumber(2);
}


Par& LightSetupClass::GetPar(fixture_number_t parNumber)
{
	assert(parNumber < NR_OF_PARS);
	return *_pars[parNumber];
}
