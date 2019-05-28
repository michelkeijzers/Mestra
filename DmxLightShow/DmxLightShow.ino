// DmxLightShow.ino
//
//            U N O        M E G A
//          Flash SRAM   Flash SRAM
// Maximum: 32256 2048  253952 8192
// Current: 12256 1230   12542 1230
//       %:   37   60     4%    15%
//
// 

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
  LightSetup.GetPlatform()->Print();


  _commandBuffer.AddChar('c');
  _commandBuffer.Process();

  _programExecuter.Run();
}


void loop() 
{
}
