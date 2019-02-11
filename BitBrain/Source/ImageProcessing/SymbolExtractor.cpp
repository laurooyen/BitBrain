// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "SymbolExtractor.h"

#include <queue>

#include <iostream>

namespace BB
{
	void SymbolExtractor::MarkIslands(Image* image)
	{
		mImage = image;

		mWidth = mImage->Width();
		mHeight = mImage->Height();

		mProcessed = std::vector<std::vector<bool>>(mHeight, std::vector<bool>(mWidth, false));
		mBounds = std::vector<RectangleI>();

		for (int y = 0; y < mHeight; y++)
		{
			for (int x = 0; x < mWidth; x++)
			{
				if (IsSafe(x, y))
				{
					BFS(x, y);
				}
			}
		}
	}

	std::stringstream SymbolExtractor::GetDebugInfo() const
	{
		std::stringstream stream;

		stream << "var rectangles = [";

		for (RectangleI r : mBounds)
		{
			stream << "[" << r.X() << "," << r.Y() << "," << r.Width() << "," << r.Height() << "],";
		}

		stream << "]";

		return stream;
	}

	std::vector<RectangleI> SymbolExtractor::GetBounds() const
	{
		return mBounds;
	}

	void SymbolExtractor::BFS(int j, int i)
	{
		// Relative coordinates of neighbours of a point.
		static int row[] = { -1, -1, -1, 0, 1, 0, 1, 1 };
		static int col[] = { -1, 1, 0, -1, -1, 1, 0, 1 };
		
		std::queue<std::pair<int, int>> q;

		q.push(std::make_pair(i, j));

		mProcessed[i][j] = true;

		mBounds.push_back(RectangleI(j, i, 0, 0));

		while (!q.empty())
		{
			int x = q.front().first;
			int y = q.front().second;

			q.pop();

			for (int k = 0; k < 8; k++)
			{
				if (IsSafe(y + col[k], x + row[k]))
				{
					mProcessed[x + row[k]][y + col[k]] = true;
					mBounds.back().Expand(y + col[k], x + row[k]);
					q.push(std::make_pair(x + row[k], y + col[k]));
				}
			}
		}
	}

	bool SymbolExtractor::IsSafe(int x, int y)
	{
		if (x < 0) return false;
		if (y < 0) return false;
		if (x >= mWidth) return false;
		if (y >= mHeight) return false;
		if (mProcessed[y][x]) return false;
		if (mImage->GetPixel(x, y) == 255) return false;

		return true;
	}
}
