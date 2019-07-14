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
	static void SetStrobeTime(Command& command);
	static void SetPresetNumber(Command& command, Par& par);
	static void SetStepNumber(Command& command, Par& par);
	static void SetHold(Command& command, Par& par);
	static void SetOnce(Command& command, Par& par);
	static void SetDefaultColor(Command& command, Par& par);
	static void SetAlternateColor(Command& command, Par& par);
};

