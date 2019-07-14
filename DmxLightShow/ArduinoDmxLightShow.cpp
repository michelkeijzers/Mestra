
// DmxLightShow.ino
//
//           
//             M E G A        
//            Flash SRAM   SRAMnew
// Maximum:  253952 8192
// Current:   19396 3268       663
//       %:       7   39         8
//
// Stack:
//
// Class          ::Method					   Parameters     Local Variables
// ProgramExecuter::Run							    0                  0
// ProgramExecuter::RunPars						    2                  2
// ProgramExecuter::FadeOutProgram				    2                  3
// ProgramExecuter::SetFadeColor				    3                  9
// ProgramExecuter::WriteIrgb				        2                  2
// ChinesePar     ::GetBlue2Dmx					    1                  0
// McuPar         ::GetBlue2GammaCorrectedDmx       1                  0
// Or alternative: DmxSimple.write()
// Total                                           11                 16      + 2 per level (7) = 11+16+14=41

// Interrupt
#include "ArduinoDmxLightShow.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(DMX_SIMPLE_CLASS)
#include HEADER_FILE(SERIAL_CLASS)

// MIDI
#include HEADER_FILE(MIDI_CLASS)

// SD
#include HEADER_FILE(SPI_CLASS)
#include HEADER_FILE(SD_CLASS)

// IR
//#include <boarddefs.h>
#include HEADER_FILE(IR_REMOTE_CLASS)
//#include <IRremoteInt.h>
//#include <ir_Lego_PF_BitStreamEncoder.h>

// LCD
#include HEADER_FILE(LIQUID_CRYSTAL_CLASS)

// RF
//#include <nRF24L01.h>
//#include <printf.h>
#include HEADER_FILE(RF24_CLASS)
//#include <RF24_config.h>

// Application
#include "SerialPrint.h"
#include "McuLightSetup.h"
#include "LightSetup.h"
#include "Command.h"
#include "CommandParser.h"
#include "ProgramExecuter.h"


// DMX
const uint8_t  DMX_SEND_PIN = 2;
const uint16_t DMX_MAX_CHANNELS = 140;

// MIDI
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiA);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, midiB);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midiC);

// SD
File dataFile;

// IR
IRrecv irrecv(0);
decode_results results;

// LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// RF
RF24 radio(7, 8); // CE, CSN
//const byte address[6] = "00001";

// Application

Command         _command;
McuLightSetup   _mcuLightSetup;



ArduinoDmxLightShow::ArduinoDmxLightShow()
{
}


ArduinoDmxLightShow::~ArduinoDmxLightShow()
{
}


/* static */ void ArduinoDmxLightShow::Setup()
{
	pinMode(LED_BUILTIN, OUTPUT);

	DmxSimple.usePin(3);
	DmxSimple.write(1, 10);

	/*
	if (!SD.begin(2)) {
	dataFile = SD.open("datalog.txt", FILE_WRITE);

	// if the file is available, write to it:
	if (dataFile) {
	dataFile.println(10);
	dataFile.close();

	midiA.begin();
	midiA.read();
	midiA.send(1, 2, 3, 4);
	midiB.begin();
	midiB.read();
	midiB.send(1, 2, 3, 4);
	midiC.begin();
	midiC.read();
	midiC.send(1, 2, 3, 4);


	irrecv.decode(&results);

	lcd.begin(16, 2);
	lcd.print('c');
	lcd.setCursor(0, 0);
	lcd.noAutoscroll();
	lcd.clear();
	

	radio.begin();
	radio.openWritingPipe(1);
	radio.setPALevel(RF24_PA_MIN);
	radio.stopListening();
	const char text[] = "Hello World";
	radio.write(&text, sizeof(text));
	radio.openReadingPipe(0, address);
	radio.startListening();

	*/

	Serial.begin(115200);
	Serial.println("DmxLightShow 0.1");

	DmxSimple.usePin(DMX_SEND_PIN);
	DmxSimple.maxChannel(DMX_MAX_CHANNELS);
	DmxSimple.write(1, 10);

	LightSetup.CreateFixtures();
	LightSetup.SetPlatformLightSetup(&_mcuLightSetup);
	LightSetup.GetPlatform()->SetProperties();
	PrintFixtures();

	CommandParser::Parse(_command);

	ProgramExecuter::Run();
}


/* static */ void ArduinoDmxLightShow::Loop()
{
	
}


/* static */ void ArduinoDmxLightShow::PrintFixtures()
{
	PlatformLightSetup& setup = *LightSetup.GetPlatform();
	setup.PrintHeader();

	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		(void)LightSetup.GetPar(parNumber);
		setup.PrintFixture(parNumber);
	}

	setup.PrintFooter();
}
