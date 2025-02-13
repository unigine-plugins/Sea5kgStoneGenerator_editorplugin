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

namespace Unigine
{
namespace Math
{

struct alignas(16) dvec2
{
	/// <summary>Constructor. Initializes the vector using the given values.</summary>
	UNIGINE_INLINE constexpr dvec2(double v, ConstexprTag): x(v), y(v) {}
	/// <summary>Constructor. Initializes the vector using the given values.</summary>
	UNIGINE_INLINE constexpr dvec2(double x, double y, ConstexprTag) : x(x), y(y) {}

	/// <summary>Default constructor. Produces a zero vector.</summary>
	UNIGINE_INLINE dvec2()
		: x(0.0)
		, y(0.0)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using the given values.</summary>
	UNIGINE_INLINE dvec2(double x, double y)
		: x(x)
		, y(y)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using a given value: x=v, y=v.</summary>
	UNIGINE_INLINE explicit dvec2(double v)
		: x(v)
		, y(v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using a given pointer to the array of elements: x=v[0], y=v[1].</summary>
	UNIGINE_INLINE explicit dvec2(const double *v)
		: x(v[0])
		, y(v[1])
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector by copying a given source vector.</summary>
	UNIGINE_INLINE dvec2(const dvec2 &v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(v);
	}
	/// <summary>Constructor. Initializes the vector using a given source vector.</summary>
	UNIGINE_INLINE explicit dvec2(const vec2 &v)
		: x(v.x)
		, y(v.y)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}

	/// <summary>Constructor. Initializes the vector using a given dvec3 source vector.</summary>
	UNIGINE_INLINE explicit dvec2(const dvec3 &v);
	/// <summary>Constructor. Initializes the vector using a given dvec4 source vector.</summary>
	UNIGINE_INLINE explicit dvec2(const dvec4 &v);
	/// <summary>Constructor. Initializes the vector using a given hvec2 source vector.</summary>
	UNIGINE_INLINE explicit dvec2(const hvec2 &v);
	/// <summary>Constructor. Initializes the vector using a given ivec2 source vector.</summary>
	UNIGINE_INLINE explicit dvec2(const ivec2 &v);

	#ifdef USE_SSE
		UNIGINE_INLINE dvec2(const __m128d &v): vec(v)
		{
			UNIGINE_ASSERT_ALIGNED16(this);
		}
		UNIGINE_INLINE dvec2 &operator=(const __m128d &val) { vec = val; return *this; }
	#endif

	/// <summary>Sets the vector components equal to specified scalar value: x=val, y=val.</summary>
	UNIGINE_INLINE void set(double val) { x = val; y = val; }
	/// <summary>Sets the vector by components.</summary>
	UNIGINE_INLINE void set(double x_, double y_) { x = x_; y = y_; }
	/// <summary>Sets the vector equal to the specified source vector.</summary>
	UNIGINE_INLINE void set(const dvec2 &val)
	{
		#ifdef USE_SSE
			vec = val.vec;
		#else
			x = val.x;
			y = val.y;
		#endif
	}
	/// <summary>Sets the vector using the array of elements: x=val[0], y=val[1].</summary>
	UNIGINE_INLINE void set(const double *val)
	{
		x = val[0];
		y = val[1];
	}

	/// <summary>Returns the pointer to the array of elements: val[0]=x, val[1]=y.</summary>
	UNIGINE_INLINE void get(double *val) const
	{
		val[0] = x;
		val[1] = y;
	}
	/// <summary>Returns the pointer to the vector.</summary>
	UNIGINE_INLINE double *get() { return v; }
	/// <summary>Returns the constant pointer to the vector.</summary>
	UNIGINE_INLINE const double *get() const { return v; }

	/// <summary>Performs type conversion to double *.</summary>
	UNIGINE_INLINE operator double *() { return v; }
	/// <summary>Performs type conversion to const double *.</summary>
	UNIGINE_INLINE operator const double *() const { return v; }
	/// <summary>Performs type conversion to void *.</summary>
	UNIGINE_INLINE operator void *() { return v; }
	/// <summary>Performs type conversion to const void *.</summary>
	UNIGINE_INLINE operator const void *() const { return v; }

