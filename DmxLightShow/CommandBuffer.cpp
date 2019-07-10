// CommandBuffer.cpp
// Contains buffer for one command.

#ifdef _WINDOWS

#include "CommandBuffer.h"
#include "StringUtils.h"
#include "AsciiCommandParser.h"


CommandBuffer::CommandBuffer()
	: _bufferLength(0)
{
	_buffer[0] = '\0';
}


CommandBuffer::~CommandBuffer()
{
}


void CommandBuffer::AddChar(char charToAdd)
{
	if (_bufferLength < COMMAND_BUFFER_MAX_LENGTH)
	{
		_buffer[_bufferLength++] = charToAdd;
	}
}


void CommandBuffer::Process(AsciiCommandParser& asciiCommandParser)
{
	if (_bufferLength > 0 && (_buffer[_bufferLength - 1] == '\n' || _buffer[_bufferLength - 1] == '\r'))
	{
		_buffer[_bufferLength - 1] = '\0';

		StringUtils::TrimWhitespace(_buffer);
		StringUtils::ToUpper(_buffer);

	    asciiCommandParser.Parse(_buffer);

		_buffer[0] = '\0';
		_bufferLength = 0;
	}
}

#endif // _WINDOWS