// DmxSimpleStub.cpp
// Stub for Arduino DmxSimple DMX512 library.

#ifdef _WINDOWS

#include "DmxSimpleStub.h"

DmxSimpleClass DmxSimple;

DmxSimpleClass::DmxSimpleClass()
	: _buffer()
{
	for (int i = 0; i < DMX_SIMPLE_STUB_MAX_DMX_CHANNELS; i++)
	{
		_buffer[i] = 0;
	}
}


DmxSimpleClass::~DmxSimpleClass()
{
}


void DmxSimpleClass::usePin(uint8_t pin) 
{
	(void)pin; 
}


uint8_t DmxSimpleClass::read(int address)
{
	return _buffer[address];
}


void DmxSimpleClass::write(int address, uint8_t value)
{
	_buffer[address] = value;
}


void DmxSimpleClass::maxChannel(int maxChannels)
{
	(void)maxChannels;
}


#endif // _WINDOWS
