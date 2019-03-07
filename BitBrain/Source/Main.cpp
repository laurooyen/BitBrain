// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "AI/Network.h"
#include "FileIO/Dataset.h"
#include "FileIO/FileManager.h"

#include "ImageProcessing/Image.h"
#include "ImageProcessing/SymbolExtractor.h"

#include "Util/Math/Functions.h"

#include <iostream>

using namespace BB;

std::stringstream GetDebugInfo(const std::vector<RectangleI>& rectangles)
{
	std::stringstream stream;

	stream << "[";

	for (int i = 0; i < rectangles.size(); i++)
	{
		stream << "[" << rectangles[i].X() << "," << rectangles[i].Y() << "," << rectangles[i].Width() << "," << rectangles[i].Height() << "]";

		if (i < rectangles.size() - 1) stream << ",";
	}

	stream << "]";

	return stream;
}

int main(int argc, char* argv[])
{
	// LOAD TRAINED NETWORK

	Network network;

	FileManager fileManager("Resource/Networks");

	fileManager.LoadNetwork(network, "Network.bin", false);

	network.Init();

	// HANDWRITING TEST

	Image image("Resource/BoundingBox/RealWorld.jpg");

	SymbolExtractor extractor(image);
	extractor.Threshold();
	extractor.CalculateBounds();
	extractor.CleanBounds();
	extractor.SortBounds();

	std::cout << GetDebugInfo(extractor.Bounds()).str() << std::endl;

	for (unsigned int i = 0; i < extractor.Size(); i++)
	{
		Matrix m = network.FeedForward(extractor.GetImage(i));
		int myResult = (int)(std::max_element(m.Elements().begin(), m.Elements().end()) - m.Elements().begin());

		std::cout << "Classifiction: " << myResult << std::endl;
	}

	system("PAUSE");
}
