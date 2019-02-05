// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include "../Util/CoreTypes.h"

#include <vector>

namespace BB
{
	class MNIST
	{
	public:

		MNIST(const char* imageFileName, const char* labelFileName);

		int Size() const;
		int Rows() const;
		int Cols() const;

		std::vector<double> GetImage(unsigned int i) const;
		int GetLabel(unsigned int i) const;

	private:

		bool LoadImages(const char* filename);
		bool LoadLabels(const char* filename);

	private:

		uint32 mSize;
		uint32 mRows;
		uint32 mCols;

		std::vector<std::vector<double>> mImages;
		std::vector<int> mLabels;
	};
}
