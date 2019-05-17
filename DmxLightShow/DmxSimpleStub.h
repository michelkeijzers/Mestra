// DmxSimpleStub.h
// Stub for Arduino DmxSimple DMX512 library.

#ifdef _WINDOWS

#pragma once


#include <stdint.h>


#define MAX_DMX_CHANNELS 512


class DmxSimpleClass
{
public:
	DmxSimpleClass();
	   
	~DmxSimpleClass();

	void maxChannel(int maxChannels) { (void) maxChannels; }

	void usePin(uint8_t pin) { (void) pin; };
	
	uint8_t read(int address);

	void write(int address, uint8_t value);

private:
	uint8_t _buffer[MAX_DMX_CHANNELS];
};


// Create instance.
extern DmxSimpleClass DmxSimple;


#endif // _WINDOWS