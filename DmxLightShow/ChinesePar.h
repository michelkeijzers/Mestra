#pragma once

#include "Par.h"

class ChinesePar :
	public Par
{
	/* override */ void GetActualColor(Irgbw& actualColor);

	/* override */ dmx_value_t GetRed2Dmx(intensity_t red);
	/* override */ dmx_value_t GetGreen2Dmx(intensity_t green);
	/* override */ dmx_value_t GetBlue2Dmx(intensity_t blue);
	/* override */ dmx_value_t GetWhite2Dmx(intensity_t white);
	
	/* override */ void WriteIrgb(Irgbw& irgbw);
	/* override */ void WriteIrgbw(Irgbw& irgbw);
};

