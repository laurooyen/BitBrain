// // Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#include "Image.h"

#include "../Utility/Containers/Array2D.h"

#include "../ThirdParty/stb/stb_image.h"
#include "../ThirdParty/stb/stb_image_write.h"
#include "../ThirdParty/stb/stb_image_resize.h"

#include <iostream>

namespace BB
{
	// Constructors

	Image::Image()
		: mWidth(0)
		, mHeight(0)
		, mChannels(0)
		, mPixels(std::vector<uint8>())
	{}

	Image::Image(unsigned int w, unsigned int h, unsigned int channels)
		: mWidth(w)
		, mHeight(h)
		, mChannels(channels)
		, mPixels(std::vector<uint8>(w * h * channels, 0))
	{}

	Image::Image(const std::vector<uint8>& data, unsigned int w, unsigned int h, unsigned int channels)
		: mWidth(w)
		, mHeight(h)
		, mChannels(channels)
		, mPixels(data)
	{}

	Image::Image(const char* filename, unsigned int channels)
	{
		uint8* pixels = stbi_load(filename, &(int&)mWidth, &(int&)mHeight, &(int&)mChannels, channels);

		if (!pixels)
		{
			std::cerr << "Failed to load image file: " << filename << std::endl;
		}

		if (channels > 0)
		{
			mChannels = channels;
		}

		mPixels = std::vector(&pixels[0], &pixels[mWidth * mHeight * mChannels]);

		stbi_image_free(pixels);
	}

	void Image::Save(const char* filename)
	{
		bool succes = stbi_write_png(filename, mWidth, mHeight, mChannels, &mPixels[0], mWidth * mChannels);

		if (!succes)
		{
			std::cerr << "Failed to save image file: " << filename << std::endl;
		}
	}

	// Calculations

	Image Image::Resize(const Image& src, const Vector2I& size)
	{
		Image dst(size.x, size.y, src.Channels());

		stbir_resize_uint8(&src.mPixels[0], src.mWidth, src.mHeight, 0, &dst.mPixels[0], dst.mWidth, dst.mHeight, 0, src.Channels());

		return dst;
	}

	void Image::Blit(const Image& src, Image& dst, const RectangleI& srcRect, const Vector2I& dstVec)
	{
		for (int y = 0; y < srcRect.Height(); y++)
		{
			for (int x = 0; x < srcRect.Width(); x++)
			{
				for (unsigned int c = 0; c < src.Channels(); c++)
				{
					dst(x + dstVec.x, y + dstVec.y, c) = src(x + srcRect.X(), y + srcRect.Y(), c);
				}
			}
		}
	}

	void Image::Fill(uint8 color)
	{
		for (uint8& pixel : mPixels)
		{
			pixel = color;
		}
	}

	void Image::Invert()
	{
		for (uint8& pixel : mPixels)
		{
			pixel = (255 - pixel);
		}
	}

	void Image::Threshold(uint8 threshold)
	{
		for (uint8& pixel : mPixels)
		{
			pixel = ((pixel <= threshold) ? 0 : 255);
		}
	}

	void Image::AdaptiveThreshold(uint8 size, uint8 constant)
	{
		int halfSize = size / 2;

		Array2D<uint64> integral(mWidth, mHeight);

		for (unsigned int y = 0; y < mHeight; y++)
		{
			uint64 sum = 0;

			for (unsigned int x = 0; x < mWidth; x++)
			{
				sum += mPixels[y * mWidth + x];

				if (y == 0)
				{
					integral(x, y) = sum;
				}
				else
				{
					integral(x, y) = integral(x, y - 1) + sum;
				}
			}
		}

		for (unsigned int y = 0; y < mHeight; y++)
		{
			for (unsigned int x = 0; x < mWidth; x++)
			{
				int x1 = x - halfSize;
				int x2 = x + halfSize;
				int y1 = y - halfSize;
				int y2 = y + halfSize;

				if (x1 < 0) x1 = 0;
				if (y1 < 0) y1 = 0;
				if (x2 >= (int)mWidth) x2 = mWidth - 1;
				if (y2 >= (int)mHeight) y2 = mHeight - 1;

				int count = (x2 - x1) * (y2 - y1);

				uint64 sum = integral(x1, y1) - integral(x1, y2) - integral(x2, y1) + integral(x2, y2);

				mPixels[y * mWidth + x] = (mPixels[y * mWidth + x] > ((sum / count) - constant)) ? 255 : 0;
			}
		}
	}

	// Operators

	uint8& Image::operator()(unsigned int index)
	{
		return mPixels[index];
	}

	const uint8& Image::operator()(unsigned int index) const
	{
		return mPixels[index];
	}

	uint8& Image::operator()(unsigned int x, unsigned int y, unsigned int channel)
	{
		return mPixels[y * mWidth + x * mChannels + channel];
	}

	const uint8& Image::operator()(unsigned int x, unsigned int y, unsigned int channel) const
	{
		return mPixels[y * mWidth + x * mChannels + channel];
	}
}
