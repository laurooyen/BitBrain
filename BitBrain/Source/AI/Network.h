// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include <vector>

#include "../Util/Math/Matrix.h"

#include "ActivationFunctions.h"
#include "CostFunctions.h"

namespace BB
{
	class MNIST;
	class FileManager;

	/// Class representing a neural network.

	class Network
	{
	public:
		
		// Constructors

		/// Creates a new empty network.
		/// Useful when loading serialized networks.
		Network();

		/// Creates a new network.
		/// @param layers The neuron count of every layer.
		Network(const std::vector<int>& layers);
		
		/// Sets the networks internal state.
		/// This function should be called before using the network.
		void Init();

		// Calculations

		/// Feed Forward.
		/// @param input The networks input vector.
		Matrix FeedForward(const std::vector<double>& input);

		/// Back Propagate.
		/// @param output The expected networks output vector.
		void BackPropagate(const std::vector<double>& output);

		/// Trains the network.
		/// @param trainData The data to train the network with.
		/// @param testData The data to test the network with.
		/// @param fileManager The filemanager to save the network with.
		void Train(const MNIST& trainData, const MNIST& testData, const FileManager* fileManager = nullptr);

		/// Trains a single epoch.
		/// @param data The data to train the network with.
		void TrainEpoch(const MNIST& data);

		/// @param data The data to test the network with.
		/// @param message The message that should appear in front of the ProgressBar.
		double CalculateAccuracy(const MNIST& data, const char* message);

		// Getters

		const std::vector<int>& Layers() const { return mLayers; }

		unsigned int Epoch() const { return mEpoch; }

		double AccuracyTest() const { return mAccuracyTest; }
		double AccuracyTrain() const { return mAccuracyTrain; }
        
	public:
		
		// Public network settings

		unsigned int epochs;			///< Number of epochs.

		unsigned int batchSize;			///< Mini batch size.
		unsigned int batchSizeFactor;	///< Mini batch size schedule factor.
		unsigned int batchSizeMax;		///< Maximum mini batch size.

		double learningRate;			///< Learning rate.
		double learningRateFactor;		///< Learning rate schedule factor.
		double learningRateMin;			///< Minimum learning rate.

		double lambda;					///< Regularization parameter.
		double mu;						///< Momentum parameter.

		std::vector<AF> af;				///< Activation functions.
		CF cf;							///< Cost function.

	private:
		
		// Private network data

		unsigned int L;					///< Layer count.

		std::vector<Matrix> N;			///< Neurons.
		std::vector<Matrix> W;			///< Weights.
		std::vector<Matrix> B;			///< Biases.

		std::vector<Matrix> dW;			///< Derivatives of weights.
		std::vector<Matrix> dB;			///< Derivatives of biases.

		std::vector<Matrix> mW;			///< Momentum of weights.
		std::vector<Matrix> mB;			///< Momentum of biases.

	private:

		// Extra network data

		std::vector<int> mLayers;		///< Neuron count of every layer.

		unsigned int mEpoch;			///< Current epoch in network training.

		double mAccuracyTest;			///< Networks accuracy on test data.
		double mAccuracyTrain;			///< Networks accuracy on train data.

	private:

		// Serialization

		template<typename Archive>
		friend void Serialize(Archive&, Network&, unsigned int);
	};
}
