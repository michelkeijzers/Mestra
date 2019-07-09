#pragma once

#include "stdlib.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


#define assert(expression) \
  if (!(expression)) \
  { \
	  Serial.println(F(__FILE__)); \
	  Serial.println(__LINE__, DEC); \
	  Serial.flush(); \
  	abort(); \
  }

/*

#define assert(expr) AssertUtils::Assert((expr), (__FILE__), (__LINE__));

class AssertUtils
{
public:
	static void Assert(bool expression, const char* fileName, int line);
};

*/