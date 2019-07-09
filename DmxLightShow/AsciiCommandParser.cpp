// CommandParser.cpp
// Parser for commands.

#ifdef _WINDOWS

#include <stdlib.h>
#include "AsciiCommandParser.h"
#include <string.h>
#include <ctype.h>
#include "CharUtils.h"


struct Chars2ParBits
{
	const char* abbr;
	par_bits_t  parBits;
};


Chars2ParBits Chars2ParBitsMapping[] =
{
	{ "AA", PAR_AA },
	{ "AC", PAR_AC },
	{ "AE", PAR_AE },
	{ "AL", PAR_AL },
	{ "AR", PAR_AR },
	{ "BA", PAR_BA },
	{ "BC", PAR_BC },
	{ "BL", PAR_BL },
	{ "BR", PAR_BR },
	{ "DA", PAR_DA },
	{ "DL", PAR_DL },
	{ "DR", PAR_DR },
	{ "EA", PAR_EA },
	{ "EL", PAR_EL },
	{ "ER", PAR_ER },
	{ "FA", PAR_FA },
	{ "FC", PAR_FC },
	{ "FI", PAR_FI },
	{ "FM", PAR_FM },
	{ "FO", PAR_FO },
	{ "L1", PAR_L1 },
	{ "L2", PAR_L2 },
	{ "L3", PAR_L3 },
	{ "L4", PAR_L4 },
	{ "LA", PAR_LA },
	{ "LI", PAR_LI },
	{ "LO", PAR_LO },
	{ "NA", PAR_NA },
	{ "NL", PAR_NL },
	{ "NR", PAR_NR },
	{ "R1", PAR_R1 },
	{ "R2", PAR_R2 },
	{ "R3", PAR_R3 },
	{ "R4", PAR_R4 },
	{ "RA", PAR_RA },
	{ "RI", PAR_RI },
	{ "RO", PAR_RO }
};


AsciiCommandParser::AsciiCommandParser()
	: _userCommand(nullptr), 
		_currentIndex(0),
	  _parseError(false)
{
}


AsciiCommandParser::~AsciiCommandParser()
{
}


Command& AsciiCommandParser::GetCommand()
{
	return _command;
}


void AsciiCommandParser::Parse(char* command)
{
	_userCommand = command;
	_currentIndex = 0;
	_parseError = false;

	SkipWhitespace();
	if (strlen(_userCommand) > 0)
	{
		ParseParBitsAndWhitespace();
	
		while (_currentIndex < strlen(_userCommand))
		{
			switch (_userCommand[_currentIndex])
			{
			case 'A':
			{
				_command.SetAlternateColorSet(true);
				_currentIndex++;
				Irgbw irgbw;
				_command.SetAlternateColorWhiteUsed(ParseColorCommand(irgbw));
				_command.SetAlternateColor(irgbw);
			}
			break;

			case 'D':
			{
				_command.SetDefaultColorSet(true);
				_currentIndex++;
				Irgbw irgbw;
				_command.SetDefaultColorWhiteUsed(ParseColorCommand(irgbw));
				_command.SetDefaultColor(irgbw);
			}
			break;

			case 'G':
			{
				_command.SetTriggerState(true);
				_currentIndex++;
			}
			break;

			case '!':
			{
				_command.SetActivateTrigger(true);
				_currentIndex++;
			}

			case 'P':
				_command.SetPresetNumberSet(true);
				_currentIndex++;
				ParsePresetCommand();
				break;

			case 'S':
				_command.SetStroboTimeSet(true);
				_currentIndex++;
				ParseStroboCommand();
				break;

			case 'T':
				_command.SetDelayTimeSet(true);
				_currentIndex++;
				ParseDelayTimeCommand();
				break;

			default:
				_parseError = true;
				break;
			}

			SkipWhitespace();
		}
	}
	else
	{
		_parseError = true;
	}
}


bool AsciiCommandParser::ParseColorCommand(Irgbw& irgbw)
{
	bool whiteIsPresent = false;

	SkipWhitespace();
	if (!_parseError)
	{
		// Check for 0, than for commas, if so, assume (<Intensity>), <Red>, <Green>, <Blue> (,<White>)
		if (_userCommand[_currentIndex] == '0')
		{
			// Black, but set intensity.
			irgbw.SetIntensity(255U);
		}

		if (strcspn(&_userCommand[_currentIndex], ",") < strlen(&_userCommand[_currentIndex]))
		{
			whiteIsPresent = ParseIrgbwAsNumbers(irgbw);
		}
		else
		{
			whiteIsPresent = ParseIrgbwAsCharacters(irgbw);
		}
	}

	return whiteIsPresent;
}


