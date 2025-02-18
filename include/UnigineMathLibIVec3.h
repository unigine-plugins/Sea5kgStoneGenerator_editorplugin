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
#include "UnigineMathLibCommon.h"
#include "UnigineMathLibVec3.h"
#include "UnigineMathLibDVec3.h"
#include "UnigineMathLibIVec2.h"

namespace Unigine
{
namespace Math
{

struct alignas(16) ivec3
{
	/// <summary>Default constructor. Produces a zero vector.</summary>
	UNIGINE_INLINE constexpr ivec3()
		: x(0)
		, y(0)
		, z(0)
		, align(0)
	{}
	/// <summary>Constructor. Initializes the vector using a given value: x=v, y=v, z=v.</summary>
	UNIGINE_INLINE constexpr explicit ivec3(int v)
		: x(v)
		, y(v)
		, z(v)
		, align(0)
	{}
	/// <summary>Constructor. Initializes the vector using the given values.</summary>
	UNIGINE_INLINE constexpr ivec3(int x, int y, int z)
		: x(x)
		, y(y)
		, z(z)
		, align(0)
	{}
	/// <summary>Constructor. Initializes the vector using a given pointer to the array of elements: x=v[0], y=v[1], z=v[2].</summary>
	UNIGINE_INLINE constexpr explicit ivec3(const int *v)
		: x(v[0])
		, y(v[1])
		, z(v[2])
		, align(0)
	{}
	/// <summary>Constructor. Initializes the vector by copying a given source vector.</summary>
	UNIGINE_INLINE ivec3(const ivec3 &v) { set(v); }

	/// <summary>Sets the vector using a two-component ivec2 source vector and a scalar.</summary>
	UNIGINE_INLINE ivec3(const ivec2 &xy, int z)
		: x(xy.x)
		, y(xy.y)
		, z(z)
		, align(0)
	{}

	/// <summary>Constructor. Initializes the vector using a given source vector.</summary>
	UNIGINE_INLINE explicit ivec3(const dvec3 &v)
		: x(toInt(v.x))
		, y(toInt(v.y))
		, z(toInt(v.z))
		, align(0)
	{}

	#ifdef USE_SSE
		UNIGINE_INLINE explicit ivec3(const vec3 &v)
		{
			vec = _mm_cvttps_epi32(v.vec);
		}
	#else
		UNIGINE_INLINE explicit ivec3(const vec3 &v)
			: x(toInt(v.x))
			, y(toInt(v.y))
			, z(toInt(v.z))
			, align(0)
		{}
	#endif

	#ifdef USE_SSE
		UNIGINE_INLINE ivec3(const __m128i &v): vec(v) {}
		UNIGINE_INLINE ivec3 &operator=(const __m128i &val)
		{
			vec = val;
			return *this;
		}
	#endif

	/// <summary>Constructor. Initializes the vector using a given ivec4 source vector.</summary>
	UNIGINE_INLINE explicit ivec3(const ivec4 &v);

	/// <summary>Sets the vector components equal to specified scalar value: x=val, y=val, z=val.</summary>
	UNIGINE_INLINE void set(int val)
	{
		x = val;
		y = val;
		z = val;
	}
	/// <summary>Sets the vector by components.</summary>
	UNIGINE_INLINE void set(int x_, int y_, int z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}
	/// <summary>Sets the vector equal to the specified source vector.</summary>
	UNIGINE_INLINE void set(const ivec3 &val)
	{
		#ifdef USE_SSE
			vec = val.vec;
		#else
			x = val.x;
			y = val.y;
			z = val.z;
			w = val.w;
		#endif
	}
	/// <summary>Sets the vector using the array of elements: x=val[0], y=val[1], z=val[2].</summary>
	UNIGINE_INLINE void set(const int *val)
	{
		x = val[0];
		y = val[1];
		z = val[2];
	}

