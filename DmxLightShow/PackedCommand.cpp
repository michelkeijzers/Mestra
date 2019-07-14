#include "PackedCommand.h"

#include "Command.h"


const uint8_t COMMAND_LENGTH    =  0;
const uint8_t COMMAND_PAR_GROUP = COMMAND_LENGTH    + 1;
const uint8_t COMMAND_FLAGS_1   = COMMAND_PAR_GROUP + 1;
const uint8_t COMMAND_FLAGS_2   = COMMAND_FLAGS_1   + 1;

const uint8_t COMMAND_PRESET_NUMBER_SET_BYTE		= COMMAND_FLAGS_1;
const uint8_t COMMAND_PRESET_NUMBER_SET_BIT			= 7;

const uint8_t COMMAND_DELAY_TIME_SET_BYTE			= COMMAND_FLAGS_1;
const uint8_t COMMAND_DELAY_TIME_SET_BIT			= 6;

const uint8_t COMMAND_STROBE_TIME_SET_BYTE			= COMMAND_FLAGS_1;
const uint8_t COMMAND_STROBE_TIME_SET_BIT			= 5;

const uint8_t COMMAND_STEP_NUMBER_SET_BYTE			= COMMAND_FLAGS_1;
const uint8_t COMMAND_STEP_NUMBER_SET_BIT			= 4;

const uint8_t COMMAND_STEP_NUMBER_SHORT_SET_BYTE	= COMMAND_FLAGS_1;
const uint8_t COMMAND_STEP_NUMBER_SHORT_SET_BIT		= 3;

const uint8_t COMMAND_STEP_NUMBER_SHORT_BYTE		= COMMAND_FLAGS_1;
const uint8_t COMMAND_STEP_NUMBER_SHORT_BIT			= 2;

const uint8_t COMMAND_HOLD_SET_BYTE					= COMMAND_FLAGS_2;
const uint8_t COMMAND_HOLD_SET_BIT					= 7;

const uint8_t COMMAND_HOLD_BYTE						= COMMAND_FLAGS_2;
const uint8_t COMMAND_HOLD_BIT						= 6;

const uint8_t COMMAND_ONCE_SET_BYTE					= COMMAND_FLAGS_2;
const uint8_t COMMAND_ONCE_SET_BIT					= 5;

const uint8_t COMMAND_ONCE_BYTE						= COMMAND_FLAGS_2;
const uint8_t COMMAND_ONCE_BIT						= 4;

const uint8_t COMMAND_DEFAULT_COLOR_SET_BYTE		= COMMAND_FLAGS_2;
const uint8_t COMMAND_DEFAULT_COLOR_SET_BIT			= 3;

const uint8_t COMMAND_ALTERNATE_COLOR_SET_BYTE		= COMMAND_FLAGS_2;
const uint8_t COMMAND_ALTERNATE_COLOR_SET_BIT		= 2;

const uint8_t COMMAND_COLOR_FORM_BIT                = 7;
const uint8_t COMMAND_COLOR_INTENSITY_BIT			= 6;
const uint8_t COMMAND_COLOR_RED_BIT					= 5;
const uint8_t COMMAND_COLOR_GREEN_BIT				= 4;
const uint8_t COMMAND_COLOR_BLUE_BIT				= 3;
const uint8_t COMMAND_COLOR_WHITE_USED_BIT			= 2;
const uint8_t COMMAND_COLOR_WHITE_BIT				= 1;
const uint8_t COMMAND_COLOR_DEFAULT_VALUE_BIT       = 0; // Only used for Long Form Color (bit 0)


