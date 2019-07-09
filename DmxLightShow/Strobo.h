// Strobo.h
// Common light setup properties for strobo.
// Strobo is equal for all pars.

#pragma once

#include "MestraTypes.h"

class Strobo
{
public:
	Strobo();
	
	~Strobo();
 
	void Start(par_bits_t parBits, step_time_t duration);
	
	void Run();
	void RunFixture(fixture_number_t parNumber) const;

	par_bits_t GetParBits() const;
	void SetParBits(par_bits_t parBits);

	bool GetState() const;
	void SetState(bool state);

	step_time_t GetDuration() const;
	void SetDuration(step_time_t duration);

	step_time_t GetNextTime() const;
	void SetNextTime(step_time_t nextTime);

private:
	par_bits_t _fixtureBits;

	bool _state;

	step_time_t _duration;
	step_time_t _nextTime;
};
