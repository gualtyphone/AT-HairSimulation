#include "Input.h"
#include <Windowsx.h>
Input::Input()
{}

void Input::HandleKeyEvent(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_KEYDOWN:
			KeyboardState[wparam] = true;
			break;
		case WM_KEYUP:
			KeyboardState[wparam] = false;
			break;
	}
}

void Input::HandleMouseEvent(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_LBUTTONDOWN:
			KeyboardState[Mouse0] = true;
			break;
		case WM_RBUTTONDOWN:
			KeyboardState[Mouse1] = true;
			break;
		case WM_LBUTTONUP:
			KeyboardState[Mouse0] = false;
			break;
		case WM_RBUTTONUP:
			KeyboardState[Mouse1] = false;
			break;
		case WM_MOUSEMOVE:
			mouseMoved = true;
			PreviousMousePosition = MousePosition;
			MousePosition.x = GET_X_LPARAM(lparam);
			MousePosition.y = GET_Y_LPARAM(lparam);
			break;
	}
	
}

bool Input::GetKeyDown(KeyCode code)
{
	if (KeyboardState[code] == true && PreviousKeyboardState[code] == false)
	{
		PreviousKeyboardState[code] = true;
		return true;
	}
	return false;
}

bool Input::GetKeyUp(KeyCode code)
{
	if (KeyboardState[code] == false && PreviousKeyboardState[code] == true)
	{
		PreviousKeyboardState[code] = false;
		return true;
	}
	return false;
}

bool Input::GetKey(KeyCode code)
{
	return KeyboardState[code] == true;
}

Vector2 Input::GetMousePosition()
{
	return MousePosition;
}

Vector2 Input::GetPreviousMousePosition()
{
	return PreviousMousePosition;
}

bool Input::MouseMoved()
{
	if (mouseMoved)
	{
		mouseMoved = false;
		return true;
	}
	return false;
}
