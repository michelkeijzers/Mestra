#pragma once

#include "PlatformLightSetup.h"
#include "Par.h" 

class McuLightSetup :
	public PlatformLightSetup
{
public:
	McuLightSetup();
	~McuLightSetup();

	/* override */ void SetProperties();

	/* override */ void PrintHeader();
	/* override */ void PrintFixture(fixture_number_t fixtureNumber);
	/* override */ void PrintFooter();

	bool ArePropertiesSet();
};

