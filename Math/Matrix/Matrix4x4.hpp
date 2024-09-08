#pragma once
#include "Vector4.hpp"
#include "MathUtility.hpp"

namespace CU
{
	template <typename T>
	class Matrix4x4
	{
	public:
		// Creates the identity matrix.
		Matrix4x4<T>()
		{
			Clear();
			myMatrix[0][0] = 1;
			myMatrix[1][1] = 1;
			myMatrix[2][2] = 1;
			myMatrix[3][3] = 1;
		}

		// Copy Constructor.
		Matrix4x4<T>(const Matrix4x4<T>& aMatrix)
		{
			*this = aMatrix;
		}

		inline void Clear()
		{
			for (int row = 1; row <= 4; row++)
			{
				for (int collum = 1; collum <= 4; collum++)
				{
					(*this)(row, collum) = 0;
				}
			}
		}

		explicit Matrix4x4<T>(const CU::Vector3<T>& aEulerAngleVector)
		{
			//BPH
			//B => z-Axes
			//P => x-Axes
			//H => y-Axes

			Matrix4x4<T> B = CreateRotationAroundZ(aEulerAngleVector.z);
			Matrix4x4<T> P = CreateRotationAroundX(aEulerAngleVector.x);
			Matrix4x4<T> H = CreateRotationAroundY(aEulerAngleVector.y);
			*this = B * P * H;
		}

		void operator=(const Matrix4x4<T>& inAMatrix)
		{
			for (int row = 1; row <= 4; row++)
			{
				for (int collum = 1; collum <= 4; collum++)
				{
					(*this)(row, collum) = inAMatrix(row, collum);
				}
			}
		}


		Matrix4x4<T>& SetRow(int aRow, const CU::Vector4<T>& aVector)
		{
			aRow--; //Consistent with () and [] operators
			myMatrix[aRow][0] = aVector[0];
			myMatrix[aRow][1] = aVector[1];
			myMatrix[aRow][2] = aVector[2];
			myMatrix[aRow][3] = aVector[3];
			return *this;
		}

		CU::Vector4<T> GetRow(int aRow) const
		{
			aRow--; //Consistent with () and [] operators
			return Vector4<T>(myMatrix[aRow][0], myMatrix[aRow][1], myMatrix[aRow][2], myMatrix[aRow][3]);
		}

		Matrix4x4<T>& SetColumn(int aColumn, const CU::Vector4<T>& aVector)
		{
			aColumn--; //Consistent with () and [] operators
			myMatrix[0][aColumn] = aVector[0];
			myMatrix[1][aColumn] = aVector[1];
			myMatrix[2][aColumn] = aVector[2];
			myMatrix[3][aColumn] = aVector[3];
			return *this;
		}

		CU::Vector4<T> GetColumn(int aColumn) const
		{
			aColumn--; //Consistent with () and [] operators
			return Vector4<T>(myMatrix[0][aColumn], myMatrix[1][aColumn], myMatrix[2][aColumn], myMatrix[3][aColumn]);
		}


		inline Matrix4x4<T> GetNormalize() const
		{
			Matrix4x4<T> matrix(*this);
			matrix.SetRow(1, GetRow(1).Normalize());
			matrix.SetRow(2, GetRow(2).Normalize());
			matrix.SetRow(3, GetRow(3).Normalize());
			matrix.SetRow(4, GetRow(4).Normalize());
			return matrix;
		}

		inline Matrix4x4<T> GetRotationNormalize() const
		{
			Matrix4x4<T> matrix(*this);
			CU::Vector4<T> column4 = matrix.GetColumn(4);
			SetColumn(4, CU::Vector4<T>());
			matrix.SetRow(1, GetRow(1).Normalize());
			matrix.SetRow(2, GetRow(2).Normalize());
			matrix.SetRow(3, GetRow(3).Normalize());
			matrix.SetColumn(4, column4);
			return matrix;
		}

		inline Matrix4x4<T>& Normalize()
		{
			SetRow(1, GetRow(1).Normalize());
			SetRow(2, GetRow(2).Normalize());
			SetRow(3, GetRow(3).Normalize());
			SetRow(4, GetRow(4).Normalize());
			return *this;
		}

