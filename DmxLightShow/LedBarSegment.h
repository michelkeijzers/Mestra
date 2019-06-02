#pragma once

#include "Par.h"

#define DATA_START_SEGMENT_NUMBER  DATA_SIZE_PAR

class LedBarSegment :
	public Par
{
public:
	LedBarSegment(fixture_number_t fixtureNumber);
	virtual ~LedBarSegment();

	void SetSegmentNumber(uint8_t segmentNumber);

private:
	/* override */ void GetActualColor(Irgbw& actualColor);

	/* override */ dmx_value_t GetRed2Dmx(intensity_t red);
	/* override */ dmx_value_t GetGreen2Dmx(intensity_t green);
	/* override */ dmx_value_t GetBlue2Dmx(intensity_t blue);
	/* override */ dmx_value_t GetWhite2Dmx(intensity_t white);

	/* override */ void WriteIrgb(Irgbw& irgbw);
	/* override */ void WriteIrgbw(Irgbw& irgbw);

	uint8_t GetSegmentNumber();

	int GetBaseDmxChannel();
	int GetRedDmxChannel();
	int GetGreenDmxChannel();
	int GetBlueDmxChannel();
};

