
#include "Command.h"
#include "ParGroups.h"


Command::Command()
/*
_parGroup(0),
_delayTimeSet(false),
_delayTime(0),
_strobeTimeSet(false),
_strobeTime(0),
_presetNumberSet(false),
_presetNumber(0),
_stepNumberSet(false),
_stepNumber(0),
_lastStepNumber(false),
_holdSet(false),
_hold(false),
_onceSet(false),
_once(false),
_defaultColorSet(false),
_defaultColor(Irgbw()),
_defaultColorWhiteUsed(false),
_alternateColorSet(false),
_alternateColor(Irgbw()),
_alternateColorWhiteUsed(false)
*/
{
	Clear();
}



Command::~Command()
{
}


void Command::Clear()
{
	_parGroup = 0;
	_delayTimeSet = false;
	_delayTime = 0;
	_strobeTimeSet = false;
	_strobeTime = 0;
	_presetNumberSet = false;
	_presetNumber = 0;
	_stepNumberSet = false;
	_stepNumber = 0;
	_lastStepNumber = false;
	_holdSet = false;
	_hold = false;
	_onceSet = false;
	_once = false;
	_defaultColorSet = false;
	_defaultColor.Clear();
	_defaultColorWhiteUsed = false;
	_alternateColorSet = false;
	_alternateColor.Clear();
	_alternateColorWhiteUsed = false;
}

par_group_t Command::GetParGroup() const
{
	return _parGroup;
}


void Command::SetParGroup(par_group_t parGroup)
{
	_parGroup = parGroup;
}


bool Command::GetPresetNumberSet() const
{
	return _presetNumberSet;
}


void Command::SetPresetNumberSet(bool set)
{
	_presetNumberSet = set;
}


preset_t Command::GetPresetNumber() const
{
	return _presetNumber;
}


void Command::SetPresetNumber(preset_t presetNumber)
{
	_presetNumber = presetNumber;
}


bool Command::GetDelayTimeSet() const
{
	return _delayTimeSet;
}


void Command::SetDelayTimeSet(bool set)
{
	_delayTimeSet = set;
}


step_duration_t Command::GetDelayTime() const
{
	return _delayTime;
}


void Command::SetDelayTime(step_duration_t delayTime)
{
	_delayTime = delayTime;
}


bool Command::GetStrobeTimeSet() const
{
	return _strobeTimeSet;
}


void Command::SetStrobeTimeSet(bool set)
{
	_strobeTimeSet = set;
}


step_duration_t Command::GetStrobeTime() const
{
	return _strobeTime;
}


void Command::SetStrobeTime(step_duration_t strobeTime)
{
	_strobeTime = strobeTime;
}


bool Command::GetStepNumberSet() const
{
	return _stepNumberSet;
}


void Command::SetStepNumberSet(bool set)
{
	_stepNumberSet = set;
}


step_t Command::GetStepNumber() const
{
	return _stepNumber;
}


void Command::SetStepNumber(step_t stepNumber)
{
	_stepNumber = stepNumber;
}

bool Command::GetLastStepNumber() const
{
	return _lastStepNumber;
}


void Command::SetLastStepNumber(bool lastStepNumber)
{
	_lastStepNumber = lastStepNumber;
}


bool Command::GetHoldSet() const
{
	return _holdSet;
}


void Command::SetHoldSet(bool set)
{
	_holdSet = set;
}


bool Command::GetHold() const
{
	return _hold;
}


void Command::SetHold(bool hold)
{
	_hold = hold;
}


bool Command::GetOnceSet() const
{
	return _onceSet;
}


void Command::SetOnceSet(bool set)
{
	_onceSet = set;
}


bool Command::GetOnce() const
{
	return _once;
}


void Command::SetOnce(bool once)
{
	_once = once;
}


bool Command::GetDefaultColorSet() const
{
	return _defaultColorSet;
}


void Command::SetDefaultColorSet(bool set)
{
	_defaultColorSet = set;
}


Irgbw Command::GetDefaultColor() const
{
	return _defaultColor;
}


void Command::SetDefaultColor(Irgbw& color)
{
	_defaultColor = color;
}



bool Command::GetDefaultColorWhiteUsed() const
{
	return _defaultColorWhiteUsed;
}


void Command::SetDefaultColorWhiteUsed(bool used)
{
	_defaultColorWhiteUsed = used;
}


bool Command::GetAlternateColorSet() const
{
	return _alternateColorSet;
}


void Command::SetAlternateColorSet(bool set)
{
	_alternateColorSet = set;
}



Irgbw Command::GetAlternateColor() const
{
	return _alternateColor;
}


void Command::SetAlternateColor(Irgbw& color)
{
	_alternateColor = color;
}


bool Command::GetAlternateColorWhiteUsed() const
{
	return _alternateColorWhiteUsed;
}


void Command::SetAlternateColorWhiteUsed(bool used)
{
	_alternateColorWhiteUsed = used;
}

