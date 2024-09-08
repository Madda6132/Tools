#pragma once
#include "Interaction.h"

//Test
#include "../../Game/InputWrapper.h"

namespace Input
{
	template<typename T>
	class Interaction_Move : public Interaction
	{ };

	//Copy/past for the different devices 

	template<>
	class Interaction_Move<KeyCode> : public Interaction
	{
	private:
		enum class MoveType
		{
			Movement,
			Wheel
		};

	public:
		void SetMovement() { myMoveType = MoveType::Movement; }
		void SetWheel() { myMoveType = MoveType::Wheel; }

		// Inherited via Interaction
		InteractionState CheckInteraction([[maybe_unused]] const float someDeltaTime, [[maybe_unused]] void* aValue) override
		{
			bool moved = false;

			switch (myMoveType)
			{
			case Input::Interaction_Move<Input::KeyCode>::MoveType::Movement:
			{
				auto deltaPos = InputWrapper::GetManager().GetDeltaMousePosition();

				moved = 0.01f < (abs(deltaPos.x) + abs(deltaPos.y));
				break;
			}
			case Input::Interaction_Move<Input::KeyCode>::MoveType::Wheel:
			{
				float deltaWheel = InputWrapper::GetManager().GetDeltaMouseWheel();

				moved = 0.01f < (abs(deltaWheel));
				break;
			}
			default:
				break;
			}


			return moved ? InteractionState::Activated : InteractionState::Inactive;
		}

		void Reset() override
		{
			__noop;
		}

	private:
		MoveType myMoveType = MoveType::Movement;

		~Interaction_Move() { }
	};


}