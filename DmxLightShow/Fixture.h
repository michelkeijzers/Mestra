// Fixture.h
// Generic properties for a fixture.

#pragma once

#include "MestraTypes.h"
#include "PlatformFixture.h"


/* abstract */ class Fixture
{
public:
	enum ETriggerState
	{
		Off,			// Default
		Waiting,	// Waiting for trigger
		Active 		// Trigger is active
	};

	Fixture(fixture_number_t fixture_number);

	virtual ~Fixture();

	void InitializeProgram(program_t programNumber, step_t nrOfSteps, step_t startStep,
		parameter_t parameter1 = 0, parameter_t parameter2 = 0, parameter_t parameter3 = 0);

	PlatformFixture& GetPlatformFixture() const;

	virtual bool CheckIncreaseStep(step_t stepsToIncrease = 1);

	virtual void StroboChanged();

	dmx_channel_t GetDmxOffsetChannel() const;

	void SetDmxOffsetChannel(dmx_channel_t dmxOffsetChannel);

	bool GetInitialize() const;
	void SetInitialize(bool initialize);

	ETriggerState GetTriggerState() const;
  void SetTriggerState(ETriggerState triggerState);

	void ActivateTrigger();

	program_t GetProgram() const;
	void SetProgram(program_t program);

	step_t GetNrOfSteps() const;
	void SetNrOfSteps(step_t nrOfSteps);

	step_time_t GetStepTime() const;
	void SetStepTime(step_time_t stepTime);

	step_duration_t GetStepDuration() const;
	void SetStepDuration(step_duration_t stepDuration);

	step_t GetCurrentStep() const;
	void SetCurrentStep(step_t currentStep);

	parameter_t GetParameter1() const;
	void SetParameter1(parameter_t parameter1);

	parameter_t GetParameter2() const;
	void SetParameter2(parameter_t parameter2);

	parameter_t GetParameter3() const;
	void SetParameter3(parameter_t parameter3);

protected:
	void SetPlatformFixture(PlatformFixture* platformFixture);

private:
	PlatformFixture* _platformFixture;

	fixture_number_t _fixtureNumber;

	bool _initialize;

	dmx_channel_t _dmxOffsetChannel;

	ETriggerState _triggerState;

	program_t _program;

	step_t _nrOfSteps;

	step_time_t _stepTime;

	step_duration_t _stepDuration;

	step_t _currentStep;

	parameter_t _parameter1;
	parameter_t _parameter2;
	parameter_t _parameter3;
};
