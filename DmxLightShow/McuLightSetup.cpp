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


/* override */ void McuLightSetup::Print()
{
	//TODO
	// Serial.print...
}


/* override */ bool McuLightSetup::ArePropertiesSet()
{
	return true;
}
