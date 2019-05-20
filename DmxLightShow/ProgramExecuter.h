// ProgramExecuter.h
// Executes program of fixtures.

#pragma once

#include "LightSetup.h"

class ProgramExecuter
{
public:
	ProgramExecuter();
	~ProgramExecuter();

	void Run();

	void FadeInOutProgram(Par& par, bool initialize);
	void FadeOutProgram(Par& par, bool initialize);

  void DualColorProgram(Par& par, bool initialize);
	void DualColorFadeProgram(Par& par, bool initialize);

	void FixedColorProgram(Par& par, bool initialize);

	void SetFadeColor(Par& par, step_t step);

private:
	void SetDefaultOrAlternate(Par& par, Par::EActiveColor color);
};