	/// <summary>Performs array access to the vector item reference by using given item index.</summary>
	UNIGINE_INLINE double &operator[](int i)
	{
		assert((unsigned int)i < 2 && "dvec2::operator[](): bad index");
		return v[i];
	}
	/// <summary>Performs array access to the vector item by using given item index.</summary>
	UNIGINE_INLINE double operator[](int i) const
	{
		assert((unsigned int)i < 2 && "dvec2::operator[](): bad index");
		return v[i];
	}

	/// <summary>Performs vector assignment. Destination vector = Source vector.</summary>
	UNIGINE_INLINE dvec2 &operator=(const dvec2 &v) { set(v); return *this; }
	/// <summary>Performs vector negation.</summary>
	UNIGINE_INLINE dvec2 operator-() const { return dvec2(-x, -y); }

	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(double v)
	{
		#ifdef USE_SSE
			vec = _mm_mul_pd(vec, _mm_set1_pd(v));
		#else
			x *= v;
			y *= v;
		#endif
	}
	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(const dvec2 &v)
	{
		#ifdef USE_SSE
			vec = _mm_mul_pd(vec, v.vec);
		#else
			x *= v.x;
			y *= v.y;
		#endif
	}
	UNIGINE_INLINE dvec2 &operator*=(double v) { mul(v); return *this; }
	UNIGINE_INLINE dvec2 &operator*=(const dvec2 &v) { mul(v); return *this; }

	UNIGINE_INLINE void div(double v) { mul(Math::rcp(v)); }
	UNIGINE_INLINE void div(const dvec2 &v)
	{
		#ifdef USE_SSE
			vec = _mm_div_pd(vec, v.vec);
		#else
			x /= v.x;
			y /= v.y;
		#endif
	}
	/// <summary>Performs component-wise division of the vector by the scalar. Implemented using the calculation of inverse scalar value with subsequent component-wise multiplication.</summary>
	UNIGINE_INLINE dvec2 &operator/=(double v) { div(v); return *this; }
	/// <summary>Performs component-wise division of vectors.</summary>
	UNIGINE_INLINE dvec2 &operator/=(const dvec2 &v) { div(v); return *this; }

	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE void sub(double v)
	{
		#ifdef USE_SSE
			vec = _mm_sub_pd(vec, _mm_set1_pd(v));
		#else
			x -= v;
			y -= v;
		#endif
	}
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE void sub(const dvec2 &v)
	{
		#ifdef USE_SSE
			vec = _mm_sub_pd(vec, v.vec);
		#else
			x -= v.x;
			y -= v.y;
		#endif
	}
	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE dvec2 &operator-=(double v) { sub(v); return *this; }
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE dvec2 &operator-=(const dvec2 &v) { sub(v); return *this; }


	/// <summary>Returns the sum of vector components.</summary>
	UNIGINE_INLINE double sum() const { return x + y; }
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE void add(double v)
	{
		#ifdef USE_SSE
			vec = _mm_add_pd(vec, _mm_set1_pd(v));
		#else
			x += v;
			y += v;
		#endif
	}
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE void add(const dvec2 &v)
	{
		#ifdef USE_SSE
			vec = _mm_add_pd(vec, v.vec);
		#else
			x += v.x;
			y += v.y;
		#endif
	}
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE dvec2 &operator+=(double v) { add(v); return *this; }
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE dvec2 &operator+=(const dvec2 &v) { add(v); return *this; }

	/// <summary>Returns the squared length of the vector.</summary>
	UNIGINE_INLINE double length2() const { return x * x + y * y; }
	/// <summary>Returns the length of the vector.</summary>
	UNIGINE_INLINE double length() const { return sqrt(length2()); }
	/// <summary>Returns the inverted length of the vector.</summary>
	UNIGINE_INLINE double iLength() const { return Math::rsqrt(length2()); }

	/// <summary>Returns a normalized vector.</summary>
	UNIGINE_INLINE dvec2 &normalize()
	{
		mul(iLength());
		return *this;
	}
	/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
	UNIGINE_INLINE dvec2 &normalizeValid()
	{
		double length = length2();
		if (length != 0.0)
			mul(Math::rsqrt(length));
		return *this;
	}

