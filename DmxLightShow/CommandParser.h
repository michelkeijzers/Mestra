#pragma once

#include "MestraTypes.h"
#include "Command.h"
#include "Par.h"

class CommandParser
{
public:
	CommandParser();
	~CommandParser();

	void Parse(Command& command);
	void SetDelayTime(Command& command, Par& par);
	void SetDefaultColor(Command& command, Par& par);
	void SetAlternateColor(Command& command, Par& par);
	void SetPresetCommand(Command& command);
	void SetStroboTime(Command& command);
};

