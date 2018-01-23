#include <cstddef>

class Trigger
{
	unsigned char _data[3];

public:
	enum EMidiTriggerType
	{
		NoteOn = 0x8,
		NoteOff = 0x9
	};

	Trigger();

	bool GetIsEnabled() const;
	void SetIsEnabled(bool enabled);

	EMidiTriggerType GetMidiTriggerType() const;
	void SetMidiTriggerType(EMidiTriggerType midiTriggerType);

	int GetMidiChannel() const;
	void SetMidiChannel(int midiChannel);

	bool GetIsGroup() const;
	void SetIsGroup(bool group);

	bool GetAll() const;
	void SetAll(bool All);

	int GetGroup() const;
	void SetGroup(int group);

	int GetValue() const;
	void SetValue(int value);

	/// <summary>
	/// Copy data.
	/// </summary>
	/// <returns></returns>
	void Clone(Trigger* trigger);
}; 
