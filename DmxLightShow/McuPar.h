#pragma once

#include "PlatformPar.h"

#include "MestraTypes.h"

class McuPar : public PlatformPar
{
public:
	McuPar();
	~McuPar();

	/* override */ dmx_value_t GetRed2Dmx(dmx_value_t red) 
	{
		return red;
	}

	/* override */ dmx_value_t GetGreen2Dmx(dmx_value_t green)
	{
		return green;
	}

	/* override */ dmx_value_t GetBlue2Dmx(dmx_value_t blue)
	{
		return blue;
	}

	/* override */ dmx_value_t GetWhite2Dmx(dmx_value_t white)
	{
		return white;
	}

	/* override */ dmx_value_t Value2WindowsIntensity(uint8_t value)
	{
		return value;
	};
};