	/// <summary>Compares components of the vector and returns the greater value.</summary>
	UNIGINE_INLINE double max() const { return Math::max(x, y); }
	/// <summary>Compares all components of the vector and returns the smaller value.</summary>
	UNIGINE_INLINE double min() const { return Math::min(x, y); }
	/// <summary>Returns the fractional part of the argument.</summary>
	UNIGINE_INLINE dvec2 frac() const
	{
		return dvec2(Math::frac(x), Math::frac(y));
	}
	/// <summary>Returns the absolute values of the vector components.</summary>
	UNIGINE_INLINE dvec2 &abs()
	{
		x = Math::abs(x);
		y = Math::abs(y);
		return *this;
	}
	/// <summary>Returns the largest integral value that's less than or equal to the argument.</summary>
	UNIGINE_INLINE ivec2 floor() const;
	/// <summary>Returns the smallest integral value that's greater than or equal to the argument.</summary>
	UNIGINE_INLINE ivec2 ceil() const;

	/// <summary>Returns a 64-bit hash generated for the vector.</summary>
	UNIGINE_INLINE unsigned long long hash64() const { return hashMixer(_hash.x, _hash.y); }
	/// <summary>Returns a hash obtained by mixing the hash values of vector components.</summary>
	UNIGINE_INLINE unsigned int hash() const { return hashCast64To32(hashCombine(hashInteger(x), y)); }

	union
	{
		struct
		{
			double x, y;
		};
		double v[2];

		struct
		{
			unsigned long long x;
			unsigned long long y;
		} _hash;

