// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "ActivationFunctions.h"

#include <cmath>

namespace BB
{
	// TODO(Lauro): This doesn't belong here.

	/// Returns the largest of two values.
	template <typename T>
	static inline constexpr T Max(const T& a, const T& b)
	{
		return (a > b) ? a : b;
	}

	// Implementations of the Activation Functions

	static Matrix Sigmoid(const Matrix& m)
	{
		return m.Foreach([](double x) {
			return 1.0f / (1.0f + exp(-x));
		});
	}

	static Matrix DeriveSigmoid(const Matrix& m)
	{
		Matrix s = Sigmoid(m);
		Matrix r(m.cols, m.cols);

		for (int diagonal = 0; diagonal < r.cols; diagonal++)
		{
			r.elements[diagonal][diagonal] = s.elements[0][diagonal] * (1 - s.elements[0][diagonal]);
		}

		return r;
	}

	Matrix Softmax(const Matrix& m)
	{
		Matrix r = m;

		// Make inputs smaller so exponential doesn't explode out of bounds
		for (int i = 0; i < r.cols; i++)
		{
			r.elements[0][i] = exp(r.elements[0][i] - m.LargestElement());
		}

		r = r / r.TotalSum();

		return r;
	}

	Matrix DeriveSoftmax(const Matrix& m)
	{
		Matrix s = Softmax(m);
		Matrix r(m.cols, m.cols);

		for (int row = 0; row < r.rows; row++)
		{
			for (int col = 0; col < r.cols; col++)
			{
				r.elements[row][col] = s.elements[0][row] * ((row == col ? 1.0 : 0.0) - s.elements[0][col]);
			}
		}

		return r;
	}

	Matrix ReLU(const Matrix& m)
	{
		return m.Foreach([](double x) {
			return Max(0.0, x);
		});
	}

	Matrix DeriveReLU(const Matrix& m)
	{
		Matrix r(m.cols, m.cols);

		for (int diag = 0; diag < r.cols; diag++)
		{
			r.elements[diag][diag] = (m.elements[0][diag] > 0) ? 1.0 : 0.0;
		}

		return r;
	}

	Matrix LeakyReLU(const Matrix& m)
	{
		return m.Foreach([](double x) {
			return (x > 0) ? x : 0.1*x;
		});
	}

	Matrix DeriveLeakyReLU(const Matrix& m)
	{
		Matrix r(m.cols, m.cols);

		for (int diag = 0; diag < r.cols; diag++)
		{
			r.elements[diag][diag] = (m.elements[0][diag] > 0) ? 1.0 : 0.1;
		}

		return r;
	}


	// INTERNAL DETAILS

	// The order should match the AF enum class order.

	const ActivationFunction GCalculateAF[] =
	{
		Sigmoid,
		Softmax,
		ReLU,
		LeakyReLU
	};

	const ActivationFunction GDeriveAF[] =
	{
		DeriveSigmoid,
		DeriveSoftmax,
		DeriveReLU,
		DeriveLeakyReLU
	};
}
