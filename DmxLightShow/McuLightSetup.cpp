#include "McuLightSetup.h"
#include "LightSetup.h"

#include "McuFixture.h"
#include "McuPar.h"

McuLightSetup::McuLightSetup()
	: PlatformLightSetup()
{
}


McuLightSetup::~McuLightSetup()
{
}


/* override */ void McuLightSetup::SetProperties()
{
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		GetPar(parNumber).SetPlatform(new McuFixture(), new McuPar());
	}
}


/* override */ void McuLightSetup::PrintHeader()
{
	//TODO
}


/* override */ void McuLightSetup::PrintFixture(fixture_number_t fixtureNumber)
{
	(void) fixtureNumber;
	//TODO
	// Serial.print...
}


/* override */ void McuLightSetup::PrintFooter()
{
	//TODO
}


/* override */ bool McuLightSetup::ArePropertiesSet()
{
	return true;
}
