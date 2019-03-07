// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include "../Util/CoreTypes.h"

#include "../Util/Math/Vector2.h"
#include "../Util/Math/Rectangle.h"

#include <vector>

namespace BB
{
	/// Class representing a 2D image.

	class Image
	{
	public:

		// Constructors

		Image();
		Image(const Vector2I& size, unsigned int channels = 1);
		Image(unsigned int w, unsigned int h, unsigned int channels = 1);
		Image(const char* filename, unsigned int channels = 1);

		// File IO

		/// Saves an image file to disk.
		/// @param filename The filename of the image.
		void Save(const char* filename);

		// Calculations

		/// Resizes an image.
		/// @param src The image to resize.
		/// @param size The size of the new image.
		/// @return The resized image.
		static Image Resize(const Image& src, const Vector2I& size);

		/// Copies a rectangular area of pixels from one image to another.
		/// @param src The source image from which pixels will be copied.
		/// @param dst The destination image in which pixels will be pasted.
		/// @param srcRect The boundaries in the source image from which to copy.
		/// @param dstVec The position in the destiniation image in which to paste.
		static void Blit(const Image& src, Image& dst, const RectangleI& srcRect, const Vector2I& dstVec);

		/// Fills the entire image with a single color.
		void Fill(uint8 color);

		/// Inverts the entire image.
		/// Makes the lightest pixels the darkest and the darkest the lightest.
		void Invert();

		/// Converts the image to a binary image.
		/// @param threshold The threshold value.
		void Threshold(uint8 threshold);

		// Operators

		uint8& operator() (unsigned int index);
		const uint8& operator() (unsigned int index) const;

		uint8& operator() (unsigned int x, unsigned int y, unsigned int channel = 0);
		const uint8& operator() (unsigned int x, unsigned int y, unsigned int channel = 0) const;

		// Getters

		unsigned int Width() const { return mWidth; }
		unsigned int Height() const { return mHeight; }
		unsigned int Channels() const { return mChannels; }

		Vector2I Size() const { return Vector2I((int)mWidth, (int)mHeight); }

		const std::vector<uint8>& Pixels() const { return mPixels; }

	private:

		unsigned int mWidth;		///< Image width.
		unsigned int mHeight;		///< Image height.
		unsigned int mChannels;		///< Number of color and alpha channels.

		std::vector<uint8> mPixels;	///< Raw image data.
	};
}
