// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include <cmath>
#include <time.h>
#include <iostream>
#include <algorithm>

#include "MNIST/MNIST.h"
#include "AI/Network.h"
#include "AI/Image.h"
#include "AI/SymbolExtractor.h"

using namespace BB;

void NetworkTest()
{
	// Global settings.
	int epochs = 1;

	// Load Data.
	std::cout << "Loading data.\n" << std::endl;

	MNIST trainData("Resource/MNIST/TrainingImages.bin", "Resource/MNIST/TrainingLabels.bin");
	MNIST testData("Resource/MNIST/TestingImages.bin", "Resource/MNIST/TestingLabels.bin");

	// Init network.
	Network network({ 784, 15, 10 }, 0.75);

	// Train network.
	std::cout << "Training network:\n" << std::endl;

	for (int i = 0; i < epochs; i++)
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
	}

	std::cout << std::endl;

	// Test network.
	std::cout << "Testing network:\n" << std::endl;

	int correct = 0;

	for (int i = 0; i < testData.Size(); i++)
	{
		if (i % 1000 == 0) std::cout << "  Sample #" << i << "\n";

		Matrix m = network.Compute(testData.GetImage(i));
		int result = (int)(std::max_element(m[0].begin(), m[0].end()) - m[0].begin());

		if (result == testData.GetLabel(i)) correct++;
	}

	std::cout << std::endl;

	// Print accuracy.
	double accuracy = ((double)correct / (double)testData.Size()) * 100.0f;
	std::cout << "Accuracy: " << accuracy << "%\n" << std::endl;
}

void BoundingBoxTest()
{
	Image image("Resource/BoundingBox/Digits.png", 1);

	SymbolExtractor extractor;

	extractor.MarkIslands(&image);

	std::cout << extractor.GetDebugInfo().str() << std::endl;
}

int main()
{
	NetworkTest();
	//BoundingBoxTest();

	// Wait to close program.
	system("PAUSE");
}
