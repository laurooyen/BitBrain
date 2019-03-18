// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "DatasetSymbols.h"

#include <fstream>
#include <iostream>

namespace BB
{
	DatasetSymbols::DatasetSymbols(const char* path, const std::vector<const char*>& symbols, uint32 max)
	{
		for (const char* symbol : symbols)
		{
			std::string filename = path + std::string("/") + symbol;

			LoadSymbol(filename.c_str(), max);
		}

		FinishDataset();
	}

	bool DatasetSymbols::LoadSymbol(const char * filename, uint32 max)
	{
		uint32 magic, size, rows, cols;

		std::ifstream file(filename, std::ios::binary);

		file.read(reinterpret_cast<char*>(&magic), sizeof(magic));
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		file.read(reinterpret_cast<char*>(&rows), sizeof(rows));
		file.read(reinterpret_cast<char*>(&cols), sizeof(cols));

		if (magic != 0x41494442 || rows != mRows || cols != mCols)
		{
			std::cerr << "Error reading dataset symbol file: " << filename << std::endl;
			file.close();
			return false;
		}

		if (max > 0 && max < size)
		{
			size = max;
		}

		for (unsigned int i = 0; i < size; i++)
		{
			std::vector<uint8> image(rows * cols);
			file.read(reinterpret_cast<char*>(&image[0]), rows * cols);
			mData.push_back(image);
		}

		mLabels.push_back(mLabels.empty() ? size : mLabels.back() + size);

		file.close();
		return true;
	}
}
