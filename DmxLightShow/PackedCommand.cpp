
#include "AssertUtils.h"
#include "BitsUtils.h"

#include "PackedCommand.h"
#include "Command.h"


const uint8_t COMMAND_LENGTH								=  0;
const uint8_t COMMAND_PAR_GROUP								= COMMAND_LENGTH    + 1;
const uint8_t COMMAND_FLAGS_1								= COMMAND_PAR_GROUP + 1;
const uint8_t COMMAND_FLAGS_2								= COMMAND_FLAGS_1   + 1;

const uint8_t COMMAND_PRESET_NUMBER_SET_BYTE				= COMMAND_FLAGS_1;
const uint8_t COMMAND_PRESET_NUMBER_SET_BIT					= 7;

const uint8_t COMMAND_DELAY_TIME_SET_BYTE					= COMMAND_FLAGS_1;
const uint8_t COMMAND_DELAY_TIME_SET_BIT					= 6;

const uint8_t COMMAND_STROBE_TIME_SET_BYTE					= COMMAND_FLAGS_1;
const uint8_t COMMAND_STROBE_TIME_SET_BIT					= 5;

const uint8_t COMMAND_STEP_NUMBER_SET_BYTE					= COMMAND_FLAGS_1;
const uint8_t COMMAND_STEP_NUMBER_SET_BITS   				= 4; // See EStepTime, 2 bits
const uint8_t COMMAND_STEP_NUMBER_SET_NR_OF_BITS			= 2;

const uint8_t COMMAND_HOLD_SET_BYTE							= COMMAND_FLAGS_2;
const uint8_t COMMAND_HOLD_SET_BIT							= 7;

const uint8_t COMMAND_HOLD_BYTE								= COMMAND_FLAGS_2;
const uint8_t COMMAND_HOLD_BIT								= 6;

const uint8_t COMMAND_ONCE_SET_BYTE							= COMMAND_FLAGS_2;
const uint8_t COMMAND_ONCE_SET_BIT							= 5;

const uint8_t COMMAND_ONCE_BYTE								= COMMAND_FLAGS_2;
const uint8_t COMMAND_ONCE_BIT								= 4;

const uint8_t COMMAND_DEFAULT_COLOR_SET_BYTE				= COMMAND_FLAGS_2;
const uint8_t COMMAND_DEFAULT_COLOR_SET_BIT					= 3;

const uint8_t COMMAND_ALTERNATE_COLOR_SET_BYTE				= COMMAND_FLAGS_2;
const uint8_t COMMAND_ALTERNATE_COLOR_SET_BIT				= 2;

const uint8_t COMMAND_COLOR_FORM_BITS						= 7;
const uint8_t COMMAND_COLOR_FORM_NR_OF_BITS                 = 2;

const uint8_t COMMAND_COLOR_SHORT_INTENSITY_BIT				= 5;
const uint8_t COMMAND_COLOR_SHORT_RED_BIT					= 4;
const uint8_t COMMAND_COLOR_SHORT_GREEN_BIT					= 3;
const uint8_t COMMAND_COLOR_SHORT_BLUE_BIT					= 2;
const uint8_t COMMAND_COLOR_SHORT_WHITE_USED_BIT			= 1;
const uint8_t COMMAND_COLOR_SHORT_WHITE_BIT					= 0;

