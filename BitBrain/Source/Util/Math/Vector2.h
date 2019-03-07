// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

namespace BB
{
	/// A two-dimensional vector.

	template<typename T>
	class TVector2
	{
	public:

		union
		{
			T elements[2];
			struct { T x, y; };
		};

	public:

		// Constructors

		TVector2();
		TVector2(T xy);
		TVector2(T x, T y);

		// Predefined vectors

		static const TVector2 One;
		static const TVector2 Zero;
		static const TVector2 UnitX;
		static const TVector2 UnitY;

		// Calculations

		/// Returns the length (magnitude) of the vector.
		T Length() const;

		/// Returns the squared length (magnitude) of the vector.
		T LengthSquared() const;

		/// Returns the normalized vector.
		TVector2 Normalized() const;

		/// Returns the dot (scalar) product of 2 vectors.
		static T Dot(const TVector2& lhs, const TVector2& rhs);

		/// Returns the distance between 2 vectors.
		static T Distance(const TVector2& lhs, const TVector2& rhs);

		// Operators

		TVector2 operator- () const;

		friend TVector2 operator* (T lhs, const TVector2& rhs);
		friend TVector2 operator/ (T lhs, const TVector2& rhs);

		// Arithmetic operators

		TVector2 operator+ (const TVector2& rhs) const;
		TVector2 operator- (const TVector2& rhs) const;

		TVector2 operator* (T rhs) const;
		TVector2 operator/ (T rhs) const;

		// Assignment operators

		TVector2& operator+= (const TVector2& rhs);
		TVector2& operator-= (const TVector2& rhs);

		TVector2& operator*= (T rhs);
		TVector2& operator/= (T rhs);

		// Relational operators

		bool operator< (const TVector2& rhs) const;
		bool operator<= (const TVector2& rhs) const;
		bool operator== (const TVector2& rhs) const;
		bool operator!= (const TVector2& rhs) const;
		bool operator>= (const TVector2& rhs) const;
		bool operator> (const TVector2& rhs) const;
	};

	// Type aliases

	using Vector2 = TVector2<float>;

	using Vector2F = TVector2<float>;
	using Vector2D = TVector2<double>;
	using Vector2I = TVector2<int>;
}
