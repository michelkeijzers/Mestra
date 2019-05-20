#pragma once

#include "PlatformFixture.h"

class McuFixture : public PlatformFixture
{
public:
	McuFixture();
	~McuFixture();

	/* override */ void PostProcessCheckIncreaseStep(bool increased) 
	{
	}

	
	/* override */ void SetProperties(
		const char* name1, const char* name2, const char* abbr, int x, int y)
	{
	}

};