const uint8_t COMMAND_COLOR_MEDIUM_INTENSITY_BYTE        	= 0; // Offset
const uint8_t COMMAND_COLOR_MEDIUM_INTENSITY_BITS 			= 5; // 0, 64, 128, 255
const uint8_t COMMAND_COLOR_MEDIUM_INTENSITY_NR_OF_BITS		= 2; // 0, 64, 128, 255
const uint8_t COMMAND_COLOR_MEDIUM_RED_BYTE				    = 0; // Offset
const uint8_t COMMAND_COLOR_MEDIUM_RED_BITS 	            = 3; // 0, 32, 64, 96, 128, 160, 196, 255
const uint8_t COMMAND_COLOR_MEDIUM_RED_NR_OF_BITS           = 3;
const uint8_t COMMAND_COLOR_MEDIUM_GREEN_BYTE			    = 0; // Offset
const uint8_t COMMAND_COLOR_MEDIUM_GREEN_BITS 			    = 0; // 0, 32, 64, 96, 128, 160, 196, 255
const uint8_t COMMAND_COLOR_MEDIUM_GREEN_NR_OF_BITS         = 3;
const uint8_t COMMAND_COLOR_MEDIUM_BLUE_BYTE			    = 1; // Offset
const uint8_t COMMAND_COLOR_MEDIUM_BLUE_BITS 			    = 5; // 0, 32, 64, 96, 128, 160, 196, 255
const uint8_t COMMAND_COLOR_MEDIUM_BLUE_NR_OF_BITS          = 3;
const uint8_t COMMAND_COLOR_MEDIUM_WHITE_BYTE               = 1; // Offset
const uint8_t COMMAND_COLOR_MEDIUM_WHITE_BITS		        = 2;  // Not set, 0, 32, 64, 96, 128, 160, 255
const uint8_t COMMAND_COLOR_MEDIUM_WHITE_NR_OF_BITS         = 3;

const uint8_t COMMAND_COLOR_SINGLE_COLOR_BITS               = 5; 
const uint8_t COMMAND_COLOR_SINGLE_COLOR_NR_OF_BITS         = 2; 

const uint8_t COMMAND_COLOR_SINGLE_COLOR_VALUE_BITS         = 3;
const uint8_t COMMAND_COLOR_SINGLE_COLOR_VALUE_NR_OF_BITS   = 4;

const uint8_t COMMAND_COLOR_LONG_DEFAULT_VALUE_BIT          = 5; // 0: 0, 1: 255
const uint8_t COMMAND_COLOR_LONG_RED_SET_BIT                = 4;
const uint8_t COMMAND_COLOR_LONG_GREEN_SET_BIT              = 3;
const uint8_t COMMAND_COLOR_LONG_BLUE_SET_BIT               = 2;
const uint8_t COMMAND_COLOR_LONG_WHITE_USED_SET_BIT         = 1;
const uint8_t COMMAND_COLOR_LONG_WHITE_SET_BIT              = 0;


