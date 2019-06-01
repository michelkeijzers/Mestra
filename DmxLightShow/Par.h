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


#define DATA_START_DEFAULT_COLOR     DATA_SIZE_FIXTURE
#define DATA_START_ALTERNATE_COLOR  (DATA_START_DEFAULT_COLOR   + 5)
#define DATA_SIZE_PAR               (DATA_START_ALTERNATE_COLOR + 5)

class Par : public Fixture
{
public:
	Par(fixture_number_t fixtureNumber);
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

	void GetDefaultColor(Irgbw& color);

	void SetDefaultColor(Irgbw& color);

	void GetAlternateColor(Irgbw& color);

	void SetAlternateColor(Irgbw& color);

protected:
	virtual dmx_value_t GetRed2Dmx(intensity_t red) = 0;
	virtual dmx_value_t GetGreen2Dmx(intensity_t green) = 0;
	virtual dmx_value_t GetBlue2Dmx(intensity_t blue) = 0;
	virtual dmx_value_t GetWhite2Dmx(intensity_t white) = 0;

private:
	PlatformPar* _platformPar;
};
