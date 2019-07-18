#pragma once

#include "MestraTypes.h"


struct decode_results
{

};


class IRrecv
{
public:
	IRrecv(uint8_t unknown);
	~IRrecv();

	void decode(decode_results* results);
};