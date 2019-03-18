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

		/// Creates a new dataset.
		/// @param path The directory with the symbols.
		/// @param symbols A list of symbol file names.
		/// @param max The maximum amount of samples to load per symbol.
		DatasetSymbols(const char* path, const std::vector<const char*>& symbols, uint32 max = 0);

	private:

		/// Loads a single dataset symbol.
		/// @param filename The filename of the symbol.
		/// @param max The maximum amount of samples to load.
		bool LoadSymbol(const char* filename, uint32 max);

	private:

		const uint32 mRows = 28;	///< Row count in single image.
		const uint32 mCols = 28;	///< Column count in single image.
	};
}
