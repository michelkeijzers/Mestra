#include "CommandParser.h"


// CommandParser.cpp
// Parser for commands.

#include <stdlib.h>
#include "AsciiCommandParser.h"
#include "PresetCommand.h"
#include "ClassNames.h"
#include <string.h>
#include <ctype.h>
#include "CharUtils.h"
#include "LightSetup.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "assert.h"


CommandParser::CommandParser()	
{
}


CommandParser::~CommandParser()
{
}


void CommandParser::Parse(Command& command)
{
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		if ((command.GetParBits() & (1 << parNumber)) > 0)
		{
			Par& par = LightSetup.GetPar(parNumber);

			SetDelayTime(command, par);
			SetDefaultColor(command, par);
			SetAlternateColor(command, par);
			SetPresetCommand(command);
			SetStroboTime(command);
		}
	}
}


void CommandParser::SetDelayTime(Command& command, Par& par)
{
	if (command.GetDelayTimeSet())
	{
		step_duration_t delayTime = command.GetDelayTime();
		par.SetStepDuration(delayTime);
		par.SetStepTime(millis() + delayTime);
	}
}

void CommandParser::SetDefaultColor(Command& command, Par& par)
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


void CommandParser::SetAlternateColor(Command& command, Par& par)
{
	if (command.GetAlternateColorSet())
	{
		Irgbw color;
		command.GetAlternateColor(color);

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


void CommandParser::SetPresetCommand(Command& command)
{
	if (command.GetPresetNumberSet())
	{
		PresetCommand presetCommand;
		presetCommand.Run(command.GetParBits(), command.GetPresetNumber());
	}
}


void CommandParser::SetStroboTime(Command& command)
{
	if (command.GetStrobeTimeSet())
	{
		LightSetup.GetStrobo().Start(command.GetParBits(), command.GetStroboTime());
	}
}
