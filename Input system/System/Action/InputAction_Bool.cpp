#include "InputAction_Bool.h"

#include "../Process/Process_AxisDeadZone.hpp"
#include "../Process/Process_Clamp.hpp"
#include "../Process/Process_Invert.hpp"
#include "../Process/Process_Normalize.hpp"
#include "../Process/Process_Scale.hpp"


Input::InputAction_Bool::~InputAction_Bool()
{ }

void Input::InputAction_Bool::Update(float someDeltaTime)
{
	float value = 0.0f;

	//Check if any binding was triggered
	if (CheckBindings(someDeltaTime, value) == false) return;

	Process(value);

	//If there is no value then do nothing
	if (abs(value) < 0.001f) return;

	auto functions = myFunctions.begin();
	while (functions != myFunctions.end())
	{
		functions->second(static_cast<bool>(0.0f < value));
		functions++;
	}
}

void Input::InputAction_Bool::AddProcess_AxisDeadZone(float aAmount)
{
	auto process = new Process_AxisDeadZone();
	process->SetDeadZone(aAmount);
	myProcesses.push_back(process);

}

void Input::InputAction_Bool::AddProcess_Clamp(float aMin, float aMax)
{
	auto process = new Process_Clamp();
	process->SetClamp(aMin, aMax);
	myProcesses.push_back(process);
}

void Input::InputAction_Bool::AddProcess_Invert()
{
	auto process = new Process_Invert();
	myProcesses.push_back(process);
}

void Input::InputAction_Bool::AddProcess_Normalize()
{
	auto process = new Process_Normalize();
	myProcesses.push_back(process);
}

void Input::InputAction_Bool::AddProcess_Scale(float aAmount)
{
	auto process = new Process_Scale();
	process->SetScale(aAmount);
	myProcesses.push_back(process);
}

void Input::InputAction_Bool::AddListenerVoid(const std::string& aID, const std::function<void()>& aVoidFunction)
{
	myFunctions[aID] = [aVoidFunction]([[maybe_unused]] bool aBool) { aVoidFunction(); };
}

void Input::InputAction_Bool::AddListenerBool(const std::string& aID, const std::function<void(bool)>& aBoolFunction)
{
	myFunctions[aID] = aBoolFunction;
}

void Input::InputAction_Bool::AddListenerFloat(const std::string& aID, const std::function<void(float)>& aFloatFunction)
{
	myFunctions[aID] = [aFloatFunction](bool aBool) { aFloatFunction( static_cast<float>(aBool) ); };
}

void Input::InputAction_Bool::AddListenerVector2(const std::string& aID, const std::function<void(float, float)>& aVector2Function)
{
	myFunctions[aID] = [aVector2Function](bool aBool) { aVector2Function( static_cast<float>(aBool), static_cast<float>(aBool) ); };
}


void Input::InputAction_Bool::RemoveListener(const std::string& aID)
{
	auto find = myFunctions.find(aID);
	if (find == myFunctions.end()) return;

	myFunctions.erase(find);
}