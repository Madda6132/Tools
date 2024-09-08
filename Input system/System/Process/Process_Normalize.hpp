#pragma once
#include "IProcess.h"
#include <cmath>

namespace Input
{
	class Process_Normalize : public IProcess
	{
	public:
		// Inherited via Interaction
		inline void Process(float& aValue) const override
		{
			aValue = 1.0f;
		}

		inline void Process(float& aValue1, float& aValue2) const override
		{
			if (aValue1 == 0.0f && aValue2 == 0.0f) return;

			const float absolute = (aValue1 * aValue1) + (aValue2 * aValue2);

			const float magnitude = sqrtf(absolute);

			aValue1 /= magnitude;
			aValue2 /= magnitude;
		}

	private:
	};


}