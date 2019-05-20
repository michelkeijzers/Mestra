// CommandParser.cpp
// Parser for commands.

#include <stdlib.h>
#include "CommandParser.h"
#include "PresetCommand.h"
#include "ClassNames.h"
#include <string.h>
#include <ctype.h>
#include "CharUtils.h"
#include HEADER_FILE(LIGHT_SETUP_CLASS)
#include HEADER_FILE(ARDUINO_CLASS)


CommandParser::CommandParser()
	: _command('\0'), 
		_currentIndex(0),
	  _parBits(0),
	  _parseError(false)
{
}


CommandParser::~CommandParser()
{
}


void CommandParser::Parse(char* command)
{
	_command = command;
	_currentIndex = 0;
	_parseError = false;

	SkipWhitespace();
	if (strlen(_command) > 0)
	{
		switch (_command[_currentIndex])
		{
		case 'A':
			_currentIndex++;
			ParseColorCommand(Par::Alternate);
			break;

		case 'D':
			_currentIndex++;
			ParseColorCommand(Par::Default);
			break;

		case 'P':
			_currentIndex++;
			ParsePresetCommand();
			break;

		case 'S':
			_currentIndex++;
			ParseStrobeCommand();
			break;

		case 'T':
			_currentIndex++;
			ParseDelayTimeCommand();
			break;

		default:
			_parseError = true;
			break;
		}
	}
	else
	{
		_parseError = true;
	}
}


void CommandParser::ParseColorCommand(Par::EActiveColor color)
{
	SkipWhitespace();
	if (!_parseError)
	{
		ParseParBits();
		if (!_parseError)
		{
			ParseWhitespace();
			if (!_parseError)
			{
				Irgbw irgbw;

				// Check for 0, than for commas, if so, assume (<Intensity>), <Red>, <Green>, <Blue> (,<White>)
				if (_command[_currentIndex] == '0')
				{
					// Black, but set intensity.
					irgbw.SetIntensity(255);
				}
				if ((strcspn(&(_command[_currentIndex]), ",")) < strlen(&(_command[_currentIndex])))
				{
					ParseIrgbwAsNumbers(irgbw);
				}
				else
				{
					ParseIrgbwAsCharacters(irgbw);
				}

				if (!_parseError)
				{
					SetIrgbw(color, irgbw);
				}
			}
		}
	}
}


// (<Intensity>), <Red>, <Green>, <Blue> (, <White>)
// 0<=Intensity<=255, 0 (%) <=Red, Green, Blue, White<=100 (%)
void CommandParser::ParseIrgbwAsNumbers(Irgbw& irgbw)
{
	// Read intensity.
	if (_command[_currentIndex] == ',')
	{
		// Intensity is not set -> 255
		irgbw.SetIntensity(255);
	}
	else
	{
		irgbw.SetIntensity((intensity_t) (strtoul(&(_command[_currentIndex]), NULL, 0)));
		SkipUntilComma();
	}
	
	// Read red.
	irgbw.SetRed((intensity_t) (strtoul(&(_command[_currentIndex]), NULL, 0) * MAX_PAR_INTENSITY / 100));
	SkipUntilComma();

	// Read green.
	irgbw.SetGreen((intensity_t) (strtoul(&(_command[_currentIndex]), NULL, 0) * MAX_PAR_INTENSITY / 100));
	SkipUntilComma();

	// Read blue.
	irgbw.SetBlue((intensity_t) (strtoul(&(_command[_currentIndex]), NULL, 0) * MAX_PAR_INTENSITY / 100));
	
	// Read white (optionally).
	if ((strcspn(&(_command[_currentIndex]), ",")) < strlen(&(_command[_currentIndex])))
	{
		// White is present
		SkipUntilComma();
		irgbw.SetWhite((intensity_t) (strtoul(&(_command[_currentIndex]), NULL, 0) * MAX_PAR_INTENSITY / 100));
	}
	else
	{
		// No white present, default is 0
		irgbw.SetWhite(0);
	}
}


void CommandParser::ParseIrgbwAsCharacters(Irgbw& irgbw)
{
	// Expect occurrences of i, r, g, b, w in any order
	while (_command[_currentIndex] != '\0')
	{
		switch (CharUtils::ToUpper(_command[_currentIndex]))
		{
		case 'I':
			irgbw.SetIntensity(MAX_INTENSITY);
			break;

		case 'R':
			irgbw.SetRed(MAX_PAR_INTENSITY);
			break;

		case 'G':
			irgbw.SetGreen(MAX_PAR_INTENSITY);
			break;

		case 'B':
			irgbw.SetBlue(MAX_PAR_INTENSITY);
			break;

		case 'W':
			irgbw.SetWhite(MAX_PAR_INTENSITY);
			break;

		default:
			_parseError = true;
			break;
		}

		_currentIndex++;
	}
}


