#pragma once
#include "Interaction.h"


//Test
#include "../../Game/InputWrapper.h"

namespace Input
{
	template<typename T>
	class Interaction_Release : public Interaction
	{ };

	//Copy/past for the different devices 

	template<>
	class Interaction_Release<KeyCode> : public Interaction
	{
	public:
		// Inherited via Interaction
		InteractionState CheckInteraction([[maybe_unused]] const float someDeltaTime, void* aValue) override
		{
			bool isReleased = InputWrapper::GetManager().IsKeyReleased(*static_cast<KeyCode*>(aValue));
			return isReleased ? InteractionState::Activated : InteractionState::Inactive;
		}

		void Reset() override
		{
			__noop;
		}

	private:

	};


}