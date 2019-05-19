// Par.h
// Properties of a single RGBW par.

#pragma once


#include <stdint.h>
#include "ClassNames.h"
#include "Irgbw.h"
#include "Fixture.h"
#include HEADER_FILE(FIXTURE_CLASS)
#include "MestraTypes.h"


#define MAX_PAR_INTENSITIES           49  // For red, green, blue, white
#define MAX_PAR_INTENSITY            (MAX_PAR_INTENSITIES - 1)
#define MAX_INTENSITY                255 // For intensity, assumed linear

#define DMX_OFFSET_CHANNEL_INTENSITY  0
#define DMX_OFFSET_CHANNEL_RED        1
#define DMX_OFFSET_CHANNEL_GREEN      2
#define DMX_OFFSET_CHANNEL_BLUE       3
#define DMX_OFFSET_CHANNEL_WHITE      4


class Par : public FIXTURE_CLASS
{
protected:
	Irgbw _defaultColor;

	// Used for cross/multicolor programs
	Irgbw _alternateColor;

	// True when going towards or already default color active, false if going towards or alternate color is active.
	bool _activeColor;

public:
	Par();

	~Par();

	enum EActiveColor
	{
		Default,
		Alternate
	};

	Irgbw& GetActualColor(Irgbw& actualColor);


	void WriteIrgb(Irgbw& irgbw);

	void WriteIrgbw(Irgbw& irgbw);


	void IsAbstractClass() { }


	Irgbw& GetDefaultColor() 
	{
		return _defaultColor; 
	}

	Irgbw& GetAlternateColor()
	{
		return _alternateColor; 
	}

private:

	virtual dmx_value_t GetRed2Dmx(intensity_t red);

	dmx_value_t GetGreen2Dmx(intensity_t green);

	dmx_value_t GetBlue2Dmx(intensity_t blue);

	dmx_value_t GetWhite2Dmx(intensity_t white);
};
