// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#include "Rectangle.h"

#include "Vector2.h"
#include "Functions.h"

namespace BB
{
	// Constructors

	template<typename T>
	TRectangle<T>::TRectangle()
		: xMin(T(0)), yMin(T(0)), xMax(T(0)), yMax(T(0)) {}

	template<typename T>
	TRectangle<T>::TRectangle(T w, T h)
		: xMin(T(0)), yMin(T(0)), xMax(w), yMax(h) {}

	template<typename T>
	TRectangle<T>::TRectangle(T x, T y, T w, T h)
		: xMin(x), yMin(y), xMax(x + w), yMax(y + h) {}

	template<typename T>
	TRectangle<T>::TRectangle(const TVector2<T>& size)
		: xMin(T(0)), yMin(T(0)), xMax(size.x), yMax(size.y) {}

	template<typename T>
	TRectangle<T>::TRectangle(const TVector2<T>& topLeft, const TVector2<T>& size)
		: xMin(topLeft.x), yMin(topLeft.y), xMax(topLeft.x + size.x), yMax(topLeft.y + size.y) {}

	// Predefined rectangles

	template<typename T>
	const TRectangle<T> TRectangle<T>::Zero(T(0), T(0), T(0), T(0));

	// Calculations

	template<typename T>
	T TRectangle<T>::X() const
	{
		return xMin;
	}

	template<typename T>
	T TRectangle<T>::Y() const
	{
		return yMin;
	}

	template<typename T>
	T TRectangle<T>::Width() const
	{
		return xMax - xMin;
	}

	template<typename T>
	T TRectangle<T>::Height() const
	{
		return yMax - yMin;
	}

	template<typename T>
	void TRectangle<T>::X(T x)
	{
		xMin = x;
	}

	template<typename T>
	void TRectangle<T>::Y(T y)
	{
		yMin = y;
	}

	template<typename T>
	void TRectangle<T>::Width(T w)
	{
		xMax = xMin + w;
	}

	template<typename T>
	void TRectangle<T>::Height(T h)
	{
		yMax = yMin + h;
	}

	template<typename T>
	T TRectangle<T>::Left() const
	{
		return xMin;
	}

	template<typename T>
	T TRectangle<T>::Right() const
	{
		return xMax;
	}

	template<typename T>
	T TRectangle<T>::Top() const
	{
		return yMin;
	}

	template<typename T>
	T TRectangle<T>::Bottom() const
	{
		return yMax;
	}

	template<typename T>
	void TRectangle<T>::Left(T x)
	{
		xMin = x;
	}

	template<typename T>
	void TRectangle<T>::Right(T x)
	{
		xMax = x;
	}

	template<typename T>
	void TRectangle<T>::Top(T x)
	{
		yMin = x;
	}

	template<typename T>
	void TRectangle<T>::Bottom(T x)
	{
		yMax = x;
	}

	template<typename T>
	TVector2<T> TRectangle<T>::Center() const
	{
		T x = (xMin + xMax) / T(2);
		T y = (yMin + yMax) / T(2);
		return TVector2(x, y);
	}

	template<typename T>
	TVector2<T> TRectangle<T>::TopLeft() const
	{
		return TVector2(xMin, yMin);
	}

	template<typename T>
	TVector2<T> TRectangle<T>::TopRight() const
	{
		return TVector2(xMax, yMin);
	}

	template<typename T>
	TVector2<T> TRectangle<T>::BottomLeft() const
	{
		return TVector2(xMin, yMax);
	}

	template<typename T>
	TVector2<T> TRectangle<T>::BottomRight() const
	{
		return TVector2(xMax, yMax);
	}

	template<typename T>
	void TRectangle<T>::Center(const TVector2<T>& v)
	{
		T w = xMax - xMin;
		T h = yMax - yMin;
		xMin = v.x - (w / T(2));
		yMin = v.y - (h / T(2));
		xMax = xMin + w;
		yMax = yMin + h;
	}

	template<typename T>
	void TRectangle<T>::TopLeft(const TVector2<T>& v)
	{
		xMin = v.x;
		yMin = v.y;
	}

	template<typename T>
	void TRectangle<T>::TopRight(const TVector2<T>& v)
	{
		xMax = v.x;
		yMin = v.y;
	}

	template<typename T>
	void TRectangle<T>::BottomLeft(const TVector2<T>& v)
	{
		xMin = v.x;
		yMax = v.y;
	}

	template<typename T>
	void TRectangle<T>::BottomRight(const TVector2<T>& v)
	{
		xMax = v.x;
		yMax = v.y;
	}

	template<typename T>
	TVector2<T> TRectangle<T>::Size() const
	{
		return TVector2(xMax - xMin, yMax - yMin);
	}

	template<typename T>
	void TRectangle<T>::Size(const TVector2<T>& s)
	{
		xMax = xMin + s.x;
		yMax = yMin + s.y;
	}

	template<typename T>
	void TRectangle<T>::Expand(T x, T y)
	{
		xMin = Math::Min(xMin, x);
		yMin = Math::Min(yMin, y);
		xMax = Math::Max(xMax, x);
		yMax = Math::Max(yMax, y);
	}

	// Relational operators

	template<typename T>
	bool TRectangle<T>::operator== (const TRectangle& rhs) const
	{
		return xMin == rhs.xMin && yMin == rhs.yMin && xMax == rhs.xMax && yMax == rhs.yMax;
	}

	template<typename T>
	bool TRectangle<T>::operator!= (const TRectangle& rhs) const
	{
		return xMin != rhs.xMin || yMin != rhs.yMin || xMax != rhs.xMax || yMax != rhs.yMax;
	}

	// Template instantiation

	template class TRectangle<float>;
	template class TRectangle<double>;
	template class TRectangle<int>;
}
