// DmxSimpleStub.h
// Stub for Arduino DmxSimple DMX512 library.

#ifdef _WINDOWS

#pragma once

#include <stdint.h>

#define DMX_SIMPLE_STUB_MAX_DMX_CHANNELS 512

class DmxSimpleClass
{
public:
	DmxSimpleClass();
	~DmxSimpleClass();

	void usePin(uint8_t pin);
	
	uint8_t read(int address);
	void write(int address, uint8_t value);

	void maxChannel(int maxChannels);

private:
	uint8_t _buffer[DMX_SIMPLE_STUB_MAX_DMX_CHANNELS];
};


// Create instance.
extern DmxSimpleClass DmxSimple;

#endif // _WINDOWS
