#pragma once
#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"

template <typename T> CU::Matrix3x3<T> TransTo3x3(const CU::Matrix4x4<T>& aMatrix)
{
	CU::Matrix3x3<T> matrix;
	
	for (int row = 1; row <= 3; row++)
	{
		for (int column = 1; column <= 3; column++)
		{
			matrix(row, column) = aMatrix(row, column);
		}
	}

	return matrix;
}

template <typename T> CU::Matrix4x4<T> TransTo4x4(const CU::Matrix3x3<T>& aMatrix)
{
	CU::Matrix4x4<T> matrix;

	for (int row = 1; row <= 3; row++)
	{
		for (int column = 1; column <= 3; column++)
		{
			matrix(row, column) = aMatrix(row, column);
		}
	}

	return matrix;
}


template <class T> CU::Matrix4x4<T> operator*(const CU::Matrix4x4<T>& aMatrix4x4, const CU::Matrix3x3<T>& aMatrix3x3)
{
	CU::Matrix4x4<T> newMatrix;
	newMatrix(1, 1) = 0;
	newMatrix(2, 2) = 0;
	newMatrix(3, 3) = 0;
	newMatrix.SetRow(4, aMatrix4x4.GetRow(4));
	newMatrix.SetColumn(4, aMatrix4x4.GetColumn(4));

	for (int row = 1; row <= 3; row++)
	{
		for (int collum = 1; collum <= 3; collum++)
		{
			for (int multi = 1; multi <= 3; multi++)
			{
				newMatrix(row, collum) += aMatrix4x4(row, multi) * aMatrix3x3(multi, collum);
			}
		}
	}

	return newMatrix;
}

template <class T> CU::Matrix3x3<T> operator*(const CU::Matrix3x3<T>& aMatrix3x3, const CU::Matrix4x4<T>& aMatrix4x4)
{
	CU::Matrix3x3<T> newMatrix;
	newMatrix(1, 1) = 0;
	newMatrix(2, 2) = 0;
	newMatrix(3, 3) = 0;

	for (int collum = 1; collum <= 3; collum++)
	{
		for (int row = 1; row <= 3; row++)
		{
			for (int multi = 1; multi <= 3; multi++)
			{
				newMatrix(row, collum) += aMatrix3x3(row, multi) * aMatrix4x4(multi, collum);
			}
		}
	}

	return newMatrix;
}

template <class T> CU::Matrix4x4<T> Multi4x4(
	const CU::Matrix3x3<T>& aLhs, 
	const CU::Matrix4x4<T>& aRhs)
{
	CU::Matrix4x4<T> matrix(aRhs);
	matrix(1, 1) = 0;
	matrix(2, 2) = 0;
	matrix(3, 3) = 0;
	matrix.SetRow(4, aRhs.GetRow(4));
	matrix.SetColumn(4, aRhs.GetColumn(4));

	for (int collum = 1; collum <= 3; collum++)
	{
		for (int row = 1; row <= 3; row++)
		{
			for (int multi = 1; multi <= 3; multi++)
			{
				matrix(row, collum) += aLhs(row, multi) * aRhs(multi, collum);
			}
		}
	}

	return matrix;
}

template <class T> CU::Matrix4x4<T> Multi4x4(
	const CU::Matrix4x4<T>& aLhs,
	const CU::Matrix3x3<T>& aRhs)
{
	return aLhs * aRhs;
}

template <class T> CU::Matrix4x4<T> Multi4x4(
	const CU::Matrix4x4<T>& aLrs,
	const CU::Matrix4x4<T>& aRhs)
{
	return aLrs * aRhs;
}

template <class T> CU::Matrix3x3<T> Multi3x3(
	const CU::Matrix3x3<T>& aLrs,
	const CU::Matrix4x4<T>& aRhs)
{
	return aLrs * aRhs;
}

template <class T> CU::Matrix3x3<T> Multi3x3(
	const CU::Matrix4x4<T>& aLhs,
	const CU::Matrix3x3<T>& aRhs)
{
	CU::Matrix3x3<T> matrix(aRhs);
	matrix(1, 1) = 0;
	matrix(2, 2) = 0;
	matrix(3, 3) = 0;

	for (int collum = 1; collum <= 3; collum++)
	{
		for (int row = 1; row <= 3; row++)
		{
			for (int multi = 1; multi <= 3; multi++)
			{
				matrix(row, collum) += aLhs(row, multi) * aRhs(multi, collum);
			}
		}
	}

	return matrix;
}

template <class T> CU::Matrix3x3<T> Multi3x3(
	const CU::Matrix3x3<T>& aLrs,
	const CU::Matrix3x3<T>& aRhs)
{
	return aLrs * aRhs;
}
