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
#include "UnigineMathLibDVec2.h"
#include "UnigineMathLibDVec3.h"

namespace Unigine
{
namespace Math
{

struct alignas(16) dvec4
{
	/// <summary>Constructor. Initializes the vector using the given values.</summary>
	UNIGINE_INLINE constexpr dvec4(double v, ConstexprTag): x(v), y(v), z(v), w(v) {}
	/// <summary>Constructor. Initializes the vector using the given values.</summary>
	UNIGINE_INLINE constexpr dvec4(double x, double y, double z, double w, ConstexprTag) : x(x), y(y), z(z), w(w) {}

	/// <summary>Default constructor. Produces a zero vector.</summary>
	UNIGINE_INLINE dvec4()
		: x(0.0)
		, y(0.0)
		, z(0.0)
		, w(0.0)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using a given value: x=v, y=v, z=v, w=v.</summary>
	UNIGINE_INLINE explicit dvec4(double v)
		: x(v)
		, y(v)
		, z(v)
		, w(v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using the given values.</summary>
	UNIGINE_INLINE dvec4(double x, double y, double z = 0.0, double w = 0.0)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using a given pointer to the array of elements: x=v[0], y=v[1], z=v[2], w=v[3].</summary>
	UNIGINE_INLINE explicit dvec4(const double *v)
		: x(v[0])
		, y(v[1])
		, z(v[2])
		, w(v[3])
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector by copying a given source vector.</summary>
	UNIGINE_INLINE dvec4(const dvec4 &v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(v);
	}

	/// <summary>Constructor. Initializes the vector using a given two-component vec2 source vector: x=v.x, y=v.y, z=0.0f, w=1.0f.</summary>
	UNIGINE_INLINE explicit dvec4(const dvec2 &v)
		: x(v.x)
		, y(v.y)
		, z(0.0)
		, w(1.0)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Sets the vector using a two-component vec2 source vector and two scalars.</summary>
	UNIGINE_INLINE dvec4(const dvec2 &v, double z, double w)
		: x(v.x)
		, y(v.y)
		, z(z)
		, w(w)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using the values of two vec2 source vectors.</summary>
	UNIGINE_INLINE dvec4(const dvec2 &v0, const dvec2 &v1)
		: x(v0.x)
		, y(v0.y)
		, z(v1.x)
		, w(v1.y)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}

	/// <summary>Constructor. Initializes the vector using a given three-component vec3 source vector: x=v.x, y=v.y, z=v.z, w=1.0.</summary>
	UNIGINE_INLINE explicit dvec4(const dvec3 &v)
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(1.0)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the vector using a given three-component source vector and a scalar.</summary>
	UNIGINE_INLINE dvec4(const dvec3 &v, double w)
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(w)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}

	/// <summary>Constructor. Initializes the vector using a given source vector.</summary>
	UNIGINE_INLINE explicit dvec4(const vec4 &v)
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(v.w)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	
	#ifdef USE_SSE
		UNIGINE_INLINE dvec4(const __m128d &v0, const __m128d &v1)
		{
			UNIGINE_ASSERT_ALIGNED16(this);
			sse.v0 = v0;
			sse.v1 = v1;
		}
	#endif

	/// <summary>Constructor. Initializes the vector using a given source vector.</summary>
	UNIGINE_INLINE explicit dvec4(const hvec4 &v);
	/// <summary>Constructor. Initializes the vector using a given source vector.</summary>
	UNIGINE_INLINE explicit dvec4(const ivec4 &v);
	/// <summary>Constructor. Initializes the vector using a given source vector.</summary>
	UNIGINE_INLINE explicit dvec4(const bvec4 &v);
	/// <summary>Constructor. Initializes the vector using a given source vector.</summary>
	UNIGINE_INLINE explicit dvec4(const svec4 &v);


	/// <summary>Sets the vector using a given scalar value: x=v, y=v, z=v, w=v.</summary>
	UNIGINE_INLINE void set(double v) { x = v; y = v; z = v; w = v; }
	/// <summary>Sets the vector by components.</summary>
	UNIGINE_INLINE void set(double x_, double y_, double z_, double w_) { x = x_; y = y_; z = z_; w = w_; }
	/// <summary>Sets the vector using a two-component source vector and two scalars.</summary>
	UNIGINE_INLINE void set(const dvec2 &v, double z_ = 0.0, double w_ = 1.0)
	{
		x = v.x;
		y = v.y;
		z = z_;
		w = w_;
	}
	/// <summary>Sets the vector using a three-component source vector and a scalar.</summary>
	UNIGINE_INLINE void set(const dvec3 &v, double w_ = 1.0)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = w_;
	}
	/// <summary>Sets the vector equal to the specified source vector.</summary>
	UNIGINE_INLINE void set(const dvec4 &v)
	{
		sse.v0 = v.sse.v0;
		sse.v1 = v.sse.v1;
	}
	/// <summary>Sets the vector using the array of elements: x=val[0], y=val[1], z=val[2], w=val[3].</summary>
	UNIGINE_INLINE void set(const double *v)
	{
		x = v[0];
		y = v[1];
		z = v[2];
		w = v[3];
	}