// (<Intensity>), <Red>, <Green>, <Blue> (, <White>)
// 0<=Intensity<=255, 0 (%) <=Red, Green, Blue, White<=100 (%)
bool AsciiCommandParser::ParseIrgbwAsNumbers(Irgbw& irgbw)
{
	bool whiteIsPresent;

	// Read intensity.
	if (_userCommand[_currentIndex] == ',')
	{
		// Intensity is not set -> 255
		irgbw.SetIntensity(255);
	}
	else
	{
		irgbw.SetIntensity(intensity_t(strtoul(&_userCommand[_currentIndex], nullptr, 0)));
		SkipDigits();
	}

	ParseComma();
	SkipWhitespace();

	// Read red.
	irgbw.SetRed(intensity_t(strtoul(&_userCommand[_currentIndex], nullptr, 0)));
	SkipDigits();
	SkipWhitespace();
	ParseComma();
	SkipWhitespace();

	// Read green.
	irgbw.SetGreen(intensity_t(strtoul(&_userCommand[_currentIndex], nullptr, 0)));
	SkipDigits();
	SkipWhitespace();
	ParseComma();
	SkipWhitespace();

	// Read blue.
	irgbw.SetBlue(intensity_t(strtoul(&_userCommand[_currentIndex], nullptr, 0)));
	SkipDigits();
	SkipWhitespace();

	// Read white (optionally).
	if (_userCommand[_currentIndex] == ',')
	{
		whiteIsPresent = true;
		ParseComma();
		SkipWhitespace();
		irgbw.SetWhite(intensity_t(strtoul(&_userCommand[_currentIndex], nullptr, 0) * PAR_MAX_PAR_INTENSITY / 255));
		SkipDigits();
	}
	else
	{
		whiteIsPresent = false;
		irgbw.SetWhite(0);
	}

	SkipWhitespace();

	return whiteIsPresent;
}


bool AsciiCommandParser::ParseIrgbwAsCharacters(Irgbw& irgbw)
{
	bool whiteIsPresent = false;

	// Expect occurrences of i, r, g, b, w in any order
	while (_userCommand[_currentIndex] != '\0' && !isblank(_userCommand[_currentIndex]))
	{
		switch (CharUtils::ToUpper(_userCommand[_currentIndex]))
		{
		case 'I':
			irgbw.SetIntensity(PAR_MAX_INTENSITY);
			break;

		case 'R':
			irgbw.SetRed(PAR_MAX_PAR_INTENSITY);
			break;

		case 'G':
			irgbw.SetGreen(PAR_MAX_PAR_INTENSITY);
			break;

		case 'B':
			irgbw.SetBlue(PAR_MAX_PAR_INTENSITY);
			break;

		case 'W':
			irgbw.SetWhite(PAR_MAX_PAR_INTENSITY);
			whiteIsPresent = true;
			break;

		default:
			_parseError = true;
			break;
		}

		_currentIndex++;
	}

	return whiteIsPresent;
}


void AsciiCommandParser::ParsePresetCommand()
{
	SkipWhitespace();
	if (!_parseError)
	{
		_command.SetPresetNumberSet(true);
		_command.SetPresetNumber(preset_t(strtoul(&_userCommand[_currentIndex], nullptr, 0)));
		SkipUntilWhitespace();
	}
}


void AsciiCommandParser::ParseStroboCommand()
{
	SkipWhitespace();
	if (!_parseError)
	{
		_command.SetStroboTime(step_duration_t(strtoul(&_userCommand[_currentIndex], nullptr, 0)));
		_parseError |= _command.GetStroboTime() == 0;
		SkipUntilWhitespace();
	}
}


void AsciiCommandParser::ParseDelayTimeCommand()
{
	SkipWhitespace();
	if (!_parseError)
	{
		_command.SetDelayTime(step_duration_t(strtoul(&_userCommand[_currentIndex], nullptr, 0)));
		_parseError |= _command.GetDelayTime() == 0;
		SkipUntilWhitespace();
	}
}


// Skip one or more whitespaces
void AsciiCommandParser::ParseWhitespace()
{
	if (!isspace(_userCommand[_currentIndex]))
	{
		_parseError = true;
		_userCommand[_currentIndex] = '\0'; // Stop parsing
	}
	else
	{
		while (_userCommand[_currentIndex] != '\0' && isspace(_userCommand[_currentIndex]))
		{
			_currentIndex++;
		}
	}

	if (_userCommand[_currentIndex] == '\0')
	{
		_parseError = true;
	}
}


void AsciiCommandParser::SkipWhitespace()
{
	while (_userCommand[_currentIndex] != '\0' && isspace(_userCommand[_currentIndex]))
	{
		_currentIndex++;
	}
}


void AsciiCommandParser::SkipUntilWhitespace()
{
	while (_userCommand[_currentIndex] != '\0' && !isblank(_userCommand[_currentIndex]))
	{
		_currentIndex++;
	}

	if (_userCommand[_currentIndex] == '\0')
	{
		//_parseError = true;
	}
	else
	{
		_currentIndex++; // Skip comma
	}
}


void AsciiCommandParser::SkipDigits()
{
	while (_userCommand[_currentIndex] != '\0' && isdigit(_userCommand[_currentIndex]))
	{
		_currentIndex++;
	}
}


void AsciiCommandParser::ParseComma()
{
	if (_userCommand[_currentIndex] == '\0' || _userCommand[_currentIndex] != ',')
	{
		_parseError = true;
	}

	_currentIndex++;
}


void AsciiCommandParser::ParseParBitsAndWhitespace()
{
	char abbr0 = _userCommand[_currentIndex];
	char abbr1 = _userCommand[_currentIndex + 1];
	_currentIndex += 2;

	for (uint8_t index = 0; index < sizeof Chars2ParBitsMapping / sizeof(Chars2ParBits); index++)
	{
		Chars2ParBits& mapping = Chars2ParBitsMapping[index];
		if (abbr0 == mapping.abbr[0] &&
			  abbr1 == mapping.abbr[1])
		{
			_command.SetParBits(mapping.parBits);
		}
	}

	_parseError |= _command.GetParBits() == 0;

	SkipWhitespace();
}


#endif // _WINDOWS