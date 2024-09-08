#pragma once
#include "InputAction.h"

namespace Input
{
	class InputAction_Vector2f : public InputAction
	{
	public:

		~InputAction_Vector2f();

		// Inherited via InputAction
		void AddListenerVoid(const std::string& aID, const std::function<void()>& aVoidFunction)						override;
		void AddListenerBool(const std::string& aID, const std::function<void(bool)>& aFunction)						override;
		void AddListenerFloat(const std::string& aID, const std::function<void(float)>& aFloatFunction)					override;
		void AddListenerVector2(const std::string& aID, const std::function<void(float, float)>& aVector2Function)		override;
		void RemoveListener(const std::string& aID)																		override;

	private:
		std::map<std::string, std::function<void(float, float)>> myFunctions;

		// Inherited via InputAction
		void Update(float someDeltaTime) override;
		void AddProcess_AxisDeadZone(float aAmount) override;
		void AddProcess_Clamp(float aMin, float aMax) override;
		void AddProcess_Invert() override;
		void AddProcess_Normalize() override;
		void AddProcess_Scale(float aAmount) override;

	};
}