PackedCommand::PackedCommand()
:
	_data{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
{
}


PackedCommand::~PackedCommand()
{
}


uint8_t PackedCommand::Pack(const Command& command)
{
	uint8_t length = 4; // Minimum without additional bytes

	_data[COMMAND_PAR_GROUP] = command.GetParGroup();
	
	if (command.GetDelayTimeSet())
	{
		_data[COMMAND_DELAY_TIME_SET_BYTE] |= 1 << COMMAND_DELAY_TIME_SET_BIT;
		uint32_t value = command.GetDelayTime();

		_data[length++] = uint8_t(value / 256);
		_data[length++] = uint8_t(value % 256);
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
		length += PackStepNumber(command, length);
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

		length += PackColor(length, color, whiteUsed);
	}

	if (command.GetAlternateColorSet())
	{
		_data[COMMAND_ALTERNATE_COLOR_SET_BYTE] |= 1 << COMMAND_ALTERNATE_COLOR_SET_BIT;

		Irgbw color = command.GetAlternateColor();
		bool whiteUsed = command.GetAlternateColorWhiteUsed();

		length += PackColor(length, color, whiteUsed);
	}

	_data[COMMAND_LENGTH] = length;

	return length;
}


uint8_t PackedCommand::PackStepNumber(const Command& command, uint8_t length)
{
	uint8_t additionalBytes = 0;

	if (command.GetLastStepNumber())
	{
		_data[COMMAND_STEP_NUMBER_SET_BYTE] |= (EStepNumber::Last >> 1) <<  COMMAND_STEP_NUMBER_SET_BITS;      // Left bit of Last to first bit
		_data[COMMAND_STEP_NUMBER_SET_BYTE] |= (EStepNumber::Last     ) << (COMMAND_STEP_NUMBER_SET_BITS - 1); // Right bit of Last to second bit
	}
	else
	{
		step_t stepNumber = command.GetStepNumber();
		if (stepNumber == 0)
		{
			_data[COMMAND_STEP_NUMBER_SET_BYTE] |= (EStepNumber::Zero >> 1) <<  COMMAND_STEP_NUMBER_SET_BITS;      // Left bit of Zero to first bit
			_data[COMMAND_STEP_NUMBER_SET_BYTE] |= (EStepNumber::Zero     ) << (COMMAND_STEP_NUMBER_SET_BITS - 1); // Right bit of Zero to second bit
		}
		else
		{
			_data[COMMAND_STEP_NUMBER_SET_BYTE] |= (EStepNumber::Set >> 1) <<  COMMAND_STEP_NUMBER_SET_BITS;      // Left bit of Set to first bit
			_data[COMMAND_STEP_NUMBER_SET_BYTE] |= (EStepNumber::Set     ) << (COMMAND_STEP_NUMBER_SET_BITS - 1); // Right bit of Set to second bit

			// Add bytes with step number.
			_data[length++] = uint8_t(command.GetStepNumber() / 256);
			_data[length++] = uint8_t(command.GetStepNumber() % 256);
			additionalBytes = 2;
		}
	}

	return additionalBytes;
}

uint8_t PackedCommand::PackColor(uint8_t length, Irgbw color, bool whiteUsed)
{
	uint8_t additionalBytes = 0;

	dmx_value_t intensity = color.GetIntensity();
	dmx_value_t red       = color.GetRed();
	dmx_value_t green     = color.GetGreen();
	dmx_value_t blue      = color.GetBlue();
	dmx_value_t white     = color.GetWhite();

	if (               (                  intensity == 255) &&
			    	   (red       == 0 || red       == 255) &&
					   (green     == 0 || green     == 255) &&
		               (blue      == 0 || blue      == 255) &&
		(!whiteUsed || (white     == 0 || white     == 255)))
	{
		PackShortFormColor(length, intensity, red, green, blue, whiteUsed, white);
	}
	else if (               ((intensity <= 128 && intensity % 64 == 0) || intensity == 255) &&
		                    ((red       <= 192 && red       % 32 == 0) || red       == 255) &&
   	     	                ((green     <= 192 && green     % 32 == 0) || green     == 255) &&
		                    ((blue      <= 192 && blue      % 32 == 0) || blue      == 255) &&
		     (!whiteUsed || ((white     <= 160 && white     % 32 == 0) || white     == 255)))
	{
		PackMediumFormColor(length, intensity, red, green, blue, whiteUsed, white);
	}
	else if ((intensity == 255) && 
		     (((red   == 0) && (green == 0) && (blue == 0)                ) ||
			  ((red   == 0) && (green == 0)                && (white == 0)) ||
			  ((red   == 0) &&                 (blue == 0) && (blue  == 0)) ||
			  (                (green == 0) && (blue == 0) && (white == 0))))
	{
		PackSingleFormColor(length, red, green, blue, white);
	}
	else
	{
		additionalBytes = PackLongFormColor(length, color, whiteUsed);
	}

	return additionalBytes;
}


void PackedCommand::PackShortFormColor(const uint8_t& length, const dmx_value_t& intensity, 
	const dmx_value_t& red, const dmx_value_t& green, const dmx_value_t& blue, bool whiteUsed, const dmx_value_t& white)
{
	// Short form
	BitsUtils::SetBitsFromZero(&(_data[length]), COMMAND_COLOR_FORM_BITS, COMMAND_COLOR_FORM_NR_OF_BITS, EColorForm::Short);
	_data[length] |= (intensity == 255) << COMMAND_COLOR_SHORT_INTENSITY_BIT;
	_data[length] |= (red == 255) << COMMAND_COLOR_SHORT_RED_BIT;
	_data[length] |= (green == 255) << COMMAND_COLOR_SHORT_GREEN_BIT;
	_data[length] |= (blue == 255) << COMMAND_COLOR_SHORT_BLUE_BIT;
	_data[length] |= whiteUsed << COMMAND_COLOR_SHORT_WHITE_USED_BIT;
	_data[length] |= (white == 255) << COMMAND_COLOR_SHORT_WHITE_BIT;
}


void PackedCommand::PackMediumFormColor(const uint8_t& length, dmx_value_t& intensity, 
	const dmx_value_t& red, const dmx_value_t& green, const dmx_value_t& blue, bool whiteUsed, const dmx_value_t& white)
{
	// Medium Form
	BitsUtils::SetBitsFromZero(&(_data[length]), COMMAND_COLOR_FORM_BITS, COMMAND_COLOR_FORM_NR_OF_BITS, EColorForm::Medium);

	// 255 / 64 = 3.98 = 3 = both bits set
	intensity /= 64;
	BitsUtils::SetBitsFromZero(&_data[length + COMMAND_COLOR_MEDIUM_INTENSITY_BYTE], COMMAND_COLOR_MEDIUM_INTENSITY_BITS,
		COMMAND_COLOR_MEDIUM_INTENSITY_NR_OF_BITS, intensity);

	// 255 / 32 = 7.97 = 7 = all 3 bits set
	BitsUtils::SetBitsFromZero(&_data[length + COMMAND_COLOR_MEDIUM_RED_BYTE], COMMAND_COLOR_MEDIUM_RED_BITS,
		COMMAND_COLOR_MEDIUM_RED_NR_OF_BITS, red / 32);
	BitsUtils::SetBitsFromZero(&_data[length + COMMAND_COLOR_MEDIUM_GREEN_BYTE], COMMAND_COLOR_MEDIUM_GREEN_BITS,
		COMMAND_COLOR_MEDIUM_GREEN_NR_OF_BITS, green / 32);
	BitsUtils::SetBitsFromZero(&_data[length + COMMAND_COLOR_MEDIUM_BLUE_BYTE], COMMAND_COLOR_MEDIUM_BLUE_BITS,
		COMMAND_COLOR_MEDIUM_BLUE_NR_OF_BITS, blue / 32);

	BitsUtils::SetBitsFromZero(&_data[length + COMMAND_COLOR_MEDIUM_WHITE_BYTE], COMMAND_COLOR_MEDIUM_WHITE_BITS,
		COMMAND_COLOR_MEDIUM_WHITE_NR_OF_BITS, whiteUsed ? 0 : (white == 255 ? 0x111 : white / 32 + 1));
}


void PackedCommand::PackSingleFormColor(const uint8_t& length, 
	const dmx_value_t& red, const dmx_value_t& green, const dmx_value_t& blue, const dmx_value_t& white)
{
	// Single form
	BitsUtils::SetBitsFromZero(&(_data[length]), COMMAND_COLOR_FORM_BITS, COMMAND_COLOR_FORM_NR_OF_BITS, EColorForm::Single);
	dmx_value_t colorValue;

	ESingleColor color;
	if (red != 255)
	{
		color = Red;
		colorValue = red;
	}
	else if (green != 255)
	{
		color = Green;
		colorValue = green;
	}
	else if (blue != 255)
	{
		color = Blue;
		colorValue = blue;
	}
	else
	{
		color = White;
		colorValue = white;
	}

	BitsUtils::SetBitsFromZero(&_data[length], COMMAND_COLOR_SINGLE_COLOR_BITS,
		COMMAND_COLOR_SINGLE_COLOR_NR_OF_BITS, color);
	BitsUtils::SetBitsFromZero(&_data[length], COMMAND_COLOR_SINGLE_COLOR_VALUE_BITS,
		COMMAND_COLOR_SINGLE_COLOR_VALUE_NR_OF_BITS, colorValue == 224 ? 255 : colorValue / 32);
}


uint8_t PackedCommand::PackLongFormColor(const uint8_t& length, const Irgbw& color, bool whiteUsed)
{
	uint8_t colorByte = length;

	BitsUtils::SetBitsFromZero(&(_data[length]), COMMAND_COLOR_FORM_BITS, COMMAND_COLOR_FORM_NR_OF_BITS, EColorForm::Long);

	// Define default value (most occurrences).
	uint8_t amount0 = CountColorValue(color, whiteUsed, 0);
	uint8_t amount255 = CountColorValue(color, whiteUsed, 255);

	return PackAdditionalColorBytes(length, color, amount0 > amount255 ? 0 : 255, whiteUsed, colorByte);
}


/* static */ bool PackedCommand::CountColorValue(Irgbw color, bool whiteUsed, uint8_t colorValueToCount)
{
	return (              color.GetIntensity() ==               255)  ? 1 : 0 +
		   (              color.GetRed()       == colorValueToCount)  ? 1 : 0 +
		   (              color.GetGreen()	   == colorValueToCount)  ? 1 : 0 +
		   (              color.GetBlue()	   == colorValueToCount)  ? 1 : 0 +
		   (whiteUsed && (color.GetWhite()	   == colorValueToCount)) ? 1 : 0;
}


uint8_t  PackedCommand::PackAdditionalColorBytes(uint8_t length, Irgbw color, uint8_t defaultColorValue, bool whiteUsed, uint8_t colorByte)
{
	uint8_t additionalColorBytes = 0;

	_data[colorByte] |= 1 << COMMAND_COLOR_LONG_DEFAULT_VALUE_BIT;

	additionalColorBytes += PackAdditionalColorByte(length, colorByte, color.GetRed()      , defaultColorValue, COMMAND_COLOR_LONG_RED_SET_BIT);
	additionalColorBytes += PackAdditionalColorByte(length, colorByte, color.GetGreen()    , defaultColorValue, COMMAND_COLOR_LONG_GREEN_SET_BIT);
	additionalColorBytes += PackAdditionalColorByte(length, colorByte, color.GetBlue()     , defaultColorValue, COMMAND_COLOR_LONG_BLUE_SET_BIT);

	if (whiteUsed)
	{
		additionalColorBytes += PackAdditionalColorByte(length, colorByte, color.GetWhite(), defaultColorValue, COMMAND_COLOR_LONG_WHITE_SET_BIT);
	}

	return additionalColorBytes;
}


uint8_t PackedCommand::PackAdditionalColorByte(uint8_t& length, uint8_t colorByte, uint8_t colorValue, uint8_t defaultColorValue, uint8_t colorBit)
{
	uint8_t additionalColorBytes = 0;

	if (colorValue != defaultColorValue)
	{
		_data[colorByte] |= 1 << colorBit;
		_data[length]   = colorValue;
		additionalColorBytes = 1;
	}

	return additionalColorBytes;
}


uint8_t PackedCommand::Unpack(Command& command)
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

	switch (EStepNumber(BitsUtils::GetBits(&_data[COMMAND_STEP_NUMBER_SET_BYTE], 
		COMMAND_STEP_NUMBER_SET_BITS, COMMAND_STEP_NUMBER_SET_NR_OF_BITS)))
	{
	case EStepNumber::NotSet:
		// Do nothing.
		break;

	case EStepNumber::Set:
		command.SetStepNumberSet(true);
		command.SetStepNumber(_data[length] * 256 + _data[length + 1]);
		length += 2;
		break;

	case EStepNumber::Zero:
		command.SetStepNumberSet(true);
		command.SetStepNumber(0);
		break;
	
	case EStepNumber::Last:
		command.SetStepNumberSet(true);
		command.SetLastStepNumber(true);
		break;

	default:
		AssertUtils::MyAssert(false);
		break;
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
		bool whiteUsed = false;
		
		length += UnpackColors(length, colorByte, color, whiteUsed);
		
		command.SetDefaultColor(color);
		command.SetDefaultColorWhiteUsed(whiteUsed);
	}
	
	if (_data[COMMAND_ALTERNATE_COLOR_SET_BYTE] & 1 << COMMAND_ALTERNATE_COLOR_SET_BIT)
	{
		command.SetAlternateColorSet(true);

		Irgbw color;
		uint8_t colorByte = length++;
		bool whiteUsed = false;

		length += UnpackColors(length, colorByte, color, whiteUsed);

		command.SetAlternateColor(color);
		command.SetAlternateColorWhiteUsed(whiteUsed);
	}

	return length;
}


