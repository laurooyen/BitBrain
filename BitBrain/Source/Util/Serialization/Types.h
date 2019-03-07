// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

namespace BB
{
	// Array2D

	template<typename T>
	class Array2D;

	template<typename Archive, typename T>
	void Serialize(Archive& archive, Array2D<T>& a, unsigned int version)
	{
		archive & a.mRows & a.mCols & a.mData;
	}

	// Matrix

	class Matrix;

	template<typename Archive>
	void Serialize(Archive& archive, Matrix& m, unsigned int version)
	{
		archive & m.mElements;
	}

	// AF

	enum class AF;

	template<typename Archive>
	void Serialize(Archive& archive, AF& af, unsigned int version)
	{
		archive & reinterpret_cast<unsigned int &>(af);
	}

	// CF

	enum class CF;

	template<typename Archive>
	void Serialize(Archive& archive, CF& cf, unsigned int version)
	{
		archive & reinterpret_cast<unsigned int &>(cf);
	}

	// Network

	class Network;

	template<typename Archive>
	void Serialize(Archive& archive, Network& n, unsigned int version)
	{
		archive & n.mEpoch & n.mAccuracyTest & n.mAccuracyTrain;
		archive & n.mLayers & n.af & n.cf;
		archive & n.batchSize & n.batchSizeFactor & n.batchSizeMax;
		archive & n.learningRate & n.learningRateFactor & n.learningRateMin;
		archive & n.lambda & n.mu;
		archive & n.L & n.W & n.B;
	}
}