		inline Matrix4x4<T>& RotationNormalize()
		{
			CU::Vector4<T> column4 = GetColumn(4);
			SetColumn(4, CU::Vector4<T>());
			SetRow(1, GetRow(1).Normalize());
			SetRow(2, GetRow(2).Normalize());
			SetRow(3, GetRow(3).Normalize());
			SetColumn(4, column4);
			return *this;
		}

		// () operator for accessing element (row, column) for read/write or read, respectively.
		T& operator()(const int aRow, const int aColumn)
		{
			return myMatrix[aRow - 1][aColumn - 1];
		}

		const T& operator()(const int aRow, const int aColumn) const
		{
			return myMatrix[aRow - 1][aColumn - 1];
		}

		T& operator[](const int aRow)
		{
			return myMatrix[aRow];
		}

		const T& operator[](const int aRow) const
		{
			return myMatrix[aRow];
		}

		Matrix4x4<T> operator+(const Matrix4x4<T>& inAMatrix) const
		{
			Matrix4x4<T> newMatrix = *this;
			for (int row = 1; row <= 4; row++)
			{
				for (int collum = 1; collum <= 4; collum++)
				{
					newMatrix(row, collum) += inAMatrix(row, collum);
				}
			}

			return newMatrix;
		}

		void operator+=(const Matrix4x4<T>& inAMatrix)
		{
			*this = *this + inAMatrix;
		}

		Matrix4x4<T> operator-(const Matrix4x4<T>& inAMatrix) const
		{
			Matrix4x4<T> newMatrix = *this;
			for (int row = 1; row <= 4; row++)
			{
				for (int collum = 1; collum <= 4; collum++)
				{
					newMatrix(row, collum) -= inAMatrix(row, collum);
				}
			}

			return newMatrix;
		}

		void operator-=(const Matrix4x4<T>& inAMatrix)
		{
			*this = *this - inAMatrix;
		}

		Matrix4x4<T> operator*(const Matrix4x4<T>& inAMatrix) const
		{
			Matrix4x4<T> newMatrix;
			newMatrix(1, 1) = 0;
			newMatrix(2, 2) = 0;
			newMatrix(3, 3) = 0;
			newMatrix(4, 4) = 0;
			for (int collum = 1; collum <= 4; collum++)
			{
				for (int row = 1; row <= 4; row++)
				{
					for (int multi = 1; multi <= 4; multi++)
					{
						newMatrix(row, collum) += (*this)(row, multi) * inAMatrix(multi, collum);
					}
				}
			}

			return newMatrix;
		}

		void operator*=(const Matrix4x4<T>& inAMatrix)
		{
			*this = *this * inAMatrix;
		}


		bool operator==(const Matrix4x4<T>& inAMatrix) const
		{
			for (int row = 1; row <= 4; row++)
			{
				for (int collum = 1; collum <= 4; collum++)
				{
					if ((*this)(row, collum) != inAMatrix(row, collum))
					{
						return false;
					}
				}
			}

			return true;
		}

		static inline Matrix4x4<T> CreateScaleMatrix(const CU::Vector3<T>& aScaleVector)
		{
			Matrix4x4<T> result;
			result(1, 1) = aScaleVector[0];
			result(2, 2) = aScaleVector[1];
			result(3, 3) = aScaleVector[2];
			return result;
		}

		// Static functions for creating rotation matrices.
		static Matrix4x4<T> CreateRotationAroundX(T aAngleInRadians)
		{
			Matrix4x4<T> newMatrix;
			newMatrix(2, 2) = static_cast<T>(cos(static_cast<double>(aAngleInRadians)));
			newMatrix(2, 3) = static_cast<T>(sin(static_cast<double>(aAngleInRadians)));
			newMatrix(3, 2) = static_cast<T>(-sin(static_cast<double>(aAngleInRadians)));
			newMatrix(3, 3) = static_cast<T>(cos(static_cast<double>(aAngleInRadians)));
			return newMatrix;
		}

