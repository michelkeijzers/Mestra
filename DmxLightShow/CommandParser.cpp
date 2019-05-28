// CommandParser.cpp
// Parser for commands.

#include <stdlib.h>
#include "CommandParser.h"
#include "PresetCommand.h"
#include "ClassNames.h"
#include <string.h>
#include <ctype.h>
#include "CharUtils.h"
#include "LightSetup.h"
#include HEADER_FILE(ARDUINO_CLASS)


//                                                   LED Bar   Ego  Banners      
//                                                             Risers      Drums  Front Left  Front Right
//                                                   BL  BC BR EL ER NL NR DL DR  FL FL FL FL FR FR FR FR
//                                                                                4  3  2  1  1  2  3  4
// Byte 3--------------------3  2--------------------2   1-------------- -----1   0--------------------0
// Bit  7  6  5  4  3  2  1  0  7  6  5  4  3  2  1  0   7  6  5  4  3  2  1  0   7  6  5  4  3  2  1  0
// Index   30 29 28 27 26 25 24 23 22 21 20 19 18 17 16  15 14 13 12 11 10 9  8   7  6  5  4  3  2  1  0
// Fixture Group      Fixture Part                   Set
// ------------------ ------------------------------ -------- ----- ----- -----  ----------- -----------
// A All Groups       A All                          1   1  1  1  1  1  1  1  1   1  1  1  1  1  1  1  1
//                    C Center                       0   1  0  0  0  0  0  0  0   0  1  1  0  0  1  1  0  
//                    E All Except Ego Risers        1   1  1  0  0  1  1  1  1   1  1  1  1  1  1  1  1
//                    L Left                         1   0  0  0  0  1  0  1  0   1  1  1  1  0  0  0  0  
//                    R Right                        0   0  1  0  0  0  1  0  1   0  0  0  0  1  1  1  1  
// B Led Bar          A All                          1   1  1  0  0  0  0  0  0   0  0  0  0  0  0  0  0  
//                    C Center                       0   1  0  0  0  0  0  0  0   0  0  0  0  0  0  0  0  
//                    L Left                         1   0  0  0  0  0  0  0  0   0  0  0  0  0  0  0  0  
//                    R Right                        0   0  1  0  0  0  0  0  0   0  0  0  0  0  0  0  0  
// D Drums            A All                          0   0  0  1  1  0  0  0  0   0  0  0  0  0  0  0  0  
//                    L Left                         0   0  0  1  0  0  0  0  0   0  0  0  0  0  0  0  0  
//                    R Right                        0   0  0  0  1  0  0  0  0   0  0  0  0  0  0  0  0  
// E Ego Risers       A All                          0   0  0  1  1  0  0  0  0   0  0  0  0  0  0  0  0  
//                    L Left                         0   0  0  1  0  0  0  0  0   0  0  0  0  0  0  0  0  
//                    R Right                        0   0  0  0  1  0  0  0  0   0  0  0  0  0  0  0  0  
// F Front            A All                          0   0  0  0  0  0  0  0  0   1  1  1  1  1  1  1  1  
//                    C Corners                      0   0  0  0  0  0  0  0  0   1  0  0  1  1  0  0  1  
//                    M Middle                       0   0  0  0  0  0  0  0  0   0  1  1  0  0  1  1  0  
//                    I Inner                        0   0  0  0  0  0  0  0  0   0  1  1  1  1  1  1  0  
//                    O Outer                        0   0  0  0  0  0  0  0  0   1  0  0  0  0  0  0  1  
// L (Front) Left     1 Inside                       0   0  0  0  0  0  0  0  0   0  0  0  1  0  0  0  1  
//                    2                              0   0  0  0  0  0  0  0  0   0  0  1  0  0  0  0  0  
//                    3                              0   0  0  0  0  0  0  0  0   0  1  0  0  0  0  0  0  
//                    4 Outside                      0   0  0  0  0  0  0  0  0   1  0  0  0  0  0  0  0  
//                    A All Left                     0   0  0  0  0  0  0  0  0   1  1  1  1  0  0  0  0  
//                    I Inner                        0   0  0  0  0  0  0  0  0   0  1  1  0  0  0  0  0  
//                    O Outer                        0   0  0  0  0  0  0  0  0   1  0  0  1  0  0  0  0  
// N Banner           A All                          0   0  0  0  0  1  1  0  0   0  0  0  0  0  0  0  0  
//                    L Left                         0   0  0  0  0  1  0  0  0   0  0  0  0  0  0  0  0  
//                    R Right                        0   0  0  0  0  0  1  0  0   0  0  0  0  0  0  0  0  
// R (Front) Right    1 Inside                       0   0  0  0  0  0  0  0  0   0  0  0  0  1  0  0  0  
//                    2                              0   0  0  0  0  0  0  0  0   0  0  0  0  0  1  0  0  
//                    3                              0   0  0  0  0  0  0  0  0   0  0  0  0  0  0  1  0  
//                    4 Outside                      0   0  0  0  0  0  0  0  0   0  0  0  0  0  0  0  1  
//                    A All                          0   0  0  0  0  0  0  0  0   0  0  0  0  1  1  1  1  
//                    I Inner                        0   0  0  0  0  0  0  0  0   0  0  0  0  0  1  1  0  
//                    O Outer                        0   0  0  0  0  0  0  0  0   0  0  0  0  1  0  0  1  


