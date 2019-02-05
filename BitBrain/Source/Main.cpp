// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "MNIST/MNIST.h"
#include "AI/Network.h"

#include <iostream>

using namespace BB;

int main()
{
	// GLOBAL SETTINGS

	int epochs = 10;
	int miniBatchSize = 10;

	Network network
	(
		{ 784, 100, 60, 10 },					// Layer count
		{ AF::ReLU, AF::ReLU, AF::Softmax },	// Activation functions
		CF::CrossEntropy,						// Cost function
		0.003,									// Learning rate
		0.0012									// Regularization lambda
	);

	// LOAD DATA

	std::cout << "Loading data.\n" << std::endl;

	MNIST trainData("Resource/MNIST/TrainingImages-200k.bin", "Resource/MNIST/TrainingLabels-200k.bin");
	MNIST testData("Resource/MNIST/TestingImages.bin", "Resource/MNIST/TestingLabels.bin");

	// TRAINING LOOP

	std::cout << "Training network.\n" << std::endl;
	
	for(int i = 0; i < epochs; i++)
	{
		std::cout << "  Epoch #" << (i + 1) << "\n\n";

		// TRAIN NETWORK
		
		network.TrainEpoch(trainData, miniBatchSize);
		
		std::cout << std::endl;
		
		// GET ACCURACY
		
		double accuracyTest = network.CalculateAccuracy(testData, "    Calc Test Accuracy  ");
		double accuracyTrain = network.CalculateAccuracy(trainData, "    Calc Train accuracy ");

		std::cout << "    Test Accuracy        " << accuracyTest << " %\n";
		std::cout << "    Train Accuracy       " << accuracyTrain << " %\n";
		
		std::cout << std::endl;
	}

	// WAIT TO CLOSE PROGRAM

	system("PAUSE");
}
