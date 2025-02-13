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

namespace Unigine
{
namespace Math
{

struct alignas(8) vec2
{
	/// <summary>Constructor. Initializes the vector using given float values.</summary>
	UNIGINE_INLINE constexpr vec2(float v, ConstexprTag): x(v), y(v) {}
	/// <summary>Constructor. Initializes the vector using given float values.</summary>
	UNIGINE_INLINE constexpr vec2(float x, float y, ConstexprTag) : x(x), y(y) {}

	/// <summary>Default constructor. Produces a zero vector.</summary>
	UNIGINE_INLINE vec2()
		: x(0.0f)
		, y(0.0f)
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}
	/// <summary>Constructor. Initializes the vector using a given scalar value: x=v, y=v.</summary>
	UNIGINE_INLINE explicit vec2(float v)
		: x(v)
		, y(v)
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}
	/// <summary>Constructor. Initializes the vector using given float values.</summary>
	UNIGINE_INLINE vec2(float x, float y)
		: x(x)
		, y(y)
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}
	/// <summary>Constructor. Initializes the vector by copying a given source vector.</summary>
	UNIGINE_INLINE vec2(const vec2 &v)
		: x(v.x)
		, y(v.y)
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}
	/// <summary>Constructor. Initializes the vector using a given pointer to the array of float elements: x=v[0], y=v[1].</summary>
	UNIGINE_INLINE explicit vec2(const float *v)
		: x(v[0])
		, y(v[1])
	{
		UNIGINE_ASSERT_ALIGNED8(this);
	}

	/// <summary>Constructor. Initializes the vector using a given vec3 source vector.</summary>
	UNIGINE_INLINE explicit vec2(const vec3 &v);
	/// <summary>Constructor. Initializes the vector using a given vec4 source vector.</summary>
	UNIGINE_INLINE explicit vec2(const vec4 &v);
	/// <summary>Constructor. Initializes the vector using a given dvec2 source vectors.</summary>
	UNIGINE_INLINE explicit vec2(const dvec2 &v);
	/// <summary>Constructor. Initializes the vector using a given hvec2 source vectors.</summary>
	UNIGINE_INLINE explicit vec2(const hvec2 &v);
	/// <summary>Constructor. Initializes the vector using a given ivec2 source vectors.</summary>
	UNIGINE_INLINE explicit vec2(const ivec2 &v);

	/// <summary>Sets the vector components equal to specified scalar value: x=val, y=val.</summary>
	UNIGINE_INLINE void set(float val) { x = val; y = val; }
	/// <summary>Sets the vector by components.</summary>
	UNIGINE_INLINE void set(float x_, float y_) { x = x_; y = y_; }
	/// <summary>Sets the vector equal to the specified source vector.</summary>
	UNIGINE_INLINE void set(const vec2 &val)
	{
		#ifdef USE_SSE
			vec = val.vec;
		#else
			x = val.x;
			y = val.y;
		#endif
	}
	/// <summary>Sets the vector using the array of float elements: x=val[0], y=val[1].</summary>
	UNIGINE_INLINE void set(const float *val) { x = val[0]; y = val[1]; }

	/// <summary>Returns the pointer to the array of float elements: val[0]=x, val[1]=y.</summary>
	UNIGINE_INLINE void get(float *val) const { val[0] = x; val[1] = y; }
	UNIGINE_INLINE float *get() { return v; }
	/// <summary>Returns the constant pointer to the vector.</summary>
	UNIGINE_INLINE const float *get() const { return v; }

	/// <summary>Performs type conversion to float *.</summary>
	UNIGINE_INLINE operator float *() { return v; }
	/// <summary>Performs type conversion to const float *.</summary>
	UNIGINE_INLINE operator const float *() const { return v; }
	/// <summary>Performs type conversion to void *.</summary>
	UNIGINE_INLINE operator void *() { return v; }
	/// <summary>Performs type conversion to const void *.</summary>
	UNIGINE_INLINE operator const void *() const { return v; }

	/// <summary>Performs array access to the vector item reference by using given item index.</summary>
	UNIGINE_INLINE float &operator[](int i)
	{
		assert((unsigned int)i < 2 && "vec2::operator[](): bad index");
		return v[i];
	}
	/// <summary>Performs array access to the vector item by using given item index.</summary>
	UNIGINE_INLINE float operator[](int i) const
	{
		assert((unsigned int)i < 2 && "vec2::operator[](): bad index");
		return v[i];
	}

	/// <summary>Performs vector assignment. Destination vector = Source vector.</summary>
	UNIGINE_INLINE vec2 &operator=(const vec2 &v) { set(v); return *this; }
	/// <summary>Performs vector negation.</summary>
	UNIGINE_INLINE vec2 operator-() const { return vec2(-x, -y); }

	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(float v)
	{
		x *= v;
		y *= v;
	}
	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(const vec2 &v)
	{
		x *= v.x;
		y *= v.y;
	}
	/// <summary>Performs scalar multiplication.</summary>
	UNIGINE_INLINE vec2 &operator*=(float v) { mul(v); return *this; }
	/// <summary>Performs vector multiplication.</summary>
	UNIGINE_INLINE vec2 &operator*=(const vec2 &v) { mul(v); return *this; }

	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(float v) { mul(Math::rcp(v)); }
	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(const vec2 &v)
	{
		x /= v.x;
		y /= v.y;
	}
	/// <summary>Performs component-wise division of the vector by the scalar. Implemented using the calculation of inverse scalar value with subsequent component-wise multiplication.</summary>
	UNIGINE_INLINE vec2 &operator/=(float v) { div(v); return *this; }
	/// <summary>Performs component-wise division of vectors.</summary>
	UNIGINE_INLINE vec2 &operator/=(const vec2 &v) { div(v); return *this; }
	/// <summary>Performs component-wise division of vectors.</summary>
	UNIGINE_INLINE vec2 &operator/=(const ivec2 &v);

	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE void sub(float v)
	{
		x -= v;
		y -= v;
	}
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE void sub(const vec2 &v)
	{
		x -= v.x;
		y -= v.y;
	}
	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE vec2 &operator-=(float v) { sub(v); return *this; }
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE vec2 &operator-=(const vec2 &v) { sub(v); return *this; }

	/// <summary>Returns the sum of vector components.</summary>
	UNIGINE_INLINE float sum() const { return x + y; }
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE void add(float v)
	{
		x += v;
		y += v;
	}
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE void add(const vec2 &v)
	{
		x += v.x;
		y += v.y;
	}
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE vec2 &operator+=(float v) { add(v); return *this; }
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE vec2 &operator+=(const vec2 &v) { add(v); return *this; }

	/// <summary>Returns the squared length of the vector.</summary>
	UNIGINE_INLINE float length2() const { return x * x + y * y; }
	/// <summary>Returns the length of the vector.</summary>
	UNIGINE_INLINE float length() const { return toFloat(sqrt(length2())); }
	/// <summary>Returns the inverted length of the vector.</summary>
	UNIGINE_INLINE float iLength() const { return Math::rsqrt(length2()); }
	/// <summary>Returns the fast-calculated inverted length of the vector.</summary>
	UNIGINE_INLINE float iLengthFast() const { return Math::rsqrtFast(length2()); }

	/// <summary>Returns a normalized vector.</summary>
	UNIGINE_INLINE vec2 &normalize()
	{
		mul(iLength());
		return *this;
	}
	/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
	UNIGINE_INLINE vec2 &normalizeValid()
	{
		float length = length2();
		if (length != 0.0f)
			mul(Math::rsqrt(length));
		return *this;
	}
	/// <summary>Returns a normalized vector, calculated using the fast inverse square root algorithm.</summary>
	UNIGINE_INLINE vec2 &normalizeFast()
	{
		mul(iLengthFast());
		return *this;
	}
	/// <summary>Returns normalized vector, calculated using the fast inverse square root algorithm. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
	UNIGINE_INLINE vec2 &normalizeValidFast()
	{
		float length = length2();
		if (length != 0.0f)
			mul(Math::rsqrtFast(length));
		return *this;
	}

	/// <summary>Returns the fractional part of the argument.</summary>
	UNIGINE_INLINE vec2 frac() const { return vec2(Math::frac(x), Math::frac(y)); }
	/// <summary>Returns the absolute values of the vector components.</summary>
	UNIGINE_INLINE vec2 &abs()
	{
		x = Math::abs(x);
		y = Math::abs(y);
		return *this;
	}

	/// <summary>Compares components of the vector and returns the greater value.</summary>
	UNIGINE_INLINE float max() const { return Math::max(x, y); }
	/// <summary>Compares all components of the vector and returns the smaller value.</summary>
	UNIGINE_INLINE float min() const { return Math::min(x, y); }

	/// <summary>Returns a 64-bit hash generated for the vector.</summary>
	UNIGINE_INLINE unsigned long long hash64() const { return _hash_64; }
	/// <summary>Returns a hash obtained by mixing the hash values of vector components.</summary>
	UNIGINE_INLINE unsigned int hash() const { return hashCombine(hashInteger(x), y); }

	/// <summary>Returns the largest integral value that's less than or equal to the argument.</summary>
	UNIGINE_INLINE ivec2 floor() const;
	/// <summary>Returns the smallest integral value that's greater than or equal to the argument.</summary>
	UNIGINE_INLINE ivec2 ceil() const;
	
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
		unsigned long long _hash_64;

		#ifdef USE_SSE
			__m64 vec; // DO NOT TOUCH UNLESS ABSOLUTELY SURE
		#endif
	};

}; // end class vec2

