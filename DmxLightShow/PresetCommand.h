// PresetCommand.h
// Command for setting a preset.

#pragma once

#include "ClassNames.h"
#include HEADER_FILE(PAR_CLASS)
#include <stdint.h>


class PresetCommand
{
public:
	PresetCommand();

	~PresetCommand();

	void Run(uint32_t parBits, uint16_t presetNumber);

private:
	void CommandAllOff(Par& par);

	void SetFixturePreset(uint16_t presetNumber, uint8_t parNumber, uint8_t selectedParIndex, uint8_t nrOfPars);

	void SetFixedIrgb(Par& par, Irgbw& color, uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue);

	void SetFixedIrgbw(Par& par, Irgbw& color, uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
};

