// LightSetup.cpp
// Set of pars/LED bars.

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "LightSetup.h"
#include "MestraTypes.h"


LightSetupClass LightSetup;


LightSetupClass::LightSetupClass()
	:
	_platformLightSetup(0)
{
}


LightSetupClass::~LightSetupClass()
{
}


PlatformLightSetup* LightSetupClass::GetPlatform() 
{
	return _platformLightSetup; 
}


void LightSetupClass::SetPlatformLightSetup(PlatformLightSetup* platformLightSetup)
{
	_platformLightSetup = platformLightSetup;
	_platformLightSetup->SetPars(_pars);
}


Strobo& LightSetupClass::GetStrobo()
{
	return _strobo;
}


void LightSetupClass::CreateFixtures()
{
	// Do not use PROGMEM, this results in segmentation faults in Arduino IDE when unrelated code changes
	static const dmx_channel_t dmxOffsetChannels[NR_OF_PARS] =
	  { 1, 9, 17, 25, 33, 41, 49, 57, 65, 73, 81, 89, 97, 105 };

	for (int n = 0; n < NR_OF_PARS; n++)
	{ 
		_pars[n].SetDmxOffsetChannel(dmxOffsetChannels[n]);
	}
}


Par& LightSetupClass::GetPar(fixture_number_t parNumber)
{
	return _pars[parNumber];
}
