// Fixture.h
// Generic properties for a fixture.

#include "AssertUtils.h"
#include "Fixture.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "MathUtils.h"

#include "Duration.h"


Fixture::Fixture(fixture_number_t fixtureNumber)
	: 
	_platformFixture(), 
	_initialize(false), 
	_forceUpdate(false),
	_dmxOffsetChannel(0), 
	_program(0), 
	_nrOfSteps(0), 
	_stepTime(0),
	_stepDuration(0),
	_stepNumber(0),
	_hold(false),
	_once(false),
	_parameter1(0),
	_parameter2(0),
	_parameter3(0)
{
	_fixtureNumber = fixtureNumber;
}



Fixture::~Fixture()
{
}


void Fixture::StroboChanged()
{
}


fixture_number_t Fixture::GetFixtureNumber() const
{
	return _fixtureNumber;
}


dmx_channel_t Fixture::GetDmxOffsetChannel() const
{
	return _dmxOffsetChannel;
}


void Fixture::SetDmxOffsetChannel(dmx_channel_t dmxOffsetChannel)
{
	_dmxOffsetChannel = dmxOffsetChannel;
}


bool Fixture::GetInitialize() const
{
	return _initialize;
}


void Fixture::SetInitialize(bool initialize)
{
	_initialize = initialize;
}


program_t Fixture::GetProgram() const
{
	return _program;
}

void Fixture::SetProgram(program_t program)
{
	_program = program;
}


step_t Fixture::GetNrOfSteps() const
{
	return _nrOfSteps;
}

void Fixture::SetNrOfSteps(step_t nrOfSteps)
{
	_nrOfSteps = nrOfSteps;
}


step_time_t Fixture::GetStepTime() const
{
	return _stepTime;
}


void Fixture::SetStepTime(step_time_t stepTime)
{
	_stepTime = stepTime;
}


step_duration_t Fixture::GetStepDuration() const
{
	return _stepDuration;
}


void Fixture::SetStepDuration(step_duration_t stepDuration)
{
	_stepDuration = stepDuration;
}


step_t Fixture::GetStepNumber() const
{
	return _stepNumber;
}


void Fixture::SetStepNumber(step_t stepNumber)
{
	if (stepNumber != _stepNumber)
	{
		_stepNumber = stepNumber;
		_forceUpdate = true;
	}
}


bool Fixture::GetHold() const
{
	return _hold;
}


void Fixture::SetHold(bool hold)
{
	if (!_hold && hold)
	{
		_forceUpdate = true;
	}
	
	_hold = hold;
}


bool Fixture::GetOnce() const
{
	return _once;
}


void Fixture::SetOnce(bool once)
{
	_once = once;
}


parameter_t Fixture::GetParameter1() const
{
	return _parameter1;
}


void Fixture::SetParameter1(parameter_t parameter1)
{
	_parameter1 = parameter1;
}


parameter_t Fixture::GetParameter2() const
{
	return _parameter2;
}


void Fixture::SetParameter2(parameter_t parameter2)
{
	_parameter2 = parameter2;
}


parameter_t Fixture::GetParameter3() const
{
	return _parameter3;
}


void Fixture::SetParameter3(parameter_t parameter3)
{
	_parameter3 = parameter3;
}


bool Fixture::GetForceUpdate() const
{
	return _forceUpdate;
}


PlatformFixture& Fixture::GetPlatformFixture() const
{
	return *_platformFixture;
}


void Fixture::SetPlatformFixture(PlatformFixture* platformFixture)
{
	_platformFixture = platformFixture;
}


void Fixture::InitializeProgram(program_t programNumber, step_t nrOfSteps, step_t startStep, 
	parameter_t parameter1 /* = 0 */, parameter_t parameter2 /* = 0 */, parameter_t parameter3 /* = 0 */ )
{
	AssertUtils::MyAssert(startStep < nrOfSteps);

	SetInitialize(true);
	SetProgram(programNumber);
	SetNrOfSteps(nrOfSteps);
	SetStepNumber(startStep);
    SetParameter1(parameter1);
	SetParameter2(parameter2);
	SetParameter3(parameter3);
}


bool Fixture::CheckIncreaseStep(step_t stepsToIncrease /* = 1 */)
{
	bool isIncreased = false;
	uint32_t currentMillis = millis();

	if (_hold)
	{
		// Do nothing
	}
	else
	{
		if (Duration::ToStepTime(GetStepDuration()) > 0 && currentMillis >= GetStepTime())
		{
			if (GetStepNumber() + stepsToIncrease < 0 ||
			    GetStepNumber() + stepsToIncrease >= GetNrOfSteps())
			{
				if (!_once)
				{
					isIncreased = true;
					SetStepNumber(step_t((GetStepNumber() + stepsToIncrease) % GetNrOfSteps()));
				}
			}
			else
			{
				isIncreased = true;
				SetStepNumber(step_t(GetStepNumber() + stepsToIncrease));
			}
		}
	}

	if (_forceUpdate)
	{
		isIncreased = true;
		_forceUpdate = false;
	}

	if (isIncreased)
	{
		SetStepTime(currentMillis + Duration::ToStepTime(GetStepDuration()));
	}

	_platformFixture->PostProcessCheckIncreaseStep(isIncreased);

	return isIncreased;
}

