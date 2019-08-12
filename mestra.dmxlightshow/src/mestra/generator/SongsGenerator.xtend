package mestra.generator

import java.util.ArrayList
import java.util.List
import mestra.dmxLightShow.Sequence
import mestra.dmxLightShow.Song
import mestra.dmxLightShow.Step

class SongsGenerator 
{
	List<Byte> _mainData; 		
	List<Byte> _songData; 		
	List<Byte> _currentSequenceData; // Only used during parsing of song data
	List<Byte> _currentStepData;     // Only used during parsing of song data

	static int SONG_DATA_NR_OF_SEQUENCE_REFS_BYTE = 2;
	static int SONG_DATA_SEQUENCE_REFS_BYTE = 3; // and 4.
	
	def CharSequence toBinary(mestra.dmxLightShow.Mestra mestra) 
	{
		_mainData = new ArrayList<Byte>;

		var songs = mestra.eAllContents.filter(Song).toList;
		 
		for (Song song : songs)
		{
			processSong(song)
		}
		
		// Copy to char sequence.
		var charSequence = new StringBuilder();
		
		for (byte byteValue : _mainData)
		{
			charSequence.append(byteValue);
		}
		return charSequence.toString();
		 
	}
	
	
	protected def void processSong(Song song) 
	{
		_songData = new ArrayList<Byte>;
		
		_songData.add(song.getBank().value as byte); // 100 Bank Number
		_songData.add(song.getProgram().value as byte); // 101 Program Number
		
		_songData.add(0 as byte); // 102 #Sequences (SONG_DATA_NR_OF_SEQUENCES_BYTE)
		
		var order = song.order;
        var sequences = song.sequences;
		
		for (var orderIndex = 0; orderIndex < order.length; orderIndex++)
		{
			processSequence(orderIndex, order, sequences);
		}
	}
	
	
	def processSequence(int orderIndex, List<Sequence> order, List<Sequence> sequences) 
	{
		// Increase number of sequences.
		_songData.set  (SONG_DATA_NR_OF_SEQUENCE_REFS_BYTE,
	     (_songData.get(SONG_DATA_NR_OF_SEQUENCE_REFS_BYTE) + 1) as byte);

		// Only add sequence if not already added before.
		var isNewSequence = (order.indexOf(order.get(orderIndex)) >= orderIndex);
		if (isNewSequence)
		{
			fillCurrentSequence(order.get(orderIndex));

			_songData.add(get location of order, (_songData.size / 256) as Byte);
			_songData.add(get location of order, (_songData.size % 256) as Byte);
		
			// Add new sequence
			_songData.addAll(_currentSequenceData);
		}
		else
		{
			
		}
	}
	
	
	def void fillCurrentSequence(Sequence sequence) 
	{
		var sequenceStartByte = _songData.size; 
		_songData.add(0 as byte); // #Steps
		
		var stepRefs = sequence.stepRefs;
		var steps = sequence.steps;
				
		for (var stepRefIndex = 0; stepRefIndex < stepRefs.length; stepRefIndex++)
		{
			 processStep(stepRefIndex, stepRefs, steps);
		}
			
	}
	
	
	def processStep(int stepRefIndex, List<Step> stepRefs, List<Step> steps) 
	{
		// Only add step if not already added before.
		if (stepRefs.indexOf(stepRefs.get(stepRefIndex)) >= stepRefIndex)
		{
			addStep(stepRefs.get(stepRefIndex));
		}
		
		// Increase number of steps.
	//	_songData.set (sequenceStartByte, 
	//	 (_songData.get(sequenceStartByte) + 1) as byte);
		
	}
	
	
	def addStep(Step step) 
	{
		
	}
	
}
	