PackedCommand::PackedCommand()
	:
	_data{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
{
}


PackedCommand::~PackedCommand()
{
}


void PackedCommand::Pack(const Command& command)
{
	uint8_t length = 4; // Minimum without additional bytes

	_data[COMMAND_PAR_GROUP] = command.GetParGroup();
	
	if (command.GetDelayTimeSet())
	{
		_data[COMMAND_DELAY_TIME_SET_BYTE] |= 1 << COMMAND_DELAY_TIME_SET_BIT;
		_data[length++] = uint8_t(command.GetDelayTime() / 256);
		_data[length++] = uint8_t(command.GetDelayTime() % 256);
	}
	
	if (command.GetStrobeTimeSet())
	{
		_data[COMMAND_STROBE_TIME_SET_BYTE] |= 1 << COMMAND_STROBE_TIME_SET_BIT;
		_data[length++] = uint8_t(command.GetStrobeTime() / 256);
		_data[length++] = uint8_t(command.GetStrobeTime() % 256);
	}

	if (command.GetPresetNumberSet())
	{
		_data[COMMAND_STEP_NUMBER_SET_BYTE] |= 1 << COMMAND_PRESET_NUMBER_SET_BIT;
		_data[length++] = command.GetPresetNumber();
	}

	if (command.GetStepNumberSet())
	{
		PackStepNumber(command, length);
	}

	if (command.GetHoldSet())
	{
		_data[COMMAND_HOLD_SET_BYTE] |= 1 << COMMAND_HOLD_SET_BIT;
		if (command.GetHold())
		{
			_data[COMMAND_HOLD_BYTE] |= 1 << COMMAND_HOLD_BIT;
		}
	}

	if (command.GetOnceSet())
	{
		_data[COMMAND_ONCE_SET_BYTE] |= 1 << COMMAND_ONCE_SET_BIT;
		if(command.GetOnce())
		{
			_data[COMMAND_ONCE_BYTE] |= 1 << COMMAND_ONCE_BIT;
		}
	}

	if (command.GetDefaultColorSet())
	{
		_data[COMMAND_DEFAULT_COLOR_SET_BYTE] |= 1 << COMMAND_DEFAULT_COLOR_SET_BIT;

		Irgbw color = command.GetDefaultColor();
		bool whiteUsed = command.GetDefaultColorWhiteUsed();

		PackColor(length, color, whiteUsed);
	}

	if (command.GetAlternateColorSet())
	{
		_data[COMMAND_ALTERNATE_COLOR_SET_BYTE] |= 1 << COMMAND_ALTERNATE_COLOR_SET_BIT;

		Irgbw color = command.GetAlternateColor();
		bool whiteUsed = command.GetAlternateColorWhiteUsed();

		PackColor(length, color, whiteUsed);
	}

	_data[COMMAND_LENGTH] = length;
}


void PackedCommand::PackStepNumber(const Command& command, uint8_t& length)
{
	if (command.GetLastStepNumber())
	{
		_data[COMMAND_STEP_NUMBER_SHORT_SET_BYTE] |= 1 << COMMAND_STEP_NUMBER_SHORT_SET_BIT;
		_data[COMMAND_STEP_NUMBER_SHORT_BYTE    ] |= 1 << COMMAND_STEP_NUMBER_SHORT_BIT;
	}
	else
	{
		step_t stepNumber = command.GetStepNumber();
		if (stepNumber == 0)
		{
			_data[COMMAND_STEP_NUMBER_SHORT_SET_BYTE] |= 1 << COMMAND_STEP_NUMBER_SHORT_SET_BIT;
		}
		else
		{
			_data[COMMAND_STEP_NUMBER_SET_BYTE] |= 1 << COMMAND_STEP_NUMBER_SET_BIT;
			_data[length++] = uint8_t(command.GetStepNumber() / 256);
			_data[length++] = uint8_t(command.GetStepNumber() % 256);
		}
	}
}

void PackedCommand::PackColor(uint8_t length, Irgbw color, bool whiteUsed)
{
	if (               (                             color.GetIntensity() == 255) &&
			    	   (color.GetRed()       == 0 || color.GetRed()       == 255) &&
					   (color.GetGreen()     == 0 || color.GetGreen()     == 255) &&
		               (color.GetBlue()      == 0 || color.GetBlue()      == 255) &&
		(!whiteUsed || (color.GetWhite()     == 0 || color.GetWhite()     == 255)))
	{
		// Short form
		_data[length] |= (color.GetIntensity() == 255) << COMMAND_COLOR_INTENSITY_BIT;
		_data[length] |= (color.GetRed()       == 255) << COMMAND_COLOR_RED_BIT;
		_data[length] |= (color.GetGreen()     == 255) << COMMAND_COLOR_GREEN_BIT;
		_data[length] |= (color.GetBlue()      == 255) << COMMAND_COLOR_BLUE_BIT;
		_data[length] |= whiteUsed                     << COMMAND_COLOR_WHITE_USED_BIT;
		_data[length] |= (color.GetWhite()     == 255) << COMMAND_COLOR_WHITE_BIT;
	}
	else
	{
		// Long form
		uint8_t colorByte = length;

		_data[colorByte] |= 1 << COMMAND_COLOR_FORM_BIT; // Long form

		// Define default value (most occurrences).
		uint8_t amount0   = CountColorValue(color, whiteUsed,   0);
		uint8_t amount255 = CountColorValue(color, whiteUsed, 255);

		PackAdditionalColorBytes(length, color, amount0 > amount255 ? 0 : 255, whiteUsed, colorByte);
	}
}


/* static */ bool PackedCommand::CountColorValue(Irgbw color, bool whiteUsed, uint8_t colorValueToCount)
{
	return	       (color.GetIntensity() ==               255)  ? 1 : 0 +
				   (color.GetRed()	     == colorValueToCount)  ? 1 : 0 +
			       (color.GetGreen()	 == colorValueToCount)  ? 1 : 0 +
	               (color.GetBlue()	     == colorValueToCount)  ? 1 : 0 +
	 (whiteUsed && (color.GetWhite()	 == colorValueToCount)) ? 1 : 0;
}


void PackedCommand::PackAdditionalColorBytes(uint8_t length, Irgbw color, uint8_t defaultColorValue, bool whiteUsed, uint8_t colorByte)
{
	_data[colorByte] |= 1 << COMMAND_COLOR_DEFAULT_VALUE_BIT;

	PackAdditionalColorByte(length, colorByte, color.GetIntensity(),               255, COMMAND_COLOR_INTENSITY_BIT);
	PackAdditionalColorByte(length, colorByte, color.GetRed()      , defaultColorValue, COMMAND_COLOR_RED_BIT);
	PackAdditionalColorByte(length, colorByte, color.GetGreen()    , defaultColorValue, COMMAND_COLOR_GREEN_BIT);
	PackAdditionalColorByte(length, colorByte, color.GetBlue()     , defaultColorValue, COMMAND_COLOR_BLUE_BIT);

	if (whiteUsed)
	{
		PackAdditionalColorByte(length, colorByte, color.GetWhite(), defaultColorValue, COMMAND_COLOR_WHITE_BIT);
	}
}


void PackedCommand::PackAdditionalColorByte(uint8_t& length, uint8_t colorByte, uint8_t colorValue, uint8_t defaultColorValue, uint8_t colorBit)
{
	if (colorValue != defaultColorValue)
	{
		_data[colorByte] |= 1 << colorBit;
		_data[length++]   = colorValue;
	}
}


void PackedCommand::Unpack(Command& command)
{
	uint8_t length = 4; // Additional bytes start at 4.

	command.SetParGroup(_data[COMMAND_PAR_GROUP]);

	if (_data[COMMAND_PRESET_NUMBER_SET_BYTE] & 1 << COMMAND_PRESET_NUMBER_SET_BIT)
	{
		command.SetPresetNumberSet(true);
		command.SetPresetNumber(_data[length++]);
	}

	if (_data[COMMAND_DELAY_TIME_SET_BYTE] & 1 << COMMAND_DELAY_TIME_SET_BIT)
	{
		command.SetDelayTimeSet(true);
		command.SetDelayTime(_data[length] * 256 + _data[length + 1]);
		length += 2;
	}

	if (_data[COMMAND_STROBE_TIME_SET_BYTE] & 1 << COMMAND_STROBE_TIME_SET_BIT)
	{
		command.SetStrobeTimeSet(true);
		command.SetStrobeTime(_data[length] * 256 + _data[length + 1]);
		length += 2;
	}

	if (_data[COMMAND_STEP_NUMBER_SHORT_SET_BYTE] & 1 << COMMAND_STEP_NUMBER_SHORT_SET_BIT)
	{
		command.SetStepNumberSet(true);
		if (_data[COMMAND_STEP_NUMBER_SHORT_BYTE] & 1 << COMMAND_STEP_NUMBER_SHORT_BIT)
		{
			command.SetLastStepNumber(true);
		}
		else
		{
			command.SetStepNumber(0);
		}
	}
	else if (_data[COMMAND_STEP_NUMBER_SET_BYTE] & 1 << COMMAND_STEP_NUMBER_SET_BIT)
	{
		command.SetStepNumberSet(true);
	
		command.SetStepNumber(_data[length] * 256 + _data[length + 1]);
		length += 2;
	}

	if (_data[COMMAND_HOLD_SET_BYTE] & 1 << COMMAND_HOLD_SET_BIT)
	{
		command.SetHoldSet(true);
		command.SetHold(_data[COMMAND_HOLD_BYTE] & 1 << _data[COMMAND_HOLD_BIT] ? true : false);
	}

	if (_data[COMMAND_ONCE_SET_BYTE] & 1 << COMMAND_ONCE_SET_BIT)
	{
		command.SetOnceSet(true);
		command.SetOnce(_data[COMMAND_ONCE_BYTE] & 1 << _data[COMMAND_ONCE_BIT] ? true : false);
	}

	if (_data[COMMAND_DEFAULT_COLOR_SET_BYTE] & 1 << COMMAND_DEFAULT_COLOR_SET_BIT)
	{
		command.SetDefaultColorSet(true);

		Irgbw color;
		uint8_t colorByte = length++;
		bool whiteUsed = _data[colorByte] & 1 << COMMAND_COLOR_WHITE_BIT ? true : false;

		UnpackColors(length, color, colorByte, whiteUsed);
		
		command.SetDefaultColor(color);
		command.SetDefaultColorWhiteUsed(whiteUsed);
	}
	
	if (_data[COMMAND_ALTERNATE_COLOR_SET_BYTE] & 1 << COMMAND_ALTERNATE_COLOR_SET_BIT)
	{
		command.SetAlternateColorSet(true);

		Irgbw color;
		uint8_t colorByte = length++;
		bool whiteUsed = _data[colorByte] & 1 << COMMAND_COLOR_WHITE_BIT ? true : false;

		UnpackColors(length, color, colorByte, whiteUsed);

		command.SetAlternateColor(color);
		command.SetAlternateColorWhiteUsed(whiteUsed);
	}
}


void PackedCommand::UnpackColors(uint8_t& length, Irgbw color, uint8_t colorByte, bool whiteUsed)
{
	if ((_data[colorByte] & 1 << COMMAND_COLOR_FORM_BIT) == 0)
	{
		// Short form
		color.SetIntensity((_data[colorByte] & 1 << COMMAND_COLOR_INTENSITY_BIT) * 255);
		color.SetRed      ((_data[colorByte] & 1 << COMMAND_COLOR_RED_BIT      ) * 255);
		color.SetGreen    ((_data[colorByte] & 1 << COMMAND_COLOR_GREEN_BIT    ) * 255);
		color.SetBlue     ((_data[colorByte] & 1 << COMMAND_COLOR_BLUE_BIT     ) * 255);

		if (_data[colorByte] & 1 << COMMAND_COLOR_WHITE_USED_BIT)
		{
			color.SetWhite(whiteUsed * 255);
		}
	}
	else
	{
		// Long form
		uint8_t defaultColorValue = _data[colorByte] & 1 << COMMAND_COLOR_DEFAULT_VALUE_BIT ? 255 : 0;
		color.SetIntensity(_data[colorByte] & 1 << COMMAND_COLOR_INTENSITY_BIT ?               255 : _data[length++]);
		color.SetRed      (_data[colorByte] & 1 << COMMAND_COLOR_RED_BIT       ? defaultColorValue : _data[length++]);
		color.SetGreen    (_data[colorByte] & 1 << COMMAND_COLOR_GREEN_BIT     ? defaultColorValue : _data[length++]);
		color.SetBlue     (_data[colorByte] & 1 << COMMAND_COLOR_BLUE_BIT      ? defaultColorValue : _data[length++]);

		if (whiteUsed)
		{
			color.SetWhite(_data[colorByte] & 1 << COMMAND_COLOR_WHITE_BIT     ? defaultColorValue : _data[length++]);
		}
	}
}

