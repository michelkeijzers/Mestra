// LightSetup.h
// Set of pars/LED bars.

#pragma once

#include "ClassNames.h" 
#include "Par.h"
#include "Strobo.h"
#include "MestraTypes.h"
#include "PlatformLightSetup.h"

const fixture_number_t NR_OF_PARS = 14;

class LightSetupClass
{
public:
	LightSetupClass();
	~LightSetupClass();

	PlatformLightSetup* GetPlatform();
	void SetPlatformLightSetup(PlatformLightSetup* platformLightSetup);

	void CreateFixtures();

	Par& GetPar(fixture_number_t parNumber);

	Strobo& GetStrobo();

private:
	PlatformLightSetup* _platformLightSetup;

	Par _pars[NR_OF_PARS];

	Strobo _strobo;
};

// Instance
extern LightSetupClass LightSetup;
