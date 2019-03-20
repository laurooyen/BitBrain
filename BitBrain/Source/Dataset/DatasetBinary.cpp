// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "DatasetBinary.h"

namespace BB
{
	DatasetBinary::DatasetBinary(uint32 max, uint32 length)
	{
		for (unsigned int i = 0; i < max; i++)
		{
			GenerateNumber(i, length);
		}
	}

	void DatasetBinary::GenerateNumber(unsigned int value, unsigned int length)
	{
		std::vector<uint8> number(length);

		for (unsigned int i = 0; i < length; i++)
		{
			number[i] = ((((value >> i) & 1) == 1) ? 255 : 0);
		}

		std::reverse(number.begin(), number.end());

		mLabels.push_back(value);
		mData.push_back(number);
	}
}
