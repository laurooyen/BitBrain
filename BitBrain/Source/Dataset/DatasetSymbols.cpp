// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "DatasetSymbols.h"

#include <fstream>
#include <iostream>

#include "MNIST.h"

namespace BB
{
	void DatasetSymbols::AppendCustom(const char* path, const std::vector<const char*>& symbols, uint32 max)
	{
		for (int i = 0; i < symbols.size(); i++)
		{
			std::string filename = path + std::string("/") + symbols[i];

			LoadSymbol(filename.c_str(), max, i + 10);
		}
	}

	void DatasetSymbols::AppendMNIST(const char* imageFileName, const char* labelFileName)
	{
		MNIST mnist(imageFileName, labelFileName);

		for (unsigned int i = 0; i < mnist.Size(); i++)
		{
			mData.push_back(mnist.GetImage(i));
			mLabels.push_back(mnist.GetLabel(i));
		}
	}

	void DatasetSymbols::PrintSymbol(uint32 index, double threshold) const
	{
		std::vector<double> data = GetData(index);

		for (unsigned int i = 0; i < (mRows * mCols); i++)
		{
			if ((i % mCols) == 0) std::cout << "\n";
			std::cout << ((data[i] >= threshold) ? "#" : ".") << " ";
		}

		std::cout << GetLabel(index) << std::endl << std::endl;
	}

	bool DatasetSymbols::LoadSymbol(const char* filename, uint32 max, uint32 label)
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

		for (unsigned int i = 0; i < size; i++)
		{
			mLabels.push_back(label);
		}

		file.close();
		return true;
	}
}
