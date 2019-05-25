// Fixture.h
// Generic properties for a fixture.

#include <assert.h>
#include "Fixture.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


Fixture::Fixture()
:
	_platformFixture(0),
	_dmxOffsetChannel(0),
	_initialize(true),
	_program(0),
	_currentStep(0),
	_nrOfSteps(1),
	_stepTime(0),
	_stepDuration(UINT16_MAX),  // Do not use 32 bit max here
	_parameter1(0),
	_parameter2(0),
	_parameter3(0)
{
}


Fixture::~Fixture()
{
}


void Fixture::StroboChanged()
{
}


void Fixture::SetDmxOffsetChannel(dmx_channel_t dmxOffsetChannel)
{
	_dmxOffsetChannel = dmxOffsetChannel;
}


bool Fixture::GetInitialize()
{
	return _initialize;
}


void Fixture::SetInitialize(bool initialize)
{
	_initialize = initialize;
}


program_t Fixture::GetProgram()
{
	return _program;
}

void Fixture::SetProgram(program_t program)
{
	_program = program;
}


step_t Fixture::GetNrOfSteps()
{
	return _nrOfSteps;
}

void Fixture::SetNrOfSteps(step_t nrOfSteps)
{
	_nrOfSteps = nrOfSteps;
}


step_time_t Fixture::GetStepTime()
{
	return _stepTime;
}


void Fixture::SetStepTime(step_time_t stepTime)
{
	_stepTime = stepTime;
}


step_time_t Fixture::GetStepDuration()
{
	return _stepDuration;
}

void Fixture::SetStepDuration(step_time_t stepDuration)
{
	_stepDuration = stepDuration;
}


step_t Fixture::GetCurrentStep()
{
	return _currentStep;
}

void Fixture::SetCurrentStep(step_t currentStep)
{
	_currentStep = currentStep;
}


parameter_t Fixture::GetParameter1()
{
	return _parameter1;
}


void Fixture::SetParameter1(parameter_t parameter1)
{
	_parameter1 = parameter1;
}


parameter_t Fixture::GetParameter2()
{
	return _parameter2;
}


void Fixture::SetParameter2(parameter_t parameter2)
{
	_parameter2 = parameter2;
}


parameter_t Fixture::GetParameter3()
{
	return _parameter3;
}


void Fixture::SetParameter3(parameter_t parameter3)
{
	_parameter3 = parameter3;
}


PlatformFixture& Fixture::GetPlatformFixture()
{
	return *_platformFixture;
}


void Fixture::SetPlatformFixture(PlatformFixture* platformFixture)
{
	_platformFixture = platformFixture;
}


dmx_channel_t Fixture::GetDmxOffsetChannel()
{
	return _dmxOffsetChannel;
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
	uint32_t currentMillis = millis();

	if (currentMillis >= GetStepTime())
	{
		SetCurrentStep((GetCurrentStep() + stepsToIncrease) % GetNrOfSteps());
		SetStepTime(GetStepTime() + GetStepDuration());
		isIncreased = true;
	}

	_platformFixture->PostProcessCheckIncreaseStep(isIncreased);

	return isIncreased;
}
