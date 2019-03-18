// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#pragma once

#include "IDataset.h"

namespace BB
{
	/// A dataset to convert binary to decimal numbers.

	class DatasetBinary : public IDataset
	{
	public:

		/// Creates a new dataset.
		/// @param max The maximum amount of numbers to generate.
		/// @param length The length of the binary number in bits.
		DatasetBinary(uint32 max, uint32 length);

	private:

		/// Generates a single binary number.
		/// @param value The decimal value to be converted into binary.
		/// @param length The length of the binary number in bits.
		void GenerateNumber(unsigned int value, unsigned int length);
	};
}
