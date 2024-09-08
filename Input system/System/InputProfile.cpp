#include "InputProfile.h"

#include "Action/InputAction_Void.h"
#include "Action/InputAction_Bool.h"
#include "Action/InputAction_Float.h"
#include "Action/InputAction_Vector2f.h"

Input::InputAction& Input::InputProfile::GetAction(const std::string& aID) const
{
	auto find = myActions.find(aID);

	if (find == myActions.end()) 
	{
		throw;
	}

	return *find->second;
}

Input::InputAction& Input::InputProfile::operator[](const std::string& aID) const
{
	return GetAction(aID);
}


Input::InputProfile::~InputProfile()
{
	auto actions = myActions.begin();
	while (actions != myActions.end())
	{
		delete actions->second;
		actions = myActions.erase(actions);
	}
}

void Input::InputProfile::Update(float someDeltaTime) const
{
	if (myEnableState == false) return;

	auto actions = myActions.begin();
	while (actions != myActions.end())
	{
		actions->second->BaseUpdate(someDeltaTime);
		actions++;
	}
}

Input::InputAction& Input::InputProfile::CreateAction_Void(const std::string aID)
{
	auto action = new InputAction_Void();
	myActions[aID] = action;
	return *action;
}

Input::InputAction& Input::InputProfile::CreateAction_Bool(const std::string aID)
{
	auto action = new InputAction_Bool();
	myActions[aID] = action;
	return *action;
}

Input::InputAction& Input::InputProfile::CreateAction_Float(const std::string aID)
{
	auto action = new InputAction_Float();
	myActions[aID] = action;
	return *action;
}

Input::InputAction& Input::InputProfile::CreateAction_Vector2(const std::string aID)
{
	auto action = new InputAction_Vector2f();
	myActions[aID] = action;
	return *action;
}

