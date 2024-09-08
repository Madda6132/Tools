#pragma once


namespace Input
{
	class IProcess
	{
	public:
		friend class InputAction;
		virtual void Process(float& aValue) const = 0;
		virtual void Process(float& aValue1, float& aValue2) const = 0;

	protected:
		virtual ~IProcess() = default;

	private:
	};

}