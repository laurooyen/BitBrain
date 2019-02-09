// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "Network.h"

#include "../MNIST/MNIST.h"

#include "../Util/Common.h"

#include <cmath>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <iostream>

#include <iostream>

namespace BB
{
	static unsigned int GSeed;
	std::default_random_engine GRandom;

	double Random(double x)
	{
		return (double)(rand() % 10000 + 1) / 10000 - 0.5;
	}

	Network::Network() {}

	Network::Network(const std::vector<int>& layers)
	{
		GSeed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

		srand(GSeed);
		GRandom.seed(GSeed);

		mLayers = layers;

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
		GSeed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

		srand(GSeed);
		GRandom.seed(GSeed);

		N = std::vector<Matrix>(L);

		dW = std::vector<Matrix>(L - 1);
		dB = std::vector<Matrix>(L - 1);
		
		Delta = std::vector<Matrix>(L - 1);
		
		momentumW = std::vector<Matrix>(L - 1);
		momentumB = std::vector<Matrix>(L - 1);
		
		for(unsigned int i = 0; i < L - 1; i++)
		{
			momentumW[i] = Matrix(W[i].Rows(), W[i].Cols());
			momentumB[i] = Matrix(B[i].Rows(), B[i].Cols());
		}
	}

	void Network::DumpSettings() const
	{
		std::cout << "  Learning Rate:         " << learningRate << "\n";

		std::cout << "  Regularization Lambda: " << lambda << "\n";

		std::cout << "  Layers:                { ";
		for (int i = 0; i < mLayers.size(); i++)
		{
			if (i != 0) std::cout << ", ";
			std::cout << mLayers[i];
		}
		std::cout << " }\n";

		std::cout << "  Activation Functions:  { ";
		for (int i = 0; i < af.size(); i++)
		{
			if (i != 0) std::cout << ", ";
			std::cout << ToString(af[i]);
		}
		std::cout << " }\n";

		std::cout << "  Cost Function:         " << ToString(cf) << "\n";
	}

	Matrix Network::FeedForward(const std::vector<double>& input)
	{
		N[0] = Matrix(input);

		for (unsigned int i = 1; i < L; i++)
		{
			N[i] = GCalculateAF[(int)af[i - 1]](N[i - 1] * W[i - 1] + B[i - 1]);
		}

		return N[L - 1];
	}
	
	void Network::BackPropagate(const std::vector<double>& output)
	{
		std::cout << "backprop";
		Matrix dCdO = GCalculateCF[(int)cf](N[L - 1], Matrix(output));

		// Calculate 'delta rule'

		Delta[L - 2] = dCdO * (GDeriveAF[(int)af[L - 2]](N[L - 2] * W[L - 2] + B[L - 2]));

		for (int i = L - 3; i >= 0; i--)
		{
			Delta[i] = (Delta[i + 1] * W[i + 1].Transposed()) * (GDeriveAF[(int)af[i]](N[i] * W[i] + B[i]));
		}

		// Calculate derivatives of the cost w.r.t. weights and biases

		for (unsigned int i = 0; i < L - 1; i++)
		{
			dB[i] = Delta[i] + momentumB[i];
			dW[i] = N[i].Transposed() * Delta[i] + W[i] * lambda + momentumW[i]; // + W * lambda = L2 regularization.
			
			momentumB[i] = (momentumB[i] + dB[i]) * mu;
			momentumW[i] = (momentumW[i] + dW[i]) * mu;
		}
	}

	void Network::TrainEpoch(const MNIST& data, unsigned int miniBatchSize)
	{
		std::vector<unsigned int> shuffle(data.Size());
		std::iota(shuffle.begin(), shuffle.end(), 0);
		std::shuffle(shuffle.begin(), shuffle.end(), GRandom);
		
		std::vector<Matrix> wChange = std::vector<Matrix>(W.size());
		std::vector<Matrix> bChange = std::vector<Matrix>(B.size());
		
		for (unsigned int i = 0; i < L - 1; i++)
		{
			wChange[i] = Matrix(W[i].Rows(), W[i].Cols());
			bChange[i] = Matrix(B[i].Rows(), B[i].Cols());
		}

		for (unsigned int j = 0; j < data.Size(); j++)
		{
			std::vector<double> out(10, 0.0f);
			out[data.GetLabel(shuffle[j])] = 1.0f;
			
			ProgressBar("    Training Network    ", j + 1, data.Size());

			FeedForward(data.GetImage(shuffle[j]));
			BackPropagate(out);
			
			// Update minibatch change average.
			
			for (unsigned int i = 0; i < L - 1; i++)
			{
				wChange[i] += dW[i];
				bChange[i] += dB[i];
				
				// Execute gradient descent when batch finished.

				if(j % miniBatchSize == miniBatchSize - 1)
				{
					W[i] -= wChange[i] * learningRate;
					B[i] -= bChange[i] * learningRate;
					
					wChange[i].Fill(0);
					bChange[i].Fill(0);
				}
			}
		}
	}
	
	double Network::CalculateAccuracy(const MNIST& data, const char* message)
	{
		unsigned int correct = 0;

		for (unsigned int i = 0; i < data.Size(); i++)
		{
			ProgressBar(message, i, data.Size());

			Matrix matrix = FeedForward(data.GetImage(i));
			int resultTest = (int)(std::max_element(matrix.Elements().begin(), matrix.Elements().end()) - matrix.Elements().begin());
			if (resultTest == data.GetLabel(i)) correct++;
		}

		std::cout << std::endl;

		return ((double)correct / (double)data.Size()) * 100.0;
	}
}
