#pragma once
#include <string>
#include <vector>

#include "Action/InputAction.h"

namespace Input
{
	class InputProfile
	{
	public:
		friend class InputControlManager;

		~InputProfile();
		void SetEnable(const bool isEnabled) { myEnableState = isEnabled; }
		bool GetEnable() const { return myEnableState; }
		inline InputAction& GetAction(const std::string& aID) const;

		InputAction& operator[](const std::string& aID) const;
	protected:

	private:
		std::map<std::string, InputAction*> myActions;
		bool myEnableState = true;

			
		void Update(float someDeltaTime) const;

		InputAction& CreateAction_Void(const std::string aID);
		InputAction& CreateAction_Bool(const std::string aID);
		InputAction& CreateAction_Float(const std::string aID);
		InputAction& CreateAction_Vector2(const std::string aID);
	};
}

