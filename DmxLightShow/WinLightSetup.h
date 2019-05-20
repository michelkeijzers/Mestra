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
	~WinLightSetup();

	/* override */ void SetProperties();

	/* override */ void Print();

	bool ArePropertiesSet();

private:
	timeb _programStartTime;

	bool _propertiesAreSet;
};

