#pragma once

#include "MestraTypes.h"


class Command;
class Irgbw;


const uint8_t COMMAND_MAX_LENGTH = 33; // Length + Par Group + Flags + Step Number Choices + Strobe Speed (2) +
									   // Preset Number + Step Number (2) + Delay Time (2) + twice Long Form Color (22)


enum EStepNumber
{
	NotSet,
	Set,
	Zero,
	Last
};

enum EColorForm
{
	Short,
	Medium,
	Single,
	Long
};

enum ESingleColor
{
	Red,
	Green,
	Blue,
	White
};


class PackedCommand
{
public:
	PackedCommand();
	~PackedCommand();

	uint8_t Pack(const Command& command);

	uint8_t Unpack(Command& command);
	
private:
	uint8_t _data[COMMAND_MAX_LENGTH];

	uint8_t PackStepNumber(const Command& command, uint8_t length);

	void PackShortFormColor(const uint8_t& length, const dmx_value_t& intensity, 
		const dmx_value_t& red, const dmx_value_t& green, const dmx_value_t& blue, bool whiteUsed, const dmx_value_t& white);

	void PackMediumFormColor(const uint8_t& length, dmx_value_t& intensity, 
		const dmx_value_t& red, const dmx_value_t& green, const dmx_value_t& blue, bool whiteUsed, const dmx_value_t& white);

	void PackSingleFormColor(const uint8_t& length, 
		const dmx_value_t& red, const dmx_value_t& green, const dmx_value_t& blue, const dmx_value_t& white);

	uint8_t PackLongFormColor(const uint8_t& length, const Irgbw& color, bool whiteUsed);

	uint8_t PackColor(uint8_t length, Irgbw color, bool whiteUsed);

	static bool CountColorValue(Irgbw color, bool whiteUsed, uint8_t valueToCount);

	uint8_t PackAdditionalColorBytes(uint8_t length, Irgbw color, uint8_t defaultColorValue,
		bool whiteUsed, uint8_t colorByte);

	uint8_t PackAdditionalColorByte(uint8_t& length, uint8_t colorByte,
		uint8_t colorValue, uint8_t defaultColorValue, uint8_t colorBit);

	uint8_t UnpackColors(uint8_t length, uint8_t colorByte, Irgbw &color,  bool &whiteUsed);

	void UnpackMediumFormColor(const uint8_t colorByte, Irgbw& color, bool& whiteUsed);

	void UnpackSingleFormColor(Irgbw& color, bool& whiteUsed, const uint8_t& colorByte);
	
	uint8_t UnpackLongFormColor(uint8_t length, uint8_t colorByte, Irgbw& color, bool& whiteUsed);
};

