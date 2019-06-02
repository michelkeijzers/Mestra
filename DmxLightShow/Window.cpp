// Window.cpp
// Only for Windows.

#ifdef _WINDOWS

// DmxLightShow.cpp : Defines the entry point for the application.
//

#include <cmath>
#include "math.h"
#include "framework.h"
#include "PlatformPar.h"
#include "DmxLightShow.h"
#include "LightSetup.h"
#include "Irgbw.h"
#include "TestProgramExecuter.h"
#include <string>
#include "CommandBuffer.h"
using namespace std;
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(DMX_SIMPLE_CLASS)
#include "MestraTypes.h"
#include "WinLightsetup.h"
#include "ChinesePar.h"
#include "LedBar.h"
#include "AsciiCommandParser.h"
#include "CommandParser.h"


#define MAX_LOADSTRING 100

//#define SMART_BACKGROUND_PAINTING
//#define SHOW_LEDS       
#define PAR_DISTANCE_X		 100
#define PAR_DISTANCE_Y		 180
#define PAR_DIAMETER			(PAR_DISTANCE_X - 3)
#define PAR_RADIUS				(PAR_DIAMETER / 2)
#define LED_DIAMETER			(PAR_DIAMETER / 4 - 12)
#define LED_RADIUS				(LED_DIAMETER / 2)
#define TEXT_OFFSET_X      -30
#define TEXT_OFFSET_Y			-100
#define FIXTURE_OFFSET_X	 -10
#define FIXTURE_OFFSET_Y	 -80
#define RGB_DISTANCE 0.4
#define WHITE_DISTANCE	     0.15

#define FONT_SIZE           11

#define PI_F 3.14159265358979f

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

CommandBuffer _commandBuffer;
ProgramExecuter _programExecuter;
AsciiCommandParser _asciiCommandParser;
CommandParser _commandParser;


int _refreshCounter;
bool _backgroundPainted = false;
bool _backgroundFixturePaint = false;

