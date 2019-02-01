// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include "../Util/Math/Matrix.h"

namespace BB
{
	enum class CF
	{
		EuclideanDistance,
		CrossEntropy
	};

	static Matrix EuclideanDistance(const Matrix& Y, const Matrix& T);
	static Matrix CrossEntropy(const Matrix& Y, const Matrix& T);

	// DETAILS

	typedef Matrix(*CostFunction)(const Matrix& Y, const Matrix& T);

	extern const CostFunction GCalculateCF[];
}
