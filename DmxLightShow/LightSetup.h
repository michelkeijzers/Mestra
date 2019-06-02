// LightSetup.h
// Set of pars/LED bars.

#pragma once

#include "ClassNames.h" 
#include HEADER_FILE(SPI_RAM_CLASS)
#include "Par.h"
#include "PlatformLightSetup.h"
#include "Strobo.h"
#include "MestraTypes.h"
#include "FixtureData.h"


const fixture_number_t NR_OF_CHINESE_PARS = 14;
const fixture_number_t NR_OF_LED_SEGMENTS =  3;
const fixture_number_t NR_OF_PARS         = NR_OF_CHINESE_PARS + NR_OF_LED_SEGMENTS;

const uint8_t          SPI_RAM_SS_PIN = 4;


class LightSetupClass
{
public:
	LightSetupClass(SpiRAM& spiRam);

	~LightSetupClass();

	Par& GetPar(fixture_number_t parNumber);

	PlatformLightSetup* GetPlatform();
	
	void SetPlatformLightSetup(PlatformLightSetup* platformLightSetup);
	
	Strobo& GetStrobo();

	void CreateFixtures();

	SpiRAM& GetSpiRam();

	fixture_number_t GetFixtureNumber();
	void SetFixtureNumber(fixture_number_t fixtureNumber);

	FixtureData& GetFixtureData();

protected:
	Par* _pars[NR_OF_PARS];

	Strobo _strobo;

	PlatformLightSetup* _platformLightSetup;

	SpiRAM& _spiRam;

	fixture_number_t _fixtureDataNumber;
	FixtureData _fixtureData;
};


extern LightSetupClass LightSetup;

