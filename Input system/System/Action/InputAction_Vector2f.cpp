#include "InputAction_Vector2f.h"

#include "../Process/Process_AxisDeadZone.hpp"
#include "../Process/Process_Clamp.hpp"
#include "../Process/Process_Invert.hpp"
#include "../Process/Process_Normalize.hpp"
#include "../Process/Process_Scale.hpp"


Input::InputAction_Vector2f::~InputAction_Vector2f()
{ }

void Input::InputAction_Vector2f::Update(float someDeltaTime)
{
	float xValue = 0.0f;
	float yValue = 0.0f;

	//Check if any binding was triggered
	if (CheckBindings(someDeltaTime, xValue, yValue) == false) return;

	Process(xValue, yValue);


	//If there is no value then do nothing
	if (abs(xValue) + abs(yValue) < 0.001f) return;

	auto functions = myFunctions.begin();
	while (functions != myFunctions.end())
	{
		functions->second(xValue, yValue);
		functions++;
	}

}

void Input::InputAction_Vector2f::AddProcess_AxisDeadZone(float aAmount)
{
	auto process = new Process_AxisDeadZone();
	process->SetDeadZone(aAmount);
	myProcesses.push_back(process);

}

void Input::InputAction_Vector2f::AddProcess_Clamp(float aMin, float aMax)
{
	auto process = new Process_Clamp();
	process->SetClamp(aMin, aMax);
	myProcesses.push_back(process);
}

void Input::InputAction_Vector2f::AddProcess_Invert()
{
	auto process = new Process_Invert();
	myProcesses.push_back(process);
}

void Input::InputAction_Vector2f::AddProcess_Normalize()
{
	auto process = new Process_Normalize();
	myProcesses.push_back(process);
}

void Input::InputAction_Vector2f::AddProcess_Scale(float aAmount)
{
	auto process = new Process_Scale();
	process->SetScale(aAmount);
	myProcesses.push_back(process);
}


void Input::InputAction_Vector2f::AddListenerVoid(const std::string& aID, const std::function<void()>& aVoidFunction)
{
	myFunctions[aID] = [aVoidFunction]([[maybe_unused]] float afloat1, [[maybe_unused]] float afloat2) { aVoidFunction(); };
}

void Input::InputAction_Vector2f::AddListenerBool(const std::string& aID, const std::function<void(bool)>& aBoolFunction)
{
	myFunctions[aID] = [aBoolFunction]([[maybe_unused]] float afloat1, [[maybe_unused]] float afloat2) { aBoolFunction(abs(afloat1 + afloat2)); };
}

void Input::InputAction_Vector2f::AddListenerFloat(const std::string& aID, const std::function<void(float)>& aFloatFunction)
{
	myFunctions[aID] = [aFloatFunction]([[maybe_unused]] float afloat1, [[maybe_unused]] float afloat2) { aFloatFunction(afloat1 + afloat2); };
}

void Input::InputAction_Vector2f::AddListenerVector2(const std::string& aID, const std::function<void(float, float)>& aVector2Function)
{
	myFunctions[aID] = [aVector2Function]([[maybe_unused]] float afloat1, [[maybe_unused]] float afloat2) { aVector2Function(afloat1, afloat2); };
}


void Input::InputAction_Vector2f::RemoveListener(const std::string& aID)
{
	auto find = myFunctions.find(aID);
	if (find == myFunctions.end()) return;

	myFunctions.erase(find);
}