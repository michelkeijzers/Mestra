// Par.h
// Properties of a single RGBW par.

#pragma once

#include <stdint.h>
#include "ClassNames.h"
#include "Irgbw.h"
#include "Fixture.h"
#include "MestraTypes.h"
#include "PlatformPar.h"

#define MAX_PAR_INTENSITIES         (intensity_t)   49  // For red, green, blue, ...
#define MAX_PAR_INTENSITY           (intensity_t)  (MAX_PAR_INTENSITIES - 1)
#define MAX_INTENSITY               (intensity_t)  255 // For intensity, assumed linear


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

	virtual void GetActualColor(Irgbw& actualColor) = 0;

	virtual void WriteIrgb(Irgbw& irgbw) = 0;
	virtual void WriteIrgbw(Irgbw& irgbw) = 0;

	Irgbw& GetDefaultColor();

	Irgbw& GetAlternateColor();

protected:
	virtual dmx_value_t GetRed2Dmx(intensity_t red) = 0;
	virtual dmx_value_t GetGreen2Dmx(intensity_t green) = 0;
	virtual dmx_value_t GetBlue2Dmx(intensity_t blue) = 0;
	virtual dmx_value_t GetWhite2Dmx(intensity_t white) = 0;

private:
	PlatformPar* _platformPar;

	Irgbw _defaultColor;

	// Used for cross/multicolor programs
	Irgbw _alternateColor;

	// True when going towards or already default color active, false if going towards or alternate color is active.
	bool _activeColor;
};
