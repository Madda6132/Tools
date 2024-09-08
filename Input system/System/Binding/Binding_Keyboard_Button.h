#pragma once
#include "InputBind.h"
#include <CommonUtilities/include/KeyCode.h>

namespace Input
{
	class Binding_Keyboard_Button : public InputBind
	{
	public:
		friend class InputAction;
		friend class Binding_Mouse;

		Binding_Keyboard_Button() = default;
		~Binding_Keyboard_Button() = default;

		enum class Vector2Modification
		{
			X,
			Y,
			Both
		};

		void SetButtons(const std::initializer_list<Input::KeyCode>& aKeyCode);
		void SetModification(Vector2Modification aModification) { myVectorModification = aModification; }

		void SetInteraction_Hold(float someDelay = 0.0f);
		void SetInteraction_Press();
		void SetInteraction_Release();

	private:

		Input::KeyCode myKeys[MaxKeyMacro] = { Input::KeyCode::None };
		Vector2Modification myVectorModification = Vector2Modification::Y;



		// Inherited via InputBind
		bool CheckBinding(const float someDeltaTime, float& aOutValue) override;
		bool CheckBinding(const float someDeltaTime, float& aOutValue1, float& aOutValue2) override;
		InteractionState UpdateInteractions(const float someDeltaTime);
	};
}




