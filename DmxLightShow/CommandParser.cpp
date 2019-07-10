#include "CommandParser.h"


// CommandParser.cpp
// Parser for commands.

#include "PresetCommand.h"
#include "ClassNames.h"
#include "LightSetup.h"
#include HEADER_FILE(ARDUINO_CLASS)


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
		if ((command.GetParBits() & 1 << parNumber) > 0)
		{
			Par& par = LightSetup.GetPar(parNumber);

			if (command.GetActivateTriggerSet())
			{
				ActivateTrigger(par);
			}
			else
			{
				SetDelayTime(command, par);
				SetDefaultColor(command, par);
				SetAlternateColor(command, par);
				SetPresetCommand(command, parNumber);
				SetStroboTime(command);
				SetTriggerState(command, par); // Perform last (after setting preset)
			}
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


/* static */ void CommandParser::SetDefaultColor(Command& command, Par& par)
{
	if (command.GetDefaultColorSet())
	{
		Irgbw color;
		command.GetDefaultColor(color);

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
		Irgbw color;
		command.GetAlternateColor( color);

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



/* static */ void CommandParser::SetTriggerState(Command& command, Par& par)
{
	if (command.GetTriggerStateSet())
	{
		par.SetTriggerState(command.GetTriggerState() ? Par::ETriggerState::Waiting : Par::ETriggerState::Off);
	}
}


/* static */ void CommandParser::ActivateTrigger(Par& par)
{
	par.ActivateTrigger();
}



/* static */ void CommandParser::SetPresetCommand(Command& command, fixture_number_t fixtureNumber)
{
	if (command.GetPresetNumberSet())
	{
		PresetCommand::Run(fixtureNumber, command.GetParBits(), command.GetPresetNumber());
	}
}


/* static */ void CommandParser::SetStroboTime(Command& command)
{
	if (command.GetStroboTimeSet())
	{
		LightSetup.GetStrobo().Start(command.GetParBits(), command.GetStroboTime());
	}
}

