#pragma once

#include "MestraTypes.h"
#include "Irgbw.h"


const par_bits_t PAR_R4 = 1UL << 0;
const par_bits_t PAR_R3 = 1UL << 1;
const par_bits_t PAR_R2 = 1UL << 2;
const par_bits_t PAR_R1 = 1UL << 3;
const par_bits_t PAR_L1 = 1UL << 4;
const par_bits_t PAR_L2 = 1UL << 5;
const par_bits_t PAR_L3 = 1UL << 6;
const par_bits_t PAR_L4 = 1UL << 7;
const par_bits_t PAR_DR = 1UL << 8;
const par_bits_t PAR_DL = 1UL << 9;
const par_bits_t PAR_NR = 1UL << 10;
const par_bits_t PAR_NL = 1UL << 11;
const par_bits_t PAR_ER = 1UL << 12;
const par_bits_t PAR_EL = 1UL << 13;
const par_bits_t PAR_BR = 1UL << 14;
const par_bits_t PAR_BC = 1UL << 15;
const par_bits_t PAR_BL = 1UL << 16;

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


const uint8_t COMMAND_START_PAR_BITS										= 0;
const uint8_t COMMAND_START_FLAGS_1                   	= COMMAND_START_PAR_BITS                    + 4;
const uint8_t COMMAND_START_FLAGS_2                     = COMMAND_START_FLAGS_1                     + 1;
const uint8_t COMMAND_START_DEFAULT_COLOR								= COMMAND_START_FLAGS_2                     + 1;
const uint8_t COMMAND_START_ALTERNATE_COLOR							= COMMAND_START_DEFAULT_COLOR							  + 5;
const uint8_t COMMAND_START_PRESET_NUMBER								= COMMAND_START_ALTERNATE_COLOR						  + 5;
const uint8_t COMMAND_START_DELAY_TIME									= COMMAND_START_PRESET_NUMBER							  + 1;
const uint8_t COMMAND_START_STROBO_TIME									= COMMAND_START_DELAY_TIME									+ 2;

const uint8_t COMMAND_LENGTH														= COMMAND_START_STROBO_TIME								  + 1;

const uint8_t COMMAND_BIT_DEFAULT_COLOR_SET							= 0;
const uint8_t COMMAND_BIT_DEFAULT_COLOR_WHITE_USED			= 1;
const uint8_t COMMAND_BIT_ALTERNATE_COLOR_SET						= 2;
const uint8_t COMMAND_BIT_ALTERNATE_COLOR_WHITE_USED		= 3;
const uint8_t COMMAND_BIT_PRESET_NUMBER_SET							= 4;
const uint8_t COMMAND_BIT_DELAY_TIME_SET								= 5;
const uint8_t COMMAND_BIT_STROBO_TIME_SET								= 6;

const uint8_t COMMAND_BIT_TRIGGER_STATE_SET							= 0;
const uint8_t COMMAND_BIT_ACTIVATE_TRIGGER							= 1;


class Command
{
public: 
	Command();
	~Command();

	par_bits_t GetParBits() const;
	void SetParBits(par_bits_t parBits);

	bool GetDefaultColorSet() const;
	void SetDefaultColorSet(bool set);

	bool GetDefaultColorWhiteUsed() const;
	void SetDefaultColorWhiteUsed(bool set);

	bool GetAlternateColorSet() const;
	void SetAlternateColorSet(bool set);

	bool GetAlternateColorWhiteUsed() const;
	void SetAlternateColorWhiteUsed(bool set);

	bool GetPresetNumberSet() const;
	void SetPresetNumberSet(bool set);

	bool GetDelayTimeSet() const;
	void SetDelayTimeSet(bool set);

	bool GetStroboTimeSet() const;
	void SetStroboTimeSet(bool set);

	bool GetTriggerState() const;
	void SetTriggerState(bool set);

	bool GetActivateTrigger() const;
	void SetActivateTrigger(bool set);

	void GetDefaultColor(Irgbw& irgbw) const;
	void SetDefaultColor(Irgbw& irgbw);

	void GetAlternateColor(Irgbw& irgbw) const;
	void SetAlternateColor(Irgbw& irgbw);

	preset_t GetPresetNumber() const;
	void SetPresetNumber(preset_t presetNumber);

	step_duration_t GetDelayTime() const;
	void SetDelayTime(step_duration_t time);

	step_duration_t GetStroboTime() const;
	void SetStroboTime(step_duration_t time);


private:
	uint8_t _data[COMMAND_LENGTH];
};

