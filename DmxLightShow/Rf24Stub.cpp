#ifdef _WINDOWS


#include "Rf24Stub.h"


RF24::RF24(uint8_t ce_pin, uint8_t csn_pin)
{
	(void) ce_pin;
	(void) csn_pin;
}


RF24::~RF24()
{

}




void RF24::begin()
{

}


void RF24::openWritingPipe(int pipe)
{

}


void RF24::setPALevel(int level)
{

}


void RF24::stopListening()
{

}


void RF24::write(const char* text, int textLength)
{

}


void RF24::openReadingPipe(int pipe, const uint8_t* address)
{

}


void RF24::startListening()
{

}

#endif // _WINDOWS