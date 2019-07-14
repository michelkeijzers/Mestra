// PresetCommand.h
// Command for setting a preset.

#pragma once

#include "Par.h"
#include "MestraTypes.h"


class PresetCommand
{
public:
	static void Run(par_group_t parGroup, Par& par, preset_t presetNumber);

private:
	PresetCommand();
	~PresetCommand();

	static void CommandAllOff(Par& par);
	
	static void SetFixturePreset(Par& par, fixture_number_t parIndexInGroup, fixture_number_t nrOfParsInGroup, preset_t presetNumber);
	
	static void SetFixedIrgb(Par& par, Irgbw& color,
		intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue);
	static void SetFixedIrgbw(Par& par, Irgbw& color,
		intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue, intensity_t white);
};