	/// <summary>Returns the pointer to the array of elements: v[0]=x, v[1]=y, v[2]=z, v[3]=w.</summary>
	UNIGINE_INLINE void get(double *v) const
	{
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;
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
		assert((unsigned int)i < 4 && "dvec4::operator[](): bad index");
		return v[i];
	}
	/// <summary>Performs array access to the vector item by using given item index.</summary>
	UNIGINE_INLINE double operator[](int i) const
	{
		assert((unsigned int)i < 4 && "dvec4::operator[](): bad index");
		return v[i];
	}

	
	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(double v)
	{
		#ifdef USE_SSE
			__m128d temp = _mm_set1_pd(v);
			sse.v0 = _mm_mul_pd(sse.v0, temp);
			sse.v1 = _mm_mul_pd(sse.v1, temp);
		#else
			x *= v;
			y *= v;
			z *= v;
			w *= v;
		#endif
	}
	/// <summary>Multiplies the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul(const dvec4 &v)
	{
		#ifdef USE_SSE
			sse.v0 = _mm_mul_pd(sse.v0, v.sse.v0);
			sse.v1 = _mm_mul_pd(sse.v1, v.sse.v1);
		#else
			x *= v.x;
			y *= v.y;
			z *= v.z;
			w *= v.w;
		#endif
	}
	/// <summary>Multiplies the X, Y, and Z components of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void mul3(double v)
	{
		x *= v;
		y *= v;
		z *= v;
	}
	/// <summary>Performs scalar multiplication.</summary>
	UNIGINE_INLINE dvec4 &operator*=(double v) { mul(v); return *this; }
	/// <summary>Performs vector multiplication.</summary>
	UNIGINE_INLINE dvec4 &operator*=(const dvec4 &v) { mul(v); return *this; }

	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(double v) { mul(rcp(v)); }
	/// <summary>Returns the result of division of the vector by the value of the specified argument.</summary>
	UNIGINE_INLINE void div(const dvec4 &v)
	{
		#ifdef USE_SSE
			sse.v0 = _mm_div_pd(sse.v0, v.sse.v0);
			sse.v1 = _mm_div_pd(sse.v1, v.sse.v1);
		#else
			x /= v.x;
			y /= v.y;
			z /= v.z;
			w /= v.w;
		#endif
	}
	/// <summary>Performs component-wise division of the vector by the scalar. Implemented using the calculation of inverse scalar value with subsequent component-wise multiplication.</summary>
	UNIGINE_INLINE dvec4 &operator/=(double v) { div(v); return *this; }
	/// <summary>Performs component-wise division of vectors.</summary>
	UNIGINE_INLINE dvec4 &operator/=(const dvec4 &v) { div(v); return *this; }

	/// <summary>Returns the sum of vector components.</summary>
	UNIGINE_INLINE double sum() const { return x + y + z + w; }
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE void add(double v)
	{
		#ifdef USE_SSE
			__m128d temp = _mm_set1_pd(v);
			sse.v0 = _mm_add_pd(sse.v0, temp);
			sse.v1 = _mm_add_pd(sse.v1, temp);
		#else
			x += v;
			y += v;
			z += v;
			w += v;
		#endif
	}
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE void add(const dvec4 &v)
	{
		#ifdef USE_SSE
			sse.v0 = _mm_add_pd(sse.v0, v.sse.v0);
			sse.v1 = _mm_add_pd(sse.v1, v.sse.v1);
		#else
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		#endif
	}
	/// <summary>Performs addition of the specified argument to each component of the vector.</summary>
	UNIGINE_INLINE dvec4 &operator+=(double v) { add(v); return *this; }
	/// <summary>Performs component-wise addition of vector values.</summary>
	UNIGINE_INLINE dvec4 &operator+=(const dvec4 &v) { add(v); return *this; }

	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE void sub(double v)
	{
		#ifdef USE_SSE
			__m128d temp = _mm_set1_pd(v);
			sse.v0 = _mm_sub_pd(sse.v0, temp);
			sse.v1 = _mm_sub_pd(sse.v1, temp);
		#else
			x += v;
			y += v;
			z += v;
			w += v;
		#endif
	}
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE void sub(const dvec4 &v)
	{
		#ifdef USE_SSE
			sse.v0 = _mm_sub_pd(sse.v0, v.sse.v0);
			sse.v1 = _mm_sub_pd(sse.v1, v.sse.v1);
		#else
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
		#endif
	}
	/// <summary>Subtracts the argument from each element of the vector.</summary>
	UNIGINE_INLINE dvec4 &operator-=(double v) { sub(v); return *this; }
	/// <summary>Performs component-wise subtraction of vector values.</summary>
	UNIGINE_INLINE dvec4 &operator-=(const dvec4 &v) { sub(v); return *this; }
	
