// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "SymbolExtractor.h"

#include "../Utility/Math/Functions.h"

#include <queue>

namespace BB
{
	SymbolExtractor::SymbolExtractor(const Image& image)
	{
		mImage = image;
	}

	void SymbolExtractor::Threshold()
	{
		mImage.AdaptiveThreshold(101, 15);
	}

	void SymbolExtractor::CalculateBounds()
	{
		mBounds = std::vector<RectangleI>();

		Array2D<bool> processed(mImage.Width(), mImage.Height(), false);

		for (unsigned int y = 0; y < mImage.Height(); y++)
		{
			for (unsigned int x = 0; x < mImage.Width(); x++)
			{
				if (IsSafe(x, y, processed))
				{
					BreadthFirstSearch(x, y, processed);
				}
			}
		}
	}

	void SymbolExtractor::CleanBounds()
	{
		mBounds.erase(std::remove_if(mBounds.begin(), mBounds.end(), [](RectangleI r) {
			return r.Width() <= 5 || r.Height() <= 5;
		}), mBounds.end());
	}

	void SymbolExtractor::SortBounds()
	{
		std::sort(mBounds.begin(), mBounds.end(), [](RectangleI a, RectangleI b) {
			return a.X() < b.X();
		});
	}

	std::vector<double> SymbolExtractor::GetImage(uint32 index)
	{
		Image tempImage(mBounds[index].Size().x, mBounds[index].Size().y);

		Image::Blit(mImage, tempImage, mBounds[index], Vector2I::Zero);

		float scale = Math::Min(22 / (float)tempImage.Width(), 22 / (float)tempImage.Height());

		tempImage = Image::Resize(tempImage, Vector2I((int)((float)tempImage.Width() * scale), (int)((float)tempImage.Height() * scale)));

		Image finalImage(28, 28);

		finalImage.Fill(255);

		Image::Blit(tempImage, finalImage, tempImage.Size(), (finalImage.Size() - tempImage.Size()) / 2);

		finalImage.Invert();

		std::vector<double> r(finalImage.Width() * finalImage.Height());

		std::transform(finalImage.Pixels().begin(), finalImage.Pixels().end(), r.begin(), [](uint8 x) -> double { return x / 255.0; });

		return r;
	}

	void SymbolExtractor::BreadthFirstSearch(int x, int y, Array2D<bool>& processed)
	{
		// Relative coordinates of neighbours of a point.
		static int row[] = { -1, -1, -1, 0, 1, 0, 1, 1 };
		static int col[] = { -1, 1, 0, -1, -1, 1, 0, 1 };

		processed(x, y) = true;
		
		mBounds.push_back(RectangleI(x, y, 0, 0));

		std::queue<std::pair<int, int>> q;

		q.push(std::make_pair(x, y));

		while (!q.empty())
		{
			int qx = q.front().first;
			int qy = q.front().second;

			q.pop();

			for (int k = 0; k < 8; k++)
			{
				if (IsSafe(qx + col[k], qy + row[k], processed))
				{
					processed(qx + col[k], qy + row[k]) = true;
					mBounds.back().Expand(qx + col[k], qy + row[k]);
					q.push(std::make_pair(qx + col[k], qy + row[k]));
				}
			}
		}

		mBounds.back().Width(mBounds.back().Width() + 1);
		mBounds.back().Height(mBounds.back().Height() + 1);
	}

	bool SymbolExtractor::IsSafe(int x, int y, const Array2D<bool>& processed) const
	{
		if (x < 0) return false;
		if (y < 0) return false;
		if (x >= (int)mImage.Width()) return false;
		if (y >= (int)mImage.Height()) return false;
		if (processed(x, y)) return false;
		if (mImage(x, y) == 255) return false;

		return true;
	}
}
