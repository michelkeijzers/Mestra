#include <assert.h>
#include "LedBarSegment.h"
#include "ClassNames.h"
#include HEADER_FILE(DMX_SIMPLE_CLASS)
#include "MathUtils.h"
#include "FixtureData.h"
#include "LightSetup.h"


#define DMX_OFFSET_CHANNEL_MODE      (dmx_channel_t)   0U
#define DMX_OFFSET_CHANNEL_INTENSITY (dmx_channel_t)   1U
#define DMX_OFFSET_CHANNEL_RED       (dmx_channel_t)   2U
#define DMX_OFFSET_CHANNEL_GREEN     (dmx_channel_t)   3U
#define DMX_OFFSET_CHANNEL_BLUE      (dmx_channel_t)   4U

// 41-80 = 11 channel mode, see https://images.thomann.de/pics/prod/255346_manual_en.pdf
#define DMX_MODE_BLACK_OUT       20
#define DMX_MODE_3_SEGMENT_MODE  60
#define DMX_MODE_1_SEGMENT_MODE 100
#define DMX_MODE_COLOR_SHUTTER  140
#define DMX_MODE_COLOR_CHANGE   180
#define DMX_MODE_COLOR_FLOW     220
#define DMX_MODE_DREAM_FLOW     250



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
	return LightSetup.GetFixtureData().ReadUint8(LED_BAR_SEGMENT_DATA_START);
}


void LedBarSegment::SetSegmentNumber(uint8_t segmentNumber)
{
	LightSetup.GetFixtureData().WriteUint8(LED_BAR_SEGMENT_DATA_START, segmentNumber);
}


void LedBarSegment::SetInitialMode()
{
	DmxSimple.write(GetDmxOffsetChannel() + DMX_OFFSET_CHANNEL_MODE, DMX_MODE_3_SEGMENT_MODE);
}


/* override */ void LedBarSegment::GetActualColor(Irgbw& actualColor)
{
	actualColor.SetIntensity(DmxSimple.read(GetIntensityDmxChannel()));
	actualColor.SetRed(DmxSimple.read(GetRedDmxChannel()));
	actualColor.SetGreen(DmxSimple.read(GetGreenDmxChannel()));
	actualColor.SetBlue(DmxSimple.read(GetBlueDmxChannel()));

	// White is calculated.
	actualColor.SetWhite((intensity_t) MathUtils::Min(
		actualColor.GetRed(), actualColor.GetGreen(), actualColor.GetBlue()));
}


/* virtual */ dmx_value_t LedBarSegment::GetRed2Dmx(intensity_t red)
{
	assert(red < PAR_MAX_PAR_INTENSITIES);
	return red * 255U / PAR_MAX_PAR_INTENSITY;
}


/* virtual */ dmx_value_t LedBarSegment::GetGreen2Dmx(intensity_t green)
{
	assert(green < PAR_MAX_PAR_INTENSITIES);
	return green * 255U / PAR_MAX_PAR_INTENSITY;
}


/* virtual */ dmx_value_t LedBarSegment::GetBlue2Dmx(intensity_t blue)
{
	assert(blue < PAR_MAX_PAR_INTENSITIES);
	return blue * 255U / PAR_MAX_PAR_INTENSITY;
}


/* virtual */ dmx_value_t LedBarSegment::GetWhite2Dmx(intensity_t white)
{
	assert(white < PAR_MAX_PAR_INTENSITIES);
	return white * 255U / PAR_MAX_PAR_INTENSITY;
}


void LedBarSegment::WriteIrgb(Irgbw& irgbw)
{
#ifdef COLOR_CHANGE_CHECKING
	GetPlatformPar().CheckColorChanged(*this, dmxOffsetChannel, irgbw);
#endif // COLOR_CHANGE_CHECKING

	DmxSimple.write(GetIntensityDmxChannel(), irgbw.GetIntensity());
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

	DmxSimple.write(GetIntensityDmxChannel(), irgbw.GetIntensity());

	DmxSimple.write(GetRedDmxChannel(), GetRed2Dmx(
		(intensity_t) MathUtils::Max(white, irgbw.GetRed())));

	DmxSimple.write(GetGreenDmxChannel(), GetGreen2Dmx(
		(intensity_t) MathUtils::Max(white, irgbw.GetGreen())));

	DmxSimple.write(GetBlueDmxChannel(), GetBlue2Dmx(
		(intensity_t) MathUtils::Max(white, irgbw.GetBlue())));
}


dmx_channel_t LedBarSegment::GetBaseDmxChannel()
{
	return (int) (GetDmxOffsetChannel() + GetSegmentNumber() * 3U);
}


dmx_channel_t LedBarSegment::GetIntensityDmxChannel()
{
	return GetDmxOffsetChannel() + DMX_OFFSET_CHANNEL_INTENSITY;
}


dmx_channel_t LedBarSegment::GetRedDmxChannel()
{
	return GetBaseDmxChannel() + DMX_OFFSET_CHANNEL_RED;
}


dmx_channel_t LedBarSegment::GetGreenDmxChannel()
{
	return GetBaseDmxChannel() + DMX_OFFSET_CHANNEL_GREEN;
}


dmx_channel_t LedBarSegment::GetBlueDmxChannel()
{
	return GetBaseDmxChannel() + DMX_OFFSET_CHANNEL_BLUE;
}

