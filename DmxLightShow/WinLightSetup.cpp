// TestLightSetup.h
// Set of pars/LED bars.
// Only for Windows.

#ifdef _WINDOWS

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include "AssertUtils.h"
#include <stdio.h>
#include "LightSetup.h"
#include "WinLightSetup.h"
#include "Par.h" 
#include "Windows.h"
#include "WinFixture.h"
#include "WinPar.h"


WinLightSetup::WinLightSetup()
	:
	PlatformLightSetup(),
	_propertiesAreSet(false)
{
	ftime(&_programStartTime);
}


WinLightSetup::~WinLightSetup()
{
}


bool WinLightSetup::ArePropertiesSet()
{
	return _propertiesAreSet;
}


void WinLightSetup::SetProperties()
{
	for (int parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		GetPar((fixture_number_t) parNumber).SetPlatform(new WinFixture(), new WinPar());
	}

	GetPar((fixture_number_t)0).GetPlatformFixture().SetProperties("Front", "Right 4", "FR4", 10, 1);
	GetPar((fixture_number_t)1).GetPlatformFixture().SetProperties("Front", "Right 3", "FR3", 9, 1);
	GetPar((fixture_number_t)2).GetPlatformFixture().SetProperties("Front", "Right 2", "FR2", 8, 1);
	GetPar((fixture_number_t)3).GetPlatformFixture().SetProperties("Front", "Right 1", "FR1", 7, 1);

	GetPar((fixture_number_t)4).GetPlatformFixture().SetProperties("Front", "Left 1", "FL1", 2, 1);
	GetPar((fixture_number_t)5).GetPlatformFixture().SetProperties("Front", "Left 2", "FL2", 3, 1);
	GetPar((fixture_number_t)6).GetPlatformFixture().SetProperties("Front", "Left 3", "FL3", 4, 1);
	GetPar((fixture_number_t)7).GetPlatformFixture().SetProperties("Front", "Left 4", "FL4", 5, 1);

	GetPar((fixture_number_t)8).GetPlatformFixture().SetProperties("Drums", "Right", "DR", 9, 3);
	GetPar((fixture_number_t)9).GetPlatformFixture().SetProperties("Drums", "Left", "DL", 8, 3);

	//Par("Keyboards", 	"Right", 	"KR",   5, 3);
	//Par("Keyboards", 	"Left", 	"KL",   4, 3);

	GetPar((fixture_number_t)10).GetPlatformFixture().SetProperties("Banner", "Right", "BR", 11, 2);
	GetPar((fixture_number_t)11).GetPlatformFixture().SetProperties("Banner", "Left", "BL", 1, 2);

	GetPar((fixture_number_t)12).GetPlatformFixture().SetProperties("Ego Riser", "Right", "ER", 9, 2);
	GetPar((fixture_number_t)13).GetPlatformFixture().SetProperties("Ego Riser", "Left", "EL", 3, 2);

	// LED Bars.
	GetPar((fixture_number_t)14).GetPlatformFixture().SetProperties("LED Bar", "Right", "LR", 5, 3);
	GetPar((fixture_number_t)15).GetPlatformFixture().SetProperties("LED Bar", "Center", "LC", 3, 3);
	GetPar((fixture_number_t)16).GetPlatformFixture().SetProperties("LED Bar", "Left", "LL", 1, 3);

	_propertiesAreSet = true;
}


#define OUTPUT_LIGHT_SETUP 1

