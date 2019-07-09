// LightSetup.h
// Set of pars/LED bars.

#pragma once

#include "Par.h"
#include "PlatformLightSetup.h"
#include "Strobo.h"
#include "MestraTypes.h"


const fixture_number_t NR_OF_CHINESE_PARS = 14;
const fixture_number_t NR_OF_LED_SEGMENTS =  3;
const fixture_number_t NR_OF_PARS         = NR_OF_CHINESE_PARS + NR_OF_LED_SEGMENTS;


class LightSetupClass
{
public:
	LightSetupClass();

	~LightSetupClass();

	Par& GetPar(fixture_number_t parNumber) const;

	PlatformLightSetup* GetPlatform() const;
	
	void SetPlatformLightSetup(PlatformLightSetup* platformLightSetup);
	
	Strobo& GetStrobo();

	void CreateFixtures();

	static void AllOff();

protected:
	Par* _pars[NR_OF_PARS];

	Strobo _strobo;

	PlatformLightSetup* _platformLightSetup;
};


extern LightSetupClass LightSetup;

