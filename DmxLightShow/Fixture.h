// Fixture.h
// Generic properties for a fixture.

#pragma once

#include "MestraTypes.h"
#include "PlatformFixture.h"


/* abstract */ class Fixture
{
public:
	Fixture(fixture_number_t fixture_number);

	virtual ~Fixture();

	void InitializeProgram(program_t programNumber, step_t nrOfSteps, step_t startStep,
		parameter_t parameter1 = 0, parameter_t parameter2 = 0, parameter_t parameter3 = 0);

	PlatformFixture& GetPlatformFixture() const;

	fixture_number_t GetFixtureNumber() const;
	
	virtual bool CheckIncreaseStep(step_t stepsToIncrease = 1);

	virtual void StroboChanged();

	dmx_channel_t GetDmxOffsetChannel() const;

	void SetDmxOffsetChannel(dmx_channel_t dmxOffsetChannel);

	bool GetInitialize() const;
	void SetInitialize(bool initialize);

	program_t GetProgram() const;
	void SetProgram(program_t program);

	step_t GetNrOfSteps() const;
	void SetNrOfSteps(step_t nrOfSteps);

	step_time_t GetStepTime() const;
	void SetStepTime(step_time_t stepTime);

	step_duration_t GetStepDuration() const;
	void SetStepDuration(step_duration_t stepDuration);

	step_t GetStepNumber() const;
	void SetStepNumber(step_t currentStep);

	bool GetHold() const;
	void SetHold(bool hold);

	bool GetOnce() const;
	void SetOnce(bool hold);

	parameter_t GetParameter1() const;
	void SetParameter1(parameter_t parameter1);

	parameter_t GetParameter2() const;
	void SetParameter2(parameter_t parameter2);

	parameter_t GetParameter3() const;
	void SetParameter3(parameter_t parameter3);

	bool GetForceUpdate() const;

protected:
	void SetPlatformFixture(PlatformFixture* platformFixture);

private:
	PlatformFixture* _platformFixture;

	fixture_number_t _fixtureNumber;

	bool _initialize : 1;

	bool _forceUpdate: 1;

	bool _hold : 1;

	bool _once : 1;

	dmx_channel_t _dmxOffsetChannel;

	program_t _program;

	step_t _nrOfSteps;

	step_time_t _stepTime;

	step_duration_t _stepDuration;

	step_t _stepNumber;

	parameter_t _parameter1;
	parameter_t _parameter2;
	parameter_t _parameter3;
};
