// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/Math/Matrix.h"

namespace BB
{
	/// Activation Functions for a network.

	enum class AF
	{
		Sigmoid,
		Softmax,
		ReLU,
		LeakyReLU
	};

	static Matrix Sigmoid(const Matrix& m);
	static Matrix DeriveSigmoid(const Matrix& m);

	static Matrix Softmax(const Matrix& m);
	static Matrix DeriveSoftmax(const Matrix& m);

	static Matrix ReLU(const Matrix& m);
	static Matrix DeriveReLU(const Matrix& m);

	static Matrix LeakyReLU(const Matrix& m);
	static Matrix DeriveLeakyReLU(const Matrix& m);

	// Internal details

	typedef Matrix(*ActivationFunction)(const Matrix& m);

	extern const ActivationFunction GCalculateAF[];
	extern const ActivationFunction GDeriveAF[];

	const char* ToString(const AF& af);
}
