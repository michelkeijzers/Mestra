// ClassNames.h

#pragma once

// Used to include variable class names
#define stringify(x) #x
#define HEADER_FILE(a) stringify(a.h)

// Class names
#ifdef _WINDOWS

#define ARDUINO_CLASS			        	ArduinoStub
#define DMX_SIMPLE_CLASS	        	DmxSimpleStub
#define SPI_RAM_CLASS               SpiRAMStub

#else

#define ARDUINO_CLASS								Arduino
#define DMX_SIMPLE_CLASS						DmxSimple
#define SPI_RAM_CLASS               SpiRAM

#endif
