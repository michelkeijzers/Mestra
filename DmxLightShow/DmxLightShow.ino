
// DmxLightShow.ino
//
//           
//             M E G A        
//            Flash SRAM   SRAMnew
// Maximum:  253952 8192
// Current:   12806 1044       663
//       %:       5   12         8
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
#include <DmxSimple.h>
#include "SerialPrint.h"
#include "McuLightSetup.h"
#include "LightSetup.h"
#include "Command.h"
#include "CommandParser.h"
#include "ProgramExecuter.h"

const uint8_t  DMX_SEND_PIN     =   2;
const uint16_t DMX_MAX_CHANNELS = 140;

Command         _command;
McuLightSetup   _mcuLightSetup;


//void onReceive(int packetSize);
void PrintFixtures();

void setup() 
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


void loop() 
{

}


void PrintFixtures()
{
  PlatformLightSetup& setup = *LightSetup.GetPlatform();
  setup.PrintHeader();

  for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
  {
	(void) LightSetup.GetPar(parNumber);
    setup.PrintFixture(parNumber);
  }

  setup.PrintFooter();
}
