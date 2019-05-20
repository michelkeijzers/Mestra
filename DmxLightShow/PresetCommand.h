// PresetCommand.h
// Command for setting a preset.

#pragma once

#include "ClassNames.h"
#include "Par.h"
#include <stdint.h>
#include "MestraTypes.h"


class PresetCommand
{
public:
	PresetCommand();

	~PresetCommand();


	void Run(par_bits_t parBits, preset_t presetNumber);

private:
	void CommandAllOff(Par& par);


	void SetFixturePreset(preset_t presetNumber, fixture_number_t parNumber, 
		intensity_t selectedParIndex, intensity_t nrOfPars);


	void SetFixedIrgb(Par& par, Irgbw& color, 
		intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue);

	void SetFixedIrgbw(Par& par, Irgbw& color, 
		intensity_t intensity, intensity_t red, intensity_t green, intensity_t blue, intensity_t white);
};

