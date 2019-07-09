// Par.h
// Properties of a single RGBW par.

#pragma once

#include "Irgbw.h"
#include "Fixture.h"
#include "MestraTypes.h"
#include "PlatformPar.h"


#define PAR_MAX_PAR_INTENSITIES         (intensity_t)   49  // For red, green, blue, ...
#define PAR_MAX_PAR_INTENSITY           (intensity_t)  (PAR_MAX_PAR_INTENSITIES - 1)
#define PAR_MAX_INTENSITY               (intensity_t)  255 // For intensity, assumed linear

#define PAR_DATA_START_DEFAULT_COLOR     FIXTURE_DATA_SIZE_FIXTURE
#define PAR_DATA_START_ALTERNATE_COLOR  (PAR_DATA_START_DEFAULT_COLOR   + 5)
#define PAR_DATA_SIZE                   (PAR_DATA_START_ALTERNATE_COLOR + 5)


class Par : public Fixture
{
public:
	explicit Par(fixture_number_t fixtureNumber);
	virtual ~Par();

	void SetPlatform(PlatformFixture* platformFixture, PlatformPar* platformPar);

	enum EActiveColor
	{
		Default,
		Alternate
	};

	PlatformPar& GetPlatformPar() const;

	virtual void GetActualColor(Irgbw& color) const = 0;

	virtual void WriteIrgb(Irgbw& irgbw) = 0;
	virtual void WriteIrgbw(Irgbw& irgbw) = 0;

	Irgbw& GetDefaultColor();

	void SetDefaultColorIrgb(Irgbw& color);
	void SetDefaultColorIrgbw(Irgbw& color);

  Irgbw& GetAlternateColor();

	void SetAlternateColorIrgb(Irgbw& color);
	void SetAlternateColorIrgbw(Irgbw& color);

	virtual intensity_t GetClosestRed(dmx_value_t value) const = 0;
	virtual intensity_t GetClosestGreen(dmx_value_t value) const = 0;
	virtual intensity_t GetClosestBlue(dmx_value_t value) const = 0;
	virtual intensity_t GetClosestWhite(dmx_value_t value) const = 0;

public:
	virtual dmx_value_t GetRed2Dmx(intensity_t red) const = 0;
	virtual dmx_value_t GetGreen2Dmx(intensity_t green) const = 0;
	virtual dmx_value_t GetBlue2Dmx(intensity_t blue) const = 0;
	virtual dmx_value_t GetWhite2Dmx(intensity_t white) const = 0;

private:
	PlatformPar* _platformPar;

	Irgbw _defaultColor;
	Irgbw _alternateColor;
};
