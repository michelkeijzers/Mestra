// Fixture.h
// Generic properties for a fixture.

#include <assert.h>
#include "Fixture.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "MathUtils.h"


Fixture::Fixture(fixture_number_t fixtureNumber)
	: 
	_platformFixture(), 
	_initialize(false), 
	_forceUpdate(false),
	_dmxOffsetChannel(0), 
	_triggerState(Off), 
	_program(0), 
	_nrOfSteps(0), 
	_stepTime(0),
	_stepDuration(0),
	_currentStep(0),
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


Fixture::ETriggerState Fixture::GetTriggerState() const
{
	return _triggerState;;
}


void Fixture::SetTriggerState(ETriggerState triggerState)
{
	_triggerState = triggerState;

	switch (_triggerState)
	{
	case Off:
		SetCurrentStep(0);
		SetStepTime(millis() + GetStepDuration());
		_forceUpdate = true;
		break;

	case Active:
		SetCurrentStep(0);
		SetStepTime(millis() + GetStepDuration());
		_forceUpdate = true;
		break;

	case Waiting:
		SetCurrentStep(MathUtils::Max(0, GetNrOfSteps() - 1));
		_forceUpdate = true;
		break;

	default:
		assert(false);
	}
}


void Fixture::ActivateTrigger()
{
	switch (GetTriggerState())
	{
	case Off:
		// Ignore
		break;

	case Active:
		// Reactivate
		SetCurrentStep(0);
		SetStepTime(millis() + GetStepDuration());
		_forceUpdate = true;
		break;

	case Waiting:
		SetTriggerState(Active);
		SetCurrentStep(0);
		SetStepTime(millis() + GetStepDuration());
		_forceUpdate = true;
		break;

	default:
		assert(false);
	}
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


step_t Fixture::GetCurrentStep() const
{
	return _currentStep;
}

void Fixture::SetCurrentStep(step_t currentStep)
{
	_currentStep = currentStep;
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
	assert(startStep < nrOfSteps);

	SetInitialize(true);
	SetProgram(programNumber);
	SetNrOfSteps(nrOfSteps);
	SetCurrentStep(startStep);
    SetParameter1(parameter1);
	SetParameter2(parameter2);
	SetParameter3(parameter3);
}


bool Fixture::CheckIncreaseStep(step_t stepsToIncrease /* = 1 */)
{
	bool isIncreased = false;

	switch (GetTriggerState())
	{
	case Off:
		{
			uint32_t currentMillis = millis();

			if (GetStepDuration() > 0)
			{
				if (currentMillis >= GetStepTime())
				{
					SetCurrentStep(step_t((GetCurrentStep() + stepsToIncrease) % GetNrOfSteps()));
					SetStepTime(currentMillis + GetStepDuration());
					isIncreased = true;
				}
			}
			break;
		}

	case Waiting:
		// Do nothing
		break;

	case Active:
		{
			uint32_t currentMillis = millis();

			if (GetStepDuration() > 0)
			{
				if (currentMillis >= GetStepTime())
				{
					step_t nextStep = GetCurrentStep() + stepsToIncrease;
					
					if (nextStep >= GetNrOfSteps())
					{
						SetTriggerState(Waiting); // Keep current step to last step too
						SetCurrentStep(MathUtils::Max(0, GetNrOfSteps() - 1));
					}
					else
					{
						SetCurrentStep(step_t((GetCurrentStep() + stepsToIncrease) % GetNrOfSteps()));
					}

					SetStepTime(currentMillis + GetStepDuration());
					isIncreased = true;
				}
			}
			break;
		}

	default:
		assert(false);
	}

	if (_forceUpdate)
	{
		isIncreased = true;
		_forceUpdate = false;
	}

	_platformFixture->PostProcessCheckIncreaseStep(isIncreased);

	return isIncreased;
}

