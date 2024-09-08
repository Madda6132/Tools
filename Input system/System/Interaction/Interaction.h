#pragma once

namespace Input
{
	//Should return a enum value of InActive, Activated, Deactivated
	//Continuous interactions will return Deactivated when its value changed from Activated to inactive
	//Press wont return Deactivated

	enum class InteractionState
	{
		Inactive,
		Activated,
		Deactivated
	};

	class Interaction
	{
	public:
		friend class InputBind;
		virtual InteractionState CheckInteraction(const float someDeltaTime, void* aValue) = 0;

		virtual void Reset() = 0;

	protected:
		virtual ~Interaction() {};

	private:
			
	};

}

