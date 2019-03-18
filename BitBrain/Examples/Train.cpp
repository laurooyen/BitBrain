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
	network.mu = 0.0;

	// FILE MANAGER SETTINGS

	FileManager fileManager("Resource/Networks");

	fileManager.RequestNetworkName();

	// LOAD TRAINING AND TESTING DATA

	std::vector<const char*> symbols =
	{
		"D0.bin", "D1.bin", "D2.bin", "D3.bin", "D4.bin", "D5.bin", "D6.bin", "D7.bin", "D8.bin", "D9.bin"
	};

	DatasetSymbols trainData("Resource/Dataset/Training", symbols, 6000);
	DatasetSymbols testData("Resource/Dataset/Testing", symbols, 6000);

	// TRAIN NETWORK

	network.Init();
	network.Train(trainData, testData, &fileManager);

	// WAIT FOR USER TO CLOSE APP

	system("PAUSE");
}
