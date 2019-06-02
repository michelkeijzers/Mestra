// Strobo.h
// Common light setup properties for strobo.
// Strobo is equal for all pars.

#pragma once

#include <stdint.h>
#include "MestraTypes.h"

class Strobo
{
public:
	Strobo();
	
	~Strobo();
 
	void Start(par_bits_t parBits, step_time_t duration);
	
	void Run();
	void RunFixture(fixture_number_t parNumber);

	void AllOff();

	par_bits_t GetParBits();
	void SetParBits(par_bits_t parBits);

	bool GetState();
	void SetState(bool state);

	step_time_t GetDuration();
	void SetDuration(step_time_t duration);

	step_time_t GetNextTime();
	void SetNextTime(step_time_t nextTime);

private:
	par_bits_t _fixtureBits;

	bool _state;

	step_time_t _duration;
	step_time_t _nextTime;
};
