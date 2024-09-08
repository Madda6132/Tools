#pragma once
#include "IProcess.h"

namespace Input
{
	class Process_AxisDeadZone : public IProcess
	{
	public:
		// Inherited via Interaction
		inline void Process(float& aValue) const override
		{
			aValue = abs(aValue) < myDeadZone ? 0 : aValue;
		}

		inline void Process(float& aValue1, float& aValue2) const override
		{
			Process(aValue1);
			Process(aValue2);
		}

		void SetDeadZone(const float aDeadZone) { myDeadZone = aDeadZone; }

	private:
		float myDeadZone = 0.2f;
	};


}