// Window.cpp
// Only for Windows.

#ifdef _WINDOWS

// DmxLightShow.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "DmxLightShow.h"
#include "TestLightSetup.h"
#include "Irgbw.h"
#include "TestProgramExecuter.h"
#include "ClassNames.h"
#include <string>
#include "CommandBuffer.h"
using namespace std;
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(DMX_SIMPLE_CLASS)
#include "MestraTypes.h"


#define MAX_LOADSTRING 100

#define PAR_DIAMETER   30
#define PAR_DISTANCE_X 60
#define PAR_DISTANCE_Y 90
#define FONT_SIZE      11


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

CommandBuffer _commandBuffer;
ProgramExecuter _programExecuter;
Fixture _fixtures[NR_OF_PARS];

int _refreshCounter;


// Forward declarations of functions included in this code module:
void InjectCommands();

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

	LightSetup.AddFixtures();
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

  // Main message loop:
  while (GetMessage(&msg, nullptr, 0, 0))
  {
      if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
      {
          TranslateMessage(&msg);
          DispatchMessage(&msg);

					//Sleep(1);
					_refreshCounter++;

					InjectCommands();

					// Reset par increase states (debug only).
					for (fixture_number_t par = 0; par < NR_OF_PARS; par++)
					{
						LightSetup.GetPar(par).GetPlatformFixture().ResetAtLeastOneStepIncreased();
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
						LightSetup.Print();
					}

					InvalidateRect(msg.hwnd, NULL, FALSE);
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


void InjectString(const char* command)
{
	for (int i = 0; i < strlen(command); i++)
	{
		_commandBuffer.AddChar(command[i]);
	}

	_commandBuffer.AddChar('\n');
	_commandBuffer.AddChar('\r');

	_commandBuffer.Process();

	// Print command.
	wchar_t wCommandText[20];
	size_t sizet;
	mbstowcs_s(&sizet, wCommandText, command, strlen(command) + 1); //Plus null
	
	wchar_t message[128];
	swprintf_s(message, L"\nCommand: %s\n", wCommandText);
	
	OutputDebugString(message);
	LightSetup.Print();
}


void InjectCommands()
{
	if (_refreshCounter == 100)
	{
		//InjectString("s a 50");

		
		InjectString("t fa 10000");

		InjectString("d fa irb");
		InjectString("a fa ib");
		InjectString("p fa 63");
		
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
      50, 50, 700, 350, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
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

					int xOffset = -40;
					int yOffset = -70;

					for (fixture_number_t parNumber = 0; parNumber < NR_OF_PARS; parNumber++)
					{
						Par& par = (Par&) LightSetup.GetPar(parNumber);
						dmx_channel_t dmxStartChannel = par.GetDmxOffsetChannel();
						dmx_value_t intensity = DmxSimple.read(dmxStartChannel + DMX_OFFSET_CHANNEL_INTENSITY);

						SelectObject(hdc, GetStockObject(DC_BRUSH));
						
						dmx_value_t white = DmxSimple.read(dmxStartChannel + DMX_OFFSET_CHANNEL_WHITE);

						dmx_value_t red   = max(white, DmxSimple.read(dmxStartChannel + DMX_OFFSET_CHANNEL_RED  ));
						dmx_value_t green = max(white, DmxSimple.read(dmxStartChannel + DMX_OFFSET_CHANNEL_GREEN));
						dmx_value_t blue  = max(white, DmxSimple.read(dmxStartChannel + DMX_OFFSET_CHANNEL_BLUE ));

						SetDCBrushColor(hdc, RGB(
							red   * intensity / 255,
							green * intensity / 255,
							blue  * intensity / 255));

						PlatformFixture& platformFixture = par.GetPlatformFixture();
						Ellipse(hdc, 
							platformFixture.GetX() * PAR_DISTANCE_X + xOffset , 
							platformFixture.GetY() * PAR_DISTANCE_Y + yOffset,
							platformFixture.GetX() * PAR_DISTANCE_X + PAR_DIAMETER + xOffset,
							platformFixture.GetY() * PAR_DISTANCE_Y + PAR_DIAMETER + yOffset) ;
				
						wchar_t wtext[20];
						size_t sizet;

						// Line 1
						mbstowcs_s(&sizet, wtext, platformFixture.GetName1(),
							strlen(platformFixture.GetName1()) + 1); //Plus null
						LPWSTR ptr = wtext;

						TextOut(hdc, 
							platformFixture.GetX() * PAR_DISTANCE_X + xOffset,
							platformFixture.GetY() * PAR_DISTANCE_Y + PAR_DIAMETER + FONT_SIZE - 2 - 8 + yOffset,
							wtext, lstrlen(wtext));

						// Line 2
						mbstowcs_s(&sizet, 
							wtext, platformFixture.GetName2(),
							strlen(platformFixture.GetName2()) + 1); //Plus null
						ptr = wtext;

						TextOut(hdc, 
							platformFixture.GetX() * PAR_DISTANCE_X + xOffset,
							platformFixture.GetY() * PAR_DISTANCE_Y + PAR_DIAMETER + (FONT_SIZE + 2) * 2 - 8 + yOffset,
							wtext, lstrlen(wtext));

						// Abbr
						mbstowcs_s(&sizet, wtext, platformFixture.GetAbbr(), 
							strlen(platformFixture.GetAbbr()) + 1); //Plus null
						ptr = wtext;

						TextOut(hdc, 
							platformFixture.GetX() * PAR_DISTANCE_X + xOffset,
							platformFixture.GetY() * PAR_DISTANCE_Y + PAR_DIAMETER + (FONT_SIZE + 2) * 3 - 4 + yOffset,
							wtext, lstrlen(wtext));
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
#endif // _WINDOWS
