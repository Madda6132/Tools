#pragma once
#include <string>
#include "../Interaction/Interaction.h"

//Base class
namespace Input
{
	class InputBind
	{
	public:
		friend class InputAction;

		void Inverse();
		void SetReturnRelease(bool willReturn) { myReturnRelease = willReturn; };
	protected:
		static const int MaxKeyMacro = 3;
		float myModifier = 1.0f;
		bool myReturnRelease = true;
		int myInteractionSize = 0;

		InputBind();
		virtual ~InputBind();

		virtual bool CheckBinding(const float someDeltaTime, float& aValue) = 0;
		virtual bool CheckBinding(const float someDeltaTime, float& aValue1, float& aValue2) = 0;
		Interaction* GetInteraction(int aIndex) const { return myInteraction[aIndex]; }

		virtual void Reset();
		virtual void Init();

		
		void SetInteraction(size_t aIndex, Interaction* aInteraction);
		InteractionState Interact(const float someDeltaTime, size_t aIndex, void* aValue) const;

	private:
		Interaction** myInteraction = nullptr;

	};
}

