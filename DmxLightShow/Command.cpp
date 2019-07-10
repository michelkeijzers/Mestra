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


void Command::Clear()
{
	for (uint8_t index = 0; index < COMMAND_LENGTH; index++)
	{
		_data[index] = 0;
	}
}


par_bits_t Command::GetParBits() const
{
	return par_bits_t(uint32_t(_data[COMMAND_START_PAR_BITS     ]) << 24U) +
		               (uint32_t(_data[COMMAND_START_PAR_BITS + 1U]) << 16U) +
		               (uint32_t(_data[COMMAND_START_PAR_BITS + 2U]) <<  8U) +
		                         _data[COMMAND_START_PAR_BITS + 3U];
}


void Command::SetParBits(par_bits_t parBits)
{
	_data[COMMAND_START_PAR_BITS]      =  parBits >> 24U;
	_data[COMMAND_START_PAR_BITS + 1U] = (parBits >> 16U) % 256U;
	_data[COMMAND_START_PAR_BITS + 2U] = (parBits >>  8U) % 256U;
	_data[COMMAND_START_PAR_BITS + 3U] =  parBits         % 256U;
}


bool Command::GetDefaultColorSet() const
{
	return bool(_data[COMMAND_START_FLAGS_1] & 1 << COMMAND_BIT_DEFAULT_COLOR_SET);
}

void Command::SetDefaultColorSet(bool set)
{
	_data[COMMAND_START_FLAGS_1] = uint8_t(
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS_1], COMMAND_BIT_DEFAULT_COLOR_SET, set));
}


bool Command::GetDefaultColorWhiteUsed() const
{
	return bool(_data[COMMAND_START_FLAGS_1] & 1 << COMMAND_BIT_DEFAULT_COLOR_WHITE_USED);
}


void Command::SetDefaultColorWhiteUsed(bool set)
{
	_data[COMMAND_START_FLAGS_1] = uint8_t(
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS_1], COMMAND_BIT_DEFAULT_COLOR_WHITE_USED, set));
}



bool Command::GetAlternateColorSet() const
{
	return bool(_data[COMMAND_START_FLAGS_1] & 1 << COMMAND_BIT_ALTERNATE_COLOR_SET);
}

void Command::SetAlternateColorSet(bool set)
{
	_data[COMMAND_START_FLAGS_1] = uint8_t(
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS_1], COMMAND_BIT_ALTERNATE_COLOR_SET, set));
}


bool Command::GetAlternateColorWhiteUsed() const
{
	return bool(_data[COMMAND_START_FLAGS_1] & 1 << COMMAND_BIT_ALTERNATE_COLOR_WHITE_USED);
}


void Command::SetAlternateColorWhiteUsed(bool set)
{
	_data[COMMAND_START_FLAGS_1] = uint8_t(
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS_1], COMMAND_BIT_ALTERNATE_COLOR_WHITE_USED, set));
}


bool Command::GetPresetNumberSet() const
{
	return bool(_data[COMMAND_START_FLAGS_1] & 1 << COMMAND_BIT_PRESET_NUMBER_SET);
}


void Command::SetPresetNumberSet(bool set)
{
	_data[COMMAND_START_FLAGS_1] = uint8_t(
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS_1], COMMAND_BIT_PRESET_NUMBER_SET, set));
}


bool Command::GetDelayTimeSet() const
{
	return bool(_data[COMMAND_START_FLAGS_1] & 1 << COMMAND_BIT_DELAY_TIME_SET);
}


void Command::SetDelayTimeSet(bool set)
{
	_data[COMMAND_START_FLAGS_1] = uint8_t(
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS_1], COMMAND_BIT_DELAY_TIME_SET, set));
}


bool Command::GetStroboTimeSet() const
{
	return bool(_data[COMMAND_START_FLAGS_1] & 1 << COMMAND_BIT_STROBO_TIME_SET);
}


void Command::SetStroboTimeSet(bool set)
{
	_data[COMMAND_START_FLAGS_1] = uint8_t(
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS_1], COMMAND_BIT_STROBO_TIME_SET, set));
}


bool Command::GetTriggerStateSet() const
{
	return bool(_data[COMMAND_START_FLAGS_1] & 1 << COMMAND_BIT_TRIGGER_STATE_SET);
}


