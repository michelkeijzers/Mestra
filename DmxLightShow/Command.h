#pragma once

#include "MestraTypes.h"
#include "Irgbw.h"


class Command
{
public: 
	Command();
	~Command();

	void Clear();

	par_group_t GetParGroup() const;
	void SetParGroup(par_group_t parGroup);
	
	bool GetPresetNumberSet() const;
	void SetPresetNumberSet(bool set);

	preset_t GetPresetNumber() const;
	void SetPresetNumber(preset_t presetNumber);

	bool GetDelayTimeSet() const;
	void SetDelayTimeSet(bool set);

	step_duration_t GetDelayTime() const;
	void SetDelayTime(step_duration_t time);

	bool GetStrobeTimeSet() const;
	void SetStrobeTimeSet(bool set);

	step_duration_t GetStrobeTime() const;
	void SetStrobeTime(step_duration_t time);

	bool GetStepNumberSet() const;
	void SetStepNumberSet(bool set);

	step_t GetStepNumber() const;
	void SetStepNumber(step_t stepNumber);

	bool GetLastStepNumber() const;
	void SetLastStepNumber(bool lastStepNumber);

	bool GetHoldSet() const;
	void SetHoldSet(bool set);

	bool GetHold() const;
	void SetHold(bool hold);

	bool GetOnceSet() const;
	void SetOnceSet(bool set);

	bool GetOnce() const;
	void SetOnce(bool once);

	bool GetDefaultColorSet() const;
	void SetDefaultColorSet(bool set);

	Irgbw GetDefaultColor() const;
	void SetDefaultColor(Irgbw& color);

	bool GetDefaultColorWhiteUsed() const;
	void SetDefaultColorWhiteUsed(bool used);

	bool GetAlternateColorSet() const;
	void SetAlternateColorSet(bool set);
	
	Irgbw GetAlternateColor() const;
	void SetAlternateColor(Irgbw& color);

	bool GetAlternateColorWhiteUsed() const;
	void SetAlternateColorWhiteUsed(bool used);


private:
	par_group_t		_parGroup;
	bool			_delayTimeSet;
	step_duration_t _delayTime;
	bool			_strobeTimeSet;
	step_duration_t _strobeTime;
	bool			_presetNumberSet;
	preset_t		_presetNumber;

	bool			_stepNumberSet;
	step_t			_stepNumber;
	bool			_lastStepNumber;
	bool			_holdSet;
	bool			_hold;
	bool			_onceSet;
	bool			_once;

	bool			_defaultColorSet;
	bool			_defaultColorWhiteUsed;
	Irgbw			_defaultColor;
	bool			_alternateColorSet;
	bool			_alternateColorWhiteUsed;
	Irgbw			_alternateColor;
};

