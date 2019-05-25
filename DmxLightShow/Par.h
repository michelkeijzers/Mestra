// Par.h
// Properties of a single RGBW par.

#pragma once

#include <stdint.h>
#include "ClassNames.h"
#include "Irgbw.h"
#include "Fixture.h"
#include "MestraTypes.h"
#include "PlatformPar.h"

#define MAX_PAR_INTENSITIES          (intensity_t)    49  // For red, green, blue, white
#define MAX_PAR_INTENSITY            (intensity_t)    (MAX_PAR_INTENSITIES - 1)
#define MAX_INTENSITY                (intensity_t)   255 // For intensity, assumed linear

#define DMX_OFFSET_CHANNEL_INTENSITY (dmx_channel_t)   0
#define DMX_OFFSET_CHANNEL_RED       (dmx_channel_t)   1
#define DMX_OFFSET_CHANNEL_GREEN     (dmx_channel_t)   2
#define DMX_OFFSET_CHANNEL_BLUE      (dmx_channel_t)   3
#define DMX_OFFSET_CHANNEL_WHITE     (dmx_channel_t)   4

class Par : public Fixture
{
public:
	Par();
	~Par();

	void SetPlatform(PlatformFixture* platformFixture, PlatformPar* platformPar);

	enum EActiveColor
	{
		Default,
		Alternate
	};

	PlatformPar& GetPlatformPar();

	Irgbw& GetActualColor(Irgbw& actualColor);

	void WriteIrgb(Irgbw& irgbw);

	void WriteIrgbw(Irgbw& irgbw);

	void IsAbstractClass() { }

	Irgbw& GetDefaultColor();

	Irgbw& GetAlternateColor();
	
private:
	PlatformPar* _platformPar;

	Irgbw _defaultColor;

	// Used for cross/multicolor programs
	Irgbw _alternateColor;

	// True when going towards or already default color active, false if going towards or alternate color is active.
	bool _activeColor;

	virtual dmx_value_t GetRed2Dmx(intensity_t red);
	dmx_value_t GetGreen2Dmx(intensity_t green);
	dmx_value_t GetBlue2Dmx(intensity_t blue);
	dmx_value_t GetWhite2Dmx(intensity_t white);
};
