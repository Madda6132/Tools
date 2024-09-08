#pragma once
#include "Interaction.h"

//Test
#include "../../Game/InputWrapper.h"

namespace Input
{
	template<typename T>
	class Interaction_Press : public Interaction
	{ };

	//Copy/past for the different devices 

	template<>
	class Interaction_Press<KeyCode> : public Interaction
	{
	public:
		// Inherited via Interaction
		InteractionState CheckInteraction([[maybe_unused]] const float someDeltaTime, void* aValue) override
		{
			KeyCode key = *static_cast<KeyCode*>(aValue);
			bool isPressed = InputWrapper::GetManager().IsKeyPressed(key);
			return isPressed ? InteractionState::Activated : InteractionState::Inactive;
		}


		void Reset() override
		{
			__noop;
		}

	private:

	};


}