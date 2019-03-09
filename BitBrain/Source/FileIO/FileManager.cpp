// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "FileManager.h"

#include "../AI/Network.h"

#include "../Utility/Serialization/Types.h"
#include "../Utility/Serialization/Archive.h"

#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

namespace fs = std::filesystem;

namespace BB
{
	FileManager::FileManager(const char* networkDir)
	{
		mNetworkDir = networkDir;
	}

	void FileManager::SetNetworkName(const char* name)
	{
		mNetworkName = name;
	}

	void FileManager::RequestNetworkName()
	{
		std::cout << "Enter network name: ";
		std::cin >> mNetworkName;
		std::cout << std::endl;

		if (!IsAlphaNumeric(mNetworkName[0]))
		{
			std::cout << "Not a valid network name. Please use a different name.\n" << std::endl;
			RequestNetworkName();
		}
		
		fs::path path(mNetworkDir);
		path.append(mNetworkName);

		if (fs::exists(path))
		{
			std::cout << "Network already exists. Please use a different name.\n" << std::endl;
			RequestNetworkName();
		}
	}

	void FileManager::LoadNetwork(Network& network, std::string name, bool confirm) const
	{
		fs::path path(mNetworkDir);
		path.append(name);

		std::ifstream file(path, std::ios::binary);

		if (file.is_open())
		{
			Network savedNetwork;

			Archive<std::ifstream, false> archive(file);
			archive >> savedNetwork;

			if (confirm)
			{
				std::cout << "Found a saved network with the follow settings:\n\n";
				std::cout << "  File Format Version:   " << archive.GetVersion() << "\n\n";

				DumpNetwork(savedNetwork);

				std::cout << "\nDo you want to load it (Y, N) ?   ";

				char input;
				std::cin >> input;
				if (input == 'Y') network = savedNetwork;
			}
			else
			{
				network = savedNetwork;
			}
		}
		else
		{
			std::cerr << "Network <" << name << "> does not exist.\n" << std::endl;
		}

		file.close();
	}

	void FileManager::SaveNetwork(const Network& network) const
	{
		fs::path path(mNetworkDir);
		path.append(mNetworkName);

		fs::create_directories(path);

		path.append(GetTimeStamp());
		path.concat("-E");
		path.concat(std::to_string(network.Epoch() + 1));
		path.concat(".bin");

		std::ofstream file(path, std::ios::binary);

		Archive<std::ofstream, true> archive(file);
		archive << network;

		file.close();
	}

	void FileManager::SaveNetworkCSV() const
	{
		for (const auto & directory : fs::recursive_directory_iterator(mNetworkDir))
		{
			if (!directory.is_directory()) continue;
			if (fs::is_empty(directory.path())) continue;

			fs::path csvPath(directory);
			csvPath.append("Network.csv");

			std::ofstream csvFile(csvPath);

			std::locale mylocale("");
			csvFile.imbue(mylocale);

			csvFile << "Trained Epochs;";
			csvFile << "Test Accuracy;";
			csvFile << "Train Accuracy;";
			csvFile << "Layers;";
			csvFile << "Activation Functions;";
			csvFile << "Cost Function;";
			csvFile << "Batch Size;";
			csvFile << "Batch Size Factor;";
			csvFile << "Batch Size Max;";
			csvFile << "Learning Rate;";
			csvFile << "Learning Rate Factor;";
			csvFile << "Learning Rate Max;";
			csvFile << "Regularization Lambda;";
			csvFile << "Momentum\n";

			for (const auto & entry : fs::directory_iterator(directory))
			{
				if (entry.path().extension() != ".bin") continue;

				Network network;

				std::ifstream networkFile(entry, std::ios::binary);
				Archive<std::ifstream, false> archive(networkFile);
				archive >> network;

				csvFile << (network.Epoch() + 1) << ";";
				csvFile << network.AccuracyTest() << " %;";
				csvFile << network.AccuracyTrain() << " %;";

				csvFile << "{ ";
				for (int l : network.Layers()) csvFile << l << " ";
				csvFile << "};";

				csvFile << "{ ";
				for (AF af : network.af) csvFile << ToString(af) << " ";
				csvFile << "};";

				csvFile << ToString(network.cf) << ";";
				csvFile << network.batchSize << ";";
				csvFile << network.batchSizeFactor << ";";
				csvFile << network.batchSizeMax << ";";
				csvFile << network.learningRate << ";";
				csvFile << network.learningRateFactor << ";";
				csvFile << network.learningRateMin << ";";
				csvFile << network.lambda << ";";
				csvFile << network.mu << "\n";

				networkFile.close();
			}

			csvFile.close();
		}
	}

	void FileManager::DumpNetwork(const Network& network) const
	{
		std::cout << "  Trained Epochs:        " << (network.Epoch() + 1) << "\n\n";

		std::cout << "  Test Accuracy:         " << network.AccuracyTest() << " %\n";
		std::cout << "  Train Accuracy:        " << network.AccuracyTrain() << " %\n\n";

		std::cout << "  Layers:                { ";
		for (int l : network.Layers()) std::cout << l << " ";
		std::cout << "}\n";

		std::cout << "  Activation Functions:  { ";
		for (AF af : network.af) std::cout << ToString(af) << " ";
		std::cout << "}\n";

		std::cout << "  Cost Function:         " << ToString(network.cf) << "\n\n";

		std::cout << "  Batch Size:            " << network.batchSize << "\n";
		std::cout << "  Batch Size Factor:     " << network.batchSizeFactor << "\n";
		std::cout << "  Batch Size Max:        " << network.batchSizeMax << "\n\n";

		std::cout << "  Learning Rate:         " << network.learningRate << "\n";
		std::cout << "  Learning Rate Factor:  " << network.learningRateFactor << "\n";
		std::cout << "  Learning Rate Min:     " << network.learningRateMin << "\n\n";

		std::cout << "  Regularization Lambda: " << network.lambda << "\n";
		std::cout << "  Momentum:              " << network.mu << "\n";
	}

	bool FileManager::IsAlphaNumeric(char c) const
	{
		return (c >= 'a' && c <= 'z') ||
		       (c >= 'A' && c <= 'Z') ||
		       (c >= '0' && c <= '9') ||
		        c == '_';
	}

	std::string FileManager::GetTimeStamp() const
	{
		time_t t = time(0);
		struct tm* timeinfo;
		timeinfo = localtime(&t);

		char buffer[20];
		strftime(buffer, 20, "%Y%m%d-%H%M%S", timeinfo);

		return std::string(buffer);
	}
}
