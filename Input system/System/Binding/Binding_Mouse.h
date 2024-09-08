#pragma once
#include "InputBind.h"
#include <CommonUtilities/include/KeyCode.h>

namespace Input
{
	class Binding_Keyboard_Button;

	class Binding_Mouse : public InputBind
	{
	public:
		friend class InputAction;

		Binding_Mouse();
		~Binding_Mouse();

		enum class Vector2Modification
		{
			X,
			Y,
			Both
		};

		void SetReturnDelta() { myReturnType = ReturnValue::Delta; }
		void SetReturnPosition() { myReturnType = ReturnValue::Position; }

		void SetMouse();
		void SetWheel();

		//When set to inverse what axis will be changed 
		void SetModification(Vector2Modification aModification) { myVectorModification = aModification; }
		void SetButtons(const std::initializer_list<Input::KeyCode>& aKeyCode);

		void SetInteraction_Hold(float someDelay = 0.0f);
		void SetInteraction_Press();
		void SetInteraction_Release();

		

	private:
		enum class ReturnValue
		{
			Delta,
			Position
		};

		enum class InputType
		{
			Mouse,
			Wheel
		};

		Binding_Keyboard_Button* myKeyBindings = nullptr;
		Vector2Modification myVectorModification = Vector2Modification::Both;
		ReturnValue myReturnType = ReturnValue::Position;
		InputType myInputType = InputType::Mouse;


		

		// Inherited via InputBind
		bool CheckBinding(const float someDeltaTime, float& aOutValue) override;
		bool CheckBinding(const float someDeltaTime, float& aOutValue1, float& aOutValue2) override;
	};
}


