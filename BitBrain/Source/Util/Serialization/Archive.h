// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include <stdint.h>
#include <string>
#include <cassert>
#include <algorithm>

#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>

#include <exception>
#include <stdexcept>

#include "../CoreTypes.h"

namespace BB
{
	template <typename StreamType, bool Save>
	class Archive
	{
	public:

		const uint32 Magic = 0x41494442;
		const uint32 Version = 0;

	public:

		Archive(StreamType& stream) : mStream(stream)
		{
			if constexpr (Save)
			{
				*this << Magic << Version;
			}
			else
			{
				*this >> mMagic >> mVersion;
			}
			
			if(mMagic != Magic) throw std::runtime_error("Incompatible file.");
		}

	public:

		uint32 GetMagic() const
		{
			return mMagic;
		}
		
		uint32 GetVersion() const
		{
			return mVersion;
		}

	public:

		template <typename T>
		Archive& operator>> (T& t)
		{
			*this & t;
			return *this;
		}

		template <typename T>
		const Archive& operator<< (const T& t) const
		{
			*this & t;
			return *this;
		}

	public:

		template <typename T>
		Archive& operator& (T& t)
		{
			Serialize(*this, t, mVersion);
			return *this;
		}

		template <typename T>
		const Archive& operator& (const T& t) const
		{
			Serialize(*this, (T&)t, mVersion);
			return *this;
		}

		template <typename T, sizeT N>
		Archive& operator& (T(&t)[N])
		{
			uint32 length;
			*this & length;

			for (sizeT i = 0; i < N; i++)
			{
				*this & t[i];
			}

			return *this;
		}

		template <typename T, sizeT N>
		const Archive& operator& (const T(&t)[N]) const
		{
			uint32 length = N;
			*this & length;

			for (sizeT i = 0; i < N; i++)
			{
				*this & t[i];
			}

			return *this;
		}

		template <typename T1, typename T2>
		Archive& operator& (std::pair<T1, T2>& t)
		{
			*this & t.first & t.second;
			return *this;
		}

		template <typename T1, typename T2>
		const Archive& operator& (const std::pair<T1, T2>& t) const
		{
			*this & t.first & t.second;
			return *this;
		}

#define SerializePOD(type) \
        Archive& operator& (type& t) \
        { \
            mStream.read((char*)&t, sizeof(type)); \
            if(!mStream) throw std::runtime_error("Archive reading error."); \
            return *this; \
        } \
        const Archive& operator& (type t) const \
        { \
            mStream.write((const char*)&t, sizeof(type)); \
            return *this; \
        }

		SerializePOD(bool)
		SerializePOD(char)

		SerializePOD(int8)
		SerializePOD(int16)
		SerializePOD(int32)
		SerializePOD(int64)

		SerializePOD(uint8)
		SerializePOD(uint16)
		SerializePOD(uint32)
		SerializePOD(uint64)

		SerializePOD(float)
		SerializePOD(double)

#define SerializeSTL(type) \
        template <typename T> \
        Archive& operator&(type<T>& t) \
        { \
            uint32 length; \
            *this & length; \
            for(uint32 i = 0; i < length; i++) \
            { \
                T data; \
                *this & data; \
                t.insert(t.end(), data); \
            } \
            return *this; \
        } \
        template <typename T> \
        const Archive& operator&(const type<T>& t) const \
        { \
            uint32 length = (uint32)t.size(); \
            *this & length; \
            for(typename type<T>::const_iterator it = t.begin(); it != t.end(); it++) *this & *it; \
            return *this; \
        }

		SerializeSTL(std::vector)
		SerializeSTL(std::deque)
		SerializeSTL(std::list)
		SerializeSTL(std::set)
		SerializeSTL(std::multiset)

#define SerializeSTL2(type) \
        template <typename T1, typename T2> \
        Archive& operator&(type<T1, T2>& t) \
        { \
            uint32 length; \
            *this & length; \
            for(uint32 i = 0; i < length; i++) \
            { \
                std::pair<T1, T2> data; \
                *this & data; \
                t.insert(t.end(), data); \
            } \
            return *this; \
        } \
        template <typename T1, typename T2> \
        const Archive& operator&(const type<T1, T2>& t) const \
        { \
            uint32 length = (uint32)t.size(); \
            *this & length; \
            for(typename type<T1, T2>::const_iterator it = t.begin(); it != t.end(); it++) *this & *it; \
            return *this; \
        }

		SerializeSTL2(std::map)
		SerializeSTL2(std::multimap)

	private:

		uint32 mMagic = Magic;
		uint32 mVersion = Version;

		StreamType& mStream;
	};

	template<typename Archive, typename T>
	static void Serialize(Archive& archive, T& type, uint32 version)
	{
		type.Serialize(archive, version);
	}
}

#undef SerializePOD
#undef SerializeSTL
#undef SerializeSTL2
