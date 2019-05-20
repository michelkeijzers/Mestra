// Irgbw.h
// Intensity, red/green/blue/white for Pars.

#pragma once

#include <stdint.h>
#include "MestraTypes.h"

class Irgbw
{
public:
	Irgbw();

	Irgbw(intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue, 
	 intensity_t white);

	Irgbw(intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue);

	~Irgbw();

	void SetIrgb(intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue);
	void SetIrgbw(intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue, 
	 intensity_t white);
	void SetIrgb(Irgbw& irgbw);
	void SetIrgbw(Irgbw& irgbw);

	void operator=(Irgbw& irgbw);

	intensity_t GetIntensity();
	void SetIntensity(intensity_t intensity);

	intensity_t GetRed();
	void SetRed(intensity_t red);

	intensity_t GetGreen();
	void SetGreen(intensity_t green);

	intensity_t GetBlue();
	void SetBlue(intensity_t blue);

	intensity_t GetWhite();
	void SetWhite(intensity_t white);

private:
	intensity_t _intensity;
	intensity_t _red;
	intensity_t _green;
	intensity_t _blue;
	intensity_t _white;
};
