#pragma once
#include <bitset>
#include "KeyCode.h"
#include "Vector.h"

typedef struct				HWND__* HWND;
typedef unsigned int		UINT;
typedef struct				tagPOINT POINT;
typedef unsigned long long	WPARAM;
typedef long long			LPARAM;

namespace CU 
{
	struct KeyboardMouse_Data
	{
#define SIZE 256
	public:
		KeyboardMouse_Data(const std::bitset<SIZE>& someData) : myData(someData) { }

		size_t Count() const { return myData.count(); }
		Input::KeyCode GetKeyCodeByIndex(size_t aIndex)
		{  
			if (myData.count() == 0 || myData.count() <= aIndex) return Input::KeyCode::None;

			size_t count = 0;
			for (size_t i = 0; i < SIZE; i++)
			{
				if (myData.test(i) == false) continue;

				if (aIndex == count) return static_cast<Input::KeyCode>(i);

				count++;
			}

			return Input::KeyCode::None;
		}

		bool Test(Input::KeyCode aKeyCode) { return myData.test( static_cast<size_t>(aKeyCode) ); }

	private:
		std::bitset<SIZE> myData;
#undef SIZE
	};

	class InputManager
	{
	public:
		InputManager();
		InputManager(const HWND& aHWND);
		void Update();
		bool UpdateEvents(UINT aMessage, WPARAM aWParam, LPARAM aLParam);
		bool IsKeyHeld(const Input::KeyCode aKeyCode) const;
		bool IsKeyPressed(const Input::KeyCode aKeyCode) const;
		bool IsKeyReleased(const Input::KeyCode aKeyCode) const;
		CU::Vector2f GetAbsoluteMousePosition() const;
		CU::Vector2f GetMousePosition() const;
		CU::Vector2f GetDeltaMousePosition() const;
		float GetDeltaMouseWheel() const;
		void SetCursorPostion(const long aX, const long aY);
		void ConfineCursorToWindow();
		void ReleaseCursorFromWindow();
		void LockCursor();
		void ReleaseCursor();
		bool GetIsCursorDisplaying() const;
		void DisplayCursor(bool aWillDisplay);
		void SetHWND(const HWND& aHWND);
		Input::KeyCode GetLatestKeyPress() const;

		KeyboardMouse_Data GetHeldData()	const	{ return KeyboardMouse_Data(  myPreviousState &  myCurrentState ); }
		KeyboardMouse_Data GetPressData()	const	{ return KeyboardMouse_Data( ~myPreviousState &  myCurrentState ); }
		KeyboardMouse_Data GetReleaseData()	const	{ return KeyboardMouse_Data(  myPreviousState & ~myCurrentState ); }

	private:

		template <typename T>
		struct ValueContainer
		{
		public:
			ValueContainer() {}
			ValueContainer(const T& aStartValue) : currentValue(aStartValue), previousValue(currentValue) { }

			void Set(const T& aValue)
			{
				currentValue = aValue;
			}

			void Add(const T& aValue)
			{
				currentValue += aValue;
			}

			void UpdatePreviousValue()
			{
				tentativeValue = previousValue;
				previousValue = currentValue;
			}

			T GetDelta() const
			{
				return previousValue - tentativeValue;
			}

			T GetCurrent() const
			{
				return currentValue;
			}

			ValueContainer<T>& operator=(const ValueContainer<T>& aOther)
			{
				if (this == &aOther)
				{
					return *this;
				}

				currentValue = aOther.currentValue;
				previousValue = aOther.previousValue;
				tentativeValue = aOther.tentativeValue;
			}

		private:
			T currentValue;
			T previousValue;
			T tentativeValue;


		};


		// Holds the "live" state that is being updated by
		// the message pump thread. This can be used in place
		// of myCurrentState but depending on how the game is
		// threaded it may be prudent to keep them separate.
		std::bitset<256> myTentativeState{};

		// The current snapshot when we last ran Update.
		std::bitset<256> myCurrentState{};

		// The previous snapshot.
		std::bitset<256> myPreviousState{};

		ValueContainer<CU::Vector2f> myMousePosition;
		ValueContainer<float> myMouseWheel;
		int myCurrentLatestKeyPress = -1;
		int myPreviousLatestKeyPress = -1;
		HWND myHWND = NULL;

		void SetCursorToCenter();

	};

}

