// CommandParser.h 

#ifdef _WINDOWS

#pragma once

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

	void ParsePresetCommand();

	void ParseStroboCommand();

	void ParseDelayTimeCommand();

	void ParseParBitsAndWhitespace();

	void ParseWhitespace();
	void SkipWhitespace();

	void SkipUntilWhitespace();
	void SkipDigits();

	bool ParseBoolean();
	void ParseComma();
};

#endif // _WINDOWS