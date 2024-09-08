#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>

#include "../Binding/InputBind.h"

//Base class
namespace Input
{
	class IProcess;

	class InputAction
	{
	public:
		friend class InputControlManager;
		friend class InputProfile;

		void SetEnable(const bool& aEnable);

		inline InputBind& GetBinding(const std::string& aID) const;

		template <typename T>
		inline T& CreateBinding(const std::string& aID)
		{
			auto find = myBindings.find(aID);

			if (find != myBindings.end())
			{
				//Already exists
				throw;
			}

			T* binding = new T();
			myBindings[aID] = binding;
			return *binding;
		}

		virtual void AddListenerVoid(const std::string& aID, const std::function<void()>&					aVoidFunction)		= 0;
		virtual void AddListenerBool(const std::string& aID, const std::function<void(bool)>&				aBoolFunction)		= 0;
		virtual void AddListenerFloat(const std::string& aID, const std::function<void(float)>&				aFloatFunction)		= 0;
		virtual void AddListenerVector2(const std::string& aID, const std::function<void(float, float)>&	aVector2Function)	= 0;
		virtual void RemoveListener(const std::string& aID)																		= 0;

		InputBind& operator[](const std::string& aID) const;

	protected:
		std::map<std::string, InputBind*> myBindings;
		std::vector<IProcess*> myProcesses;

		virtual ~InputAction();

		virtual void Update(float someDeltaTime)				= 0;
		virtual void AddProcess_AxisDeadZone(float aAmount)		= 0;
		virtual void AddProcess_Clamp(float aMin, float aMax)	= 0;
		virtual void AddProcess_Invert()						= 0;
		virtual void AddProcess_Normalize()						= 0;
		virtual void AddProcess_Scale(float aAmount)			= 0;

		bool CheckBindings(float someDeltaTime, float& aValue) const;
		bool CheckBindings(float someDeltaTime, float& aValue1, float& aValue2) const;
		void Process(float& aValue) const;
		void Process(float& aValue1, float& aValue2) const;

	private:
		bool myIsActive = true;


		void BaseUpdate(float someDeltaTime);
		
	};
}

