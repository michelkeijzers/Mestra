#include "LedBarSegment.h"
#include "ClassNames.h"
#include HEADER_FILE(DMX_SIMPLE_CLASS)
#include "MathUtils.h"

#define DMX_OFFSET_CHANNEL_RED       (dmx_channel_t)   0
#define DMX_OFFSET_CHANNEL_GREEN     (dmx_channel_t)   1
#define DMX_OFFSET_CHANNEL_BLUE      (dmx_channel_t)   2

void LedBarSegment::SetSegmentNumber(uint8_t segmentNumber)
{
	_segmentNumber = segmentNumber;
	_intensityDmxOffsetChannel = - 3 * segmentNumber - 1; // Intensity channel (shutter) is directly before segment 0
}


/* override */ void LedBarSegment::GetActualColor(Irgbw& actualColor)
{
	dmx_channel_t dmxOffsetChannel = GetDmxOffsetChannel();
	actualColor.SetIntensity(DmxSimple.read(dmxOffsetChannel + _intensityDmxOffsetChannel));
	actualColor.SetRed(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_RED));
	actualColor.SetGreen(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_GREEN));
	actualColor.SetBlue(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_BLUE));

	// White is calculated.
	actualColor.SetWhite((intensity_t) MathUtils::Min(actualColor.GetRed(), actualColor.GetGreen(), actualColor.GetBlue()));
}


/* virtual */ dmx_value_t LedBarSegment::GetWhite2Dmx(intensity_t white)
{
	return GetPlatformPar().GetWhite2GammaCorrectedDmx(white);
}


void LedBarSegment::WriteIrgb(Irgbw& irgbw)
{
#ifdef COLOR_CHANGE_CHECKING
	GetPlatformPar().CheckColorChanged(*this, dmxOffsetChannel, irgbw);
#endif // COLOR_CHANGE_CHECKING

	dmx_channel_t dmxOffsetChannel = GetDmxOffsetChannel();

	DmxSimple.write(dmxOffsetChannel + _intensityDmxOffsetChannel, irgbw.GetIntensity());
	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_RED, GetRed2Dmx(irgbw.GetRed()));
	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_GREEN, GetGreen2Dmx(irgbw.GetGreen()));
	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_BLUE, GetBlue2Dmx(irgbw.GetBlue()));
}


void LedBarSegment::WriteIrgbw(Irgbw& irgbw)
{
#ifdef COLOR_CHANGE_CHECKING
	GetPlatformPar().CheckColorChanged(*this, dmxOffsetChannel, irgbw);
#endif // COLOR_CHANGE_CHECKING

	dmx_channel_t dmxOffsetChannel = GetDmxOffsetChannel();
	intensity_t white = irgbw.GetWhite();

	DmxSimple.write(dmxOffsetChannel + _intensityDmxOffsetChannel, irgbw.GetIntensity());

	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_RED, GetRed2Dmx(
		(intensity_t) MathUtils::Max(white, irgbw.GetRed())));

	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_GREEN, GetGreen2Dmx(
		(intensity_t) MathUtils::Max(white, irgbw.GetGreen())));

	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_BLUE, GetBlue2Dmx(
		(intensity_t) MathUtils::Max(white, irgbw.GetBlue())));
}


