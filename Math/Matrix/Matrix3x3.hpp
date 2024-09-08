#pragma once
#include "Vector3.hpp"
#include "MathUtility.hpp"

namespace CU
{
	template <typename T>
	class Matrix3x3
	{
	public:
		// Creates the identity matrix.
		Matrix3x3<T>()
		{
			Clear();
			myMatrix[0][0] = 1;
			myMatrix[1][1] = 1;
			myMatrix[2][2] = 1;
		}

		// Copy Constructor.
		Matrix3x3<T>(const Matrix3x3<T>& aMatrix)
		{
			*this = aMatrix;
		}

		Matrix3x3<T>(const CU::Vector3<T>& aEulerAngleVector)
		{
			//BPH
			//B => z-Axes
			//P => x-Axes
			//H => y-Axes
			CU::Vector3<T> radians = aEulerAngleVector * CU::DEG2RAD;
			Matrix3x3<T> B = CreateRotationAroundZ(radians.z);
			Matrix3x3<T> P = CreateRotationAroundX(radians.x);
			Matrix3x3<T> H = CreateRotationAroundY(radians.y);
			*this = B * P * H;
		}

		inline void Clear()
		{
			for (int row = 1; row <= 3; row++)
			{
				for (int collum = 1; collum <= 3; collum++)
				{
					(*this)(row, collum) = 0;
				}
			}
		}

		CU::Vector3<T> GetEularAngles() const
		{
			// We will compute the Euler angle values in radians
			// and store them here:
			CU::Vector3<T> eular;
			
			// Extract pitch from m32, being careful for domain errors with
			// asin (). We could have values slightly out of range due to
			// floating point arithmetic .
			
			float sp = -myMatrix[2][1];
			if(sp <= -1.0f) {
				eular.x = -1.570796f; // −pi/2
			}
			 else if (sp >= 1.0f) 
			{
				eular.x = 1.570796f; // pi/2
			}
			 else 
			{
				eular.x = asin(sp);
			}
			// Check for the Gimbal lock case , giving a slight tolerance
			// for numerical imprecision
			if(fabs(sp) > 0.9999f) 
			{
				// We are looking straight up or down.
				// Slam bank to zero and just set heading
				eular.z = 0.0f;
				eular.y = std::atan2(-myMatrix[0][2], myMatrix[0][0]);
			}
			else 
			{
				// Compute heading from m13 and m33
				eular.y = std::atan2(myMatrix[2][0], myMatrix[2][2]);
				// Compute bank from m21 and m22
				eular.z = std::atan2(myMatrix[0][1], myMatrix[1][1]);
			}

			eular *= CU::RAD2DEG;
			return eular;
		}

		inline Matrix3x3<T> GetNormalize() const
		{
			Matrix3x3<T> matrix(*this);
			matrix.SetRow(1, GetRow(1).Normalize());
			matrix.SetRow(2, GetRow(2).Normalize());
			matrix.SetRow(3, GetRow(3).Normalize());
			return matrix;
		}

		inline Matrix3x3<T>& Normalize()
		{
			SetRow(1, GetRow(1).Normalize());
			SetRow(2, GetRow(2).Normalize());
			SetRow(3, GetRow(3).Normalize());
			return *this;
		}

		Matrix3x3<T>& SetRow(int aRow, const CU::Vector3<T>& aVector) 
		{
			aRow--; //Consistent with () and [] operators
			myMatrix[aRow][0] = aVector[0];
			myMatrix[aRow][1] = aVector[1];
			myMatrix[aRow][2] = aVector[2];
			return *this;
		}


		CU::Vector3<T> GetRow(int aRow) const
		{
			aRow--; //Consistent with () and [] operators
			return Vector3<T>(myMatrix[aRow][0], myMatrix[aRow][1], myMatrix[aRow][2]);
		}


		Matrix3x3<T>& SetColumn(int aColumn, const CU::Vector3<T>& aVector)
		{
			aColumn--; //Consistent with () and [] operators
			myMatrix[0][aColumn] = aVector[0];
			myMatrix[1][aColumn] = aVector[1];
			myMatrix[2][aColumn] = aVector[2];
			return *this;
		}