const par_bits_t PAR_R4 = 1 << 0;
const par_bits_t PAR_R3 = 1 << 1;
const par_bits_t PAR_R2 = 1 << 2;
const par_bits_t PAR_R1 = 1 << 3;
const par_bits_t PAR_L1 = 1 << 4;
const par_bits_t PAR_L2 = 1 << 5;
const par_bits_t PAR_L3 = 1 << 6;
const par_bits_t PAR_L4 = 1 << 7;
const par_bits_t PAR_DR = 1 << 8;
const par_bits_t PAR_DL = 1 << 9;
const par_bits_t PAR_NR = 1 << 10;
const par_bits_t PAR_NL = 1 << 11;
const par_bits_t PAR_ER = 1 << 12;
const par_bits_t PAR_EL = 1 << 13;
const par_bits_t PAR_BR = 1 << 14;
const par_bits_t PAR_BC = 1 << 15;
const par_bits_t PAR_BL = 1 << 16;

const par_bits_t PAR_BA = PAR_BL + PAR_BC + PAR_BR;

const par_bits_t PAR_DA = PAR_DL + PAR_DR;

const par_bits_t PAR_EA = PAR_EL + PAR_ER;

const par_bits_t PAR_LI = PAR_L2 + PAR_L3;
const par_bits_t PAR_LO = PAR_L4 + PAR_L1;
const par_bits_t PAR_LA = PAR_LI + PAR_LO;

const par_bits_t PAR_NA = PAR_NL + PAR_NR;

const par_bits_t PAR_RI = PAR_R2 + PAR_R3;
const par_bits_t PAR_RO = PAR_R4 + PAR_R1;
const par_bits_t PAR_RA = PAR_RI + PAR_RO;

const par_bits_t PAR_FA = PAR_LA + PAR_RA;
const par_bits_t PAR_FC = PAR_LO + PAR_RO;
const par_bits_t PAR_FM = PAR_LI + PAR_RI;
const par_bits_t PAR_FI = PAR_FM + PAR_L1 + PAR_R1;
const par_bits_t PAR_FO = PAR_L4 + PAR_R4;

const par_bits_t PAR_AA = PAR_FA + PAR_DA + PAR_NA + PAR_EA + PAR_BA;
const par_bits_t PAR_AC = PAR_FM + PAR_BC;
const par_bits_t PAR_AE = PAR_FA + PAR_DA + PAR_NA + PAR_BA;
const par_bits_t PAR_AL = PAR_LA + PAR_DL + PAR_NL + PAR_BL;
const par_bits_t PAR_AR = PAR_RA + PAR_DR + PAR_NR + PAR_BR;



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
  _parBits = 0; 

	char abbr0 = _command[_currentIndex];
	char abbr1 = _command[_currentIndex + 1];
	_currentIndex += 2;

	for (int index = 0; index < sizeof(Chars2ParBitsMapping) / sizeof(Chars2ParBits); index++)
	{
		Chars2ParBits& mapping = Chars2ParBitsMapping[index];
		if ((abbr0 == mapping.abbr[0]) &&
			(abbr1 == mapping.abbr[1]))
		{
			_parBits = mapping.parBits;
		}
	}

	_parseError &= (_parBits == 0);
}


void CommandParser::SetDelay(step_time_t delay)
{
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		if ((_parBits & (1 << parNumber)) > 0)
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
		if ((_parBits & (1 << parNumber)) > 0)
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
