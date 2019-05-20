#include "PlatformLightSetup.h"

PlatformLightSetup::PlatformLightSetup()
	:
	_pars(0)
{
}


PlatformLightSetup::~PlatformLightSetup()
{
}


Par& PlatformLightSetup::GetPar(fixture_number_t parNumber)
{
	return _pars[parNumber]; 
}


void PlatformLightSetup::SetPars(Par* pars) 
{
	_pars = pars; 
}
