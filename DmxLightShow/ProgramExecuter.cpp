// ProgramExecuter.cpp
// Executes program of fixtures.

#include <stdlib.h>

#include "BitsUtils.h"
#include "MathUtils.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(LIGHT_SETUP_CLASS)
#include "ProgramExecuter.h"



ProgramExecuter::ProgramExecuter()
{
}


ProgramExecuter::~ProgramExecuter()
{
}


void ProgramExecuter::Run()
{  
	for (par_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		Par& par = LightSetup.GetPar(parNumber);
		bool initialize = par.GetInitialize();

		if (initialize)
		{
			par.SetStepTime(millis() + par.GetStepDuration());
			par.SetInitialize(false);
		}

		switch (par.GetProgram())
		{
		case 0:
			FixedColorProgram(par, initialize);
			break;
					
		case 10: // Only on at step Parameter 1 or 2 (On/off, Chase)
			DualColorProgram(par, initialize);
			break;

		case 20: // Fade In/Out
			FadeInOutProgram(par, initialize);
			break;

		case 21: // Fade Out
			FadeOutProgram(par, initialize);
			break;

		case 30: // Only fade in/out at step Parameter 1 or 2 (Chase)
			DualColorFadeProgram(par, initialize);
			break;

		default:
			break;
		}
	}

	LightSetup.GetStrobo().Run();
}


void ProgramExecuter::FixedColorProgram(Par& par, bool initialize)
{
	if (initialize)
	{
		par.SetCurrentStep(0);
		par.WriteIrgb(par.GetDefaultColor());
	}
	else if (par.CheckIncreaseStep())
	{
		// If default color changed, update.
		par.WriteIrgb(par.GetDefaultColor());
	}
}


/*
Parameter 1 and parameter 2 are active steps (default color), otherwise alternative color.*/
void ProgramExecuter::DualColorProgram(Par& par, bool initialize)
{
	bool enable = (par.GetCurrentStep() == par.GetParameter1()) ||
		(par.GetCurrentStep() == par.GetParameter2());

	if (initialize)
	{
		SetDefaultOrAlternate(par, enable ? Par::EActiveColor::Default : Par::EActiveColor::Alternate);
		par.SetCurrentStep(1);
	}
	else if (par.CheckIncreaseStep())
	{
		SetDefaultOrAlternate(par, enable ? Par::EActiveColor::Default : Par::EActiveColor::Alternate);
	}
}


void ProgramExecuter::FadeInOutProgram(Par & par, bool initialize)
{
	if (initialize)
	{
		par.WriteIrgb(par.GetCurrentStep() < MAX_PAR_INTENSITIES
			? par.GetDefaultColor()
			: par.GetAlternateColor());

		par.SetStepDuration(par.GetStepDuration() / (2 * (MAX_PAR_INTENSITY - 1)));
		par.SetStepTime(millis() + par.GetStepDuration());
	}
	else if (par.CheckIncreaseStep())
	{
		step_t currentStep = par.GetCurrentStep();
		SetFadeColor(par,
			currentStep < MAX_PAR_INTENSITIES
			? currentStep
			: (2 * MAX_PAR_INTENSITY - currentStep - 1) % MAX_PAR_INTENSITY);
	}
}


void ProgramExecuter::FadeOutProgram(Par & par, bool initialize)
{
	{
		if (initialize)
		{
			par.WriteIrgb(par.GetAlternateColor());
			par.SetStepDuration(par.GetStepDuration() / (MAX_PAR_INTENSITY - 1));
			par.SetStepTime(millis() + par.GetStepDuration());
		}
		else if (par.CheckIncreaseStep())
		{
			step_t currentStep = par.GetCurrentStep();
			SetFadeColor(par, MAX_PAR_INTENSITY - currentStep - 1);
		}
	}
}


void ProgramExecuter::DualColorFadeProgram(Par & par, bool initialize)
{
	if (initialize)
	{
		// Always exactly default color or alternate color, not an inbetween color
		par.WriteIrgb(
			((par.GetParameter1() * (MAX_PAR_INTENSITIES - 1) == par.GetCurrentStep()) ||
		   (par.GetParameter2() * (MAX_PAR_INTENSITIES - 1) == par.GetCurrentStep()))
			? par.GetDefaultColor()
			: par.GetAlternateColor());

		par.SetStepDuration(par.GetStepDuration() / (2 * (par.GetParameter3() - 1) * (MAX_PAR_INTENSITY - 1)));
		par.SetStepTime(millis() + par.GetStepDuration());
	}
	else if (par.CheckIncreaseStep())
	{
		step_t activeStep1 = par.GetParameter1() * (MAX_PAR_INTENSITIES - 1);
		if ((activeStep1 == 0) && (par.GetCurrentStep() >= MAX_PAR_INTENSITIES))
		{
			activeStep1 += par.GetParameter3() * (MAX_PAR_INTENSITIES - 1);
		}

		step_t activeStep2 = par.GetParameter2() * (MAX_PAR_INTENSITIES - 1);
		if ((activeStep2 == 0) && (par.GetCurrentStep() >= MAX_PAR_INTENSITIES))
		{
			activeStep2 += par.GetParameter3() * (MAX_PAR_INTENSITIES - 1);
		}

		if (abs(par.GetCurrentStep() - activeStep1) < MAX_PAR_INTENSITIES)
		{
			if (par.GetCurrentStep() < activeStep1)
			{
				// Towards active step 1.
				SetFadeColor(par, activeStep1 - par.GetCurrentStep());
			}
			else
			{
				// Away from step 1.
				SetFadeColor(par, par.GetCurrentStep() - activeStep1);
			}
		}
		else if (abs(par.GetCurrentStep() - activeStep2) < MAX_PAR_INTENSITIES)
		{
			if (par.GetCurrentStep() < activeStep2)
			{
				// Towards active step 2.
				SetFadeColor(par, activeStep2 - par.GetCurrentStep());
			}
			else
			{
				// Away from step 2.
				SetFadeColor(par, par.GetCurrentStep() - activeStep2);
			}
		}
	}
}

