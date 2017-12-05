#pragma once
#define Win32
#ifdef Win32
//This is my way of hiding the platform specific initialization
#include <Windows.h>
#include <GL\glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class Display
{
private:
	HINSTANCE hInstance;    // window app instance
	HWND hwnd;      // handle for the window
	HDC   hdc;      // handle to device context
	HGLRC hglrc;    // handle to OpenGL rendering context
	int width, height;      // the desired width and
							// height of the CLIENT AREA
							// (DRAWABLE REGION in Window)
	
public:
	//create the OpenGL stuff
	Display(HINSTANCE _hInstance, int iCmdShow, int width, int height, std::string title);
	~Display();

	bool isClosed();

	void StartDraw();
	void EndDraw();

	//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	static Display* getDisplay();
	static void setDisplay(Display*);

	void SetMousePosition(int x, int y);
};

#endif