void CommandParser::ParsePresetCommand()
{
	ParseWhitespace();
	if (!_parseError)
	{
		ParseParBits();
		if (!_parseError)
		{
			ParseWhitespace();
			if (!_parseError)
			{
				preset_t presetNumber = (preset_t) (strtoul(&(_command[_currentIndex]), NULL, 0));
				if (presetNumber != 0)
				{
					PresetCommand command;
					command.Run(_parBits, presetNumber);
				}
				else
				{
					_parseError = true;
				}
			}
		}
	}
}


void CommandParser::ParseStrobeCommand()
{
	ParseWhitespace();
	if (!_parseError)
	{
		ParseParBits();
		if (!_parseError)
		{
			step_time_t duration = strtoul(&(_command[_currentIndex]), NULL, 0);
			if (duration > 0)
			{
				LightSetup.GetStrobo().Start(_parBits, duration);
			}
			else
			{
				_parseError = true;
			}
		}
	}
}


void CommandParser::ParseDelayTimeCommand()
{
	ParseWhitespace();
	if (!_parseError)
	{
		ParseParBits();
		if (!_parseError)
		{
			ParseWhitespace();
			if (!_parseError)
			{
				step_time_t delay = strtoul(&(_command[_currentIndex]), NULL, 0);
				if (delay > 0)
				{
					SetDelay(delay);
				}
				else
				{
					_parseError = true;
				}
			}
		}
	}
}


// Skip one or more whitespaces
void CommandParser::ParseWhitespace()
{
	if (!isspace(_command[_currentIndex]))
	{
		_parseError = true;
		_command[_currentIndex] = '\0'; // Stop parsing
	}
	else
	{
		while ((_command[_currentIndex] != '\0') && isspace(_command[_currentIndex]))
		{
			_currentIndex++;
		}
	}

	if (_command[_currentIndex] == '\0')
	{
		_parseError = true;
	}
}


void CommandParser::SkipWhitespace()
{
	while ((_command[_currentIndex] != '\0') && isspace(_command[_currentIndex]))
	{
		_currentIndex++;
	}
}


void CommandParser::SkipUntilComma()
{
	while ((_command[_currentIndex] != '\0') && (_command[_currentIndex] != ','))
	{
		_currentIndex++;
	}

	if (_command[_currentIndex] == '\0')
	{
		_parseError = true;
	}
	else
	{
		_currentIndex++; // Skip comma
	}
}


