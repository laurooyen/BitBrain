// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include <vector>

#include "../Util/Math/Matrix.h"

#include "ActivationFunctions.h"

namespace BB
{
	/// Class representing a neural network.

	class Network
	{
	public:

		Network(const std::vector<int>& layers, const std::vector<AF>& af, double learningRate);

		Matrix Compute(const std::vector<double>& input);
		void Learn(const std::vector<double>& output);

	private:

		int mLayerCount;
		double mLearningRate;

		std::vector<Matrix> N; ///< Neurons
		std::vector<Matrix> W; ///< Weights
		std::vector<Matrix> B; ///< Biases

		// TODO(Lauro): Consider removing dW and dB to save allocations.
		// These are temporary variables only used by the learn function.

		std::vector<Matrix> dW; ///< Derivatives of weights
		std::vector<Matrix> dB; ///< Derivatives of biases

		std::vector<AF> mAF;
	};
}
