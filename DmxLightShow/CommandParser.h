#pragma once

#include "Command.h"
#include "Par.h"

class CommandParser
{
public:
	static void Parse(Command& command);

private:
	CommandParser();
	~CommandParser();

	static void SetDelayTime(Command& command, Par& par);
	static void SetDefaultColor(Command& command, Par& par);
	static void SetAlternateColor(Command& command, Par& par);
	static void SetTriggerState(Command& command, Par& par);
	static void ActivateTrigger(Par& par);
	static void SetPresetCommand(Command& command, fixture_number_t fixtureNumber);
	static void SetStroboTime(Command& command);
};

