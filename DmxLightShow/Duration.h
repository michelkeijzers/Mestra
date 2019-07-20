#pragma once


# include "MestraTypes.h"


class Duration
{
private:
	Duration();
	~Duration();
	
public:
	static step_duration_t ToStepDuration(step_time_t stepTime);
	static step_time_t     ToStepTime(step_duration_t duration);
};

