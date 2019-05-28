#include "assert.h"
#include "ChinesePar.h"
#include "Irgbw.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(DMX_SIMPLE_CLASS)

#define DMX_OFFSET_CHANNEL_INTENSITY (dmx_channel_t)   0
#define DMX_OFFSET_CHANNEL_RED       (dmx_channel_t)   1
#define DMX_OFFSET_CHANNEL_GREEN     (dmx_channel_t)   2
#define DMX_OFFSET_CHANNEL_BLUE      (dmx_channel_t)   3
#define DMX_OFFSET_CHANNEL_WHITE     (dmx_channel_t)   4


// MAX_PAR_INTENSITIES:                                              0  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47   48
static const dmx_value_t _red2Dmx[MAX_PAR_INTENSITIES] PROGMEM = { 0, 9, 10, 12, 13, 15, 17, 18, 20, 21, 23, 25, 26, 27, 28, 29, 30, 31, 32, 34, 36, 38, 40, 44, 48, 52, 56, 58, 62, 69, 75, 82, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 255 };
static const dmx_value_t _green2Dmx[MAX_PAR_INTENSITIES] PROGMEM = { 0, 1,  1,  1,  1,  2,  2,  3,  3,  4,  5,  6,  6,  7,  7,  7,  8,  9, 10, 10, 10, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15, 16, 17,  20,  25,  30,  35,  40,  50,  60,  80, 100, 120, 140, 160, 180, 200, 220, 255 };
static const dmx_value_t _blue2Dmx[MAX_PAR_INTENSITIES] PROGMEM = { 0, 1,  1,  2,  2,  3,  3,  4,  4,  5,  5,  6,  7,  7,  8,  9, 10, 11, 12, 13, 14, 16, 18, 20, 22, 24, 28, 32, 36, 40, 44, 50, 60,  70,  80,  90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 220, 240, 255 };
static const dmx_value_t _white2Dmx[MAX_PAR_INTENSITIES] PROGMEM = { 0, 2,  2,  2,  3,  3,  3,  3,  4,  4,  4,  5,  5,  6,  6,  7,  8,  9, 10, 10, 10, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15, 16, 17,  20,  25,  30,  35,  40,  50,  60,  80, 100, 120, 140, 160, 180, 200, 220, 255 };



/* override */ void ChinesePar::GetActualColor(Irgbw &actualColor)
{
	dmx_channel_t dmxOffsetChannel = GetDmxOffsetChannel();
	actualColor.SetIntensity(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_INTENSITY));
	actualColor.SetRed(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_RED));
	actualColor.SetGreen(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_GREEN));
	actualColor.SetBlue(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_BLUE));
	actualColor.SetWhite(DmxSimple.read(dmxOffsetChannel + DMX_OFFSET_CHANNEL_WHITE));
}


/* virtual */ dmx_value_t ChinesePar::GetRed2Dmx(intensity_t red)
{
	assert(red < MAX_PAR_INTENSITIES);
	return GetPlatformPar().GetRed2GammaCorrectedDmx(_red2Dmx[red]);
}


/* virtual */ dmx_value_t ChinesePar::GetGreen2Dmx(intensity_t green)
{
	assert(green < MAX_PAR_INTENSITIES);
	return GetPlatformPar().GetGreen2GammaCorrectedDmx(_green2Dmx[green]);
}


/* virtual */ dmx_value_t ChinesePar::GetBlue2Dmx(intensity_t blue)
{
	return GetPlatformPar().GetBlue2GammaCorrectedDmx(_blue2Dmx[blue]);
}


/* virtual */ dmx_value_t ChinesePar::GetWhite2Dmx(intensity_t white)
{
	return GetPlatformPar().GetWhite2GammaCorrectedDmx(_white2Dmx[white]);
}


void ChinesePar::WriteIrgb(Irgbw& irgbw)
{
#ifdef COLOR_CHANGE_CHECKING
	GetPlatformPar().CheckColorChanged(*this, dmxOffsetChannel, irgbw);
#endif // COLOR_CHANGE_CHECKING

	dmx_channel_t dmxOffsetChannel = GetDmxOffsetChannel();

	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_INTENSITY, irgbw.GetIntensity());
	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_RED, GetRed2Dmx(irgbw.GetRed()));
	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_GREEN, GetGreen2Dmx(irgbw.GetGreen()));
	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_BLUE, GetBlue2Dmx(irgbw.GetBlue()));
}


void ChinesePar::WriteIrgbw(Irgbw& irgbw)
{
#ifdef COLOR_CHANGE_CHECKING
	GetPlatformPar().CheckColorChanged(*this, dmxOffsetChannel, irgbw);
#endif // COLOR_CHANGE_CHECKING

	dmx_channel_t dmxOffsetChannel = GetDmxOffsetChannel();

	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_INTENSITY, irgbw.GetIntensity());
	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_RED, GetRed2Dmx(irgbw.GetRed()));
	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_GREEN, GetGreen2Dmx(irgbw.GetGreen()));
	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_BLUE, GetBlue2Dmx(irgbw.GetBlue()));
	DmxSimple.write(dmxOffsetChannel + DMX_OFFSET_CHANNEL_WHITE, GetWhite2Dmx(irgbw.GetWhite()));
}


