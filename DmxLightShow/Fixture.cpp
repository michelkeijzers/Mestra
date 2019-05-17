// Fixture.h
// Generic properties for a fixture.


#include <assert.h>
#include "Fixture.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

Fixture::Fixture()
:
	_dmxOffsetChannel(0),
	_initialize(true),
	_program(0),
	_currentStep(0),
	_nrOfSteps(1),
	_stepTime(0),
	_stepDuration(UINT16_MAX),  // Do not use 32 bit max here
	_parameter1(0),
	_parameter2(0)
{
}


Fixture::~Fixture()
{
}


void Fixture::InitializeProgram(uint16_t programNumber, uint16_t nrOfSteps, uint16_t startStep, 
	uint16_t parameter1 /* = 0 */, uint16_t parameter2 /* = 0 */)
{
	assert(startStep < nrOfSteps);

	SetInitialize(true);
	SetProgram(programNumber);
	SetNrOfSteps(nrOfSteps);
	SetCurrentStep(startStep);
  SetParameter1(parameter1);
	SetParameter2(parameter2);
}


bool Fixture::CheckIncreaseStep()
{
	bool isIncreased = false;
	uint32_t currentMillis = millis();

	if (currentMillis >= GetStepTime())
	{
		SetCurrentStep((GetCurrentStep() + 1) % GetNrOfSteps());
		SetStepTime(GetStepTime() + GetStepDuration());
		isIncreased = true;
	}

	return isIncreased;
}