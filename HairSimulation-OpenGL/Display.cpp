#include "Display.h"
#include "Input.h"
#define Win32
#ifdef Win32

static Display* current;

//Standard Windows message pump thingy
//This should probs be inside of the Display class
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		case WM_CREATE:
			Beep(50, 10);
			return 0;
			break;

		case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(hwnd, &ps);
			// don't draw here.  would be waaay too slow.
			// draw in the draw() function instead.
			EndPaint(hwnd, &ps);
		}
		return 0;
		break;
		case WM_MOUSEMOVE:
			Input::HandleMouseEvent(message, wparam, lparam);
			break;
			return 0;
		case WM_KEYDOWN:
			switch (wparam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;
				default:
					Input::HandleKeyEvent(message, wparam, lparam);
					break;
			}
			return 0;
		case WM_KEYUP:
			switch (wparam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;
				default:
					Input::HandleKeyEvent(message, wparam, lparam);
					break;
			}
			return 0;
		case WM_LBUTTONDOWN:
			Input::HandleMouseEvent(message, wparam, lparam);
			break;
			return 0;
		case WM_RBUTTONDOWN:
			Input::HandleMouseEvent(message, wparam, lparam);
			break;
			return 0;
		case WM_LBUTTONUP:
			Input::HandleMouseEvent(message, wparam, lparam);
			break;
			return 0;
		case WM_RBUTTONUP:
			Input::HandleMouseEvent(message, wparam, lparam);
			break;
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}

//---Construction/Destruction------
Display::Display(HINSTANCE _hInstance, int iCmdShow, int _width, int _height, std::string title)
{
	hInstance = _hInstance;

	//create a window class
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT(title.c_str());
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	// Register that class with the Windows O/S..
	RegisterClass(&wc);

	RECT rect;
	SetRect(&rect, 50, 50, _width + 50, _height + 50); 
	
	// Save width and height off.
	width = _width;
	height = _height;

	// Adjust it.
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//call CreateWindow
	hwnd = CreateWindow(TEXT(title.c_str()),
						  TEXT(title.c_str()),
						  WS_OVERLAPPEDWINDOW,
						  rect.left, rect.top,  // adjusted x, y positions
						  rect.right - rect.left, rect.bottom - rect.top,  // adjusted width and height
						  NULL, NULL,
						  hInstance, NULL);

	// check to see that the window
	// was created successfully!
	if (hwnd == NULL)
	{
		FatalAppExit(NULL, TEXT("CreateWindow() failed!"));
	}

	// and show.
	ShowWindow(hwnd, iCmdShow);
	
	//Get device context
	hdc = GetDC(hwnd);

	//Create pixel format
	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;

	int chosenPixelFormat = ChoosePixelFormat(hdc, &pfd);
	if (chosenPixelFormat == 0)
	{
		FatalAppExit(NULL, TEXT("ChoosePixelFormat() failed!"));
	}
	int result = SetPixelFormat(hdc, chosenPixelFormat, &pfd);

	if (result == NULL)
	{
		FatalAppExit(NULL, TEXT("SetPixelFormat() failed!"));
	}

	//create rendering context
	hglrc = wglCreateContext(hdc);

	//Make current, don't know why but i know i have to do it
	wglMakeCurrent(hdc, hglrc);

	//Because i'm using glew i need to call glewInit after creating the rendering context
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
	}
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	//glFrontFace(GL_CCW);
	
}


Display::~Display()
{
	// UNmake your rendering context (make it 'uncurrent')
	wglMakeCurrent(NULL, NULL);

	// Delete the rendering context, we no longer need it.
	wglDeleteContext(hglrc);

	// release your window's DC
	ReleaseDC(hwnd, hdc);
	#pragma endregion

	// and a cheesy fade exit
	AnimateWindow(hwnd, 200, AW_HIDE | AW_BLEND);

}

//-----Utils--------
bool Display::isClosed()
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return true;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return false;
}

//-----Drawing-------
void Display::StartDraw()
{
	// 1. set up the viewport
	glViewport(0, 0, width, height); // set viewport
										 // to be the whole width and height
										 // of the CLIENT AREA (drawable region) of the window,
										 // (the CLIENT AREA excludes the titlebar and the 
										 // maximize/minimize buttons).

										 // 2. projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)width / (float)height, 1, 1000);

	// 3. viewing transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 10,
			  0, 0, 0,
			  0, 1, 0);

	// 4. modelling transformation and drawing
	glClearColor(0.0, 0.00, 0.00, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::EndDraw()
{
	SwapBuffers(hdc);
}


//---------STATIC------------
Display* Display::getDisplay()
{
	return current;
}

void Display::setDisplay(Display* disp)
{
	current = disp;
}


#endif // Win32

#ifdef OSX

GUGL::GUGL()
{


}


GUGL::~GUGL()
{}

#endif // OSX