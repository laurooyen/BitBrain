// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "AI/Network.h"
#include "FileIO/FileManager.h"
#include "ImageProcessing/Image.h"
#include "ImageProcessing/SymbolExtractor.h"

#include <iostream>

using namespace BB;

std::stringstream GetDebugInfo(const std::vector<RectangleI>& rectangles, const std::vector<int>& classifications, const std::vector<const char*>& symbols)
{
	std::stringstream stream;

	stream << "[";

	for (int i = 0; i < rectangles.size(); i++)
	{
		stream << "[" << "\"" << symbols[classifications[i]] << "\"" << "," << rectangles[i].X() << "," << rectangles[i].Y() << "," << rectangles[i].Width() << "," << rectangles[i].Height() << "]";

		if (i < rectangles.size() - 1) stream << ",";
	}

	stream << "]";

	return stream;
}

int main(int argc, char* argv[])
{
	const char* imagePath;
	const char* networkPath;

	if (argc == 3)
	{
		imagePath = argv[1];
		networkPath = argv[2];
	}
	else
	{
		imagePath = "Resource/Images/Example Image.jpg";
		networkPath = "Resource/Networks";
	}

	Network network;

	FileManager fileManager(networkPath);

	fileManager.LoadNetwork(network, "Network.bin", false);

	network.Init();

	std::vector<const char*> symbols =
	{
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
	};

	Image image(imagePath);

	SymbolExtractor extractor(image);
	extractor.Threshold();
	extractor.CalculateBounds();
	extractor.CleanBounds();
	extractor.SortBounds();

	std::vector<int> results;

	for (unsigned int i = 0; i < extractor.Size(); i++)
	{
		Matrix m = network.FeedForward(extractor.GetImage(i));
		int result = (int)(std::max_element(m.Elements().begin(), m.Elements().end()) - m.Elements().begin());

		results.push_back(result);
	}

	std::cout << GetDebugInfo(extractor.Bounds(), results, symbols).str() << std::endl;
}
