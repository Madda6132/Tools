#pragma once
#include <cmath>

namespace CU
{
	template <typename T>
	class Vector2;

	template <typename T>
	class Vector4;

	template <typename T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;

		Vector3() : x(), y(), z() {}

		Vector3(const T& inAX, const T& inAY = 0, const T& inAZ = 0)
		{
			x = inAX;
			y = inAY;
			z = inAZ;
		}

		Vector3<T>(const Vector3<T>& inAVector) = default;

		Vector3(const Vector2<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
			z = 0;
		}

		Vector3(const Vector4<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
			z = aVector.z;
		}

		template<typename D>
		Vector3(const Vector2<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
			z = 0;
		}

		template<typename D>
		Vector3(const Vector4<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
			z = static_cast<T>(aVector.z);
		}


		template <typename D>
		Vector3<T>& operator=(const Vector2<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
			return *this;
		}

		Vector3<T>& operator=(const Vector2<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
			return *this;
		}

		Vector3<T>& operator=(const Vector4<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
			z = aVector.z;
			return *this;
		}

		template <typename D>
		Vector3<T>& operator=(const Vector4<D>& aVector)
		{
			x = static_cast<T>(aVector.x);
			y = static_cast<T>(aVector.y);
			z = static_cast<T>(aVector.z);
			return *this;
		}

		//Assignment operator (compiler generated)
		Vector3<T>& operator=(const Vector3<T>& aVector) = default;


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
			default:
				throw 0;
				break;
			}
		}

		//Destructor (compiler generated)
		~Vector3<T>() = default;

		static Vector3 Zero()
		{
			return Vector3();
		}

		T LengthSqr() const
		{
			T absolute = (x * x) + (y * y) + (z * z);
			return absolute;
		}

		T Length() const
		{
			return static_cast<T>(sqrt(LengthSqr()));
		}


		Vector3 GetNormalized() const
		{
			if (x == 0 && y == 0 && z == 0)
			{
				return Zero();
			}

			T magnitude = Length();
			return Vector3(x / magnitude, y / magnitude, z / magnitude);
		}

		void Normalize()
		{
			*this = GetNormalized();
		}

		T Dot(const Vector3& inAVector) const
		{
			T xValue = x * inAVector.x;
			T yValue = y * inAVector.y;
			T zValue = z * inAVector.z;
			return xValue + yValue + zValue;
		}


		//Vector1 will determine the direction the cross will point
		Vector3 Cross(const Vector3& inAVector) const
		{
			T xValue = (y * inAVector.z) - (z * inAVector.y);
			T yValue = (z * inAVector.x) - (x * inAVector.z);
			T zValue = (x * inAVector.y) - (y * inAVector.x);
			return Vector3(xValue, yValue, zValue);
		}

	private:

	};

	typedef Vector3<float>			Vector3f;
	typedef Vector3<unsigned int>	Vector3ui;
	typedef Vector3<int>			Vector3i;

	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> newVector = Vector3<T>(aVector0);
		newVector.x += aVector1.x;
		newVector.y += aVector1.y;
		newVector.z += aVector1.z;
		return newVector;
	}

	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> newVector = Vector3<T>(aVector0);
		newVector.x -= aVector1.x;
		newVector.y -= aVector1.y;
		newVector.z -= aVector1.z;
		return newVector;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const Vector3<T>& aVector, const int& aScalar)
	{
		Vector3<T> newVector = Vector3<T>(aVector);
		newVector.x *= static_cast<T>(aScalar);
		newVector.y *= static_cast<T>(aScalar);
		newVector.z *= static_cast<T>(aScalar);
		return newVector;
	}

	template <class T> Vector3<T> operator*(const int& aScalar, const Vector3<T>& aVector)
	{
		return aVector * aScalar;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const Vector3<T>& aVector, const float& aScalar)
	{
		Vector3<T> newVector = Vector3<T>(aVector);
		newVector.x *= static_cast<T>(aScalar);
		newVector.y *= static_cast<T>(aScalar);
		newVector.z *= static_cast<T>(aScalar);
		return newVector;
	}

	template <class T> Vector3<T> operator*(const float& aScalar, const Vector3<T>& aVector)
	{
		return aVector * aScalar;
	}

	template <class T> Vector3<T> operator*(const Vector3<T>& aVector1, const Vector3<T>& aVector2)
	{
		Vector3<T> newVector = Vector3<T>(aVector1);
		newVector.x *= aVector2.x;
		newVector.y *= aVector2.y;
		newVector.z *= aVector2.z;
		return newVector;
	}

	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T> Vector3<T> operator/(const Vector3<T>& aVector, const float& aScalar)
	{
		Vector3<T> newVector = Vector3<T>(aVector);
		newVector.x /= static_cast<T>(aScalar);
		newVector.y /= static_cast<T>(aScalar);
		newVector.z /= static_cast<T>(aScalar);
		return newVector;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T, typename D> Vector3<T> operator/(Vector3<T>& aVector1, const Vector3<D>& aVector2)
	{
		Vector3<T> newVector = Vector3<T>(aVector1);
		newVector.x /= static_cast<D>(aVector2.x);
		newVector.y /= static_cast<D>(aVector2.y);
		newVector.z /= static_cast<D>(aVector2.z);
		return newVector;
	}

	template <class T> Vector3<T> operator/(const float& aScalar, const Vector3<T>& aVector)
	{
		return aVector / aScalar;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
	}

	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T, typename D> void operator*=(Vector3<T>& aVector, const D& aScalar)
	{
		aVector.x *= static_cast<T>(aScalar);
		aVector.y *= static_cast<T>(aScalar);
		aVector.z *= static_cast<T>(aScalar);
	}

	//Equivalent to setting aVector to (aVector * aVector)
	template <class T> void operator*=(Vector3<T>& aVector1, const Vector3<T>& aVector2)
	{
		aVector1.x *= aVector2.x;
		aVector1.y *= aVector2.y;
		aVector1.z *= aVector2.z;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T, typename D> void operator/=(Vector3<T>& aVector, const D& aScalar)
	{
		aVector.x /= static_cast<T>(aScalar);
		aVector.y /= static_cast<T>(aScalar);
		aVector.z /= static_cast<T>(aScalar);
	}


	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T, typename D> void operator/=(Vector3<T>& aVector1, const Vector3<D>& aVector2)
	{
		aVector1.x /= static_cast<D>(aVector2.x);
		aVector1.y /= static_cast<D>(aVector2.y);
		aVector1.z /= static_cast<D>(aVector2.z);
	}
}