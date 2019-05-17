// Irgbw.h
// Intensity, red/green/blue/white for Pars.

#pragma once


#include <stdint.h>


class Irgbw
{
public:

	Irgbw();

	Irgbw(uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

	Irgbw(uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue);

	~Irgbw();

	void SetIrgb(uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue);

	void SetIrgbw(uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
	
	void SetIrgb(Irgbw& irgbw);

	void SetIrgbw(Irgbw& irgbw);

	uint8_t GetIntensity() { return _intensity; }
	void SetIntensity(uint8_t intensity) { _intensity = intensity; }

	uint8_t GetRed() { return _red; }
	void SetRed(uint8_t red) { _red = red; }

	uint8_t GetGreen() { return _green; }
	void SetGreen(uint8_t green) { _green = green; }

	uint8_t GetBlue() { return _blue; }
	void SetBlue(uint8_t blue) { _blue = blue; }

	uint8_t GetWhite() { return _white; }
	void SetWhite(uint8_t white) { _white = white; }

	void operator=(Irgbw& irgbw);

private:
  uint8_t _intensity;

  uint8_t _red;

  uint8_t _green;

  uint8_t _blue;

  uint8_t _white;
};
