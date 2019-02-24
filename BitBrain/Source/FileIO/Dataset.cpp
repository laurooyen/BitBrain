// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "Dataset.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>

namespace BB
{
	std::default_random_engine GRandom;

	Dataset::Dataset(const char* path, const std::vector<DatasetSymbol>& symbols)
	{
		mSymbols = symbols;

		for (DatasetSymbol& symbol : mSymbols)
		{
			std::string filename = path + std::string("/") + symbol.filename;

			LoadSymbol(filename.c_str());
		}

		mIndices = std::vector<uint32>(mImages.size());

		mImages.shrink_to_fit();
		mLabels.shrink_to_fit();

		Shuffle();
	}

	void Dataset::Shuffle()
	{
		std::iota(mIndices.begin(), mIndices.end(), 0);
		std::shuffle(mIndices.begin(), mIndices.end(), GRandom);
	}

	std::vector<double> Dataset::GetImage(uint32 index) const
	{
		std::vector<double> image(mRows * mCols);

		std::transform(mImages[mIndices[index]].begin(), mImages[mIndices[index]].end(), image.begin(), [](uint8 x) -> double { return x / 255.0; });

		return image;
	}

	uint32 Dataset::GetLabel(uint32 index) const
	{
		for (int i = 0; i < mLabels.size(); i++)
		{
			if (mIndices[index] < mLabels[i]) return i;
		}

		return 0;
	}

	bool Dataset::LoadSymbol(const char* filename)
	{
		uint32 magic, size, rows, cols;
		
		std::ifstream file(filename, std::ios::binary);

		file.read(reinterpret_cast<char*>(&magic), sizeof(magic));
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		file.read(reinterpret_cast<char*>(&rows), sizeof(rows));
		file.read(reinterpret_cast<char*>(&cols), sizeof(cols));

		if (magic != 0x41494442 || rows != mRows || cols != mCols)
		{
			std::cout << "Error reading dataset symbol file: " << filename << std::endl;
			file.close();
			return false;
		}

		for (unsigned int i = 0; i < size; i++)
		{
			std::vector<uint8> image(rows * cols);
			file.read(reinterpret_cast<char*>(&image[0]), rows * cols);
			mImages.push_back(image);
		}

		mLabels.push_back(mLabels.empty() ? size : mLabels.back() + size);

		file.close();
		return true;
	}
}
