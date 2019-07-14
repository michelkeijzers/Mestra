#pragma once

#include "MestraTypes.h"


class RF24
{
public:
	RF24(uint8_t ce_pin, uint8_t csn_pin);
	~RF24();
};