		CU::Vector3<T> GetColumn(int aColumn) const
		{
			aColumn--; //Consistent with () and [] operators
			return Vector3<T>(myMatrix[0][aColumn], myMatrix[1][aColumn], myMatrix[2][aColumn]);
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

		Matrix3x3<T> operator+(const Matrix3x3<T>& inAMatrix) const
		{
			Matrix3x3<T> newMatrix = *this;
			for (int row = 1; row <= 3; row++)
			{
				for (int collum = 1; collum <= 3; collum++)
				{
					newMatrix(row, collum) += inAMatrix(row, collum);
				}
			}

			return newMatrix;
		}

		void operator+=(const Matrix3x3<T>& inAMatrix)
		{
			*this = *this + inAMatrix;
		}

		Matrix3x3<T> operator-(const Matrix3x3<T>& inAMatrix) const
		{
			Matrix3x3<T> newMatrix = *this;
			for (int row = 1; row <= 3; row++)
			{
				for (int collum = 1; collum <= 3; collum++)
				{
					newMatrix(row, collum) -= inAMatrix(row, collum);
				}
			}

			return newMatrix;
		}

		void operator-=(const Matrix3x3<T>& inAMatrix)
		{
			*this = *this - inAMatrix;
		}

		void operator*=(const Matrix3x3<T>& inAMatrix)
		{
			*this = *this * inAMatrix;
		}


		Matrix3x3<T> operator*(const Matrix3x3<T>& inAMatrix) const
		{
			Matrix3x3<T> newMatrix;
			newMatrix(1, 1) = 0;
			newMatrix(2, 2) = 0;
			newMatrix(3, 3) = 0;
			for (int collum = 1; collum <= 3; collum++)
			{
				for (int row = 1; row <= 3; row++)
				{
					for (int multi = 1; multi <= 3; multi++)
					{
						float rowValue = (*this)(multi, collum);
						float collumValue = inAMatrix(row, multi);
						newMatrix(row, collum) += (*this)(row, multi) * inAMatrix(multi, collum);
					}

				}
			}

			return newMatrix;
		}

		bool operator==(const Matrix3x3<T>& inAMatrix) const
		{
			for (int row = 1; row <= 3; row++)
			{
				for (int collum = 1; collum <= 3; collum++)
				{
					if ((*this)(row, collum) != inAMatrix(row, collum))
					{
						return false;
					}
				}
			}

			return true;
		}

		static inline Matrix3x3<T> CreateScaleMatrix(const CU::Vector3<T>& aScaleVector)
		{
			Matrix3x3<T> result;
			result(1, 1) = aScaleVector[0];
			result(2, 2) = aScaleVector[1];
			result(3, 3) = aScaleVector[2];
			return result;
		}

		// Static functions for creating rotation matrices.
		static Matrix3x3<T> CreateRotationAroundX(T aAngleInRadians)
		{
			Matrix3x3<T> newMatrix;
			newMatrix(2, 2) = static_cast<T>( cos(static_cast<double>(aAngleInRadians))		);
			newMatrix(2, 3) = static_cast<T>( sin(static_cast<double>(aAngleInRadians))		);
			newMatrix(3, 2) = static_cast<T>( -sin(static_cast<double>(aAngleInRadians))	);
			newMatrix(3, 3) = static_cast<T>( cos(static_cast<double>(aAngleInRadians))		);
			return newMatrix;

		}

		static Matrix3x3<T> CreateRotationAroundY(T aAngleInRadians)
		{
			Matrix3x3<T> newMatrix;
			newMatrix(1, 1) = static_cast<T>( cos(static_cast<double>(aAngleInRadians))		);
			newMatrix(1, 3) = static_cast<T>( -sin(static_cast<double>(aAngleInRadians))	);
			newMatrix(3, 1) = static_cast<T>( sin(static_cast<double>(aAngleInRadians))		);
			newMatrix(3, 3) = static_cast<T>( cos(static_cast<double>(aAngleInRadians))		);
			return newMatrix;

		}

		static Matrix3x3<T> CreateRotationAroundZ(T aAngleInRadians)
		{
			Matrix3x3<T> newMatrix;
			newMatrix(1, 1) = static_cast<T>( cos(static_cast<double>(aAngleInRadians))		);
			newMatrix(1, 2) = static_cast<T>( sin(static_cast<double>(aAngleInRadians))		);
			newMatrix(2, 1) = static_cast<T>( -sin(static_cast<double>(aAngleInRadians))	);
			newMatrix(2, 2) = static_cast<T>( cos(static_cast<double>(aAngleInRadians))		);
			return newMatrix;

		}


		// Static function for creating a transpose of a matrix.
		static Matrix3x3<T> Transpose(const Matrix3x3<T>& aMatrixToTranspose)
		{
			Matrix3x3 newMatrix = aMatrixToTranspose;
			Swap(newMatrix(1, 2), newMatrix(2, 1));
			Swap(newMatrix(3, 1), newMatrix(1, 3));
			Swap(newMatrix(3, 2), newMatrix(2, 3));

			return newMatrix;
		}

		Matrix3x3<T>& Transpose()
		{
			*this = Matrix3x3<T>::Transpose(*this);
			return *this;
		}

	private:
		T myMatrix[3][3];

		static void Swap(T& inoutAValue, T& inoutAOtherValue)
		{
			T temp = inoutAValue;
			inoutAValue = inoutAOtherValue;
			inoutAOtherValue = temp;
		}
	};

	template <class T> CU::Matrix3x3<T> Multi3x3(
		const CU::Matrix3x3<T>& aLrs,
		const CU::Matrix3x3<T>& aRrs)
	{
		return aLrs * aRrs;
	}

	template <class T> Vector3<T> operator*(const Matrix3x3<T>& outAMatrix, const Vector3<T>& inAVector)
	{
		Vector3<T> newVector;
		for (int collum = 1; collum <= 3; collum++)
		{
			for (int row = 1; row <= 3; row++)
			{
				newVector[collum - 1] += outAMatrix(row, collum) * inAVector[row - 1];
			}
		}

		return newVector;
	}

	template <class T> Vector3<T> operator*(const Vector3<T>& inAVector, const Matrix3x3<T>& outAMatrix)
	{
		return outAMatrix * inAVector;
	}

	typedef CU::Matrix3x3<float>		Matrix3x3f;
	typedef CU::Matrix3x3<unsigned int>	Matrix3x3ui;
	typedef CU::Matrix3x3<int>			Matrix3x3i;
}
