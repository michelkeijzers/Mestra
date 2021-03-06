// ProgramExecuter.cpp
// Executes program of fixtures.

#include <stdlib.h>

#include "AssertUtils.h"

#include "ClassNames.h"
#include "LightSetup.h"
#include "MathUtils.h"
#include "MestraTypes.h"
#include "ProgramExecuter.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "Duration.h"


ProgramExecuter::ProgramExecuter()
{
}


ProgramExecuter::~ProgramExecuter()
{
}


/* static */ void ProgramExecuter::Run()
{  
	RunFixtures();

	LightSetup.GetStrobo().Run();
}


/* static */ void ProgramExecuter::RunFixtures()
{
	// Run each par.
	for (fixture_number_t fixtureNumber = 0; fixtureNumber < NR_OF_PARS; fixtureNumber++)
	{
		Par& par = LightSetup.GetPar(fixtureNumber);

		LightSetup.GetStrobo().RunFixture(fixtureNumber);

		bool initialize = par.GetInitialize();

		if (initialize)
		{
			step_time_t duration = Duration::ToStepTime(par.GetStepDuration());
			if (duration > 0)
			{
				par.SetStepTime(millis() + duration);
			}

			par.SetInitialize(false);
		}

		switch (par.GetProgram())
		{
		case 0: 
			// No action
			break;

		case 5:
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

		case 40: // Rainbow colors, param 1 = +1 / -1
			RainbowColorProgram(par, initialize);
			break;

		default:
			AssertUtils::MyAssert(false);
			break;
		}
	}
}


/* static */ void ProgramExecuter::FixedColorProgram(Par& par, bool initialize)
{
	if (initialize)
	{
		par.SetStepNumber(0);
		Irgbw defaultColor = par.GetDefaultColor();
		par.WriteIrgb(defaultColor);
	}
	else if (par.CheckIncreaseStep())
	{
		// If default color changed, update.
		Irgbw defaultColor = par.GetDefaultColor();
		par.WriteIrgb(defaultColor);
	}
}


/*
Parameter 1 and parameter 2 are active steps (default color), otherwise alternative color.*/
/* static */ void ProgramExecuter::DualColorProgram(Par& par, bool initialize)
{
	bool enable = par.GetStepNumber() == step_t(par.GetParameter1()) ||
                  par.GetStepNumber() == step_t(par.GetParameter2());

	if (initialize)
	{
		SetDefaultOrAlternate(par, enable ? Par::EActiveColor::Default : Par::EActiveColor::Alternate);
		par.SetStepNumber(1);
	}
	else if (par.CheckIncreaseStep())
	{
		SetDefaultOrAlternate(par, enable ? Par::EActiveColor::Default : Par::EActiveColor::Alternate);
	}
}


/* static */ void ProgramExecuter::FadeInOutProgram(Par& par, bool initialize)
{
	if (initialize)
	{
		Irgbw defaultColor = par.GetDefaultColor();
		Irgbw alternateColor = par.GetAlternateColor();

		par.WriteIrgb(par.GetStepNumber() < PAR_MAX_PAR_INTENSITIES - 1 ? defaultColor : alternateColor);

		par.SetStepDuration(step_duration_t(MathUtils::Max(1, par.GetStepDuration() / (2U * (PAR_MAX_PAR_INTENSITY - 1U)))));
		par.SetStepTime(millis() + Duration::ToStepTime(par.GetStepDuration()));
	}
	else if (par.CheckIncreaseStep())
	{
		step_t currentStep = par.GetStepNumber();
		SetFadeColor(par,
			currentStep < PAR_MAX_PAR_INTENSITIES - 1
			? currentStep
			: (2 * PAR_MAX_PAR_INTENSITY - currentStep - 1U) % PAR_MAX_PAR_INTENSITY);
	}
}


/* static */ void ProgramExecuter::FadeOutProgram(Par& par, bool initialize)
{
	{
		if (initialize)
		{
			Irgbw alternateColor = par.GetAlternateColor();
			par.WriteIrgb(alternateColor);

			par.SetStepDuration(step_duration_t(MathUtils::Max(1, par.GetStepDuration() / (PAR_MAX_PAR_INTENSITY - 1U))));
			par.SetStepTime(millis() + Duration::ToStepTime(par.GetStepDuration()));
		}
		else if (par.CheckIncreaseStep())
		{
			step_t currentStep = par.GetStepNumber();
			SetFadeColor(par, PAR_MAX_PAR_INTENSITY - currentStep - 1U);
		}
	}
}


