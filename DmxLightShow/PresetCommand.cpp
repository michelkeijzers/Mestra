// PresetCommand.cpp
// Command for changing a default color property of a Par.

#include "PresetCommand.h"
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
		if ((parBits & (0x8000 >> parNumber)) > 0)
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
	step_t nrOfSteps = 1;
	
	switch (presetNumber)
	{
	case 10: 
		// Default color -> Alternate color
		par.GetAlternateColor() = par.GetDefaultColor();
		break;

	case 11:
		// Alternate color -> Default color
		par.GetDefaultColor() = par.GetAlternateColor();
		break;

	case 12:
		{
			// Default color <-> Alternate color
		  Irgbw& defaultColor = par.GetDefaultColor();
			par.GetDefaultColor() = par.GetAlternateColor();
			par.GetAlternateColor() = defaultColor;
		}
		break;

	case 13:
		// Default color -> Actual color
		par.WriteIrgb(par.GetDefaultColor());
		break;

	case 14:
		{
			// Actual color -> Default color
			Irgbw ActualColor;
			par.GetDefaultColor() = par.GetActualColor(ActualColor);
		}
		break;

	case 15:
		// Default color <-> Actual color
	  {
			Irgbw actualColor;
		  par.GetActualColor(actualColor);
			par.WriteIrgb(par.GetDefaultColor());
			par.GetDefaultColor() = actualColor;
		}
		break;

	case 16:
		// Alternate color -> Actual color
		par.WriteIrgb(par.GetAlternateColor());
		break;

	case 17:
		// Actual color -> Alternate color
		{
			Irgbw actualColor;
			par.GetAlternateColor() = par.GetActualColor(actualColor);
		}
		break;

	case 18:
		// Alternate color <-> Actual color
		{
			Irgbw actualColor;
			par.GetActualColor(actualColor);
			par.WriteIrgb(par.GetAlternateColor());
			par.GetAlternateColor() = actualColor;
		}
		break;
		
	case 20:
		// Solid (default color)
		par.InitializeProgram(0, nrOfSteps, 0); // Start with default color
		break;

	case 30:
		// Switch between default and alternate color
		par.InitializeProgram(10, 2, 0);
		break;

	case 31:
		// Switch between alternate and default color
		par.InitializeProgram(10, 2, 1);
		break;

	case 40:
		// Chase left -> right
		par.InitializeProgram(10, nrOfPars, 0, selectedParIndex, selectedParIndex);
		break;

	case 41:
		// Chase right -> left
		par.InitializeProgram(10, nrOfPars, 0, 
			nrOfPars - selectedParIndex - 1, nrOfPars - selectedParIndex - 1);
		break;

	case 42:
		// Chase left -> right -> left
		nrOfSteps = (nrOfPars - 1) * 2;
		par.InitializeProgram(10, nrOfSteps, 0, 
			selectedParIndex, (nrOfSteps - selectedParIndex) % nrOfSteps);
		break;

	case 43:
		// Chase right -> left -> right
		par.InitializeProgram(10, (nrOfPars - 1) * 2, 0, 
			nrOfPars - 1 - selectedParIndex, nrOfPars - 1 + selectedParIndex);
		break;

	case 50: 
		// Fade default color -> alternate color
		// Use only half the steps
		par.InitializeProgram(20, MAX_PAR_INTENSITIES, 0);
		break;

	case 51:
		// Fade alternate color -> default color
		// Use only last half the steps (like program 20, but start halfway).
		par.InitializeProgram(21, MAX_PAR_INTENSITIES - 1, 0, MAX_PAR_INTENSITIES - 1, 0);
		break;

	case 52:
		// Fade default color -> alternate color -> default color
		par.InitializeProgram(20, 2 * (MAX_PAR_INTENSITIES * 1), 0);
		break;

	case 53:
		// Fade alternate color -> default color -> alternate color
		// Start halfway.
		par.InitializeProgram(20, MAX_PAR_INTENSITIES * 2 - 2, MAX_PAR_INTENSITIES - 1);
		break;

	case 60:
		// Fade chase left -> Right
		par.InitializeProgram(30, nrOfPars * (MAX_PAR_INTENSITIES - 1), 0, 
			selectedParIndex, selectedParIndex, nrOfPars);
		break;

	case 61:
	  // Fade chase right -> left
		par.InitializeProgram(30, nrOfPars * (MAX_PAR_INTENSITIES - 1), 0,
			nrOfPars - selectedParIndex - 1, nrOfPars - selectedParIndex - 1, nrOfPars);
		break;

	case 62:
		// Fade chase left -> right -> left
		nrOfSteps = (nrOfPars - 1) * 2;
		par.InitializeProgram(30, nrOfSteps * (MAX_PAR_INTENSITIES - 1), 0,
			selectedParIndex, (nrOfSteps - selectedParIndex) % nrOfSteps, nrOfPars);
		break;

	case 63:
		// Fade chase right -> left -> right
		nrOfSteps = (nrOfPars - 1) * 2;
		par.InitializeProgram(30, nrOfSteps * (MAX_PAR_INTENSITIES - 1), 0,
			nrOfPars - 1 - selectedParIndex, nrOfPars - 1 + selectedParIndex, nrOfSteps);
		break;

	default:
		break;
	}
}


void PresetCommand::CommandAllOff(Par& par)
{
	SetFixedIrgb(par, par.GetDefaultColor(), MAX_INTENSITY, 0, 0, 0);
	SetFixedIrgb(par, par.GetAlternateColor(), MAX_INTENSITY, 0, 0, 0);
	//TODO: Strobo off
}


void PresetCommand::SetFixedIrgb(Par &par, Irgbw& color, uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue)
{
	color.SetIrgb(intensity, red, green, blue);
	par.SetProgram(0);
}


void PresetCommand::SetFixedIrgbw(Par& par, Irgbw& color, uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
{
	color.SetIrgbw(intensity, red, green, blue, white);
	par.SetProgram(0);
}
