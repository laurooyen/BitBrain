// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "AI/Network.h"
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

	// DEFINE DATA

	std::vector<const char*> symbols =
	{
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
	};

	Image image("Resource/Images/Example Image.jpg");

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
