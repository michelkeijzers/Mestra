#include "Trigger.h"

Trigger::Trigger()
{
}

bool Trigger::GetIsEnabled() const
{
	return (_data[0] & 0x80) == 0x80; // MSB
}

void Trigger::SetIsEnabled(bool enabled)
{
	_data[0] = static_cast<unsigned char>((_data[0] & 0x7F) + (enabled ? 0x80 : 0x00));
}
 

Trigger::EMidiTriggerType Trigger::GetMidiTriggerType() const
{
	return static_cast<EMidiTriggerType>(_data[0] & 0x0F);
}

void Trigger::SetMidiTriggerType(EMidiTriggerType midiTriggerType)
{
	_data[0] = static_cast<unsigned char>((_data[0] & 0x80) + static_cast<unsigned char >(midiTriggerType));   // MIDI = 000 (bits 6~4
}


int Trigger::GetMidiChannel() const
{
	return _data[1];
}

void Trigger::SetMidiChannel(int midiChannel)
{
	_data[1] = static_cast<unsigned char>(midiChannel);
}


bool Trigger::GetIsGroup() const
{
	return (_data[2] & 0x80) == 0x80;
}

void Trigger::SetIsGroup(bool isGroup)
{
	_data[2] = static_cast<unsigned char>((_data[2] & 0x7F) + (isGroup ? 0x80 : 0x00));
}


bool Trigger::GetAll() const
{
	return (_data[2] & 0x40) == 0x40;
}

void Trigger::SetAll(bool all)
{
	_data[2] = static_cast<unsigned char>((_data[2] & 0xBF) + (all ? 0x40 : 0x00));
}


int Trigger::GetGroup() const
{
	return (_data[2] & 0x3C) >> 2;
}

void Trigger::SetGroup(int group)
{
	_data[2] = static_cast<unsigned char>((_data[2] & 0xC3) + (group << 2));
}


int Trigger::GetValue() const
{
	return _data[2] & 0x7F;
}

void Trigger::SetValue(int value)
{
	_data[2] = static_cast<unsigned char>((_data[2] & 0x80) + value);
}

/// <summary>
/// Copy data.
/// </summary>
/// <returns></returns>
void Trigger::Clone(Trigger* trigger)
{
	this[0] = trigger[0];
	this[1] = trigger[1];
	this[2] = trigger[2];
}
