// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include "../Util/Math/Matrix.h"

namespace BB
{
	// IMPORTANT
	//
	// Follow these steps to add new Activation Functions.
	//   - Add the new item to the AF enum class below.
	//   - Create the definitions and implementations for the AF and its derivative.
	//   - Add the functions created above to the calculateAF[] and deriveAF[] arrays in the .cpp file.

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

	// DETAILS

	typedef Matrix(*ActivationFunction)(const Matrix&);

	extern const ActivationFunction GCalculateAF[];
	extern const ActivationFunction GDeriveAF[];
}
