/*

#include "AssertUtils.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

*/

/* static */ /* void AssertUtils::Assert(bool expression, const char* fileName, int line)
{
	if (!expression)
	{
		//Serial.println(funcName);
		Serial.println(fileName);
		Serial.println(line, DEC);
		Serial.flush();
		
		// Abort program execution.
		abort();
	}
}

*/