uint8_t PackedCommand::UnpackColors(uint8_t length, uint8_t colorByte, Irgbw &color,  bool &whiteUsed)
{
	uint8_t additionalBytes = 0;

	EColorForm form = (EColorForm) BitsUtils::GetBits(&_data[colorByte], COMMAND_COLOR_FORM_BITS, COMMAND_COLOR_FORM_NR_OF_BITS);
	switch (form)
	{
	case Short:
		color.SetIntensity((_data[colorByte] & 1 << COMMAND_COLOR_SHORT_INTENSITY_BIT) * 255);
		color.SetRed      ((_data[colorByte] & 1 << COMMAND_COLOR_SHORT_RED_BIT      ) * 255);
		color.SetGreen    ((_data[colorByte] & 1 << COMMAND_COLOR_SHORT_GREEN_BIT    ) * 255);
		color.SetBlue     ((_data[colorByte] & 1 << COMMAND_COLOR_SHORT_BLUE_BIT     ) * 255);

		whiteUsed = _data[colorByte] & (1 << COMMAND_COLOR_SHORT_WHITE_USED_BIT) ? true : false;
		if (whiteUsed)
		{
			color.SetWhite((_data[colorByte] & 1 << COMMAND_COLOR_SHORT_WHITE_BIT    ) * 255);
		}
		break;

	case Medium:
		UnpackMediumFormColor(colorByte, color, whiteUsed);
		break;
		
	case Single:
		UnpackSingleFormColor(color, whiteUsed, colorByte);
		break;

	case Long:
		additionalBytes = UnpackLongFormColor(length, colorByte, color, whiteUsed);
		break;

	default:
		AssertUtils::MyAssert(false);
	}

	return additionalBytes;
}