	/// <summary>Performs vector assignment. Destination vector = Source vector.</summary>
	UNIGINE_INLINE dvec4 &operator=(const dvec4 &v) { set(v); return *this; }
	/// <summary>Performs vector negation.</summary>
	UNIGINE_INLINE dvec4 operator-() const { return dvec4(-x, -y, -z, -w); }

	/// <summary>Returns the squared length of the vector.</summary>
	UNIGINE_INLINE double length2() const { return x * x + y * y + z * z + w * w; }
	/// <summary>Returns the length of the vector.</summary>
	UNIGINE_INLINE double length() const { return sqrt(length2()); }
	/// <summary>Returns the inverted length of the vector.</summary>
	UNIGINE_INLINE double iLength() const { return rsqrt(length2()); }

	/// <summary>Returns a normalized vector.</summary>
	UNIGINE_INLINE dvec4 &normalize() { mul(iLength()); return *this; }
	/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
	UNIGINE_INLINE dvec4 &normalizeValid()
	{
		double length = length2();
		if (length != 0.0f)
			mul(rsqrt(length));
		return *this;
	}

	/// <summary>Returns the vector with normalized XYZ components.</summary>
	UNIGINE_INLINE dvec4 &normalize3()
	{
		mul3(xyz.iLength());
		return *this;
	}

	/// <summary>Returns the vector with normalized XYZ components. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
	UNIGINE_INLINE dvec4 &normalizeValid3()
	{
		double length = xyz.length2();
		if (length != 0.0f)
			mul3(rsqrt(length));
		return *this;
	}

	/// <summary>Returns the absolute values of the vector components.</summary>
	UNIGINE_INLINE dvec4 &abs()
	{
		x = Math::abs(x);
		y = Math::abs(y);
		z = Math::abs(z);
		w = Math::abs(w);
		return *this;
	}

	/// <summary>Compares the X and Y components of the vector and returns the greater one.</summary>
	UNIGINE_INLINE double maxXY() const { return Math::max(x, y); }
	/// <summary>Compares the X, Y, and Z components of the vector and returns the greatest one.</summary>
	UNIGINE_INLINE double maxXYZ() const { return Math::max(maxXY(), z); }
	/// <summary>Compares all components of the vector and returns the greatest value.</summary>
	UNIGINE_INLINE double max() const { return Math::max(maxXYZ(), w); }

	/// <summary>Returns a 64-bit hash generated for the vector.</summary>
	UNIGINE_INLINE unsigned long long hash64() const { return hashMixer(hashMixer(hashMixer(_hash.x, _hash.y), _hash.z), _hash.w); }
	/// <summary>Returns a hash obtained by mixing the hash values of vector components.</summary>
	UNIGINE_INLINE unsigned int hash() const { return hashCast64To32(hashCombine(hashCombine(hashCombine(hashInteger(x), y), z), w)); }

	#ifdef USE_SSE
		struct sse_data
		{
			__m128d v0;
			__m128d v1;
		}; 
	#endif

	union
	{
		struct
		{
			double x, y, z, w;
		};
		double v[4];

		const dvec3 xyz;
		dvec2 xy;

		struct
		{
			dvec2 xy;
			dvec2 zw;
		} swizzle;

		struct
		{
			unsigned long long x;
			unsigned long long y;
			unsigned long long z;
			unsigned long long w;
		} _hash;

		#ifdef USE_SSE
			sse_data sse; // DO NOT TOUCH UNLESS ABSOLUTELY SURE
		#endif
	};
};

