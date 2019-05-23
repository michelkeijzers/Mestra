// LightSetup.h
// Set of pars/LED bars.

#pragma once

#include "ClassNames.h" 
#include "Par.h"
#include "PlatformLightSetup.h"
#include "Strobo.h"
#include "MestraTypes.h"


const fixture_number_t NR_OF_PARS = 14;


class LightSetupClass
{
public:
	LightSetupClass();

	~LightSetupClass();

	Par& GetPar(fixture_number_t parNumber);

	PlatformLightSetup* GetPlatform();
	
	void SetPlatformLightSetup(PlatformLightSetup* platformLightSetup);
	
	Strobo& GetStrobo();

	void CreateFixtures();

protected:
	Par _pars[NR_OF_PARS];

	Strobo _strobo;

	PlatformLightSetup* _platformLightSetup;
};


extern LightSetupClass LightSetup;

