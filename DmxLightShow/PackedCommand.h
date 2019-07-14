#pragma once

#include "MestraTypes.h"


class Command;
class Irgbw;

const uint8_t COMMAND_MAX_LENGTH = 33; // Length + Par Group + Flags + Step Number Choices + Strobe Speed (2) +
									   // Preset Number + Step Number (2) + Delay Time (2) + twice Long Form Color (22)



class PackedCommand
{
public:
	PackedCommand();
	~PackedCommand();
	void Pack(const Command& command);

	void Unpack(Command& command);
	
private:
	uint8_t _data[COMMAND_MAX_LENGTH];

	void PackStepNumber(const Command& command, uint8_t& length);

	void PackColor(uint8_t length, Irgbw color, bool whiteUsed);

	static bool CountColorValue(Irgbw color, bool whiteUsed, uint8_t valueToCount);

	void PackAdditionalColorBytes(uint8_t length, Irgbw color, uint8_t defaultColorValue,
		bool whiteUsed, uint8_t colorByte);

	void PackAdditionalColorByte(uint8_t& length, uint8_t colorByte,
		uint8_t colorValue, uint8_t defaultColorValue, uint8_t colorBit);

	void UnpackColors(uint8_t& length, Irgbw color, uint8_t colorByte, bool whiteUsed);
};

