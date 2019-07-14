#pragma once
class ArduinoDmxLightShow
{
public:
	ArduinoDmxLightShow();
	~ArduinoDmxLightShow();

	static void Setup();
	static void Loop();

	static void PrintFixtures();
};
