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

	// Implementations of the Activation Functions.

	static Matrix Sigmoid(const Matrix& m)
	{
		return m.Foreach([](double x) {
			return 1.0f / (1.0f + exp(-x));
		});
	}

	static Matrix DeriveSigmoid(const Matrix& m)
	{
		Matrix s = Sigmoid(m);
		Matrix r(m.Cols(), m.Cols());

		for (int diagonal = 0; diagonal < r.Cols(); diagonal++)
		{
			r(diagonal, diagonal) = s(0, diagonal) * (1 - s(0, diagonal));
		}

		return r;
	}

	Matrix Softmax(const Matrix& m)
	{
		Matrix r = m;

		// Make inputs smaller so exponential doesn't explode out of bounds
		for (int i = 0; i < r.Cols(); i++)
		{
			r(0, i) = exp(r(0, i) - m.LargestElement());
		}

		r = r / r.TotalSum();

		return r;
	}

	Matrix DeriveSoftmax(const Matrix& m)
	{
		Matrix s = Softmax(m);
		Matrix r(m.Cols(), m.Cols());

		for (int row = 0; row < r.Rows(); row++)
		{
			for (int col = 0; col < r.Cols(); col++)
			{
				r(row, col) = s(0, row) * ((row == col ? 1.0 : 0.0) - s(0, col));
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
		Matrix r(m.Cols(), m.Cols());

		for (int diagonal = 0; diagonal < r.Cols(); diagonal++)
		{
			r(diagonal, diagonal) = (m(0, diagonal) > 0) ? 1.0 : 0.0;
		}

		return r;
	}

	Matrix LeakyReLU(const Matrix& m)
	{
		return m.Foreach([](double x) {
			return (x > 0) ? x : 0.1 * x;
		});
	}

	Matrix DeriveLeakyReLU(const Matrix& m)
	{
		Matrix r(m.Cols(), m.Cols());

		for (int diagonal = 0; diagonal < r.Cols(); diagonal++)
		{
			r(diagonal, diagonal) = (m(0, diagonal) > 0) ? 1.0 : 0.1;
		}

		return r;
	}

	// Internal details.
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

	const char* ToString(const AF& af)
	{
		switch (af)
		{
		case AF::Sigmoid:	return "Sigmoid";
		case AF::Softmax:	return "Softmax";
		case AF::ReLU:		return "ReLU";
		case AF::LeakyReLU:	return "Leaky ReLU";
		default:			return "Unknown";
		}
	}
}
