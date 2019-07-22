#include "Command.h"
#include "PackedCommand.h"
#include "Song.h"
#include "CommandParser.h"
#include "MestraTypes.h"
#include "BitsUtils.h"
#include "AssertUtils.h"


const uint8_t SONG_REF_BYTE								= 0;
const uint8_t PACKED_COMMANDS_REF_BYTE					= SONG_REF_BYTE + 2;
const uint8_t PACKED_TRIGGERS_REF_BYTE					= PACKED_COMMANDS_REF_BYTE + 2;

const uint8_t UNPACKED_COMMANDS_FROM_SONG_REF_BYTE		= PACKED_TRIGGERS_REF_BYTE + 2;
const uint8_t UNPACKED_COMMANDS_FROM_SEQUENCE_REF_BYTE	= UNPACKED_COMMANDS_FROM_SONG_REF_BYTE + 2;
const uint8_t UNPACKED_COMMANDS_FROM_STEP_REF_BYTE		= UNPACKED_COMMANDS_FROM_SEQUENCE_REF_BYTE + 2;

const uint8_t UNPACKED_TRIGGERS_FROM_SONG_REF_BYTE		= UNPACKED_COMMANDS_FROM_STEP_REF_BYTE + 2;
const uint8_t UNPACKED_TRIGGERS_FROM_SEQUENCE_REF_BYTE	= UNPACKED_TRIGGERS_FROM_SONG_REF_BYTE + 2;
const uint8_t UNPACKED_TRIGGERS_FROM_STEP_REF_BYTE		= UNPACKED_TRIGGERS_FROM_SEQUENCE_REF_BYTE + 2;

const uint8_t NR_OF_SEQUENCES_BYTE						= UNPACKED_TRIGGERS_FROM_STEP_REF_BYTE + 2;



Song::Song()
:
	_currentSequence(0),
	_currentStep(0)
{

}


Song::~Song()
{

}


void Song::Clear()
{

}


song_ref_t Song::GetSongRef()
{
	return BitsUtils::GetUint16(_data, SONG_REF_BYTE);
}

song_ref_t Song::GetPackedCommandsRef()
{
	return BitsUtils::GetUint16(_data, PACKED_COMMANDS_REF_BYTE);
}


song_ref_t Song::GetPackedTriggersRef()
{
	return BitsUtils::GetUint16(_data, PACKED_TRIGGERS_REF_BYTE);
}


song_ref_t Song::GetUnpackedCommandsFromSongRef()
{
	return BitsUtils::GetUint16(_data, UNPACKED_COMMANDS_FROM_SONG_REF_BYTE);
}


song_ref_t Song::GetUnpackedCommandsFromSequenceRef()
{
	return BitsUtils::GetUint16(_data, UNPACKED_COMMANDS_FROM_SEQUENCE_REF_BYTE);
}


song_ref_t Song::GetUnpackedCommandsFromStepRef()
{
	return BitsUtils::GetUint16(_data, UNPACKED_COMMANDS_FROM_STEP_REF_BYTE);
}


song_ref_t Song::GetUnpackedTriggersFromSongRef()
{
	return BitsUtils::GetUint16(_data, UNPACKED_TRIGGERS_FROM_SONG_REF_BYTE);
}


song_ref_t Song::GetUnpackedTriggersFromSequenceRef()
{
	return BitsUtils::GetUint16(_data, UNPACKED_TRIGGERS_FROM_SEQUENCE_REF_BYTE);
}


song_ref_t Song::GetUnpackedTriggersFromStepRef()
{
	return BitsUtils::GetUint16(_data, UNPACKED_TRIGGERS_FROM_STEP_REF_BYTE);
}


uint8_t Song::GetNrOfSequences()
{
	return _data[NR_OF_SEQUENCES_BYTE];
}


song_ref_t Song::GetSequenceRef(uint8_t sequenceIndex)
{
	AssertUtils::MyAssert(sequenceIndex < GetNrOfSequences());

	return BitsUtils::GetUint16(_data, NR_OF_SEQUENCES_BYTE + 2 * sequenceIndex);
}




void Song::Unpack()
{
	Command       command;
	PackedCommand packedCommand;
	
	packedCommand.Unpack(command);
	CommandParser::Parse(command);
}