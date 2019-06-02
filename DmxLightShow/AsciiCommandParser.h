// CommandParser.h 

#ifdef _WINDOWS

#pragma once

#include <string.h>
#include "ClassNames.h"
#include "Par.h"
#include "Command.h"


class AsciiCommandParser
{
public:
	AsciiCommandParser();
	~AsciiCommandParser();

	void Parse(char* command);

	Command& GetCommand();

private:
	// Current index within string
	Command _command;

	char* _userCommand;

	uint8_t _currentIndex;

	bool _parseError;

	bool ParseColorCommand(Irgbw& irgbw);

	bool ParseIrgbwAsNumbers(Irgbw& irgwb);
	bool ParseIrgbwAsCharacters(Irgbw& irgbw);

	void SetIrgbw(Par::EActiveColor color, Irgbw& irgbw);

	void SetColor(Irgbw& irgbw, Irgbw& irgbwTarget);

	void ParsePresetCommand();

	void ParseStrobeCommand();

	void ParseDelayTimeCommand();

	void ParseParBitsAndWhitespace();

	void ParseWhitespace();
	void SkipWhitespace();

	void SkipUntilWhitespace();
	void SkipUntilComma();

	void SetDelay(step_time_t delay);
};

#endif // _WINDOWS