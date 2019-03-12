// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "AI/Network.h"
#include "FileIO/Dataset.h"
#include "FileIO/FileManager.h"

using namespace BB;

int main()
{
	// NETWORK SETTINGS

	Network net02({ 784, 15, 10 });

	net02.epochs = 50;

	net02.af = { AF::Sigmoid, AF::Sigmoid };
	net02.cf = CF::MeanSquaredError;

	net02.batchSize = 1;
	net02.batchSizeFactor = 1;
	net02.batchSizeMax = 1;

	net02.learningRate = 0.75;
	net02.learningRateFactor = 1.0;
	net02.learningRateMin = 0.75;

	net02.lambda = 0.0;
	net02.mu = 0.0;

	// FILE MANAGER SETTINGS

	FileManager fileManager("Resource/Networks");

	// UNCOMMENT TO CREATE CSV FILES
	// fileManager.SaveNetworkCSV();

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

	net02.Init();
	net02.Train(trainData, testData, &fileManager);

	// WAIT FOR USER TO CLOSE APP

	system("PAUSE");
}
