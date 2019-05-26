#pragma once

#include "Par.h"

class ChinesePar :
	public Par
{
	/* override */ void GetActualColor(Irgbw& actualColor);

	/* override */ dmx_value_t GetWhite2Dmx(intensity_t white);

	/* override */ void WriteIrgb(Irgbw& irgbw);
	/* override */ void WriteIrgbw(Irgbw& irgbw);
};

