// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "Image.h"

#include <iostream>

#include "../ThirdParty/stb_image.h"

namespace BB
{
	Image::Image()
		: mWidth(0)
		, mHeight(0)
		, mChannels(0)
		, mPixels(nullptr)
	{}

	Image::Image(const char* filename, int channels)
	{
		Load(filename, channels);
	}

	Image::~Image()
	{
		if (mPixels) stbi_image_free(mPixels);
	}

	bool Image::Load(const char * filename, int channels)
	{
		mPixels = stbi_load(filename, &mWidth, &mHeight, &mChannels, channels);

		if (channels > 0)
		{
			mChannels = channels;
		}

		if (!mPixels)
		{
			std::cout << "Failed to load image file: " << filename << std::endl;
			return false;
		}

		return true;
	}

	const uint8 Image::GetPixel(unsigned int x, unsigned int y, unsigned int channel) const
	{
		return mPixels[y * mWidth + x * mChannels + channel];
	}
}
