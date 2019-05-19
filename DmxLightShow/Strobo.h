// Strobo.h
// Common light setup properties for strobo.
// Strobo is equal for all pars.

#pragma once


#include <stdint.h>
#include "MestraTypes.h"


class Strobo
{
private:
	par_bits_t _parBits;

	bool _state;

	step_time_t _duration;

	step_time_t _nextTime;


public:
	Strobo();
	
	~Strobo();
  

	void Start(par_bits_t parBits, step_time_t duration);


	void Run();


	par_bits_t GetParBits()
	{
		return _parBits;
	}
	
	void SetParBits(par_bits_t parBits)
	{
		_parBits = parBits;
	}


	bool GetState()
	{
		return _state;
	}

	void SetState(bool state)
	{
		_state = state;
	}


	step_time_t GetDuration()
	{
		return _duration;
	}

	void SetDuration(step_time_t duration)
	{
		_duration = duration;
	}


	step_time_t GetNextTime()
	{
		return _nextTime;
	}

	void SetNextTime(step_time_t nextTime)
	{
		_duration = nextTime;
	}
};
