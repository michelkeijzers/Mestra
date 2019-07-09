// PresetCommand.h
// Command for setting a preset.

#pragma once

#include "Par.h"
#include "MestraTypes.h"


class PresetCommand
{
public:
	static void Run(par_bits_t parBits, preset_t presetNumber);

private:
	PresetCommand();
	~PresetCommand();

	static void CommandAllOff(Par& par);
	
	static void SetFixturePreset(preset_t presetNumber, fixture_number_t parNumber,
		fixture_number_t selectedParIndex, fixture_number_t nrOfPars);
	
	static void SetFixedIrgb(Par& par, Irgbw& color,
		intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue);
	static void SetFixedIrgbw(Par& par, Irgbw& color,
		intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue, intensity_t white);
};

