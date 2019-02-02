// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include <cmath>
#include <time.h>
#include <iostream>
#include <algorithm>

#include "MNIST/MNIST.h"
#include "AI/Network.h"

using namespace BB;

void ProgressBar(const char* text, int progress, int total, int barWidth = 50, int updateFrequency = 50)
{
	if (progress % (total / updateFrequency) == 0)
	{
		float percentage = (float)progress / (float)total;

		std::cout << text << " [";

		for (int i = 0; i < barWidth; i++)
		{
			std::cout << ((i < percentage * barWidth) ? "#" : "-");
		}

		std::cout << "] " << (percentage * 100) << " %\r" << std::flush;
	}
}

int main()
{
	// Global settings.
	int epochs = 5;

	// Load Data.
	std::cout << "Loading data.\n" << std::endl;

	MNIST trainData("Resource/MNIST/TrainingImages.bin", "Resource/MNIST/TrainingLabels.bin");
	MNIST testData("Resource/MNIST/TestingImages.bin", "Resource/MNIST/TestingLabels.bin");

	// Init network.
	Network network
	(
		{ 784, 15, 10 },			// Layer count
		{ AF::ReLU, AF::Softmax },	// Activation functions
		CF::CrossEntropy,			// Cost function
		0.01,						// Learning rate
		0.0005						// Regularization lambda
	);

	// Train network.
	std::cout << "Training network.\n" << std::endl;

	for (int i = 0; i < epochs; i++)
	{
		std::cout << "  Epoch #" << (i + 1) << "\n\n";

		// Train network

		for (int j = 0; j < trainData.Size(); j++)
		{
			ProgressBar("    Training", j + 1, trainData.Size());

			std::vector<double> out(10, 0.0f);
			out[trainData.GetLabel(j)] = 1.0f;

			network.Compute(trainData.GetImage(j));
			network.Learn(out);
		}

		std::cout << std::endl;

		// Test network.

		int correct = 0;

		for (int i = 0; i < testData.Size(); i++)
		{
			ProgressBar("    Testing ", i + 1, testData.Size());

			Matrix m = network.Compute(testData.GetImage(i));
			int result = (int)(std::max_element(m[0].begin(), m[0].end()) - m[0].begin());

			if (result == testData.GetLabel(i)) correct++;
		}

		std::cout << std::endl;

		// Print accuracy.

		double accuracy = ((double)correct / (double)testData.Size()) * 100.0f;
		std::cout << "    Accuracy " << accuracy << " %\n";
		
		std::cout << std::endl;
	}

	// Wait to close program.
	system("PAUSE");
}
