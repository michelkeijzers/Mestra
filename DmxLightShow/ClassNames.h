// ClassNames.h

#pragma once

// Used to include variable class names
#define stringify(x) #x
#define HEADER_FILE(a) stringify(a.h)

// Class names
#ifdef _WINDOWS

#define ARDUINO_CLASS			        	ArduinoStub
#define DMX_SIMPLE_CLASS	        	DmxSimpleStub

#else

#define ARDUINO_CLASS								Arduino
#define DMX_SIMPLE_CLASS						DmxSimple

#endif
