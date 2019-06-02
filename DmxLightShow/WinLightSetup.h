// TestLightSetup.h
// Set of pars/LED bars.
// Only for Windows.

#pragma once

#include <sys/timeb.h>
#include "LightSetup.h"

class WinLightSetup : public PlatformLightSetup
{
public:
	WinLightSetup();
	virtual ~WinLightSetup();

	/* override */ void SetProperties();

	/* override */ void PrintHeader();
	/* override */ void PrintFixture(fixture_number_t fixtureNumber);
	/* override */ void PrintFooter();
	
	bool ArePropertiesSet();

private:
	timeb _programStartTime;

	bool _propertiesAreSet;
};