constexpr vec2 vec2_zero(0.0f, ConstexprTag{});
constexpr vec2 vec2_one(1.0f, ConstexprTag{});
constexpr vec2 vec2_half(0.5f, ConstexprTag{});
constexpr vec2 vec2_eps(Consts::EPS, ConstexprTag{});
constexpr vec2 vec2_inf(Consts::INF, ConstexprTag{});


/// <summary>Calculates the length of a given vector.</summary>
UNIGINE_INLINE float length(const vec2 &v) { return v.length(); }
/// <summary>Calculates the squared length of a given vector. This method is much faster than length() - the calculation is basically the same only without the slow Sqrt call. If you are using lengths simply to compare distances, then it is faster to compare squared lengths against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE float length2(const vec2 &v) { return v.length2(); }

/// <summary>Returns a normalized vector.</summary>
UNIGINE_INLINE vec2 normalize(const vec2 &v)
{
	vec2 ret = v;
	return ret.normalize();
}
/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
UNIGINE_INLINE vec2 normalizeValid(const vec2 &v)
{
	vec2 ret = v;
	return ret.normalizeValid();
}


/// <summary>Compares two vectors according to the degree of precision equal to 1.0e-6f.</summary>
UNIGINE_INLINE bool compare(const vec2 &v0, const vec2 &v1)
{
	return compare(v0.x, v1.x) && compare(v0.y, v1.y);
}
/// <summary>Compares two vectors according to the specified degree of precision (epsilon).</summary>
UNIGINE_INLINE bool compare(const vec2 &v0, const vec2 &v1, float epsilon)
{
	return compare(v0.x, v1.x, epsilon) && compare(v0.y, v1.y, epsilon);
}
/// <summary>Vector equal comparison.</summary>
UNIGINE_INLINE bool operator==(const vec2 &v0, const vec2 &v1) { return compare(v0, v1); }
/// <summary>Vector not equal comparison.</summary>
UNIGINE_INLINE bool operator!=(const vec2 &v0, const vec2 &v1) { return !compare(v0, v1); }

