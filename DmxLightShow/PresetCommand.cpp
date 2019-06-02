// PresetCommand.cpp
// Command for changing a default color property of a Par.

#include "PresetCommand.h"
#include "ProgramExecuter.h"
#include "BitsUtils.h"
#include "ClassNames.h"
#include "LightSetup.h"
#include "Irgbw.h"


PresetCommand::PresetCommand()
{
}


PresetCommand::~PresetCommand()
{
}


void PresetCommand::Run(par_bits_t parBits, preset_t presetNumber)
{
	fixture_number_t selectedParIndex = 0;
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		if ((parBits & (0x0001 << parNumber)) > 0)
		{
			fixture_number_t nrOfPars = BitsUtils::GetNrOfHighBits(parBits);
			SetFixturePreset(presetNumber, parNumber, selectedParIndex, nrOfPars);
			selectedParIndex++;
		}
	}
}


// GetValue contains preset number.
void PresetCommand::SetFixturePreset(preset_t presetNumber, fixture_number_t parNumber, fixture_number_t selectedParIndex, fixture_number_t nrOfPars)
{
	Par& par = LightSetup.GetPar(parNumber);
	
	step_t nrOfSteps = 1U;
	
	switch (presetNumber)
	{
	case 10U: 
		// Default color -> Alternate color
		{
			Irgbw color;
			par.GetDefaultColor(color);
			par.SetAlternateColorIrgbw(color);
		}
		break;

	case 11U:
		// Alternate color -> Default color
		{
			Irgbw color;
			par.GetAlternateColor(color);
			par.SetDefaultColorIrgbw(color);
		}
		break;

	case 12U:
		// Default color <-> Alternate color
		{
			Irgbw defaultColor;
			Irgbw alternateColor;
			par.GetDefaultColor(defaultColor); 
			par.GetAlternateColor(alternateColor);
			par.SetDefaultColorIrgbw(alternateColor);
			par.SetAlternateColorIrgbw(defaultColor);
		}
		break;

	case 13U:
		// Default color -> Actual color
		{
			Irgbw color;
			par.GetDefaultColor(color);
			par.WriteIrgb(color);
		}
		break;

	case 14U:
		// Actual color -> Default color
		{
			Irgbw color;
			par.GetActualColor(color);
			par.SetDefaultColorIrgbw(color);
		}
		break;

	case 15U:
		// Default color <-> Actual color
	  {
			Irgbw color;
		  par.GetActualColor(color);
			par.SetDefaultColorIrgbw(color);
		}
		break;

	case 16U:
		{
			// Alternate color -> Actual color
			Irgbw color;
			par.GetAlternateColor(color);
			par.WriteIrgb(color);
		}
		break;

	case 17U:
		// Actual color -> Alternate color
		{
			Irgbw actualColor;
			par.GetActualColor(actualColor);
			par.SetAlternateColorIrgbw(actualColor);
		}
		break;

	case 18U:
		// Alternate color <-> Actual color
		{
			Irgbw actualColor;
			Irgbw alternateColor;
			par.GetActualColor(actualColor);
			par.GetAlternateColor(alternateColor);
			par.WriteIrgb(alternateColor);
			par.SetAlternateColorIrgbw(actualColor);
		}
		break;
		
	case 20U:
		// Solid (default color)
		par.InitializeProgram(5, nrOfSteps, 0U); // Start with default color
		break;

	case 30U:
		// Switch between default and alternate color
		par.InitializeProgram(10U, 2U, 0U);
		break;

	case 31U:
		// Switch between alternate and default color
		par.InitializeProgram(10U, 2U, 1U);
		break;

	case 40U:
		// Chase left -> right
		par.InitializeProgram(10U, nrOfPars, 0U, selectedParIndex, selectedParIndex);
		break;

	case 41U:
		// Chase right -> left
		par.InitializeProgram(10U, nrOfPars, 0U, 
			(parameter_t)(nrOfPars - selectedParIndex - 1), 
			(parameter_t)(nrOfPars - selectedParIndex - 1U));
		break;

	case 42U:
		// Chase left -> right -> left
		nrOfSteps = (nrOfPars - 1U) * 2;
		par.InitializeProgram(10U, nrOfSteps, 0U, 
			(parameter_t)selectedParIndex, 
			(parameter_t)((nrOfSteps - selectedParIndex) % nrOfSteps));
		break;

	case 43U:
		// Chase right -> left -> right
		par.InitializeProgram(10U, (nrOfPars - 1U) * 2U, 0U, 
			(parameter_t)(nrOfPars - 1U - selectedParIndex),
			(parameter_t)(nrOfPars - 1U + selectedParIndex));
		break;

	case 50U: 
		// Fade default color -> alternate color
		// Use only half the steps
		par.InitializeProgram(20U, MAX_PAR_INTENSITIES, 0U);
		break;

	case 51U:
		// Fade alternate color -> default color
		// Use only last half the steps (like program 20, but start halfway).
		par.InitializeProgram(21, MAX_PAR_INTENSITIES - 1U, 
			(parameter_t)0U,
			(parameter_t)(MAX_PAR_INTENSITIES - 1U), 
			(parameter_t)0U);
		break;

	case 52U:
		// Fade default color -> alternate color -> default color
		par.InitializeProgram(20U, 2U * (MAX_PAR_INTENSITIES * 1U),  0U);
		break;

	case 53U:
		// Fade alternate color -> default color -> alternate color
		// Start halfway.
		par.InitializeProgram(20, MAX_PAR_INTENSITIES * 2U - 2U, (MAX_PAR_INTENSITIES - 1U));
		break;

	case 60U:
		// Fade chase left -> Right
		par.InitializeProgram(30U, nrOfPars * (MAX_PAR_INTENSITIES - 1U), 0U, 
			(parameter_t)selectedParIndex, (parameter_t)selectedParIndex, (parameter_t)nrOfPars);
		break;

	case 61U:
	  // Fade chase right -> left
		par.InitializeProgram(30U, nrOfPars * (MAX_PAR_INTENSITIES - 1U), 0U,
			(parameter_t)(nrOfPars - selectedParIndex - 1U), (parameter_t)(nrOfPars - selectedParIndex - 1U), (parameter_t)nrOfPars);
		break;

	case 62U:
		// Fade chase left -> right -> left
		nrOfSteps = (nrOfPars - 1U) * 2U;
		par.InitializeProgram(30U, nrOfSteps * (MAX_PAR_INTENSITIES - 1U), 0U,
			(parameter_t) selectedParIndex, 
			(parameter_t)(nrOfSteps - selectedParIndex) % nrOfSteps, 
			(parameter_t)nrOfSteps);
		break;

	case 63U:
		// Fade chase right -> left -> right
		nrOfSteps = (nrOfPars - 1U) * 2U;
		par.InitializeProgram(30, nrOfSteps * (MAX_PAR_INTENSITIES - 1U), 0U,
			(parameter_t)(nrOfPars - 1U - selectedParIndex), 
			(parameter_t)(nrOfPars - 1U + selectedParIndex), 
			(parameter_t)nrOfSteps);
		break;

	case 70U:
		// Rainbow colors, left -> right
		par.InitializeProgram(40U, MAX_PAR_INTENSITIES * RAINBOW_COLORS,
			(parameter_t)(MAX_PAR_INTENSITIES * (selectedParIndex % RAINBOW_COLORS)),
			(parameter_t)-MAX_PAR_INTENSITIES); // -MAX_PAR_INTENSITIES means decreasing a full color (no fade), left -> right
		break;

	case 71U:
		// Rainbow colors, right -> left
		par.InitializeProgram(40U, MAX_PAR_INTENSITIES * RAINBOW_COLORS,
			(parameter_t)(MAX_PAR_INTENSITIES * (RAINBOW_COLORS - 1U) - MAX_PAR_INTENSITIES * (selectedParIndex % RAINBOW_COLORS)),
			(parameter_t)MAX_PAR_INTENSITIES); // MAX_PAR_INTENSITIES means increasing a full color (no fade), right -> left
		break;

	case 72U:
		// Rainbow colors + Fade, left -> right
		par.InitializeProgram(40U, MAX_PAR_INTENSITIES * RAINBOW_COLORS, 
			(parameter_t)(MAX_PAR_INTENSITIES * (RAINBOW_COLORS) - 1U - MAX_PAR_INTENSITIES * (selectedParIndex % RAINBOW_COLORS)),
			(parameter_t)1U); // 1 means left -> right
		break;

	case 73U:
		// Rainbow colors + Fade, right -> left (note left->right->left or vice versa is not needed)
		par.InitializeProgram(40U, MAX_PAR_INTENSITIES * RAINBOW_COLORS,
			(parameter_t)(MAX_PAR_INTENSITIES * (selectedParIndex % RAINBOW_COLORS)),
			(parameter_t)1U); // -1 means right -> left
		break;

	default:
		break;
	}
}


void PresetCommand::CommandAllOff(Par& par)
{
	Irgbw color;
	par.GetDefaultColor(color);
	SetFixedIrgbw(par, color, 0, 0, 0, 0, 0);
	par.SetDefaultColorIrgbw(color);

	par.GetAlternateColor(color);
	SetFixedIrgbw(par, color, 0, 0, 0, 0, 0);
	par.SetAlternateColorIrgbw(color);
		
	LightSetup.GetStrobo().AllOff();
}


void PresetCommand::SetFixedIrgb(Par& par, Irgbw& color, uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue)
{
	color.SetIrgb(intensity, red, green, blue);
	par.SetProgram(0);
}


void PresetCommand::SetFixedIrgbw(Par& par, Irgbw& color, uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
{
	color.SetIrgbw(intensity, red, green, blue, white);
	par.SetProgram(0);
}
