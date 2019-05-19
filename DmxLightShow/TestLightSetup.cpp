// TestLightSetup.h
// Set of pars/LED bars.
// Only for Windows.

#ifdef _WINDOWS

#include "ClassNames.h"
#include <stdio.h>
#include HEADER_FILE(ARDUINO_CLASS)
#include "TestLightSetup.h"
#include "Par.h" 
#include "Windows.h"


TestLightSetupClass LightSetup;


TestLightSetupClass::TestLightSetupClass()
	: LightSetupClass()
{
	ftime(&_programStartTime);
}


TestLightSetupClass::~TestLightSetupClass()
{
}


void TestLightSetupClass::AddFixtures()
{
	LightSetupClass::AddFixtures();

	_pars[ 0].SetProperties("Front", "Left 1", "FL1", 2, 1);
	_pars[ 1].SetProperties("Front", "Left 2", "FL2", 3, 1);
	_pars[ 2].SetProperties("Front", "Left 3", "FL3", 4, 1);
	_pars[ 3].SetProperties("Front", "Left 4", "FL4", 5, 1);

	_pars[ 4].SetProperties("Front", "Right 1", "FR1", 7, 1);
	_pars[ 5].SetProperties("Front", "Right 2", "FR2", 8, 1);
	_pars[ 6].SetProperties("Front", "Right 3", "FR3", 9, 1);
	_pars[ 7].SetProperties("Front", "Right 4", "FR4", 10, 1);

	_pars[ 8].SetProperties("Drums", "Left", "DL", 6, 3);
	_pars[ 9].SetProperties("Drums", "Right", "DR", 7, 3);

	//Par("Keyboards", 	"Left", 	"KL",   4, 3);
	//Par("Keyboards", 	"Right", 	"KR",   5, 3);

	_pars[10].SetProperties("Banner", "Left", "BL", 1, 2);
	_pars[11].SetProperties("Banner", "Right", "BR", 11, 2);

	_pars[12].SetProperties("Ego Riser", "Left", "EL", 3, 2);
	_pars[13].SetProperties("Ego Riser", "Right", "ER", 9, 2);

	//for (int n = 0; n < NR_OF_PARS; n++)
	//{
	//	_pars[n].SetColor();
	//}
}


void TestLightSetupClass::Print()
{
#define OUTPUT_LIGHT_SETUP 1
#ifdef OUTPUT_LIGHT_SETUP

  WCHAR message[128];

	swprintf_s(message, L"Time: %u\n", millis() - ((uint32_t)(_programStartTime.time * 1000 + _programStartTime.millitm)));
	OutputDebugString(message);

	OutputDebugString(L"┌▬▬▬┬▬▬▬▬┬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬┐\n");
	OutputDebugString(L"│Fix│Abbr│DMX│   Current Color   │   Default Color   │  Altarnate Color  │  Program   │Program Params   │       Steps        │\n");
	OutputDebugString(L"│   │    │   ├▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┼▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┼▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┼▬▬▬▬┬▬▬▬▬▬▬▬┼▬▬▬▬▬┬▬▬▬▬▬┬▬▬▬▬▬┼▬▬▬▬▬┬▬▬▬▬▬┬▬▬▬▬▬▬▬▬┼\n");
	OutputDebugString(L"│   │    │Off│Int│Red│Gre│Bl │Whi│Int│Red│Gre│Bl │Whi│Int│Red│Gre│Bl │Whi│Init│Program│Param│Param│Param│Curr │Nr of│ Step   │\n");
	OutputDebugString(L"│   │    │Cha│ens│   │ en│ ue│ te│ens│   │ en│ ue│ te│ens│   │ en│ ue│ te│    │Number │  1  │  2  │  3  │Step │Steps│Duration│\n");
	OutputDebugString(L"┼▬▬▬┼▬▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┬▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬▬┼▬▬▬▬▬▬▬┼▬▬▬▬▬┼▬▬▬▬▬┼▬▬▬▬▬┼▬▬▬▬▬┼▬▬▬▬▬┼▬▬▬▬▬▬▬▬┼\n");


	for (par_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		Par& par = GetPar(parNumber);
		Irgbw& defaultColor = par.GetDefaultColor();
		Irgbw& alternateColor = par.GetAlternateColor();
		uint16_t dmx = par.GetDmxOffsetChannel();
		const char* abbr = par.GetAbbr();
				
		swprintf_s(message, L"│%2u │%c%c%c │%3u│%3u:%3u:%3u:%3u:%3u│%3u:%3u:%3u:%3u:%3u│%3u:%3u:%3u:%3u:%3u│%4u│%7u│%5u:%5u:%5u│%5u│%5u│%6u  │\n",
			parNumber,
			wchar_t(abbr[0] == '\0' ? ' ' : abbr[0]),
			wchar_t(abbr[1] == '\0' ? ' ' : abbr[1]),
			wchar_t(abbr[2] == '\0' ? ' ' : abbr[2]),
			dmx,
			DmxSimple.read(dmx + DMX_OFFSET_CHANNEL_INTENSITY),
			DmxSimple.read(dmx + DMX_OFFSET_CHANNEL_RED),
			DmxSimple.read(dmx + DMX_OFFSET_CHANNEL_GREEN),
			DmxSimple.read(dmx + DMX_OFFSET_CHANNEL_BLUE),
			DmxSimple.read(dmx + DMX_OFFSET_CHANNEL_WHITE),
			defaultColor.GetIntensity(), defaultColor.GetRed(), defaultColor.GetGreen(), defaultColor.GetBlue(), defaultColor.GetWhite(),
			alternateColor.GetIntensity(), alternateColor.GetRed(), alternateColor.GetGreen(), alternateColor.GetBlue(), alternateColor.GetWhite(),
			par.GetInitialize(), par.GetProgram(), par.GetParameter1(), par.GetParameter2(), par.GetParameter3(),
			par.GetCurrentStep(), par.GetNrOfSteps(), par.GetStepDuration());
		OutputDebugString(message);
	}

	OutputDebugString(L"└▬▬▬┴▬▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬▬┴▬▬▬▬▬▬▬┴▬▬▬▬▬┴▬▬▬▬▬┴▬▬▬▬▬┴▬▬▬▬▬┴▬▬▬▬▬┴▬▬▬▬▬▬▬▬┼\n");


#endif
}

#endif // _WINDOWS
