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
SpiRAM          SpiRam(0, SPI_RAM_SS_PIN);
LightSetupClass LightSetup(SpiRam);


LightSetupClass::LightSetupClass(SpiRAM& spiRam)
:
	_pars { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	_platformLightSetup(),
	_spiRam(spiRam),
	_fixtureDataNumber(-1)
{
	_fixtureData.ClearAll();
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
		_pars[fixtureNumber] = new ChinesePar(fixtureNumber);
	}

	for (fixture_number_t fixtureNumber = NR_OF_CHINESE_PARS; fixtureNumber < NR_OF_PARS; fixtureNumber++)
	{
		_pars[fixtureNumber] = new LedBarSegment(fixtureNumber);
		((LedBarSegment&)(_pars[fixtureNumber])).SetSegmentNumber((fixtureNumber - NR_OF_CHINESE_PARS) % 3);
	}

	// Do not use PROGMEM, this results in segmentation faults in Arduino IDE when unrelated code changes
	static const dmx_channel_t dmxOffsetChannels[NR_OF_PARS] =
	  { 1, 9, 17, 25, 33, 41, 49, 57, 65, 73, 81, 89, 97, 105, 113, 113, 113 };

	for (fixture_number_t fixture_number = 0; fixture_number < NR_OF_PARS; fixture_number++)
	{ 
		Par& par = LightSetup.GetPar(fixture_number);
		par.SetDmxOffsetChannel(dmxOffsetChannels[fixture_number]);
	}

	((LedBarSegment&) GetPar(NR_OF_CHINESE_PARS + 0)).SetSegmentNumber(0);
	((LedBarSegment&) GetPar(NR_OF_CHINESE_PARS + 1)).SetSegmentNumber(1);
	((LedBarSegment&) GetPar(NR_OF_CHINESE_PARS + 2)).SetSegmentNumber(2);
}


Par& LightSetupClass::GetPar(fixture_number_t parNumber)
{
	assert(parNumber < NR_OF_PARS);

	if (_fixtureDataNumber != parNumber)
	{
		_fixtureData.Save(_fixtureDataNumber);
		_fixtureData.Load(parNumber);
		_fixtureDataNumber = parNumber;
	}

	return *_pars[parNumber];
}


SpiRAM& LightSetupClass::GetSpiRam()
{
	return _spiRam;
}


fixture_number_t LightSetupClass::GetFixtureNumber()
{
	return _fixtureDataNumber;
}


void LightSetupClass::SetFixtureNumber(fixture_number_t fixtureNumber)
{
	assert(DATA_SIZE_MAX == 64);

	_fixtureData.WriteUint8(DATA_START_FIXTURE_NUMBER, fixtureNumber);
}


FixtureData& LightSetupClass::GetFixtureData()
{
	return _fixtureData;
}