void Command::SetTriggerStateSet(bool set)
{
	_data[COMMAND_START_FLAGS_1] = uint8_t(
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS_1], COMMAND_BIT_TRIGGER_STATE_SET, set));
}


bool Command::GetActivateTriggerSet() const
{
	return bool(_data[COMMAND_START_FLAGS_2] & 1 << COMMAND_BIT_ACTIVATE_TRIGGER);
}


void Command::SetActivateTriggerSet(bool set)
{
	_data[COMMAND_START_FLAGS_2] = uint8_t(
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS_2], COMMAND_BIT_ACTIVATE_TRIGGER, set));
}


void Command::GetDefaultColor(Irgbw& irgbw) const
{
	irgbw.SetIrgbw(
		_data[COMMAND_START_DEFAULT_COLOR    ],
		_data[COMMAND_START_DEFAULT_COLOR + 1],
		_data[COMMAND_START_DEFAULT_COLOR + 2],
		_data[COMMAND_START_DEFAULT_COLOR + 3],
		_data[COMMAND_START_DEFAULT_COLOR + 4]); // TODO: Use ClosestRed/... ?
}


void Command::SetDefaultColor(Irgbw& irgbw)
{
	_data[COMMAND_START_DEFAULT_COLOR    ] = irgbw.GetIntensity();
	_data[COMMAND_START_DEFAULT_COLOR + 1] = irgbw.GetRed();
	_data[COMMAND_START_DEFAULT_COLOR + 2] = irgbw.GetGreen();
	_data[COMMAND_START_DEFAULT_COLOR + 3] = irgbw.GetBlue();
	_data[COMMAND_START_DEFAULT_COLOR + 4] = irgbw.GetWhite();
}


void Command::GetAlternateColor(Irgbw& irgbw) const
{
	irgbw.SetIrgbw(
		_data[COMMAND_START_ALTERNATE_COLOR],
		_data[COMMAND_START_ALTERNATE_COLOR + 1],
		_data[COMMAND_START_ALTERNATE_COLOR + 2],
		_data[COMMAND_START_ALTERNATE_COLOR + 3],
		_data[COMMAND_START_ALTERNATE_COLOR + 4]); // TODO: Use ClosestRed/... ?
}


void Command::SetAlternateColor(Irgbw& irgbw)
{
	_data[COMMAND_START_ALTERNATE_COLOR] = irgbw.GetIntensity();
	_data[COMMAND_START_ALTERNATE_COLOR + 1] = irgbw.GetRed();
	_data[COMMAND_START_ALTERNATE_COLOR + 2] = irgbw.GetGreen();
	_data[COMMAND_START_ALTERNATE_COLOR + 3] = irgbw.GetBlue();
	_data[COMMAND_START_ALTERNATE_COLOR + 4] = irgbw.GetWhite();

}


preset_t Command::GetPresetNumber() const
{
	return _data[COMMAND_START_PRESET_NUMBER];
}


void Command::SetPresetNumber(preset_t presetNumber)
{
	_data[COMMAND_START_PRESET_NUMBER] = uint8_t(presetNumber);
}


bool Command::GetTriggerState() const
{
	return bool(_data[COMMAND_START_FLAGS_2] & 1 << COMMAND_BIT_TRIGGER_STATE);
}


void Command::SetTriggerState(bool set)
{
	_data[COMMAND_START_FLAGS_2] = uint8_t(
		BitsUtils::ChangeBit(_data[COMMAND_START_FLAGS_2], COMMAND_BIT_TRIGGER_STATE, set));
}


step_duration_t Command::GetDelayTime() const
{
	return step_duration_t(
	 _data[COMMAND_START_DELAY_TIME + 1] * 256 + 
	 _data[COMMAND_START_DELAY_TIME]);
}


void Command::SetDelayTime(step_duration_t time)
{
	_data[COMMAND_START_DELAY_TIME + 1] = uint8_t(time / 256);
	_data[COMMAND_START_DELAY_TIME    ] = uint8_t(time % 256);
}


step_duration_t Command::GetStroboTime() const
{
	return step_duration_t(
	 _data[COMMAND_START_STROBO_TIME + 1] * 256 + 
		_data[COMMAND_START_STROBO_TIME]);
}


void Command::SetStroboTime(step_duration_t time)
{
	_data[COMMAND_START_STROBO_TIME + 1] = uint8_t(time / 256);
	_data[COMMAND_START_STROBO_TIME    ] = uint8_t(time % 256);
}