void PackedCommand::UnpackMediumFormColor(const uint8_t colorByte, Irgbw& color, bool& whiteUsed)
{
	dmx_value_t value = (dmx_value_t)BitsUtils::GetBits(&_data[colorByte + COMMAND_COLOR_MEDIUM_INTENSITY_BYTE],
		COMMAND_COLOR_MEDIUM_INTENSITY_BITS, COMMAND_COLOR_MEDIUM_INTENSITY_NR_OF_BITS);
	color.SetIntensity(value == 3 ? 255 : value * 64);

	value = (dmx_value_t)BitsUtils::GetBits(&_data[colorByte + COMMAND_COLOR_MEDIUM_RED_BYTE],
		COMMAND_COLOR_MEDIUM_RED_BITS, COMMAND_COLOR_MEDIUM_RED_NR_OF_BITS);
	color.SetRed(value == 7 ? 255 : value * 32);

	value = (dmx_value_t)BitsUtils::GetBits(&_data[colorByte + COMMAND_COLOR_MEDIUM_GREEN_BYTE],
		COMMAND_COLOR_MEDIUM_GREEN_BITS, COMMAND_COLOR_MEDIUM_GREEN_NR_OF_BITS);
	color.SetGreen(value == 7 ? 255 : value * 32);

	value = (dmx_value_t)BitsUtils::GetBits(&_data[colorByte + COMMAND_COLOR_MEDIUM_BLUE_BYTE],
		COMMAND_COLOR_MEDIUM_BLUE_BITS, COMMAND_COLOR_MEDIUM_BLUE_NR_OF_BITS);
	color.SetBlue(value == 7 ? 255 : value * 32);

	value = (dmx_value_t)BitsUtils::GetBits(&_data[colorByte + COMMAND_COLOR_MEDIUM_WHITE_BYTE],
		COMMAND_COLOR_MEDIUM_WHITE_BITS, COMMAND_COLOR_MEDIUM_WHITE_NR_OF_BITS);

	whiteUsed = value != 0;
	if (whiteUsed)
	{
		color.SetWhite(value == 7 ? 255 : (value - 1) * 32);
	}
}


