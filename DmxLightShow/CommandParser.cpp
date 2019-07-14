#include "CommandParser.h"


// CommandParser.cpp
// Parser for commands.

#include "PresetCommand.h"
#include "ClassNames.h"
#include "LightSetup.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "ParGroups.h"
#include "MathUtils.h"


CommandParser::CommandParser()	
{
}


CommandParser::~CommandParser()
{
}


/* static */ void CommandParser::Parse(Command& command)
{
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		if ((ParGroups::GetParBits(command.GetParGroup()) & 1 << parNumber) > 0)
		{
			Par& par = LightSetup.GetPar(parNumber);

			SetDelayTime(command, par);
			SetStrobeTime(command);
			SetPresetNumber(command, par);
			SetStepNumber(command, par); // Must be after setting preset (to count step numbers first before setting last)
			SetHold(command, par);
			SetOnce(command, par);
			SetDefaultColor(command, par);
			SetAlternateColor(command, par);
		}
	}
}


/* static */ void CommandParser::SetDelayTime(Command& command, Par& par)
{
	if (command.GetDelayTimeSet())
	{
		step_duration_t delayTime = command.GetDelayTime();
		par.SetStepDuration(delayTime);
		par.SetStepTime(millis() + delayTime);
	}
}


/* static */ void CommandParser::SetStrobeTime(Command& command)
{
	if (command.GetStrobeTimeSet())
	{
		LightSetup.GetStrobo().Start(ParGroups::GetParBits(command.GetParGroup()), command.GetStrobeTime());
	}
}


/* static */ void CommandParser::SetPresetNumber(Command& command, Par& par)
{
	if (command.GetPresetNumberSet())
	{
		PresetCommand::Run(command.GetParGroup(), par, command.GetPresetNumber());
	}
}


/* static */ void CommandParser::SetStepNumber(Command& command, Par& par)
{
	// If a preset number has been set, set last step number if set.
	if (command.GetPresetNumberSet() && command.GetLastStepNumber())
	{
		par.SetStepNumber(step_t(MathUtils::Max(0, par.GetNrOfSteps() - 1)));
	}

	// Else, if a preset number is not set, check if the step number needs to be set.
	else if (!command.GetPresetNumberSet() && command.GetStepNumberSet())
	{
		par.SetStepNumber(command.GetStepNumber());
	}
}


/* static */ void CommandParser::SetHold(Command& command, Par& par)
{
	if (command.GetHoldSet())
	{
		par.SetHold(command.GetHold());
	}
}


/* static */ void CommandParser::SetOnce(Command& command, Par& par)
{
	if (command.GetOnceSet())
	{
		par.SetOnce(command.GetOnce());
	}
}


/* static */ void CommandParser::SetDefaultColor(Command& command, Par& par)
{
	if (command.GetDefaultColorSet())
	{
		Irgbw color = command.GetDefaultColor();

		if (command.GetDefaultColorWhiteUsed())
		{
			par.SetDefaultColorIrgbw(color);
		}
		else
		{
			par.SetDefaultColorIrgb(color);
		}
	}
}


/* static */ void CommandParser::SetAlternateColor(Command& command, Par& par)
{
	if (command.GetAlternateColorSet())
	{
		Irgbw color =  command.GetAlternateColor();

		if (command.GetAlternateColorWhiteUsed())
		{
			par.SetAlternateColorIrgbw(color);
		}
		else
		{
			par.SetAlternateColorIrgb(color);
		}
	}
}
