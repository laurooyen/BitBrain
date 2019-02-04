// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include <cmath>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

#include "MNIST/MNIST.h"
#include "AI/Network.h"
#include "AI/Image.h"
#include "AI/SymbolExtractor.h"

using namespace BB;

void NetworkTest();
void HandwritingTest();
void BoundingBoxTest();

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
	NetworkTest();
	//HandwritingTest();
	//BoundingBoxTest();

	// Wait to close program.
	system("PAUSE");
}

// --------------------------------------------------
// TEST SUITES
// --------------------------------------------------

void NetworkTest()
{
	// GLOBAL SETTINGS

	int epochs = 10;

	// LOAD DATA

	std::cout << "Loading data.\n" << std::endl;

	MNIST trainData("Resource/MNIST/TrainingImages-200k.bin", "Resource/MNIST/TrainingLabels-200k.bin");
	MNIST testData("Resource/MNIST/TestingImages.bin", "Resource/MNIST/TestingLabels.bin");

	// INIT NETWORK

	Network network
	(
		{ 784, 100, 60, 10 },					// Layer count
        { AF::ReLU, AF::ReLU, AF::Softmax },	// Activation functions
		CF::CrossEntropy,						// Cost function
		0.003,									// Learning rate
		0.00115									// Regularization lambda
	);

	// TRAINING LOOP

	std::cout << "Training network:\n" << std::endl;

	std::vector<unsigned int> shuffle(trainData.Size());
	std::iota(shuffle.begin(), shuffle.end(), 0);

	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine rng(seed);

	for (int i = 0; i < epochs; i++)
	{
		std::cout << "  Epoch #" << (i + 1) << "\n\n";

		std::shuffle(shuffle.begin(), shuffle.end(), rng);

		// TRAIN NETWORK

		for (int j = 0; j < trainData.Size(); j++)
		{
			ProgressBar("    Training", j + 1, trainData.Size());

			std::vector<double> out(10, 0.0f);
			out[trainData.GetLabel(shuffle[j])] = 1.0f;

			network.Compute(trainData.GetImage(shuffle[j]));
			network.Learn(out);
		}

		std::cout << std::endl;

		// TEST NETWORK

        int correctTrain = 0;
		int correctTest = 0;

		for (int i = 0; i < testData.Size(); i++)
		{
			ProgressBar("    Testing ", i + 1, testData.Size());

			Matrix mTest = network.Compute(testData.GetImage(i));
			int resultTest = (int)(std::max_element(mTest.Elements().begin(), mTest.Elements().end()) - mTest.Elements().begin());
			if (resultTest == testData.GetLabel(i)) correctTest++;

            Matrix mTrain = network.Compute(trainData.GetImage(shuffle[i]));
            int resultTrain = (int)(std::max_element(mTrain.Elements().begin(), mTrain.Elements().end()) - mTrain.Elements().begin());
            if (resultTrain == trainData.GetLabel(shuffle[i])) correctTrain++;
		}

		std::cout << std::endl;

		// PRINT ACCURACY

		double accuracyTest = ((double)correctTest / (double)testData.Size()) * 100.0f;
        double accuracyTrain = ((double)correctTrain / (double)testData.Size()) * 100.0f;

		std::cout << "    Test Accuracy " << accuracyTest << " %\n";
        std::cout << "    Train Accuracy " << accuracyTrain << " %\n";

		std::cout << std::endl;
	}
}

void HandwritingTest()
{
	// Global settings.
	int epochs = 1;

	// Load Data.
	std::cout << "Loading data.\n" << std::endl;

	MNIST trainData("Resource/MNIST/TrainingImages.bin", "Resource/MNIST/TrainingLabels.bin");

	// Init network.
	Network network
	(
		{ 784, 15, 10 },				// Layer count
		{ AF::Sigmoid, AF::Sigmoid },	// Activation functions
		CF::EuclideanDistance,			// Cost function
		0.75,							// Learning rate
		0.0005							// Regularization lambda
	);

	// Train network.
	std::cout << "Training network:\n" << std::endl;

	for (int i = 0; i < epochs; i++)
	{
		std::cout << "  Epoch #" << (i + 1) << "\n\n";

		// Train network.

		for (int j = 0; j < trainData.Size(); j++)
		{
			ProgressBar("    Training", j + 1, trainData.Size());

			std::vector<double> out(10, 0.0f);
			out[trainData.GetLabel(j)] = 1.0f;

			network.Compute(trainData.GetImage(j));
			network.Learn(out);
		}
	}

	std::cout << "\n" << std::endl;

	// Handwriting test.
	std::cout << "Handwriting test:\n" << std::endl;

	Image image("Resource/BoundingBox/Three-004.png", 1);

	std::vector<double> myTestData(image.Width() * image.Height());

	for (int i = 0; i < image.Width() * image.Height(); i++)
	{
		myTestData[i] = image.GetRaw(i) / 255.0;

		// TODO(Lauro): Test to see if this works better.
		// myTestData[i] = (image.GetRaw(i) > 0) ? 1.0 : 0.0;
	}

	Matrix m = network.Compute(myTestData);
	int myResult = (int)(std::max_element(m.Elements().begin(), m.Elements().end()) - m.Elements().begin());

	std::cout << "  Classifiction: " << myResult << std::endl;

	std::cout << std::endl;
}

void BoundingBoxTest()
{
	Image image("Resource/BoundingBox/Digits.png", 1);

	SymbolExtractor extractor;

	extractor.MarkIslands(&image);

	std::cout << extractor.GetDebugInfo().str() << std::endl;

	std::cout << std::endl;
}
