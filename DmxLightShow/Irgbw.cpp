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
	assert(red   <= MAX_PAR_INTENSITY);
	assert(green <= MAX_PAR_INTENSITY);
	assert(blue  <= MAX_PAR_INTENSITY);

	SetIntensity(intensity);
	SetRed(red);
	SetGreen(green);
	SetBlue(blue);
}


void Irgbw::SetIrgbw(intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue, 
 intensity_t white)
{
	assert(white <= MAX_PAR_INTENSITY);

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