#include "Command.h"
#include "PackedCommand.h"
#include "Commands.h"
#include "CommandParser.h"


Commands::Commands()
{

}


Commands::~Commands()
{

}


void Commands::Unpack()
{
	Command       command;
	PackedCommand packedCommand;
	
	packedCommand.Unpack(command);
	CommandParser::Parse(command);
}