#pragma once

#include "Par.h"
#include "MestraTypes.h"

/*abstract */ class PlatformLightSetup
{
public:
	PlatformLightSetup();
	~PlatformLightSetup();

	virtual void SetProperties() = 0;

	virtual void Print() = 0;

	Par& GetPar(fixture_number_t parNumber);
	void SetPars(Par* pars[]);

	virtual bool ArePropertiesSet() = 0;

private:
	Par** _pars;
};

