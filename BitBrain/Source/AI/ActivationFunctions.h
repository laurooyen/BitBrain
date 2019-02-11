// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include "../Util/Math/Matrix.h"

namespace BB
{
	enum class AF
	{
		Sigmoid,
		Softmax,
		ReLU,
		LeakyReLU // TODO(Jonathan): Test this (not sure if it works well).
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
