//Change this to go to other OS
#define Win32

#ifdef Win32
#include <Windows.h>
#include "Display.h"
#include "Simulation.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

//Windows starting point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
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
