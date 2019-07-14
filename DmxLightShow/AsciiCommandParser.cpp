// CommandParser.cpp
// Parser for commands.

#ifdef _WINDOWS

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "AssertUtils.h"
#include "StringUtils.h"

#include "AsciiCommandParser.h"
#include "ParGroups.h"


struct Chars2ParBits
{
	const char* abbr;
	par_bits_t  parBits;
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
	_command.Clear();

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

			case 'B':
				_command.SetStrobeTimeSet(true);
				_currentIndex++;
				ParseStrobeTime();
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

			case 'C':
				_currentIndex++;
				ParseCommand();
				break;

			case 'H':
				_command.SetHoldSet(true);
				_currentIndex++;
				_command.SetHold(ParseBoolean());
				break;

			case 'O':
				_command.SetOnceSet(true);
				_currentIndex++;
				_command.SetOnce(ParseBoolean());
				break;

			case 'P':
				_command.SetPresetNumberSet(true);
				_currentIndex++;
				ParsePresetNumber();
				break;

			case 'S':
				_command.SetStepNumberSet(true);
				_currentIndex++;
				ParseStepNumber();
				break;

			case 'T':
				_command.SetDelayTimeSet(true);
				_currentIndex++;
				ParseDelayTime();
				break;

			default:
				_parseError = true;
				AssertUtils::MyAssert(false);
				break;
			}

			SkipWhitespace();
		}
	}
	else
	{
		_parseError = true;
		AssertUtils::MyAssert(false);
	}
}


void AsciiCommandParser::ParseCommand()
{
	SkipWhitespace();

	switch (_userCommand[_currentIndex])
	{
	case 'G':
		// Trigger mode
		_currentIndex++;

		_command.SetStepNumberSet(true);
		_command.SetLastStepNumber(true);
		_command.SetHoldSet(true);
		_command.SetHold(true);
		_command.SetOnceSet(true);
		_command.SetOnce(true);
		break;

	case 'L':
		_currentIndex++;

		_command.SetStepNumberSet(true);
		_command.SetStepNumber(0);
		_command.SetHoldSet(true);
		_command.SetHold(false);
		_command.SetOnceSet(true);
		_command.SetOnce(false);
		break;

	case 'O':
		_currentIndex++;

		_command.SetStepNumberSet(true);
		_command.SetStepNumber(0);
		_command.SetHoldSet(true);
		_command.SetHold(false);
		_command.SetOnceSet(true);
		_command.SetOnce(true);
		break;

	case 'R':
		_currentIndex++;

		_command.SetStepNumberSet(true);
		_command.SetStepNumber(0);
		_command.SetHoldSet(true);
		_command.SetHold(false);
		break;

	default:
		_parseError = true;
		AssertUtils::MyAssert(false);
		break;
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
		switch (_userCommand[_currentIndex])
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
			AssertUtils::MyAssert(false);
			break;
		}

		_currentIndex++;
	}

	return whiteIsPresent;
}


void AsciiCommandParser::ParsePresetNumber()
{
	SkipWhitespace();
	if (!_parseError)
	{
		_command.SetPresetNumberSet(true);
		_command.SetPresetNumber(preset_t(strtoul(&_userCommand[_currentIndex], nullptr, 0)));
		SkipUntilWhitespace();
	}
}


void AsciiCommandParser::ParseStepNumber()
{
	SkipWhitespace();
	if (!_parseError)
	{
		_command.SetStepNumberSet(true);
		if (_userCommand[_currentIndex] == 'L')
		{
			_command.SetLastStepNumber(true);
		}
		else
		{
			_command.SetStepNumber(preset_t(strtoul(&_userCommand[_currentIndex], nullptr, 0)));
		}
		
		SkipUntilWhitespace();
	}
}




void AsciiCommandParser::ParseStrobeTime()
{
	SkipWhitespace();
	if (!_parseError)
	{
		_command.SetStrobeTime(step_duration_t(strtoul(&_userCommand[_currentIndex], nullptr, 0)));
		_parseError |= _command.GetStrobeTime() == 0;
		SkipUntilWhitespace();
	}
}


void AsciiCommandParser::ParseDelayTime()
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
		AssertUtils::MyAssert(false);
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
		AssertUtils::MyAssert(false);
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


bool AsciiCommandParser::ParseBoolean()
{
	bool booleanValue = false;

	SkipWhitespace();

	if (_userCommand[_currentIndex] == '\0' || (_userCommand[_currentIndex] != '0' && _userCommand[_currentIndex] != '1'))
	{
		_parseError = true;
		AssertUtils::MyAssert(false);
	}
	else
	{
		booleanValue = _userCommand[_currentIndex] == '1';
	}

	_currentIndex++;

	SkipWhitespace();
	return booleanValue;
}


void AsciiCommandParser::ParseComma()
{
	if (_userCommand[_currentIndex] == '\0' || _userCommand[_currentIndex] != ',')
	{
		_parseError = true;
		AssertUtils::MyAssert(false);
	}

	_currentIndex++;
}


void AsciiCommandParser::ParseParBitsAndWhitespace()
{
	char abbr0 = _userCommand[_currentIndex];
	char abbr1 = _userCommand[_currentIndex + 1];
	_currentIndex += 2;

	bool ok;
	_command.SetParGroup(ParGroups::GetParGroup(abbr0, abbr1, &ok));
	_parseError &= ok;

	SkipWhitespace();
}


#endif // _WINDOWS