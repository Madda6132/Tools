#pragma once
#include <assert.h>
#include <random>

namespace CU 
{
	constexpr float PI = 3.14159274f;
	constexpr float TAU = 6.28318548f;
	constexpr float RAD2DEG = 57.29578f;
	constexpr float DEG2RAD = 0.0174532924f;

	template <typename T>
	const T& Max(const T& inAValue1, const T& inAValue2)
	{
		return inAValue1 < inAValue2 ? inAValue2 : inAValue1;
	}

	template <typename T>
	const T& Min(const T& inAValue1, const T& inAValue2)
	{
		return inAValue1 < inAValue2 ? inAValue1 : inAValue2;
	}

	template <typename T>
	bool Approximately(const T& inAValue1, const T& inAValue2, int someDecimals = 3)
	{
		int multiplier = 1;
		for (size_t i = 0; i < someDecimals; i++)
		{
			multiplier *= 10;
		}
		int approximately1 = static_cast<int>(inAValue1 * multiplier);
		int approximately2 = static_cast<int>(inAValue2 * multiplier);

		return approximately1 && approximately2;
	}

	template <typename T>
	T Abs(const T& aValue)
	{
		return 0 < aValue ? aValue : aValue * -1;
	}

	template <typename T>
	T Sign(const T& aValue)
	{
		if (aValue == 0)
		{
			return 0;
		}
		return 0 < aValue ? 1 : -1;
	}

	template <typename T>
	const T& Clamp(const T& aValue, const T& aMinValue, const T& aMaxValue)
	{
		assert(aMinValue <= aMaxValue && "Min Value cant be higher than max value");

		if (aValue < aMinValue)
		{
			return aMinValue;
		}

		if (aMaxValue < aValue)
		{
			return aMaxValue;
		}

		return aValue;
	}

	template <typename T>
	T Lerp(const T& aValue1, const T& aValue2, float somePercent)
	{
		somePercent = Clamp(somePercent, 0.0f, 1.0f);

		return aValue1 + (somePercent * (aValue2 - aValue1));
	}

	template <typename T>
	void Swap(T& inoutAValue, T& inoutAOtherValue)
	{
		T temp = inoutAValue;
		inoutAValue = inoutAOtherValue;
		inoutAOtherValue = temp;
	}

	__forceinline int RandomValue(const int& aMinValue, const int& aMaxValue)
	{
		std::random_device randEngine;
		std::uniform_int_distribution<int> uniformInt(aMinValue, aMaxValue);
		return uniformInt(randEngine);
	}


	__forceinline float RandomValue(const float& aMinValue, const float& aMaxValue)
	{
		std::random_device randEngine;
		std::uniform_real_distribution<float> uniformInt(aMinValue, aMaxValue);
		return uniformInt(randEngine);
	}

}
