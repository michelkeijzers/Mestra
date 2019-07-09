#include "PlatformLightSetup.h"


PlatformLightSetup::PlatformLightSetup()
	:
	_pars(nullptr)
{
}


PlatformLightSetup::~PlatformLightSetup()
{
}


Par& PlatformLightSetup::GetPar(fixture_number_t parNumber) const
{
	return *_pars[parNumber]; 
}


void PlatformLightSetup::SetPars(Par* pars[]) 
{
	_pars = pars; 
}
