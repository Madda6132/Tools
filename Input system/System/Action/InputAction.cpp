#include "InputAction.h"
#include "../Process/IProcess.h"

void Input::InputAction::SetEnable(const bool& aEnable)
{
	if (myIsActive == aEnable) return;

	myIsActive = aEnable;

	if (myIsActive)
	{
		auto binding = myBindings.begin();
		while (binding != myBindings.end())
		{
			binding->second->Reset();
			binding++;
		}
	}
}

Input::InputBind& Input::InputAction::GetBinding(const std::string& aID) const
{
	auto find = myBindings.find(aID);

	if (find == myBindings.end())
	{
		//No binding found
		throw;
	}

	return *find->second;
}

Input::InputBind& Input::InputAction::operator[](const std::string& aID) const
{
	return GetBinding(aID);
}

Input::InputAction::~InputAction()
{
	auto binding = myBindings.begin();
	while (binding != myBindings.end())
	{
		delete binding->second;
		binding = myBindings.erase(binding);
	}
	
	while (myProcesses.empty() == false)
	{
		delete myProcesses.back();
		myProcesses.pop_back();
	}
}

bool Input::InputAction::CheckBindings(float someDeltaTime, float& aValue) const
{
	bool activated = false;
	auto binding = myBindings.begin();
	while (binding != myBindings.end())
	{
		if (binding->second->CheckBinding(someDeltaTime, aValue)) activated = true;
		binding++;
	}

	return activated;
}

bool Input::InputAction::CheckBindings(float someDeltaTime, float& aValue1, float& aValue2) const
{
	bool activated = false;
	auto binding = myBindings.begin();
	while (binding != myBindings.end())
	{
		if (binding->second->CheckBinding(someDeltaTime, aValue1, aValue2)) activated = true;
		binding++;
	}

	return activated;
}

void Input::InputAction::Process(float& aValue) const
{
	if (myProcesses.empty()) return;

	size_t size = myProcesses.size();
	for (size_t i = 0; i < size; i++)
	{
		myProcesses[i]->Process(aValue);
	}
}

void Input::InputAction::Process(float& aValue1, float& aValue2) const
{
	if (myProcesses.empty()) return;

	size_t size = myProcesses.size();
	for (size_t i = 0; i < size; i++)
	{
		myProcesses[i]->Process(aValue1, aValue2);
	}
}

void Input::InputAction::BaseUpdate(float someDeltaTime)
{
	if (myIsActive == false) return;

	Update(someDeltaTime);
}
