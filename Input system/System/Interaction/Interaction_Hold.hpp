#pragma once
#include "Interaction.h"

//Test
#include "../../Game/InputWrapper.h"

namespace Input
{
	template<typename T>
	class Interaction_Hold : public Interaction
	{ };

	//Copy/past for the different devices 

	template<>
	class Interaction_Hold<KeyCode> : public Interaction
	{
	public:
		void SetDelay(const float aDelay) { myDelayTime = aDelay; }

		// Inherited via Interaction
		InteractionState CheckInteraction(const float someDeltaTime, void* aValue) override
		{
			bool isHeld = InputWrapper::GetManager().IsKeyHeld(*static_cast<Input::KeyCode*>(aValue));
			bool active = myDelayTime < myTimer;
			if (isHeld == false)
			{
				myTimer = 0.0f;
				return active ? InteractionState::Deactivated : InteractionState::Inactive;
			}

			myTimer += someDeltaTime;

			return active ? InteractionState::Activated : InteractionState::Inactive;
		}

		void Reset() override
		{
			myTimer = 0.0f;
		}

	private:
		float myDelayTime = 0.2f;
		float myTimer = 0.0f;

		~Interaction_Hold() { }
	};


}