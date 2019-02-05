// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include <vector>
#include <algorithm>

namespace BB
{
	/// A 2D array emulator which uses a single allocation.

	template<typename T>
	class Array2D
	{
	public:

		// Types

		using data_type					= std::vector<T>;
		using value_type				= typename std::vector<T>::value_type;
		using size_type					= typename std::vector<T>::size_type;
		using pointer					= typename std::vector<T>::pointer;
		using const_pointer				= typename std::vector<T>::const_pointer;
		using reference					= typename std::vector<T>::reference;
		using const_reference			= typename std::vector<T>::const_reference;
		using iterator					= typename std::vector<T>::iterator;
		using const_iterator			= typename std::vector<T>::const_iterator;
		using reverse_iterator			= typename std::vector<T>::reverse_iterator;
		using const_reverse_iterator	= typename std::vector<T>::const_reverse_iterator;

		// Constructors

		Array2D() = default;

		Array2D(size_type rows, size_type cols)
			: mRows(rows), mCols(cols), mData(rows * cols) {}

		Array2D(size_type rows, size_type cols, const_reference value)
			: mRows(rows), mCols(cols), mData(rows * cols, value) {}

		Array2D(const std::vector<double>& row)
			: mRows(1), mCols(row.size()), mData(row) {}

		// Iterators

		iterator begin() { return mData.begin(); }
		const_iterator begin() const { return mData.begin(); }
		const_iterator cbegin() const { return mData.cbegin(); }

		iterator end() { return mData.end(); }
		const_iterator end() const { return mData.end(); }
		const_iterator cend() const { return mData.cend(); }
		
		reverse_iterator rbegin() { return mData.rbegin(); }
		const_reverse_iterator rbegin() const { return mData.rbegin(); }
		const_reverse_iterator crbegin() const { return mData.crbegin(); }

		reverse_iterator rend() { return mData.rend(); }
		const_reverse_iterator rend() const { return mData.rend(); }
		const_reverse_iterator crend() const { return mData.crend(); }

		// Getters

		size_type Rows() const { return mRows; }
		size_type Cols() const { return mCols; }
		size_type Size() const { return mData.size(); }

		bool Empty() const { return mData.empty(); }

		// Operators

		reference operator() (const size_type idx) { return mData[idx]; }
		const_reference operator() (const size_type idx) const { return mData[idx]; }

		reference operator() (const size_type row, const size_type col) { return mData[mCols * row + col]; }
		const_reference operator() (const size_type row, const size_type col) const { return mData[mCols * row + col]; }

	private:

		size_type mRows;
		size_type mCols;
		data_type mData;

	private:

		template<typename Archive, typename T>
		friend void Serialize(Archive&, Array2D<T>&, unsigned int);
	};

	template<class T>
	bool operator== (const Array2D<T>& lhs, const Array2D<T>& rhs)
	{
		if (lhs.Rows() != rhs.Rows() || lhs.Cols() != rhs.Cols())
		{
			return false;
		}

		return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class T>
	bool operator!= (const Array2D<T>& lhs, const Array2D<T>& rhs)
	{
		return !(lhs == rhs);
	}

	// Serialization

	template<typename Archive, typename T>
	void Serialize(Archive& archive, Array2D<T>& a, unsigned int version)
	{
		archive & a.mRows & a.mCols & a.mData;
	}
}
