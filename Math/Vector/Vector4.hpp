#pragma once
#include <cmath>

namespace CU
{

	template<typename T>
	class Vector2;

	template<typename T>
	class Vector3;


	template <typename T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;

		Vector4() : x(), y(), z(), w() {}

		Vector4(const T& inAX, const T& inAY = 0, const T& inAZ = 0, const T& inAW = 0)
		{
			x = inAX;
			y = inAY;
			z = inAZ;
			w = inAW;
		}

		Vector4<T>(const Vector4<T>& inAVector) = default;

		Vector4(const Vector2<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
			z = 0;
			w = 0;
		}

		Vector4(const Vector3<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
			z = aVector.z;
			w = 0;
		}

		template<typename D>
		Vector4(const Vector3<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
			z = static_cast<T>(aVector.z);
			w = 0;
		}

		template<typename D>
		Vector4(const Vector2<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
			z = 0;
			w = 0;
		}


		Vector4<T>& operator=(const Vector2<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
			return *this;
		}

		template <typename D>
		Vector4<T>& operator=(const Vector2<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
			return *this;
		}

		Vector4<T>& operator=(const Vector3<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
			z = aVector.z;
			return *this;
		}

		template <typename D>
		Vector4<T>& operator=(const Vector3<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
			z = static_cast<T>(aVector.z);
			return *this;
		}

		//Assignment operator (compiler generated)
		Vector4<T>& operator=(const Vector4<T>& aVector) = default;


		T& operator[](const int& inAIndex)
		{
			switch (inAIndex)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			default:
				throw 0;
				break;
			}
		}

		const T& operator[](const int& inAIndex) const
		{
			switch (inAIndex)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			default:
				throw 0;
				break;
			}
		}

		//Destructor (compiler generated)
		~Vector4<T>() = default;

		static Vector4 Zero()
		{
			return Vector4();
		}

		T LengthSqr() const
		{
			T absolute = (x * x) + (y * y) + (z * z) + (w * w);
			return absolute;
		}

		T Length() const
		{
			return static_cast<T>(sqrt(LengthSqr()));
		}

		Vector4 GetNormalized() const
		{
			if (x == 0 && y == 0 && z == 0 && w == 0)
			{
				return Zero();
			}
			float magnitude = Length();
			return Vector4(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
		}

		inline Vector4& Normalize()
		{
			*this = GetNormalized();
			return *this;
		}

		T Dot(const Vector4& inAVector) const
		{
			T xValue = x * inAVector.x;
			T yValue = y * inAVector.y;
			T zValue = z * inAVector.z;
			T wValue = w * inAVector.w;
			return xValue + yValue + zValue + wValue;
		}



	private:

	};


	typedef Vector4<float>			Vector4f;
	typedef Vector4<unsigned int>	Vector4ui;
	typedef Vector4<int>			Vector4i;

	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> newVector = Vector4<T>(aVector0);
		newVector.x += aVector1.x;
		newVector.y += aVector1.y;
		newVector.z += aVector1.z;
		newVector.w += aVector1.w;
		return newVector;
	}

	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> newVector = Vector4<T>(aVector0);
		newVector.x -= aVector1.x;
		newVector.y -= aVector1.y;
		newVector.z -= aVector1.z;
		newVector.w -= aVector1.w;
		return newVector;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const Vector4<T>& aVector, const float& aScalar)
	{
		Vector4<T> newVector = Vector4<T>(aVector);
		newVector.x *= static_cast<T>(aScalar);
		newVector.y *= static_cast<T>(aScalar);
		newVector.z *= static_cast<T>(aScalar);
		newVector.w *= static_cast<T>(aScalar);
		return newVector;
	}

	template <class T> Vector4<T> operator*(const Vector4<T>& aVector, const int& aScalar)
	{
		Vector4<T> newVector = Vector4<T>(aVector);
		newVector.x *= static_cast<T>(aScalar);
		newVector.y *= static_cast<T>(aScalar);
		newVector.z *= static_cast<T>(aScalar);
		newVector.w *= static_cast<T>(aScalar);
		return newVector;
	}

	template <class T> Vector4<T> operator*(const float& aScalar, const Vector4<T>& aVector)
	{
		return aVector * aScalar;
	}

	template <class T> Vector4<T> operator*(const int& aScalar, const Vector4<T>& aVector)
	{
		return aVector * aScalar;
	}

	template <class T> Vector4<T> operator*(const Vector4<T>& aVector1, const Vector4<T>& aVector2)
	{
		Vector4<T> newVector = Vector4<T>(aVector1);
		newVector.x *= aVector2.x;
		newVector.y *= aVector2.y;
		newVector.z *= aVector2.z;
		newVector.w *= aVector2.w;
		return newVector;
	}


	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T> Vector4<T> operator/(const Vector4<T>& aVector, const int& aScalar)
	{
		Vector4<T> newVector = Vector4<T>(aVector);
		newVector.x /= static_cast<T>(aScalar);
		newVector.y /= static_cast<T>(aScalar);
		newVector.z /= static_cast<T>(aScalar);
		newVector.w /= static_cast<T>(aScalar);
		return newVector;
	}

	template <class T> Vector4<T> operator/(const Vector4<T>& aVector, const float& aScalar)
	{
		Vector4<T> newVector = Vector4<T>(aVector);
		newVector.x /= static_cast<T>(aScalar);
		newVector.y /= static_cast<T>(aScalar);
		newVector.z /= static_cast<T>(aScalar);
		newVector.w /= static_cast<T>(aScalar);
		return newVector;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
		aVector0.w += aVector1.w;
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
		aVector0.w -= aVector1.w;
	}

	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T, typename D> void operator*=(Vector4<T>& aVector, const D& aScalar)
	{
		aVector.x *= static_cast<T>(aScalar);
		aVector.y *= static_cast<T>(aScalar);
		aVector.z *= static_cast<T>(aScalar);
		aVector.w *= static_cast<T>(aScalar);
	}

	//Equivalent to setting aVector to (aVector * aVector)
	template <class T> void operator*=(Vector4<T>& aVector1, const Vector4<T>& aVector2)
	{
		aVector1.x *= aVector2.x;
		aVector1.y *= aVector2.y;
		aVector1.z *= aVector2.z;
		aVector1.w *= aVector2.w;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T, typename D> void operator/=(Vector4<T>& aVector, const D& aScalar)
	{
		aVector.x /= static_cast<T>(aScalar);
		aVector.y /= static_cast<T>(aScalar);
		aVector.z /= static_cast<T>(aScalar);
		aVector.w /= static_cast<T>(aScalar);
	}
}