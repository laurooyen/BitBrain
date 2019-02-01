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

		// Operators

		std::vector<double>& operator[] (unsigned int row);

		double& operator() (unsigned int row, unsigned int col);
		const double& operator() (unsigned int row, unsigned int col) const;

		Matrix operator- () const;
		friend Matrix operator* (float lhs, const Matrix& rhs);

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

		// Relational operators

		bool operator== (const Matrix& rhs) const;
		bool operator!= (const Matrix& rhs) const;
	};
}