// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

#pragma once

#include <cmath>

namespace BB
{
	/// A collection of common math functions and constants.

	class Math
	{
	public:

		// Constants

		template<typename T>
		static constexpr T Pi = T(3.14159265358979323846);

		template<typename T>
		static constexpr T TwoPi = Pi<T> * T(2);

		template<typename T>
		static constexpr T HalfPi = Pi<T> / T(2);

		template<typename T>
		static constexpr T Sqrt2 = T(1.41421356237309504880);

		template<typename T>
		static constexpr T Deg2Rad = Pi<T> / T(180);

		template<typename T>
		static constexpr T Rad2Deg = T(180) / Pi<T>;

		// Functions

		/// Square root.
		/// @return The square root of x.
		template<typename T>
		static T Sqrt(T x)
		{
			return T(std::sqrt(float(x)));
		}

		/// Modulus.
		/// @return The remainder of (numerator / denominator).
		template<typename T>
		static T Mod(T numerator, T denominator)
		{
			return T(std::fmod(float(numerator), float(denominator)));
		}

		/// Power.
		/// @return base raised to the power exponent.
		template<typename T>
		static T Pow(T base, T exponent)
		{
			return T(std::pow(float(base), float(exponent)));
		}

		/// Rounds a value up.
		/// @return The smallest integral value that is not less than x.
		template<typename T>
		static T Ceil(T x)
		{
			return T(std::ceil(float(x)));
		}

		/// Rounds a value down.
		/// @return The largest integral value that is not greater than x.
		template<typename T>
		static T Floor(T x)
		{
			return T(std::floor(float(x)));
		}

		// Function templates

		/// Returns the absolute value of x.
		template <typename T>
		static inline constexpr T Abs(const T& x)
		{
			return (x >= T(0)) ? x : -x;
		}

		/// Returns the smallest of two values.
		template <typename T>
		static inline constexpr T Min(const T& a, const T& b)
		{
			return (a < b) ? a : b;
		}

		/// Returns the largest of two values.
		template <typename T>
		static inline constexpr T Max(const T& a, const T& b)
		{
			return (a > b) ? a : b;
		}

		/// Clamps a value within the range [min, max].
		/// @param x The value to be clamped.
		/// @param min The minimum of the range.
		/// @param max The maximum of the range.
		/// @return Returns the value in the range [min, max].
		template <typename T>
		static inline constexpr T Clamp(const T& x, const T& min, const T& max)
		{
			return Max(min, Min(max, x));
		}

		/// Remaps a number from one range to another.
		/// The minimum of either range may be larger or smaller than the maximum.
		/// This allows reversing a range of numbers.
		/// Negative numbers aren't a problem either.
		/// @param x The value to remap.
		/// @param inMin The minimum of the value's current range.
		/// @param inMax The maximum of the value's current range.
		/// @param outMin The minimum of the value's target range.
		/// @param outMax The maximum of the value's target range.
		/// @return The mapped value.
		template <typename T>
		static inline constexpr T Map(const T& x, const T& inMin, const T& inMax, const T& outMin, const T& outMax)
		{
			return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
		}

		/// Interpolates between two values.
		/// @param min,max Input value.
		/// @param t Interpolant specified in the range [0, 1].
		/// @return Returns the result of linear interpolation.
		template <typename T>
		static inline constexpr T Lerp(const T& min, const T& max, const T& t)
		{
			return min + t * (max - min);
		}

		/// Returns the sign of x.
		/// @param x The value to get the sign from.
		/// @return Returns 1 if the sign is positive, -1 if it is negative.
		template <typename T>
		static inline constexpr T Sign(const T& x)
		{
			return (x < T(0)) ? T(-1) : T(1);
		}

		/// Solves a quadtratic equation. Ax� + Bx + C = 0.
		/// @param a,b,c The equation parameters.
		/// @param root1,root2 The root that was found.
		/// @return The number of roots that were found.
		static int SolveQuadratic(float a, float b, float c, float& root1, float& root2)
		{
			if (a == 0.0f) return 0;

			float discriminant = b * b - 4.0f * a * c;

			if (discriminant < 0.0f) return 0;

			float sqrt = Sqrt(discriminant);

			root1 = (-b + sqrt) / (2.0f * a);
			root2 = (-b - sqrt) / (2.0f * a);

			return (root1 == root2) ? 1 : 2;
		}
	};
}
