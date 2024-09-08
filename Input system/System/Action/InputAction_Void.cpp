#include "InputAction_Void.h"

#include "../Process/Process_AxisDeadZone.hpp"
#include "../Process/Process_Clamp.hpp"
#include "../Process/Process_Invert.hpp"
#include "../Process/Process_Normalize.hpp"
#include "../Process/Process_Scale.hpp"


Input::InputAction_Void::~InputAction_Void()
{ }

void Input::InputAction_Void::Update(float someDeltaTime)
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
		functions->second();
		functions++;
	}
}

void Input::InputAction_Void::AddProcess_AxisDeadZone(float aAmount)
{
	auto process = new Process_AxisDeadZone();
	process->SetDeadZone(aAmount);
	myProcesses.push_back(process);

}

void Input::InputAction_Void::AddProcess_Clamp(float aMin, float aMax)
{
	auto process = new Process_Clamp();
	process->SetClamp(aMin, aMax);
	myProcesses.push_back(process);
}

void Input::InputAction_Void::AddProcess_Invert()
{
	auto process = new Process_Invert();
	myProcesses.push_back(process);
}

void Input::InputAction_Void::AddProcess_Normalize()
{
	auto process = new Process_Normalize();
	myProcesses.push_back(process);
}

void Input::InputAction_Void::AddProcess_Scale(float aAmount)
{
	auto process = new Process_Scale();
	process->SetScale(aAmount);
	myProcesses.push_back(process);
}


void Input::InputAction_Void::AddListenerVoid(const std::string& aID, const std::function<void()>& aVoidFunction)
{
	myFunctions[aID] = aVoidFunction;
}

void Input::InputAction_Void::AddListenerBool(const std::string& aID, const std::function<void(bool)>& aBoolFunction)
{
	myFunctions[aID] = [aBoolFunction]() { aBoolFunction(true); };
}

void Input::InputAction_Void::AddListenerFloat(const std::string& aID, const std::function<void(float)>& aFloatFunction)
{
	myFunctions[aID] = [aFloatFunction]() { aFloatFunction(1.0f); };
}

void Input::InputAction_Void::AddListenerVector2(const std::string& aID, const std::function<void(float, float)>& aVector2Function)
{
	myFunctions[aID] = [aVector2Function]() { aVector2Function(1.0f, 1.0f); };
}


void Input::InputAction_Void::RemoveListener(const std::string& aID)
{
	auto find = myFunctions.find(aID);
	if (find == myFunctions.end()) return;

	myFunctions.erase(find);
}
