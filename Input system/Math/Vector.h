#pragma once
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace CU
{
#pragma region Vector2

#pragma region With Vector3

	//Returns the vector sum of aVector0 and aVector1
	template <typename T, typename D> Vector2<T> operator+(const Vector2<T>& aVector0, const Vector3<D>& aVector1)
	{
		Vector2<T> newVector = Vector2<T>(aVector0);
		newVector.x += static_cast<T>(aVector1.x);
		newVector.y += static_cast<T>(aVector1.y);
		return newVector;
	}

	//Returns the vector difference of aVector0 and aVector1
	template <typename T, typename D> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector3<D>& aVector1)
	{
		Vector2<T> newVector = Vector2<T>(aVector0);
		newVector.x -= static_cast<T>(aVector1.x);
		newVector.y -= static_cast<T>(aVector1.y);
		return newVector;
	}

	template <typename T, typename D> Vector2<T> operator*(const Vector2<T>& aVector1, const Vector3<D>& aVector2)
	{
		Vector2<T> newVector = Vector2<T>(aVector1);
		newVector.x *= static_cast<T>(aVector2.x);
		newVector.y *= static_cast<T>(aVector2.y);
		return newVector;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> Vector2<T> operator/(Vector2<T>& aVector1, const Vector3<D>& aVector2)
	{
		Vector2<T> newVector = Vector2<T>(aVector1);
		newVector.x /= static_cast<T>(aVector2.x);
		newVector.y /= static_cast<T>(aVector2.y);
		return newVector;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <typename T, typename D> void operator+=(Vector2<T>& aVector0, const Vector3<D>& aVector1)
	{
		aVector0.x += static_cast<T>(aVector1.x);
		aVector0.y += static_cast<T>(aVector1.y);
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <typename T, typename D> void operator-=(Vector2<T>& aVector0, const Vector3<D>& aVector1)
	{
		aVector0.x -= static_cast<T>(aVector1.x);
		aVector0.y -= static_cast<T>(aVector1.y);
	}

	//Equivalent to setting aVector to (aVector * aVector)
	template <typename T, typename D> void operator*=(Vector2<T>& aVector1, const Vector3<D>& aVector2)
	{
		aVector1.x *= static_cast<T>(aVector2.x);
		aVector1.y *= static_cast<T>(aVector2.y);
	}


	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> void operator/=(Vector2<T>& aVector1, const Vector3<D>& aVector2)
	{
		aVector1.x /= static_cast<T>(aVector2.x);
		aVector1.y /= static_cast<T>(aVector2.y);
	}
#pragma endregion

#pragma region With Vector4


	//Returns the vector sum of aVector0 and aVector1
	template <typename T, typename D> Vector2<T> operator+(const Vector2<T>& aVector0, const Vector4<D>& aVector1)
	{
		Vector2<T> newVector = Vector2<T>(aVector0);
		newVector.x += static_cast<T>(aVector1.x);
		newVector.y += static_cast<T>(aVector1.y);
		return newVector;
	}

	//Returns the vector difference of aVector0 and aVector1
	template <typename T, typename D> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector4<D>& aVector1)
	{
		Vector2<T> newVector = Vector2<T>(aVector0);
		newVector.x -= static_cast<T>(aVector1.x);
		newVector.y -= static_cast<T>(aVector1.y);
		return newVector;
	}

	template <typename T, typename D> Vector2<T> operator*(const Vector2<T>& aVector1, const Vector4<D>& aVector2)
	{
		Vector2<T> newVector = Vector2<T>(aVector1);
		newVector.x *= static_cast<T>(aVector2.x);
		newVector.y *= static_cast<T>(aVector2.y);
		return newVector;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> Vector2<T> operator/(Vector2<T>& aVector1, const Vector4<D>& aVector2)
	{
		Vector2<T> newVector = Vector2<T>(aVector1);
		newVector.x /= static_cast<T>(aVector2.x);
		newVector.y /= static_cast<T>(aVector2.y);
		return newVector;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <typename T, typename D> void operator+=(Vector2<T>& aVector0, const Vector4<D>& aVector1)
	{
		aVector0.x += static_cast<T>(aVector1.x);
		aVector0.y += static_cast<T>(aVector1.y);
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <typename T, typename D> void operator-=(Vector2<T>& aVector0, const Vector4<D>& aVector1)
	{
		aVector0.x -= static_cast<T>(aVector1.x);
		aVector0.y -= static_cast<T>(aVector1.y);
	}

	//Equivalent to setting aVector to (aVector * aVector)
	template <typename T, typename D> void operator*=(Vector2<T>& aVector1, const Vector4<D>& aVector2)
	{
		aVector1.x *= static_cast<T>(aVector2.x);
		aVector1.y *= static_cast<T>(aVector2.y);
	}


	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> void operator/=(Vector2<T>& aVector1, const Vector4<D>& aVector2)
	{
		aVector1.x /= static_cast<T>(aVector2.x);
		aVector1.y /= static_cast<T>(aVector2.y);
	}
#pragma endregion


#pragma endregion
#pragma region Vector3

#pragma region With Vector2

	//Returns the vector sum of aVector0 and aVector1
	template <typename T, typename D> Vector3<T> operator+(const Vector3<T>& aVector0, const Vector2<D>& aVector1)
	{
		Vector3<T> newVector = Vector3<T>(aVector0);
		newVector.x += static_cast<T>(aVector1.x);
		newVector.y += static_cast<T>(aVector1.y);
		return newVector;
	}

	//Returns the vector difference of aVector0 and aVector1
	template <typename T, typename D> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector2<D>& aVector1)
	{
		Vector3<T> newVector = Vector3<T>(aVector0);
		newVector.x -= static_cast<T>(aVector1.x);
		newVector.y -= static_cast<T>(aVector1.y);
		return newVector;
	}

	template <typename T, typename D> Vector3<T> operator*(const Vector3<T>& aVector1, const Vector2<D>& aVector2)
	{
		Vector3<T> newVector = Vector3<T>(aVector1);
		newVector.x *= static_cast<T>(aVector2.x);
		newVector.y *= static_cast<T>(aVector2.y);
		return newVector;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> Vector3<T> operator/(Vector3<T>& aVector1, const Vector2<D>& aVector2)
	{
		Vector3<T> newVector = Vector3<T>(aVector1);
		newVector.x /= static_cast<T>(aVector2.x);
		newVector.y /= static_cast<T>(aVector2.y);
		return newVector;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <typename T, typename D> void operator+=(Vector3<T>& aVector0, const Vector2<D>& aVector1)
	{
		aVector0.x += static_cast<T>(aVector1.x);
		aVector0.y += static_cast<T>(aVector1.y);
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <typename T, typename D> void operator-=(Vector3<T>& aVector0, const Vector2<D>& aVector1)
	{
		aVector0.x -= static_cast<T>(aVector1.x);
		aVector0.y -= static_cast<T>(aVector1.y);
	}

	//Equivalent to setting aVector to (aVector * aVector)
	template <typename T, typename D> void operator*=(Vector3<T>& aVector1, const Vector2<D>& aVector2)
	{
		aVector1.x *= static_cast<T>(aVector2.x);
		aVector1.y *= static_cast<T>(aVector2.y);
	}


	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> void operator/=(Vector3<T>& aVector1, const Vector2<D>& aVector2)
	{
		aVector1.x /= static_cast<T>(aVector2.x);
		aVector1.y /= static_cast<T>(aVector2.y);
	}

#pragma endregion

#pragma region With Vector4

	//Returns the vector sum of aVector0 and aVector1
	template <typename T, typename D> Vector3<T> operator+(const Vector3<T>& aVector0, const Vector4<D>& aVector1)
	{
		Vector3<T> newVector = Vector3<T>(aVector0);
		newVector.x += static_cast<T>(aVector1.x);
		newVector.y += static_cast<T>(aVector1.y);
		newVector.z += static_cast<T>(aVector1.z);
		return newVector;
	}

	//Returns the vector difference of aVector0 and aVector1
	template <typename T, typename D> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector4<D>& aVector1)
	{
		Vector3<T> newVector = Vector3<T>(aVector0);
		newVector.x -= static_cast<T>(aVector1.x);
		newVector.y -= static_cast<T>(aVector1.y);
		newVector.z -= static_cast<T>(aVector1.z);
		return newVector;
	}

	template <typename T, typename D> Vector3<T> operator*(const Vector3<T>& aVector1, const Vector4<D>& aVector2)
	{
		Vector3<T> newVector = Vector3<T>(aVector1);
		newVector.x *= static_cast<T>(aVector2.x);
		newVector.y *= static_cast<T>(aVector2.y);
		newVector.z *= static_cast<T>(aVector2.z);
		return newVector;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> Vector3<T> operator/(Vector3<T>& aVector1, const Vector4<D>& aVector2)
	{
		Vector3<T> newVector = Vector3<T>(aVector1);
		newVector.x /= static_cast<T>(aVector2.x);
		newVector.y /= static_cast<T>(aVector2.y);
		newVector.z /= static_cast<T>(aVector2.z);
		return newVector;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <typename T, typename D> void operator+=(Vector3<T>& aVector0, const Vector4<D>& aVector1)
	{
		aVector0.x += static_cast<T>(aVector1.x);
		aVector0.y += static_cast<T>(aVector1.y);
		aVector0.z += static_cast<T>(aVector1.z);
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <typename T, typename D> void operator-=(Vector3<T>& aVector0, const Vector4<D>& aVector1)
	{
		aVector0.x -= static_cast<T>(aVector1.x);
		aVector0.y -= static_cast<T>(aVector1.y);
		aVector0.z -= static_cast<T>(aVector1.z);
	}

	//Equivalent to setting aVector to (aVector * aVector)
	template <typename T, typename D> void operator*=(Vector3<T>& aVector1, const Vector4<D>& aVector2)
	{
		aVector1.x *= static_cast<T>(aVector2.x);
		aVector1.y *= static_cast<T>(aVector2.y);
		aVector1.z *= static_cast<T>(aVector2.z);
	}


	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> void operator/=(Vector3<T>& aVector1, const Vector4<D>& aVector2)
	{
		aVector1.x /= static_cast<T>(aVector2.x);
		aVector1.y /= static_cast<T>(aVector2.y);
		aVector1.z /= static_cast<T>(aVector2.z);
	}

#pragma endregion


#pragma endregion
#pragma region Vector4

#pragma region With Vector2

	//Returns the vector sum of aVector0 and aVector1
	template <typename T, typename D> Vector4<T> operator+(const Vector4<T>& aVector0, const Vector2<D>& aVector1)
	{
		Vector4<T> newVector = Vector4<T>(aVector0);
		newVector.x += static_cast<T>(aVector1.x);
		newVector.y += static_cast<T>(aVector1.y);
		return newVector;
	}

	//Returns the vector difference of aVector0 and aVector1
	template <typename T, typename D> Vector4<T> operator-(const Vector4<T>& aVector0, const Vector2<D>& aVector1)
	{
		Vector4<T> newVector = Vector4<T>(aVector0);
		newVector.x -= static_cast<T>(aVector1.x);
		newVector.y -= static_cast<T>(aVector1.y);
		return newVector;
	}

	template <typename T, typename D> Vector4<T> operator*(const Vector4<T>& aVector1, const Vector2<D>& aVector2)
	{
		Vector4<T> newVector = Vector4<T>(aVector1);
		newVector.x *= static_cast<T>(aVector2.x);
		newVector.y *= static_cast<T>(aVector2.y);
		return newVector;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> Vector4<T> operator/(Vector4<T>& aVector1, const Vector2<D>& aVector2)
	{
		Vector4<T> newVector = Vector4<T>(aVector1);
		newVector.x /= static_cast<T>(aVector2.x);
		newVector.y /= static_cast<T>(aVector2.y);
		return newVector;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <typename T, typename D> void operator+=(Vector4<T>& aVector0, const Vector2<D>& aVector1)
	{
		aVector0.x += static_cast<T>(aVector1.x);
		aVector0.y += static_cast<T>(aVector1.y);
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <typename T, typename D> void operator-=(Vector4<T>& aVector0, const Vector2<D>& aVector1)
	{
		aVector0.x -= static_cast<T>(aVector1.x);
		aVector0.y -= static_cast<T>(aVector1.y);
	}

	//Equivalent to setting aVector to (aVector * aVector)
	template <class T, typename D> void operator*=(Vector4<T>& aVector1, const Vector2<D>& aVector2)
	{
		aVector1.x *= static_cast<T>(aVector2.x);
		aVector1.y *= static_cast<T>(aVector2.y);
	}


	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> void operator/=(Vector4<T>& aVector1, const Vector2<D>& aVector2)
	{
		aVector1.x /= static_cast<T>(aVector2.x);
		aVector1.y /= static_cast<T>(aVector2.y);
	}
#pragma endregion

#pragma region With Vector3

	//Returns the vector sum of aVector0 and aVector1
	template <typename T, typename D> Vector4<T> operator+(const Vector4<T>& aVector0, const Vector3<D>& aVector1)
	{
		Vector4<T> newVector = Vector4<T>(aVector0);
		newVector.x += static_cast<T>(aVector1.x);
		newVector.y += static_cast<T>(aVector1.y);
		newVector.z += static_cast<T>(aVector1.z);
		return newVector;
	}

	//Returns the vector difference of aVector0 and aVector1
	template <typename T, typename D> Vector4<T> operator-(const Vector4<T>& aVector0, const Vector3<D>& aVector1)
	{
		Vector4<T> newVector = Vector4<T>(aVector0);
		newVector.x -= static_cast<T>(aVector1.x);
		newVector.y -= static_cast<T>(aVector1.y);
		newVector.z -= static_cast<T>(aVector1.z);
		return newVector;
	}

	template <typename T, typename D> Vector4<T> operator*(const Vector4<T>& aVector1, const Vector3<D>& aVector2)
	{
		Vector4<T> newVector = Vector4<T>(aVector1);
		newVector.x *= static_cast<T>(aVector2.x);
		newVector.y *= static_cast<T>(aVector2.y);
		newVector.z *= static_cast<T>(aVector2.z);
		return newVector;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> Vector4<T> operator/(Vector4<T>& aVector1, const Vector3<D>& aVector2)
	{
		Vector4<T> newVector = Vector4<T>(aVector1);
		newVector.x /= static_cast<T>(aVector2.x);
		newVector.y /= static_cast<T>(aVector2.y);
		newVector.z /= static_cast<T>(aVector2.z);
		return newVector;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <typename T, typename D> void operator+=(Vector4<T>& aVector0, const Vector3<D>& aVector1)
	{
		aVector0.x += static_cast<T>(aVector1.x);
		aVector0.y += static_cast<T>(aVector1.y);
		aVector0.z += static_cast<T>(aVector1.z);
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <typename T, typename D> void operator-=(Vector4<T>& aVector0, const Vector3<D>& aVector1)
	{
		aVector0.x -= static_cast<T>(aVector1.x);
		aVector0.y -= static_cast<T>(aVector1.y);
		aVector0.z -= static_cast<T>(aVector1.z);
	}

	//Equivalent to setting aVector to (aVector * aVector)
	template <typename T, typename D> void operator*=(Vector4<T>& aVector1, const Vector3<D>& aVector2)
	{
		aVector1.x *= static_cast<T>(aVector2.x);
		aVector1.y *= static_cast<T>(aVector2.y);
		aVector1.z *= static_cast<T>(aVector2.z);
	}


	//Equivalent to setting aVector to (aVector / aScalar)
	template <typename T, typename D> void operator/=(Vector4<T>& aVector1, const Vector3<D>& aVector2)
	{
		aVector1.x /= static_cast<T>(aVector2.x);
		aVector1.y /= static_cast<T>(aVector2.y);
		aVector1.z /= static_cast<T>(aVector2.z);
	}
#pragma endregion


#pragma endregion
}
