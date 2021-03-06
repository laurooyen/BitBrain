// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/CoreTypes.h"

#include "../Utility/Math/Vector2.h"
#include "../Utility/Math/Rectangle.h"

#include <vector>

namespace BB
{
	/// Class representing a 2D image.

	class Image
	{
	public:

		// Constructors

		/// Creates an empty image.
		Image();

		/// Creates a new black image.
		/// @param w The width of the image.
		/// @param h The height of the image.
		/// @param channels The desired amount of channels to load. 1 = G, 2 = GA, 3 = RGB, 4 = RGBA.
		Image(unsigned int w, unsigned int h, unsigned int channels = 1);

		/// Loads an image file from memory.
		/// @param data The raw image data in row-major format.
		/// @param w The width of the image.
		/// @param h The height of the image.
		/// @param channels The desired amount of channels to load. 1 = G, 2 = GA, 3 = RGB, 4 = RGBA.
		Image(const std::vector<uint8>& data, unsigned int w, unsigned int h, unsigned int channels = 1);

		/// Loads an image file from disk.
		/// @param filename The filename of the image.
		/// @param channels The desired amount of channels to load. 1 = G, 2 = GA, 3 = RGB, 4 = RGBA.
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
		/// This function assumes that the values it gets passed are valid.
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

		/// Converts the image to a binary image.
		/// @param size Size of the pixel area that is used to calculate a threshold value for the pixel.
		/// @param constant Constant subtracted from the mean pixel value.
		void AdaptiveThreshold(uint8 size, uint8 constant);

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
