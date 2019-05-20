// Fixture.h
// Generic properties for a fixture.

#pragma once

#include <stdint.h>
#include "MestraTypes.h"
#include "PlatformFixture.h"

/* abstract */ class Fixture
{
public:
	Fixture();

	~Fixture();
		
	void InitializeProgram(program_t programNumber, step_t nrOfSteps, step_t startStep,
		parameter_t parameter1 = 0, parameter_t parameter2 = 0, parameter_t parameter3 = 0);

	PlatformFixture& GetPlatformFixture();

	virtual bool CheckIncreaseStep();

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

	step_time_t GetStepDuration();
	void SetStepDuration(step_time_t stepDuration);

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

	dmx_channel_t	_dmxOffsetChannel;

	// True until it has been processed for the first time.
	bool	    _initialize;

	program_t	_program;

	// Current step within the program.
	step_t	_currentStep;

	// Number of steps within the program.
	step_t	_nrOfSteps;

	// Absolute time when the next step starts.
	step_time_t	_stepTime;

	// Duration of a step.
	step_time_t	_stepDuration;

	// Parameters for specific programs.
	parameter_t _parameter1;
	parameter_t _parameter2;
	parameter_t _parameter3;
};
