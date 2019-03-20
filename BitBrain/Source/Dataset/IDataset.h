// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/CoreTypes.h"

#include <vector>
#include <random>

namespace BB
{
	/// Abstract interface for passing training and testing data to a network.

	class IDataset
	{
	public:

		/// Initializes the internal state.
		/// This function should be called before using the dataset.
		void FinishDataset();
		
		/// Randomly shuffles the data order.
		void Shuffle();

		/// Returns a single data entry.
		/// @param index The data index in the range [0, Size() - 1].
		std::vector<double> GetData(uint32 index) const;

		/// Returns a single label.
		/// @param index The label index in the range [0, Size() - 1].
		uint32 GetLabel(uint32 index) const;

		// Getters

		/// Returns the amount of data in this dataset.
		uint32 Size() const;

	protected:

		std::vector<std::vector<uint8>> mData;	///< Raw data.
		std::vector<uint32> mIndices;			///< Random indices to index into data.
		std::vector<uint32> mLabels;			///< Labels for the data entries.

	private:

		std::default_random_engine mRandom;		///< Random number generator.
	};
}
