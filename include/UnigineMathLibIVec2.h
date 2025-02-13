/* Copyright (C) 2005-2024, UNIGINE. All rights reserved.
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
#include "UnigineMathLibCommon.h"
#include "UnigineMathLibVec2.h"
#include "UnigineMathLibDVec2.h"

namespace Unigine
{
namespace Math
{

struct alignas(8) ivec2
{
	UNIGINE_INLINE constexpr ivec2(int v, ConstexprTag): x(v), y(v) {}

	/// <summary>Default constructor. Produces a zero vector.</summary>
	UNIGINE_INLINE ivec2(): x(0), y(0)
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}
	/// <summary>Constructor. Initializes the vector using the given values.</summary>
	UNIGINE_INLINE ivec2(int x, int y): x(x), y(y)
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}
	/// <summary>Constructor. Initializes the vector using a given value: x=v, y=v.</summary>
	UNIGINE_INLINE explicit ivec2(int v): x(v), y(v)
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}
	/// <summary>Constructor. Initializes the vector using a given pointer to the array of elements: x=v[0], y=v[1].</summary>
	UNIGINE_INLINE explicit ivec2(const int *v): x(v[0]), y(v[1])
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}
	/// <summary>Constructor. Initializes the vector using a given source vector.</summary>
	UNIGINE_INLINE explicit ivec2(const dvec2 &v): x(toInt(v.x)), y(toInt(v.y))
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}
	/// <summary>Constructor. Initializes the vector using a given source vector.</summary>
	UNIGINE_INLINE explicit ivec2(const vec2 &v): x(toInt(v.x)), y(toInt(v.y))
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}
	/// <summary>Constructor. Initializes the vector by copying a given source vector.</summary>
	UNIGINE_INLINE ivec2(const ivec2 & v): long_v(v.long_v)
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}
	
	/// <summary>Sets the vector components equal to specified scalar value: x=val, y=val.</summary>
	UNIGINE_INLINE void set(int val)
	{
		x = val;
		y = val;
	}
	/// <summary>Sets the vector by components.</summary>
	UNIGINE_INLINE void set(int x_, int y_)
	{
		x = x_;
		y = y_;
	}
	/// <summary>Sets the vector equal to the specified source vector.</summary>
	UNIGINE_INLINE void set(const ivec2 &val)
	{
		long_v = val.long_v;
	}
	/// <summary>Sets the vector using the array of elements: x=val[0], y=val[1].</summary>
	UNIGINE_INLINE void set(const int *val)
	{
		x = val[0];
		y = val[1];
	}

	/// <summary>Returns the pointer to the array of elements: val[0]=x, val[1]=y.</summary>
	UNIGINE_INLINE void get(int *val) const
	{
		val[0] = x;
		val[1] = y;
	}
	/// <summary>Returns the pointer to the vector.</summary>
	UNIGINE_INLINE int *get() { return v; }
	/// <summary>Returns the constant pointer to the vector.</summary>
	UNIGINE_INLINE const int *get() const { return v; }

	/// <summary>Performs type conversion to int *.</summary>
	UNIGINE_INLINE operator int *() { return v; }
	/// <summary>Performs type conversion to const int *.</summary>
	UNIGINE_INLINE operator const int *() const { return v; }
	/// <summary>Performs type conversion to void *.</summary>
	UNIGINE_INLINE operator void *() { return v; }
	/// <summary>Performs type conversion to const void *.</summary>
	UNIGINE_INLINE operator const void *() const { return v; }

	/// <summary>Performs array access to the vector item reference by using given item index.</summary>
	UNIGINE_INLINE int &operator[](int i)
	{
		assert((unsigned int)i < 2 && "ivec2::operator[](): bad index");
		return v[i];
	}
	/// <summary>Performs array access to the vector item by using given item index.</summary>
	UNIGINE_INLINE int operator[](int i) const
	{
		assert((unsigned int)i < 2 && "ivec2::operator[](): bad index");
		return v[i];
	}

	/// <summary>Performs vector assignment. Destination vector = Source vector.</summary>
	UNIGINE_INLINE ivec2 &operator=(const ivec2 &val) { long_v = val.long_v; return *this; }
	/// <summary>Performs vector negation.</summary>
	UNIGINE_INLINE ivec2 operator-() const { return ivec2(-x, -y); }

	/// <summary>Returns the result of multiplication of all vector component values.</summary>
	UNIGINE_INLINE int mul() const { return x * y; }
	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(int v) { x *= v; y *= v; }
	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(const ivec2 &v) { x *= v.x; y *= v.y; }
	/// <summary>Performs scalar multiplication.</summary>
	UNIGINE_INLINE ivec2 &operator*=(int v) { mul(v); return *this; }
	/// <summary>Performs vector multiplication.</summary>
	UNIGINE_INLINE ivec2 &operator*=(const ivec2 &v) { mul(v); return *this; }

	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(int v) { x /= v; y /= v; }
	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(const ivec2 &v) { x /= v.x; y /= v.y; }
	/// <summary>Performs component-wise division of the vector by the scalar. Implemented using the calculation of inverse scalar value with subsequent component-wise multiplication.</summary>
	UNIGINE_INLINE ivec2 &operator/=(int v) { div(v); return *this; }
	/// <summary>Performs component-wise division of vectors.</summary>
	UNIGINE_INLINE ivec2 &operator/=(const ivec2 &v) { div(v); return *this; }

	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE void sub(int v) { x -= v; y -= v; }
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE void sub(const ivec2 &v) { x -= v.x; y -= v.y; }
	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE ivec2 &operator-=(int v) { add(v); return *this; }
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE ivec2 &operator-=(const ivec2 &v) { sub(v); return *this; }

	/// <summary>Returns the sum of vector components.</summary>
	UNIGINE_INLINE int sum() const { return x + y; }
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE void add(int v) { x += v; y += v; }
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE void add(const ivec2 &v) { x += v.x; y += v.y; }
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE ivec2 &operator+=(int v) { add(v); return *this; }
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE ivec2 &operator+=(const ivec2 &v) { add(v); return *this; }

	/// <summary>Shifts each component bitwise to the left by the specified value.</summary>
	UNIGINE_INLINE void shiftLeft(int v) { x <<= v; y <<= v; }
	/// <summary>Shifts each component bitwise to the left by the specified value.</summary>
	UNIGINE_INLINE void shiftLeft(const ivec2 &v) { x <<= v.x; y <<= v.y; }
	/// <summary>Shifts each component bitwise to the left by the specified value.</summary>
	UNIGINE_INLINE ivec2 &operator<<=(int v) { shiftLeft(v); return *this; }
	/// <summary>Shifts each component bitwise to the left by the specified value.</summary>
	UNIGINE_INLINE ivec2 &operator<<=(const ivec2 &v) { shiftLeft(v); return *this; }
	
	/// <summary>Shifts each component bitwise to the right by the specified value.</summary>
	UNIGINE_INLINE void shiftRight(int v) { x >>= v; y >>= v; }
	/// <summary>Shifts each component bitwise to the right by the specified value.</summary>
	UNIGINE_INLINE void shiftRight(const ivec2 &v) { x >>= v.x; y >>= v.y; }
	/// <summary>Shifts each component bitwise to the right by the specified value.</summary>
	UNIGINE_INLINE ivec2 &operator>>=(int v) { shiftRight(v); return *this; }
	/// <summary>Shifts each component bitwise to the right by the specified value.</summary>
	UNIGINE_INLINE ivec2 &operator>>=(const ivec2 &v) { shiftRight(v); return *this; }

	/// <summary>Returns the squared length of the vector.</summary>
	UNIGINE_INLINE int length2() const { return x * x + y * y; }

	/// <summary>Returns the absolute values of the vector components.</summary>
	UNIGINE_INLINE ivec2 &abs()
	{
		x = Math::abs(x);
		y = Math::abs(y);
		return *this;
	}

	/// <summary>Compares all components of the vector and returns the greatest value.</summary>
	UNIGINE_INLINE int max() const { return Math::max(x, y); }
	/// <summary>Compares all components of the vector and returns the smallest value.</summary>
	UNIGINE_INLINE int min() const { return Math::min(x, y); }

	/// <summary>Returns a 64-bit hash generated for the vector.</summary>
	UNIGINE_INLINE unsigned long long hash64() const { return long_v; }
	/// <summary>Returns a hash obtained by mixing the hash values of vector components.</summary>
	UNIGINE_INLINE unsigned int hash() const { return hashCombine(x, y); }

	union
	{
		struct
		{
			int x, y;
		};
		int v[2];
		long long long_v;

		#ifdef USE_SSE
			__m64 vec;
		#endif
	};
};

constexpr ivec2 ivec2_zero(0, ConstexprTag{});
constexpr ivec2 ivec2_one(1, ConstexprTag{});

/// <summary>Calculates the squared length of a given vector. This method is much faster than length() - the calculation is basically the same only without the slow Sqrt call. If you are using lengths simply to compare distances, then it is faster to compare squared lengths against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE int length2(const ivec2 &v) { return v.length2(); }

/// <summary>Compares two vectors according to the degree of precision equal to 1.0e-6f.</summary>
UNIGINE_INLINE bool compare(const ivec2 &v0, const ivec2 &v1) { return v0.long_v == v1.long_v; }
/// <summary>Vector equal comparison.</summary>
UNIGINE_INLINE bool operator==(const ivec2 &v0, const ivec2 &v1) { return v0.long_v == v1.long_v; }
/// <summary>Vector not equal comparison.</summary>
UNIGINE_INLINE bool operator!=(const ivec2 &v0, const ivec2 &v1) { return v0.long_v != v1.long_v; }

/// <summary>Vector less than comparison.</summary>
UNIGINE_INLINE bool operator<(const ivec2 &v0, const ivec2 &v1) { return v0.long_v < v1.long_v; }
/// <summary>Vector greater than comparison.</summary>
UNIGINE_INLINE bool operator>(const ivec2 &v0, const ivec2 &v1) { return v0.long_v > v1.long_v; }

/// <summary>Vector less than or equal comparison.</summary>
UNIGINE_INLINE bool operator>=(const ivec2 &v0, const ivec2 &v1) { return v0.long_v >= v1.long_v; }
/// <summary>Vector greater than or equal comparison.</summary>
UNIGINE_INLINE bool operator<=(const ivec2 &v0, const ivec2 &v1) { return v0.long_v <= v1.long_v; }

/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec2 &mul(ivec2 &ret, const ivec2 &v0, int v1)
{
	ret.x = v0.x * v1;
	ret.y = v0.y * v1;
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec2 &mul(ivec2 &ret, const ivec2 &v0, const ivec2 &v1)
{
	ret.x = v0.x * v1.x;
	ret.y = v0.y * v1.y;
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value.</summary>
UNIGINE_INLINE ivec2 mul(const ivec2 &v0, int v1)
{
	ivec2 ret;
	return mul(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise multiplication of two vectors.</summary>
UNIGINE_INLINE ivec2 mul(const ivec2 &v0, const ivec2 &v1)
{
	ivec2 ret;
	return mul(ret, v0, v1);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE ivec2 operator*(const ivec2 &v0, int v1) { return mul(v0, v1); }
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE ivec2 operator*(const ivec2 &v0, const ivec2 &v1) { return mul(v0, v1); }

/// <summary>Returns the result of a component-wise division of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec2 &div(ivec2 &ret, const ivec2 &v0, int v1)
{
	ret.x = v0.x / v1;
	ret.y = v0.y / v1;
	return ret;
}
/// <summary>Returns the result of a component-wise division of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec2 &div(ivec2 &ret, const ivec2 &v0, const ivec2 &v1)
{
	ret.x = v0.x / v1.x;
	ret.y = v0.y / v1.y;
	return ret;
}
/// <summary>Returns the result of a component-wise division of a vector by a scalar value.</summary>
UNIGINE_INLINE ivec2 div(const ivec2 &v0, int v1)
{
	ivec2 ret;
	return div(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise division of two vectors.</summary>
UNIGINE_INLINE ivec2 div(const ivec2 &v0, const ivec2 &v1)
{
	ivec2 ret;
	return div(ret, v0, v1);
}
/// <summary>Division operator.</summary>
UNIGINE_INLINE ivec2 operator/(const ivec2 &v0, int v1) { return div(v0, v1); }
/// <summary>Division operator.</summary>
UNIGINE_INLINE ivec2 operator/(const ivec2 &v0, const ivec2 &v1) { return div(v0, v1); }

/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec2 &mod(ivec2 &ret, const ivec2 &v0, int v1)
{
	ret.x = v0.x % v1;
	ret.y = v0.y % v1;
	return ret;
}
/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec2 &mod(ivec2 &ret, const ivec2 &v0, const ivec2 &v1)
{
	ret.x = v0.x % v1.x;
	ret.y = v0.y % v1.y;
	return ret;
}
/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec2 mod(const ivec2 &v0, int v1)
{
	ivec2 ret;
	return mod(ret, v0, v1);
}
/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec2 mod(const ivec2 &v0, const ivec2 &v1)
{
	ivec2 ret;
	return mod(ret, v0, v1);
}
/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec2 operator%(const ivec2 &v0, int v1) { return mod(v0, v1); }
/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec2 operator%(const ivec2 &v0, const ivec2 &v1) { return mod(v0, v1); }

/// <summary>Returns the result of a component-wise addition of a vector with a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec2 &add(ivec2 &ret, const ivec2 &v0, int v1)
{
	ret.x = v0.x + v1;
	ret.y = v0.y + v1;
	return ret;
}
/// <summary>Returns the result of a component-wise addition of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec2 &add(ivec2 &ret, const ivec2 &v0, const ivec2 &v1)
{
	ret.x = v0.x + v1.x;
	ret.y = v0.y + v1.y;
	return ret;
}
/// <summary>Returns the result of a component-wise addition of a vector with a scalar value.</summary>
UNIGINE_INLINE ivec2 add(const ivec2 &v0, int v1)
{
	ivec2 ret;
	return add(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise addition of two vectors.</summary>
UNIGINE_INLINE ivec2 add(const ivec2 &v0, const ivec2 &v1)
{
	ivec2 ret;
	return add(ret, v0, v1);
}
/// <summary>Addition operator.</summary>
UNIGINE_INLINE ivec2 operator+(const ivec2 &v0, int v1) { return add(v0, v1); }
/// <summary>Addition operator.</summary>
UNIGINE_INLINE ivec2 operator+(const ivec2 &v0, const ivec2 &v1) { return add(v0, v1); }

/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec2 &sub(ivec2 &ret, const ivec2 &v0, int v1)
{
	ret.x = v0.x - v1;
	ret.y = v0.y - v1;
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1) by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec2 &sub(ivec2 &ret, const ivec2 &v0, const ivec2 &v1)
{
	ret.x = v0.x - v1.x;
	ret.y = v0.y - v1.y;
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector.</summary>
UNIGINE_INLINE ivec2 sub(const ivec2 &v0, int v1)
{
	ivec2 ret;
	return sub(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1).</summary>
UNIGINE_INLINE ivec2 sub(const ivec2 &v0, const ivec2 &v1)
{
	ivec2 ret;
	return sub(ret, v0, v1);
}
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE ivec2 operator-(const ivec2 &v0, int v1) { return sub(v0, v1); }
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE ivec2 operator-(const ivec2 &v0, const ivec2 &v1) { return sub(v0, v1); }

/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 &shiftLeft(ivec2 &ret, const ivec2 &v0, int v1)
{
	ret.x = v0.x << v1;
	ret.y = v0.y << v1;
	return ret;
}
/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 &shiftLeft(ivec2 &ret, const ivec2 &v0, const ivec2 &v1)
{
	ret.x = v0.x << v1.x;
	ret.y = v0.y << v1.y;
	return ret;
}
/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 shiftLeft(const ivec2 &v0, int v1)
{
	ivec2 ret;
	return shiftLeft(ret, v0, v1);
}
/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 shiftLeft(const ivec2 &v0, const ivec2 &v1)
{
	ivec2 ret;
	return shiftLeft(ret, v0, v1);
}
/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 operator<<(const ivec2 &v0, int v1) { return shiftLeft(v0, v1); }
/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 operator<<(const ivec2 &v0, const ivec2 &v1) { return shiftLeft(v0, v1); }

/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 &shiftRight(ivec2 &ret, const ivec2 &v0, int v1)
{
	ret.x = v0.x >> v1;
	ret.y = v0.y >> v1;
	return ret;
}
/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 &shiftRight(ivec2 &ret, const ivec2 &v0, const ivec2 &v1)
{
	ret.x = v0.x >> v1.x;
	ret.y = v0.y >> v1.y;
	return ret;
}
/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 shiftRight(const ivec2 &v0, int v1)
{
	ivec2 ret;
	return shiftRight(ret, v0, v1);
}
/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 shiftRight(const ivec2 &v0, const ivec2 &v1)
{
	ivec2 ret;
	return shiftRight(ret, v0, v1);
}
/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 operator>>(const ivec2 &v0, int v1) { return shiftRight(v0, v1); }
/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec2 operator>>(const ivec2 &v0, const ivec2 &v1) { return shiftRight(v0, v1); }

/// <summary>Returns the result of multiplication of each component of the first vector by the integer value and addition of the corresponding component of the second vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE ivec2 &mad(ivec2 &ret, const ivec2 &v0, int v1, const ivec2 &v2)
{
	ret.x = v0.x * v1 + v2.x;
	ret.y = v0.y * v1 + v2.y;
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE ivec2 &mad(ivec2 &ret, const ivec2 &v0, const ivec2 &v1, const ivec2 &v2)
{
	ret.x = v0.x * v1.x + v2.x;
	ret.y = v0.y * v1.y + v2.y;
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the integer value and addition of the corresponding component of the second vector (a * b + c).</summary>
UNIGINE_INLINE ivec2 mad(const ivec2 &v0, int v1, const ivec2 &v2)
{
	ivec2 ret;
	return mad(ret, v0, v1, v2);
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c).</summary>
UNIGINE_INLINE ivec2 mad(const ivec2 &v0, const ivec2 &v1, const ivec2 &v2)
{
	ivec2 ret;
	return mad(ret, v0, v1, v2);
}

/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE ivec2 &lerp(ivec2 &ret, const ivec2 &v0, const ivec2 &v1, int k)
{
	ret.x = lerp(v0.x, v1.x, k);
	ret.y = lerp(v0.y, v1.y, k);
	return ret;
}
/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE ivec2 &lerp(ivec2 &ret, const ivec2 &v0, const ivec2 &v1, const ivec2 &k)
{
	ret.x = lerp(v0.x, v1.x, k.x);
	ret.y = lerp(v0.y, v1.y, k.y);
	return ret;
}
/// <summary>Returns the vector component values interpolated according to the formula v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE ivec2 lerp(const ivec2 &v0, const ivec2 &v1, const ivec2 &k)
{
	ivec2 ret;
	return lerp(ret, v0, v1, k);
}
/// <summary>Returns the vector component values interpolated according to the formula v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE ivec2 lerp(const ivec2 &v0, const ivec2 &v1, int k)
{
	ivec2 ret;
	return lerp(ret, v0, v1, k);
}

/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE int dot(const ivec2 &v0, const ivec2 &v1)
{
	return v0.x * v1.x + v0.y * v1.y;
}

/// <summary>Compares the arguments component-wise and returns the minimum value for each component.</summary>
UNIGINE_INLINE ivec2 min(const ivec2 &v0, const ivec2 &v1)
{
	ivec2 ret;
	ret.x = min(v0.x, v1.x);
	ret.y = min(v0.y, v1.y);
	return ret;
}
/// <summary>Compares the arguments component-wise and returns the maximum value for each component.</summary>
UNIGINE_INLINE ivec2 max(const ivec2 &v0, const ivec2 &v1)
{
	ivec2 ret;
	ret.x = max(v0.x, v1.x);
	ret.y = max(v0.y, v1.y);
	return ret;
}
/// <summary>Clamps the value (v) within the minimum (v0) and maximum (v1) limits and returns the result.</summary>
UNIGINE_INLINE ivec2 clamp(const ivec2 &v, const ivec2 &v0, const ivec2 &v1)
{
	ivec2 ret;
	ret.x = clamp(v.x, v0.x, v1.x);
	ret.y = clamp(v.y, v0.y, v1.y);
	return ret;
}
/// <summary>Returns the absolute value of the specified argument.</summary>
UNIGINE_INLINE ivec2 abs(const ivec2 &v)
{
	return {abs(v.x), abs(v.y)};
}

}
}