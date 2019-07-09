// ProgramExecuter.h
// Executes program of fixtures.

#pragma once

#include "LightSetup.h"

// R -> G -> B
#define PROGRAM_EXECUTER_RAINBOW_COLORS 3U

class ProgramExecuter
{
public:
	static void Run();
	static void RunFixtures();

	static void FadeInOutProgram(Par& par, bool initialize);
	static void FadeOutProgram(Par& par, bool initialize);

	static void DualColorProgram(Par& par, bool initialize);
	static void DualColorFadeProgram(Par& par, bool initialize);

	static void FixedColorProgram(Par& par, bool initialize);

	static void RainbowColorProgram(Par& par, bool initialize); // Both normal and fade

	static void SetFadeColor(Par& par, step_t step);

private:
	ProgramExecuter();
	~ProgramExecuter();

	static void SetDefaultOrAlternate(Par& par, Par::EActiveColor color);

	static void SetRainbowColor(Par& par, step_t step);
	static intensity_t CalcRainbowColor(step_t step,
		intensity_t firstRangeValue, intensity_t secondRangeValue, intensity_t thirdRangeValue);
};