constexpr dvec4 dvec4_zero(0.0, ConstexprTag{});
constexpr dvec4 dvec4_one(1.0, ConstexprTag{});
constexpr dvec4 dvec4_eps(Consts::EPS, ConstexprTag{});
constexpr dvec4 dvec4_inf(Consts::INF, ConstexprTag{});

/// <summary>Calculates the length of a given vector.</summary>
UNIGINE_INLINE double length(const dvec4 &v) { return v.length(); }
/// <summary>Calculates the squared length of a given vector. This method is much faster than length() - the calculation is basically the same only without the slow Sqrt call. If you are using lengths simply to compare distances, then it is faster to compare squared lengths against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE double length2(const dvec4 &v) { return v.length2(); }

/// <summary>Calculates the squared distance between the two given vectors. The squared distance is calculated as: length2(v0 - v1). This method is much faster than distance() - the calculation is basically the same only without the slow Sqrt call. If you simply want to compare distances, then it is faster to compare squared distances against the squares of distances as the comparison gives the same result.</summary>
UNIGINE_INLINE double distance2(const dvec4 &v0, const dvec4 &v1)
{
	#ifdef USE_SSE
		double ret;
		__m128d temp_v0 = _mm_sub_pd(v0.sse.v0, v1.sse.v0);
		__m128d temp_v1 = _mm_sub_pd(v0.sse.v1, v1.sse.v1);
		temp_v0 = _mm_dp_pd(temp_v0, temp_v0, 0x7f);
		temp_v1 = _mm_dp_pd(temp_v1, temp_v1, 0x7f);

		_mm_store_sd(&ret, _mm_add_pd(temp_v0, temp_v1));
		return ret;
	#else
		return length2(v0 - v1);
	#endif
}
/// <summary>Calculates the distance between the two given vectors. The distance is calculated as: length(v0 - v1).</summary>
UNIGINE_INLINE double distance(const dvec4 &v0, const dvec4 &v1)
{
	#ifdef USE_SSE
		double ret;
		__m128d temp_v0 = _mm_sub_pd(v0.sse.v0, v1.sse.v0);
		__m128d temp_v1 = _mm_sub_pd(v0.sse.v1, v1.sse.v1);
		temp_v0 = _mm_dp_pd(temp_v0, temp_v0, 0x7f);
		temp_v1 = _mm_dp_pd(temp_v1, temp_v1, 0x7f);

		_mm_store_sd(&ret, _mm_add_pd(temp_v0, temp_v1));
		return sqrt(ret);
	#else
		return length(v0 - v1);
	#endif
}

/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1.</summary>
UNIGINE_INLINE dvec4 normalize(const dvec4 &v)
{
	dvec4 ret = v;
	return ret.normalize();
}
/// <summary>Normalizes a vector, makes its magnitude equal to 1. When normalized, a vector keeps the same direction but its length is equal to 1. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
UNIGINE_INLINE dvec4 normalizeValid(const dvec4 &v)
{
	dvec4 ret = v;
	return ret.normalizeValid();
}

/// <summary>Normalizes a vector making its magnitude equal to 1. The vector is normalized as if it has only the first three components (the fourth one is ignored).</summary>
UNIGINE_INLINE dvec4 normalize3(const dvec4 &v)
{
	dvec4 ret = v;
	return ret.normalize3();
}
/// <summary>Normalizes a vector making its magnitude equal to 1. The vector is normalized as if it has only the first three components (the fourth one is ignored). Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
UNIGINE_INLINE dvec4 normalizeValid3(const dvec4 &v)
{
	dvec4 ret = v;
	return ret.normalizeValid3();
}

/// <summary>Compares two vectors according to the degree of precision equal to 1.0e-6f.</summary>
UNIGINE_INLINE int compare(const dvec4 &v0, const dvec4 &v1)
{
	return (compare(v0.x, v1.x) && compare(v0.y, v1.y) && compare(v0.z, v1.z) && compare(v0.w, v1.w));
}
/// <summary>Compares two vectors according to the specified degree of precision (epsilon).</summary>
UNIGINE_INLINE int compare(const dvec4 &v0, const dvec4 &v1, double epsilon)
{
	return (compare(v0.x, v1.x, epsilon) && compare(v0.y, v1.y, epsilon) && compare(v0.z, v1.z, epsilon) && compare(v0.w, v1.w, epsilon));
}
/// <summary>Vector equal comparison.</summary>
UNIGINE_INLINE int operator==(const dvec4 &v0, const dvec4 &v1) { return compare(v0, v1); }
/// <summary>Vector not equal comparison.</summary>
UNIGINE_INLINE int operator!=(const dvec4 &v0, const dvec4 &v1) { return !compare(v0, v1); }

