// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/Math/Matrix.h"

namespace BB
{
	/// Cost Functions for a neural netowrk.

	enum class CF
	{
		MeanSquaredError,
		CrossEntropy
	};

	static double MeanSquaredError(const Matrix& Y, const Matrix& T);
	static Matrix DeriveMeanSquaredError(const Matrix& Y, const Matrix& T);

	static double CrossEntropy(const Matrix& Y, const Matrix& T);
	static Matrix DeriveCrossEntropy(const Matrix& Y, const Matrix& T);

	// Internal details

	typedef double(*CostFunction)(const Matrix& Y, const Matrix& T);
	typedef Matrix(*DeriveCostFunction)(const Matrix& Y, const Matrix& T);

	extern const CostFunction GCalculateCF[];
	extern const DeriveCostFunction GDeriveCF[];

	const char* ToString(const CF& cf);
}
