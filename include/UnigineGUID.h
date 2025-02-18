/* Copyright (C) 2005-2025, UNIGINE. All rights reserved.
*
* This file is a part of the UNIGINE 2 SDK.
*
* Your use and / or redistribution of this software in source and / or
* binary form, with or without modification, is subject to: (i) your
* ongoing acceptance of and compliance with the terms and conditions of
* the UNIGINE License Agreement; and (ii) your inclusion of this notice
* in any version of this software that you use or redistribute.
* A copy of the UNIGINE License Agreement is available by contacting
* UNIGINE. at http://unigine.com/
*/

#pragma once

#include <UnigineBase.h>
#include "UnigineChecksum.h"
#include "UnigineString.h"
#include "UnigineMathLibCommon.h"

namespace Unigine
{

class UNIGINE_API UGUID
{
public:
	static const UGUID empty;

	static constexpr size_t NUM_VALUE_INT = 5;
	static constexpr size_t VALUE_SIZE = NUM_VALUE_INT * sizeof(int);
	static constexpr size_t HASH_SIZE = VALUE_SIZE * 2;

	using GUIDString = StringStack<HASH_SIZE + 1>;

	UNIGINE_INLINE UGUID() { clear(); }
	UNIGINE_INLINE explicit UGUID(const char *str)
	{
		clear();
		setString(str);
	}
	UNIGINE_INLINE explicit UGUID(const String &str) : UGUID(str.get()) {}
	UNIGINE_INLINE explicit UGUID(unsigned char(&value_)[VALUE_SIZE])
	{
		memcpy(value, value_, VALUE_SIZE);
	}
	UNIGINE_INLINE explicit UGUID(unsigned int(&value_)[NUM_VALUE_INT])
	{
		memcpy(value_int, value_, sizeof(value_int));
	}

	UNIGINE_INLINE UGUID(const UGUID &g)
	{
		memcpy(value_int, g.value_int, sizeof(value_int));
	}
	UNIGINE_INLINE UGUID &operator=(const UGUID &g)
	{
		memcpy(value_int, g.value_int, sizeof(value_int));
		return *this;
	}
	UNIGINE_INLINE UGUID &operator=(const char *str)
	{
		setString(str);
		return *this;
	}
	UNIGINE_INLINE UGUID &operator=(const String &str)
	{
		setString(str.get());
		return *this;
	}

	UNIGINE_INLINE bool operator==(const UGUID &g) const
	{
		return memcmp(value_int, g.value_int, sizeof(value_int)) == 0;
	}
	UNIGINE_INLINE bool operator!=(const UGUID &g) const
	{
		return memcmp(value_int, g.value_int, sizeof(value_int)) != 0;
	}
	UNIGINE_INLINE bool operator<=(const UGUID &g) const
	{
		return *this == g || *this > g;
	}
	UNIGINE_INLINE bool operator>=(const UGUID &g) const
	{
		return *this == g || *this > g;
	}
	UNIGINE_INLINE bool operator<(const UGUID &g) const
	{
		return memcmp(value_int, g.value_int, sizeof(value_int)) < 0;
	}
	UNIGINE_INLINE bool operator>(const UGUID &g) const
	{
		return memcmp(value_int, g.value_int, sizeof(value_int)) > 0;
	}

	void generate();
	UNIGINE_INLINE void generate(const char *str)
	{
		Checksum::SHA1(value_int, str, static_cast<int>(strlen(str)));
	}
	UNIGINE_INLINE void generate(int &seed_)
	{
		for (size_t i = 0; i < NUM_VALUE_INT; ++i)
			value_int[i] = seed_ = (unsigned int)((unsigned long long)seed_ * 1664525 + 1013904223); // Numerical Recipes: The Art of Scientific Computing
	}
	UNIGINE_INLINE void generate(const void *data, int size)
	{
		Checksum::SHA1(value_int, data, size);
	}

	UNIGINE_INLINE const unsigned char *getValue() const { return value; }
	GUIDString makeString() const
	{
		GUIDString ret;
		if (isEmpty())
			return ret;

		ret.resize(HASH_SIZE);
		write_string(ret.getRaw());
		return ret;
	}
	void setString(const char *str)
	{
		if (!str || !*str || strlen(str) != HASH_SIZE)
		{
			clear();
			return;
		}

		read_string(str);
	}

	UNIGINE_INLINE void clear()
	{
		memset(value_int, 0, sizeof(value_int));
	}
	UNIGINE_INLINE bool isEmpty() const { return memcmp(UGUID::empty.value_int, value_int, sizeof(value_int)) == 0; }
	UNIGINE_INLINE bool isValid() const { return !isEmpty(); }

	UNIGINE_INLINE unsigned int hash() const
	{
		return (((value_int[0] ^ value_int[1]) << 5) ^ value_int[2] ^ value_int[3] ^ value_int[4]);
	}

private:

	void read_string(const char *str)
	{
		int index = 0;
		while (*str)
		{
			unsigned int &value = value_int[index++];
			int value_size = 8;
			while (value_size--)
			{
				char c = *str++;
				if (c >= '0' && c <= '9')
					value = (value << 4) + (c - '0');
				else if (c >= 'a' && c <= 'f')
					value = (value << 4) + (c - 'a' + 10);
				else if (c >= 'A' && c <= 'F')
					value = (value << 4) + (c - 'A' + 10);
			}
		}
	}
	void write_string(char *dst) const
	{
		const unsigned int radix = 16;
		const char *digits = "0123456789abcdef";

		char *p = dst + HASH_SIZE;
		*p = '\0';

		int size = NUM_VALUE_INT;
		while (size--)
		{
			unsigned int value = value_int[size];
			int value_size = 8;
			while (value_size--)
			{
				*--p = digits[value & (radix - 1)];
				value /= radix;
			}
		}
	}

	union
	{
		unsigned char value[VALUE_SIZE];
		unsigned int value_int[NUM_VALUE_INT];
	};
};

static_assert(sizeof(UGUID) == 20, "UGUID size is changed");

template<typename Type>
struct Hasher;

template<>
struct Hasher<UGUID>
{
	using HashType = unsigned int;
	UNIGINE_INLINE static HashType create(const UGUID &v) { return v.hash(); }
};

} // namespace
