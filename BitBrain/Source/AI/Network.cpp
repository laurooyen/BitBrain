// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "Network.h"

#include <cmath>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

#include <iostream> //TEST voor COUT

namespace BB
{
	double Random(double x)
	{
		return (double)(rand() % 10000 + 1) / 10000 - 0.5;
	}

	Network::Network(const std::vector<int>& layers, const std::vector<AF>& af, CF cf, double learningRate, double lambda)
	{
		srand((unsigned int)time(NULL));

		mLayerCount = (int)layers.size();
		mLearningRate = learningRate;
		mLambda = lambda;
		mAF = af;
		mCF = cf;

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

	Matrix Network::FeedForward(const std::vector<double>& input)
	{
		N[0] = Matrix(input);

		for (int i = 1; i < mLayerCount; i++)
		{
			N[i] = GCalculateAF[(int)mAF[i - 1]](N[i - 1] * W[i - 1] + B[i - 1]);
		}

		return N[mLayerCount - 1];
	}
    
    void Network::TrainEpoch(BB::MNIST trainData, int miniBatchSize)
	{

        std::cout << "Training network:\n" << std::endl;
        
        std::vector<unsigned int> shuffle(trainData.Size());
        std::iota(shuffle.begin(), shuffle.end(), 0);
        
        unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
        
        std::default_random_engine rng(seed);
        
        std::cout << " Train Epoch" << "\n\n";
        
        std::shuffle(shuffle.begin(), shuffle.end(), rng);
        
        std::vector<Matrix> wChange = std::vector<Matrix>(W.size());
        std::vector<Matrix> bChange = std::vector<Matrix>(B.size());
        
        for (int i = 0; i < mLayerCount - 1; i++)
        {
            wChange[i] = Matrix(W[i].Rows(), W[i].Cols());
            bChange[i] = Matrix(B[i].Rows(), B[i].Cols());
        }
        
        // TRAIN NETWORK
        for (int j = 0; j < trainData.Size(); j++)
        {
            
            std::vector<double> out(10, 0.0f);
            out[trainData.GetLabel(shuffle[j])] = 1.0f;
            
            FeedForward(trainData.GetImage(shuffle[j]));
            
            BackPropagate(out);
            
            // Update minibatch change average and if batch completed update the weights and biases.
            
            for (int i = 0; i < mLayerCount - 1; i++)
            {
                wChange[i] += dW[i];
                bChange[i] += dB[i];
                
                // If batch finished do gradient descent
                if(j % miniBatchSize == miniBatchSize - 1)
                {
                    W[i] -= wChange[i] * mLearningRate;
                    B[i] -= bChange[i] * mLearningRate;
                    
                    wChange[i] *= 0; //EIKES VIES PLS OPTIMIZE ik was te lui om te bedenken hoe ik de matrix deftig reset naar 0
                    bChange[i] *= 0; // ''
                }
            }
            if(j % (miniBatchSize*1000) == 0) std::cout << "batch " << (j/miniBatchSize) << "/" << trainData.Size()/miniBatchSize << "\n";

        }
    }
    
    double Network::testAccuracy(BB::MNIST testData, int testAmt) { printf("not implemented yet"); return 0.0; }

    
    
    void Network::BackPropagate(const std::vector<double>& output)
    {
        Matrix dCdO = GCalculateCF[(int)mCF](N[mLayerCount - 1], Matrix(output));
        
        // Calculate derivatives for biases.
        
        dB[mLayerCount - 2] = dCdO * (GDeriveAF[(int)mAF[mLayerCount - 2]](N[mLayerCount - 2] * W[mLayerCount - 2] + B[mLayerCount - 2]));
        
        for (int i = mLayerCount - 3; i >= 0; i--)
        {
            dB[i] = (dB[i + 1] * W[i + 1].Transposed()) * (GDeriveAF[(int)mAF[i]](N[i] * W[i] + B[i]));
        }
        
        // Calculate derivatives for weights.
        
        for (int i = 0; i < mLayerCount - 1; i++)
        {
            dW[i] = N[i].Transposed() * dB[i] + W[i] * mLambda; // + W * lambda = L2 regularization
        }
    }
}
