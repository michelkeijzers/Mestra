// CommandBuffer.cpp
// Contains buffer for one command.

#include "CommandBuffer.h"
#include "CharUtils.h"
#include "StringUtils.h"
#include <string.h>
#include "CommandParser.h"


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
	if (_bufferLength < MAX_BUFFER_LENGTH)
	{
		_buffer[_bufferLength++] = charToAdd;
	}
}


void CommandBuffer::Process()
{
	if ((_bufferLength > 0) && ((_buffer[_bufferLength - 1] == '\n') || (_buffer[_bufferLength - 1] == '\r')))
	{
		_buffer[_bufferLength - 1] = '\0';

		StringUtils::TrimWhitespace(_buffer);
		StringUtils::ToUpper(_buffer);

		CommandParser parser;
		parser.Parse(_buffer);

		_buffer[0] = '\0';
		_bufferLength = 0;
	}
}