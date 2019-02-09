// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "MNIST/MNIST.h"
#include "AI/Network.h"

#include "Util/Common.h"
#include "Util/Serialization/Archive.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace BB;

void LoadNetwork(Network& network, std::string filename);

int main()
{
	// GLOBAL SETTINGS

	unsigned int epochs = 10;
	unsigned int miniBatchSize = 5;

	Network network({ 784, 100, 60, 10 });

	network.af = { AF::ReLU, AF::ReLU, AF::Softmax };
	network.cf = CF::EuclideanDistance;
	network.learningRate = 0.0035;
	network.lambda = 0.00125;
	network.mu = 0.01; //idk still have to test which value is best

	double learningRateScheduleFactor = 0.8; //still have to test which value to use
	double previousAccuracy = 0;
	
	// LOAD SAVED NETWORK

	// Change the filename below to load a saved network.
	// When the file doesn't exist, nothing will happen.

	// Move the network parameters (af, cf, learningRate, lambda) listed above,
	// below the LoadNetwork() function to overwrite the respective parameters of the loaded network.
	// Note that the neuron count can't be adjusted since it is passed to the networks constructor.

	
	std::cout << "load network?";
	std::string loadPath = "";
	std::cin >> loadPath;
	LoadNetwork(network, loadPath);
	
	
	// STORE SAVE PATH
	
	std::cout << "save trained network epochs to (existing, absolute) path (you can add prefix to filenames after last / ): \n ";
	std::string savePath = "";
	std::cin >> savePath;
	

	// LOAD TRAINING AND TESTING DATA

	std::cout << "Loading data.\n" << std::endl;

	MNIST trainData("Resource/MNIST/TrainingImages-200k.bin", "Resource/MNIST/TrainingLabels-200k.bin");
	MNIST testData("Resource/MNIST/TestingImages.bin", "Resource/MNIST/TestingLabels.bin");

	
	// TRAINING LOOP

	std::cout << "Training network.\n" << std::endl;

	network.Init();
	
	for(unsigned int i = 0; i < epochs; i++)
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

		// SAVE NETWORK
		std::stringstream filePath;
		filePath << savePath << "" << GetTimeStamp() << "-E" << (i + 1) << ".bin";
		
		std::ofstream file(filePath.str(), std::ios::binary);
		
		Archive<std::ofstream, true> archive(file);

		archive << network << i << miniBatchSize << accuracyTest << accuracyTrain;

		file.close();

		std::cout << "    Saved network: " << filePath.str() << "\n";

		std::cout << std::endl;
		
		//learning rate scheduling
		if(previousAccuracy > accuracyTest)
		{
			network.learningRate *= learningRateScheduleFactor;
			std::cout << "		Learning rate updated: " << network.learningRate;
		}
	}

	// WAIT TO CLOSE PROGRAM

	system("PAUSE");
}

// --------------------------------------------------
// HELPER FUNCTIONS
// --------------------------------------------------

void LoadNetwork(Network& network, std::string filename)
{
	std::ifstream file(filename, std::ios::binary);

	if (file.is_open())
	{
		Network savedNetwork;
		unsigned int epoch;
		unsigned int miniBatchSize;
		double accuracyTest;
		double accuracyTrain;

		Archive<std::ifstream, false> archive(file);
		archive >> savedNetwork >> epoch >> miniBatchSize >> accuracyTest >> accuracyTrain;

		std::cout << "Found a saved network with the follow settings:\n\n";
		std::cout << "  File Format Version:   " << archive.GetVersion() << "\n\n";
		std::cout << "  Trained Epochs:        " << (epoch + 1) << "\n";
		std::cout << "  Mini Batch Size:       " << miniBatchSize << " \n\n";
		std::cout << "  Test Accuracy:         " << accuracyTest << " %\n";
		std::cout << "  Train Accuracy:        " << accuracyTrain << " %\n\n";
		savedNetwork.DumpSettings();

		std::cout << "\nDo you want to load it (Y, N) ?   ";

		char load;
		std::cin >> load;

		if (load == 'Y') network = savedNetwork;

		system("CLS");
	}
	else
	{
		std::cout << "file " << filename << " not found\n";
	}

	file.close();
}
