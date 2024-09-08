#include "InputBind.h"


Input::InputBind::InputBind()
{
	myInteraction = new Interaction*[MaxKeyMacro];

	for (size_t i = 0; i < MaxKeyMacro; i++)
	{
		myInteraction[i] = nullptr;
	}
}

Input::InputBind::~InputBind()
{
	if (myInteraction)
	{
		for (int i = MaxKeyMacro - 1; 0 < i; i--)
		{
			if (myInteraction[i] == nullptr) break;

			delete myInteraction[i];
			myInteraction[i] = nullptr;
		}

		delete[] myInteraction;
		myInteraction = nullptr;
	}
}

void Input::InputBind::Reset()
{
	for (int i = MaxKeyMacro - 1; 0 < i; i--)
	{
		myInteraction[i]->Reset();
	}
}

void Input::InputBind::Init()
{
	for (int i = MaxKeyMacro - 1; 0 < i; i--)
	{
		if (myInteraction[i] == nullptr) break;

		delete myInteraction[i];
		myInteraction[i] = nullptr;
	}
}

void Input::InputBind::SetInteraction(size_t aIndex, Interaction* aInteraction)
{
	auto& interPtr = myInteraction[aIndex];

	if (interPtr)
	{
		delete interPtr;
		interPtr = nullptr;
	}

	interPtr = aInteraction;
}

Input::InteractionState Input::InputBind::Interact(const float someDeltaTime, size_t aIndex, void* aValue) const
{
	return myInteraction[aIndex]->CheckInteraction(someDeltaTime, aValue);
}

void Input::InputBind::Inverse()
{
	myModifier = myModifier < 0 ? 1.0f : -1.0f;
}