void CommandParser::ParseParBits()
{
  _parBits = 0; // Use 32 bits although 16 are used because of 16/32 bit conversion for <</+ operations below
	uint8_t parBitsLength = 0;

  switch (CharUtils::ToUpper(_command[_currentIndex]))
  {
  case 'A':
    switch (CharUtils::ToUpper((_command[_currentIndex + 1])))
    {
		case ' ': _parBits = (0b11111111 << 8) + 0b11111100; parBitsLength = 1; break;
    }
    break;

  case 'B':
    switch (CharUtils::ToUpper((_command[_currentIndex + 1])))
    {
    case ' ': _parBits = (0b00000000 << 8) + 0b00110000; parBitsLength = 1; break;
    case 'D': _parBits = (0b00000000 << 8) + 0b11110000; parBitsLength = 2; break;
    case 'L': _parBits = (0b00000000 << 8) + 0b00100000; parBitsLength = 2; break;
    case 'R': _parBits = (0b00000000 << 8) + 0b00010000; parBitsLength = 2; break;
    }
    break;

  case 'D':
    switch (CharUtils::ToUpper((_command[_currentIndex + 1])))
    {
    case ' ': _parBits = (0b00000000 << 8) + 0b11000000; parBitsLength = 1; break;
    case 'L': _parBits = (0b00000000 << 8) + 0b10000000; parBitsLength = 2; break;
    case 'R': _parBits = (0b00000000 << 8) + 0b01000000; parBitsLength = 2; break;
    }
    break;

  case 'E':
    switch (CharUtils::ToUpper((_command[_currentIndex + 1])))
    {
    case ' ': _parBits = (0b00000000 << 8) + 0b00001100; parBitsLength = 1; break;
    case 'L': _parBits = (0b00000000 << 8) + 0b00001000; parBitsLength = 2; break;
    case 'R': _parBits = (0b00000000 << 8) + 0b00000100; parBitsLength = 2; break;
    case 'E': _parBits = (0b01010101 << 8) + 0b01010100; parBitsLength = 2; break;
    }
    break;

  case 'F':
    switch (CharUtils::ToUpper((_command[_currentIndex + 1])))
    {
		case ' ': _parBits = (0b11111111 << 8) + 0b00000000; parBitsLength = 1; break;
    case 'A': _parBits = (0b11111111 << 8) + 0b00000000; parBitsLength = 2; break;
    case 'O': _parBits = (0b10000001 << 8) + 0b00000000; parBitsLength = 2; break;
    case 'I': _parBits = (0b01111110 << 8) + 0b00000000; parBitsLength = 2; break;
    case 'C': _parBits = (0b10011001 << 8) + 0b00000000; parBitsLength = 2; break;
    case 'E': _parBits = (0b01100110 << 8) + 0b00000000; parBitsLength = 2; break;
    case 'L':
      switch (CharUtils::ToUpper((_command[_currentIndex + 2])))
      {
      case ' ': _parBits = (0b11110000 << 8) + 0b00000000; parBitsLength = 2; break;
      case 'C': _parBits = (0b10010000 << 8) + 0b00000000; parBitsLength = 3; break;
      case 'E': _parBits = (0b01100000 << 8) + 0b00000000; parBitsLength = 3; break;
      case '1': _parBits = (0b10000000 << 8) + 0b00000000; parBitsLength = 3; break;
      case '2': _parBits = (0b01000000 << 8) + 0b00000000; parBitsLength = 3; break;
      case '3': _parBits = (0b00100000 << 8) + 0b00000000; parBitsLength = 3; break;
      case '4': _parBits = (0b00010000 << 8) + 0b00000000; parBitsLength = 3; break;
      }
      break;

    case 'R':
      switch (CharUtils::ToUpper((_command[_currentIndex + 2])))
      {
      case ' ': _parBits = (0b00001111 << 8) + 0b00000000; parBitsLength = 2; break;
      case 'C': _parBits = (0b00001001 << 8) + 0b00000000; parBitsLength = 3; break;
      case 'E': _parBits = (0b00000110 << 8) + 0b00000000; parBitsLength = 3; break;
      case '1': _parBits = (0b00001000 << 8) + 0b00000000; parBitsLength = 3; break;
      case '2': _parBits = (0b00000100 << 8) + 0b00000000; parBitsLength = 3; break;
      case '3': _parBits = (0b00000010 << 8) + 0b00000000; parBitsLength = 3; break;
      case '4': _parBits = (0b00000001 << 8) + 0b00000000; parBitsLength = 3; break;
      }
      break;
    }
    break;

  case 'N':
    switch (CharUtils::ToUpper((_command[_currentIndex + 1])))
    {
    case 'F':
      switch (CharUtils::ToUpper((_command[_currentIndex + 2])))
      {
			case ' ': _parBits = (0b00000000 << 8) + 0b11110000; parBitsLength = 2; break;
			case 'E': _parBits = (0b00000000 << 8) + 0b11111100; parBitsLength = 3; break;
			}
      break;
    }
    break;

  case 'U':
    switch (CharUtils::ToUpper((_command[_currentIndex + 1])))
    {
    case 'N':  _parBits = (0b01010101 << 8) + 0b01010100; parBitsLength = 2; break;
      break;
    }
    break;
  }

	_currentIndex += parBitsLength;

	_parseError &= (_parBits == 0);
}


void CommandParser::SetDelay(step_time_t delay)
{
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		if ((_parBits & (0x8000 >> parNumber)) > 0)
		{
			Par& par = LightSetup.GetPar(parNumber);
			par.SetStepDuration(delay);
			par.SetStepTime(millis() + delay);
		}
	}
}


void CommandParser::SetIrgbw(Par::EActiveColor color, Irgbw& irgbw)
{
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		if ((_parBits & (0x8000 >> parNumber)) > 0)
		{
			Par& par = LightSetup.GetPar(parNumber);
			Irgbw* irgbwTarget = NULL;
			switch (color)
			{
			case Par::EActiveColor::Default:
				irgbwTarget = &(par.GetDefaultColor());
				break;

			case Par::EActiveColor::Alternate:
				irgbwTarget = &(par.GetAlternateColor());
				break;

			default:
				//TODO: error
				break;
			}

			if (irgbw.GetWhite() == 0)
			{
				irgbwTarget->SetIrgb(irgbw);
			}
			else
			{
				irgbwTarget->SetIrgbw(irgbw);
			}
		}
	}
}
