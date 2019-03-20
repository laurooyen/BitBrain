// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "AI/Network.h"
#include "Dataset/DatasetSymbols.h"
#include "FileIO/FileManager.h"

#include <iostream>

#include "Dataset/MNIST.h"

using namespace BB;

int main()
{
	// FILE MANAGER SETTINGS

	FileManager fileManager("Resource/Networks");

	// LOAD TRAINING AND TESTING DATA

	std::vector<const char*> symbols =
	{
		// Digits 0-9 get loaded using the AppendMNIST() function below.
		"ADD.bin", "SUB.bin", "MUL.bin", "SLASH.bin"
	};

	DatasetSymbols trainData("Resource/Dataset/Training", symbols, 20000);
	trainData.AppendMNIST("Resource/MNIST/TrainingImages-200k.bin", "Resource/MNIST/TrainingLabels-200k.bin");

	DatasetSymbols testData("Resource/Dataset/Testing", symbols, 6000);
	testData.AppendMNIST("Resource/MNIST/TestingImages.bin", "Resource/MNIST/TestingLabels.bin");

	// TRAIN NETWORKS

	// IMPORTANT NOTICE !!!
	// Duplicate the code block below to train multiple networks at once.
	// It is important that the surrounding scope {} gets duplicated as well.
	// Don't forget to give the network a UNIQUE name in the SetNetworkName() function.

	{
		// Network name

		fileManager.SetNetworkName("NET01");

		// Network settings

		Network network({ 784, 100, 50, 14 });

		network.epochs = 50;

		network.af = { AF::ReLU, AF::ReLU, AF::Softmax };
		network.cf = CF::CrossEntropy;

		network.batchSize = 1;
		network.batchSizeFactor = 2;
		network.batchSizeMax = 10000;

		network.learningRate = 0.005;
		network.learningRateFactor = 0.5;
		network.learningRateMin = 0.00000001;

		network.lambda = 0.0005;

		// Train network

		network.Init();
		network.Train(trainData, testData, &fileManager);

		// Save CSV files

		fileManager.SaveNetworkCSV();
	}

	// WAIT FOR USER TO CLOSE APP

	system("PAUSE");
}
