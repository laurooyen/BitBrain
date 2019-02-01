// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include <vector>

namespace BB
{
	/// Class representing a NxM matrix in a row-major format.

	class Matrix
	{
	public:

		int rows; ///< Number of rows.
		int cols; ///< Number of columns.

		/// Interpreted as [row][column]
		std::vector<std::vector<double>> elements;

	public:

		// Constructors

		Matrix();
		Matrix(int rows, int cols);
		Matrix(const std::vector<std::vector<double>>& elements);

		// Calculations

		/// Transpose this matrix.
		Matrix Transposed() const;

		/// Executes the given function for every matrix element.
		Matrix Foreach(double(*function)(double)) const;

		/// Calculates the entrywise product aka Hadamard product.
		Matrix MultiplyEntries(const Matrix& m) const;

		/// Calculates the total sum of all matrix elements.
		double TotalSum() const;

		/// Returns the largest element from the matrix.
		double LargestElement() const;

		// Arithmetic operators

		Matrix operator+ (const Matrix& rhs) const;
		Matrix operator- (const Matrix& rhs) const;
		Matrix operator* (const Matrix& rhs) const;

		Matrix operator* (double rhs) const;
		Matrix operator/ (double rhs) const;

		// Assignment operators

		Matrix& operator+= (const Matrix& rhs);
		Matrix& operator-= (const Matrix& rhs);
		Matrix& operator*= (const Matrix& rhs);

		Matrix& operator*= (double rhs);
		Matrix& operator/= (double rhs);
	};
}
