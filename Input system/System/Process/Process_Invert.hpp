#pragma once
#include "IProcess.h"

namespace Input
{
	class Process_Invert : public IProcess
	{
	public:
		// Inherited via Interaction
		void Process(float& aValue) const override
		{
			aValue *= -1;
		}

		inline void Process(float& aValue1, float& aValue2) const override
		{
			Process(aValue1);
			Process(aValue2);
		}

	private:

	};


}