	/// <summary>Returns the pointer to the array of elements: val[0]=x, val[1]=y, val[2]=z.</summary>
	UNIGINE_INLINE void get(int *val) const
	{
		val[0] = x;
		val[1] = y;
		val[2] = z;
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
		assert((unsigned int)i < 3 && "ivec3::operator[](): bad index");
		return v[i];
	}
	/// <summary>Performs array access to the vector item by using given item index.</summary>
	UNIGINE_INLINE int operator[](int i) const
	{
		assert((unsigned int)i < 3 && "ivec3::operator[](): bad index");
		return v[i];
	}


	/// <summary>Performs vector assignment. Destination vector = Source vector.</summary>
	UNIGINE_INLINE ivec3 &operator=(const ivec3 &v) { set(v); return *this; }
	/// <summary>Performs vector negation.</summary>
	UNIGINE_INLINE ivec3 operator-() const { return ivec3(-x, -y, -z); }

	/// <summary>Returns the result of multiplication of all vector component values.</summary>
	UNIGINE_INLINE int mul() const { return x * y * z; }
	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(int v)
	{
		x *= v;
		y *= v;
		z *= v;
	}
	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(const ivec3 &v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}
	/// <summary>Performs scalar multiplication.</summary>
	UNIGINE_INLINE ivec3 &operator*=(int v) { mul(v); return *this; }
	/// <summary>Performs vector multiplication.</summary>
	UNIGINE_INLINE ivec3 &operator*=(const ivec3 &v) { mul(v); return *this; }
	
	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(int v)
	{
		x /= v;
		y /= v;
		z /= v;
	}
	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(const ivec3 &v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
	}
	/// <summary>Performs component-wise division of the vector by the scalar. Implemented using the calculation of inverse scalar value with subsequent component-wise multiplication.</summary>
	UNIGINE_INLINE ivec3 &operator/=(int v) { div(v); return *this; }
	/// <summary>Performs component-wise division of vectors.</summary>
	UNIGINE_INLINE ivec3 &operator/=(const ivec3 &v) { div(v); return *this; }

	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE void sub(int v)
	{
		x -= v;
		y -= v;
		z -= v;
	}
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE void sub(const ivec3 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}
	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE ivec3 &operator-=(int v) { sub(v); return *this; }
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE ivec3 &operator-=(const ivec3 &v) { sub(v); return *this; }

