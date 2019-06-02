#include <assert.h>
#include "LedBarSegment.h"
#include "ClassNames.h"
#include HEADER_FILE(DMX_SIMPLE_CLASS)
#include "MathUtils.h"
#include "FixtureData.h"
#include "LightSetup.h"


#define DMX_OFFSET_CHANNEL_RED       (dmx_channel_t)   1U
#define DMX_OFFSET_CHANNEL_GREEN     (dmx_channel_t)   2U
#define DMX_OFFSET_CHANNEL_BLUE      (dmx_channel_t)   3U


LedBarSegment::LedBarSegment(fixture_number_t fixtureNumber)
:
	Par(fixtureNumber)
{
}


LedBarSegment::~LedBarSegment()
{
}


uint8_t LedBarSegment::GetSegmentNumber()
{
	return LightSetup.GetFixtureData().ReadUint8(DATA_START_SEGMENT_NUMBER);
}


void LedBarSegment::SetSegmentNumber(uint8_t segmentNumber)
{
	LightSetup.GetFixtureData().WriteUint8(DATA_START_SEGMENT_NUMBER, segmentNumber);
}


/* override */ void LedBarSegment::GetActualColor(Irgbw& actualColor)
{
	actualColor.SetIntensity(DmxSimple.read(GetBaseDmxChannel()));
	actualColor.SetRed(DmxSimple.read(GetRedDmxChannel()));
	actualColor.SetGreen(DmxSimple.read(GetGreenDmxChannel()));
	actualColor.SetBlue(DmxSimple.read(GetBlueDmxChannel()));

	// White is calculated.
	actualColor.SetWhite((intensity_t) MathUtils::Min(
		actualColor.GetRed(), actualColor.GetGreen(), actualColor.GetBlue()));
}


/* virtual */ dmx_value_t LedBarSegment::GetRed2Dmx(intensity_t red)
{
	assert(red < MAX_PAR_INTENSITIES);
	return red * 255U / MAX_PAR_INTENSITY;
}


/* virtual */ dmx_value_t LedBarSegment::GetGreen2Dmx(intensity_t green)
{
	assert(green < MAX_PAR_INTENSITIES);
	return green * 255U / MAX_PAR_INTENSITY;
}


/* virtual */ dmx_value_t LedBarSegment::GetBlue2Dmx(intensity_t blue)
{
	assert(blue < MAX_PAR_INTENSITIES);
	return blue * 255U / MAX_PAR_INTENSITY;
}


/* virtual */ dmx_value_t LedBarSegment::GetWhite2Dmx(intensity_t white)
{
	assert(white < MAX_PAR_INTENSITIES);
	return white * 255U / MAX_PAR_INTENSITY;
}


void LedBarSegment::WriteIrgb(Irgbw& irgbw)
{
#ifdef COLOR_CHANGE_CHECKING
	GetPlatformPar().CheckColorChanged(*this, dmxOffsetChannel, irgbw);
#endif // COLOR_CHANGE_CHECKING

	DmxSimple.write(GetBaseDmxChannel(), irgbw.GetIntensity());
	DmxSimple.write(GetRedDmxChannel(), GetRed2Dmx(irgbw.GetRed()));
	DmxSimple.write(GetGreenDmxChannel(), GetGreen2Dmx(irgbw.GetGreen()));
	DmxSimple.write(GetBlueDmxChannel(), GetBlue2Dmx(irgbw.GetBlue()));
}


void LedBarSegment::WriteIrgbw(Irgbw& irgbw)
{
#ifdef COLOR_CHANGE_CHECKING
	GetPlatformPar().CheckColorChanged(*this, dmxOffsetChannel, irgbw);
#endif // COLOR_CHANGE_CHECKING

	intensity_t white = irgbw.GetWhite();

	DmxSimple.write(GetBaseDmxChannel(), irgbw.GetIntensity());

	DmxSimple.write(GetRedDmxChannel(), GetRed2Dmx(
		(intensity_t) MathUtils::Max(white, irgbw.GetRed())));

	DmxSimple.write(GetGreenDmxChannel(), GetGreen2Dmx(
		(intensity_t) MathUtils::Max(white, irgbw.GetGreen())));

	DmxSimple.write(GetBlueDmxChannel(), GetBlue2Dmx(
		(intensity_t) MathUtils::Max(white, irgbw.GetBlue())));
}


int LedBarSegment::GetBaseDmxChannel()
{
	return (int) (GetDmxOffsetChannel() + GetSegmentNumber() * 3U);
}


int LedBarSegment::GetRedDmxChannel()
{
	return GetBaseDmxChannel() + DMX_OFFSET_CHANNEL_RED;
}


int LedBarSegment::GetGreenDmxChannel()
{
	return GetBaseDmxChannel() + DMX_OFFSET_CHANNEL_GREEN;
}


int LedBarSegment::GetBlueDmxChannel()
{
	return GetBaseDmxChannel() + DMX_OFFSET_CHANNEL_BLUE;
}

