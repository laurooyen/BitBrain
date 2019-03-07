// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

namespace BB
{
	template<typename T>
	class TVector2;

	/// A rectangle.

	template<typename T>
	class TRectangle
	{
	private:

		T xMin, yMin;
		T xMax, yMax;

	public:

		// Constructors

		TRectangle();
		TRectangle(T w, T h);
		TRectangle(T x, T y, T w, T h);
		TRectangle(const TVector2<T>& size);
		TRectangle(const TVector2<T>& topLeft, const TVector2<T>& size);

		// Predefined rectangles

		static const TRectangle Zero;

		// Calculations

		T X() const;
		T Y() const;
		T Width() const;
		T Height() const;

		void X(T x);
		void Y(T y);
		void Width(T w);
		void Height(T h);

		T Left() const;
		T Right() const;
		T Top() const;
		T Bottom() const;

		void Left(T x);
		void Right(T x);
		void Top(T x);
		void Bottom(T x);

		TVector2<T> Center() const;
		TVector2<T> TopLeft() const;
		TVector2<T> TopRight() const;
		TVector2<T> BottomLeft() const;
		TVector2<T> BottomRight() const;

		void Center(const TVector2<T>& v);
		void TopLeft(const TVector2<T>& v);
		void TopRight(const TVector2<T>& v);
		void BottomLeft(const TVector2<T>& v);
		void BottomRight(const TVector2<T>& v);

		TVector2<T> Size() const;

		void Size(const TVector2<T>& s);

		void Expand(T x, T y);

		// Relational operators

		bool operator== (const TRectangle& rhs) const;
		bool operator!= (const TRectangle& rhs) const;
	};

	// Type aliases

	using Rectangle = TRectangle<float>;

	using RectangleF = TRectangle<float>;
	using RectangleD = TRectangle<double>;
	using RectangleI = TRectangle<int>;
}
