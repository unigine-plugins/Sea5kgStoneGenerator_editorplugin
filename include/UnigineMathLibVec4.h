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
#include "UnigineMathLibVec2.h"
#include "UnigineMathLibVec3.h"

namespace Unigine
{
namespace Math
{

struct alignas(16) vec4
{
	/// <summary>Constructor. Initializes the vector using the given values.</summary>
	UNIGINE_INLINE constexpr vec4(float v, ConstexprTag): x(v), y(v), z(v), w(v) {}
	/// <summary>Constructor. Initializes the vector using the given values.</summary>
	UNIGINE_INLINE constexpr vec4(float x, float y, float z, float w, ConstexprTag): x(x), y(y), z(z), w(w) {}

	/// <summary>Default constructor. Produces a zero vector.</summary>
	UNIGINE_INLINE vec4()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using a given scalar value: x=v, y=v, z=v, w=v.</summary>
	UNIGINE_INLINE explicit vec4(float v)
		: x(v)
		, y(v)
		, z(v)
		, w(v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using given float values.</summary>
	UNIGINE_INLINE vec4(float x, float y, float z = 0.0f, float w = 0.0f)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using a given pointer to the array of float elements: x=v[0], y=v[1], z=v[2], w=v[3].</summary>
	UNIGINE_INLINE explicit vec4(const float *v)
		: x(v[0])
		, y(v[1])
		, z(v[2])
		, w(v[3])
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector by copying a given source vector.</summary>
	UNIGINE_INLINE vec4(const vec4 &v)
	{
		set(v);
		UNIGINE_ASSERT_ALIGNED16(this);
	}

	/// <summary>Constructor. Initializes the vector using a given two-component vec2 source vector: x=v.x, y=v.y, z=0.0f, w=1.0f.</summary>
	UNIGINE_INLINE explicit vec4(const vec2 &v)
		: x(v.x)
		, y(v.y)
		, z(0.0f)
		, w(1.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Sets the vector using a two-component vec2 source vector and two scalars.</summary>
	UNIGINE_INLINE vec4(const vec2 &v, float z, float w)
		: x(v.x)
		, y(v.y)
		, z(z)
		, w(w)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using the values of two vec2 source vectors.</summary>
	UNIGINE_INLINE explicit vec4(const vec2 &v0, const vec2 &v1)
		: x(v0.x)
		, y(v0.y)
		, z(v1.x)
		, w(v1.y)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}

	/// <summary>Constructor. Initializes the vector using a given three-component vec3 source vector: x=v.x, y=v.y, z=v.z, w=1.0f.</summary>
	UNIGINE_INLINE explicit vec4(const vec3 &v)
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(1.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using a given three-component vec3 source vector and a scalar.</summary>
	UNIGINE_INLINE vec4(const vec3 &v, float w)
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(w)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}

	/// <summary>Constructor. Initializes the vector using a given dvec4 source vector.</summary>
	UNIGINE_INLINE explicit vec4(const dvec4 &v);
	/// <summary>Constructor. Initializes the vector using given two dvec2 source vectors.</summary>
	UNIGINE_INLINE explicit vec4(const dvec2 &v0, const dvec2 &v1);
	/// <summary>Constructor. Initializes the vector using a given hvec4 source vector.</summary>
	UNIGINE_INLINE explicit vec4(const hvec4 &v);
	/// <summary>Constructor. Initializes the vector using a given ivec4 source vector.</summary>
	UNIGINE_INLINE explicit vec4(const ivec4 &v);
	/// <summary>Constructor. Initializes the vector using a given bvec4 source vector.</summary>
	UNIGINE_INLINE explicit vec4(const bvec4 &v);
	/// <summary>Constructor. Initializes the vector using a given svec4 source vector.</summary>
	UNIGINE_INLINE explicit vec4(const svec4 &v);
	/// <summary>Constructor. Initializes the vector using a given source quaternion.</summary>
	UNIGINE_INLINE explicit vec4(const quat &q)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(q);
	}


	/// <summary>Sets the vector components equal to specified scalar value: x=val, y=val, z=val, w=val.</summary>
	UNIGINE_INLINE void set(float v) { x = v; y = v; z = v; w = v; }
	/// <summary>Sets the vector by components.</summary>
	UNIGINE_INLINE void set(float x_, float y_, float z_, float w_) { x = x_; y = y_; z = z_; w = w_; }
	/// <summary>Sets the vector using a two-component vec2 source vector and two scalars.</summary>
	UNIGINE_INLINE void set(const vec2 &v, float z_ = 0.0f, float w_ = 1.0f)
	{
		x = v.x;
		y = v.y;
		z = z_;
		w = w_;
	}
	/// <summary>Sets the vector using a three-component vec3 source vector and a scalar.</summary>
	UNIGINE_INLINE void set(const vec3 &v, float w_ = 1.0f)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = w_;
	}
	/// <summary>Sets the vector equal to the specified source vector.</summary>
	UNIGINE_INLINE void set(const vec4 &v)
	{
		#ifdef USE_SSE
			vec = v.vec;
		#else
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
		#endif
	}
	/// <summary>Sets the vector using the array of float elements: x=val[0], y=val[1], z=val[2], w=val[3].</summary>
	UNIGINE_INLINE void set(const float *v)
	{
		x = v[0];
		y = v[1];
		z = v[2];
		w = v[3];
	}
	/// <summary>Sets the vector using a quaternion.</summary>
	UNIGINE_INLINE void set(const quat &q);

