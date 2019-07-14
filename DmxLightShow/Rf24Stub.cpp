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


#endif // _WINDOWS