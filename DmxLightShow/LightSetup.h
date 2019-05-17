// LightSetup.h
// Set of pars/LED bars.

#pragma once

#include "ClassNames.h" 
#include HEADER_FILE(PAR_CLASS)
#include "Strobo.h"


const uint8_t NR_OF_PARS = 14;


class LightSetupClass
{
public:
	LightSetupClass();

	~LightSetupClass();

	virtual void AddFixtures();

	Par& GetPar(int parNumber);

protected:
	PAR_CLASS _pars[NR_OF_PARS];

	Strobo _strobo;
};

#ifndef _WINDOWS
extern LightSetupClass LightSetup;
#endif