void WinLightSetup::PrintHeader()
{
#ifdef OUTPUT_LIGHT_SETUP

	WCHAR message[256];

	swprintf_s(message, L"Time: %u\n", millis() - ((uint32_t)(_programStartTime.time * 1000 + _programStartTime.millitm)));
	OutputDebugString(message);

	OutputDebugString(L"┌▬▬▬┬▬▬▬▬┬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬┬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬┐\n");
	OutputDebugString(L"│Fix│Abbr│DMX│   Current Color   │   Default Color   │  Alternate Color  │  Program   │Program Params   │       Steps        │\n");
	OutputDebugString(L"│   │    │   ├▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┼▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┼▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┬▬▬▬┼▬▬▬▬┬▬▬▬▬▬▬▬┼▬▬▬▬▬┬▬▬▬▬▬┬▬▬▬▬▬┼▬▬▬▬▬┬▬▬▬▬▬┬▬▬▬▬▬▬▬▬┼\n");
	OutputDebugString(L"│   │    │Off│Int│Red│Gre│Bl │Whi│Int│Red│Gre│Bl │Whi│Int│Red│Gre│Bl │Whi│Init│Program│Param│Param│Param│Curr │Nr of│ Step   │\n");
	OutputDebugString(L"│   │    │Cha│ens│   │ en│ ue│ te│ens│   │ en│ ue│ te│ens│   │ en│ ue│ te│    │Number │  1  │  2  │  3  │Step │Steps│Duration│\n");
	OutputDebugString(L"┼▬▬▬┼▬▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┬▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬┼▬▬▬▬┼▬▬▬▬▬▬▬┼▬▬▬▬▬┼▬▬▬▬▬┼▬▬▬▬▬┼▬▬▬▬▬┼▬▬▬▬▬┼▬▬▬▬▬▬▬▬┼\n");

#endif // OUTPUT_LIGHT_SETUP
}


void WinLightSetup::PrintFixture(fixture_number_t fixtureNumber)
{
#ifdef OUTPUT_LIGHT_SETUP

	WCHAR message[256];

	Par& par = GetPar(fixtureNumber);
	Irgbw actualColor;
	par.GetActualColor(actualColor);

	Irgbw defaultColor;
	par.GetDefaultColor(defaultColor);
	Irgbw alternateColor;
	par.GetAlternateColor(alternateColor);

	const char* abbr = par.GetPlatformFixture().GetAbbr();
				
	//                   Par Number                                                        Init Program               Current Step
	//                      |  Abbreviation                                                           \ Program              |    Number of Steps
	//                      |     |  DMX Channel                                                       \ Number              |    / 
	//                      |     |      |    --Actual Color--   --Default Color--   -Alternate Color-  \    |   Parameters  |   /  Step Duration
	//                      |     |      |   /                \ /                 \ /                 \  |   |  /         |  |   |   |
	swprintf_s(message, L"│%2u │%c%c%c │%3u│%3u:%3u:%3u:%3u:%3u│%3u:%3u:%3u:%3u:%3u│%3u:%3u:%3u:%3u:%3u│%4u│%7u│%5u:%5u:%5u│%5u│%5u│%6u  │\n",
		fixtureNumber,
		wchar_t(abbr[0] == '\0' ? ' ' : abbr[0]),
		wchar_t(abbr[1] == '\0' ? ' ' : abbr[1]),
		wchar_t(abbr[2] == '\0' ? ' ' : abbr[2]),
		par.GetDmxOffsetChannel(),
		actualColor.GetIntensity(), actualColor.GetRed(), actualColor.GetGreen(), actualColor.GetBlue(), actualColor.GetWhite(),
		defaultColor.GetIntensity(), defaultColor.GetRed(), defaultColor.GetGreen(), defaultColor.GetBlue(), defaultColor.GetWhite(),
		alternateColor.GetIntensity(), alternateColor.GetRed(), alternateColor.GetGreen(), alternateColor.GetBlue(), alternateColor.GetWhite(),
		par.GetInitialize(), par.GetProgram(), par.GetParameter1(), par.GetParameter2(), par.GetParameter3(),
		par.GetCurrentStep(), par.GetNrOfSteps(), par.GetStepDuration());
	OutputDebugString(message);

#endif // OUTPUT_LIGHT_SETUP
}


void WinLightSetup::PrintFooter()
{
#ifdef OUTPUT_LIGHT_SETUP

	OutputDebugString(L"└▬▬▬┴▬▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬┴▬▬▬▬┴▬▬▬▬▬▬▬┴▬▬▬▬▬┴▬▬▬▬▬┴▬▬▬▬▬┴▬▬▬▬▬┴▬▬▬▬▬┴▬▬▬▬▬▬▬▬┼\n");

#endif // OUTPUT_LIGHT_SETUP
}

#endif // _WINDOWS
