// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#pragma once

#include "MNIST.h"

#include <iostream>
#include <fstream>

#include "../Utility/Endianness.h"

namespace BB
{
	MNIST::MNIST(const char* imageFileName, const char* labelFileName)
	{
		LoadImages(imageFileName);
		LoadLabels(labelFileName);
	}

	unsigned int MNIST::Size() const
	{
		return mSize;
	}

	unsigned int MNIST::Rows() const
	{
		return mRows;
	}

	unsigned int MNIST::Cols() const
	{
		return mCols;
	}

	std::vector<uint8> MNIST::GetImage(unsigned int i) const
	{
		return mImages[i];
	}

	int MNIST::GetLabel(unsigned int i) const
	{
		return mLabels[i];
	}

	bool MNIST::LoadImages(const char* filename)
	{
		uint32 magic;

		std::ifstream file(filename, std::ios::binary);

		file.read(reinterpret_cast<char*>(&magic), sizeof(magic));
		file.read(reinterpret_cast<char*>(&mSize), sizeof(mSize));
		file.read(reinterpret_cast<char*>(&mRows), sizeof(mRows));
		file.read(reinterpret_cast<char*>(&mCols), sizeof(mCols));

		magic = SwapEndianness(magic);
		mSize = SwapEndianness(mSize);
		mRows = SwapEndianness(mRows);
		mCols = SwapEndianness(mCols);

		if (magic != 0x803)
		{
			std::cout << "Error reading MNIST image file: " << filename << std::endl;
			file.close();
			return false;
		}

		mImages.reserve(mSize);

		uint8* temp = new uint8[mRows * mCols];
		for (unsigned int i = 0; i < mSize; ++i)
		{
			file.read(reinterpret_cast<char*>(temp), mRows * mCols);
			std::vector<uint8> image(mRows * mCols);
			for (unsigned int j = 0; j < mRows * mCols; ++j)
			{
				image[j] = temp[j];
			}
			mImages.push_back(image);
		}
		delete[] temp;

		file.close();
		return true;
	}

	bool MNIST::LoadLabels(const char* filename)
	{
		uint32 magic;

		std::ifstream file(filename, std::ios::binary);

		file.read(reinterpret_cast<char*>(&magic), sizeof(magic));
		file.read(reinterpret_cast<char*>(&mSize), sizeof(mSize));

		magic = SwapEndianness(magic);
		mSize = SwapEndianness(mSize);

		if (magic != 0x801)
		{
			std::cout << "Error reading MNIST label file: " << filename << std::endl;
			file.close();
			return false;
		}

		mLabels.reserve(mSize);

		for (unsigned int i = 0; i < mSize; i++)
		{
			int8 label;
			file.read(reinterpret_cast<char*>(&label), sizeof(label));
			mLabels.push_back(label);
		}

		file.close();
		return true;
	}
}
