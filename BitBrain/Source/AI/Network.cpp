// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "Network.h"

#include <cmath>
#include <time.h>

namespace BB
{
	double Random(double x)
	{
		return (double)(rand() % 10000 + 1) / 10000 - 0.5;
	}

	Network::Network(const std::vector<int>& layers, const std::vector<AF>& af, double learningRate)
	{
		srand(time(NULL));

		mLayerCount = layers.size();
		mLearningRate = learningRate;

		mAF = af;

		// TODO(Lauro): assert(layers.size() == af.size() + 1);

		N = std::vector<Matrix>(mLayerCount);
		W = std::vector<Matrix>(mLayerCount - 1);
		B = std::vector<Matrix>(mLayerCount - 1);

		dW = std::vector<Matrix>(mLayerCount - 1);
		dB = std::vector<Matrix>(mLayerCount - 1);

		for (int i = 0; i < mLayerCount - 1; i++)
		{
			W[i] = Matrix(layers[i], layers[i + 1]);
			B[i] = Matrix(1, layers[i + 1]);

			W[i] = W[i].Foreach(Random);
			B[i] = B[i].Foreach(Random);
		}
	}

	Matrix Network::Compute(const std::vector<double>& input)
	{
		N[0] = Matrix({ input });

		for (int i = 1; i < mLayerCount; i++)
		{
			N[i] = GCalculateAF[(int)mAF[i - 1]](N[i - 1] * W[i - 1] + B[i - 1]);
		}

		return N[mLayerCount - 1];
	}

	void Network::Learn(const std::vector<double>& output)
	{
		Matrix Y({ output });

		// Calculate derivatives for biases.

		dB[mLayerCount - 2] = (N[mLayerCount - 1] - Y).MultiplyEntries(GDeriveAF[(int)mAF[mLayerCount - 2]](N[mLayerCount - 2] * W[mLayerCount - 2] + B[mLayerCount - 2]));

		for (int i = mLayerCount - 3; i >= 0; i--)
		{
			dB[i] = (dB[i + 1] * W[i + 1].Transposed()).MultiplyEntries(GDeriveAF[(int)mAF[i]](N[i] * W[i] + B[i]));
		}

		// Calculate derivatives for weights.

		for (int i = 0; i < mLayerCount - 1; i++)
		{
			dW[i] = N[i].Transposed() * dB[i];
		}

		// Change the weights and biases.

		for (int i = 0; i < mLayerCount - 1; i++)
		{
			W[i] -= dW[i] * mLearningRate;
			B[i] -= dB[i] * mLearningRate;
		}
	}
}
