// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include <vector>

#include "../Util/Math/Matrix.h"

#include "ActivationFunctions.h"
#include "CostFunctions.h"

namespace BB
{
	class MNIST;

	/// Class representing a neural network.

	class Network
	{
	public:
		
		Network();
		Network(const std::vector<int>& layers);
		
		void Init();

		void DumpSettings() const;

		Matrix FeedForward(const std::vector<double>& input);
		void BackPropagate(const std::vector<double>& output);

		void TrainEpoch(const MNIST& data, unsigned int miniBatchSize);
		double CalculateAccuracy(const MNIST& data, const char* message);
        
	public:

		double learningRate;	///< learning rate
		double lambda;			///< regularization parameter
		double mu;				///< momentum parameter

		std::vector<AF> af;
		CF cf;

	private:

		std::vector<int> mLayers;

		unsigned int L; ///< Layer count.

		std::vector<Matrix> N; ///< Neurons.
		std::vector<Matrix> W; ///< Weights.
		std::vector<Matrix> B; ///< Biases.
		
		std::vector<Matrix> Delta; ///< Matrices for 'delta rule' (dC/dZ)

		std::vector<Matrix> dW; ///< Derivatives of weights.
		std::vector<Matrix> dB; ///< Derivatives of biases.
		
		std::vector<Matrix> momentumW; ///< Momentum of weights.
		std::vector<Matrix> momentumB; ///< Momentum of biases.
		
	private:

		template<typename Archive>
		friend void Serialize(Archive&, Network&, unsigned int);
	};

	// Serialization

	template<typename Archive>
	void Serialize(Archive& archive, Network& n, unsigned int version)
	{
		archive & n.learningRate & n.lambda & n.mLayers & n.af & n.cf & n.L & n.W & n.B;
	}
}
