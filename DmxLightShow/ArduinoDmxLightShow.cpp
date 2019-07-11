
// Interrupt
#include "ArduinoDmxLightShow.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(DMX_SIMPLE_CLASS)
#include HEADER_FILE(SERIAL_CLASS)


#include "SerialPrint.h"
#include "McuLightSetup.h"
#include "LightSetup.h"
#include "Command.h"
#include "CommandParser.h"
#include "ProgramExecuter.h"


const uint8_t  DMX_SEND_PIN = 2;
const uint16_t DMX_MAX_CHANNELS = 140;


Command         _command;
McuLightSetup   _mcuLightSetup;


ArduinoDmxLightShow::ArduinoDmxLightShow()
{
}


ArduinoDmxLightShow::~ArduinoDmxLightShow()
{
}


void ArduinoDmxLightShow::Setup()
{
	pinMode(LED_BUILTIN, OUTPUT);

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


void ArduinoDmxLightShow::Loop()
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