		#ifdef USE_SSE
			__m128d vec; // DO NOT TOUCH UNLESS ABSOLUTELY SURE
		#endif
	};
};

constexpr dvec2 dvec2_zero(0.0, ConstexprTag{});
constexpr dvec2 dvec2_one(1.0, ConstexprTag{});
constexpr dvec2 dvec2_half(0.5, ConstexprTag{});
constexpr dvec2 dvec2_eps(Consts::EPS, ConstexprTag{});
constexpr dvec2 dvec2_inf(Consts::INF, ConstexprTag{});

/// <summary>Calculates the length of a given vector.</summary>
UNIGINE_INLINE double length(const dvec2 &v) { return v.length(); }
/// <summary>Calculates the squared length of a given vector. This method is much faster than length() - the calculation is basically the same only without the slow Sqrt call. If you are using lengths simply to compare distances, then it is faster to compare squared lengths against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE double length2(const dvec2 &v) { return v.length2(); }

/// <summary>Calculates the squared distance between the two given vectors. The squared distance is calculated as: length2(v0 - v1). This method is much faster than distance() - the calculation is basically the same only without the slow Sqrt call. If you simply want to compare distances, then it is faster to compare squared distances against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE double distance2(const dvec2 &v0, const dvec2 &v1)
{
	#ifdef USE_SSE
		double ret;
		__m128d vec = _mm_sub_pd(v0.vec, v1.vec);
		_mm_store_sd(&ret, _mm_dp_pd(vec, vec, 0x7f));
		return ret;
	#else
		return length2(v0 - v1);
	#endif
}
/// <summary>Calculates the distance between the two given vectors. The distance is calculated as: length(v0 - v1).</summary>
UNIGINE_INLINE double distance(const dvec2 &v0, const dvec2 &v1)
{
	#ifdef USE_SSE
		double ret;
		__m128d vec = _mm_sub_pd(v0.vec, v1.vec);
		_mm_store_sd(&ret, _mm_dp_pd(vec, vec, 0x7f));
		return sqrt(ret);
	#else
		return length(v0 - v1);
	#endif
}

/// <summary>Returns a normalized vector.</summary>
UNIGINE_INLINE dvec2 normalize(const dvec2 &v)
{
	dvec2 ret = v;
	return ret.normalize();
}
/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
UNIGINE_INLINE dvec2 normalizeValid(const dvec2 &v)
{
	dvec2 ret = v;
	return ret.normalizeValid();
}

/// <summary>Compares two vectors according to the degree of precision equal to 1.0e-6f.</summary>
UNIGINE_INLINE int compare(const dvec2 &v0, const dvec2 &v1)
{
	return (compare(v0.x, v1.x) && compare(v0.y, v1.y));
}
/// <summary>Compares two vectors according to the specified degree of precision (eps).</summary>
UNIGINE_INLINE int compare(const dvec2 &v0, const dvec2 &v1, double eps)
{
	return (compare(v0.x, v1.x, eps) && compare(v0.y, v1.y, eps));
}
/// <summary>Vector equal comparison.</summary>
UNIGINE_INLINE int operator==(const dvec2 &v0, const dvec2 &v1) { return compare(v0, v1); }
/// <summary>Vector not equal comparison.</summary>
UNIGINE_INLINE int operator!=(const dvec2 &v0, const dvec2 &v1) { return !compare(v0, v1); }

/// <summary>Vector less than comparison.</summary>
UNIGINE_INLINE int operator<(const dvec2 &v0, const dvec2 &v1) { return v0.x < v1.x &&v0.y < v1.y; }
/// <summary>Vector greater than comparison.</summary>
UNIGINE_INLINE int operator>(const dvec2 &v0, const dvec2 &v1) { return v0.x > v1.x && v0.y > v1.y; }

/// <summary>Vector less than or equal comparison.</summary>
UNIGINE_INLINE int operator>=(const dvec2 &v0, const dvec2 &v1) { return v0.x >= v1.x && v0.y >= v1.y; }
/// <summary>Vector greater than or equal comparison.</summary>
UNIGINE_INLINE int operator<=(const dvec2 &v0, const dvec2 &v1) { return v0.x <= v1.x && v0.y <= v1.y; }

/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec2 &mul(dvec2 &ret, const dvec2 &v0, double v1)
{
	#ifdef USE_SSE
		ret = _mm_mul_pd(v0.vec, _mm_set1_pd(v1));
	#else
		ret.x = v0.x * v1;
		ret.y = v0.y * v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec2 &mul(dvec2 &ret, const dvec2 &v0, const dvec2 &v1)
{
	#ifdef USE_SSE
		ret = _mm_mul_pd(v0.vec, v1.vec);
	#else
		ret.x = v0.x * v1;
		ret.y = v0.y * v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value.</summary>
UNIGINE_INLINE dvec2 mul(const dvec2 &v0, double v1)
{
	dvec2 ret;
	return mul(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise multiplication of two vectors.</summary>
UNIGINE_INLINE dvec2 mul(const dvec2 &v0, const dvec2 &v1)
{
	dvec2 ret;
	return mul(ret, v0, v1);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dvec2 operator*(const dvec2 &v0, double v1) { return mul(v0, v1); }
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dvec2 operator*(const dvec2 &v0, const dvec2 &v1) { return mul(v0, v1); }

/// <summary>Returns the result of a component-wise division of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec2 &div(dvec2 &ret, const dvec2 &v0, double v1) { mul(ret, v0, rcp(v1)); return ret; }
/// <summary>Returns the result of a component-wise division of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec2 &div(dvec2 &ret, const dvec2 &v0, const dvec2 &v1)
{
	#ifdef USE_SSE
		ret = _mm_div_pd(v0.vec, v1.vec);
	#else
		ret.x = v0.x / v1;
		ret.y = v0.y / v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise division of a vector by a scalar value.</summary>
UNIGINE_INLINE dvec2 div(const dvec2 &v0, double v1)
{
	dvec2 ret;
	return div(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise division of two vectors.</summary>
UNIGINE_INLINE dvec2 div(const dvec2 &v0, const dvec2 &v1)
{
	dvec2 ret;
	return div(ret, v0, v1);
}
/// <summary>Division operator.</summary>
UNIGINE_INLINE dvec2 operator/(const dvec2 &v0, double v1) { return div(v0, v1); }
/// <summary>Division operator.</summary>
UNIGINE_INLINE dvec2 operator/(const dvec2 &v0, const dvec2 &v1) { return div(v0, v1); }

/// <summary>Returns the result of a component-wise addition of a vector with a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec2 &add(dvec2 &ret, const dvec2 &v0, double v1)
{
	#ifdef USE_SSE
		ret = _mm_add_pd(v0.vec, _mm_set1_pd(v1));
	#else
		ret.x = v0.x + v1;
		ret.y = v0.y + v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise addition of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec2 &add(dvec2 &ret, const dvec2 &v0, const dvec2 &v1)
{
	#ifdef USE_SSE
		ret = _mm_add_pd(v0.vec, v1.vec);
	#else
		ret.x = v0.x + v1;
		ret.y = v0.y + v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise addition of a vector with a scalar value.</summary>
UNIGINE_INLINE dvec2 add(const dvec2 &v0, double v1)
{
	dvec2 ret;
	return add(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise addition of two vectors.</summary>
UNIGINE_INLINE dvec2 add(const dvec2 &v0, const dvec2 &v1)
{
	dvec2 ret;
	return add(ret, v0, v1);
}
/// <summary>Addition operator.</summary>
UNIGINE_INLINE dvec2 operator+(const dvec2 &v0, double v1) { return add(v0, v1); }
/// <summary>Addition operator.</summary>
UNIGINE_INLINE dvec2 operator+(const dvec2 &v0, const dvec2 &v1) { return add(v0, v1); }

/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec2 &sub(dvec2 &ret, const dvec2 &v0, double v1)
{
	#ifdef USE_SSE
		ret = _mm_sub_pd(v0.vec, _mm_set1_pd(v1));
	#else
		ret.x = v0.x - v1;
		ret.y = v0.y - v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1) by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec2 &sub(dvec2 &ret, const dvec2 &v0, const dvec2 &v1)
{
	#ifdef USE_SSE
		ret = _mm_sub_pd(v0.vec, v1.vec);
	#else
		ret.x = v0.x - v1;
		ret.y = v0.y - v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector.</summary>
UNIGINE_INLINE dvec2 sub(const dvec2 &v0, double v1)
{
	dvec2 ret;
	return sub(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1).</summary>
UNIGINE_INLINE dvec2 sub(const dvec2 &v0, const dvec2 &v1)
{
	dvec2 ret;
	return sub(ret, v0, v1);
}
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE dvec2 operator-(const dvec2 &v0, double v1) { return sub(v0, v1); }
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE dvec2 operator-(const dvec2 &v0, const dvec2 &v1) { return sub(v0, v1); }

/// <summary>Returns the result of multiplication of each component of the first vector by the scalar value and addition of the corresponding component of the second vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE dvec2 &mad(dvec2 &ret, const dvec2 &v0, double v1, const dvec2 &v2)
{
	#ifdef USE_SSE
		ret = _mm_add_pd(_mm_mul_pd(v0.vec, _mm_set1_pd(v1)), v2.vec);
	#else
		ret.x = v0.x * v1 + v2.x;
		ret.y = v0.y * v1 + v2.y;
	#endif
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE dvec2 &mad(dvec2 &ret, const dvec2 &v0, const dvec2 &v1, const dvec2 &v2)
{
	#ifdef USE_SSE
		ret = _mm_add_pd(_mm_mul_pd(v0.vec, v1.vec), v2.vec);
	#else
		ret.x = v0.x * v1 + v2.x;
		ret.y = v0.y * v1 + v2.y;
	#endif
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the scalar value and addition of the corresponding component of the second vector (a * b + c).</summary>
UNIGINE_INLINE dvec2 mad(const dvec2 &v0, double v1, const dvec2 &v2)
{
	dvec2 ret;
	return mad(ret, v0, v1, v2);
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c).</summary>
UNIGINE_INLINE dvec2 mad(const dvec2 &v0, const dvec2 &v1, const dvec2 &v2)
{
	dvec2 ret;
	return mad(ret, v0, v1, v2);
}

/// <summary>Compares the arguments component-wise and returns the minimum value for each component.</summary>
UNIGINE_INLINE dvec2 min(const dvec2 &v0, const dvec2 &v1)
{
	dvec2 ret;
	#ifdef USE_SSE
		ret = _mm_min_pd(v0.vec, v1.vec);
	#else
		ret.x = min(v0.x, v1.x);
		ret.y = min(v0.y, v1.y);
	#endif
	return ret;
}
/// <summary>Compares the arguments component-wise and returns the maximum value for each component.</summary>
UNIGINE_INLINE dvec2 max(const dvec2 &v0, const dvec2 &v1)
{
	dvec2 ret;
	#ifdef USE_SSE
		ret = _mm_max_pd(v0.vec, v1.vec);
	#else
		ret.x = max(v0.x, v1.x);
		ret.y = max(v0.y, v1.y);
	#endif
	return ret;
}
/// <summary>Clamps the value (v) within the minimum (v0) and maximum (v1) limits and returns the result.</summary>
UNIGINE_INLINE dvec2 clamp(const dvec2 &v, const dvec2 &v0, const dvec2 &v1)
{
	dvec2 ret;
	#ifdef USE_SSE
		ret = _mm_min_pd(_mm_max_pd(v.vec, v0.vec), v1.vec);
	#else
		ret.x = clamp(v.x, v0.x, v1.x);
		ret.y = clamp(v.y, v0.y, v1.y);
	#endif
	return ret;
}
/// <summary>Clamps the vector component values within the range [0.0, 1.0] and returns the result.</summary>
UNIGINE_INLINE dvec2 saturate(const dvec2 &v)
{
	dvec2 ret;
	#ifdef USE_SSE
		ret = _mm_min_pd(_mm_max_pd(v.vec, dvec2_zero.vec), dvec2_one.vec);
	#else
		ret.x = saturate(v.x);
		ret.y = saturate(v.y);
	#endif
	return ret;
}

/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE dvec2 &lerp(dvec2 &ret, const dvec2 &v0, double v1, double k)
{
	#ifdef USE_SSE
		ret = _mm_add_pd(v0.vec, _mm_mul_pd(_mm_sub_pd(_mm_set1_pd(v1), v0.vec), _mm_set1_pd(k)));
	#else
		ret.x = lerp(v0.x, v1, k);
		ret.y = lerp(v0.y, v1, k);
	#endif
	return ret;
}
/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE dvec2 &lerp(dvec2 &ret, double v0, const dvec2 &v1, double k)
{
	#ifdef USE_SSE
		__m128d temp = _mm_set1_pd(v0);
		ret = _mm_add_pd(temp, _mm_mul_pd(_mm_sub_pd(v1.vec, temp), _mm_set1_pd(k)));
	#else
		ret.x = lerp(v0, v1.x, k);
		ret.y = lerp(v0, v1.y, k);
	#endif
	return ret;
}
/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE dvec2 &lerp(dvec2 &ret, const dvec2 &v0, const dvec2 &v1, double k)
{
	#ifdef USE_SSE
		ret = _mm_add_pd(v0.vec, _mm_mul_pd(_mm_sub_pd(v1.vec, v0.vec), _mm_set1_pd(k)));
	#else
		ret.x = lerp(v0.x, v1.x, k);
		ret.y = lerp(v0.y, v1.y, k);
	#endif
	return ret;
}
/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE dvec2 &lerp(dvec2 &ret, const dvec2 &v0, const dvec2 &v1, const dvec2 &k)
	{
	#ifdef USE_SSE
		ret = _mm_add_pd(v0.vec, _mm_mul_pd(_mm_sub_pd(v1.vec, v0.vec), k.vec));
	#else
		ret.x = lerp(v0.x, v1.x, k.x);
		ret.y = lerp(v0.y, v1.y, k.y);
	#endif
	return ret;
}
/// <summary>Returns the vector component values interpolated according to the formula v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE dvec2 lerp(const dvec2 &v0, const dvec2 &v1, double k)
{
	dvec2 ret;
	return lerp(ret, v0, v1, k);
}

/// <summary>Returns the value calculated according to the formula: (v - v0) / (v1 - v0) clamped within 0.0f and 1.0f.</summary>
UNIGINE_INLINE dvec2 &inverseLerp(dvec2 &ret, const dvec2 &v0, const dvec2 &v1, const dvec2 &v)
{
	ret = saturate((v - v0) / (v1 - v0));
	return ret;
}
/// <summary>Returns the value calculated according to the formula: (v - v0) / (v1 - v0) clamped within 0.0f and 1.0f.</summary>
UNIGINE_INLINE dvec2 inverseLerp(const dvec2 &v0, const dvec2 &v1, const dvec2 &v)
{
	dvec2 ret;
	return inverseLerp(ret, v0, v1, v);
}

/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE double dot(const dvec2 &v0, const dvec2 &v1)
{
	return v0.x * v1.x + v0.y * v1.y;
}

/// <summary>Returns an argument rounded to the nearest integral value.</summary>
UNIGINE_INLINE dvec2 round(const dvec2 &v) { return {round(v.x), round(v.y)}; }
/// <summary>Returns the largest integral value that's less than or equal to the argument.</summary>
UNIGINE_INLINE dvec2 floor(const dvec2 &v)
{
	#ifdef USE_SSE
		return _mm_floor_pd(v.vec);
	#else
		return {floor(v.x), floor(v.y)};
	#endif
}
/// <summary>Returns the smallest integral value that's greater than or equal to the argument.</summary>
UNIGINE_INLINE dvec2 ceil(const dvec2 &v)
{
	#ifdef USE_SSE
		return _mm_ceil_pd(v.vec);
	#else
		return {ceil(v.x), ceil(v.y)};
	#endif
}
/// <summary>Returns the absolute value of the specified argument.</summary>
UNIGINE_INLINE dvec2 abs(const dvec2 &v) { return {abs(v.x), abs(v.y)}; }

}
}