/// <summary>Vector less than comparison.</summary>
UNIGINE_INLINE bool operator<(const vec2 &v0, const vec2 &v1) { return v0.x < v1.x && v0.y < v1.y; }
/// <summary>Vector greater than comparison.</summary>
UNIGINE_INLINE bool operator>(const vec2 &v0, const vec2 &v1) { return v0.x > v1.x && v0.y > v1.y; }

/// <summary>Vector less than or equal comparison.</summary>
UNIGINE_INLINE bool operator>=(const vec2 &v0, const vec2 &v1) { return v0.x >= v1.x && v0.y >= v1.y; }
/// <summary>Vector greater than or equal comparison.</summary>
UNIGINE_INLINE bool operator<=(const vec2 &v0, const vec2 &v1) { return v0.x <= v1.x && v0.y <= v1.y; }

/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE vec2 &mul(vec2 &ret, const vec2 &v0, float v1)
{
	ret.x = v0.x * v1;
	ret.y = v0.y * v1;
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE vec2 &mul(vec2 &ret, const vec2 &v0, const vec2 &v1)
{
	ret.x = v0.x * v1.x;
	ret.y = v0.y * v1.y;
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value.</summary>
UNIGINE_INLINE vec2 mul(const vec2 &v0, float v1)
{
	vec2 ret;
	mul(ret, v0, v1);
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of two vectors.</summary>
UNIGINE_INLINE vec2 mul(const vec2 &v0, const vec2 &v1)
{
	vec2 ret;
	mul(ret, v0, v1);
	return ret;
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec2 operator*(const vec2 &v0, float v1) { return mul(v0, v1); }
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec2 operator*(const vec2 &v0, const vec2 &v1) { return mul(v0, v1); }

/// <summary>Returns the result of a component-wise division of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE vec2 &div(vec2 &ret, const vec2 &v0, float v1) { mul(ret, v0, rcp(v1)); return ret; }
/// <summary>Returns the result of a component-wise division of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE vec2 &div(vec2 &ret, const vec2 &v0, const vec2 &v1)
{
	ret.x = v0.x / v1.x;
	ret.y = v0.y / v1.y;
	return ret;
}
/// <summary>Returns the result of a component-wise division of a vector by a scalar value.</summary>
UNIGINE_INLINE vec2 div(const vec2 &v0, float v1)
{
	vec2 ret;
	div(ret, v0, v1);
	return ret;
}
/// <summary>Returns the result of a component-wise division of two vectors.</summary>
UNIGINE_INLINE vec2 div(const vec2 &v0, const vec2 &v1)
{
	vec2 ret;
	div(ret, v0, v1);
	return ret;
}
/// <summary>Division operator.</summary>
UNIGINE_INLINE vec2 operator/(const vec2 &v0, float v1) { return div(v0, v1); }
/// <summary>Division operator.</summary>
UNIGINE_INLINE vec2 operator/(const vec2 &v0, const vec2 &v1) { return div(v0, v1); }

/// <summary>Returns the result of a component-wise addition of a vector with a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE vec2 &add(vec2 &ret, const vec2 &v0, float v1)
{
	ret.x = v0.x + v1;
	ret.y = v0.y + v1;
	return ret;
}
/// <summary>Returns the result of a component-wise addition of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE vec2 &add(vec2 &ret, const vec2 &v0, const vec2 &v1)
{
	ret.x = v0.x + v1.x;
	ret.y = v0.y + v1.y;
	return ret;
}
/// <summary>Returns the result of a component-wise addition of a vector with a scalar value.</summary>
UNIGINE_INLINE vec2 add(const vec2 &v0, float v1)
{
	vec2 ret;
	add(ret, v0, v1);
	return ret;
}
/// <summary>Returns the result of a component-wise addition of two vectors.</summary>
UNIGINE_INLINE vec2 add(const vec2 &v0, const vec2 &v1)
{
	vec2 ret;
	add(ret, v0, v1);
	return ret;
}
/// <summary>Addition operator.</summary>
UNIGINE_INLINE vec2 operator+(const vec2 &v0, float v1) { return add(v0, v1); }
/// <summary>Addition operator.</summary>
UNIGINE_INLINE vec2 operator+(const vec2 &v0, const vec2 &v1) { return add(v0, v1); }

/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector by saving it in the ret argument.</summary>
UNIGINE_INLINE vec2 &sub(vec2 &ret, const vec2 &v0, float v1)
{
	ret.x = v0.x - v1;
	ret.y = v0.y - v1;
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1) by saving it in the ret argument.</summary>
UNIGINE_INLINE vec2 &sub(vec2 &ret, const vec2 &v0, const vec2 &v1)
{
	ret.x = v0.x - v1.x;
	ret.y = v0.y - v1.y;
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector.</summary>
UNIGINE_INLINE vec2 sub(const vec2 &v0, float v1)
{
	vec2 ret;
	sub(ret, v0, v1);
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1).</summary>
UNIGINE_INLINE vec2 sub(const vec2 &v0, const vec2 &v1)
{
	vec2 ret;
	sub(ret, v0, v1);
	return ret;
}
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE vec2 operator-(const vec2 &v0, float v1) { return sub(v0, v1); }
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE vec2 operator-(const vec2 &v0, const vec2 &v1) { return sub(v0, v1); }

/// <summary>Returns the result of multiplication of each component of the first vector by the scalar value and addition of the corresponding component of the second vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE vec2 &mad(vec2 &ret, const vec2 &v0, float v1, const vec2 &v2)
{
	ret.x = v0.x * v1 + v2.x;
	ret.y = v0.y * v1 + v2.y;
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE vec2 &mad(vec2 &ret, const vec2 &v0, const vec2 &v1, const vec2 &v2)
{
	ret.x = v0.x * v1.x + v2.x;
	ret.y = v0.y * v1.y + v2.y;
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the scalar value and addition of the corresponding component of the second vector (a * b + c).</summary>
UNIGINE_INLINE vec2 mad(const vec2 &v0, float v1, const vec2 &v2)
{
	vec2 ret;
	mad(ret, v0, v1, v2);
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c).</summary>
UNIGINE_INLINE vec2 mad(const vec2 &v0, const vec2 &v1, const vec2 &v2)
{
	vec2 ret;
	mad(ret, v0, v1, v2);
	return ret;
}

/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec2 &lerp(vec2 &ret, const vec2 &v0, float v1, float k)
{
	ret.x = lerp(v0.x, v1, k);
	ret.y = lerp(v0.y, v1, k);
	return ret;
}
/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec2 &lerp(vec2 &ret, float v0, const vec2 &v1, float k)
{
	ret.x = lerp(v0, v1.x, k);
	ret.y = lerp(v0, v1.y, k);
	return ret;
}
/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec2 &lerp(vec2 &ret, const vec2 &v0, const vec2 &v1, float k)
{
	ret.x = lerp(v0.x, v1.x, k);
	ret.y = lerp(v0.y, v1.y, k);
	return ret;
}
/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec2 &lerp(vec2 &ret, const vec2 &v0, const vec2 &v1, const vec2 &k)
{
	ret.x = lerp(v0.x, v1.x, k.x);
	ret.y = lerp(v0.y, v1.y, k.y);
	return ret;
}
/// <summary>Returns the vector component values interpolated according to the formula v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE vec2 lerp(const vec2 &v0, const vec2 &v1, float k)
{
	vec2 ret;
	lerp(ret, v0, v1, k);
	return ret;
}
/// <summary>Returns the vector component values interpolated according to the formula v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE vec2 lerp(const vec2 &v0, const vec2 &v1, const vec2 &k)
{
	vec2 ret;
	lerp(ret, v0, v1, k);
	return ret;
}

/// <summary>Returns the value calculated according to the formula: (v - v0) / (v1 - v0) clamped within 0.0f and 1.0f.</summary>
UNIGINE_INLINE vec2 &inverseLerp(vec2 &ret, const vec2 &v0, const vec2 &v1, const vec2 &k)
{
	ret.x = inverseLerp(v0.x, v1.x, k.x);
	ret.y = inverseLerp(v0.y, v1.y, k.y);
	return ret;
}
/// <summary>Returns the value calculated according to the formula: (v - v0) / (v1 - v0) clamped within 0.0f and 1.0f.</summary>
UNIGINE_INLINE vec2 inverseLerp(const vec2 &v0, const vec2 &v1, const vec2 &k)
{
	vec2 ret;
	lerp(ret, v0, v1, k);
	return ret;
}

/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE float dot(const vec2 &v0, const vec2 &v1) { return v0.x * v1.x + v0.y * v1.y; }
/// <summary>Returns the cross product of two vectors.</summary>
UNIGINE_INLINE float cross(const vec2 &v0, const vec2 &v1) { return v0.x * v1.y - v0.y * v1.x; }

/// <summary>Returns an argument rounded to the nearest integral value.</summary>
UNIGINE_INLINE vec2 round(const vec2 &v) { return {round(v.x), round(v.y)}; }
/// <summary>Returns the largest integral value that's less than or equal to the argument.</summary>
UNIGINE_INLINE vec2 floor(const vec2 &v) { return {floor(v.x), floor(v.y)}; }
/// <summary>Returns the smallest integral value that's greater than or equal to the argument.</summary>
UNIGINE_INLINE vec2 ceil(const vec2 &v) { return {ceil(v.x), ceil(v.y)}; }
/// <summary>Returns the absolute value of the specified argument.</summary>
UNIGINE_INLINE vec2 abs(const vec2 &v) { return {abs(v.x), abs(v.y)}; }
/// <summary>Clamps the vector component values within the range [0.0, 1.0] and returns the result.</summary>
UNIGINE_INLINE vec2 saturate(const vec2 &v) { return {saturate(v.x), saturate(v.y)}; }

/// <summary>Compares the arguments component-wise and returns the minimum value for each component.</summary>
UNIGINE_INLINE vec2 min(const vec2 &v0, const vec2 &v1)
{
	vec2 ret;
	ret.x = min(v0.x, v1.x);
	ret.y = min(v0.y, v1.y);
	return ret;
}
/// <summary>Compares the arguments component-wise and returns the maximum value for each component.</summary>
UNIGINE_INLINE vec2 max(const vec2 &v0, const vec2 &v1)
{
	vec2 ret;
	ret.x = max(v0.x, v1.x);
	ret.y = max(v0.y, v1.y);
	return ret;
}
/// <summary>Compares each vector component with the float value and returns the minimum value for each component.</summary>
UNIGINE_INLINE vec2 min(const vec2 &v0, float v1)
{
	vec2 ret;
	ret.x = min(v0.x, v1);
	ret.y = min(v0.y, v1);
	return ret;
}
/// <summary>Compares each vector component with the float value and returns the maximum value for each component.</summary>
UNIGINE_INLINE vec2 max(const vec2 &v0, float v1)
{
	vec2 ret;
	ret.x = max(v0.x, v1);
	ret.y = max(v0.y, v1);
	return ret;
}
/// <summary>Clamps the value (v) within the minimum (v0) and maximum (v1) limits and returns the result.</summary>
UNIGINE_INLINE vec2 clamp(const vec2 &v, const vec2 &v0, const vec2 &v1)
{
	vec2 ret;
	ret.x = clamp(v.x, v0.x, v1.x);
	ret.y = clamp(v.y, v0.y, v1.y);
	return ret;
}

/// <summary>Converts RGB color value to sRGB format.</summary>
UNIGINE_INLINE vec2 srgb(const vec2 &color) { return vec2(srgb(color.x), srgb(color.y)); }
/// <summary>Converts sRGB color value to RGB format.</summary>
UNIGINE_INLINE vec2 isrgb(const vec2 &color) { return vec2(isrgb(color.x), isrgb(color.y)); }

/// <summary>Performs a smooth interpolation between two vectors (point_a and point_b) using a specified coefficient range to create a smooth transition effect.</summary>
UNIGINE_INLINE vec2 contrastLerp(const vec2 &point_a, const vec2 &point_b, float coef_min_bound, float coef_max_bound, float coef)
{
	return lerp(point_a, point_b, smoothstep(coef_min_bound, coef_max_bound, coef));
}

/// <summary>Performs a component-wise comparison between two arguments, and returns a new vector with a component set to 1.0 if the corresponding component in a is greater than in b, and 0.0 otherwise.</summary>
UNIGINE_INLINE vec2 step(const vec2 &a, const vec2 &b)
{
	return {toFloat(a.x > b.x), toFloat(a.y > b.y)};
}
/// <summary>Performs a component-wise comparison between two arguments, and returns a new vector with a component set to 1.0 if the corresponding component in a is greater than in b, and 0.0 otherwise.</summary>
UNIGINE_INLINE vec2 step(const vec2 &a, float b)
{
	return {toFloat(a.x > b), toFloat(a.y > b)};
}

/// <summary>Combines two vectors using an overlay blending effect, using the additional x value that determines the interpolation level between the vectors.</summary>
UNIGINE_INLINE vec2 overlay(const vec2 &a, const vec2 &b, float x)
{
	return max(lerp(a, lerp(vec2_one - (vec2_one - a) * (vec2_one - b) * 2.0f, a * b * 2.0f, step(a, vec2_half)), x), vec2_zero);
}
/// <summary>Combines two vectors using an overlay blending effect, using the additional x value that determines the interpolation level between the vectors.</summary>
UNIGINE_INLINE vec2 overlay(const vec2 &a, const vec2 &b, const vec2 &x)
{
	return max(lerp(a, lerp(vec2_one - (vec2_one - a) * (vec2_one - b) * 2.0f, a * b * 2.0f, step(a, vec2_half)), x), vec2_zero);
}

/// <summary>Calculates the squared distance between the two given vectors. The squared distance is calculated as: length2(v0 - v1). This method is much faster than distance() - the calculation is basically the same only without the slow Sqrt call. If you simply want to compare distances, then it is faster to compare squared distances against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE float distance2(const vec2 &v0, const vec2 &v1) { return length2(v0 - v1); }
/// <summary>Calculates the distance between the two given vectors. The distance is calculated as: length(v0 - v1).</summary>
UNIGINE_INLINE float distance(const vec2 &v0, const vec2 &v1) { return length(v0 - v1); }

}
}