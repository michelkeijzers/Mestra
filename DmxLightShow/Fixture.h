// Fixture.h
// Generic properties for a fixture.

#pragma once

#include <stdint.h>
#include "MestraTypes.h"
#include "PlatformFixture.h"
#include "Irgbw.h"


/* abstract */ class Fixture
{
public:
	Fixture(fixture_number_t fixture_number);

	~Fixture();

	void InitializeProgram(program_t programNumber, step_t nrOfSteps, step_t startStep,
		parameter_t parameter1 = 0, parameter_t parameter2 = 0, parameter_t parameter3 = 0);

	PlatformFixture& GetPlatformFixture();

	virtual bool CheckIncreaseStep(step_t stepsToIncrease = 1);

	virtual void StroboChanged();

	dmx_channel_t GetDmxOffsetChannel();

	void SetDmxOffsetChannel(dmx_channel_t dmxOffsetChannel);

	bool GetInitialize();
	void SetInitialize(bool initialize);

	program_t GetProgram();
	void SetProgram(program_t program);

	step_t GetNrOfSteps();
	void SetNrOfSteps(step_t nrOfSteps);

	step_time_t GetStepTime();
	void SetStepTime(step_time_t stepTime);

	step_duration_t GetStepDuration();
	void SetStepDuration(step_duration_t stepDuration);

	step_t GetCurrentStep();
	void SetCurrentStep(step_t currentStep);

	parameter_t GetParameter1();
	void SetParameter1(parameter_t parameter1);

	parameter_t GetParameter2();
	void SetParameter2(parameter_t parameter2);

	parameter_t GetParameter3();
	void SetParameter3(parameter_t parameter3);

protected:
	void SetPlatformFixture(PlatformFixture* platformFixture);

private:
	PlatformFixture* _platformFixture;
};