// Forward declarations of functions included in this code module:
void HandleMestraMessages(MSG& msg);
void InjectCommands();
void InitMestra();
void CalcCenter(int degrees, int centerX, int centerY, int distance, int* outputX, int* outputY);
void PrintFixtures();


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

	LightSetup.CreateFixtures();
	_refreshCounter = 0;

  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // Initialize global strings
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_DMXLIGHTSHOW, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // Perform application initialization:
  if (!InitInstance (hInstance, nCmdShow))
  {
      return FALSE;
  }

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DMXLIGHTSHOW));

  MSG msg;

	InitMestra();

  // Main message loop:
  while (GetMessage(&msg, nullptr, 0, 0))
  {
      if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
      {
          TranslateMessage(&msg);
          DispatchMessage(&msg);

					HandleMestraMessages(msg);
      }
  }

  return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DMXLIGHTSHOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DMXLIGHTSHOW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      50, 50, 1200, 700, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
          PAINTSTRUCT ps;
          HDC hdc = BeginPaint(hWnd, &ps);

					for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
					{
						Par& par = (Par&) LightSetup.GetPar(parNumber);
						Irgbw actualColor;
						par.GetActualColor(actualColor);

						if ((LightSetup.GetPlatform() != 0) && LightSetup.GetPlatform()->ArePropertiesSet())
						{
							_backgroundFixturePaint = true;

							SelectObject(hdc, GetStockObject(DC_BRUSH));
													 
							PlatformFixture& platformFixture = par.GetPlatformFixture(); 
							
							int centerX = FIXTURE_OFFSET_X + platformFixture.GetX() * PAR_DISTANCE_X;
							int centerY = FIXTURE_OFFSET_Y + platformFixture.GetY() * PAR_DISTANCE_Y;
								
							// If color not changed, continue with next par.
#ifdef COLOR_CHANGE_CHECKING
							//if (par.GetPlatformFixture().HasColorChanged())
							{
								//par.GetPlatformFixture().SetColorChanged(false);
#endif // COLOR_CHANGE_CHECKING
								// Total color
								dmx_value_t intensity = actualColor.GetIntensity();
								dmx_value_t red = actualColor.GetRed();
								dmx_value_t green = actualColor.GetGreen();
								dmx_value_t blue = actualColor.GetBlue();
								dmx_value_t white = actualColor.GetWhite();

  							dmx_value_t totalRed = min(intensity, max(white, red));
								dmx_value_t totalGreen = min(intensity, max(white, green));
								dmx_value_t totalBlue = min(intensity, max(white, blue));

								SetDCBrushColor(hdc, RGB(totalRed, totalGreen, totalBlue));

								if (parNumber >= NR_OF_CHINESE_PARS)
								{
									// Led Bar.

									SetDCBrushColor(hdc, RGB(totalRed, totalGreen, totalBlue));

									Rectangle(hdc, centerX - 20, centerY - 20, centerX + (2 * PAR_DISTANCE_X) - 25, centerY + 20);
								}
								else
								{
									// Black PAR.
									if (!_backgroundPainted)
									{
										SetDCBrushColor(hdc, RGB(0, 0, 0));

										Ellipse(hdc,
											centerX - PAR_RADIUS, centerY - PAR_RADIUS,
											centerX + PAR_RADIUS, centerY + PAR_RADIUS);
									}

									Ellipse(hdc,
										centerX - PAR_RADIUS, centerY - PAR_RADIUS,
										centerX + PAR_RADIUS, centerY + PAR_RADIUS);

#ifdef SHOW_LEDS
									// Red circles
									SetDCBrushColor(hdc, RGB(red, 0, 0));

									CalcCenter(40, centerX, centerY, (int)(PAR_DIAMETER * RGB_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);

									CalcCenter(40 + 120, centerX, centerY, (int)(PAR_DIAMETER * RGB_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);

									CalcCenter(40 + 240, centerX, centerY, (int)(PAR_DIAMETER * RGB_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);

									// Green circles
									SetDCBrushColor(hdc, RGB(0, green, 0));
									CalcCenter(0, centerX, centerY, (int)(PAR_DIAMETER * RGB_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);

									CalcCenter(0 + 120, centerX, centerY, (int)(PAR_DIAMETER * RGB_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);

									CalcCenter(0 + 240, centerX, centerY, (int)(PAR_DIAMETER * RGB_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);

									// Blue circles
									SetDCBrushColor(hdc, RGB(0, 0, blue));
									CalcCenter(80, centerX, centerY, (int)(PAR_DIAMETER * RGB_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);

									CalcCenter(80 + 120, centerX, centerY, (int)(PAR_DIAMETER * RGB_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);

									CalcCenter(80 + 240, centerX, centerY, (int)(PAR_DIAMETER * RGB_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);


									// White circles
									SetDCBrushColor(hdc, RGB(white, white, white));
									CalcCenter(0, centerX, centerY, (int)(PAR_DIAMETER * WHITE_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);

									CalcCenter(120, centerX, centerY, (int)(PAR_DIAMETER * WHITE_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);

									CalcCenter(240, centerX, centerY, (int)(PAR_DIAMETER * WHITE_DISTANCE), &x, &y);
									Ellipse(hdc,
										x - LED_RADIUS, y - LED_RADIUS,
										x + LED_RADIUS, y + LED_RADIUS);
#endif // SHOW_LEDS
								}

								wchar_t wtext[20];
								size_t sizet;

								// Line 1
								mbstowcs_s(&sizet, wtext, platformFixture.GetName1(),
									strlen(platformFixture.GetName1()) + 1); //Plus null
								LPWSTR ptr = wtext;

								TextOut(hdc,
									TEXT_OFFSET_X + platformFixture.GetX() * PAR_DISTANCE_X,
									TEXT_OFFSET_Y + platformFixture.GetY() * PAR_DISTANCE_Y + PAR_DIAMETER + FONT_SIZE - 2 - 8,
									wtext, lstrlen(wtext));

								// Line 2
								mbstowcs_s(&sizet,
									wtext, platformFixture.GetName2(),
									strlen(platformFixture.GetName2()) + 1); //Plus null
								ptr = wtext;

								TextOut(hdc,
									TEXT_OFFSET_X + platformFixture.GetX() * PAR_DISTANCE_X,
									TEXT_OFFSET_Y + platformFixture.GetY() * PAR_DISTANCE_Y + PAR_DIAMETER + (FONT_SIZE + 2) * 2 - 8,
									wtext, lstrlen(wtext));

								// Abbr
								mbstowcs_s(&sizet, wtext, platformFixture.GetAbbr(),
									strlen(platformFixture.GetAbbr()) + 1); //Plus null
								ptr = wtext;

								TextOut(hdc,
									TEXT_OFFSET_X + platformFixture.GetX() * PAR_DISTANCE_X,
									TEXT_OFFSET_Y + platformFixture.GetY() * PAR_DISTANCE_Y + PAR_DIAMETER + (FONT_SIZE + 2) * 3 - 4,
									wtext, lstrlen(wtext));
							}
#ifdef COLOR_CHANGE_CHECKING
						}
#endif // COLOR_CHANGE_CHECKING
					}

					if (_backgroundFixturePaint)
					{
						_backgroundPainted = true;
					}

					EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void CalcCenter(int degrees, int centerX, int centerY, int distance, int* outputX, int* outputY)
{
	*outputX = centerX + (int) (sin(degrees / 180.0f * PI_F) * distance);
	*outputY = centerY + (int) (cos(degrees / 180.0f * PI_F) * distance);
}

void InitMestra()
{
	LightSetup.CreateFixtures();
	PlatformLightSetup& setup = *(new WinLightSetup());
	LightSetup.SetPlatformLightSetup(&setup);
	setup.SetProperties();
	PrintFixtures();
}


void HandleMestraMessages(MSG& msg)
{
	Sleep(1);
	_refreshCounter++;
	InjectCommands();

	// Reset par increase states (debug only).
	for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
	{
		Par& par = LightSetup.GetPar(parNumber);
		par.GetPlatformFixture().ResetAtLeastOneStepIncreased();
	}

	// Run program executer.
	_programExecuter.Run();

	bool atLeasOneParIncreased = false;
	for (fixture_number_t par = 0; par < NR_OF_PARS; par++)
	{
		atLeasOneParIncreased |= LightSetup.GetPar(par).GetPlatformFixture().GetAtLeastOneStepIncreased();
	}

	if (atLeasOneParIncreased)
	{
		PrintFixtures();
	}

	InvalidateRect(msg.hwnd, NULL, FALSE);
}


void InjectString(const char* commandString)
{
	for (uint16_t i = 0; i < strlen(commandString); i++)
	{
		_commandBuffer.AddChar(commandString[i]);
	}

	_commandBuffer.AddChar('\n');
	_commandBuffer.AddChar('\r');

	_commandBuffer.Process(_asciiCommandParser);
	Command& command = _asciiCommandParser.GetCommand();
	_commandParser.Parse(command);
	
	// Print command.
	wchar_t wCommandText[20];
	size_t sizet;
	mbstowcs_s(&sizet, wCommandText, commandString, strlen(commandString) + 1); //Plus null

	wchar_t message[128];
	swprintf_s(message, L"\nCommand: %s\n", wCommandText);

	OutputDebugString(message);
	PrintFixtures();
}


void PrintFixtures()
{
	PlatformLightSetup& setup = *LightSetup.GetPlatform();
	setup.PrintHeader();

	for (fixture_number_t fixtureNumber = 0; fixtureNumber < NR_OF_PARS; fixtureNumber++)
	{
		(void) LightSetup.GetPar(fixtureNumber);
		setup.PrintFixture(fixtureNumber);
	}

	setup.PrintFooter();
}


void InjectCommands()
{
	if (_refreshCounter == 100)
	{

	  InjectString("AA t 4000");



		//InjectString("t fr 1000");

		//InjectString("d EA irbw");
		//InjectString("p EA 20");

		//InjectString("d AL ir");
		//InjectString("d AR ib");
		//InjectString("d AC ig");
		//InjectString("d AA irb");
		//InjectString("p AA 30");
		//InjectString("p AA 73");

		//InjectString("t BA 4000");
		//InjectString("p BA 72");

		InjectString("ra d irb a ib p 72");
		//InjectString("ra a ib");
		//InjectString("ra p 72");
		/*
		InjectString("t d 1000");
		InjectString("d d ib");
		InjectString("a d ibg");
		InjectString("p dl 50");
		InjectString("p dr 51");

		InjectString("t e 10000");
		InjectString("d e 0");
		InjectString("a e irgb");
		InjectString("p e 50");

		InjectString("t b 100");
		InjectString("d b ir");
		InjectString("a b i");
		InjectString("p b 50");
		*/
	}
}


#endif // _WINDOWS