		static Matrix4x4<T> CreateRotationAroundY(T aAngleInRadians)
		{
			Matrix4x4<T> newMatrix;
			newMatrix(1, 1) = static_cast<T>(cos(static_cast<double>(aAngleInRadians)));
			newMatrix(1, 3) = static_cast<T>(-sin(static_cast<double>(aAngleInRadians)));
			newMatrix(3, 1) = static_cast<T>(sin(static_cast<double>(aAngleInRadians)));
			newMatrix(3, 3) = static_cast<T>(cos(static_cast<double>(aAngleInRadians)));
			return newMatrix;
		}

		static Matrix4x4<T> CreateRotationAroundZ(T aAngleInRadians)
		{
			Matrix4x4<T> newMatrix;
			newMatrix(1, 1) = static_cast<T>(cos(static_cast<double>(aAngleInRadians)));
			newMatrix(1, 2) = static_cast<T>(sin(static_cast<double>(aAngleInRadians)));
			newMatrix(2, 1) = static_cast<T>(-sin(static_cast<double>(aAngleInRadians)));
			newMatrix(2, 2) = static_cast<T>(cos(static_cast<double>(aAngleInRadians)));
			return newMatrix;
		}


		// Static function for creating a transpose of a matrix.
		static Matrix4x4<T> Transpose(const Matrix4x4<T>& aMatrixToTranspose)
		{
			Matrix4x4 newMatrix = aMatrixToTranspose;
			Swap(newMatrix(1, 2), newMatrix(2, 1));
			Swap(newMatrix(3, 1), newMatrix(1, 3));
			Swap(newMatrix(3, 2), newMatrix(2, 3));
			Swap(newMatrix(4, 1), newMatrix(1, 4));
			Swap(newMatrix(4, 2), newMatrix(2, 4));
			Swap(newMatrix(4, 3), newMatrix(3, 4));
			return newMatrix;
		}

		Matrix4x4<T>& Transpose()
		{
			*this = Matrix4x4<T>::Transpose(*this);
			return *this;
		}

		// Assumes aTransform is made up of nothing but rotations and translations.
		static Matrix4x4<T> FastInverse(const Matrix4x4<T>& aMatrix)
		{
			Matrix4x4<T> transposedMatrix = aMatrix;
			Swap(transposedMatrix(1, 2), transposedMatrix(2, 1));
			Swap(transposedMatrix(3, 1), transposedMatrix(1, 3));
			Swap(transposedMatrix(3, 2), transposedMatrix(2, 3));
			Vector3<T> position = { transposedMatrix(4, 1), transposedMatrix(4, 2), transposedMatrix(4, 3) };
			position *= -1;
			for (int collum = 1; collum <= 3; collum++)
			{
				transposedMatrix(4, collum) = 0;
				for (int row = 1; row <= 3; row++)
				{
					transposedMatrix(4, collum) += transposedMatrix(row, collum) * position[row - 1];
				}
			}
			return transposedMatrix;
		}


		Matrix4x4<T> GetFastInverse() const { return Matrix4x4<T>::FastInverse(*this); }

		Matrix4x4<T>& FastInverse()
		{
			*this = Matrix4x4<T>::FastInverse(*this);
			return *this;
		}


	private:
		T myMatrix[4][4];

		static void Swap(T& inoutAValue, T& inoutAOtherValue)
		{
			T temp = inoutAValue;
			inoutAValue = inoutAOtherValue;
			inoutAOtherValue = temp;
		}
	};

	template <class T> CU::Matrix4x4<T> Multi4x4(
		const CU::Matrix4x4<T>& aLrs,
		const CU::Matrix4x4<T>& aRrs)
	{
		return aLrs * aRrs;
	}

	template <class T> Vector4<T> operator*(const Matrix4x4<T>& outAMatrix, const Vector4<T>& inAVector)
	{
		Vector4<T> newVector;
		for (int collum = 1; collum <= 4; collum++)
		{
			for (int row = 1; row <= 4; row++)
			{
				newVector[collum - 1] += outAMatrix(row, collum) * inAVector[row - 1];
			}
		}

		return newVector;
	}

	template <class T> Vector4<T> operator*(const Vector4<T>& inAVector, const Matrix4x4<T>& outAMatrix)
	{
		return outAMatrix * inAVector;
	}

	typedef CU::Matrix4x4<float>		Matrix4x4f;
	typedef CU::Matrix4x4<unsigned int>	Matrix4x4ui;
	typedef CU::Matrix4x4<int>			Matrix4x4i;
}