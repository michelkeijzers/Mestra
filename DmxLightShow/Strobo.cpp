// Strobo.h
// Common light setup properties for strobo.
// Strobo is equal for all pars.

#include "Strobo.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "Par.h"
#include HEADER_FILE(LIGHT_SETUP_CLASS)


Strobo::Strobo() :
	_parBits(0),
	_state(false),
	_duration(0),
	_nextTime(0)
{
}


Strobo::~Strobo()
{
}


void Strobo::Start(par_bits_t parBits, step_time_t duration)
{
	// Stop all current strobo (white).
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		if ((_parBits & (0x8000 >> parNumber)) > 0)
		{
			Par& par = LightSetup.GetPar(parNumber);
			Irgbw irgbw;
			par.GetActualColor(irgbw);
			// Intensity cannot be restored.
			irgbw.SetWhite(0);
			par.WriteIrgbw(irgbw);
		}
	}

	// Set properties
	_parBits = parBits;
	_state = true;
	_duration = duration;
	_nextTime = millis() + _duration; // Execute next time

	// Initialize generic parbits intensity.
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		if ((_parBits & (0x8000 >> parNumber)) > 0)
		{
			Par& par = LightSetup.GetPar(parNumber);
			Irgbw irgbw;
			par.GetActualColor(irgbw);
			irgbw.SetIntensity(MAX_INTENSITY);
			irgbw.SetWhite(MAX_PAR_INTENSITY);
			par.WriteIrgbw(irgbw);
		}
	}
}


void Strobo::Run()
{
	// Stop all current strobo (white).
	if (millis() > _nextTime)
	{
		_state = !_state;

		for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
		{
			if ((_parBits & (0x8000 >> parNumber)) > 0)
			{
				Par& par = LightSetup.GetPar(parNumber);
				Irgbw irgbw;

				par.GetActualColor(irgbw);
				irgbw.SetIntensity(_state ? MAX_INTENSITY     : 0);
				irgbw.SetWhite    (_state ? MAX_PAR_INTENSITY : 0);
				par.WriteIrgbw(irgbw);

				par.StroboChanged();
			}
		}

		_nextTime = millis() + _duration;
	}
}