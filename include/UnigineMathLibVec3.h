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

struct alignas(16) vec3
{
	/// <summary>Constructor. Initializes the vector using given float values.</summary>
	UNIGINE_INLINE constexpr vec3(float v, ConstexprTag): x(v), y(v), z(v), align(0.0f) {}
	/// <summary>Constructor. Initializes the vector using given float values.</summary>
	UNIGINE_INLINE constexpr vec3(float x, float y, float z, ConstexprTag) : x(x), y(y), z(z), align(0.0f) {}

	/// <summary>Default constructor. Produces a zero vector.</summary>
	UNIGINE_INLINE vec3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, align(0.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using a given scalar value: x=v, y=v, z=v.</summary>
	UNIGINE_INLINE explicit vec3(float v)
		: x(v)
		, y(v)
		, z(v)
		, align(0.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using given float values.</summary>
	UNIGINE_INLINE vec3(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
		, align(0.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using a given pointer to the array of float elements: x=v[0], y=v[1], z=v[2].</summary>
	UNIGINE_INLINE explicit vec3(const float *v)
		: x(v[0])
		, y(v[1])
		, z(v[2])
		, align(0.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}

	/// <summary>Sets the vector using a two-component vec2 source vector and a scalar.</summary>
	UNIGINE_INLINE vec3(const vec2 &v, float z)
		: x(v.x)
		, y(v.y)
		, z(z)
		, align(0.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using a given two-component vec2 source vector: x=v.x, y=v.y, z=0.0f.</summary>
	UNIGINE_INLINE explicit vec3(const vec2 &v)
		: x(v.x)
		, y(v.y)
		, z(0.0f)
		, align(0.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}

	#ifdef USE_SSE
		UNIGINE_INLINE vec3(const vec3 &v): vec(v.vec)
		{
			UNIGINE_ASSERT_ALIGNED16(this);
		}
		UNIGINE_INLINE vec3(const __m128 &v): vec(v)
		{
			UNIGINE_ASSERT_ALIGNED16(this);
		}
		UNIGINE_INLINE vec3 &operator=(const __m128 &val) { vec =val; return *this; }
	#endif

	/// <summary>Constructor. Initializes the vector using a given vec4 source vector.</summary>
	UNIGINE_INLINE explicit vec3(const vec4 &v);
	/// <summary>Constructor. Initializes the vector using a given dvec3 source vector.</summary>
	UNIGINE_INLINE explicit vec3(const dvec3 &v);
	/// <summary>Constructor. Initializes the vector using a given hvec3 source vector.</summary>
	UNIGINE_INLINE explicit vec3(const hvec3 &v);
	/// <summary>Constructor. Initializes the vector using a given ivec3 source vector.</summary>
	UNIGINE_INLINE explicit vec3(const ivec3 &v);

	/// <summary>Sets the vector components equal to specified scalar value: x=val, y=val, z=val.</summary>
	UNIGINE_INLINE void set(float val)
	{
		x = val;
		y = val;
		z = val;
	}
	/// <summary>Sets the vector by components.</summary>
	UNIGINE_INLINE void set(float x_, float y_, float z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}
	/// <summary>Sets the vector using a two-component vec2 source vector and a scalar.</summary>
	UNIGINE_INLINE void set(const vec2 &val, float z_ = 0.0f)
	{
		x = val.x;
		y = val.y;
		z = z_;
	}
	/// <summary>Sets the vector equal to the specified source vector.</summary>
	UNIGINE_INLINE void set(const vec3 &val)
	{
		#ifdef USE_SSE
			vec = val.vec;
		#else
			x = val.x;
			y = val.y;
			z = val.z;
		#endif
	}
	/// <summary>Sets the vector using the array of float elements: x=val[0], y=val[1], z=val[2].</summary>
	UNIGINE_INLINE void set(const float *val)
	{
		x = val[0];
		y = val[1];
		z = val[2];
	}
	/// <summary>Sets the vector using a vec4 source vector: x=v.x, y=v.y, z=v.z.</summary>
	UNIGINE_INLINE void set(const vec4 &v);

	UNIGINE_INLINE void get(float *val) const
	{
		val[0] = x;
		val[1] = y;
		val[2] = z;
	}
	/// <summary>Returns the pointer to the vector.</summary>
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
		UNIGINE_ASSERT((unsigned int)i < 3 && "vec3::operator[](): bad index");
		return v[i];
	}
	/// <summary>Performs array access to the vector item by using given item index.</summary>
	UNIGINE_INLINE float operator[](int i) const
	{
		UNIGINE_ASSERT((unsigned int)i < 3 && "vec3::operator[](): bad index");
		return v[i];
	}


	/// <summary>Performs vector assignment. Destination vector = Source vector.</summary>
	UNIGINE_INLINE vec3 &operator=(const vec3 &v) { set(v); return *this; }
	/// <summary>Performs vector negation.</summary>
	UNIGINE_INLINE vec3 operator-() const { return vec3(-x, -y, -z); }


	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(float v)
	{
		#ifdef USE_SSE
			vec =_mm_mul_ps(vec, _mm_set_ps1(v));
		#else
			x *= v;
			y *= v;
			z *= v;
		#endif
	}
	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(const vec3 &v)
	{
		#ifdef USE_SSE
			vec =_mm_mul_ps(vec, v.vec);
		#else
			x *= v.x;
			y *= v.y;
			z *= v.z;
		#endif
	}
	/// <summary>Performs scalar multiplication.</summary>
	UNIGINE_INLINE vec3 &operator*=(float v) { mul(v); return *this; }
	/// <summary>Performs vector multiplication.</summary>
	UNIGINE_INLINE vec3 &operator*=(const vec3 &v) { mul(v); return *this; }

	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(float v) { mul(rcp(v)); }
	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(const vec3 &v)
	{
		#ifdef USE_SSE
			vec =_mm_div_ps(vec, v.vec);
		#else
			x /= v.x;
			y /= v.y;
			z /= v.z;
		#endif
	}
	/// <summary>Performs component-wise division of the vector by the scalar. Implemented using the calculation of inverse scalar value with subsequent component-wise multiplication.</summary>
	UNIGINE_INLINE vec3 &operator/=(float v) { div(v); return *this; }
	/// <summary>Performs component-wise division of vectors.</summary>
	UNIGINE_INLINE vec3 &operator/=(const vec3 &v) { div(v); return *this; }

	/// <summary>Returns the sum of vector components.</summary>
	UNIGINE_INLINE float sum() const { return x + y + z; }
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE void add(float v)
	{
		#ifdef USE_SSE
			vec =_mm_add_ps(vec, _mm_set_ps1(v));
		#else
			x += v;
			y += v;
			z += v;
		#endif
	}
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE void add(const vec3 &v)
	{
		#ifdef USE_SSE
			vec =_mm_add_ps(vec, v.vec);
		#else
			x += v.x;
			y += v.y;
			z += v.z;
		#endif
	}
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE vec3 &operator+=(float v) { add(v); return *this; }
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE vec3 &operator+=(const vec3 &v) { add(v); return *this; }
	
	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE void sub(float v)
	{
		#ifdef USE_SSE
			vec =_mm_sub_ps(vec, _mm_set_ps1(v));
		#else
			x -= v;
			y -= v;
			z -= v;
		#endif
	}
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE void sub(const vec3 &v)
	{
		#ifdef USE_SSE
			vec =_mm_sub_ps(vec, v.vec);
		#else
			x -= v.x;
			y -= v.y;
			z -= v.z;
		#endif
	}
	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE vec3 &operator-=(float v) { sub(v); return *this; }
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE vec3 &operator-=(const vec3 &v) { sub(v); return *this; }


	/// <summary>Returns the squared length of the vector.</summary>
	UNIGINE_INLINE float length2() const
	{
		#ifdef USE_SSE
			float ret;
			_mm_store_ss(&ret, _mm_dp_ps(vec, vec, 0x7f));
			return ret;
		#else
			return x * x + y * y + z * z;
		#endif
	}
	/// <summary>Returns the length of the vector.</summary>
	UNIGINE_INLINE float length() const { return toFloat(sqrt(length2())); }
	/// <summary>Returns the fast-calculated length of the vector.</summary>
	UNIGINE_INLINE float lengthFast() const
	{
		#ifdef USE_SSE
			float ret;
			_mm_store_ss(&ret, _mm_rcp_ss(_mm_rsqrt_ss(_mm_dp_ps(vec, vec, 0x7f))));
			return ret;
		#else
			return Math::sqrtFast(length2());
		#endif
	}
	/// <summary>Returns the inverted length of the vector.</summary>
	UNIGINE_INLINE float iLength() const { return Math::rsqrt(length2()); }
	/// <summary>Returns the fast-calculated inverted length of the vector.</summary>
	UNIGINE_INLINE float iLengthFast() const { return Math::rsqrtFast(length2()); }

	/// <summary>Returns a normalized vector.</summary>
	UNIGINE_INLINE vec3 &normalize()
	{
		#ifdef USE_SSE
			float length;
			_mm_store_ss(&length, _mm_dp_ps(vec, vec, 0x7f));
			vec =_mm_mul_ps(vec, _mm_set_ps1(Math::rsqrt(length)));
		#else
			mul(iLength());
		#endif
		return *this;
	}
	/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
	UNIGINE_INLINE vec3 &normalizeValid()
	{
		float length = length2();
		if (length != 0.0f)
			mul(Math::rsqrt(length));
		return *this;
	}
	/// <summary>Returns a normalized vector, calculated using the fast inverse square root algorithm.</summary>
	UNIGINE_INLINE vec3 &normalizeFast()
	{
		#ifdef USE_SSE
			vec =_mm_mul_ps(vec, _MM_SWIZZLE(_mm_rsqrt_ss(_mm_dp_ps(vec, vec, 0x7f)), X, X, X, X));
		#else
			mul(iLengthFast());
		#endif
		return *this;
	}
	/// <summary>Returns normalized vector, calculated using the fast inverse square root algorithm. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
	UNIGINE_INLINE vec3 &normalizeValidFast()
	{
		float length = length2();
		if (length != 0.0f)
			mul(Math::rsqrtFast(length));
		return *this;
	}

	/// <summary>Compares the X and Y components of the vector and returns the greater one.</summary>
	UNIGINE_INLINE float maxXY() const { return Math::max(x, y); }
	/// <summary>Compares all components of the vector and returns the greatest value.</summary>
	UNIGINE_INLINE float max() const { return Math::max(maxXY(), z); }

	/// <summary>Compares the X and Y components of the vector and returns the smaller one.</summary>
	UNIGINE_INLINE float minXY() { return Math::min(x, y); }
	/// <summary>Compares all components of the vector and returns the smallest value.</summary>
	UNIGINE_INLINE float min() { return Math::min(minXY(), z); }

	/// <summary>Returns a 64-bit hash generated for the vector.</summary>
	UNIGINE_INLINE unsigned long long hash64() const { return hashMixer(_hash.xy, (unsigned long long)_hash.z); }
	/// <summary>Returns a hash obtained by mixing the hash values of vector components.</summary>
	UNIGINE_INLINE unsigned int hash() const { return hashCombine(hashCombine(hashInteger(x), y), z); }

	/// <summary>Returns the absolute values of the vector components.</summary>
	UNIGINE_INLINE vec3 &abs()
	{
		x = Math::abs(x);
		y = Math::abs(y);
		z = Math::abs(z);
		return *this;
	}
	/// <summary>Returns a new vector that contains values representing signs of the corresponding vector components: 1 for non-negative values, and -1 for negative values.</summary>
	UNIGINE_INLINE vec3 sign() const { return vec3(Math::sign(x), Math::sign(y), Math::sign(z)); }

public:
	union
	{
		struct
		{
			float x, y, z, align;
		};
		vec2 xy;
		float v[3];

		struct
		{
			unsigned long long xy;
			unsigned int z;
		} _hash;

		#ifdef USE_SSE
			__m128 vec; // DO NOT TOUCH UNLESS ABSOLUTELY SURE
		#endif
	};
};

constexpr vec3 vec3_zero(0.0f, ConstexprTag{});
constexpr vec3 vec3_one(1.0f, ConstexprTag{});
constexpr vec3 vec3_half(0.5f, ConstexprTag{});
constexpr vec3 vec3_eps(Consts::EPS, ConstexprTag{});
constexpr vec3 vec3_inf(Consts::INF, ConstexprTag{});
constexpr vec3 vec3_up(0.0f, 0.0f, 1.0f, ConstexprTag{});
constexpr vec3 vec3_down(0.0f, 0.0f, -1.0f, ConstexprTag{});
constexpr vec3 vec3_forward(0.0f, 1.0f, 0.0f, ConstexprTag{});
constexpr vec3 vec3_back(0.0f, -1.0f, 0.0f, ConstexprTag{});
constexpr vec3 vec3_right(1.0f, 0.0f, 0.0f, ConstexprTag{});
constexpr vec3 vec3_left(-1.0f, 0.0f, 0.0f, ConstexprTag{});


/// <summary>Calculates the length of a given vector.</summary>
UNIGINE_INLINE float length(const vec3 &v) { return v.length(); }
/// <summary>Calculates the squared length of a given vector. This method is much faster than length() - the calculation is basically the same only without the slow Sqrt call. If you are using lengths simply to compare distances, then it is faster to compare squared lengths against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE float length2(const vec3 &v) { return v.length2(); }
/// <summary>Calculates the squared length of a given vector and handles cases where the result is NaN (Not a Number). If the squared length calculation results in NaN, the function returns 0.0f instead of the NaN value.</summary>
UNIGINE_INLINE float length2nan(const vec3 &v)
{
	float t = v.length2();
	return isNan(t) ? 0.0f : t;
}

/// <summary>Calculates the squared distance between the two given vectors. The squared distance is calculated as: length2(v0 - v1). This method is much faster than distance() - the calculation is basically the same only without the slow Sqrt call. If you simply want to compare distances, then it is faster to compare squared distances against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE float distance2(const vec3 &v0, const vec3 &v1)
{
	#ifdef USE_SSE
		float ret;
		__m128	vec = _mm_sub_ps(v0.vec, v1.vec);
		_mm_store_ss(&ret, _mm_dp_ps(vec, vec, 0x7f));
		return ret;
	#else
		return length2(v0 - v1);
	#endif
}
/// <summary>Calculates the distance between the two given vectors. The distance is calculated as: length(v0 - v1).</summary>
UNIGINE_INLINE float distance(const vec3 &v0, const vec3 &v1)
{
	#ifdef USE_SSE
		float ret;
		__m128	vec = _mm_sub_ps(v0.vec, v1.vec);
		_mm_store_ss(&ret, _mm_dp_ps(vec, vec, 0x7f));
		return sqrtf(ret);
	#else
		return length(v0 - v1);
	#endif
}

/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1.</summary>
UNIGINE_INLINE vec3 normalize(const vec3 &v)
{
	vec3 ret = v;
	return ret.normalize();
}
/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
UNIGINE_INLINE vec3 normalizeValid(const vec3 &v)
{
	vec3 ret = v;
	return ret.normalizeValid();
}

/// <summary>Compares two vectors according to the degree of precision equal to 1.0e-6f.</summary>
UNIGINE_INLINE int compare(const vec3 &v0, const vec3 &v1)
{
	return (compare(v0.x, v1.x) && compare(v0.y, v1.y) && compare(v0.z, v1.z));
}
/// <summary>Compares two vectors according to the specified degree of precision (epsilon).</summary>
UNIGINE_INLINE int compare(const vec3 &v0, const vec3 &v1, float epsilon)
{
	return (compare(v0.x, v1.x, epsilon) && compare(v0.y, v1.y, epsilon) && compare(v0.z, v1.z, epsilon));
}
/// <summary>Vector equal comparison.</summary>
UNIGINE_INLINE int operator==(const vec3 &v0, const vec3 &v1) { return compare(v0, v1); }
/// <summary>Vector not equal comparison.</summary>
UNIGINE_INLINE int operator!=(const vec3 &v0, const vec3 &v1) { return !compare(v0, v1); }

/// <summary>Vector less than comparison.</summary>
UNIGINE_INLINE int operator<(const vec3 &v0, const vec3 &v1) { return v0.x < v1.x && v0.y < v1.y && v0.z < v1.z; }
/// <summary>Vector greater than comparison.</summary>
UNIGINE_INLINE int operator>(const vec3 &v0, const vec3 &v1) { return v0.x > v1.x && v0.y > v1.y && v0.z > v1.z; }

/// <summary>Vector less than or equal comparison.</summary>
UNIGINE_INLINE int operator<=(const vec3 &v0, const vec3 &v1) { return v0.x <= v1.x && v0.y <= v1.y && v0.z <= v1.z; }
/// <summary>Vector greater than or equal comparison.</summary>
UNIGINE_INLINE int operator>=(const vec3 &v0, const vec3 &v1) { return v0.x >= v1.x && v0.y >= v1.y && v0.z >= v1.z; }

/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &mul(vec3 &ret, const vec3 &v0, float v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_mul_ps(v0.vec, _mm_set_ps1(v1));
	#else
		ret.x = v0.x * v1;
		ret.y = v0.y * v1;
		ret.z = v0.z * v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &mul(vec3 &ret, const vec3 &v0, const vec3 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_mul_ps(v0.vec, v1.vec);
	#else
		ret.x = v0.x * v1.x;
		ret.y = v0.y * v1.y;
		ret.z = v0.z * v1.z;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value.</summary>
UNIGINE_INLINE vec3 mul(const vec3 &v0, float v1)
{
	vec3 ret;
	return mul(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise multiplication of two vectors.</summary>
UNIGINE_INLINE vec3 mul(const vec3 &v0, const vec3 &v1)
{
	vec3 ret;
	return mul(ret, v0, v1);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec3 operator*(const vec3 &v0, float v1) { return mul(v0, v1); }
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec3 operator*(const vec3 &v0, const vec3 &v1) { return mul(v0, v1); }

/// <summary>Returns the result of a component-wise division of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &div(vec3 &ret, const vec3 &v0, float v1) { return mul(ret, v0, rcp(v1)); }
/// <summary>Returns the result of a component-wise division of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &div(vec3 &ret, const vec3 &v0, const vec3 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_div_ps(v0.vec, v1.vec);
	#else
		ret.x = v0.x / v1.x;
		ret.y = v0.y / v1.y;
		ret.z = v0.z / v1.z;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise division of a vector by a scalar value.</summary>
UNIGINE_INLINE vec3 div(const vec3 &v0, float v1)
{
	vec3 ret;
	return div(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise division of two vectors.</summary>
UNIGINE_INLINE vec3 div(const vec3 &v0, const vec3 &v1)
{
	vec3 ret;
	return div(ret, v0, v1);
}
/// <summary>Division operator.</summary>
UNIGINE_INLINE vec3 operator/(const vec3 &v0, float v1) { return div(v0, v1); }
/// <summary>Division operator.</summary>
UNIGINE_INLINE vec3 operator/(const vec3 &v0, const vec3 &v1) { return div(v0, v1); }


/// <summary>Returns the result of a component-wise addition of a vector with a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &add(vec3 &ret, const vec3 &v0, float v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(v0.vec, _mm_set_ps1(v1));
	#else
		ret.x = v0.x + v1;
		ret.y = v0.y + v1;
		ret.z = v0.z + v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise addition of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &add(vec3 &ret, const vec3 &v0, const vec3 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(v0.vec, v1.vec);
	#else
		ret.x = v0.x + v1.x;
		ret.y = v0.y + v1.y;
		ret.z = v0.z + v1.z;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise addition of a vector with a scalar value.</summary>
UNIGINE_INLINE vec3 add(const vec3 &v0, float v1)
{
	vec3 ret;
	return add(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise addition of two vectors.</summary>
UNIGINE_INLINE vec3 add(const vec3 &v0, const vec3 &v1)
{
	vec3 ret;
	return add(ret, v0, v1);
}
/// <summary>Addition operator.</summary>
UNIGINE_INLINE vec3 operator+(const vec3 &v0, float v1) { return add(v0, v1); }
/// <summary>Addition operator.</summary>
UNIGINE_INLINE vec3 operator+(const vec3 &v0, const vec3 &v1) { return add(v0, v1); }

/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &sub(vec3 &ret, const vec3 &v0, float v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_sub_ps(v0.vec, _mm_set_ps1(v1));
	#else
		ret.x = v0.x - v1;
		ret.y = v0.y - v1;
		ret.z = v0.z - v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1) by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &sub(vec3 &ret, const vec3 &v0, const vec3 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_sub_ps(v0.vec, v1.vec);
	#else
		ret.x = v0.x - v1.x;
		ret.y = v0.y - v1.y;
		ret.z = v0.z - v1.z;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector.</summary>
UNIGINE_INLINE vec3 sub(const vec3 &v0, float v1)
{
	vec3 ret;
	return sub(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1).</summary>
UNIGINE_INLINE vec3 sub(const vec3 &v0, const vec3 &v1)
{
	vec3 ret;
	return sub(ret, v0, v1);
}
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE vec3 operator-(const vec3 &v0, float v1) { return sub(v0, v1); }
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE vec3 operator-(const vec3 &v0, const vec3 &v1) { return sub(v0, v1); }

/// <summary>Returns the result of multiplication of each component of the first vector by the float value and addition of the corresponding component of the second vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE vec3 &mad(vec3 &ret, const vec3 &v0, float v1, const vec3 &v2)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(_mm_mul_ps(v0.vec, _mm_set_ps1(v1)), v2.vec);
	#else
		ret.x = v0.x * v1 + v2.x;
		ret.y = v0.y * v1 + v2.y;
		ret.z = v0.z * v1 + v2.z;
	#endif
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE vec3 &mad(vec3 &ret, const vec3 &v0, const vec3 &v1, const vec3 &v2)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(_mm_mul_ps(v0.vec, v1.vec), v2.vec);
	#else
		ret.x = v0.x * v1.x + v2.x;
		ret.y = v0.y * v1.y + v2.y;
		ret.z = v0.z * v1.z + v2.z;
	#endif
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the float value and addition of the corresponding component of the second vector (a * b + c).</summary>
UNIGINE_INLINE vec3 mad(const vec3 &v0, float v1, const vec3 &v2)
{
	vec3 ret;
	return mad(ret, v0, v1, v2);
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c).</summary>
UNIGINE_INLINE vec3 mad(const vec3 &v0, const vec3 &v1, const vec3 &v2)
{
	vec3 ret;
	return mad(ret, v0, v1, v2);
}

/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE float dot(const vec2 &v0, const vec3 &v1) { return v0.x * v1.x + v0.y * v1.y + v1.z; }
/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE float dot(const vec3 &v0, const vec2 &v1) { return v0.x * v1.x + v0.y * v1.y + v0.z; }
/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE float dot(const vec3 &v0, const vec3 &v1)
{
	#ifdef USE_SSE
		float ret;
		_mm_store_ss(&ret, _mm_dp_ps(v0.vec, v1.vec, 0x7f));
		return ret;
	#else
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	#endif
}

/// <summary>Compares the arguments component-wise and returns the minimum value for each component by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &min(vec3 &ret, const vec3 &v0, const vec3 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_min_ps(v0.vec, v1.vec);
	#else
		ret.x = min(v0.x, v1.x);
		ret.y = min(v0.y, v1.y);
		ret.z = min(v0.z, v1.z);
	#endif
	return ret;
}
/// <summary>Compares each vector component with the float value and returns the minimum value for each component by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &min(vec3 &ret, const vec3 &v0, float v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_min_ps(v0.vec, _mm_set_ps1(v1));
	#else
		ret.x = min(v0.x, v1);
		ret.y = min(v0.y, v1);
		ret.z = min(v0.z, v1);
	#endif
	return ret;
}
/// <summary>Compares the arguments component-wise and returns the minimum value for each component.</summary>
UNIGINE_INLINE vec3 min(const vec3 &v0, const vec3 &v1)
{
	vec3 ret;
	return min(ret, v0, v1);
}
/// <summary>Compares each vector component with the float value and returns the minimum value for each component.</summary>
UNIGINE_INLINE vec3 min(const vec3 &v0, float v1)
{
	vec3 ret;
	return min(ret, v0, v1);
}

/// <summary>Compares the arguments component-wise and returns the maximum value for each component by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &max(vec3 &ret, const vec3 &v0, const vec3 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_max_ps(v0.vec, v1.vec);
	#else
		ret.x = max(v0.x, v1.x);
		ret.y = max(v0.y, v1.y);
		ret.z = max(v0.z, v1.z);
	#endif
	return ret;
}
/// <summary>Compares each vector component with the float value and returns the maximum value for each component by saving it in the ret argument.</summary>
UNIGINE_INLINE vec3 &max(vec3 &ret, const vec3 &v0, float v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_max_ps(v0.vec, _mm_set_ps1(v1));
	#else
		ret.x = max(v0.x, v1);
		ret.y = max(v0.y, v1);
		ret.z = max(v0.z, v1);
	#endif
	return ret;
}
/// <summary>Compares the arguments component-wise and returns the maximum value for each component.</summary>
UNIGINE_INLINE vec3 max(const vec3 &v0, const vec3 &v1)
{
	vec3 ret;
	return max(ret, v0, v1);
}
/// <summary>Compares each vector component with the float value and returns the maximum value for each component.</summary>
UNIGINE_INLINE vec3 max(const vec3 &v0, float v1)
{
	vec3 ret;
	return max(ret, v0, v1);
}

/// <summary>Clamps the value (v) within the minimum (v0) and maximum (v1) limits and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec3 &clamp(vec3 &ret, const vec3 &v, const vec3 &v0, const vec3 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_min_ps(_mm_max_ps(v.vec, v0.vec), v1.vec);
	#else
		ret.x = clamp(v.x, v0.x, v1.x);
		ret.y = clamp(v.y, v0.y, v1.y);
		ret.z = clamp(v.z, v0.z, v1.z);
	#endif
	return ret;
}
/// <summary>Clamps the value (v) within the minimum (v0) and maximum (v1) limits and returns the result.</summary>
UNIGINE_INLINE vec3 clamp(const vec3 &v, const vec3 &v0, const vec3 &v1)
{
	vec3 ret;
	return clamp(ret, v, v0, v1);
}

/// <summary>Clamps the vector component values within the range [0.0, 1.0] and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec3 &saturate(vec3 &ret, const vec3 &v)
{
	#ifdef USE_SSE
		ret.vec = _mm_min_ps(_mm_max_ps(v.vec, vec3_zero.vec), vec3_one.vec);
	#else
		ret.x = saturate(v.x);
		ret.y = saturate(v.y);
		ret.z = saturate(v.z);
	#endif
	return ret;
}
/// <summary>Clamps the vector component values within the range [0.0, 1.0] and returns the result.</summary>
UNIGINE_INLINE vec3 saturate(const vec3 &v)
{
	vec3 ret;
	return saturate(ret, v);
}

/// <summary>Interpolates the vector component values according to the formula  v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec3 &lerp(vec3 &ret, const vec3 &v0, const vec3 &v1, float k)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(v0.vec, _mm_mul_ps(_mm_sub_ps(v1.vec, v0.vec), _mm_set_ps1(k)));
	#else
		ret.x = lerp(v0.x, v1.x, k);
		ret.y = lerp(v0.y, v1.y, k);
		ret.z = lerp(v0.z, v1.z, k);
	#endif
	return ret;
}
/// <summary>Returns the vector component values interpolated according to the formula  v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE vec3 lerp(const vec3 &v0, const vec3 &v1, float k)
{
	vec3 ret;
	return lerp(ret, v0, v1, k);
}

/// <summary>Interpolates the vector component values according to the formula  v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec3 &lerp(vec3 &ret, const vec3 &v0, const vec3 &v1, const vec3 &k)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(v0.vec, _mm_mul_ps(_mm_sub_ps(v1.vec, v0.vec), k.vec));
	#else
		ret.x = lerp(v0.x, v1.x, k);
		ret.y = lerp(v0.y, v1.y, k);
		ret.z = lerp(v0.z, v1.z, k);
	#endif
	return ret;
}
/// <summary>Returns the vector component values interpolated according to the formula  v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE vec3 lerp(const vec3 &v0, const vec3 &v1, const vec3 &k)
{
	vec3 ret;
	return lerp(ret, v0, v1, k);
}

/// <summary>Returns the cross product of two vectors.</summary>
UNIGINE_INLINE vec3 &cross(vec3 &ret, const vec3 &v0, const vec3 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_cross_ps(v0.vec, v1.vec);
	#else
		ret.x = v0.y * v1.z - v0.z * v1.y;
		ret.y = v0.z * v1.x - v0.x * v1.z;
		ret.z = v0.x * v1.y - v0.y * v1.x;
	#endif
	return ret;
}
/// <summary>Returns the cross product of two vectors.</summary>
UNIGINE_INLINE vec3 cross(const vec3 &v0, const vec3 &v1)
{
	vec3 ret;
	return cross(ret, v0, v1);
}

/// <summary>Computes the reflection of a vector (v0) about another vector (v1) and stores the result in the ret value.</summary>
UNIGINE_INLINE vec3 &reflect(vec3 &ret, const vec3 &v0, const vec3 &v1)
{
	float k = dot(v0, v1) * 2.0f;
	#ifdef USE_SSE
		ret.vec = _mm_sub_ps(v0.vec, _mm_mul_ps(v1.vec, _mm_set_ps1(k)));
	#else
		ret.x = v0.x - v1.x * k;
		ret.y = v0.y - v1.y * k;
		ret.z = v0.z - v1.z * k;
	#endif
	return ret;
}
/// <summary>Returns the reflection of a vector (v0) about another vector (v1).</summary>
UNIGINE_INLINE vec3 reflect(const vec3 &v0, const vec3 &v1)
{
	vec3 ret;
	return reflect(ret, v0, v1);
}

/// <summary>Returns an argument rounded to the nearest integral value.</summary>
UNIGINE_INLINE vec3 round(const vec3 &v)
{
	return {round(v.x), round(v.y), round(v.z)};
}
/// <summary>Returns the largest integral value that's less than or equal to the argument.</summary>
UNIGINE_INLINE vec3 floor(const vec3 &v)
{
	#ifdef USE_SSE
		return _mm_floor_ps(v.vec);
	#else
		return {floor(v.x), floor(v.y), floor(v.z)};
	#endif
}
/// <summary>Returns the smallest integral value that's greater than or equal to the argument.</summary>
UNIGINE_INLINE vec3 ceil(const vec3 &v)
{
	#ifdef USE_SSE
		return _mm_ceil_ps(v.vec);
	#else
		return {ceil(v.x), ceil(v.y), ceil(v.z)};
	#endif
}

/// <summary>Returns the fractional part of the argument.</summary>
UNIGINE_INLINE vec3 frac(const vec3 &v) { return {frac(v.x), frac(v.y), frac(v.z)}; }
/// <summary>Returns the absolute value of the specified argument.</summary>
UNIGINE_INLINE vec3 abs(const vec3 &v) { return {abs(v.x), abs(v.y), abs(v.z)}; }

/// <summary>Performs a component-wise comparison between two arguments, and returns a new vector with a component set to 1.0 if the corresponding component in a is greater than in b, and 0.0 otherwise.</summary>
UNIGINE_INLINE vec3 step(const vec3 &a, const vec3 &b)
{
	return {toFloat(a.x > b.x), toFloat(a.y > b.y), toFloat(a.z > b.z)};
}
/// <summary>Performs a component-wise comparison between two arguments, and returns a new vector with a component set to 1.0 if the corresponding component in a is greater than in b, and 0.0 otherwise.</summary>
UNIGINE_INLINE vec3 step(const vec3 &a, float b)
{
	return {toFloat(a.x > b), toFloat(a.y > b), toFloat(a.z > b)};
}

/// <summary>Returns the value calculated according to the formula: (v - v0) / (v1 - v0) clamped within 0.0f and 1.0f.</summary>
UNIGINE_INLINE vec3 inverseLerp(const vec3 &v0, const vec3 &v1, const vec3 &v)
{
	return saturate((v - v0) / (v1 - v0));
}

/// <summary>Performs a smooth interpolation between two vectors (point_a and point_b) using a specified coefficient range to create a smooth transition effect.</summary>
UNIGINE_INLINE vec3 contrastLerp(const vec3 &point_a, const vec3 &point_b, float coef_min_bound, float coef_max_bound, float coef)
{
	return lerp(point_a, point_b, smoothstep(coef_min_bound, coef_max_bound, coef));
}

/// <summary>Combines two vectors using an overlay blending effect, using the additional x value that determines the interpolation level between the vectors.</summary>
UNIGINE_INLINE vec3 overlay(const vec3 &a, const vec3 &b, float x)
{
	return max(lerp(a, lerp(vec3_one - (vec3_one - a) * (vec3_one - b) * 2.0f, a * b * 2.0f, step(a, vec3_half)), x), vec3_zero);
}
/// <summary>Combines two vectors using an overlay blending effect, using the additional x value that determines the interpolation level between the vectors.</summary>
UNIGINE_INLINE vec3 overlay(const vec3 &a, const vec3 &b, const vec3 &x)
{
	return max(lerp(a, lerp(vec3_one - (vec3_one - a) * (vec3_one - b) * 2.0f, a * b * 2.0f, step(a, vec3_half)), x), vec3_zero);
}

/// <summary>Checks if the vectors are collinear.</summary>
UNIGINE_INLINE bool areCollinear(const vec3 &v0, const vec3 &v1) { return length(cross(v0, v1)) < 1e-6f; }

/// <summary>Converts RGB color value to sRGB format.</summary>
UNIGINE_INLINE vec3 srgb(const vec3 &color) { return vec3(srgb(color.x), srgb(color.y), srgb(color.z)); }
/// <summary>Converts sRGB color value to RGB format.</summary>
UNIGINE_INLINE vec3 isrgb(const vec3 &color) { return vec3(isrgb(color.x), isrgb(color.y), isrgb(color.z)); }

/// <summary>Returns the perceived brightness of the color.</summary>
UNIGINE_INLINE float rgbToLuma(const vec3 &color)
{
	return dot(color, vec3(0.299f, 0.587f, 0.114f));
}

/// <summary>Returns the angle (in degrees) between the given first and second vectors. The angle returned is the unsigned acute angle between the two vectors. This means the smaller of the two possible angles is used.</summary>
UNIGINE_INLINE float getAngle(const vec3 &v0, const vec3 &v1)
{
	float d = dot(v0, v1) / (length(v0) * length(v1));
	return acos(clamp(d, -1.0f, 1.0f)) * Consts::RAD2DEG;
}
/// <summary>Returns the angle (in degrees) between the given first and second vectors. The angle returned is the unsigned acute angle between the two vectors. This means the smaller of the two possible angles is used.</summary>
UNIGINE_INLINE float getAngle(const vec3 &v0, const vec3 &v1, const vec3 &up)
{
	vec3 n = cross(v0, v1);
	return atan2(dot(normalize(up), n), dot(v0, v1)) * Consts::RAD2DEG;
}


}
}
