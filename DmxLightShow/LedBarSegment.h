#pragma once

#include "Par.h"


class LedBarSegment :
	public Par
{
public:
	LedBarSegment(fixture_number_t fixtureNumber);
	~LedBarSegment();

	void SetSegmentNumber(led_bar_segment_number_t segmentNumber);

	void SetInitialMode() const;

private:
	void GetActualColor(Irgbw& actualColor) const override;

	intensity_t GetClosestRed(dmx_value_t value) const override;
	intensity_t GetClosestGreen(dmx_value_t value) const override;
	intensity_t GetClosestBlue(dmx_value_t value) const override;
	intensity_t GetClosestWhite(dmx_value_t value) const override;

	dmx_value_t GetRed2Dmx(intensity_t red) const override;
	dmx_value_t GetGreen2Dmx(intensity_t green) const override;
	dmx_value_t GetBlue2Dmx(intensity_t blue) const override;
	dmx_value_t GetWhite2Dmx(intensity_t white) const override;

	void WriteIrgb(Irgbw& irgbw) override;
	void WriteIrgbw(Irgbw& irgbw) override;

	led_bar_segment_number_t GetSegmentNumber() const;

	dmx_channel_t GetBaseDmxChannel() const;
	dmx_channel_t GetIntensityDmxChannel() const;
	dmx_channel_t GetRedDmxChannel() const;
	dmx_channel_t GetGreenDmxChannel() const;
	dmx_channel_t GetBlueDmxChannel() const;

	led_bar_segment_number_t _segmentNumber;
};

