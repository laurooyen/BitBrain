// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "Network.h"

#include "../Utility/Common.h"

#include "../Dataset/IDataset.h"
#include "../FileIO/FileManager.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <cassert>

namespace BB
{
	double Random(double x)
	{
		return (double)(rand() % 10000 + 1) / 10000 - 0.5;
	}

	Network::Network() {}

	Network::Network(const std::vector<int>& layers)
	{
		srand((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());

		mLayers = layers;

		mEpoch = 0;

		mAccuracyTest = 0.0;
		mAccuracyTrain = 0.0;

		mCostTest = 0.0;
		mCostTrain = 0.0;

		L = (unsigned int)layers.size();

		W = std::vector<Matrix>(L - 1);
		B = std::vector<Matrix>(L - 1);

		for (unsigned int i = 0; i < L - 1; i++)
		{
			W[i] = Matrix(layers[i], layers[i + 1]);
			B[i] = Matrix(1, layers[i + 1]);
			
			W[i] = W[i].Foreach(Random);
			B[i] = B[i].Foreach(Random);
		}
	}

	void Network::Init()
	{
		assert(L - 1 == af.size());

		A = std::vector<Matrix>(L);

		dW = std::vector<Matrix>(L - 1);
		dB = std::vector<Matrix>(L - 1);
	}

	Matrix Network::FeedForward(const std::vector<double>& input)
	{
		A[0] = Matrix(input);

		for (unsigned int i = 1; i < L; i++)
		{
			A[i] = GCalculateAF[(int)af[i - 1]](A[i - 1] * W[i - 1] + B[i - 1]);
		}

		return A[L - 1];
	}
	
	void Network::BackPropagate(const std::vector<double>& target)
	{
		Matrix dCdO = GDeriveCF[(int)cf](A[L - 1], Matrix(target));

		// Calculate derivatives for biases.

		dB[L - 2] = dCdO * (GDeriveAF[(int)af[L - 2]](A[L - 2] * W[L - 2] + B[L - 2]));

		for (int i = L - 3; i >= 0; i--)
		{
			dB[i] = (dB[i + 1] * W[i + 1].Transposed()) * (GDeriveAF[(int)af[i]](A[i] * W[i] + B[i]));
		}

		// Calculate derivatives for weights.

		for (unsigned int i = 0; i < L - 1; i++)
		{
			dW[i] = A[i].Transposed() * dB[i] + W[i] * lambda;
		}
	}

	void Network::Train(IDataset& trainData, IDataset& testData, const FileManager* fileManager)
	{
		std::cout << "Training network.\n" << std::endl;

		double previousCost = 1.0;

		for (mEpoch = 0; mEpoch < epochs; mEpoch++)
		{
			std::cout << "  Epoch #" << (mEpoch + 1) << "\n\n";

			// Train network

			TrainEpoch(trainData);

			// Test network performance

			CalculatePerformance(testData,  "    Calc Test Performance ", mAccuracyTest, mCostTest);
			CalculatePerformance(trainData, "    Calc Train Performance", mAccuracyTrain, mCostTrain);

			std::cout << "    Test Accuracy          " << mAccuracyTest << " %\n";
			std::cout << "    Train Accuracy         " << mAccuracyTrain << " %\n";
			std::cout << "    Test Cost              " << mCostTest << "\n";
			std::cout << "    Train Cost             " << mCostTrain << "\n\n";

			// Save network

			if (fileManager) fileManager->SaveNetwork(*this);

			// Batch size and learning rate scheduling

			if (previousCost < mCostTest)
			{
				batchSize *= batchSizeFactor;
				learningRate *= learningRateFactor;
				
				if (batchSize > batchSizeMax) batchSize = batchSizeMax;
				if (learningRate < learningRateMin) learningRate = learningRateMin;
				
				std::cout << "    Updated batch size:    " << batchSize << "\n";
				std::cout << "    Updated learning rate: " << learningRate << "\n\n";
			}

			previousCost = mCostTest;
		}

		std::cout << "Finished training network.\n" << std::endl;
	}

	void Network::TrainEpoch(IDataset& data)
	{
		data.Shuffle();
		
		std::vector<Matrix> wChange = std::vector<Matrix>(W.size());
		std::vector<Matrix> bChange = std::vector<Matrix>(B.size());
		
		for (unsigned int i = 0; i < L - 1; i++)
		{
			wChange[i] = Matrix(W[i].Rows(), W[i].Cols());
			bChange[i] = Matrix(B[i].Rows(), B[i].Cols());
		}

		for (unsigned int i = 0; i < data.Size(); i++)
		{
			ProgressBar("    Training Network      ", i + 1, data.Size());

			std::vector<double> target(mLayers.back(), 0.0);
			target[data.GetLabel(i)] = 1.0;

			FeedForward(data.GetData(i));
			BackPropagate(target);
			
			// Update batch change average.
			
			for (unsigned int j = 0; j < L - 1; j++)
			{
				wChange[j] += dW[j];
				bChange[j] += dB[j];
				
				// Execute gradient descent when batch finished.

				if(i % batchSize == batchSize - 1)
				{
					W[j] -= wChange[j] * learningRate;
					B[j] -= bChange[j] * learningRate;
					
					wChange[j].Fill(0);
					bChange[j].Fill(0);
				}
			}
		}

		std::cout << std::endl;
	}
	
	void Network::CalculatePerformance(IDataset& data, const char* message, double& accuracy, double& cost)
	{
		unsigned int correct = 0;

		double totalCost = 0.0;

		for (unsigned int i = 0; i < data.Size(); i++)
		{
			ProgressBar(message, i + 1, data.Size());

			Matrix m = FeedForward(data.GetData(i));

			int result = (int)(std::max_element(m.Elements().begin(), m.Elements().end()) - m.Elements().begin());
			if (result == data.GetLabel(i)) correct++;

			std::vector<double> target(mLayers.back(), 0.0);
			target[data.GetLabel(i)] = 1.0;

			totalCost += GCalculateCF[(int)cf](m, target);
		}

		std::cout << std::endl;

		accuracy =  ((double)correct / (double)data.Size()) * 100.0;
		cost = (totalCost / (double)data.Size());
	}
}
