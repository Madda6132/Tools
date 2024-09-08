#pragma once
#include "Interaction.h"

//Test
#include "../../Game/InputWrapper.h"

namespace Input
{
	template<typename T>
	class Interaction_Tap : public Interaction
	{ };

	//Copy/past for the different devices 

	template<>
	class Interaction_Tap<KeyCode> : public Interaction
	{
	public:
		void SetDelay(const float aDelay) { myMaxDelay = aDelay; }

		// Inherited via Interaction
		InteractionState CheckInteraction(const float someDeltaTime, void* aValue) override
		{
			myTimer += someDeltaTime;

			//Start Tap check
			bool pressed = InputWrapper::GetManager().IsKeyPressed(*static_cast<KeyCode*>(aValue));
			if (pressed) 
			{
				myTimer = 0.0f;
				myTappedOnce = true;
				return InteractionState::Inactive;
			}

			//Check if Tap was started
			if (myTappedOnce == false) return InteractionState::Inactive;
				
			//If any other key was pressed it wasn't tapped
			KeyCode key = InputWrapper::GetManager().GetLatestKeyPress();
			myTappedOnce = key == Input::KeyCode::None;

			//Has enough time passed to trigger Tap
			if (myTimer < myMaxDelay) return InteractionState::Inactive;

			myTappedOnce = false;
			return InteractionState::Activated;
		}

		void Reset() override
		{
			myTimer = 0.0f;
		}

	private:
		float myTimer = 0.0f;
		float myMaxDelay = 0.2f;
		bool myTappedOnce = false;
	};


}