	/// <summary>Returns the pointer to the array of float elements: val[0]=x, val[1]=y, val[2]=z, val[3]=w.</summary>
	UNIGINE_INLINE void get(float *v) const
	{
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;
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
		UNIGINE_ASSERT((unsigned int)i < 4 && "vec4::operator[](): bad index");
		return v[i];
	}
	/// <summary>Performs array access to the vector item by using given item index.</summary>
	UNIGINE_INLINE float operator[](int i) const
	{
		UNIGINE_ASSERT((unsigned int)i < 4 && "vec4::operator[](): bad index");
		return v[i];
	}

	
	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(float v)
	{
		#ifdef USE_SSE
			vec = _mm_mul_ps(vec, _mm_set_ps1(v));
		#else
			x *= v;
			y *= v;
			z *= v;
			w *= v;
		#endif
	}
	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(const vec4 &v)
	{
		#ifdef USE_SSE
			vec = _mm_mul_ps(vec, v.vec);
		#else
			x *= v.x;
			y *= v.y;
			z *= v.z;
			w *= v.w;
		#endif
	}
	/// <summary>Multiplies the X, Y, and Z components of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul3(float v)
	{
		x *= v;
		y *= v;
		z *= v;
	}
	/// <summary>Performs scalar multiplication.</summary>
	UNIGINE_INLINE vec4 &operator*=(float v) { mul(v); return *this; }
	/// <summary>Performs vector multiplication.</summary>
	UNIGINE_INLINE vec4 &operator*=(const vec4 &v) { mul(v); return *this; }

	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(float v) { mul(rcp(v)); }
	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(const vec4 &v)
	{
		#ifdef USE_SSE
			vec = _mm_div_ps(vec, v.vec);
		#else
			x /= v.x;
			y /= v.y;
			z /= v.z;
			w /= v.w;
		#endif
	}
	/// <summary>Performs component-wise division of the vector by the scalar. Implemented using the calculation of inverse scalar value with subsequent component-wise multiplication.</summary>
	UNIGINE_INLINE vec4 &operator/=(float v) { div(v); return *this; }
	/// <summary>Performs component-wise division of vectors.</summary>
	UNIGINE_INLINE vec4 &operator/=(const vec4 &v) { div(v); return *this; }

	/// <summary>Returns the sum of vector components.</summary>
	UNIGINE_INLINE float sum() const { return x + y + z + w; }
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE void add(float v)
	{
		#ifdef USE_SSE
			vec = _mm_add_ps(vec, _mm_set_ps1(v));
		#else
			x += v;
			y += v;
			z += v;
			w += v;
		#endif
	}
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE void add(const vec4 &v)
	{
		#ifdef USE_SSE
			vec = _mm_add_ps(vec, v.vec);
		#else
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		#endif
	}
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE vec4 &operator+=(float v) { add(v); return *this; }
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE vec4 &operator+=(const vec4 &v) { add(v); return *this; }

	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE void sub(float v)
	{
		#ifdef USE_SSE
			vec = _mm_sub_ps(vec, _mm_set_ps1(v));
		#else
			x -= v;
			y -= v;
			w -= v;
			z -= v;
		#endif
	}
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE void sub(const vec4 &v)
	{
		#ifdef USE_SSE
			vec = _mm_sub_ps(vec, v.vec);
		#else
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
		#endif
	}
	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE vec4 &operator-=(float v) { sub(v); return *this; }
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE vec4 &operator-=(const vec4 &v) { sub(v); return *this; }


	#ifdef USE_SSE
		UNIGINE_INLINE vec4(const __m128 &v): vec(v)
		{
			UNIGINE_ASSERT_ALIGNED16(this);
		}
		UNIGINE_INLINE vec4 &operator=(const __m128 &v) { vec = v; return *this; }
	#endif
	/// <summary>Performs vector assignment. Destination vector = Source vector.</summary>
	UNIGINE_INLINE vec4 &operator=(const vec4 &v) { set(v); return *this; }
	/// <summary>Sets each vector component equal to specified scalar value.</summary>
	UNIGINE_INLINE vec4 &operator=(const float v) { set(v); return *this; }
	/// <summary>Performs vector negation.</summary>
	UNIGINE_INLINE vec4 operator-() const { return vec4(-x, -y, -z, -w); }


	/// <summary>Returns the squared length of the vector.</summary>
	UNIGINE_INLINE float length2() const
	{
		#ifdef USE_SSE
			float ret;
			_mm_store_ss(&ret, _mm_dp_ps(vec, vec, 0xff));
			return ret;
		#else
			return x * x + y * y + z * z + w * w;
		#endif
	}
	/// <summary>Returns the length of the vector.</summary>
	UNIGINE_INLINE float length() const { return toFloat(sqrt(length2())); }
	/// <summary>Returns the fast-calculated length of the vector.</summary>
	UNIGINE_INLINE float lengthFast() const { return Math::sqrtFast(length2()); }
	/// <summary>Returns the inverted length of the vector.</summary>
	UNIGINE_INLINE float iLength() const { return Math::rsqrt(length2()); }
	/// <summary>Returns the fast-calculated inverted length of the vector.</summary>
	UNIGINE_INLINE float iLengthFast() const { return Math::rsqrtFast(length2()); }

