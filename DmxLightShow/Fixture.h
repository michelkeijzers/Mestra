// Fixture.h
// Generic properties for a fixture.

#pragma once

#include <stdint.h>


/* abstract */ class Fixture
{
private:
	uint16_t	_dmxOffsetChannel;

	// True until it has been processed for the first time.
	bool	    _initialize;

	uint16_t	_program;
	
	// Current step within the program.
	uint16_t	_currentStep;

	// Number of steps within the program.
	uint16_t	_nrOfSteps;

	// Absolute time when the next step starts.
	uint32_t	_stepTime;

	// Duration of a step.
	uint32_t	_stepDuration;

	// Parameters for specific programs.
	uint16_t _parameter1;
	uint16_t _parameter2;

public:
	Fixture();

	~Fixture();

	uint16_t GetDmxOffsetChannel() { return _dmxOffsetChannel; }
	void SetDmxOffsetChannel(uint16_t dmxOffsetChannel) { _dmxOffsetChannel = dmxOffsetChannel; }

	bool GetInitialize() { return _initialize; }
	void SetInitialize(bool initialize) { _initialize = initialize; }

	uint16_t GetProgram() { return _program; }
	void SetProgram(uint16_t program) { _program = program; }

	uint16_t GetNrOfSteps() { return _nrOfSteps; }
	void SetNrOfSteps(uint16_t nrOfSteps) { _nrOfSteps = nrOfSteps; }

	uint32_t GetStepTime() { return _stepTime; }
	void SetStepTime(uint32_t stepTime) { _stepTime = stepTime; }

	uint32_t GetStepDuration() { return _stepDuration; }
	void SetStepDuration(uint32_t stepDuration) { _stepDuration = stepDuration; }

	uint16_t GetCurrentStep() { return _currentStep; }
	void SetCurrentStep(uint16_t currentStep) { _currentStep = currentStep; }

	uint16_t GetParameter1() { return _parameter1; }
	void SetParameter1(uint16_t parameter1) { _parameter1 = parameter1; }

	uint16_t GetParameter2() { return _parameter2; }
	void SetParameter2(uint16_t parameter2) { _parameter2 = parameter2; }

	void InitializeProgram(uint16_t programNumber, uint16_t nrOfSteps, uint16_t startStep, 
		uint16_t parameter1 = 0, uint16_t parameter2 = 0);
	
	virtual bool CheckIncreaseStep();
};
