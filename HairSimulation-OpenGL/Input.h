#pragma once
#include <Windows.h>
#include "GMath.h"
using namespace GMath;

enum KeyCode
{
	//None = 0,
	Mouse0 = VK_LBUTTON,
	Mouse1 = VK_RBUTTON,
	Backspace = VK_BACK,
	Delete = VK_DELETE,
	Tab = VK_TAB,
	Clear = VK_CLEAR,
	Return = VK_RETURN,
	LeftShift = VK_SHIFT,
	Pause = VK_PAUSE,
	EscapeKey = VK_ESCAPE,
	Space = VK_SPACE,
	/*Keypad0 = VK_ESCAPE,
	Keypad1 = VK_ESCAPE,
	Keypad2 = VK_ESCAPE,
	Keypad3 = VK_ESCAPE,
	Keypad4 = VK_ESCAPE,
	Keypad5 = VK_ESCAPE,
	Keypad6 = VK_ESCAPE,
	Keypad7 = VK_ESCAPE,
	Keypad8 = VK_ESCAPE,
	Keypad9 = VK_ESCAPE,
	KeypadPeriod	Numeric keypad '.'.
	KeypadDivide	Numeric keypad '/'.
	KeypadMultiply	Numeric keypad '*'.
	KeypadMinus	Numeric keypad '-'.
	KeypadPlus	Numeric keypad '+'.
	KeypadEnter	Numeric keypad enter.
	KeypadEquals	Numeric keypad '='.
	UpArrow	Up arrow key.
	DownArrow	Down arrow key.
	RightArrow	Right arrow key.
	LeftArrow	Left arrow key.
	Insert	Insert key key.
	Home	Home key.
	End	End key.
	PageUp	Page up.
	PageDown	Page down.
	F1	F1 function key.
	F2	F2 function key.
	F3	F3 function key.
	F4	F4 function key.
	F5	F5 function key.
	F6	F6 function key.
	F7	F7 function key.
	F8	F8 function key.
	F9	F9 function key.
	F10	F10 function key.
	F11	F11 function key.
	F12	F12 function key.
	F13	F13 function key.
	F14	F14 function key.
	F15	F15 function key.
	Alpha0	The '0' key on the top of the alphanumeric keyboard.
	Alpha1	The '1' key on the top of the alphanumeric keyboard.
	Alpha2	The '2' key on the top of the alphanumeric keyboard.
	Alpha3	The '3' key on the top of the alphanumeric keyboard.
	Alpha4	The '4' key on the top of the alphanumeric keyboard.
	Alpha5	The '5' key on the top of the alphanumeric keyboard.
	Alpha6	The '6' key on the top of the alphanumeric keyboard.
	Alpha7	The '7' key on the top of the alphanumeric keyboard.
	Alpha8	The '8' key on the top of the alphanumeric keyboard.
	Alpha9	The '9' key on the top of the alphanumeric keyboard.
	Exclaim	Exclamation mark key '!'.
	DoubleQuote	Double quote key '"'.
	Hash	Hash key '#'.
	Dollar	Dollar sign key '$'.
	Ampersand	Ampersand key '&'.
	Quote	Quote key '.
	LeftParen	Left Parenthesis key '('.
	RightParen	Right Parenthesis key ')'.
	Asterisk	Asterisk key '*'.
	Plus	Plus key '+'.
	Comma	Comma ',' key.
	Minus	Minus '-' key.
	Period	Period '.' key.
	Slash	Slash '/' key.
	Colon	Colon ':' key.
	Semicolon	Semicolon ';' key.
	Less	Less than '<' key.
	Equals	Equals '=' key.
	Greater	Greater than '>' key.
	Question	Question mark '?' key.
	At	At key '@'.
	LeftBracket	Left square bracket key '['.
	Backslash	Backslash key '\'.
	RightBracket	Right square bracket key ']'.
	Caret	Caret key '^'.
	Underscore	Underscore '_' key.
	BackQuote	Back quote key '`'.*/
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,/*
	Numlock	Numlock key.
	CapsLock	Capslock key.
	ScrollLock	Scroll lock key.
	RightShift	Right shift key.*/
	/*RightControl	Right Control key.
	LeftControl	Left Control key.
	RightAlt	Right Alt key.
	LeftAlt	Left Alt key.
	LeftCommand	Left Command key.
	LeftApple	Left Command key.
	LeftWindows	Left Windows key.
	RightCommand	Right Command key.
	RightApple	Right Command key.
	RightWindows	Right Windows key.
	AltGr	Alt Gr key.
	Help	Help key.
	Print	Print key.
	SysReq	Sys Req key.
	Break	Break key.
	Menu	Menu key.*/


	END_KEYS
};

static bool KeyboardState[KeyCode::END_KEYS];
static bool PreviousKeyboardState[KeyCode::END_KEYS];

static Vector2 MousePosition;
static Vector2 PreviousMousePosition;

static bool mouseMoved = false;

class Input
{
public:
	Input();

	static void HandleKeyEvent(UINT msg, WPARAM wparam, LPARAM lparam);
	static void HandleMouseEvent(UINT msg, WPARAM wparam, LPARAM lparam);

	static bool GetKeyDown(KeyCode code);
	static bool GetKeyUp(KeyCode code);
	static bool GetKey(KeyCode code);

	static Vector2 GetMousePosition();
	static Vector2 GetPreviousMousePosition();

	static bool MouseMoved();

	static void SetMousePosition(int x, int y);
protected:
private:

};


