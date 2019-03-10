// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "AI/Network.h"
#include "FileIO/Dataset.h"
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
	
	std::vector<DatasetSymbol> symbols =
	{
		{ "0", "D0.bin" }, { "1", "D1.bin" }, { "2", "D2.bin" }, { "3", "D3.bin" }, { "4", "D4.bin" },
		{ "5", "D5.bin" }, { "6", "D6.bin" }, { "7", "D7.bin" }, { "8", "D8.bin" }, { "9", "D9.bin" },
	};

	Dataset trainData("Resource/Dataset/Training", symbols, 6000);
	Dataset testData("Resource/Dataset/Testing", symbols, 6000);

	// TRAIN NETWORK

	network.Init();
	network.Train(trainData, testData, &fileManager);

	// WAIT FOR USER TO CLOSE APP

	system("PAUSE");
}
