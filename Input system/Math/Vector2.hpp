#pragma once
#include <cmath>


namespace CU
{

	template<typename T>
	class Vector3;

	template<typename T>
	class Vector4;

	template <typename T>
	class Vector2
	{
	public:
		T x;
		T y;

		Vector2() : x(), y() {}

		Vector2(const T& inAX, const T& inAY = 0)
		{
			x = inAX;
			y = inAY;
		}

		Vector2<T>(const Vector2<T>& inAVector) = default;

		Vector2(const Vector3<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
		}

		Vector2(const Vector4<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
		}

		template<typename D>
		Vector2(const Vector3<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
		}

		template<typename D>
		Vector2(const Vector4<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
		}


		//Assignment operator (compiler generated)
		Vector2<T>& operator=(const Vector2<T>& aVector) = default;

		template <typename D>
		Vector2<T>& operator=(const Vector3<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
			return *this;
		}

		Vector2<T>& operator=(const Vector3<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
			return *this;
		}

		Vector2<T>& operator=(const Vector4<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
			return *this;
		}

		template <typename D>
		Vector2<T>& operator=(const Vector4<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
			return *this;
		}



		T& operator[](const int& inAIndex)
		{
			switch (inAIndex)
			{
			case 0:
				return x;
			case 1:
				return y;
			default:
				throw 0;
				break;
			}
		}


		const T& operator[](const int& inAIndex) const
		{
			return *this[inAIndex];
		}

		//Destructor (compiler generated)
		~Vector2<T>() = default;

		static Vector2 Zero()
		{
			return Vector2();
		}

		T LengthSqr() const
		{
			T absolute = (x * x) + (y * y);
			return absolute;
		}

		T Length() const
		{
			return static_cast<T>(sqrt(LengthSqr()));
		}

		Vector2 GetNormalized() const
		{
			if (x == 0 && y == 0)
			{
				return Zero();
			}

			float magnitude = Length();
			return Vector2(x / magnitude, y / magnitude);
		}

		void Normalize()
		{
			*this = GetNormalized();
		}

		T Dot(const Vector2& inAVector) const
		{
			T xValue = x * inAVector.x;
			T yValue = y * inAVector.y;
			return xValue + yValue;
		}

		float GetVectorAngle() const
		{

			const float PI = 3.14159265f;
			return atan2(y, x) * 180 / PI;
		}


	public:

		Vector2 GetRotatedCounterClockwise(float aAngle) const
		{
			return GetRotated(aAngle);
		}

		Vector2 GetRotatedClockwise(float aAngle) const
		{
			return GetRotated(-aAngle);
		}
	private:

		Vector2 GetRotated(float aAngle) const
		{
			const float PI = 3.14159265f;
			aAngle *= PI / 180;

			T clockX = static_cast<T>((x * cos(aAngle)) - (y * sin(aAngle)));
			T clockY = static_cast<T>(x * sin(aAngle) + y * cos(aAngle));
			return Vector2(clockX, clockY);
		}
	};

	typedef Vector2<float>			Vector2f;
	typedef Vector2<unsigned int>	Vector2ui;
	typedef Vector2<int>			Vector2i;


	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> newVector = Vector2<T>(aVector0);
		newVector.x += aVector1.x;
		newVector.y += aVector1.y;
		return newVector;
	}

	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> newVector = Vector2<T>(aVector0);
		newVector.x -= aVector1.x;
		newVector.y -= aVector1.y;
		return newVector;
	}



	//Returns the vector aVector multiplied by the scalar aScalar

	template <class T> Vector2<T> operator*(const Vector2<T>& aVector, const int& aScalar)
	{
		Vector2<T> newVector = Vector2<T>(aVector);
		newVector.x *= static_cast<T>(aScalar);
		newVector.y *= static_cast<T>(aScalar);
		return newVector;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const Vector2<T>& aVector, const float& aScalar)
	{
		Vector2<T> newVector = Vector2<T>(aVector);
		newVector.x *= static_cast<T>(aScalar);
		newVector.y *= static_cast<T>(aScalar);
		return newVector;
	}


	template <class T> Vector2<T> operator*(const Vector2<T>& aVector1, const Vector2<T>& aVector2)
	{
		Vector2<T> newVector = Vector2<T>(aVector1);
		newVector.x *= aVector2.x;
		newVector.y *= aVector2.y;
		return newVector;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const int& aScalar, const Vector2<T>& aVector)
	{
		return aVector * aScalar;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const float& aScalar, const Vector2<T>& aVector)
	{
		return aVector * aScalar;
	}

	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T> Vector2<T> operator/(const Vector2<T>& aVector, const int& aScalar)
	{
		Vector2<T> newVector = Vector2<T>(aVector);
		newVector.x /= static_cast<T>(aScalar);
		newVector.y /= static_cast<T>(aScalar);
		return newVector;
	}

	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T> Vector2<T> operator/(const Vector2<T>& aVector, const float& aScalar)
	{
		Vector2<T> newVector = Vector2<T>(aVector);
		newVector.x /= static_cast<T>(aScalar);
		newVector.y /= static_cast<T>(aScalar);
		return newVector;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
	}

	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T, typename D> void operator*=(Vector2<T>& aVector, const D& aScalar)
	{
		aVector.x *= static_cast<T>(aScalar);
		aVector.y *= static_cast<T>(aScalar);
	}

	//Equivalent to setting aVector to (aVector * aVector)
	template <class T> void operator*=(Vector2<T>& aVector1, const Vector2<T>& aVector2)
	{
		aVector1.x *= aVector2.x;
		aVector1.y *= aVector2.y;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T, typename D> void operator/=(Vector2<T>& aVector, const int& aScalar)
	{
		aVector.x /= static_cast<T>(aScalar);
		aVector.y /= static_cast<T>(aScalar);
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T, typename D> void operator/=(Vector2<T>& aVector, const float& aScalar)
	{
		aVector.x /= static_cast<T>(aScalar);
		aVector.y /= static_cast<T>(aScalar);
	}

}