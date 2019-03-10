// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "AI/Network.h"
#include "FileIO/Dataset.h"
#include "FileIO/FileManager.h"
#include "ImageProcessing/Image.h"
#include "ImageProcessing/SymbolExtractor.h"

#include <iostream>

using namespace BB;

int main()
{
	// LOAD TRAINED NETWORK

	Network network;

	FileManager fileManager("Resource/Networks");

	fileManager.LoadNetwork(network, "Network.bin", false);

	network.Init();

	// LOAD DATA

	std::vector<std::string> symbols =
	{
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
	};

	Image image("Resource/Images/Example 1.jpg");

	// EXTRACT SYMBOLS

	SymbolExtractor extractor(image);
	extractor.Threshold();
	extractor.CalculateBounds();
	extractor.CleanBounds();
	extractor.SortBounds();

	// CLASSIFY SYMBOLS

	for (unsigned int i = 0; i < extractor.Size(); i++)
	{
		Matrix m = network.FeedForward(extractor.GetImage(i));
		int result = (int)(std::max_element(m.Elements().begin(), m.Elements().end()) - m.Elements().begin());

		std::cout << "Classification: " << symbols[result] << std::endl;
	}

	// WAIT FOR USER TO CLOSE APP

	system("PAUSE");
}
