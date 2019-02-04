// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include <vector>

#include "../Util/Math/Matrix.h"
#include "../MNIST/MNIST.h"

#include "ActivationFunctions.h"
#include "CostFunctions.h"

namespace BB
{
	/// Class representing a neural network.

	class Network
	{
	public:
		Network(const std::vector<int>& layers, const std::vector<AF>& af, CF cf, double learningRate, double lambda);
		Matrix FeedForward(const std::vector<double>& input);
        void TrainEpoch(BB::MNIST trainData, int miniBatchSize);
        double testAccuracy(BB::MNIST testData, int testAmt);
        
	private:
        void BackPropagate(const std::vector<double>& output);
        
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
