// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#pragma once

#include "IDataset.h"

namespace BB
{
	/// A dataset to recognize handwritten symbols.

	class DatasetSymbols : public IDataset
	{
	public:

		/// Adds symbols using our own dataset format.
		/// @param path The directory with the symbols.
		/// @param symbols A list of symbol file names.
		/// @param max The maximum amount of samples to load per symbol.
		void AppendCustom(const char* path, const std::vector<const char*>& symbols, uint32 max = 0);

		/// Adds symbols using the original MNIST file format.
		/// @param imageFileName The name of the file containing the images.
		/// @param labelFileName The name of the file containing the labels.
		void AppendMNIST(const char* imageFileName, const char* labelFileName);

		/// Prints a single symbol to the console.
		/// Foreground pixels get represented by a hastag, background pixels by a dot.
		/// @param index The symbol index in the range [0, Size() - 1].
		/// @param threshold Threshold to determine whether a pixel is foreground or background.
		void PrintSymbol(uint32 index, double threshold = 0.5) const;

	private:

		/// Loads a single dataset symbol.
		/// @param filename The filename of the symbol.
		/// @param max The maximum amount of samples to load.
		/// @param label The label for the symbol.
		bool LoadSymbol(const char* filename, uint32 max, uint32 label);

	private:

		const uint32 mRows = 28;	///< Row count in single image.
		const uint32 mCols = 28;	///< Column count in single image.
	};
}
