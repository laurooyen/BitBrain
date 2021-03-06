// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#pragma once

#include "../Containers/Array2D.h"

#include <vector>

namespace BB
{
	/// Class representing a NxM matrix in a row-major format.

	class Matrix
	{
	private:

		Array2D<double> mElements;

	public:

		// Constructors

		Matrix();
		Matrix(int rows, int cols);
		Matrix(const std::vector<double>& row);

		// Getters

		int Rows() const;
		int Cols() const;
		int Size() const;

		Array2D<double>& Elements();

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

		/// Fills the entire matrix with a single value.
		void Fill(double value);

		// Operators

		double& operator() (unsigned int index);
		const double& operator() (unsigned int index) const;

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

	private:

		template<typename Archive>
		friend void Serialize(Archive&, Matrix&, unsigned int);
	};
}