	/// <summary>Returns a normalized vector.</summary>
	UNIGINE_INLINE vec4 &normalize()
	{
		#ifdef USE_SSE
			float length;
			_mm_store_ss(&length, _mm_dp_ps(vec, vec, 0xff));
			vec = _mm_mul_ps(vec, _mm_set_ps1(Math::rsqrt(length)));
		#else
			mul(iLength());
		#endif
		return *this;
	}
	/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
	UNIGINE_INLINE vec4 &normalizeValid()
	{
		float length = length2();
		if (length != 0.0f)
			mul(Math::rsqrt(length));
		return *this;
	}
	/// <summary>Returns a normalized vector, calculated using the fast inverse square root algorithm.</summary>
	UNIGINE_INLINE vec4 &normalizeFast()
	{
		mul(iLengthFast());
		return *this;
	}
	/// <summary>Returns normalized vector, calculated using the fast inverse square root algorithm. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
	UNIGINE_INLINE vec4 &normalizeValidFast()
	{
		float length = length2();
		if (length != 0.0f)
			mul(Math::rsqrtFast(length));
		return *this;
	}

	/// <summary>Returns the vector with normalized XYZ components.</summary>
	UNIGINE_INLINE vec4 &normalize3() { mul3(xyz.iLength()); return *this; }
	/// <summary>Returns the vector with normalized XYZ components. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
	UNIGINE_INLINE vec4 &normalizeValid3()
	{
		float length = xyz.length2();
		if (length != 0.0f)
			mul3(Math::rsqrt(length));
		return *this;
	}
	/// <summary>Returns the vector with XYZ components normalized using the fast inverse square root algorithm.</summary>
	UNIGINE_INLINE vec4 &normalizeFast3() { mul3(xyz.iLength()); return *this; }
	/// <summary>Returns the vector with XYZ components normalized using the fast inverse square root algorithm. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
	UNIGINE_INLINE vec4 &normalizeValidFast3()
	{
		float length = xyz.length2();
		if (length != 0.0f)
			mul3(Math::rsqrtFast(length));
		return *this;
	}

	/// <summary>Returns the absolute values of the vector components.</summary>
	UNIGINE_INLINE vec4 &abs()
	{
		x = Math::abs(x);
		y = Math::abs(y);
		z = Math::abs(z);
		w = Math::abs(w);
		return *this;
	}

	/// <summary>Compares the X and Y components of the vector and returns the greater one.</summary>
	UNIGINE_INLINE float maxXY() const { return Math::max(x, y); }
	/// <summary>Compares the X, Y, and Z components of the vector and returns the greatest one.</summary>
	UNIGINE_INLINE float maxXYZ() const { return Math::max(maxXY(), z); }
	/// <summary>Compares all components of the vector and returns the greatest value.</summary>
	UNIGINE_INLINE float max() const { return Math::max(maxXYZ(), w); }

	/// <summary>Returns a 64-bit hash generated for the vector.</summary>
	UNIGINE_INLINE unsigned long long hash64() const { return hashMixer(_hash.xy, _hash.zw); }
	/// <summary>Returns a hash obtained by mixing the hash values of vector components.</summary>
	UNIGINE_INLINE unsigned int hash() const { return hashCombine(hashCombine(hashCombine(hashInteger(x), y), z), w); }

	/// <summary>Converts a color string in the Web format (RRGGBB / #RRGGBB or RRGGBBAA / #RRGGBBAA) into its vec4 equivalent.</summary>
	UNIGINE_INLINE static vec4 parseColor(const char *str);

public:
	union
	{
		struct
		{
			float x, y, z, w;
		};

		const vec3 xyz;
		vec2 xy;

		struct
		{
			vec2 xy;
			vec2 zw;
		} swizzle;

		float v[4];

		struct
		{
			unsigned long long xy;
			unsigned long long zw;
		} _hash;

