#pragma once
#include "Interaction.h"

//Test
#include "../../Game/InputWrapper.h"

namespace Input
{
	template<typename T>
	class Interaction_MultiTap : public Interaction
	{ };

	//Copy/past for the different devices 

	template<>
	class Interaction_MultiTap<KeyCode> : public Interaction
	{
	public:
		void SetDelay(const float aDelay) { myMaxDelay = aDelay; }

		// Inherited via Interaction
		InteractionState CheckInteraction(const float someDeltaTime, void* aValue) override
		{
			myTimer += someDeltaTime;
			bool pressed = InputWrapper::GetManager().IsKeyPressed(*static_cast<KeyCode*>(aValue));
			bool multiTapped = false;
			if (pressed) 
			{
				multiTapped = myTimer < myMaxDelay;
				myTimer = 0.0f;
			}

			return multiTapped ? InteractionState::Activated : InteractionState::Inactive;
		}

		void Reset() override
		{
			myTimer = 0.0f;
		}

	private:
		float myTimer = 0.0f;
		float myMaxDelay = 0.2f;
	};


}