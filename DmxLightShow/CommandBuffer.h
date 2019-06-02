// CommandBuffer.h 
// Contains buffer for one command.

#ifdef _WINDOWS

#pragma once

#include <stdint.h>
#include "AsciiCommandParser.h"

#define MAX_BUFFER_LENGTH   32

class CommandBuffer
{
public:
	CommandBuffer();

	~CommandBuffer();

	// Add a character to the buffer if there is space.
	void AddChar(char charToAdd);

	// Process (parse) a command.
	void Process(AsciiCommandParser& asciiCommandParser);

private:
	char    _buffer[MAX_BUFFER_LENGTH];

	// Length of buffer that is filled.
	uint8_t _bufferLength = 0;
};

#endif // _WINDOWS