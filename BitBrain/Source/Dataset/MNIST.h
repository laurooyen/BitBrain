// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#pragma once

#include "IDataset.h"

namespace BB
{
	class MNIST
	{
	public:

		MNIST(const char* imageFileName, const char* labelFileName);

		unsigned int Size() const;
		unsigned int Rows() const;
		unsigned int Cols() const;

		std::vector<uint8> GetImage(unsigned int i) const;
		int GetLabel(unsigned int i) const;

	private:

		bool LoadImages(const char* filename);
		bool LoadLabels(const char* filename);

	public:

		uint32 mSize;
		uint32 mRows;
		uint32 mCols;

		std::vector<std::vector<uint8>> mImages;
		std::vector<int> mLabels;
	};
}
