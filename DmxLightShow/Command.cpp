#include "Command.h"
#include "BitsUtils.h"
#include "Irgbw.h"


Command::Command()
	:
	_data{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
{
}


Command::~Command()
{
}


par_bits_t Command::GetParBits()
{
	return (par_bits_t)
		((uint32_t)(_data[COMMAND_START_PAR_BITS]) << 24U) +
		((uint32_t)(_data[COMMAND_START_PAR_BITS + 1U]) << 16U) +
		((uint32_t)(_data[COMMAND_START_PAR_BITS + 2U]) << 8U) +
		(_data[COMMAND_START_PAR_BITS + 3U]);
}


void Command::SetParBits(par_bits_t parBits)
{
	_data[COMMAND_START_PAR_BITS] = (parBits >> 24U);
	_data[COMMAND_START_PAR_BITS + 1U] = ((parBits >> 16U) % 256U);
	_data[COMMAND_START_PAR_BITS + 2U] = ((parBits >> 8U) % 256U);
	_data[COMMAND_START_PAR_BITS + 3U] = (parBits % 256U);
}


bool Command::GetDefaultColorSet()
{
	return (bool)(_data[COMMAND_START_FLAGS] & (1 << COMMAND_BIT_DEFAULT_COLOR_SET));
}

void Command::SetDefaultColorSet(bool set)
{
	_data[COMMAND_START_FLAGS] = (uint8_t)
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS], COMMAND_BIT_DEFAULT_COLOR_SET, set);
}


bool Command::GetDefaultColorWhiteUsed()
{
	return (bool)(_data[COMMAND_START_FLAGS] & (1 << COMMAND_BIT_DEFAULT_COLOR_WHITE_USED));
}


void Command::SetDefaultColorWhiteUsed(bool set)
{
	_data[COMMAND_START_FLAGS] = (uint8_t)
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS], COMMAND_BIT_DEFAULT_COLOR_WHITE_USED, set);
}



bool Command::GetAlternateColorSet()
{
	return (bool)(_data[COMMAND_START_FLAGS] & (1 << COMMAND_BIT_ALTERNATE_COLOR_SET));
}

void Command::SetAlternateColorSet(bool set)
{
	_data[COMMAND_START_FLAGS] = (uint8_t)
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS], COMMAND_BIT_ALTERNATE_COLOR_SET, set);
}


bool Command::GetAlternateColorWhiteUsed()
{
	return (bool)(_data[COMMAND_START_FLAGS] & (1 << COMMAND_BIT_ALTERNATE_COLOR_WHITE_USED));
}


void Command::SetAlternateColorWhiteUsed(bool set)
{
	_data[COMMAND_START_FLAGS] = (uint8_t)
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS], COMMAND_BIT_ALTERNATE_COLOR_WHITE_USED, set);
}


bool Command::GetPresetNumberSet()
{
	return (bool)(_data[COMMAND_START_FLAGS] & (1 << COMMAND_BIT_PRESET_NUMBER_SET));
}


void Command::SetPresetNumberSet(bool set)
{
	_data[COMMAND_START_FLAGS] = (uint8_t)
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS], COMMAND_BIT_PRESET_NUMBER_SET, set);
}


bool Command::GetDelayTimeSet()
{
	return (bool)(_data[COMMAND_START_FLAGS] & (1 << COMMAND_BIT_DELAY_TIME_SET));
}


void Command::SetDelayTimeSet(bool set)
{
	_data[COMMAND_START_FLAGS] = (uint8_t)
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS], COMMAND_BIT_DELAY_TIME_SET, set);
}


bool Command::GetStrobeTimeSet()
{
	return (bool)(_data[COMMAND_START_FLAGS] & (1 << COMMAND_BIT_STROBE_TIME_SET));
}


void Command::SetStrobeTimeSet(bool set)
{
	_data[COMMAND_START_FLAGS] = (uint8_t)
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS], COMMAND_BIT_STROBE_TIME_SET, set);
}


void Command::GetDefaultColor(Irgbw& irgbw)
{
	irgbw.SetIrgbw(
		_data[COMMAND_START_DEFAULT_COLOR    ],
		_data[COMMAND_START_DEFAULT_COLOR + 1],
		_data[COMMAND_START_DEFAULT_COLOR + 2],
		_data[COMMAND_START_DEFAULT_COLOR + 3],
		_data[COMMAND_START_DEFAULT_COLOR + 4]);
}


void Command::SetDefaultColor(Irgbw& irgbw)
{
	_data[COMMAND_START_DEFAULT_COLOR    ] = irgbw.GetIntensity();
	_data[COMMAND_START_DEFAULT_COLOR + 1] = irgbw.GetRed();
	_data[COMMAND_START_DEFAULT_COLOR + 2] = irgbw.GetGreen();
	_data[COMMAND_START_DEFAULT_COLOR + 3] = irgbw.GetBlue();
	_data[COMMAND_START_DEFAULT_COLOR + 4] = irgbw.GetWhite();
}


void Command::GetAlternateColor(Irgbw& irgbw)
{
	irgbw.SetIrgbw(
		_data[COMMAND_START_ALTERNATE_COLOR],
		_data[COMMAND_START_ALTERNATE_COLOR + 1],
		_data[COMMAND_START_ALTERNATE_COLOR + 2],
		_data[COMMAND_START_ALTERNATE_COLOR + 3],
		_data[COMMAND_START_ALTERNATE_COLOR + 4]);
}


void Command::SetAlternateColor(Irgbw& irgbw)
{
	_data[COMMAND_START_ALTERNATE_COLOR] = irgbw.GetIntensity();
	_data[COMMAND_START_ALTERNATE_COLOR + 1] = irgbw.GetRed();
	_data[COMMAND_START_ALTERNATE_COLOR + 2] = irgbw.GetGreen();
	_data[COMMAND_START_ALTERNATE_COLOR + 3] = irgbw.GetBlue();
	_data[COMMAND_START_ALTERNATE_COLOR + 4] = irgbw.GetWhite();

}


preset_t Command::GetPresetNumber()
{
	return _data[COMMAND_START_PRESET_NUMBER];
}


void Command::SetPresetNumber(preset_t presetNumber)
{
	_data[COMMAND_START_PRESET_NUMBER] = presetNumber;
}


step_duration_t Command::GetDelayTime()
{
	return _data[COMMAND_START_DELAY_TIME + 1] * 256 + _data[COMMAND_START_DELAY_TIME];
}


void Command::SetDelayTime(step_duration_t time)
{
	_data[COMMAND_START_DELAY_TIME + 1] = (uint8_t) (time / 256);
	_data[COMMAND_START_DELAY_TIME] = time % 256;
}


step_duration_t Command::GetStroboTime()
{
	return _data[COMMAND_START_STROBO_TIME + 1] * 256 + _data[COMMAND_START_STROBO_TIME];
}


void Command::SetStroboTime(step_duration_t time)
{
	_data[COMMAND_START_STROBO_TIME + 1] = (uint8_t) (time / 256);
	_data[COMMAND_START_STROBO_TIME] = time % 256;
}


uint8_t Command::GetCrc()
{
	return _data[COMMAND_START_CRC];
}


void Command::CalculateCrc()
{
	uint8_t crc = 0;
	for (uint8_t index = 0; index < COMMAND_LENGTH - 1; index++) // Exclude CRC
	{
		crc += _data[index];
	}

	_data[COMMAND_START_CRC] = crc;
}
