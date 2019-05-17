// ProgramExecuter.cpp
// Executes program of fixtures.

#include "ProgramExecuter.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(LIGHT_SETUP_CLASS)
#include "BitsUtils.h"
#include <stdlib.h>
#include "MathUtils.h"




ProgramExecuter::ProgramExecuter()
{
}


ProgramExecuter::~ProgramExecuter()
{
}


void ProgramExecuter::Run()
{  
	for (uint8_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
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

		case 30: // Only fade in/out at step Paremeter 1 or 2 (Chase)
			DualColorFadeProgram(par, initialize);
			break;

		default:
			break;
		}
	}
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


void ProgramExecuter::FadeInOutProgram(Par& par, bool initialize)
{
	if (initialize)
	{
		par.WriteIrgb(par.GetCurrentStep() < MAX_PAR_INTENSITIES 
			? par.GetDefaultColor() 
			: par.GetAlternateColor());

		par.SetStepDuration(par.GetStepDuration() / (MAX_PAR_INTENSITY * 2));
		par.SetStepTime(millis() + par.GetStepDuration());
	}
	else if (par.CheckIncreaseStep())
	{
		uint16_t currentStep = par.GetCurrentStep();
		SetFadeColor(par,
			currentStep < MAX_PAR_INTENSITIES
			? currentStep
			: (2 * MAX_PAR_INTENSITY - currentStep - 1) % MAX_PAR_INTENSITY);
	}
}


void ProgramExecuter::FadeOutProgram(Par& par, bool initialize)
{
	{
		if (initialize)
		{
			par.WriteIrgb(par.GetAlternateColor());
			par.SetStepDuration(par.GetStepDuration() / (MAX_PAR_INTENSITY));
			par.SetStepTime(millis() + par.GetStepDuration());
		}
		else if (par.CheckIncreaseStep())
		{
			uint16_t currentStep = par.GetCurrentStep();
			SetFadeColor(par, MAX_PAR_INTENSITY - currentStep - 1);
		}
	}
}


void ProgramExecuter::DualColorFadeProgram(Par& par, bool initialize)
{
	if (initialize)
	{
		par.WriteIrgb(
		 ((par.GetParameter1() * (MAX_PAR_INTENSITIES - 1) == par.GetCurrentStep()) ||
	    (par.GetParameter1() * (MAX_PAR_INTENSITIES - 1) == par.GetCurrentStep()))
			? par.GetDefaultColor()
			: par.GetAlternateColor());

		par.SetStepDuration(par.GetStepDuration() / (MAX_PAR_INTENSITY * 2));
		par.SetStepTime(millis() + par.GetStepDuration());
	}
	else if (par.CheckIncreaseStep())
	{
		uint16_t toParameter1Step = par.GetCurrentStep() - par.GetParameter1() * (MAX_PAR_INTENSITIES - 1);
		uint16_t toParameter2Step = par.GetCurrentStep() - par.GetParameter2() * (MAX_PAR_INTENSITIES - 1);

		bool colorSet = false;
		if (toParameter1Step > -MAX_PAR_INTENSITIES)
		{
			if (toParameter1Step < 0)
			{
				// Towards default color
				SetFadeColor(par, MAX_PAR_INTENSITIES - 1 - toParameter1Step);
					colorSet = true;
			}
			else if (toParameter1Step < MAX_PAR_INTENSITIES)
			{
				SetFadeColor(par, toParameter1Step);
					colorSet = true;
			}
		}

		// Almost like above
		if (!colorSet)
		{
			if (toParameter2Step > -MAX_PAR_INTENSITIES)
			{
				if (toParameter2Step < 0)
				{
					// Towards default color
					SetFadeColor(par, MAX_PAR_INTENSITIES - 1 - toParameter2Step);
						colorSet = true;
				}
				else if (toParameter2Step < MAX_PAR_INTENSITIES)
				{
					SetFadeColor(par, toParameter2Step);
						colorSet = true;
				}
			}
		}
	}
}


/*
Step 0: 100% default color, step MAX_PAR_INTENSITY: 100% alternate color
*/
void ProgramExecuter::SetFadeColor(Par& par, uint16_t step)
{
	Irgbw targetColor;
	Irgbw& defaultColor = par.GetDefaultColor();
	Irgbw& alternateColor = par.GetAlternateColor();

	targetColor.SetIntensity((uint8_t)(defaultColor.GetIntensity() +
		(alternateColor.GetIntensity() - defaultColor.GetIntensity()) * step / MAX_PAR_INTENSITY));

	targetColor.SetRed((uint8_t)(defaultColor.GetRed() + 
		(alternateColor.GetRed() - defaultColor.GetRed()) * step / MAX_PAR_INTENSITY));

	targetColor.SetGreen((uint8_t)(defaultColor.GetGreen() +
		(alternateColor.GetGreen() - defaultColor.GetGreen()) * step / MAX_PAR_INTENSITY));

	targetColor.SetBlue((uint8_t)(defaultColor.GetBlue() +
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
