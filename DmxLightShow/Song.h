#pragma once

#include "MestraTypes.h"

typedef uint16_t song_ref_t;

const uint16_t COMMANDS_STORAGE_BYTES = (1024 * 3);


class Song
{
public:
	Song();
	~Song();

	void Clear();
	void Unpack();

private:
	song_ref_t GetSongRef();
	
	song_ref_t GetPackedCommandsRef();
	song_ref_t GetPackedTriggersRef();
	
	song_ref_t GetUnpackedCommandsFromSongRef();
	song_ref_t GetUnpackedCommandsFromSequenceRef();
	song_ref_t GetUnpackedCommandsFromStepRef();

	song_ref_t GetUnpackedTriggersFromSongRef();
	song_ref_t GetUnpackedTriggersFromSequenceRef();
	song_ref_t GetUnpackedTriggersFromStepRef();

	uint8_t GetNrOfSequences();
	song_ref_t GetSequenceRef(uint8_t sequenceIndex);

	uint8_t _data[COMMANDS_STORAGE_BYTES];

	uint8_t _currentSequence;
	uint8_t _currentStep; // within sequence
};

