// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "IDataset.h"

#include <numeric>

namespace BB
{
	void IDataset::FinishDataset()
	{
		mIndices = std::vector<uint32>(mData.size());

		mData.shrink_to_fit();
		mLabels.shrink_to_fit();

		Shuffle();
	}

	void IDataset::Shuffle()
	{
		std::iota(mIndices.begin(), mIndices.end(), 0);
		std::shuffle(mIndices.begin(), mIndices.end(), mRandom);
	}

	std::vector<double> IDataset::GetData(uint32 index) const
	{
		std::vector<double> data(mData[index].size());

		std::transform(mData[mIndices[index]].begin(), mData[mIndices[index]].end(), data.begin(), [](uint8 x) -> double { return x / 255.0; });

		return data;
	}

	uint32 IDataset::GetLabel(uint32 index) const
	{
		return mLabels[mIndices[index]];
	}

	uint32 IDataset::Size() const
	{
		return (uint32)mData.size();
	}
}
