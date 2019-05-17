// Strobo.h
// Common light setup properties for strobo.
// Strobo is equal for all pars.

#pragma once


#include <stdint.h>


class Strobo
{
public:
	Strobo();
	
	~Strobo();
  
private:
  uint32_t _parBits;

  uint16_t _duration;

  uint8_t  _step;

  uint32_t _nextTime;
};
