// ArduinoStub.cpp
// Stub for Arduino function on Windows.
// Only for Windows

#ifdef _WINDOWS

#include "ArduinoStub.h"
#include <sys/timeb.h>


uint32_t millis()
{
	timeb now;

	ftime(&now);
	return uint32_t(now.time * 1000 + now.millitm);
}

#endif // _WINDOWS
