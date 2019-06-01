#pragma once

#include "Par.h"
#include "MestraTypes.h"

/*abstract */ class PlatformLightSetup
{
public:
	PlatformLightSetup();
	~PlatformLightSetup();

	virtual void SetProperties() = 0;
	
	virtual void PrintHeader() = 0;
	virtual void PrintFixture(fixture_number_t fixtureNumber) = 0;
	virtual void PrintFooter() = 0;

	Par& GetPar(fixture_number_t parNumber);
	void SetPars(Par* pars[]);

	virtual bool ArePropertiesSet() = 0;

private:
	Par** _pars;
};

