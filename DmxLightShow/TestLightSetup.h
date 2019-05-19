// TestLightSetup.h
// Set of pars/LED bars.
// Only for Windows.

#pragma once

#include <sys/timeb.h>
#include "LightSetup.h"


class TestLightSetupClass : public LightSetupClass
{
public:
	TestLightSetupClass();

	~TestLightSetupClass();


	void AddFixtures();


	void Print();


private:
	timeb _programStartTime;;
};

extern TestLightSetupClass LightSetup;