/* static */ void ProgramExecuter::DualColorFadeProgram(Par& par, bool initialize)
{
	if (initialize)
	{
		Irgbw defaultColor = par.GetDefaultColor();
		Irgbw alternateColor = par.GetAlternateColor();

		// Always exactly default color or alternate color, not an inbetween color
		par.WriteIrgb(
			par.GetParameter1() * (PAR_MAX_PAR_INTENSITIES - 1) == par.GetStepNumber() ||
			par.GetParameter2() * (PAR_MAX_PAR_INTENSITIES - 1) == par.GetStepNumber()
			? defaultColor
			: alternateColor);

		par.SetStepDuration(step_duration_t(MathUtils::Max(1, par.GetStepDuration() / (2U * (par.GetParameter3() - 1U) * (PAR_MAX_PAR_INTENSITY - 1U)))));
		par.SetStepTime(millis() + Duration::ToStepTime(par.GetStepDuration()));
	}
	else if (par.CheckIncreaseStep())
	{
		step_t activeStep1 = par.GetParameter1() * (PAR_MAX_PAR_INTENSITIES - 1);
		if (activeStep1 == 0U && (par.GetStepNumber() >= PAR_MAX_PAR_INTENSITIES))
		{
			activeStep1 += par.GetParameter3() * (PAR_MAX_PAR_INTENSITIES - 1);
		}

		step_t activeStep2 = par.GetParameter2() * (PAR_MAX_PAR_INTENSITIES - 1);
		if (activeStep2 == 0U && (par.GetStepNumber() >= PAR_MAX_PAR_INTENSITIES))
		{
			activeStep2 += par.GetParameter3() * (PAR_MAX_PAR_INTENSITIES - 1);
		}

		if (abs(par.GetStepNumber() - activeStep1) < PAR_MAX_PAR_INTENSITIES)
		{
			if (par.GetStepNumber() < activeStep1)
			{
				// Towards active step 1.
				SetFadeColor(par, step_t(activeStep1 - par.GetStepNumber()));
			}
			else
			{
				// Away from step 1.
				SetFadeColor(par, step_t(par.GetStepNumber() - activeStep1));
			}
		}
		else if (abs(par.GetStepNumber() - activeStep2) < PAR_MAX_PAR_INTENSITIES)
		{
			if (par.GetStepNumber() < activeStep2)
			{
				// Towards active step 2.
				SetFadeColor(par, step_t(activeStep2 - par.GetStepNumber()));
			}
			else
			{
				// Away from step 2.
				SetFadeColor(par, step_t(par.GetStepNumber() - activeStep2));
			}
		}
	}
}


// Both normal and fade
// Fade steps with increments of +1 or -1 through all steps (# Rainbow colors * MAX_PAR_INTENSITIES steps,
// +1 for right, -1 for left (stored in parameter 1).
// Normal skips with steps of MAX_PAR_INTENSITIES, i.e. steps to the next/previous 'full' rainbow color.
// Normal and default colors are not used (SetRainbowColor instead).
/* static */ void ProgramExecuter::RainbowColorProgram(Par& par, bool initialize)
{
	if (initialize)
	{
		SetRainbowColor(par, par.GetStepNumber());

		par.SetStepDuration(step_duration_t(MathUtils::Max(1, step_duration_t(par.GetStepDuration() / 
		 (PROGRAM_EXECUTER_RAINBOW_COLORS * PAR_MAX_PAR_INTENSITY / abs(par.GetParameter1()))))));

		par.SetStepTime(millis() + Duration::ToStepTime(par.GetStepDuration()));
	}
	else if (par.CheckIncreaseStep(step_t(par.GetParameter1())))
	{
		SetRainbowColor(par, par.GetStepNumber());
	}
}


/*
 * Colors:
 * 0 * MAX_PAR_INTENSITIES    Red
 * 1 * MAX_PAR_INTENSITIES    Green
 * 2 * MAX_PAR_INTENSITIES    Blue
 */
/* static */ void ProgramExecuter::SetRainbowColor(Par& par, step_t step)
{
	Irgbw targetColor;
	
	targetColor.SetIrgb(
		PAR_MAX_INTENSITY,
		CalcRainbowColor(step, 
		 intensity_t(PAR_MAX_PAR_INTENSITIES - 1U - step), 
		 0U, 
		 intensity_t((step - 2U * PAR_MAX_PAR_INTENSITIES))),

		CalcRainbowColor(step, 
		 intensity_t(step),
		 intensity_t(2U * PAR_MAX_PAR_INTENSITIES - 1U - step), 
		 0U),
		
		CalcRainbowColor(step, 
		 0U, 
		 intensity_t((step - PAR_MAX_PAR_INTENSITIES)), 
		 intensity_t(3U * PAR_MAX_PAR_INTENSITIES - 1U - step)));

	par.WriteIrgb(targetColor);
}


/* static */ intensity_t ProgramExecuter::CalcRainbowColor(step_t step, 
	intensity_t firstRangeValue, intensity_t secondRangeValue, intensity_t thirdRangeValue)
{
	return step < PAR_MAX_PAR_INTENSITIES ? firstRangeValue
		: step < 2 * PAR_MAX_PAR_INTENSITIES
		       ? secondRangeValue
		       : thirdRangeValue;
}


/*
Step: 0=100% default color, step MAX_PAR_INTENSITY=100% alternate color
*/
/* static */ void ProgramExecuter::SetFadeColor(Par& par, step_t step)
{
	
	Irgbw defaultColor = par.GetDefaultColor();
	Irgbw alternateColor = par.GetAlternateColor();;

	Irgbw targetColor;
	targetColor.SetIntensity(intensity_t(defaultColor.GetIntensity() +
		(alternateColor.GetIntensity() - defaultColor.GetIntensity()) * step / PAR_MAX_PAR_INTENSITY));

	targetColor.SetRed(intensity_t(defaultColor.GetRed() +
		(alternateColor.GetRed() - defaultColor.GetRed()) * step / PAR_MAX_PAR_INTENSITY));

	targetColor.SetGreen(intensity_t(defaultColor.GetGreen() +
		(alternateColor.GetGreen() - defaultColor.GetGreen()) * step / PAR_MAX_PAR_INTENSITY));

	targetColor.SetBlue(intensity_t(defaultColor.GetBlue() +
		(alternateColor.GetBlue() - defaultColor.GetBlue()) * step / PAR_MAX_PAR_INTENSITY));

	par.WriteIrgb(targetColor);
}


/* static */ void ProgramExecuter::SetDefaultOrAlternate(Par& par, Par::EActiveColor activeColor)
{
	Irgbw color;
	
	switch (activeColor)
	{
	case Par::EActiveColor::Default:
		color = par.GetDefaultColor(); //TOOD: Remove
		break;

	case Par::EActiveColor::Alternate:
		color = par.GetAlternateColor(); //TODO: Remove
		break;

	default:
		AssertUtils::MyAssert(false);
		break;
	}

	par.WriteIrgb(color);
}