void PackedCommand::UnpackSingleFormColor(Irgbw& color, bool& whiteUsed, const uint8_t& colorByte)
{
	color.SetIntensity(255);
	whiteUsed = false;

	const ESingleColor singleColor = (ESingleColor)BitsUtils::GetBits(&_data[colorByte],
		COMMAND_COLOR_SINGLE_COLOR_BITS, COMMAND_COLOR_SINGLE_COLOR_NR_OF_BITS);

	dmx_value_t colorValue = (dmx_value_t)BitsUtils::GetBits(&_data[colorByte],
		COMMAND_COLOR_SINGLE_COLOR_VALUE_BITS, COMMAND_COLOR_SINGLE_COLOR_VALUE_NR_OF_BITS) * 32;
	colorValue = (colorValue == 224) ? 255 : colorValue;

	switch (singleColor)
	{
	case Red:
		color.SetRed(colorValue);
		break;

	case Green:
		color.SetGreen(colorValue);
		break;

	case Blue:
		color.SetBlue(colorValue);
		break;

	case White:
		whiteUsed = true;
		color.SetWhite(colorValue);
		break;

	default:
		AssertUtils::MyAssert(false);
		break;
	}
}


uint8_t PackedCommand::UnpackLongFormColor(uint8_t length, uint8_t colorByte, Irgbw& color, bool& whiteUsed)
{
	uint8_t additionalBytes = 0;

	uint8_t defaultColorValue = _data[colorByte] & 1 << COMMAND_COLOR_LONG_DEFAULT_VALUE_BIT ? 255 : 0;
	color.SetIntensity(255);

	if (_data[colorByte] & 1 << COMMAND_COLOR_LONG_RED_SET_BIT)
	{
		additionalBytes++;
		color.SetRed(_data[length + additionalBytes]);
	}
	else
	{
		color.SetRed(defaultColorValue);
	}

	if (_data[colorByte] & 1 << COMMAND_COLOR_LONG_GREEN_SET_BIT)
	{
		additionalBytes++;
		color.SetGreen(_data[length + additionalBytes]);
	}
	else
	{
		color.SetGreen(defaultColorValue);
	}

	if (_data[colorByte] & 1 << COMMAND_COLOR_LONG_BLUE_SET_BIT)
	{
		additionalBytes++;
		color.SetBlue(_data[length + additionalBytes]);
	}
	else
	{
		color.SetBlue(defaultColorValue);
	}

	whiteUsed = _data[colorByte] & 1 << COMMAND_COLOR_LONG_WHITE_USED_SET_BIT ? true : false;
	if (whiteUsed)
	{
		if (_data[colorByte] & 1 << COMMAND_COLOR_LONG_WHITE_SET_BIT)
		{
			additionalBytes++;
			color.SetWhite(_data[length + additionalBytes]);
		}
		else
		{
			color.SetWhite(defaultColorValue);
		}
	}

	return additionalBytes;
}

