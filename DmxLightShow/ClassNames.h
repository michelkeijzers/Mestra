// ClassNames.h

#pragma once

// Used to include variable class names
#define stringify(x) #x
#define HEADER_FILE(a) stringify(a.h)

// Class names
#ifdef _WINDOWS

#define ARDUINO_CLASS			ArduinoStub
#define DMX_SIMPLE_CLASS		DmxSimpleStub
#define SPI_RAM_CLASS			SpiRAMStub
#define SERIAL_CLASS			SerialStub
#define MIDI_CLASS				MidiStub
#define SPI_CLASS				SpiStub
#define SD_CLASS				SdStub
#define IR_REMOTE_CLASS			IrRemoteStub
#define LIQUID_CRYSTAL_CLASS	LiquidCrystalStub
#define RF24_CLASS              Rf24Stub

#else

#define ARDUINO_CLASS			Arduino
#define DMX_SIMPLE_CLASS		DmxSimple
#define SPI_RAM_CLASS			SpiRAM
#define SERIAL_CLASS			Arduino
#define MIDI_CLASS				MIDI
#define SPI_CLASS				SPI
#define SD_CLASS				SD
#define IR_REMOTE_CLASS			IRremote
#define LIQUID_CRYSTAL_CLASS	LiquidCrystal
#define RF24_CLASS              RF24

#endif
