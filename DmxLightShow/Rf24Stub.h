#pragma once

#include "MestraTypes.h"

#define RF24_PA_MIN 0

class RF24
{
public:
	RF24(uint8_t ce_pin, uint8_t csn_pin);
	~RF24();

	void begin();
	void openWritingPipe(int pipe);
	void setPALevel(int level);
	void stopListening();
	void write(const char* text, int textLength);
	void openReadingPipe(int pipe, const uint8_t* address);
	void startListening();
};

