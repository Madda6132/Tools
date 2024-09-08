#include "Binding_Keyboard_Button.h"

#include "../Interaction/Interaction_Hold.hpp"
#include "../Interaction/Interaction_Press.hpp"
#include "../Interaction/Interaction_Release.hpp"
#include "../Interaction/Interaction_Tap.hpp"
#include "../Interaction/Interaction_MultiTap.hpp"

#include <assert.h>

void Input::Binding_Keyboard_Button::SetButtons(const std::initializer_list<Input::KeyCode>& aKeyCode)
{
	assert(0 < aKeyCode.size() && aKeyCode.size() <= MaxKeyMacro && "Too many keys. Max: " + MaxKeyMacro);

	//Reset button list
	for (size_t i = 0; i < MaxKeyMacro; i++)
	{
		myKeys[i] = KeyCode::None;
	}

	size_t index = MaxKeyMacro - aKeyCode.size();
	auto key = aKeyCode.begin();
	while (key != aKeyCode.end())
	{
		myKeys[index] = *key;
		index++;
		key++;
	}

	myInteractionSize = static_cast<int>(aKeyCode.size());
}

	//These are bad allocated but I will return later when adding these to a stack container
void Input::Binding_Keyboard_Button::SetInteraction_Hold(float someDelay)
{
	Init();

	for (int i = MaxKeyMacro - 1; 0 <= i; i--)
	{
		auto* hold = new Interaction_Hold<Input::KeyCode>;
		hold->SetDelay(someDelay);
		SetInteraction(i, hold);
	}
}

void Input::Binding_Keyboard_Button::SetInteraction_Press()
{
	Init();

	//only the last key will be press
	SetInteraction_Hold();

	SetReturnRelease(false);
	auto* press = new Interaction_Press<Input::KeyCode>;
	SetInteraction(MaxKeyMacro - 1, press);

}

void Input::Binding_Keyboard_Button::SetInteraction_Release()
{
	Init();

	//only the last key will be released
	SetInteraction_Hold();

	SetReturnRelease(false);
	auto* release = new Interaction_Release<Input::KeyCode>;
	SetInteraction(MaxKeyMacro - 1, release);
}


Input::InteractionState Input::Binding_Keyboard_Button::UpdateInteractions(const float someDeltaTime)
{
	InteractionState finalState = InteractionState::Activated;
	int last = MaxKeyMacro - myInteractionSize;
	for (int i = MaxKeyMacro - 1; last <= i; i--)
	{
		InteractionState state = Interact(someDeltaTime, i, &myKeys[i]);

		if (finalState == InteractionState::Inactive) continue;

		switch (state)
		{
		case Input::InteractionState::Inactive:
			finalState = InteractionState::Inactive;
			break;
		case Input::InteractionState::Deactivated:
			finalState = myReturnRelease ? InteractionState::Deactivated : InteractionState::Inactive;
			break;
		default:
			break;
		}
	}

	return finalState;
}

bool Input::Binding_Keyboard_Button::CheckBinding(const float someDeltaTime, float& aOutValue)
{
	InteractionState state = UpdateInteractions(someDeltaTime);

	if (state == InteractionState::Inactive) return false;


	aOutValue += state == InteractionState::Activated ? myModifier : -myModifier;
	return true;
}

bool Input::Binding_Keyboard_Button::CheckBinding(const float someDeltaTime, float& aOutValue1, float& aOutValue2)
{

	InteractionState state = UpdateInteractions(someDeltaTime);

	if (state == InteractionState::Inactive) return false;

	switch (myVectorModification)
	{
	case Input::Binding_Keyboard_Button::Vector2Modification::X:
		aOutValue1 += state == InteractionState::Activated ? myModifier : 0.0f;
		break;
	case Input::Binding_Keyboard_Button::Vector2Modification::Y:
		aOutValue2 += state == InteractionState::Activated ? myModifier : 0.0f;
		break;
	case Input::Binding_Keyboard_Button::Vector2Modification::Both:
		aOutValue1 += state == InteractionState::Activated ? myModifier :  0.0f;
		aOutValue2 += state == InteractionState::Activated ? myModifier :  0.0f;
		break;
	default:
		break;
	}

	return true;
}

