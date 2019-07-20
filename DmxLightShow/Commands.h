#pragma once

#include "MestraTypes.h"


const uint16_t COMMANDS_STORAGE_BYTES = 4 * 1024;


class Commands
{
public:
	Commands();
	~Commands();

	void Unpack();

private:
	uint8_t _packedCommands[COMMANDS_STORAGE_BYTES];
};

