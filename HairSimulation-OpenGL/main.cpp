//Change this to go to other OS
#define Win32

#ifdef Win32
#include <Windows.h>
#include "Display.h"
#include "Simulation.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif
#include "guicon.h"


#include <crtdbg.h>


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

//Windows starting point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	#ifdef _DEBUG
	RedirectIOToConsole();
	#endif

	//// test CrtDbg output
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	//_RPT0(_CRT_WARN, "This is testing _CRT_WARN output\n");
	//_RPT0(_CRT_ERROR, "This is testing _CRT_ERROR output\n");
	//_ASSERT(0 && "testing _ASSERT");
	//_ASSERTE(0 && "testing _ASSERTE");

	Display* display = new Display(hInstance, iCmdShow, 800, 600, "Hair and Fur");
	Display::setDisplay(display);
	Simulation* sim = new Simulation();

	while (!display->isClosed())
	{
		sim->Tick();
		display->StartDraw();
		sim->Draw();
		display->EndDraw();
	}

	delete display;
	delete sim;
	return 0;
}


#endif // Win32
