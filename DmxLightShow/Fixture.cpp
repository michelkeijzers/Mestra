// Fixture.h
// Generic properties for a fixture.

#include <assert.h>
#include "Fixture.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(SPI_RAM_CLASS)
#include "LightSetup.h"
#include "FixtureData.h"


Fixture::Fixture(fixture_number_t fixture_number)
	: _platformFixture()
{
	LightSetup.SetFixtureNumber(fixture_number);
}



Fixture::~Fixture()
{
}


void Fixture::StroboChanged()
{
}


dmx_channel_t Fixture::GetDmxOffsetChannel()
{
	return (dmx_channel_t) LightSetup.GetFixtureData().ReadUint16(DATA_START_DMX_OFFSET_CHANNEL);
}


void Fixture::SetDmxOffsetChannel(dmx_channel_t dmxOffsetChannel)
{
	LightSetup.GetFixtureData().WriteUint16(DATA_START_DMX_OFFSET_CHANNEL, dmxOffsetChannel);
}


bool Fixture::GetInitialize()
{
  return LightSetup.GetFixtureData().ReadBool(DATA_START_INITIALIZE, DATA_START_INITIALIZE_BIT);
}


void Fixture::SetInitialize(bool initialize)
{
	LightSetup.GetFixtureData().WriteBool(DATA_START_INITIALIZE, DATA_START_INITIALIZE_BIT, initialize);
}


bool Fixture::GetOneShotProgram()
{
	return LightSetup.GetFixtureData().ReadBool(DATA_START_ONE_SHOT_PROGRAM, DATA_START_ONE_SHOT_PROGRAM_BIT);
}


void Fixture::SetOneShotProgram(bool oneShotProgram)
{
	LightSetup.GetFixtureData().WriteBool(DATA_START_ONE_SHOT_PROGRAM, DATA_START_ONE_SHOT_PROGRAM_BIT, oneShotProgram);
}


program_t Fixture::GetProgram()
{
	return (program_t) LightSetup.GetFixtureData().ReadUint8(DATA_START_PROGRAM);
}

void Fixture::SetProgram(program_t program)
{
	LightSetup.GetFixtureData().WriteUint8(DATA_START_PROGRAM, program);
}


step_t Fixture::GetNrOfSteps()
{
	return (step_t) LightSetup.GetFixtureData().ReadUint16(DATA_START_NR_OF_STEPS);
}

void Fixture::SetNrOfSteps(step_t nrOfSteps)
{
	LightSetup.GetFixtureData().WriteUint16(DATA_START_NR_OF_STEPS, nrOfSteps);
}


step_time_t Fixture::GetStepTime()
{
	return (step_time_t) LightSetup.GetFixtureData().ReadUint32(DATA_START_STEP_TIME);
}


void Fixture::SetStepTime(step_time_t stepTime)
{
	LightSetup.GetFixtureData().WriteUint32(DATA_START_STEP_TIME, stepTime);
}


step_duration_t Fixture::GetStepDuration()
{
	return (step_duration_t) LightSetup.GetFixtureData().ReadUint16(DATA_START_STEP_DURATION);
}


void Fixture::SetStepDuration(step_duration_t stepDuration)
{
	LightSetup.GetFixtureData().WriteUint16(DATA_START_STEP_DURATION, stepDuration);
}


step_t Fixture::GetCurrentStep()
{
	return (step_t) LightSetup.GetFixtureData().ReadUint16(DATA_START_CURRENT_STEP);
}

void Fixture::SetCurrentStep(step_t currentStep)
{
	LightSetup.GetFixtureData().WriteUint16(DATA_START_CURRENT_STEP, currentStep);
}


parameter_t Fixture::GetParameter1()
{
	return (parameter_t) LightSetup.GetFixtureData().ReadInt16(DATA_START_PARAMETER_1);
}


void Fixture::SetParameter1(parameter_t parameter1)
{
	LightSetup.GetFixtureData().WriteInt16(DATA_START_PARAMETER_1, parameter1);
}


parameter_t Fixture::GetParameter2()
{
	return (parameter_t) LightSetup.GetFixtureData().ReadInt16(DATA_START_PARAMETER_2);
}


void Fixture::SetParameter2(parameter_t parameter2)
{
	LightSetup.GetFixtureData().WriteInt16(DATA_START_PARAMETER_2, parameter2);
}


parameter_t Fixture::GetParameter3()
{
	return (parameter_t) LightSetup.GetFixtureData().ReadInt16(DATA_START_PARAMETER_3);
}


void Fixture::SetParameter3(parameter_t parameter3)
{
	LightSetup.GetFixtureData().WriteInt16(DATA_START_PARAMETER_3, parameter3);
}


PlatformFixture& Fixture::GetPlatformFixture()
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

	if (GetStepDuration() > 0)
	{
		uint32_t currentMillis = millis();

		if (currentMillis >= GetStepTime())
		{
			SetCurrentStep((step_t) ((GetCurrentStep() + stepsToIncrease) % GetNrOfSteps()));
			SetStepTime(GetStepTime() + GetStepDuration());
			isIncreased = true;
		}

		_platformFixture->PostProcessCheckIncreaseStep(isIncreased);
	}

	return isIncreased;
}

