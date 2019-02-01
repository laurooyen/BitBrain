// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include <cmath>
#include <time.h>
#include <iostream>

#include "MNIST/MNIST.h"
#include "AI/Network.h"

using namespace BB;

// --------------------------------
// GLOBAL VARIABLES
// --------------------------------

int GEpochs = 20;

// --------------------------------
// FUNCTIONS
// --------------------------------

int GetClassification(const std::vector<double>& v)
{
	double max = 0.0f;
	double index = 0;

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] > max)
		{
			max = v[i];
			index = i;
		}
	}

	return index;
}

// --------------------------------
// MAIN FUNCTION
// --------------------------------

int main()
{
	// Load Data.
	std::cout << "Loading data.\n" << std::endl;

	MNIST trainData("Resource/MNIST/TrainingImages.bin", "Resource/MNIST/TrainingLabels.bin");
	MNIST testData("Resource/MNIST/TestingImages.bin", "Resource/MNIST/TestingLabels.bin");

	// Init network.
	Network network
	(
		{ 784, 75, 10 },			// Layer count
		{ AF::ReLU, AF::Softmax },	// Activation functions
		1,							// Cost function ID (0: euclid. dist., 1: multiclass cross-entropy) (yeah sure its an int, im too lazy. And who cares about readable code, right?)
		0.01f,						// Learning rate
		0.0005						// Regularization param
	);

	// Train network.
	std::cout << "Training network:\n" << std::endl;;

	for (int i = 0; i < GEpochs; i++)
	{
		std::cout << "  Epoch #" << i << "\n";

		for (int j = 0; j < trainData.Size(); j++)
		{
			if (j % 6000 == 0) std::cout << "    Sample #" << j << "\n";

			std::vector<double> out(10, 0.0f);
			out[trainData.GetLabel(j)] = 1.0f;

			network.Compute(trainData.GetImage(j));
			network.Learn(out);
		}

		std::cout << std::endl;

		// Test network.
		std::cout << "Testing network:\n" << std::endl;

		int correct = 0;

		for (int i = 0; i < testData.Size(); i++)
		{
			if (i % 1000 == 0) std::cout << "  Sample #" << i << "\n";

			Matrix m = network.Compute(testData.GetImage(i));
			int result = GetClassification(m.elements[0]);

			if (result == testData.GetLabel(i)) correct++;
		}

		std::cout << std::endl;

		// Print accuracy.
		double accuracy = ((double)correct / (double)testData.Size()) * 100.0f;
		std::cout << "Accuracy: " << accuracy << "%\n" << std::endl;

	}

	// Wait to close program.
	system("PAUSE");
}