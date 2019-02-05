// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "Matrix.h"

// TODO(Lauro): Use custom assertions.
#include <cassert>

#include <algorithm>

namespace BB
{
	// Constructors

	Matrix::Matrix() {}

	Matrix::Matrix(int rows, int cols)
	{
		mElements = Array2D<double>(rows, cols);
	}

	Matrix::Matrix(const std::vector<double>& row)
	{
		mElements = Array2D<double>(row);
	}

	// Getters

	int Matrix::Rows() const
	{
		return (int)mElements.Rows();
	}

	int Matrix::Cols() const
	{
		return (int)mElements.Cols();
	}

	int Matrix::Size() const
	{
		return (int)mElements.Size();
	}

	Array2D<double>& Matrix::Elements()
	{
		return mElements;
	}

	// Calculations

	Matrix Matrix::Transposed() const
	{
		Matrix r(Cols(), Rows());

		for (int col = 0; col < Cols(); col++)
		{
			for (int row = 0; row < Rows(); row++)
			{
				r(col, row) = mElements(row, col);
			}
		}

		return r;
	}

	Matrix Matrix::Foreach(double(*function)(double)) const
	{
		Matrix r(Rows(), Cols());

		for (int i = 0; i < Size(); i++)
		{
			r(i) = (*function)(mElements(i));
		}

		return r;
	}

	Matrix Matrix::MultiplyEntries(const Matrix& m) const
	{
		assert(Rows() == m.Rows() && Cols() == m.Cols());

		Matrix r(Rows(), Cols());

		for (int i = 0; i < Size(); i++)
		{
			r(i) = mElements(i) * m(i);
		}

		return r;
	}

	double Matrix::TotalSum() const
	{
		double r = 0.0;

		for (int i = 0; i < Size(); i++)
		{
			r += mElements(i);
		}

		return r;
	}

	double Matrix::LargestElement() const
	{
		double r = 0.0;

		for (int i = 0; i < Size(); i++)
		{
			if (mElements(i) > r) r = mElements(i);
		}

		return r;
	}

	void Matrix::Fill(double value)
	{
		std::fill(mElements.begin(), mElements.end(), value);
	}

	// Operators

	double & Matrix::operator()(unsigned int idx)
	{
		return mElements(idx);
	}

	const double & Matrix::operator()(unsigned int idx) const
	{
		return mElements(idx);
	}

	double& Matrix::operator() (unsigned int row, unsigned int col)
	{
		return mElements(row, col);
	}

	const double& Matrix::operator() (unsigned int row, unsigned int col) const
	{
		return mElements(row, col);
	}

	Matrix Matrix::operator- () const
	{
		Matrix r(Rows(), Cols());

		for (int i = 0; i < Size(); i++)
		{
			r(i) = -mElements(i);
		}

		return r;
	}

	Matrix operator* (float lhs, const Matrix& rhs)
	{
		Matrix r(rhs.Rows(), rhs.Cols());

		for (int i = 0; i < rhs.Size(); i++)
		{
			r(i) = lhs * rhs(i);
		}

		return r;
	}

	// Arithmetic operators

	Matrix Matrix::operator+ (const Matrix& rhs) const
	{
		assert(Rows() == rhs.Rows() && Cols() == rhs.Cols());

		Matrix r(Rows(), Cols());

		for (int i = 0; i < Size(); i++)
		{
			r(i) = mElements(i) + rhs(i);
		}

		return r;
	}

	Matrix Matrix::operator- (const Matrix& rhs) const
	{
		assert(Rows() == rhs.Rows() && Cols() == rhs.Cols());

		Matrix r(Rows(), Cols());

		for (int i = 0; i < Size(); i++)
		{
			r(i) = mElements(i) - rhs(i);
		}

		return r;
	}

	Matrix Matrix::operator* (const Matrix& rhs) const
	{
		assert(Cols() == rhs.Rows());

		Matrix r(Rows(), rhs.Cols());

		for (int row = 0; row < Rows(); row++)
		{
			for (int col = 0; col < rhs.Cols(); col++)
			{
				double sum = 0.0;

				for (int i = 0; i < Cols(); i++)
				{
					sum += mElements(row, i) * rhs(i, col);
				}

				r(row, col) = sum;
			}
		}

		return r;
	}

	Matrix Matrix::operator* (double rhs) const
	{
		Matrix r(Rows(), Cols());

		for (int i = 0; i < Size(); i++)
		{
			r(i) = mElements(i) * rhs;
		}

		return r;
	}

	Matrix Matrix::operator/ (double rhs) const
	{
		Matrix r(Rows(), Cols());

		for (int i = 0; i < Size(); i++)
		{
			r(i) = mElements(i) / rhs;
		}

		return r;
	}

	// Assignment operators

	Matrix& Matrix::operator+= (const Matrix& rhs)
	{
		return *this = *this + rhs;
	}

	Matrix& Matrix::operator-= (const Matrix& rhs)
	{
		return *this = *this - rhs;
	}

	Matrix& Matrix::operator*= (const Matrix& rhs)
	{
		return *this = *this * rhs;
	}

	Matrix& Matrix::operator*= (double rhs)
	{
		return *this = *this * rhs;
	}

	Matrix& Matrix::operator/= (double rhs)
	{
		return *this = *this / rhs;
	}

	// Relational operators

	bool Matrix::operator== (const Matrix& rhs) const
	{
		return mElements == rhs.mElements;
	}

	bool Matrix::operator!= (const Matrix& rhs) const
	{
		return mElements != rhs.mElements;
	}
}
