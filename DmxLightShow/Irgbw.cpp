// Irgbw.cpp
// Intensity, red/green/blue/white for Pars.

#include "Irgbw.h"
#include "Par.h"
#include <assert.h>


Irgbw::Irgbw()
	: Irgbw(0, 0, 0, 0, 0)
{
}


Irgbw::Irgbw(intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue)
: Irgbw(intensity, red, green, blue, 0)
{
}


Irgbw::Irgbw(intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue, 
 intensity_t white)
	: _intensity(intensity),
	_red(red),
	_green(green),
	_blue(blue),
	_white(white)
{
	SetIrgb(intensity, red, green, blue);
	SetWhite(white);
}


Irgbw::~Irgbw()
{
}


intensity_t Irgbw::GetIntensity()
{
	return _intensity;
}


void Irgbw::SetIntensity(intensity_t intensity)
{
	_intensity = intensity;
}


intensity_t Irgbw::GetRed()
{
	return _red;
}


void Irgbw::SetRed(intensity_t red)
{
	_red = red;
}


intensity_t Irgbw::GetGreen()
{
	return _green;
}


void Irgbw::SetGreen(intensity_t green)
{
	_green = green;
}


intensity_t Irgbw::GetBlue()
{
	return _blue;
}

void Irgbw::SetBlue(intensity_t blue)
{
	_blue = blue;
}


intensity_t Irgbw::GetWhite()
{
	return _white;
}


void Irgbw::SetWhite(intensity_t white)
{
	_white = white;
}


void Irgbw::SetIrgb(Irgbw& irgbw)
{
	SetIrgb(irgbw.GetIntensity(), irgbw.GetRed(), irgbw.GetGreen(), irgbw.GetBlue());
}


void Irgbw::SetIrgbw(Irgbw& irgbw)
{
	SetIrgbw(irgbw.GetIntensity(), irgbw.GetRed(), irgbw.GetGreen(), irgbw.GetBlue(), 
	 irgbw.GetWhite());
}


void Irgbw::SetIrgb(intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue)
{
	assert(red   <= PAR_MAX_PAR_INTENSITY);
	assert(green <= PAR_MAX_PAR_INTENSITY);
	assert(blue  <= PAR_MAX_PAR_INTENSITY);

	SetIntensity(intensity);
	SetRed(red);
	SetGreen(green);
	SetBlue(blue);
}


void Irgbw::SetIrgbw(intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue, 
 intensity_t white)
{
	assert(white <= PAR_MAX_PAR_INTENSITY);

	SetIrgb(intensity, red, green, blue);
	SetWhite(white);
}


void Irgbw::operator=(Irgbw& irgbw)
{
	_intensity = irgbw._intensity;
	_red = irgbw._red;
	_green = irgbw._green;
	_blue = irgbw._blue;
	_white = irgbw._white;
}