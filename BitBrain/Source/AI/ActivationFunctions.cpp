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
		return m.Foreach([](double x) {
			double s = 1.0f / (1.0f + exp(-x));
			return s * (1.0f - s);
		});
	}

	Matrix Softmax(const Matrix& m)
	{
		// TODO(Jonathan): Implement this.
		return Matrix();
	}

	Matrix DeriveSoftmax(const Matrix& m)
	{
		// TODO(Jonathan): Implement this.
		return Matrix();
	}

	Matrix ReLU(const Matrix& m)
	{
		return m.Foreach([](double x) {
			return Max(0.0, x);
		});
	}

	Matrix DeriveReLU(const Matrix& m)
	{
		return m.Foreach([](double x) {
			return (x > 0) ? 1.0 : 0.0;
		});
	}

	// INTERNAL DETAILS

	// The order should match the AF enum class order.

	const ActivationFunction GCalculateAF[] =
	{
		Sigmoid,
		Softmax,
		ReLU
	};

	const ActivationFunction GDeriveAF[] =
	{
		DeriveSigmoid,
		DeriveSoftmax,
		DeriveReLU
	};
}
