
// DmxLightShow.ino
//
//           PRO MINI
//            N A N O       U N O       M E G A        
//           Flash SRAM   Flash SRAM   Flash SRAM      
// Maximum:  30720 2048   32256 2048  253952 8192
// Current:  13510 1282   12855 1303    5736 1153
//       %:    44   62     39   63
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
// Total                                            11                16      + 2 per level (7) = 11+16+14=41

// Interrupt

#include "SerialPrint.h"
#include <DmxSimple.h>
#include "McuLightSetup.h"
#include "LightSetup.h"
#include "CommandBuffer.h"
#include "ProgramExecuter.h"


const uint8_t  DMX_SEND_PIN     =   2;
const uint16_t DMX_MAX_CHANNELS = 140;


CommandBuffer   _commandBuffer;
ProgramExecuter _programExecuter;
McuLightSetup   _mcuLightSetup;


void PrintFixtures();


void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  PRINTLN("DmxLightShow 0.1");
  
  DmxSimple.usePin(DMX_SEND_PIN);
  DmxSimple.maxChannel(DMX_MAX_CHANNELS);
  DmxSimple.write(1, 10);

  LightSetup.CreateFixtures();
  LightSetup.SetPlatformLightSetup(&_mcuLightSetup);
  LightSetup.GetPlatform()->SetProperties();
  PrintFixtures();

  _commandBuffer.AddChar('c');
  _commandBuffer.Process();

  _programExecuter.Run();
}


void loop() 
{
}


void PrintFixtures()
{
  PlatformLightSetup& setup = *LightSetup.GetPlatform();
  setup.PrintHeader();

  for (int parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
  {
	Par& par = LightSetup.GetPar(parNumber);
    setup.PrintFixture(parNumber);
  }

  setup.PrintFooter();
}

