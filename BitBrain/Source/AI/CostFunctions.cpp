// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "CostFunctions.h"

namespace BB
{
	// Implementations of the Cost Functions.

	double MeanSquaredError(const Matrix& Y, const Matrix& T)
	{
		return 0.5 * ((Y - T).MultiplyEntries(Y - T)).TotalSum();
	}

	Matrix DeriveMeanSquaredError(const Matrix& Y, const Matrix& T)
	{
		return (Y - T);
	}

	double CrossEntropy(const Matrix& Y, const Matrix& T)
	{
		return -1.0 * (T.MultiplyEntries(Y.Foreach(log10))).TotalSum();
	}

	Matrix DeriveCrossEntropy(const Matrix& Y, const Matrix& T)
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
		MeanSquaredError,
		CrossEntropy
	};

	const DeriveCostFunction GDeriveCF[] =
	{
		DeriveMeanSquaredError,
		DeriveCrossEntropy
	};

	const char* ToString(const CF& cf)
	{
		switch (cf)
		{
		case CF::MeanSquaredError:	return "Mean Squared Error";
		case CF::CrossEntropy:		return "Cross Entropy";
		default:					return "Unknown";
		}
	}
}
