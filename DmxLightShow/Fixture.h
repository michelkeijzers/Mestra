// Fixture.h
// Generic properties for a fixture.

#pragma once

#include <stdint.h>
#include "MestraTypes.h"

#include "PlatformFixture.h"

/* abstract */ class Fixture
{
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

public:
	Fixture();

	~Fixture();



	void InitializeProgram(program_t programNumber, step_t nrOfSteps, step_t startStep,
		parameter_t parameter1 = 0, parameter_t parameter2 = 0, parameter_t parameter3 = 0);


	PlatformFixture& GetPlatformFixture()
	{
		return *_platformFixture;
	}

	virtual bool CheckIncreaseStep();


	virtual void StroboChanged() { };


	dmx_channel_t GetDmxOffsetChannel() 
	{ 
		return _dmxOffsetChannel; 
	}
	
	
	void SetDmxOffsetChannel(dmx_channel_t dmxOffsetChannel) 
	{
		_dmxOffsetChannel = dmxOffsetChannel; 
	}


	bool GetInitialize()
	{
		return _initialize; 
	}
	
	
	void SetInitialize(bool initialize) 
	{
		_initialize = initialize; 
	}


	program_t GetProgram() 
	{
		return _program; 
	}
		
	void SetProgram(program_t program) 
	{
		_program = program; 
	}


	step_t GetNrOfSteps() 
	{
		return _nrOfSteps; 
	}
		
	void SetNrOfSteps(step_t nrOfSteps) 
	{
		_nrOfSteps = nrOfSteps; 
	}


	step_time_t GetStepTime() 
	{
		return _stepTime; 
	}
		
	void SetStepTime(step_time_t stepTime)
	{
		_stepTime = stepTime; 
	}


	step_time_t GetStepDuration() 
	{
		return _stepDuration; 
	}
	
	void SetStepDuration(step_time_t stepDuration) 
	{
		_stepDuration = stepDuration; 
	}


	step_t GetCurrentStep()
	{
		return _currentStep; 
	}
		
	void SetCurrentStep(step_t currentStep) 
	{
		_currentStep = currentStep; 
	}

	
	parameter_t GetParameter1() 
	{
		return _parameter1; 
	}
		
	void SetParameter1(parameter_t parameter1)
	{
		_parameter1 = parameter1; 
	}

	
	parameter_t GetParameter2() 
	{
		return _parameter2; 
	}
		
	void SetParameter2(parameter_t parameter2) 
	{
		_parameter2 = parameter2; 
	}


	parameter_t GetParameter3() 
	{
		return _parameter3; 
	}
		
	void SetParameter3(parameter_t parameter3) 
	{
		_parameter3 = parameter3; 
	}

protected:
	void SetPlatformFixture(PlatformFixture* platformFixture);

};
