// ClassNames.h

#pragma once

// Used to include variable class names
#define stringify(x) #x
#define HEADER_FILE(a) stringify(a.h)

// Class names
#ifdef _WINDOWS

#define LIGHT_SETUP_CLASS           TestLightSetup
#define FIXTURE_CLASS			        	TestFixture
#define PAR_CLASS	        					TestPar
#define ARDUINO_CLASS			        	ArduinoStub
#define DMX_SIMPLE_CLASS	        	DmxSimpleStub

#else

#define LIGHT_SETUP_CLASS						LightSetup
#define FIXTURE_CLASS								Fixture
#define PAR_CLASS										Par
#define ARDUINO_CLASS								Arduino
#define DMX_SIMPLE_CLASS						DmxSimple

#endif