	/// <summary>Returns the sum of vector components.</summary>
	UNIGINE_INLINE int sum() const { return x + y + z; }
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE void add(int v)
	{
		x += v;
		y += v;
		z += v;
	}
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE void add(const ivec3 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE ivec3 &operator+=(int v) { add(v); return *this; }
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE ivec3 &operator+=(const ivec3 &v) { add(v); return *this; }

	/// <summary>Shifts each component bitwise to the left by the specified value.</summary>
	UNIGINE_INLINE void shiftLeft(int v)
	{
		x <<= v;
		y <<= v;
		z <<= v;
	}
	/// <summary>Shifts each component bitwise to the left by the specified value.</summary>
	UNIGINE_INLINE void shiftLeft(const ivec3 &v)
	{
		x <<= v.x;
		y <<= v.y;
		z <<= v.z;
	}
	/// <summary>Shifts each component bitwise to the left by the specified value.</summary>
	UNIGINE_INLINE ivec3 &operator<<=(int v) { shiftLeft(v); return *this; }
	/// <summary>Shifts each component bitwise to the left by the specified value.</summary>
	UNIGINE_INLINE ivec3 &operator<<=(const ivec3 &v) { shiftLeft(v); return *this; }
	
	/// <summary>Shifts each component bitwise to the right by the specified value.</summary>
	UNIGINE_INLINE void shiftRight(int v)
	{
		x >>= v;
		y >>= v;
		z >>= v;
	}
	/// <summary>Shifts each component bitwise to the right by the specified value.</summary>
	UNIGINE_INLINE void shiftRight(const ivec3 &v)
	{
		x >>= v.x;
		y >>= v.y;
		z >>= v.z;
	}
	/// <summary>Shifts each component bitwise to the right by the specified value.</summary>
	UNIGINE_INLINE ivec3 &operator>>=(int v) { shiftRight(v); return *this; }
	/// <summary>Shifts each component bitwise to the right by the specified value.</summary>
	UNIGINE_INLINE ivec3 &operator>>=(const ivec3 &v) { shiftRight(v); return *this; }

	/// <summary>Returns the squared length of the vector.</summary>
	UNIGINE_INLINE int length2() const
	{
		return x * x + y * y + z * z;
	}

	/// <summary>Returns the absolute values of the vector components.</summary>
	UNIGINE_INLINE ivec3 &abs()
	{
		x = Math::abs(x);
		y = Math::abs(y);
		z = Math::abs(z);
		return *this;
	}

	/// <summary>Compares all components of the vector and returns the greatest value.</summary>
	UNIGINE_INLINE int max() const { return Math::max(Math::max(x, y), z); }
	/// <summary>Compares all components of the vector and returns the smallest value.</summary>
	UNIGINE_INLINE int min() const { return Math::min(Math::min(x, y), z); }

	/// <summary>Returns a 64-bit hash generated for the vector.</summary>
	UNIGINE_INLINE unsigned long long hash64() const { return hashMixer(_hash.xy, (unsigned long long)_hash.z); }
	/// <summary>Returns a hash obtained by mixing the hash values of vector components.</summary>
	UNIGINE_INLINE unsigned int hash() const { return hashCombine(hashCombine(x, y), z); }

	union
	{
		struct
		{
			int x, y, z, align;
		};
		ivec2 xy;
		int v[3];

		struct
		{
			unsigned long long xy;
			unsigned int z;
		} _hash;

		#ifdef USE_SSE
			__m128i vec; // DO NOT TOUCH UNLESS ABSOLUTELY SURE
		#else
			int vec[4];
		#endif
	};
};

constexpr ivec3 ivec3_zero(0);
constexpr ivec3 ivec3_one(1);

/// <summary>Calculates the squared length of a given vector. This method is much faster than length() - the calculation is basically the same only without the slow Sqrt call. If you are using lengths simply to compare distances, then it is faster to compare squared lengths against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE int length2(const ivec3 &v) { return v.length2(); }

/// <summary>Compares two vectors according to the degree of precision equal to 1.0e-6f.</summary>
UNIGINE_INLINE int compare(const ivec3 &v0, const ivec3 &v1) { return v0.x == v1.x && v0.y == v1.y && v0.z == v1.z; }
/// <summary>Vector equal comparison.</summary>
UNIGINE_INLINE int operator==(const ivec3 &v0, const ivec3 &v1) { return compare(v0, v1); }
/// <summary>Vector not equal comparison.</summary>
UNIGINE_INLINE int operator!=(const ivec3 &v0, const ivec3 &v1) { return !compare(v0, v1); }

/// <summary>Vector less than comparison.</summary>
UNIGINE_INLINE int operator<(const ivec3 &v0, const ivec3 &v1) { return v0.x < v1.x && v0.y < v1.y && v0.z < v1.z; }
/// <summary>Vector greater than comparison.</summary>
UNIGINE_INLINE int operator>(const ivec3 &v0, const ivec3 &v1) { return v0.x > v1.x && v0.y > v1.y && v0.z > v1.z; }

/// <summary>Vector less than or equal comparison.</summary>
UNIGINE_INLINE int operator<=(const ivec3 &v0, const ivec3 &v1) { return v0.x <= v1.x && v0.y <= v1.y && v0.z <= v1.z; }
/// <summary>Vector greater than or equal comparison.</summary>
UNIGINE_INLINE int operator>=(const ivec3 &v0, const ivec3 &v1) { return v0.x >= v1.x && v0.y >= v1.y && v0.z >= v1.z; }

/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec3 &mul(ivec3 &ret, const ivec3 &v0, int v1)
{
	ret.x = v0.x * v1;
	ret.y = v0.y * v1;
	ret.z = v0.z * v1;
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec3 &mul(ivec3 &ret, const ivec3 &v0, const ivec3 &v1)
{
	ret.x = v0.x * v1.x;
	ret.y = v0.y * v1.y;
	ret.z = v0.z * v1.z;
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value.</summary>
UNIGINE_INLINE ivec3 mul(const ivec3 &v0, int v1)
{
	ivec3 ret;
	return mul(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise multiplication of two vectors.</summary>
UNIGINE_INLINE ivec3 mul(const ivec3 &v0, const ivec3 &v1)
{
	ivec3 ret;
	return mul(ret, v0, v1);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE ivec3 operator*(const ivec3 &v0, int v1) { return mul(v0, v1); }
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE ivec3 operator*(const ivec3 &v0, const ivec3 &v1) { return mul(v0, v1); }

/// <summary>Returns the result of a component-wise division of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec3 &div(ivec3 &ret, const ivec3 &v0, int v1)
{
	ret.x = v0.x / v1;
	ret.y = v0.y / v1;
	ret.z = v0.z / v1;
	return ret;
}
/// <summary>Returns the result of a component-wise division of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec3 &div(ivec3 &ret, const ivec3 &v0, const ivec3 &v1)
{
	ret.x = v0.x / v1.x;
	ret.y = v0.y / v1.y;
	ret.z = v0.z / v1.z;
	return ret;
}
/// <summary>Returns the result of a component-wise division of a vector by a scalar value.</summary>
UNIGINE_INLINE ivec3 div(const ivec3 &v0, int v1)
{
	ivec3 ret;
	return div(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise division of two vectors.</summary>
UNIGINE_INLINE ivec3 div(const ivec3 &v0, const ivec3 &v1)
{
	ivec3 ret;
	return div(ret, v0, v1);
}
/// <summary>Division operator.</summary>
UNIGINE_INLINE ivec3 operator/(const ivec3 &v0, int v1) { return div(v0, v1); }
/// <summary>Division operator.</summary>
UNIGINE_INLINE ivec3 operator/(const ivec3 &v0, const ivec3 &v1) { return div(v0, v1); }

/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec3 &mod(ivec3 &ret, const ivec3 &v0, int v1)
{
	ret.x = v0.x % v1;
	ret.y = v0.y % v1;
	ret.z = v0.z % v1;
	return ret;
}
/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec3 &mod(ivec3 &ret, const ivec3 &v0, const ivec3 &v1)
{
	ret.x = v0.x % v1.x;
	ret.y = v0.y % v1.y;
	ret.z = v0.z % v1.z;
	return ret;
}
/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec3 mod(const ivec3 &v0, int v1)
{
	ivec3 ret;
	return mod(ret, v0, v1);
}
/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec3 mod(const ivec3 &v0, const ivec3 &v1)
{
	ivec3 ret;
	return mod(ret, v0, v1);
}
/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec3 operator%(const ivec3 &v0, int v1) { return mod(v0, v1); }
/// <summary>Modulus operation.</summary>
UNIGINE_INLINE ivec3 operator%(const ivec3 &v0, const ivec3 &v1) { return mod(v0, v1); }

/// <summary>Returns the result of a component-wise addition of a vector with a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec3 &add(ivec3 &ret, const ivec3 &v0, int v1)
{
	ret.x = v0.x + v1;
	ret.y = v0.y + v1;
	ret.z = v0.z + v1;
	return ret;
}
/// <summary>Returns the result of a component-wise addition of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec3 &add(ivec3 &ret, const ivec3 &v0, const ivec3 &v1)
{
	ret.x = v0.x + v1.x;
	ret.y = v0.y + v1.y;
	ret.z = v0.z + v1.z;
	return ret;
}
/// <summary>Returns the result of a component-wise addition of a vector with a scalar value.</summary>
UNIGINE_INLINE ivec3 add(const ivec3 &v0, int v1)
{
	ivec3 ret;
	return add(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise addition of two vectors.</summary>
UNIGINE_INLINE ivec3 add(const ivec3 &v0, const ivec3 &v1)
{
	ivec3 ret;
	return add(ret, v0, v1);
}
/// <summary>Addition operator.</summary>
UNIGINE_INLINE ivec3 operator+(const ivec3 &v0, int v1) { return add(v0, v1); }
/// <summary>Addition operator.</summary>
UNIGINE_INLINE ivec3 operator+(const ivec3 &v0, const ivec3 &v1) { return add(v0, v1); }

/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec3 &sub(ivec3 &ret, const ivec3 &v0, int v1)
{
	ret.x = v0.x - v1;
	ret.y = v0.y - v1;
	ret.z = v0.z - v1;
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1) by saving it in the ret argument.</summary>
UNIGINE_INLINE ivec3 &sub(ivec3 &ret, const ivec3 &v0, const ivec3 &v1)
{
	ret.x = v0.x - v1.x;
	ret.y = v0.y - v1.y;
	ret.z = v0.z - v1.z;
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector.</summary>
UNIGINE_INLINE ivec3 sub(const ivec3 &v0, int v1)
{
	ivec3 ret;
	return sub(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1).</summary>
UNIGINE_INLINE ivec3 sub(const ivec3 &v0, const ivec3 &v1)
{
	ivec3 ret;
	return sub(ret, v0, v1);
}
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE ivec3 operator-(const ivec3 &v0, int v1) { return sub(v0, v1); }
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE ivec3 operator-(const ivec3 &v0, const ivec3 &v1) { return sub(v0, v1); }

/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 &shiftLeft(ivec3 &ret, const ivec3 &v0, int v1)
{
	ret.x = v0.x << v1;
	ret.y = v0.y << v1;
	ret.z = v0.z << v1;
	return ret;
}
/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 &shiftLeft(ivec3 &ret, const ivec3 &v0, const ivec3 &v1)
{
	ret.x = v0.x << v1.x;
	ret.y = v0.y << v1.y;
	ret.z = v0.z << v1.z;
	return ret;
}
/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 shiftLeft(const ivec3 &v0, int v1)
{
	ivec3 ret;
	return shiftLeft(ret, v0, v1);
}
/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 shiftLeft(const ivec3 &v0, const ivec3 &v1)
{
	ivec3 ret;
	return shiftLeft(ret, v0, v1);
}
/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 operator<<(const ivec3 &v0, int v1) { return shiftLeft(v0, v1); }
/// <summary>Shifts each v0 vector component bitwise to the left by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 operator<<(const ivec3 &v0, const ivec3 &v1) { return shiftLeft(v0, v1); }

/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 &shiftRight(ivec3 &ret, const ivec3 &v0, int v1)
{
	ret.x = v0.x >> v1;
	ret.y = v0.y >> v1;
	ret.z = v0.z >> v1;
	return ret;
}
/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 &shiftRight(ivec3 &ret, const ivec3 &v0, const ivec3 &v1)
{
	ret.x = v0.x >> v1.x;
	ret.y = v0.y >> v1.y;
	ret.z = v0.z >> v1.z;
	return ret;
}
/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 shiftRight(const ivec3 &v0, int v1)
{
	ivec3 ret;
	return shiftRight(ret, v0, v1);
}
/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 shiftRight(const ivec3 &v0, const ivec3 &v1)
{
	ivec3 ret;
	return shiftRight(ret, v0, v1);
}
/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 operator>>(const ivec3 &v0, int v1) { return shiftRight(v0, v1); }
/// <summary>Shifts each v0 vector component bitwise to the right by the specified v1 value.</summary>
UNIGINE_INLINE ivec3 operator>>(const ivec3 &v0, const ivec3 &v1) { return shiftRight(v0, v1); }

/// <summary>Returns the result of multiplication of each component of the first vector by the integer value and addition of the corresponding component of the second vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE ivec3 &mad(ivec3 &ret, const ivec3 &v0, int v1, const ivec3 &v2)
{
	ret.x = v0.x * v1 + v2.x;
	ret.y = v0.y * v1 + v2.y;
	ret.z = v0.z * v1 + v2.z;
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE ivec3 &mad(ivec3 &ret, const ivec3 &v0, const ivec3 &v1, const ivec3 &v2)
{
	ret.x = v0.x * v1.x + v2.x;
	ret.y = v0.y * v1.y + v2.y;
	ret.z = v0.z * v1.z + v2.z;
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the integer value and addition of the corresponding component of the second vector (a * b + c).</summary>
UNIGINE_INLINE ivec3 mad(const ivec3 &v0, int v1, const ivec3 &v2)
{
	ivec3 ret;
	return mad(ret, v0, v1, v2);
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c).</summary>
UNIGINE_INLINE ivec3 mad(const ivec3 &v0, const ivec3 &v1, const ivec3 &v2)
{
	ivec3 ret;
	return mad(ret, v0, v1, v2);
}

/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE ivec3 &lerp(ivec3 &ret, const ivec3 &v0, const ivec3 &v1, int k)
{
	ret.x = lerp(v0.x, v1.x, k);
	ret.y = lerp(v0.y, v1.y, k);
	ret.z = lerp(v0.z, v1.z, k);
	return ret;
}
/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE ivec3 &lerp(ivec3 &ret, const ivec3 &v0, const ivec3 &v1, const ivec3 &k)
{
	ret.x = lerp(v0.x, v1.x, k.x);
	ret.y = lerp(v0.y, v1.y, k.y);
	ret.z = lerp(v0.z, v1.z, k.z);
	return ret;
}
/// <summary>Returns the vector component values interpolated according to the formula v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE ivec3 lerp(const ivec3 &v0, const ivec3 &v1, const ivec3 &k)
{
	ivec3 ret;
	return lerp(ret, v0, v1, k);
}
/// <summary>Returns the vector component values interpolated according to the formula v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE ivec3 lerp(const ivec3 &v0, const ivec3 &v1, int k)
{
	ivec3 ret;
	return lerp(ret, v0, v1, k);
}

/// <summary>Returns the cross product of two vectors.</summary>
UNIGINE_INLINE ivec3 &cross(ivec3 &ret, const ivec3 &v0, const ivec3 &v1)
{
	ret.x = v0.y * v1.z - v0.z * v1.y;
	ret.y = v0.z * v1.x - v0.x * v1.z;
	ret.z = v0.x * v1.y - v0.y * v1.x;
	return ret;
}
/// <summary>Returns the cross product of two vectors.</summary>
UNIGINE_INLINE ivec3 cross(const ivec3 &v0, const ivec3 &v1)
{
	ivec3 ret;
	return cross(ret, v0, v1);
}

/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE int dot(const ivec3 &v0, const ivec3 &v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

/// <summary>Compares the arguments component-wise and returns the minimum value for each component.</summary>
UNIGINE_INLINE ivec3 min(const ivec3 &v0, const ivec3 &v1)
{
	ivec3 ret;
	ret.x = min(v0.x, v1.x);
	ret.y = min(v0.y, v1.y);
	ret.z = min(v0.z, v1.z);
	return ret;
}
/// <summary>Compares the arguments component-wise and returns the maximum value for each component.</summary>
UNIGINE_INLINE ivec3 max(const ivec3 &v0, const ivec3 &v1)
{
	ivec3 ret;
	ret.x = max(v0.x, v1.x);
	ret.y = max(v0.y, v1.y);
	ret.z = max(v0.z, v1.z);
	return ret;
}
/// <summary>Clamps the value (v) within the minimum (v0) and maximum (v1) limits and returns the result.</summary>
UNIGINE_INLINE ivec3 clamp(const ivec3 &v, const ivec3 &v0, const ivec3 &v1)
{
	ivec3 ret;
	ret.x = clamp(v.x, v0.x, v1.x);
	ret.y = clamp(v.y, v0.y, v1.y);
	ret.z = clamp(v.z, v0.z, v1.z);
	return ret;
}
/// <summary>Returns the absolute value of the specified argument.</summary>
UNIGINE_INLINE ivec3 abs(const ivec3 &v)
{
	return {abs(v.x), abs(v.y), abs(v.z)};
}

}
}
