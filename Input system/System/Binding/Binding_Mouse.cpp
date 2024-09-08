#include "Binding_Mouse.h"

#include "../../Game/InputWrapper.h"
#include "Binding_Keyboard_Button.h"
#include "../Interaction/Interaction_Move.hpp"

void Input::Binding_Mouse::SetMouse()
{ 
	myInputType = InputType::Mouse; 
	auto move =  dynamic_cast<Interaction_Move<Input::KeyCode>*>(GetInteraction(MaxKeyMacro - 1));
	move->SetMovement();
}

void Input::Binding_Mouse::SetWheel()
{
	myInputType = InputType::Wheel;
	auto move = dynamic_cast<Interaction_Move<Input::KeyCode>*>(GetInteraction(MaxKeyMacro - 1));
	move->SetWheel();
}

void Input::Binding_Mouse::SetButtons(const std::initializer_list<Input::KeyCode>& aKeyCode)
{
	myKeyBindings->SetButtons(aKeyCode);
}

void Input::Binding_Mouse::SetInteraction_Hold(float someDelay)
{
	myKeyBindings->SetInteraction_Hold(someDelay);
}

void Input::Binding_Mouse::SetInteraction_Press()
{
	myKeyBindings->SetInteraction_Press();
}

void Input::Binding_Mouse::SetInteraction_Release()
{
	myKeyBindings->SetInteraction_Release();
}

Input::Binding_Mouse::Binding_Mouse()
{
	myKeyBindings = new Binding_Keyboard_Button();
	

	SetReturnRelease(false);
	auto* move = new Interaction_Move<Input::KeyCode>();
	SetInteraction(MaxKeyMacro - 1, move);
}

Input::Binding_Mouse::~Binding_Mouse()
{
	delete myKeyBindings;
}

bool Input::Binding_Mouse::CheckBinding(const float someDeltaTime, float& aOutValue)
{
	float value = aOutValue;

	if (myKeyBindings->CheckBinding(someDeltaTime, value) == false) return false;

	auto state = Interact(someDeltaTime, MaxKeyMacro - 1, nullptr);

	if (state == InteractionState::Inactive) return false;

	switch (myInputType)
	{
	case Input::Binding_Mouse::InputType::Mouse:
	{
		auto inputValue = myReturnType == ReturnValue::Position ?
			InputWrapper::GetManager().GetMousePosition() :
			InputWrapper::GetManager().GetDeltaMousePosition();

		aOutValue += static_cast<float>(inputValue.x + inputValue.y);
		break;
	}
	case Input::Binding_Mouse::InputType::Wheel:
	{
		float wheelDelta = InputWrapper::GetManager().GetDeltaMouseWheel();
		aOutValue += wheelDelta;
		break;
	}
	default:
		break;
	}
	

	return true;
}

bool Input::Binding_Mouse::CheckBinding(const float someDeltaTime, float& aOutValue1, float& aOutValue2)
{
	float value1 = aOutValue1;
	float value2 = aOutValue2;

	if (myKeyBindings->CheckBinding(someDeltaTime, value1, value2) == false) return false;

	auto state = Interact(someDeltaTime, MaxKeyMacro - 1, nullptr);

	if (state == InteractionState::Inactive) return false;

	switch (myInputType)
	{
	case Input::Binding_Mouse::InputType::Mouse:
	{
		auto inputValue = myReturnType == ReturnValue::Position ?
			InputWrapper::GetManager().GetMousePosition() :
			InputWrapper::GetManager().GetDeltaMousePosition();

		switch (myVectorModification)
		{
		case Input::Binding_Mouse::Vector2Modification::X:
			aOutValue1 += static_cast<float>(inputValue.x);
			break;
		case Input::Binding_Mouse::Vector2Modification::Y:
			aOutValue2 += static_cast<float>(inputValue.y);
			break;
		case Input::Binding_Mouse::Vector2Modification::Both:
			aOutValue1 += static_cast<float>(inputValue.x);
			aOutValue2 += static_cast<float>(inputValue.y);
			break;
		default:
			break;
		}
		break;
	}
	case Input::Binding_Mouse::InputType::Wheel:
	{
		float wheelDelta = InputWrapper::GetManager().GetDeltaMouseWheel();

		switch (myVectorModification)
		{
		case Input::Binding_Mouse::Vector2Modification::X:
			aOutValue1 += wheelDelta;
			break;
		case Input::Binding_Mouse::Vector2Modification::Y:
			aOutValue2 += wheelDelta;
			break;
		case Input::Binding_Mouse::Vector2Modification::Both:
			aOutValue1 += wheelDelta;
			aOutValue2 += wheelDelta;
			break;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	

	return true;
}
