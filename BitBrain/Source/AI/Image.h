// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include "../Util/CoreTypes.h"

namespace BB
{
	class Image
	{
	public:

		Image();
		Image(const char* filename, int channels);

		~Image();

		bool Load(const char* filename, int channels);

		const uint8* GetPixels() const { return mPixels; }

		const uint8 GetPixel(unsigned int x, unsigned int y, unsigned int channel = 0) const;

		int Width() const { return mWidth; }
		int Height() const { return mHeight; }
		int Channels() const { return mChannels; }

	private:

		int mWidth;
		int mHeight;
		int mChannels;

		uint8* mPixels;
	};
}