/*
void ProgramExecuter::DualColorFadeProgram(Par& par, bool initialize)
{
	if (initialize)
	{
		// Always exactly default color or alternate color, not an inbetween color
		par.WriteIrgb(
			((par.GetParameter1() * (MAX_PAR_INTENSITIES - 1) == par.GetCurrentStep()) ||
			(par.GetParameter2() * (MAX_PAR_INTENSITIES - 1) == par.GetCurrentStep()))
			? par.GetDefaultColor()
			: par.GetAlternateColor());

		par.SetStepDuration(par.GetStepDuration() / (2 * (par.GetParameter3() - 1) * (MAX_PAR_INTENSITY - 1)));
		par.SetStepTime(millis() + par.GetStepDuration());
	}
	else if (par.CheckIncreaseStep())
	{
		step_t activeStep1 = par.GetParameter1() * (MAX_PAR_INTENSITIES - 1);
		if ((activeStep1 == 0) && (par.GetCurrentStep() >= MAX_PAR_INTENSITIES))
		{
			activeStep1 += par.GetParameter3() * (MAX_PAR_INTENSITIES - 1);
		}

		step_t activeStep2 = par.GetParameter2() * (MAX_PAR_INTENSITIES - 1);
		if ((activeStep2 == 0) && (par.GetCurrentStep() >= MAX_PAR_INTENSITIES))
		{
			activeStep2 += par.GetParameter3() * (MAX_PAR_INTENSITIES - 1);
		}

		if (abs(par.GetCurrentStep() - activeStep1) < MAX_PAR_INTENSITIES)
		{
			if (par.GetCurrentStep() < activeStep1)
			{
				// Towards active step 1.
				SetFadeColor(par, activeStep1 - par.GetCurrentStep());
			}
			else
			{
				// Away from step 1.
				SetFadeColor(par, par.GetCurrentStep() - activeStep1);
			}
		}
		else if (abs(par.GetCurrentStep() - activeStep2) < MAX_PAR_INTENSITIES)
		{
			if (par.GetCurrentStep() < activeStep2)
			{
				// Towards active step 2.
				SetFadeColor(par, activeStep2 - par.GetCurrentStep());
			}
			else
			{
				// Away from step 2.
				SetFadeColor(par, par.GetCurrentStep() - activeStep2);
			}
		}
	}
}
*/
/*
Step: 0=100% default color, step MAX_PAR_INTENSITY=100% alternate color
*/
void ProgramExecuter::SetFadeColor(Par& par, step_t step)
{
	Irgbw targetColor;
	Irgbw& defaultColor = par.GetDefaultColor();
	Irgbw& alternateColor = par.GetAlternateColor();

	targetColor.SetIntensity((intensity_t)(defaultColor.GetIntensity() +
		(alternateColor.GetIntensity() - defaultColor.GetIntensity()) * step / MAX_PAR_INTENSITY));

	targetColor.SetRed((intensity_t)(defaultColor.GetRed() +
		(alternateColor.GetRed() - defaultColor.GetRed()) * step / MAX_PAR_INTENSITY));

	targetColor.SetGreen((intensity_t)(defaultColor.GetGreen() +
		(alternateColor.GetGreen() - defaultColor.GetGreen()) * step / MAX_PAR_INTENSITY));

	targetColor.SetBlue((intensity_t)(defaultColor.GetBlue() +
		(alternateColor.GetBlue() - defaultColor.GetBlue()) * step / MAX_PAR_INTENSITY));

	par.WriteIrgb(targetColor);
}


void ProgramExecuter::SetDefaultOrAlternate(Par& par, Par::EActiveColor color)
{
	switch (color)
	{
	case Par::EActiveColor::Default:
		par.WriteIrgb(par.GetDefaultColor());
		break;

	case Par::EActiveColor::Alternate:
		par.WriteIrgb(par.GetAlternateColor());
		break;

	default:
		//TODO
		break;
	}
}