/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec4 &mul(dvec4 &ret, const dvec4 &v0, double v1)
{
	#ifdef USE_SSE
		__m128d temp = _mm_set1_pd(v1);
		ret.sse.v0 = _mm_mul_pd(v0.sse.v0, temp);
		ret.sse.v1 = _mm_mul_pd(v0.sse.v1, temp);
	#else
		ret.x = v0.x * v1;
		ret.y = v0.y * v1;
		ret.z = v0.z * v1;
		ret.w = v0.w * v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec4 &mul(dvec4 &ret, const dvec4 &v0, const dvec4 &v1)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_mul_pd(v0.sse.v0, v1.sse.v0);
		ret.sse.v1 = _mm_mul_pd(v0.sse.v1, v1.sse.v1);
	#else
		ret.x = v0.x * v1.x;
		ret.y = v0.y * v1.y;
		ret.z = v0.z * v1.z;
		ret.w = v0.z * v1.w;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise multiplication of a vector by a scalar value.</summary>
UNIGINE_INLINE dvec4 mul(const dvec4 &v0, double v1)
{
	dvec4 ret;
	return mul(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise multiplication of two vectors.</summary>
UNIGINE_INLINE dvec4 mul(const dvec4 &v0, const dvec4 &v1)
{
	dvec4 ret;
	return mul(ret, v0, v1);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dvec4 operator*(const dvec4 &v0, double v1) { return mul(v0, v1); }
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dvec4 operator*(const dvec4 &v0, const dvec4 &v1) { return mul(v0, v1); }

/// <summary>Returns the result of a component-wise division of a vector by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec4 &div(dvec4 &ret, const dvec4 &v0, double v1) { return mul(ret, v0, rcp(v1)); }
/// <summary>Returns the result of a component-wise division of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec4 &div(dvec4 &ret, const dvec4 &v0, const dvec4 &v1)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_div_pd(v0.sse.v0, v1.sse.v0);
		ret.sse.v1 = _mm_div_pd(v0.sse.v1, v1.sse.v1);
	#else
		ret.x = v0.x / v1.x;
		ret.y = v0.y / v1.y;
		ret.z = v0.z / v1.z;
		ret.w = v0.w / v1.w;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise division of a vector by a scalar value.</summary>
UNIGINE_INLINE dvec4 div(const dvec4 &v0, double v1)
{
	dvec4 ret;
	return div(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise division of two vectors.</summary>
UNIGINE_INLINE dvec4 div(const dvec4 &v0, const dvec4 &v1)
{
	dvec4 ret;
	return div(ret, v0, v1);
}
/// <summary>Division operator.</summary>
UNIGINE_INLINE dvec4 operator/(const dvec4 &v0, double v1) { return div(v0, v1); }
/// <summary>Division operator.</summary>
UNIGINE_INLINE dvec4 operator/(const dvec4 &v0, const dvec4 &v1) { return div(v0, v1); }

/// <summary>Returns the result of a component-wise addition of a vector with a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec4 &add(dvec4 &ret, const dvec4 &v0, double v1)
{
	#ifdef USE_SSE
		__m128d temp = _mm_set1_pd(v1);
		ret.sse.v0 = _mm_add_pd(v0.sse.v0, temp);
		ret.sse.v1 = _mm_add_pd(v0.sse.v1, temp);
	#else
		ret.x = v0.x + v1;
		ret.y = v0.y + v1;
		ret.z = v0.z + v1;
		ret.w = v0.w + v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise addition of two vectors by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec4 &add(dvec4 &ret, const dvec4 &v0, const dvec4 &v1)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_add_pd(v0.sse.v0, v1.sse.v0);
		ret.sse.v1 = _mm_add_pd(v0.sse.v1, v1.sse.v1);
	#else
		ret.x = v0.x + v1.x;
		ret.y = v0.y + v1.y;
		ret.z = v0.z + v1.z;
		ret.w = v0.w + v1.w;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise addition of a vector with a scalar value.</summary>
UNIGINE_INLINE dvec4 add(const dvec4 &v0, double v1)
{
	dvec4 ret;
	return add(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise addition of two vectors.</summary>
UNIGINE_INLINE dvec4 add(const dvec4 &v0, const dvec4 &v1)
{
	dvec4 ret;
	return add(ret, v0, v1);
}
/// <summary>Addition operator.</summary>
UNIGINE_INLINE dvec4 operator+(const dvec4 &v0, double v1) { return add(v0, v1); }
/// <summary>Addition operator.</summary>
UNIGINE_INLINE dvec4 operator+(const dvec4 &v0, const dvec4 &v1) { return add(v0, v1); }

/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec4 &sub(dvec4 &ret, const dvec4 &v0, double v1)
{
	#ifdef USE_SSE
		__m128d temp = _mm_set1_pd(v1);
		ret.sse.v0 = _mm_sub_pd(v0.sse.v0, temp);
		ret.sse.v1 = _mm_sub_pd(v0.sse.v1, temp);
	#else
		ret.x = v0.x - v1;
		ret.y = v0.y - v1;
		ret.z = v0.z - v1;
		ret.w = v0.w - v1;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1) by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec4 &sub(dvec4 &ret, const dvec4 &v0, const dvec4 &v1)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_sub_pd(v0.sse.v0, v1.sse.v0);
		ret.sse.v1 = _mm_sub_pd(v0.sse.v1, v1.sse.v1);
	#else
		ret.x = v0.x - v1.x;
		ret.y = v0.y - v1.y;
		ret.z = v0.z - v1.z;
		ret.w = v0.w - v1.w;
	#endif
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction of a scalar value from a vector.</summary>
UNIGINE_INLINE dvec4 sub(const dvec4 &v0, double v1)
{
	dvec4 ret;
	return sub(ret, v0, v1);
}
/// <summary>Returns the result of a component-wise subtraction (v0 - v1).</summary>
UNIGINE_INLINE dvec4 sub(const dvec4 &v0, const dvec4 &v1)
{
	dvec4 ret;
	return sub(ret, v0, v1);
}
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE dvec4 operator-(const dvec4 &v0, double v1) { return sub(v0, v1); }
/// <summary>Subtraction operator.</summary>
UNIGINE_INLINE dvec4 operator-(const dvec4 &v0, const dvec4 &v1) { return sub(v0, v1); }

/// <summary>Returns the result of multiplication of each component of the first vector by the double value and addition of the corresponding component of the second vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE dvec4 &mad(dvec4 &ret, const dvec4 &v0, double v1, const dvec4 &v2)
{
	#ifdef USE_SSE
		__m128d temp = _mm_set1_pd(v1);
		ret.sse.v0 = _mm_add_pd(_mm_mul_pd(v0.sse.v0, temp), v2.sse.v0);
		ret.sse.v1 = _mm_add_pd(_mm_mul_pd(v0.sse.v1, temp), v2.sse.v1);
	#else
		ret.x = v0.x * v1 + v2.x;
		ret.y = v0.y * v1 + v2.y;
		ret.z = v0.z * v1 + v2.z;
		ret.w = v0.w * v1 + v2.w;
	#endif
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c). The result is assigned to the ret argument.</summary>
UNIGINE_INLINE dvec4 &mad(dvec4 &ret, const dvec4 &v0, const dvec4 &v1, const dvec4 &v2)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_add_pd(_mm_mul_pd(v0.sse.v0, v1.sse.v0), v2.sse.v0);
		ret.sse.v1 = _mm_add_pd(_mm_mul_pd(v0.sse.v1, v1.sse.v1), v2.sse.v1);
	#else
		ret.x = v0.x * v1.x + v2.x;
		ret.y = v0.y * v1.y + v2.y;
		ret.z = v0.z * v1.z + v2.z;
		ret.w = v0.w * v1.w + v2.w;
	#endif
	return ret;
}
/// <summary>Returns the result of multiplication of each component of the first vector by the double value and addition of the corresponding component of the second vector (a * b + c).</summary>
UNIGINE_INLINE dvec4 mad(const dvec4 &v0, double v1, const dvec4 &v2)
{
	dvec4 ret;
	return mad(ret, v0, v1, v2);
}
/// <summary>Returns the result of multiplication of each component of the first vector by the corresponding component of the second vector and addition of the corresponding component of the third vector (a * b + c).</summary>
UNIGINE_INLINE dvec4 mad(const dvec4 &v0, const dvec4 &v1, const dvec4 &v2)
{
	dvec4 ret;
	return mad(ret, v0, v1, v2);
}

/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE double dot(const dvec3 &v0, const dvec4 &v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v1.w;
}
/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE double dot(const dvec4 &v0, const dvec3 &v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w;
}
/// <summary>Dot product of vectors.</summary>
UNIGINE_INLINE double dot(const dvec4 &v0, const dvec4 &v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
}

/// <summary>Dot product only of three components of vectors. W component of four-component vector is ignored.</summary>
UNIGINE_INLINE double dot3(const dvec3 &v0, const dvec4 &v1) { return dot(v0, v1.xyz); }
/// <summary>Dot product only of three components of vectors. W component of four-component vector is ignored.</summary>
UNIGINE_INLINE double dot3(const dvec4 &v0, const dvec3 &v1) { return dot(v0.xyz, v1); }
/// <summary>Dot product only of three components of vectors. W components of four-component vectors are ignored.</summary>
UNIGINE_INLINE double dot3(const dvec4 &v0, const dvec4 &v1) { return dot(v0.xyz, v1.xyz); }

/// <summary>Compares the arguments component-wise and returns the minimum value for each component by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec4 &min(dvec4 &ret, const dvec4 &v0, const dvec4 &v1)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_min_pd(v0.sse.v0, v1.sse.v0);
		ret.sse.v1 = _mm_min_pd(v0.sse.v1, v1.sse.v1);
	#else
		ret.x = min(v0.x, v1.x);
		ret.y = min(v0.y, v1.y);
		ret.z = min(v0.z, v1.z);
		ret.w = min(v0.w, v1.w);
	#endif
	return ret;
}
/// <summary>Compares the arguments component-wise and returns the minimum value for each component.</summary>
UNIGINE_INLINE dvec4 min(const dvec4 &v0, const dvec4 &v1)
{
	dvec4 ret;
	return min(ret, v0, v1);
}

/// <summary>Compares the arguments component-wise and returns the maximum value for each component by saving it in the ret argument.</summary>
UNIGINE_INLINE dvec4 &max(dvec4 &ret, const dvec4 &v0, const dvec4 &v1)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_max_pd(v0.sse.v0, v1.sse.v0);
		ret.sse.v1 = _mm_max_pd(v0.sse.v1, v1.sse.v1);
	#else
		ret.x = max(v0.x, v1.x);
		ret.y = max(v0.y, v1.y);
		ret.z = max(v0.z, v1.z);
		ret.w = max(v0.w, v1.w);
	#endif
	return ret;
}
/// <summary>Compares the arguments component-wise and returns the maximum value for each component.</summary>
UNIGINE_INLINE dvec4 max(const dvec4 &v0, const dvec4 &v1)
{
	dvec4 ret;
	return max(ret, v0, v1);
}

/// <summary>Clamps the value (v) within the minimum (v0) and maximum (v1) limits and saves the result in the ret argument.</summary>
UNIGINE_INLINE dvec4 &clamp(dvec4 &ret, const dvec4 &v, const dvec4 &v0, const dvec4 &v1)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_min_pd(_mm_max_pd(v.sse.v0, v0.sse.v0), v1.sse.v0);
		ret.sse.v1 = _mm_min_pd(_mm_max_pd(v.sse.v1, v0.sse.v1), v1.sse.v1);
	#else
		ret.x = clamp(v.x, v0.x, v1.x);
		ret.y = clamp(v.y, v0.y, v1.y);
		ret.z = clamp(v.z, v0.z, v1.z);
		ret.w = clamp(v.w, v0.w, v1.w);
	#endif
	return ret;
}
/// <summary>Clamps the value (v) within the minimum (v0) and maximum (v1) limits and returns the result.</summary>
UNIGINE_INLINE dvec4 clamp(const dvec4 &v, const dvec4 &v0, const dvec4 &v1)
{
	dvec4 ret;
	return clamp(ret, v, v0, v1);
}

/// <summary>Clamps the vector component values within the range [0.0, 1.0] and saves the result in the ret argument.</summary>
UNIGINE_INLINE dvec4 &saturate(dvec4 &ret, const dvec4 &v)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_min_pd(_mm_max_pd(v.sse.v0, dvec4_zero.sse.v0), dvec4_one.sse.v0);
		ret.sse.v1 = _mm_min_pd(_mm_max_pd(v.sse.v1, dvec4_zero.sse.v1), dvec4_one.sse.v1);
	#else
		ret.x = saturate(v.x);
		ret.y = saturate(v.y);
		ret.z = saturate(v.z);
		ret.w = saturate(v.w);
	#endif
	return ret;
}
/// <summary>Clamps the vector component values within the range [0.0, 1.0] and returns the result.</summary>
UNIGINE_INLINE dvec4 saturate(const dvec4 &v)
{
	dvec4 ret;
	return saturate(ret, v);
}

/// <summary>Interpolates the vector component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE dvec4 &lerp(dvec4 &ret, const dvec4 &v0, const dvec4 &v1, double k)
{
	#ifdef USE_SSE
		__m128d temp = _mm_set1_pd(k);
		ret.sse.v0 = _mm_add_pd(v0.sse.v0, _mm_mul_pd(_mm_sub_pd(v1.sse.v0, v0.sse.v0), temp));
		ret.sse.v1 = _mm_add_pd(v0.sse.v1, _mm_mul_pd(_mm_sub_pd(v1.sse.v1, v0.sse.v1), temp));
	#else
		ret.x = lerp(v0.x, v1.x, k);
		ret.y = lerp(v0.y, v1.y, k);
		ret.z = lerp(v0.z, v1.z, k);
		ret.w = lerp(v0.w, v1.w, k);
	#endif
	return ret;
}
/// <summary>Returns the vector component values interpolated according to the formula v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE dvec4 lerp(const dvec4 &v0, const dvec4 &v1, double k)
{
	dvec4 ret;
	return lerp(ret, v0, v1, k);
}

/// <summary>Performs linear interpolation between three vectors.</summary>
UNIGINE_INLINE dvec4 &lerp3(dvec4 &ret, const dvec4 &v0, const dvec4 &v1, const dvec4 &v2, float k)
{
	if (k < 0.5f)
		lerp(ret, v0, v1, k * 2.0);
	else
		lerp(ret, v1, v2, k * 2.0 - 1.0);
	return ret;
}
/// <summary>Performs linear interpolation between three vectors.</summary>
UNIGINE_INLINE dvec4 lerp3(const dvec4 &v0, const dvec4 &v1, const dvec4 &v2, float k)
{
	dvec4 ret;
	return lerp3(ret, v0, v1, v2, k);
}

/// <summary>Returns the cross product of two vectors.</summary>
UNIGINE_INLINE dvec4 &cross(dvec4 &ret, const dvec3 &v0, const dvec3 &v1)
{
	ret.x = v0.y * v1.z - v0.z * v1.y;
	ret.y = v0.z * v1.x - v0.x * v1.z;
	ret.z = v0.x * v1.y - v0.y * v1.x;
	return ret;
}

/// <summary>Returns an argument rounded to the nearest integral value.</summary>
UNIGINE_INLINE dvec4 round(const dvec4 &v) { return {round(v.x), round(v.y), round(v.z), round(v.w)}; }
/// <summary>Returns the largest integral value that's less than or equal to the argument.</summary>
UNIGINE_INLINE dvec4 floor(const dvec4 &v)
{
	#ifdef USE_SSE
		return dvec4(_mm_floor_pd(v.sse.v0), _mm_floor_pd(v.sse.v1));
	#else
		return {floor(v.x), floor(v.y), floor(v.z), floor(v.w)};
	#endif
}
/// <summary>Returns the smallest integral value that's greater than or equal to the argument.</summary>
UNIGINE_INLINE dvec4 ceil(const dvec4 &v)
{
	#ifdef USE_SSE
		return dvec4(_mm_ceil_pd(v.sse.v0), _mm_ceil_pd(v.sse.v1));
	#else
		return {ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w)};
	#endif
}

/// <summary>Returns the absolute value of the specified argument.</summary>
UNIGINE_INLINE dvec4 abs(const dvec4 &v)
{
	return {abs(v.x), abs(v.y), abs(v.z), abs(v.w)};
}
/// <summary>Returns the fractional part of the argument.</summary>
UNIGINE_INLINE dvec4 frac(const dvec4 &v)
{
	return {frac(v.x), frac(v.y), frac(v.z), frac(v.w)};
}

/// <summary>Returns the value calculated according to the formula: (v - v0) / (v1 - v0) clamped within 0.0f and 1.0f.</summary>
UNIGINE_INLINE dvec4 inverseLerp(const dvec4 &v0, const dvec4 &v1, const dvec4 &v)
{
	return saturate((v - v0) / (v1 - v0));
}

/// <summary>Transforms the value from the source range to the corresponding value within target range.</summary>
/// <param name="value">The value within the source range, which is to be reranged.</param>
/// <param name="range">X and Y define the source range, Z and W define the target range.</param>
UNIGINE_INLINE double changeRange(double value, const dvec4 &range)
{
	return saturate(value - range.x) / range.y * range.w + range.z;
}

}
}