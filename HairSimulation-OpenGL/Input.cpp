#include "Input.h"

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
{}

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
	return Vector2();
}
