// ProgramExecuter.h
// Executes program of fixtures.

#pragma once

#include "LightSetup.h"

// R -> G -> B
#define RAINBOW_COLORS 3U

class ProgramExecuter
{
public:
	ProgramExecuter();
	~ProgramExecuter();

	void Run();
	void RunFixtures();

	void FadeInOutProgram(Par& par, bool initialize);
	void FadeOutProgram(Par& par, bool initialize);

  void DualColorProgram(Par& par, bool initialize);
	void DualColorFadeProgram(Par& par, bool initialize);

	void FixedColorProgram(Par& par, bool initialize);

	void RainbowColorProgram(Par& par, bool initialize); // Both normal and fade

	void SetFadeColor(Par& par, step_t step);

private:
	void SetDefaultOrAlternate(Par& par, Par::EActiveColor color);

	void SetRainbowColor(Par& par, step_t step);
	intensity_t CalcRainbowColor(step_t step,
		intensity_t firstRangeValue, intensity_t secondRangeValue, intensity_t thirdRangeValue);
};

