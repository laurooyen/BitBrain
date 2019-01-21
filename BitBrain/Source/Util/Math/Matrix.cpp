// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "Matrix.h"

// TODO(Lauro): Use custom assertions.
#include <cassert>

namespace BB
{
	// Constructors

	Matrix::Matrix()
		: rows(0), cols(0) {}

	Matrix::Matrix(int rows, int cols)
		: rows(rows), cols(cols)
	{
		this->elements = std::vector<std::vector<double>>(rows, std::vector<double>(cols));
	}

	Matrix::Matrix(const std::vector<std::vector<double>>& elements)
		: rows((int)elements.size()), cols((int)elements[0].size())
	{
		this->elements = elements;
	}

	// Calculations

	Matrix Matrix::Transposed() const
	{
		Matrix r(cols, rows);

		for (int col = 0; col < cols; col++)
		{
			for (int row = 0; row < rows; row++)
			{
				r.elements[col][row] = elements[row][col];
			}
		}

		return r;
	}

	Matrix Matrix::Foreach(double(*function)(double)) const
	{
		Matrix r(rows, cols);

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				r.elements[row][col] = (*function)(elements[row][col]);
			}
		}

		return r;
	}

	Matrix Matrix::MultiplyEntries(const Matrix& m) const
	{
		assert(rows == m.rows && cols == m.cols);

		Matrix r(rows, cols);

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				r.elements[row][col] = elements[row][col] * m.elements[row][col];
			}
		}

		return r;
	}

	// Operators

	std::vector<double>& Matrix::operator[](unsigned int row)
	{
		return elements[row];
	}

	double& Matrix::operator() (unsigned int row, unsigned int col)
	{
		return elements[row][col];
	}

	const double& Matrix::operator() (unsigned int row, unsigned int col) const
	{
		return elements[row][col];
	}

	Matrix Matrix::operator- () const
	{
		Matrix r(rows, cols);

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				r.elements[row][col] = -elements[row][col];
			}
		}

		return r;
	}

	Matrix operator* (float lhs, const Matrix& rhs)
	{
		Matrix r(rhs.rows, rhs.cols);

		for (int row = 0; row < rhs.rows; row++)
		{
			for (int col = 0; col < rhs.cols; col++)
			{
				r.elements[row][col] = lhs * rhs.elements[row][col];
			}
		}

		return r;
	}

	// Arithmetic operators

	Matrix Matrix::operator+ (const Matrix& rhs) const
	{
		assert(rows == rhs.rows && cols == rhs.cols);

		Matrix r(rows, cols);

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				r.elements[row][col] = elements[row][col] + rhs.elements[row][col];
			}
		}

		return r;
	}

	Matrix Matrix::operator- (const Matrix& rhs) const
	{
		assert(rows == rhs.rows && cols == rhs.cols);

		Matrix r(rows, cols);

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				r.elements[row][col] = elements[row][col] - rhs.elements[row][col];
			}
		}

		return r;
	}

	Matrix Matrix::operator* (const Matrix& rhs) const
	{
		assert(cols == rhs.rows);

		Matrix r(rows, rhs.cols);

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < rhs.cols; col++)
			{
				double sum = 0.0f;

				for (int i = 0; i < cols; i++)
				{
					sum += elements[row][i] * rhs.elements[i][col];
				}

				r.elements[row][col] = sum;
			}
		}

		return r;
	}

	Matrix Matrix::operator* (double rhs) const
	{
		Matrix r(rows, cols);

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				r.elements[row][col] = elements[row][col] * rhs;
			}
		}

		return r;
	}

	Matrix Matrix::operator/ (double rhs) const
	{
		Matrix r(rows, cols);

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				r.elements[row][col] = elements[row][col] / rhs;
			}
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
		return elements == rhs.elements;
	}

	bool Matrix::operator!= (const Matrix& rhs) const
	{
		return elements != rhs.elements;
	}
}
