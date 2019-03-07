// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include "../Util/CoreTypes.h"

#include <vector>

namespace BB
{
	/// Description for a single symbol in a Dataset.

	struct DatasetSymbol
	{
		const char* name;		///< Mathematical name.
		const char* filename;	///< Filepath to the binary data file.
	};

	/// Class responsible for loading training and testing data.

	class Dataset
	{
	public:

		// Constructors

		/// Creates a new dataset.
		/// @param path The directory with the symbols.
		/// @param symbols A list of DatasetSymbol.
		/// @param max The maximum amount of samples to load per symbol.
		Dataset(const char* path, const std::vector<DatasetSymbol>& symbols, uint32 max = 0);

		// Calculations

		/// Randomly shuffles the image order.
		void Shuffle();

		/// Returns a single image.
		/// @param index The image index in the range [0, Size() - 1].
		std::vector<double> GetImage(uint32 index) const;

		/// Returns a single label for an image.
		/// @param index The label index in the range [0, Size() - 1].
		uint32 GetLabel(uint32 index) const;

		// Getters

		uint32 Size() const { return (uint32)mImages.size(); }
		uint32 Rows() const { return mRows; }
		uint32 Cols() const { return mCols; }

	private:

		/// Loads a single dataset symbol.
		/// @param filename The filename of the symbol.
		/// @param max The maximum amount of samples to load.
		bool LoadSymbol(const char* filename, uint32 max);

	private:

		const uint32 mRows = 28;					///< Row count in single image.
		const uint32 mCols = 28;					///< Column count in single image.

		std::vector<DatasetSymbol> mSymbols;		///< List of symbols.

		std::vector<std::vector<uint8>> mImages;	///< Raw image data.
		std::vector<uint32> mIndices;				///< Random indices to index into image data.
		std::vector<uint32> mLabels;				///< Start index for every label.
	};
}
