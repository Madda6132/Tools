#pragma once
#include "pch.h"
#include "InputManager.h"
#include <Windows.h>
#include <WinUser.h>

CU::InputManager::InputManager() : myMouseWheel(0.0f)
{
}

CU::InputManager::InputManager(const HWND& aHWND) : myMouseWheel(0.0f), myHWND(aHWND)
{
}

void CU::InputManager::Update()
{
	myMousePosition.UpdatePreviousValue();
	myMouseWheel.Set(0.0f);

	myPreviousState = myCurrentState;
	myCurrentState = myTentativeState;

	myPreviousLatestKeyPress = myCurrentLatestKeyPress;
	myCurrentLatestKeyPress = -1;
}

bool CU::InputManager::UpdateEvents(UINT aMessage, WPARAM aWParam, LPARAM aLParam)
{

#define PRESSED (HIWORD(aLParam) & KF_REPEAT) == 0
#define HELD	(HIWORD(aLParam) & KF_REPEAT) > 0
	aLParam;
	int keyCode = LOWORD(aWParam);
	bool isPressed = true;

	switch (aMessage)
	{
	case WM_MOUSEMOVE:
	{
#define GET_X_LPARAM(lp)	((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)	((int)(short)HIWORD(lp))
		const int xPos = GET_X_LPARAM(aLParam);
		const int yPos = GET_Y_LPARAM(aLParam);
		myMousePosition.Set({ static_cast<float>(xPos), static_cast<float>(yPos) });

		if (GetCapture())
		{
			SetCursorToCenter();
		}
		return true;
	}
	case WM_MOUSEWHEEL:
	{
		auto delta = GET_WHEEL_DELTA_WPARAM(aWParam) / WHEEL_DELTA;
		myMouseWheel.Add(static_cast<float>(delta));
		return true;
	}
	case WM_LBUTTONDOWN:
	{
		keyCode = static_cast<int>(Input::KeyCode::MouseLeftButton);
		isPressed = true;
		break;
	}
	case WM_LBUTTONUP:
	{
		keyCode = static_cast<int>(Input::KeyCode::MouseLeftButton);
		isPressed = false;
		break;
	}
	case WM_RBUTTONDOWN:
	{
		keyCode = static_cast<int>(Input::KeyCode::MouseRightButton);
		isPressed = true;
		break;
	}
	case WM_RBUTTONUP:
	{
		keyCode = static_cast<int>(Input::KeyCode::MouseRightButton);
		isPressed = false;
		break;
	}
	case WM_MBUTTONDOWN: 
	{
		keyCode = static_cast<int>(Input::KeyCode::MouseMiddleButton);
		isPressed = true;
		break;
	}
	case WM_MBUTTONUP:
	{
		keyCode = static_cast<int>(Input::KeyCode::MouseMiddleButton);
		isPressed = false;
		break;
	}
	case WM_XBUTTONDOWN:
	{
		keyCode = static_cast<int>(Input::KeyCode::MouseX1);
		isPressed = true;
		break;
	}
	case WM_XBUTTONUP:
	{
		keyCode = static_cast<int>(Input::KeyCode::MouseX1);
		isPressed = false;
		break;
	}
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		isPressed = false;
		break;
	}
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		isPressed = true;
		break;
	}
	case WM_COMMAND:
	{
		return false;
	}
	default:
	{
		return false;
	}
	}

	myCurrentLatestKeyPress = keyCode;
	myTentativeState[keyCode] = isPressed;
	return true;
}

bool CU::InputManager::IsKeyHeld(const Input::KeyCode aKeyCode) const
{
	const size_t key = static_cast<size_t>(aKeyCode);
	return myCurrentState[key] && myPreviousState[key];

}

bool CU::InputManager::IsKeyPressed(const Input::KeyCode aKeyCode) const
{
	const size_t key = static_cast<size_t>(aKeyCode);
	return myCurrentState[key] && !myPreviousState[key];
}

bool CU::InputManager::IsKeyReleased(const Input::KeyCode aKeyCode) const
{
	const size_t key = static_cast<size_t>(aKeyCode);
	return !myCurrentState[key] && myPreviousState[key];
}

CU::Vector2f CU::InputManager::GetAbsoluteMousePosition() const
{
	POINT point;
	GetCursorPos(&point);
	return CU::Vector2f(static_cast<float>(point.x), static_cast<float>(point.y));
}

CU::Vector2f CU::InputManager::GetMousePosition() const
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(myHWND, &point);

	return CU::Vector2f(static_cast<float>(point.x), static_cast<float>(point.y));
}

CU::Vector2f CU::InputManager::GetDeltaMousePosition() const
{
	return myMousePosition.GetDelta();
}

float CU::InputManager::GetDeltaMouseWheel() const
{
	return myMouseWheel.GetDelta();
}

void CU::InputManager::SetCursorPostion(const long aX, const long aY)
{
	SetCursorPos(aX, aY);
}

void CU::InputManager::ConfineCursorToWindow()
{
	if (myHWND == NULL)
	{
		return;
	}

	RECT rect;
	GetClientRect(myHWND, &rect);

	POINT ul;
	ul.x = rect.left;
	ul.y = rect.top;

	POINT lr;
	lr.x = rect.right;
	lr.y = rect.bottom;

	MapWindowPoints(myHWND, nullptr, &ul, 1);
	MapWindowPoints(myHWND, nullptr, &lr, 1);

	rect.left = ul.x;
	rect.top = ul.y;

	rect.right = lr.x;
	rect.bottom = lr.y;

	ClipCursor(&rect);
}

void CU::InputManager::ReleaseCursorFromWindow()
{
	ClipCursor(nullptr);
}

void CU::InputManager::LockCursor()
{
	SetCapture(myHWND);
}

void CU::InputManager::ReleaseCursor()
{
	ReleaseCapture();
}

bool CU::InputManager::GetIsCursorDisplaying() const
{
	CURSORINFO ci = { sizeof(CURSORINFO) };

	if (GetCursorInfo(&ci) == false)
	{ //Error
		return false;
	}

	return ci.flags == CURSOR_SHOWING;
}

void CU::InputManager::DisplayCursor(bool aWillDisplay)
{
	ShowCursor(aWillDisplay);
}

void CU::InputManager::SetHWND(const HWND& aHWND)
{
	myHWND = aHWND;
}

Input::KeyCode CU::InputManager::GetLatestKeyPress() const
{
	return static_cast<Input::KeyCode>(myPreviousLatestKeyPress);
}

void CU::InputManager::SetCursorToCenter()
{
	HWND window = GetCapture();
	RECT rect;
	GetClientRect(window, &rect);
	HWND windowParent = GetParent(window);
	POINT point = { rect.right / 2, rect.bottom / 2 };
	MapWindowPoints(window, windowParent, &point, 1);
	SetCursorPostion(point.x, point.y);
}