#pragma once

#include "PlatformLightSetup.h"
#include "Par.h" 

class McuLightSetup :
	public PlatformLightSetup
{
public:
	McuLightSetup();
	~McuLightSetup();

	/* override */ void SetProperties();

	/* override */ void Print();

	bool ArePropertiesSet();
};

