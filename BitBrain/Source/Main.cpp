// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "MNIST/MNIST.h"
#include "AI/Network.h"
#include "Util/FileManager.h"

using namespace BB;

int main()
{
	// NETWORK SETTINGS

	Network network({ 784, 100, 60, 10 });

	network.epochs = 10;

	network.af = { AF::ReLU, AF::ReLU, AF::Softmax };
	network.cf = CF::CrossEntropy;

	network.batchSize = 1;
	network.batchSizeFactor = 2;
	network.batchSizeMax = 10000;

	network.learningRate = 0.003;
	network.learningRateFactor = 1.0;
	network.learningRateMin = 0.00000001;

	network.lambda = 0.0012;
	network.mu = 0.0;

	// FILE MANAGER SETTINGS

	FileManager fileManager("Resource/Networks");

	fileManager.RequestName();

	// LOAD SAVED NETWORK

	fileManager.LoadNetwork(network, "FOLDER/YYYYMMDD-HHMMSS-E0.bin");

	// LOAD TRAINING AND TESTING DATA
	
	MNIST trainData("Resource/MNIST/TrainingImages.bin", "Resource/MNIST/TrainingLabels.bin");
	MNIST testData("Resource/MNIST/TestingImages.bin", "Resource/MNIST/TestingLabels.bin");

	// TRAIN NETWORK

	network.Init();
	network.Train(trainData, testData, &fileManager);
}
