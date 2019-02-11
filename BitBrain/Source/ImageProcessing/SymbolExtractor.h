// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include <vector>
#include <sstream>

#include "../Util/CoreTypes.h"
#include "../Util/Math/Rectangle.h"
#include "Image.h"

namespace BB
{
	class SymbolExtractor
	{
	public:

		void MarkIslands(Image* image);
		std::stringstream GetDebugInfo() const;
		std::vector<RectangleI> GetBounds() const;

	private:

		void BFS(int j, int i);
		bool IsSafe(int x, int y);

	private:

		int mWidth;
		int mHeight;

		Image* mImage;

		int mThreshold;

		std::vector<std::vector<bool>> mProcessed;
		std::vector<RectangleI> mBounds;
	};
}
