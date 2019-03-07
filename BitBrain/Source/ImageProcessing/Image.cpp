// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "Image.h"

#include <iostream>

#include "../ThirdParty/stb_image.h"
#include "../ThirdParty/stb_image_write.h"
#include "../ThirdParty/stb_image_resize.h"

namespace BB
{
	// Constructors

	Image::Image()
		: mWidth(0)
		, mHeight(0)
		, mChannels(0)
		, mPixels(std::vector<uint8>())
	{}

	Image::Image(const Vector2I & size, unsigned int channels)
		: mWidth(size.x)
		, mHeight(size.y)
		, mChannels(channels)
		, mPixels(std::vector<uint8>(size.x * size.y * channels))
	{}

	Image::Image(unsigned int w, unsigned int h, unsigned int channels)
		: mWidth(w)
		, mHeight(h)
		, mChannels(channels)
		, mPixels(std::vector<uint8>(w * h * channels))
	{}

	Image::Image(const char* filename, unsigned int channels)
	{
		uint8* pixels = stbi_load(filename, &(int&)mWidth, &(int&)mHeight, &(int&)mChannels, channels);

		if (!pixels)
		{
			std::cout << "Failed to load image file: " << filename << std::endl;
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
			std::cout << "Failed to save image file: " << filename << std::endl;
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
		// TODO(Lauro): src and dst should be large enough to hold the data.
		// TODO(Lauro): src and dst should have the same amount of channels.

		for (int y = 0; y < srcRect.Height(); y++)
		{
			for (int x = 0; x < srcRect.Width(); x++)
			{
				for (unsigned int i = 0; i < src.Channels(); i++)
				{
					dst(x + dstVec.x, y + dstVec.y, i) = src(x + srcRect.X(), y + srcRect.Y(), i);
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
