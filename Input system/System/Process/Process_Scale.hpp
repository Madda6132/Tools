#pragma once
#include "IProcess.h"

namespace Input
{
	class Process_Scale : public IProcess
	{
	public:
		// Inherited via Interaction
		inline void Process(float& aValue) const override
		{
			aValue *= myScale;
		}


		inline void Process(float& aValue1, float& aValue2) const override
		{
			Process(aValue1);
			Process(aValue2);
		}

		void SetScale(const float aScale) { myScale = aScale; }

	private:
		float myScale = 1.0f;
	};


}