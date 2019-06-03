// Strobo.h
// Common light setup properties for strobo.
// Strobo is equal for all pars.

#include "Strobo.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "Par.h"
#include "LightSetup.h"


Strobo::Strobo() :
	_fixtureBits(0),
	_state(false),
	_duration(0),
	_nextTime(0)
{
}


Strobo::~Strobo()
{
}


par_bits_t Strobo::GetParBits()
{
	return _fixtureBits;
}


void Strobo::SetParBits(par_bits_t parBits)
{
	_fixtureBits = parBits;
}


bool Strobo::GetState()
{
	return _state;
}


void Strobo::SetState(bool state)
{
	_state = state;
}


step_time_t Strobo::GetDuration()
{
	return _duration;
}


void Strobo::SetDuration(step_time_t duration)
{
	_duration = duration;
}


step_time_t Strobo::GetNextTime()
{
	return _nextTime;
}


void Strobo::SetNextTime(step_time_t nextTime)
{
	_duration = nextTime;
}


void Strobo::Start(par_bits_t parBits, step_time_t duration)
{
	// Stop all current strobo (white).
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		if ((_fixtureBits & (1 << parNumber)) > 0)
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
	_fixtureBits = parBits;
	_state = true;
	_duration = duration;
	_nextTime = millis() + _duration; // Execute next time

	// Initialize generic parbits intensity.
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		if ((_fixtureBits & (1 << parNumber)) > 0)
		{
			Par& par = LightSetup.GetPar(parNumber);

			Irgbw irgbw;
			par.GetActualColor(irgbw);
			irgbw.SetIntensity(PAR_MAX_INTENSITY);
			irgbw.SetWhite(PAR_MAX_PAR_INTENSITY);
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
		_nextTime = millis() + _duration;
	}
}


void Strobo::RunFixture(fixture_number_t fixtureNumber)
{
	if ((_fixtureBits & (1U << fixtureNumber)) > 0U)
	{
		Par& par = LightSetup.GetPar(fixtureNumber);
		Irgbw irgbw;

		par.GetActualColor(irgbw);
		irgbw.SetIntensity(_state ? PAR_MAX_INTENSITY : 0U);
		irgbw.SetWhite(_state ? PAR_MAX_PAR_INTENSITY : 0U);
		par.WriteIrgbw(irgbw);

		par.StroboChanged();
	}
}


void Strobo::AllOff()
{
	for (fixture_number_t parNumber = 0U; parNumber < NR_OF_PARS; parNumber++)
	{
		Irgbw irgbw;
		Par& par = LightSetup.GetPar(parNumber);

		par.GetActualColor(irgbw);
		irgbw.SetWhite(0);
		par.WriteIrgbw(irgbw);
		par.StroboChanged();
	}
}
