#pragma once

#include "Par.h"
#include "MestraTypes.h"

/*abstract */ class PlatformLightSetup
{
public:
	PlatformLightSetup();
	virtual ~PlatformLightSetup();

	virtual void SetProperties() = 0;
	
	virtual void PrintHeader() const = 0;
	virtual void PrintFixture(fixture_number_t fixtureNumber) const = 0;
	virtual void PrintFooter() const = 0;

	Par& GetPar(fixture_number_t parNumber) const;
	void SetPars(Par* pars[]);

	virtual bool ArePropertiesSet() const = 0;

private:
	Par** _pars;
};