		#ifdef USE_SSE
			__m128 vec; // DO NOT TOUCH UNLESS ABSOLUTELY SURE
		#endif
	};

}; // end class vec4

constexpr vec4 vec4_zero(0.0f, ConstexprTag{});
constexpr vec4 vec4_one(1.0f, ConstexprTag{});
constexpr vec4 vec4_half(0.5f, ConstexprTag{});
constexpr vec4 vec4_eps(Consts::EPS, ConstexprTag{});
constexpr vec4 vec4_inf(Consts::INF, ConstexprTag{});
constexpr vec4 vec4_white(1.0f, ConstexprTag{});
constexpr vec4 vec4_black(0.0f, 0.0f, 0.0f, 1.0f, ConstexprTag{});
constexpr vec4 vec4_red(1.0f, 0.0f, 0.0f, 1.0f, ConstexprTag{});
constexpr vec4 vec4_green(0.0f, 1.0f, 0.0f, 1.0f, ConstexprTag{});
constexpr vec4 vec4_blue(0.0f, 0.0f, 1.0f, 1.0f, ConstexprTag{});

/// <summary>Calculates the length of a given vector.</summary>
UNIGINE_INLINE float length(const vec4 &v) { return v.length(); }
/// <summary>Calculates the squared length of a given vector. This method is much faster than length() - the calculation is basically the same only without the slow Sqrt call. If you are using lengths simply to compare distances, then it is faster to compare squared lengths against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE float length2(const vec4 &v) { return v.length2(); }

/// <summary>Calculates the squared distance between the two given vectors. The squared distance is calculated as: length2(v0 - v1). This method is much faster than distance() - the calculation is basically the same only without the slow Sqrt call. If you simply want to compare distances, then it is faster to compare squared distances against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE float distance2(const vec4 &v0, const vec4 &v1)
{
	#ifdef USE_SSE
		float ret;
		__m128	vec = _mm_sub_ps(v0.vec, v1.vec);
		_mm_store_ss(&ret, _mm_dp_ps(vec, vec, 0xff));
		return ret;
	#else
		return length2(v0 - v1);
	#endif
}
/// <summary>Calculates the distance between the two given vectors. The distance is calculated as: length(v0 - v1).</summary>
UNIGINE_INLINE float distance(const vec4 &v0, const vec4 &v1)
{
	#ifdef USE_SSE
		float ret;
		__m128	vec = _mm_sub_ps(v0.vec, v1.vec);
		_mm_store_ss(&ret, _mm_dp_ps(vec, vec, 0xff));
		return sqrtf(ret);
	#else
		return length(v0 - v1);
	#endif
}

/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1.</summary>
UNIGINE_INLINE vec4 normalize(const vec4 &v)
{
	vec4 ret = v;
	return ret.normalize();
}
/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
UNIGINE_INLINE vec4 normalizeValid(const vec4 &v)
{
	vec4 ret = v;
	return ret.normalizeValid();
}

/// <summary>Normalizes a vector making its magnitude equal to 1. The vector is normalized as if it has only the first three components (the fourth one is ignored).</summary>
UNIGINE_INLINE vec4 normalize3(const vec4 &v)
{
	vec4 ret = v;
	return ret.normalize3();
}
/// <summary>Normalizes a vector making its magnitude equal to 1. The vector is normalized as if it has only the first three components (the fourth one is ignored). Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
UNIGINE_INLINE vec4 normalizeValid3(const vec4 &v)
{
	vec4 ret = v;
	return ret.normalizeValid3();
}

/// <summary>Compares two vectors according to the degree of precision equal to 1.0e-6f.</summary>
UNIGINE_INLINE int compare(const vec4 &v0, const vec4 &v1)
{
	return (compare(v0.x, v1.x) && compare(v0.y, v1.y) && compare(v0.z, v1.z) && compare(v0.w, v1.w));
}
/// <summary>Compares two vectors according to the specified degree of precision (epsilon).</summary>
UNIGINE_INLINE int compare(const vec4 &v0, const vec4 &v1, float epsilon)
{
	return (compare(v0.x, v1.x, epsilon) && compare(v0.y, v1.y, epsilon) && compare(v0.z, v1.z, epsilon) && compare(v0.w, v1.w, epsilon));
}
/// <summary>Vector equal comparison.</summary>
UNIGINE_INLINE int operator==(const vec4 &v0, const vec4 &v1) { return compare(v0, v1); }
/// <summary>Vector not equal comparison.</summary>
UNIGINE_INLINE int operator!=(const vec4 &v0, const vec4 &v1) { return !compare(v0, v1); }

/// <summary>Vector less than comparison.</summary>
UNIGINE_INLINE int operator<(const vec4 &v0, const vec4 &v1) { return v0.x < v1.x && v0.y < v1.y && v0.z < v1.z && v0.w < v1.w; }
/// <summary>Vector greater than comparison.</summary>
UNIGINE_INLINE int operator>(const vec4 &v0, const vec4 &v1) { return v0.x > v1.x && v0.y > v1.y && v0.z > v1.z && v0.w > v1.w; }

/// <summary>Vector less than or equal comparison.</summary>
UNIGINE_INLINE int operator<=(const vec4 &v0, const vec4 &v1) { return v0.x <= v1.x && v0.y <= v1.y && v0.z <= v1.z && v0.w <= v1.w; }
/// <summary>Vector greater than or equal comparison.</summary>
UNIGINE_INLINE int operator>=(const vec4 &v0, const vec4 &v1) { return v0.x >= v1.x && v0.y >= v1.y && v0.z >= v1.z && v0.w >= v1.w; }

/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &mul(vec4 &ret, const vec4 &v0, float v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_mul_ps(v0.vec, _mm_set_ps1(v1));
	#else
		ret.x = v0.x * v1;
		ret.y = v0.y * v1;
		ret.z = v0.z * v1;
		ret.w = v0.w * v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &mul(vec4 &ret, const vec4 &v0, const vec4 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_mul_ps(v0.vec, v1.vec);
	#else
		ret.x = v0.x * v1.x;
		ret.y = v0.y * v1.y;
		ret.z = v0.z * v1.z;
		ret.w = v0.w * v1.w;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value.</summary>
UNIGINE_INLINE vec4 mul(const vec4 &v0, float v1)
{
	vec4 ret;
	return mul(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise multiplication of two vectors.</summary>
UNIGINE_INLINE vec4 mul(const vec4 &v0, const vec4 &v1)
{
	vec4 ret;
	return mul(ret, v0, v1);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec4 operator*(const vec4 &v0, float v1) { return mul(v0, v1); }
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec4 operator*(const vec4 &v0, const vec4 &v1) { return mul(v0, v1); }

/// <summary>Returns the result of a component-wise division of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &div(vec4 &ret, const vec4 &v0, float v1) { return mul(ret, v0, rcp(v1)); }
/// <summary>Returns the result of a component-wise division of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &div(vec4 &ret, const vec4 &v0, const vec4 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_div_ps(v0.vec, v1.vec);
	#else
		ret.x = v0.x / v1.x;
		ret.y = v0.y / v1.y;
		ret.z = v0.z / v1.z;
		ret.w = v0.w / v1.w;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise division of a vector by a scalar value.</summary>
UNIGINE_INLINE vec4 div(const vec4 &v0, float v1)
{
	vec4 ret;
	return div(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise division of two vectors.</summary>
UNIGINE_INLINE vec4 div(const vec4 &v0, const vec4 &v1)
{
	vec4 ret;
	return div(ret, v0, v1);
}
/// <summary>Division operator.</summary>
UNIGINE_INLINE vec4 operator/(const vec4 &v0, float v1) { return div(v0, v1); }
/// <summary>Division operator.</summary>
UNIGINE_INLINE vec4 operator/(const vec4 &v0, const vec4 &v1) { return div(v0, v1); }

/// <summary>Returns the result of a component-wise addition of a vector with a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &add(vec4 &ret, const vec4 &v0, float v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(v0.vec, _mm_set_ps1(v1));
	#else
		ret.x = v0.x + v1;
		ret.y = v0.y + v1;
		ret.z = v0.z + v1;
		ret.w = v0.w + v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise addition of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &add(vec4 &ret, const vec4 &v0, const vec4 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(v0.vec, v1.vec);
	#else
		ret.x = v0.x + v1.x;
		ret.y = v0.y + v1.y;
		ret.z = v0.z + v1.z;
		ret.w = v0.w + v1.w;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise addition of a vector with a scalar value.</summary>
UNIGINE_INLINE vec4 add(const vec4 &v0, float v1)
{
	vec4 ret;
	return add(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise addition of two vectors.</summary>
UNIGINE_INLINE vec4 add(const vec4 &v0, const vec4 &v1)
{
	vec4 ret;
	return add(ret, v0, v1);
}
/// <summary>Addition operator.</summary>
UNIGINE_INLINE vec4 operator+(const vec4 &v0, float v1) { return add(v0, v1); }
/// <summary>Addition operator.</summary>
UNIGINE_INLINE vec4 operator+(const vec4 &v0, const vec4 &v1) { return add(v0, v1); }

/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &sub(vec4 &ret, const vec4 &v0, float v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_sub_ps(v0.vec, _mm_set_ps1(v1));
	#else
		ret.x = v0.x - v1;
		ret.y = v0.y - v1;
		ret.z = v0.z - v1;
		ret.w = v0.w - v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1) by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &sub(vec4 &ret, const vec4 &v0, const vec4 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_sub_ps(v0.vec, v1.vec);
	#else
		ret.x = v0.x - v1.x;
		ret.y = v0.y - v1.y;
		ret.z = v0.z - v1.z;
		ret.w = v0.w - v1.w;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector.</summary>
UNIGINE_INLINE vec4 sub(const vec4 &v0, float v1)
{
	vec4 ret;
	return sub(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1).</summary>
UNIGINE_INLINE vec4 sub(const vec4 &v0, const vec4 &v1)
{
	vec4 ret;
	return sub(ret, v0, v1);
}
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE vec4 operator-(const vec4 &v0, float v1) { return sub(v0, v1); }
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE vec4 operator-(const vec4 &v0, const vec4 &v1) { return sub(v0, v1); }

/// <summary>Returns the result of multiplication of each component of the first vector by the float value and addition of the corresponding component of the second vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE vec4 &mad(vec4 &ret, const vec4 &v0, float v1, const vec4 &v2)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(_mm_mul_ps(v0.vec, _mm_set_ps1(v1)), v2.vec);
	#else
		ret.x = v0.x * v1 + v2.x;
		ret.y = v0.y * v1 + v2.y;
		ret.z = v0.z * v1 + v2.z;
		ret.w = v0.w * v1 + v2.w;
	#endif
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE vec4 &mad(vec4 &ret, const vec4 &v0, const vec4 &v1, const vec4 &v2)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(_mm_mul_ps(v0.vec, v1.vec), v2.vec);
	#else
		ret.x = v0.x * v1.x + v2.x;
		ret.y = v0.y * v1.y + v2.y;
		ret.z = v0.z * v1.z + v2.z;
		ret.w = v0.w * v1.w + v2.w;
	#endif
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the float value and addition of the corresponding component of the second vector (a * b + c).</summary>
UNIGINE_INLINE vec4 mad(const vec4 &v0, float v1, const vec4 &v2)
{
	vec4 ret;
	return mad(ret, v0, v1, v2);
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c).</summary>
UNIGINE_INLINE vec4 mad(const vec4 &v0, const vec4 &v1, const vec4 &v2)
{
	vec4 ret;
	return mad(ret, v0, v1, v2);
}

/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE float dot(const vec3 &v0, const vec4 &v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v1.w;
}
/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE float dot(const vec4 &v0, const vec3 &v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w;
}
/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE float dot(const vec4 &v0, const vec4 &v1)
{
	#ifdef USE_SSE
		float ret;
		_mm_store_ss(&ret, _mm_dp_ps(v0.vec, v1.vec, 0xff));
		return ret;
	#else
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
	#endif
}

/// <summary>Dot product only of three components of vectors. W component of four-component vector is ignored.</summary>
UNIGINE_INLINE float dot3(const vec3 &v0, const vec4 &v1) { return dot(v0, v1.xyz); }
/// <summary>Dot product only of three components of vectors. W component of four-component vector is ignored.</summary>
UNIGINE_INLINE float dot3(const vec4 &v0, const vec3 &v1) { return dot(v0.xyz, v1); }
/// <summary>Dot product only of three components of vectors. W components of four-component vectors are ignored.</summary>
UNIGINE_INLINE float dot3(const vec4 &v0, const vec4 &v1) { return dot(v0.xyz, v1.xyz); }

/// <summary>Compares the arguments component-wise and returns the minimum value for each component by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &min(vec4 &ret, const vec4 &v0, const vec4 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_min_ps(v0.vec, v1.vec);
	#else
		ret.x = min(v0.x, v1.x);
		ret.y = min(v0.y, v1.y);
		ret.z = min(v0.z, v1.z);
		ret.w = min(v0.w, v1.w);
	#endif
	return ret;
}
/// <summary>Compares each vector component with the float value and returns the minimum value for each component by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &min(vec4 &ret, const vec4 &v0, float v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_min_ps(v0.vec, _mm_set_ps1(v1));
	#else
		ret.x = min(v0.x, v1);
		ret.y = min(v0.y, v1);
		ret.z = min(v0.z, v1);
		ret.w = min(v0.w, v1);
	#endif
	return ret;
}
/// <summary>Compares the arguments component-wise and returns the minimum value for each component.</summary>
UNIGINE_INLINE vec4 min(const vec4 &v0, const vec4 &v1)
{
	vec4 ret;
	return min(ret, v0, v1);
}
/// <summary>Compares each vector component with the float value and returns the minimum value for each component.</summary>
UNIGINE_INLINE vec4 min(const vec4 &v0, float v1)
{
	vec4 ret;
	return min(ret, v0, v1);
}

/// <summary>Compares the arguments component-wise and returns the maximum value for each component by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &max(vec4 &ret, const vec4 &v0, const vec4 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_max_ps(v0.vec, v1.vec);
	#else
		ret.x = max(v0.x, v1.x);
		ret.y = max(v0.y, v1.y);
		ret.z = max(v0.z, v1.z);
		ret.w = max(v0.w, v1.w);
	#endif
	return ret;
}
/// <summary>Compares each vector component with the float value and returns the maximum value for each component by saving it in the ret argument.</summary>
UNIGINE_INLINE vec4 &max(vec4 &ret, const vec4 &v0, float v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_max_ps(v0.vec, _mm_set_ps1(v1));
	#else
		ret.x = max(v0.x, v1);
		ret.y = max(v0.y, v1);
		ret.z = max(v0.z, v1);
		ret.w = max(v0.w, v1);
	#endif
	return ret;
}
/// <summary>Compares the arguments component-wise and returns the maximum value for each component.</summary>
UNIGINE_INLINE vec4 max(const vec4 &v0, const vec4 &v1)
{
	vec4 ret;
	return max(ret, v0, v1);
}
/// <summary>Compares each vector component with the float value and returns the maximum value for each component.</summary>
UNIGINE_INLINE vec4 max(const vec4 &v0, float v1)
{
	vec4 ret;
	return max(ret, v0, v1);
}

/// <summary>Clamps the value (v) within the minimum (v0) and maximum (v1) limits and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec4 &clamp(vec4 &ret, const vec4 &v, const vec4 &v0, const vec4 &v1)
{
	#ifdef USE_SSE
		ret.vec = _mm_min_ps(_mm_max_ps(v.vec, v0.vec), v1.vec);
	#else
		ret.x = clamp(v.x, v0.x, v1.x);
		ret.y = clamp(v.y, v0.y, v1.y);
		ret.z = clamp(v.z, v0.z, v1.z);
		ret.w = clamp(v.w, v0.w, v1.w);
	#endif
	return ret;
}
/// <summary>Clamps the value (v) within the minimum (v0) and maximum (v1) limits and returns the result.</summary>
UNIGINE_INLINE vec4 clamp(const vec4 &v, const vec4 &v0, const vec4 &v1)
{
	vec4 ret;
	return clamp(ret, v, v0, v1);
}

/// <summary>Clamps the vector component values within the range [0.0, 1.0] and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec4 &saturate(vec4 &ret, const vec4 &v)
{
	#ifdef USE_SSE
		ret.vec = _mm_min_ps(_mm_max_ps(v.vec, vec4_zero.vec), vec4_one.vec);
	#else
		ret.x = saturate(v.x);
		ret.y = saturate(v.y);
		ret.z = saturate(v.z);
		ret.w = saturate(v.w);
	#endif
	return ret;
}
/// <summary>Clamps the vector component values within the range [0.0, 1.0] and returns the result.</summary>
UNIGINE_INLINE vec4 saturate(const vec4 &v)
{
	vec4 ret;
	return saturate(ret, v);
}

/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec4 &lerp(vec4 &ret, const vec4 &v0, const vec4 &v1, float k)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(v0.vec, _mm_mul_ps(_mm_sub_ps(v1.vec, v0.vec), _mm_set1_ps(k)));
	#else
		ret.x = lerp(v0.x, v1.x, k);
		ret.y = lerp(v0.y, v1.y, k);
		ret.z = lerp(v0.z, v1.z, k);
		ret.w = lerp(v0.w, v1.w, k);
	#endif
	return ret;
}
/// <summary>Returns the vector component values interpolated according to the formula v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE vec4 lerp(const vec4 &v0, const vec4 &v1, float k)
{
	vec4 ret;
	return lerp(ret, v0, v1, k);
}

/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE vec4 &lerp(vec4 &ret, const vec4 &v0, const vec4 &v1, const vec4 &k)
{
	#ifdef USE_SSE
		ret.vec = _mm_add_ps(v0.vec, _mm_mul_ps(_mm_sub_ps(v1.vec, v0.vec), k.vec));
	#else
		ret.x = lerp(v0.x, v1.x, k);
		ret.y = lerp(v0.y, v1.y, k);
		ret.z = lerp(v0.z, v1.z, k);
		ret.w = lerp(v0.w, v1.w, k);
	#endif
	return ret;
}
/// <summary>Returns the vector component values interpolated according to the formula v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE vec4 lerp(const vec4 &v0, const vec4 &v1, const vec4 &k)
{
	vec4 ret;
	return lerp(ret, v0, v1, k);
}

/// <summary>Performs linear interpolation between three vectors.</summary>
UNIGINE_INLINE vec4 &lerp3(vec4 &ret, const vec4 &v0, const vec4 &v1, const vec4 &v2, float k)
{
	if (k < 0.5f)
		lerp(ret, v0, v1, k * 2.0f);
	else
		lerp(ret, v1, v2, k * 2.0f - 1.0f);
	return ret;
}
/// <summary>Performs linear interpolation between three vectors.</summary>
UNIGINE_INLINE vec4 lerp3(const vec4 &v0, const vec4 &v1, const vec4 &v2, float k)
{
	vec4 ret;
	return lerp3(ret, v0, v1, v2, k);
}

/// <summary>Returns the cross product of two vectors.</summary>
UNIGINE_INLINE vec4 &cross(vec4 &ret, const vec3 &v0, const vec3 &v1)
{
	ret.x = v0.y * v1.z - v0.z * v1.y;
	ret.y = v0.z * v1.x - v0.x * v1.z;
	ret.z = v0.x * v1.y - v0.y * v1.x;
	return ret;
}
/// <summary>Returns the cross product of three components of vectors. The W component of four-component vectors is ignored.</summary>
UNIGINE_INLINE vec3 &cross3(vec3 &ret, const vec4 &v0, const vec4 &v1)
{
	ret.x = v0.y * v1.z - v0.z * v1.y;
	ret.y = v0.z * v1.x - v0.x * v1.z;
	ret.z = v0.x * v1.y - v0.y * v1.x;
	return ret;
}
/// <summary>Returns the cross product of three components of vectors. The W component of four-component vectors is ignored.</summary>
UNIGINE_INLINE vec3 &cross3(vec3 &ret, const vec4 &v0, const vec3 &v1)
{
	ret.x = v0.y * v1.z - v0.z * v1.y;
	ret.y = v0.z * v1.x - v0.x * v1.z;
	ret.z = v0.x * v1.y - v0.y * v1.x;
	return ret;
}
/// <summary>Returns the cross product of three components of vectors. The W component of four-component vectors is ignored.</summary>
UNIGINE_INLINE vec3 &cross3(vec3 &ret, const vec3 &v0, const vec4 &v1)
{
	ret.x = v0.y * v1.z - v0.z * v1.y;
	ret.y = v0.z * v1.x - v0.x * v1.z;
	ret.z = v0.x * v1.y - v0.y * v1.x;
	return ret;
}

/// <summary>Returns the cross product of three components of vectors. The W component of four-component vectors is ignored.</summary>
UNIGINE_INLINE vec3 cross3(const vec4 &v0, const vec4 &v1)
{
	vec3 ret;
	return cross3(ret, v0, v1);
}
/// <summary>Returns the cross product of three components of vectors. The W component of four-component vectors is ignored.</summary>
UNIGINE_INLINE vec3 cross3(const vec4 &v0, const vec3 &v1)
{
	vec3 ret;
	return cross3(ret, v0, v1);
}
/// <summary>Returns the cross product of three components of vectors. The W component of four-component vectors is ignored.</summary>
UNIGINE_INLINE vec3 cross3(const vec3 &v0, const vec4 &v1)
{
	vec3 ret;
	return cross3(ret, v0, v1);
}

/// <summary>Returns an argument rounded to the nearest integral value.</summary>
UNIGINE_INLINE vec4 round(const vec4 &v) { return {round(v.x), round(v.y), round(v.z), round(v.w)}; }
/// <summary>Returns the largest integral value that's less than or equal to the argument.</summary>
UNIGINE_INLINE vec4 floor(const vec4 &v)
{
	#ifdef USE_SSE
		return _mm_floor_ps(v.vec);
	#else
		return {floor(v.x), floor(v.y), floor(v.z), floor(v.w)};
	#endif
}
/// <summary>Returns the smallest integral value that's greater than or equal to the argument.</summary>
UNIGINE_INLINE vec4 ceil(const vec4 &v)
{
	#ifdef USE_SSE
		return _mm_ceil_ps(v.vec);
	#else
		return {ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w)};
	#endif
}

/// <summary>Returns the absolute value of the specified argument.</summary>
UNIGINE_INLINE vec4 abs(const vec4 &v)
{
	return {abs(v.x), abs(v.y), abs(v.z), abs(v.w)};
}
/// <summary>Returns the fractional part of the argument.</summary>
UNIGINE_INLINE vec4 frac(const vec4 &v)
{
	return {frac(v.x), frac(v.y), frac(v.z), frac(v.w)};
}

/// <summary>Performs a component-wise comparison between two arguments, and returns a new vector with a component set to 1.0 if the corresponding component in a is greater than in b, and 0.0 otherwise.</summary>
UNIGINE_INLINE vec4 step(const vec4 &a, const vec4 &b)
{
	return {toFloat(a.x > b.x), toFloat(a.y > b.y), toFloat(a.z > b.z), toFloat(a.w > b.w)};
}
/// <summary>Performs a component-wise comparison between two arguments, and returns a new vector with a component set to 1.0 if the corresponding component in a is greater than in b, and 0.0 otherwise.</summary>
UNIGINE_INLINE vec4 step(const vec4 &a, float b)
{
	return {toFloat(a.x > b), toFloat(a.y > b), toFloat(a.z > b), toFloat(a.w > b)};
}

/// <summary>Returns the value calculated according to the formula: (v - v0) / (v1 - v0) clamped within 0.0f and 1.0f.</summary>
UNIGINE_INLINE vec4 inverseLerp(const vec4 &v0, const vec4 &v1, const vec4 &v)
{
	return saturate((v - v0) / (v1 - v0));
}

/// <summary>Performs a smooth interpolation between two vectors (point_a and point_b) using a specified coefficient range to create a smooth transition effect.</summary>
UNIGINE_INLINE vec4 contrastLerp(const vec4 &point_a, const vec4 &point_b, float coef_min_bound, float coef_max_bound, float coef)
{
	return lerp(point_a, point_b, smoothstep(coef_min_bound, coef_max_bound, coef));
}

/// <summary>Combines two vectors using an overlay blending effect, using the additional x value that determines the interpolation level between the vectors.</summary>
UNIGINE_INLINE vec4 overlay(const vec4 &a, const vec4 &b, float x)
{
	return max(lerp(a, lerp(vec4_one - (vec4_one - a) * (vec4_one - b) * 2.0f, a * b * 2.0f, step(a, vec4_half)), x), vec4_zero);
}
/// <summary>Combines two vectors using an overlay blending effect, using the additional x value that determines the interpolation level between the vectors.</summary>
UNIGINE_INLINE vec4 overlay(const vec4 &a, const vec4 &b, const vec4 &x)
{
	return max(lerp(a, lerp(vec4_one - (vec4_one - a) * (vec4_one - b) * 2.0f, a * b * 2.0f, step(a, vec4_half)), x), vec4_zero);
}

/// <summary>Returns a gradient value for the specified argument using four key components.</summary>
UNIGINE_INLINE float gradient4(float x, const vec4 &keys)
{
	return smoothstep(keys.x, keys.y, x) - smoothstep(keys.z, keys.w, x);
}

/// <summary>Converts RGB color value to sRGB format.</summary>
UNIGINE_INLINE vec4 srgb(const vec4 &color) { return vec4(srgb(color.x), srgb(color.y), srgb(color.z), srgb(color.w)); }
/// <summary>Converts sRGB color value to RGB format.</summary>
UNIGINE_INLINE vec4 isrgb(const vec4 &color) { return vec4(isrgb(color.x), isrgb(color.y), isrgb(color.z), isrgb(color.w)); }

/// <summary>Converts RGB color value to sRGB format without converting alpha.</summary>
UNIGINE_INLINE vec4 srgbColor(const vec4 &color) { return vec4(srgb(color.x), srgb(color.y), srgb(color.z), color.w); }
/// <summary>Converts sRGB color value to RGB format without converting alpha.</summary>
UNIGINE_INLINE vec4 isrgbColor(const vec4 &color) { return vec4(isrgb(color.x), isrgb(color.y), isrgb(color.z), color.w); }

/// <summary>Returns the perceived brightness of the color.</summary>
UNIGINE_INLINE float rgbToLuma(const vec4 &color)
{
	return rgbToLuma(color.xyz);
}

}
}