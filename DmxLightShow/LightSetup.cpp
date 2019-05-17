// LightSetup.cpp
// Set of pars/LED bars.

#include "LightSetup.h"


#ifndef _WINDOWS
LightSetupClass LightSetup;
#endif


LightSetupClass::LightSetupClass()
{
}


LightSetupClass::~LightSetupClass()
{
}


void LightSetupClass::AddFixtures()
{
	uint16_t dmxOffsetChannels[NR_OF_PARS] = 
	  { 1, 9, 17, 25, 33, 41, 49, 57, 65, 73, 81, 89, 97, 105 };

	for (int n = 0; n < NR_OF_PARS; n++)
	{
		_pars[n].SetDmxOffsetChannel(dmxOffsetChannels[n]);
	}
}


Par& LightSetupClass::GetPar(int parNumber)
{
	return _pars[parNumber];
}
