#pragma once
#include "IProcess.h"

namespace Input
{
	class Process_Clamp : public IProcess
	{
	public:
		// Inherited via Interaction
		inline void Process(float& aValue) const override
		{
			aValue = aValue < myMin ? myMin : aValue;
			aValue = myMax < aValue ? myMax : aValue;
		}

		inline void Process(float& aValue1, float& aValue2) const override
		{
			Process(aValue1);
			Process(aValue2);
		}

		void SetClamp(const float aMin, const float aMax) 
		{ 
			myMin = aMin;
			myMax = aMax;
		}

	private:
		float myMin = 1.0f;
		float myMax = 1.0f;
	};


}