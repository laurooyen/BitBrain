// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include <vector>

#include "../Util/Math/Matrix.h"

#include "ActivationFunctions.h"
#include "CostFunctions.h"

namespace BB
{
	/// Class representing a neural network.

	class Network
	{
	public:

		Network(const std::vector<int>& layers, const std::vector<AF>& af, CF cf, double learningRate, double lambda);

		Matrix Compute(const std::vector<double>& input);
		void Learn(const std::vector<double>& output);

	private:

		int mLayerCount;
		double mLearningRate;
		double mLambda;

		std::vector<AF> mAF;
		CF mCF;

		std::vector<Matrix> N; ///< Neurons
		std::vector<Matrix> W; ///< Weights
		std::vector<Matrix> B; ///< Biases

		std::vector<Matrix> dW; ///< Derivatives of weights
		std::vector<Matrix> dB; ///< Derivatives of biases
	};
}
