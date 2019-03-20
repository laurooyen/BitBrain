// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "AI/Network.h"
#include "Dataset/DatasetSymbols.h"
#include "FileIO/FileManager.h"

using namespace BB;

int main()
{
	// NETWORK SETTINGS

	Network network({ 784, 15, 10 });

	network.epochs = 10;

	network.af = { AF::Sigmoid, AF::Sigmoid };
	network.cf = CF::MeanSquaredError;

	network.batchSize = 1;
	network.batchSizeFactor = 1;
	network.batchSizeMax = 1;

	network.learningRate = 0.75;
	network.learningRateFactor = 1.0;
	network.learningRateMin = 0.75;

	network.lambda = 0.0;

	// FILE MANAGER SETTINGS

	FileManager fileManager("Resource/Networks");

	fileManager.RequestNetworkName();

	// LOAD TRAINING AND TESTING DATA

	DatasetSymbols trainData;
	trainData.AppendMNIST("Resource/MNIST/TrainingImages.bin", "Resource/MNIST/TrainingLabels.bin");
	trainData.FinishDataset();

	DatasetSymbols testData;
	testData.AppendMNIST("Resource/MNIST/TestingImages.bin", "Resource/MNIST/TestingLabels.bin");
	testData.FinishDataset();

	// TRAIN NETWORK

	network.Init();
	network.Train(trainData, testData, &fileManager);

	// WAIT FOR USER TO CLOSE APP

	system("PAUSE");
}
