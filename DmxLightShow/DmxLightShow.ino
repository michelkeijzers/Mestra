
#include "ArduinoDmxLightShow.h"

ArduinoDmxLightShow _lightShow;

void setup() 
{
	_lightShow.Setup();
}


void loop() 
{
	_lightShow.Loop();
}

