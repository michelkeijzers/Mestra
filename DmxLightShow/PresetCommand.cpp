// PresetCommand.cpp
// Command for changing a default color property of a Par.

#include "PresetCommand.h"
#include "ProgramExecuter.h"
#include "BitsUtils.h"
#include "LightSetup.h"
#include "Irgbw.h"


PresetCommand::PresetCommand()
{
}


PresetCommand::~PresetCommand()
{
}


/* static */ void PresetCommand::Run(par_bits_t parBits, preset_t presetNumber) 
{
	fixture_number_t selectedParIndex = 0;
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		if ((parBits & 0x0001 << parNumber) > 0)
		{
			fixture_number_t nrOfPars = BitsUtils::GetNrOfHighBits(parBits);
			SetFixturePreset(presetNumber, parNumber, selectedParIndex, nrOfPars);
			selectedParIndex++;
		}
	}
}


// GetValue contains preset number.
/* static */ void PresetCommand::SetFixturePreset(preset_t presetNumber, fixture_number_t parNumber, fixture_number_t selectedParIndex, fixture_number_t nrOfPars)
{
	Par& par = LightSetup.GetPar(parNumber);
	
	step_t nrOfSteps = 1;
	
	switch (presetNumber)
	{
	case 10: 
		// Default color -> Alternate color
		{
			Irgbw color = par.GetDefaultColor();
			par.SetAlternateColorIrgbw(color);
		}
		break;

	case 11:
		// Alternate color -> Default color
		{
			Irgbw color = par.GetAlternateColor();
			par.SetDefaultColorIrgbw(color);
		}
		break;

	case 12:
		// Default color <-> Alternate color
		{
			Irgbw defaultColor = par.GetDefaultColor(); 
			Irgbw alternateColor = par.GetAlternateColor();
			par.SetDefaultColorIrgbw(alternateColor);
			par.SetAlternateColorIrgbw(defaultColor);
		}
		break;

	case 13:
		// Default color -> Actual color
	  {
	  	Irgbw color = par.GetDefaultColor();
			par.WriteIrgb(color);
		}
		break;

	case 14:
		// Actual color -> Default color
		{
  		Irgbw actualColor;
	  	par.GetActualColor(actualColor);

			par.SetDefaultColorIrgbw(actualColor);
		}
		break;

	case 15:
		// Default color <-> Actual color
	  {
		Irgbw actualColor;
		par.GetActualColor(actualColor);

			par.SetDefaultColorIrgbw(actualColor);
		}
		break;

	case 16:
		{
			// Alternate color -> Actual color
		  Irgbw color = par.GetAlternateColor();
			par.WriteIrgb(color);
		}
		break;

	case 17:
		// Actual color -> Alternate color
		{
  		Irgbw actualColor;
	  	par.GetActualColor(actualColor);

			par.SetAlternateColorIrgbw(actualColor);
		}
		break;

	case 18:
		// Alternate color <-> Actual color
		{
		  Irgbw actualColor;
		  par.GetActualColor(actualColor);
		  Irgbw alternateColor = par.GetAlternateColor();
			par.WriteIrgb(alternateColor);
			par.SetAlternateColorIrgbw(actualColor);
		}
		break;
		
	case 20:
		// Solid (default color)
		par.InitializeProgram(program_t(5), 
			step_t(nrOfSteps), step_t(0)); // Start with default color
		break;

	case 30:
		// Switch between default and alternate color
		par.InitializeProgram(program_t(10), step_t(2), step_t(0));
		break; 

	case 31:
		// Switch between alternate and default color
		par.InitializeProgram(program_t(10), step_t(2), step_t(1));
		break;

	case 40:
		// Chase left -> right
		par.InitializeProgram(program_t(10), step_t(nrOfPars), step_t(0), 
			selectedParIndex, selectedParIndex);
		break;

	case 41:
		// Chase right -> left
		par.InitializeProgram(program_t(10), step_t(nrOfPars), step_t(0),
			parameter_t(nrOfPars - selectedParIndex - 1),
			parameter_t(nrOfPars - selectedParIndex - 1));
		break;

	case 42:
		// Chase left -> right -> left
		nrOfSteps = (nrOfPars - 1) * 2;
		par.InitializeProgram(program_t(10), nrOfSteps, step_t(0),
			parameter_t(selectedParIndex), 
			parameter_t((nrOfSteps - selectedParIndex) % nrOfSteps));
		break;

	case 43:
		// Chase right -> left -> right
		par.InitializeProgram(program_t(10), step_t((nrOfPars - 1) * 2), step_t(0),
			parameter_t(nrOfPars - 1 - selectedParIndex),
			parameter_t(nrOfPars - 1 + selectedParIndex));
		break;

	case 50: 
		// Fade default color -> alternate color
		// Use only half the steps
		par.InitializeProgram(program_t(20), step_t(PAR_MAX_PAR_INTENSITIES), step_t(0));
		break;

	case 51:
		// Fade alternate color -> default color
		// Use only last half the steps (like program 20, but start halfway).
		par.InitializeProgram(program_t(21), step_t(PAR_MAX_PAR_INTENSITIES - 1), step_t(0),
			parameter_t(PAR_MAX_PAR_INTENSITIES - 1));
		break;

	case 52:
		// Fade default color -> alternate color -> default color
		par.InitializeProgram(program_t(20), step_t(PAR_MAX_PAR_INTENSITIES - 1), step_t(0));
		break;

	case 53:
		// Fade alternate color -> default color -> alternate color
		// Start halfway.
		par.InitializeProgram(program_t(20), 
			step_t(PAR_MAX_PAR_INTENSITIES * 2 - 2), step_t(PAR_MAX_PAR_INTENSITIES - 1));
		break;

	case 60:
		// Fade chase left -> Right
		par.InitializeProgram(program_t(30), step_t(nrOfPars * (PAR_MAX_PAR_INTENSITIES - 1)),
			step_t(0), 
			parameter_t(selectedParIndex), parameter_t(selectedParIndex), parameter_t(nrOfPars));
		break;

	case 61:
	  // Fade chase right -> left
		par.InitializeProgram(program_t(30), 
			step_t(nrOfPars * (PAR_MAX_PAR_INTENSITIES - 1)), step_t(0),
			parameter_t(nrOfPars - selectedParIndex - 1), 
			parameter_t(nrOfPars - selectedParIndex - 1), 
			parameter_t(nrOfPars));
		break;

	case 62:
		// Fade chase left -> right -> left
		nrOfSteps = (nrOfPars - 1) * 2;
		par.InitializeProgram(program_t(30), 
			step_t(nrOfSteps * (PAR_MAX_PAR_INTENSITIES - 1)), step_t(0),
			parameter_t(selectedParIndex), 
			parameter_t((nrOfSteps - selectedParIndex) % nrOfSteps), 
			parameter_t(nrOfSteps));
		break;

	case 63:
		// Fade chase right -> left -> right
		nrOfSteps = (nrOfPars - 1) * 2;
		par.InitializeProgram(program_t(30), 
			step_t(nrOfSteps * (PAR_MAX_PAR_INTENSITIES - 1)), step_t(0),
			parameter_t(nrOfPars - 1 - selectedParIndex), 
			parameter_t(nrOfPars - 1 + selectedParIndex), 
			parameter_t(nrOfSteps));
		break;

	case 70:
		// Rainbow colors, left -> right
		par.InitializeProgram(program_t(40), 
			step_t(PAR_MAX_PAR_INTENSITIES * PROGRAM_EXECUTER_RAINBOW_COLORS),
			step_t(PAR_MAX_PAR_INTENSITIES * (selectedParIndex % PROGRAM_EXECUTER_RAINBOW_COLORS)),
			parameter_t(-PAR_MAX_PAR_INTENSITIES)); // -MAX_PAR_INTENSITIES means decreasing a full color
																					// (no fade), left -> right
		break;

	case 71:
		// Rainbow colors, right -> left
		par.InitializeProgram(program_t(40), 
			step_t(PAR_MAX_PAR_INTENSITIES * PROGRAM_EXECUTER_RAINBOW_COLORS),
			step_t(PAR_MAX_PAR_INTENSITIES * 
			 (PROGRAM_EXECUTER_RAINBOW_COLORS - 1) - PAR_MAX_PAR_INTENSITIES * (selectedParIndex % PROGRAM_EXECUTER_RAINBOW_COLORS)),
			parameter_t(PAR_MAX_PAR_INTENSITIES)); // MAX_PAR_INTENSITIES means increasing a full color (no 
																	    			 // fade), right -> left
		break;

	case 72:
		// Rainbow colors + Fade, left -> right
		par.InitializeProgram(program_t(40), 
			step_t(PAR_MAX_PAR_INTENSITIES * PROGRAM_EXECUTER_RAINBOW_COLORS),
			step_t(PAR_MAX_PAR_INTENSITIES *
				PROGRAM_EXECUTER_RAINBOW_COLORS - 1 - PAR_MAX_PAR_INTENSITIES * (selectedParIndex % PROGRAM_EXECUTER_RAINBOW_COLORS)),
			parameter_t(1)); // 1 means left -> right
		break;

	case 73:
		// Rainbow colors + Fade, right -> left (note left->right->left or vice versa is not needed)
		par.InitializeProgram(program_t(40), 
			step_t(PAR_MAX_PAR_INTENSITIES * PROGRAM_EXECUTER_RAINBOW_COLORS),
			step_t(PAR_MAX_PAR_INTENSITIES * (selectedParIndex % PROGRAM_EXECUTER_RAINBOW_COLORS)),
			parameter_t(1)); // -1 means right -> left
		break;

	default:
		break;
	}
}


/* static */ void PresetCommand::CommandAllOff(Par& par)
{
	Irgbw color = par.GetDefaultColor();
	SetFixedIrgbw(par, color, 0, 0, 0, 0, 0);
	par.SetDefaultColorIrgbw(color);

	color = par.GetAlternateColor();
	SetFixedIrgbw(par, color, 0, 0, 0, 0, 0);
	par.SetAlternateColorIrgbw(color);
		
	LightSetup.AllOff();
}


/* static */ void PresetCommand::SetFixedIrgb(Par& par, Irgbw& color, intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue)
{
	color.SetIrgb(intensity, red, green, blue);
	par.SetProgram(0);
}


/* static */ void PresetCommand::SetFixedIrgbw(Par& par, Irgbw& color, intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue, intensity_t white)
{
	color.SetIrgbw(intensity, red, green, blue, white);
	par.SetProgram(0);
}
