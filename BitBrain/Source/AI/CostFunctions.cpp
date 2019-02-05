// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "CostFunctions.h"

namespace BB
{
	// Implementations of the Cost Functions.

	Matrix EuclideanDistance(const Matrix& Y, const Matrix& T)
	{
		return (Y - T);
	}

	Matrix CrossEntropy(const Matrix& Y, const Matrix& T)
	{
		Matrix dCdO = -T;

		for (int i = 0; i < dCdO.Cols(); i++)
		{
			dCdO(0, i) /= Y(0, i);
		}

		return dCdO;
	}

	// Internal details.
	// The order should match the CF enum class order.

	const CostFunction GCalculateCF[] =
	{
		EuclideanDistance,
		CrossEntropy
	};

	const char* ToString(const CF& cf)
	{
		switch (cf)
		{
		case CF::EuclideanDistance:	return "Euclidean Distance";
		case CF::CrossEntropy:		return "Cross Entropy";
		default:					return "Unknown";
		}
	}
}
