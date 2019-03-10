// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#pragma once

#include "Image.h"

#include "../Utility/CoreTypes.h"
#include "../Utility/Math/Rectangle.h"
#include "../Utility/Containers/Array2D.h"

#include <vector>
#include <sstream>

namespace BB
{
	class Image;

	/// Extracts individual symbols out of an image.

	class SymbolExtractor
	{
	public:

		// Constructors

		/// Creates a new symbol extractor.
		/// @param image The image to process.
		SymbolExtractor(const Image& image);

		// Calculations

		/// Converts the input image to a binary image.
		void Threshold();

		/// Calculates the bounding boxes of connected pixels.
		void CalculateBounds();

		/// Removes bounding boxes that are smaller than a predefined threshold.
		/// If the threshold is small enough, these bounding boxes won't contain any symbols.
		void CleanBounds();

		/// Sorts the bounding boxes based on ascending x and y coordinates.
		void SortBounds();

		/// Returns a single image.
		/// @param index The image index in the range [0, Size() - 1].
		std::vector<double> GetImage(uint32 index);

		// Getters

		uint32 Size() const { return (uint32)mBounds.size(); }

		std::vector<RectangleI> Bounds() const { return mBounds; }

	private:

		/// Performs a breadth first search on the image starting at coordinate (x, y).
		void BreadthFirstSearch(int x, int y, Array2D<bool>& processed);

		/// Checks whether it's safe to access the image pixel at coordinate (x, y).
		bool IsSafe(int x, int y, const Array2D<bool>& processed) const;

	private:

		Image mImage;						///< Image that is currently getting processed.
		std::vector<RectangleI> mBounds;	///< Bounding boxes of individual symbols. 
	};
}
