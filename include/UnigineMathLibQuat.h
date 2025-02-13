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
#include "UnigineMathLibVec3.h"
#include "UnigineMathLibVec4.h"

#include "UnigineMathLibDVec2.h"
#include "UnigineMathLibDVec3.h"
#include "UnigineMathLibDVec4.h"

#include "UnigineMathLibMat2.h"
#include "UnigineMathLibMat3.h"
#include "UnigineMathLibMat4.h"

#include "UnigineMathLibDMat4.h"

namespace Unigine
{
namespace Math
{

struct alignas(16) quat
{
	/// <summary>Constructor. Initializes the quaternion using given constant float values.</summary>
	UNIGINE_INLINE constexpr quat(float x_, float y_, float z_, float w_, ConstexprTag): x(x_), y(y_), z(z_), w(w_) {}

	/// <summary>Default constructor. Produces an identity quaternion (0.0, 0.0, 0.0, 1.0).</summary>
	UNIGINE_INLINE quat()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(1.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the quaternion using the given rotation axis component values and angle.</summary>
	UNIGINE_INLINE quat(float x, float y, float z, float angle)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(x, y, z, angle);
	}
	/// <summary>Constructor. Initializes the quaternion using given angles for each axis.</summary>
	UNIGINE_INLINE quat(float angle_x, float angle_y, float angle_z)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(angle_x, angle_y, angle_z);
	}
	/// <summary>Constructor. Initializes the quaternion using given rotation axis and angle.</summary>
	UNIGINE_INLINE quat(const vec3 &axis, float angle)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(axis, angle);
	}
	/// <summary>Constructor. Initializes the quaternion using three given matrix columns represented by vec3 vectors.</summary>
	UNIGINE_INLINE quat(const vec3 &col0, const vec3 &col1, const vec3 &col2)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(col0, col1, col2);
	}

	/// <summary>Constructor. Initializes the quaternion by copying a given source quaternion.</summary>
	UNIGINE_INLINE quat(const quat &q)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(q);
	}
	/// <summary>Constructor. Initializes the quaternion by copying a given source quaternion.</summary>
	UNIGINE_INLINE explicit quat(const float *q)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(q);
	}
	/// <summary>Constructor. Initializes the quaternion using a given four-component vec4 source vector.</summary>
	UNIGINE_INLINE explicit quat(const vec4 &v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(v);
	}
	/// <summary>Constructor. Initializes the quaternion using a given mat3 source matrix (3x3).</summary>
	UNIGINE_INLINE explicit quat(const mat3 &m)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m);
	}
	/// <summary>Constructor. Initializes the quaternion using a given mat4 source matrix (4x4).</summary>
	UNIGINE_INLINE explicit quat(const mat4 &m)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m);
	}
	/// <summary>Constructor. Initializes the quaternion using a given dmat4 source matrix (3x4).</summary>
	UNIGINE_INLINE explicit quat(const dmat4 &m)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m);
	}

	#ifdef USE_SSE
		/// <summary>Constructor. Initializes the quaternion using a given __m128 variable (128-bit). We do not recommend to use this method unless you have a clear understanding of SSE2.</summary>
		UNIGINE_INLINE quat(const __m128 &v): vec(v)
		{
			UNIGINE_ASSERT_ALIGNED16(this);
		}
		UNIGINE_INLINE quat &operator=(const __m128 &v) { vec = v; return *this; }

		UNIGINE_INLINE void set(const vec4 &v) { vec = v.vec; }
		UNIGINE_INLINE void set(const quat &v) { vec = v.vec; }
	#else
		UNIGINE_INLINE void set(const vec4 &v) { x = v.x; y = v.y; z = v.z; w = v.w; }
		UNIGINE_INLINE void set(const quat &v) { x = v.x; y = v.y; z = v.z; w = v.w; }
	#endif

	/// <summary>Sets the quaternion using a given mat3 source matrix (3x3).</summary>
	UNIGINE_INLINE void set(const mat3 &m)
	{
		quat q = m.getQuat();
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}
	/// <summary>Sets the quaternion using a given mat4 source matrix (4x4).</summary>
	UNIGINE_INLINE void set(const mat4 &m)
	{
		quat q = mat3(m).getQuat();
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}
	/// <summary>Sets the quaternion using a given dmat4 source matrix (3x4).</summary>
	UNIGINE_INLINE void set(const dmat4 &m)
	{
		quat q = mat3(m).getQuat();
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}
	/// <summary>Sets the quaternion using given rotation axis and angle.</summary>
	UNIGINE_INLINE void set(const vec3 &axis, float angle)
	{
		float s, c;
		Math::sincos(angle * Consts::DEG2RAD * 0.5f, s, c);
		float ilength = Math::rsqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
		x = axis.x * ilength * s;
		y = axis.y * ilength * s;
		z = axis.z * ilength * s;
		w = c;
	}
	/// <summary>Sets the quaternion using the axis coordinates and the angle.</summary>
	UNIGINE_INLINE void set(float axis_x, float axis_y, float axis_z, float angle)
	{
		float s, c;
		Math::sincos(angle * Consts::DEG2RAD * 0.5f, s, c);
		float ilength = Math::rsqrt(axis_x * axis_x + axis_y * axis_y + axis_z * axis_z);
		x = axis_x * ilength * s;
		y = axis_y * ilength * s;
		z = axis_z * ilength * s;
		w = c;
	}
	/// <summary>Sets the quaternion using given angles for each axis.</summary>
	UNIGINE_INLINE void set(float angle_x, float angle_y, float angle_z)
	{
		float sx, cx, sy, cy, sz, cz;
		Math::sincos(angle_x * Consts::DEG2RAD * 0.5f, sx, cx);
		Math::sincos(angle_y * Consts::DEG2RAD * 0.5f, sy, cy);
		Math::sincos(angle_z * Consts::DEG2RAD * 0.5f, sz, cz);
		float sxcy = sx * cy;
		float cxcy = cx * cy;
		float sxsy = sx * sy;
		float cxsy = cx * sy;
		x = cxsy * sz + sxcy * cz;
		y = cxsy * cz - sxcy * sz;
		z = sxsy * cz + cxcy * sz;
		w = cxcy * cz - sxsy * sz;
	}
	/// <summary>Sets the quaternion using three given matrix columns represented by vec3 vectors.</summary>
	UNIGINE_INLINE void set(const vec3 &col0, const vec3 &col1, const vec3 &col2)
	{
		quat q = mat3(col0, col1, col2).getQuat();
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}
	/// <summary>Sets the quaternion using a given pointer to the source quaternion.</summary>
	UNIGINE_INLINE void set(const float *q)
	{
		x = q[0];
		y = q[1];
		z = q[2];
		w = q[3];
	}

	/// <summary>Returns the rotation axis and angle of the quaternion and puts the values to corresponding variables: axis.x = x, axis.y = y, axis.z = z, angle = w.</summary>
	UNIGINE_INLINE void get(vec3 &axis, float &angle) const
	{
		float ilength = Math::rsqrt(x * x + y * y + z * z);
		axis.x = x * ilength;
		axis.y = y * ilength;
		axis.z = z * ilength;
		angle = acos(clamp(w, -1.0f, 1.0f)) * Consts::RAD2DEG * 2.0f;
		if (angle > 180.0f)
			angle -= 360.0f;
	}
	/// <summary>Returns the quaternion: qq[0]=x, qq[1]=y, qq[2]=z, qq[3]=w.</summary>
	UNIGINE_INLINE void get(float *qq) const
	{
		qq[0] = x;
		qq[1] = y;
		qq[2] = z;
		qq[3] = w;
	}
	/// <summary>Returns a pointer to the quaternion.</summary>
	UNIGINE_INLINE float *get() { return q; }
	/// <summary>Returns a constant pointer to the quaternion.</summary>
	UNIGINE_INLINE const float *get() const { return q; }

	/// <summary>Performs type conversion to float *.</summary>
	UNIGINE_INLINE operator float *() { return q; }
	/// <summary>Performs type conversion to const float *.</summary>
	UNIGINE_INLINE operator const float *() const { return q; }
	/// <summary>Performs type conversion to void *.</summary>
	UNIGINE_INLINE operator void *() { return q; }
	/// <summary>Performs type conversion to const void *.</summary>
	UNIGINE_INLINE operator const void *() const { return q; }

	/// <summary>Performs array access to the quaternion item reference by using given item index.</summary>
	UNIGINE_INLINE float &operator[](int i)
	{
		assert((unsigned int)i < 4 && "quat::operator[](): bad index");
		return q[i];
	}
	/// <summary>Performs array access to the quaternion item by using given item index.</summary>
	UNIGINE_INLINE float operator[](int i) const
	{
		assert((unsigned int)i < 4 && "quat::operator[](): bad index");
		return q[i];
	}

	/// <summary>Performs quaternion assignment. Destination quaternion = Source quaternion.</summary>
	UNIGINE_INLINE quat &operator=(const quat &q) { set(q); return *this; }
	/// <summary>erforms quaternion negation. The sign of each component of the quaternion is flipped.</summary>
	UNIGINE_INLINE quat operator-() const
	{
		quat ret;
		ret.x = -x;
		ret.y = -y;
		ret.z = -z;
		ret.w = -w;
		return ret;
	}

	/// <summary>Performs scalar multiplication.</summary>
	UNIGINE_INLINE quat &operator*=(float v);
	/// <summary>Performs quaternion multiplication.</summary>
	UNIGINE_INLINE quat &operator*=(const quat &q);

	/// <summary>Performs quaternion addition.</summary>
	UNIGINE_INLINE quat &operator+=(const quat &q);
	/// <summary>Performs quaternion subtraction.</summary>
	UNIGINE_INLINE quat &operator-=(const quat &q);

	/// <summary>Returns the rotation matrix for the quaternion.</summary>
	UNIGINE_INLINE mat3 getMat3() const
	{
		mat3 ret;
		float x2 = x * 2.0f;
		float y2 = y * 2.0f;
		float z2 = z * 2.0f;
		float xx2 = x * x2;
		float yy2 = y * y2;
		float zz2 = z * z2;
		float zx2 = z * x2;
		float xy2 = x * y2;
		float yz2 = y * z2;
		float wx2 = w * x2;
		float wy2 = w * y2;
		float wz2 = w * z2;
		ret.m00 = 1.0f - yy2 - zz2;
		ret.m01 = xy2 - wz2;
		ret.m02 = zx2 + wy2;
		ret.m10 = xy2 + wz2;
		ret.m11 = 1.0f - xx2 - zz2;
		ret.m12 = yz2 - wx2;
		ret.m20 = zx2 - wy2;
		ret.m21 = yz2 + wx2;
		ret.m22 = 1.0f - xx2 - yy2;
		return ret;
	}

	/// <summary>Returns the quaternion normal vector.</summary>
	UNIGINE_INLINE vec3 getNormal() const
	{
		vec3 ret;
		float x2 = x * 2.0f;
		float y2 = y * 2.0f;
		float z2 = z * 2.0f;
		ret.x = z * x2 + w * y2;
		ret.y = y * z2 - w * x2;
		ret.z = 1.0f - x * x2 - y * y2;
		return ret;
	}
	/// <summary>Returns the quaternion tangent vector.</summary>
	UNIGINE_INLINE vec3 getTangent() const
	{
		vec3 ret;
		float x2 = x * 2.0f;
		float y2 = y * 2.0f;
		float z2 = z * 2.0f;
		ret.x = 1.0f - y * y2 - z * z2;
		ret.y = x * y2 + w * z2;
		ret.z = z * x2 - w * y2;
		return ret;
	}
	/// <summary>Returns the quaternion tangent vector and binormal orientation as a four-component vec4 vector.</summary>
	UNIGINE_INLINE vec4 getTangent4() const
	{
		vec4 ret;
		float x2 = x * 2.0f;
		float y2 = y * 2.0f;
		float z2 = z * 2.0f;
		ret.x = 1.0f - y * y2 - z * z2;
		ret.y = x * y2 + w * z2;
		ret.z = z * x2 - w * y2;
		ret.w = Math::sign(w);
		return ret;
	}
	/// <summary>Returns the quaternion binormal vector with respect to orientation.</summary>
	UNIGINE_INLINE vec3 getBinormal() const
	{
		vec3 ret;
		float x2 = x * 2.0f;
		float y2 = y * 2.0f;
		float z2 = z * 2.0f;
		ret.x = x * y2 - w * z2;
		ret.y = 1.0f - x * x2 - z * z2;
		ret.z = y * z2 + w * x2;
		return ret * Math::sign(w);
	}

	/// <summary>Returns the rotation angle of the quaternion for a given rotation axis, in degrees, within the [-180, 180] range.</summary>
	UNIGINE_INLINE float getAngle(const vec3 &axis) const;

	/// <summary>Returns normalized quaternion.</summary>
	UNIGINE_INLINE quat &normalize()
	{
		float ilength = Math::rsqrt(x * x + y * y + z * z + w * w);
		x *= ilength;
		y *= ilength;
		z *= ilength;
		w *= ilength;
		return *this;
	}
	/// <summary>Normalizes a quaternion, makes its magnitude equal to 1. When normalized, a quaternion keeps the same direction but its length is equal to 1. Check for the zero quaternion is performed: if the argument is a zero quaternion, then a zero quaternion is returned.</summary>
	UNIGINE_INLINE quat &normalizeValid()
	{
		float length = x * x + y * y + z * z + w * w;
		if (length == 0.0f)
			return *this;
		float ilength = Math::rsqrt(length);
		x *= ilength;
		y *= ilength;
		z *= ilength;
		w *= ilength;
		return *this;
	}
	/// <summary>Returns normalized quaternion, calculated using the fast inverse square root algorithm.</summary>
	UNIGINE_INLINE quat &normalizeFast()
	{
		float ilength = Math::rsqrtFast(x * x + y * y + z * z + w * w);
		x *= ilength;
		y *= ilength;
		z *= ilength;
		w *= ilength;
		return *this;
	}
	/// <summary>Returns normalized quaternion, calculated using the fast inverse square root algorithm. Check for the zero quaternion is performed: if the argument is a zero quaternion, then a zero quaternion is returned.</summary>
	UNIGINE_INLINE quat &normalizeValidFast()
	{
		float length = x * x + y * y + z * z + w * w;
		if (length == 0.0f)
			return *this;
		float ilength = Math::rsqrtFast(length);
		x *= ilength;
		y *= ilength;
		z *= ilength;
		w *= ilength;
		return *this;
	}

	/// <summary>Returns a hash for the quaternion.</summary>
	UNIGINE_INLINE unsigned int hash() const { return hashCombine(hashCombine(hashCombine(hashInteger(x), y), z), w); }

	union
	{
		struct
		{
			float x, y, z, w;
		};
		float q[4];
		#ifdef USE_SSE
			__m128 vec; // DO NOT TOUCH UNLESS ABSOLUTELY SURE
		#endif
	};
};

/// <summary>Zero quaternion (0.0, 0.0, 0.0, 0.0).</summary>
constexpr quat quat_zero(0.0f, 0.0f, 0.0f, 0.0f, ConstexprTag{});
/// <summary>Quaternion representing no rotation (0.0, 0.0, 0.0, 1.0).</summary>
constexpr quat quat_identity(0.0f, 0.0f, 0.0f, 1.0f, ConstexprTag{});


/// <summary>Normalizes a quaternion, makes its magnitude equal to 1. When normalized, a quaternion keeps the same oreintation but its magnitude is equal to 1.</summary>
UNIGINE_INLINE quat normalize(const quat &q)
{
	quat ret = q;
	return ret.normalize();
}
/// <summary>Normalizes a quaternion, makes its magnitude equal to 1. When normalized, a quaternion keeps the same oreintation but its magnitude is equal to 1. Check for the zero vector is performed: if the argument is a zero vector, then a zero vector is returned.</summary>
UNIGINE_INLINE quat normalizeValid(const quat &q)
{
	quat ret = q;
	return ret.normalizeValid();
}

/// <summary>Returns a resulting matrix for rotation by the specified angle around the axis specified as a quaternion/vector/vector components. The resulting matrix size for this method is 3 x 3.</summary>
UNIGINE_INLINE mat3 rotate3(const quat &q) { return q.getMat3(); }
/// <summary>Returns a resulting matrix for rotation by the specified angle around the axis specified as a quaternion/vector/vector components.</summary>
UNIGINE_INLINE mat4 rotate(const quat &q) { return mat4(q.getMat3()); }


/// <summary>Compares two quaternions according to the degree of precision equal to 1.0e-6f. Returns 1 if they are equal, otherwise 0.</summary>
UNIGINE_INLINE int compare(const quat &q0, const quat &q1)
{
	return (compare(q0.x, q1.x) && compare(q0.y, q1.y) && compare(q0.z, q1.z) && compare(q0.w, q1.w));
}
/// <summary>Compares two quaternions according to the specified degree of precision. Returns 1 if they are equal, otherwise 0.</summary>
UNIGINE_INLINE int compare(const quat &q0, const quat &q1, float epsilon)
{
	return (compare(q0.x, q1.x, epsilon) && compare(q0.y, q1.y, epsilon) && compare(q0.z, q1.z, epsilon) && compare(q0.w, q1.w, epsilon));
}
/// <summary>Quaternion equality comparison.</summary>
UNIGINE_INLINE int operator==(const quat &q0, const quat &q1) { return compare(q0, q1); }
/// <summary>Quaternion non-equality comparison.</summary>
UNIGINE_INLINE int operator!=(const quat &q0, const quat &q1) { return !compare(q0, q1); }


/// <summary>Quaternion multiplication by the vector value.</summary>
UNIGINE_INLINE vec3 &mul(vec3 &ret, const quat &q, const vec3 &v)
{
	float x2 = q.x + q.x;
	float y2 = q.y + q.y;
	float z2 = q.z + q.z;
	float xx2 = q.x * x2;
	float yy2 = q.y * y2;
	float zz2 = q.z * z2;
	float zx2 = q.z * x2;
	float xy2 = q.x * y2;
	float yz2 = q.y * z2;
	float wx2 = q.w * x2;
	float wy2 = q.w * y2;
	float wz2 = q.w * z2;
	float x = v.x;
	float y = v.y;
	float z = v.z;
	ret.x = (1.0f - yy2 - zz2) * x + (xy2 - wz2) * y + (zx2 + wy2) * z;
	ret.y = (xy2 + wz2) * x + (1.0f - xx2 - zz2) * y + (yz2 - wx2) * z;
	ret.z = (zx2 - wy2) * x + (yz2 + wx2) * y + (1.0f - xx2 - yy2) * z;
	return ret;
}
/// <summary>Vector multiplication by the quaternion.</summary>
UNIGINE_INLINE vec3 &mul(vec3 &ret, const vec3 &v, const quat &q)
{
	float x2 = q.x + q.x;
	float y2 = q.y + q.y;
	float z2 = q.z + q.z;
	float xx2 = q.x * x2;
	float yy2 = q.y * y2;
	float zz2 = q.z * z2;
	float zx2 = q.z * x2;
	float xy2 = q.x * y2;
	float yz2 = q.y * z2;
	float wx2 = q.w * x2;
	float wy2 = q.w * y2;
	float wz2 = q.w * z2;
	float x = v.x;
	float y = v.y;
	float z = v.z;
	ret.x = (1.0f - yy2 - zz2) * x + (xy2 + wz2) * y + (zx2 - wy2) * z;
	ret.y = (xy2 - wz2) * x + (1.0f - xx2 - zz2) * y + (yz2 + wx2) * z;
	ret.z = (zx2 + wy2) * x + (yz2 - wx2) * y + (1.0f - xx2 - yy2) * z;
	return ret;
}
/// <summary>Quaternion multiplication by the vector value.</summary>
UNIGINE_INLINE dvec3 &mul(dvec3 &ret, const quat &q, const dvec3 &v)
{
	double x2 = q.x + q.x;
	double y2 = q.y + q.y;
	double z2 = q.z + q.z;
	double xx2 = q.x * x2;
	double yy2 = q.y * y2;
	double zz2 = q.z * z2;
	double zx2 = q.z * x2;
	double xy2 = q.x * y2;
	double yz2 = q.y * z2;
	double wx2 = q.w * x2;
	double wy2 = q.w * y2;
	double wz2 = q.w * z2;
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = (1.0 - yy2 - zz2) * x + (xy2 - wz2) * y + (zx2 + wy2) * z;
	ret.y = (xy2 + wz2) * x + (1.0 - xx2 - zz2) * y + (yz2 - wx2) * z;
	ret.z = (zx2 - wy2) * x + (yz2 + wx2) * y + (1.0 - xx2 - yy2) * z;
	return ret;
}
/// <summary>Vector multiplication by the quaternion.</summary>
UNIGINE_INLINE dvec3 &mul(dvec3 &ret, const dvec3 &v, const quat &q)
{
	double x2 = q.x + q.x;
	double y2 = q.y + q.y;
	double z2 = q.z + q.z;
	double xx2 = q.x * x2;
	double yy2 = q.y * y2;
	double zz2 = q.z * z2;
	double zx2 = q.z * x2;
	double xy2 = q.x * y2;
	double yz2 = q.y * z2;
	double wx2 = q.w * x2;
	double wy2 = q.w * y2;
	double wz2 = q.w * z2;
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = (1.0 - yy2 - zz2) * x + (xy2 + wz2) * y + (zx2 - wy2) * z;
	ret.y = (xy2 - wz2) * x + (1.0 - xx2 - zz2) * y + (yz2 + wx2) * z;
	ret.z = (zx2 + wy2) * x + (yz2 - wx2) * y + (1.0 - xx2 - yy2) * z;
	return ret;
}
/// <summary>Quaternion multiplication by the scalar value.</summary>
UNIGINE_INLINE quat &mul(quat &ret, const quat &q, float v)
{
	ret.x = q.x * v;
	ret.y = q.y * v;
	ret.z = q.z * v;
	ret.w = q.w * v;
	return ret;
}
/// <summary>Quaternion multiplication.</summary>
UNIGINE_INLINE quat &mul(quat &ret, const quat &q0, const quat &q1)
{
	float x0 = q0.x;
	float y0 = q0.y;
	float z0 = q0.z;
	float w0 = q0.w;
	float x1 = q1.x;
	float y1 = q1.y;
	float z1 = q1.z;
	float w1 = q1.w;
	ret.x = w0 * x1 + x0 * w1 + y0 * z1 - z0 * y1;
	ret.y = w0 * y1 + y0 * w1 + z0 * x1 - x0 * z1;
	ret.z = w0 * z1 + z0 * w1 + x0 * y1 - y0 * x1;
	ret.w = w0 * w1 - x0 * x1 - y0 * y1 - z0 * z1;
	return ret;
}
/// <summary>Quaternion multiplication by the scalar value.</summary>
UNIGINE_INLINE quat operator*(const quat &q, float v)
{
	quat ret;
	return mul(ret, q, v);
}
/// <summary>Quaternion multiplication by the vector value.</summary>
UNIGINE_INLINE vec3 operator*(const quat &q, const vec3 &v)
{
	vec3 ret;
	return mul(ret, q, v);
}
/// <summary>Vector multiplication by the quaternion.</summary>
UNIGINE_INLINE vec3 operator*(const vec3 &v, const quat &q)
{
	vec3 ret;
	return mul(ret, v, q);
}
/// <summary>Quaternion multiplication by the vector value.</summary>
UNIGINE_INLINE dvec3 operator*(const quat &q, const dvec3 &v)
{
	dvec3 ret;
	return mul(ret, q, v);
}
/// <summary>Vector multiplication by the quaternion.</summary>
UNIGINE_INLINE dvec3 operator*(const dvec3 &v, const quat &q)
{
	dvec3 ret;
	return mul(ret, v, q);
}
/// <summary>Quaternion multiplication.</summary>
UNIGINE_INLINE quat operator*(const quat &q0, const quat &q1)
{
	quat ret;
	return mul(ret, q0, q1);
}
/// <summary>Performs scalar multiplication.</summary>
UNIGINE_INLINE quat &quat::operator*=(float v)
{
	return mul(*this, *this, v);
}
/// <summary>Performs quaternion multiplication.</summary>
UNIGINE_INLINE quat &quat::operator*=(const quat &q)
{
	return mul(*this, quat(*this), q);
}

/// <summary>Performs quaternion addition.</summary>
UNIGINE_INLINE quat &add(quat &ret, const quat &q0, const quat &q1)
{
	ret.x = q0.x + q1.x;
	ret.y = q0.y + q1.y;
	ret.z = q0.z + q1.z;
	ret.w = q0.w + q1.w;
	return ret;
}
/// <summary>Performs quaternion addition.</summary>
UNIGINE_INLINE quat operator+(const quat &q0, const quat &q1)
{
	quat ret;
	return add(ret, q0, q1);
}
/// <summary>Performs quaternion addition.</summary>
UNIGINE_INLINE quat &quat::operator+=(const quat &q)
{
	return add(*this, *this, q);
}

/// <summary>Performs quaternion subtraction.</summary>
UNIGINE_INLINE quat &sub(quat &ret, const quat &q0, const quat &q1)
{
	ret.x = q0.x - q1.x;
	ret.y = q0.y - q1.y;
	ret.z = q0.z - q1.z;
	ret.w = q0.w - q1.w;
	return ret;
}
/// <summary>Performs quaternion subtraction.</summary>
UNIGINE_INLINE quat operator-(const quat &q0, const quat &q1)
{
	quat ret;
	return sub(ret, q0, q1);
}
/// <summary>Performs quaternion subtraction.</summary>
UNIGINE_INLINE quat &quat::operator-=(const quat &q)
{
	return sub(*this, *this, q);
}

/// <summary>Returns the result of multiplication of the first value by the second value and addition of the third value (a * b + c).</summary>
UNIGINE_INLINE quat &mad(quat &ret, const quat &q0, float v, const quat &q1)
{
	ret.x = q0.x * v + q1.x;
	ret.y = q0.y * v + q1.y;
	ret.z = q0.z * v + q1.z;
	ret.w = q0.w * v + q1.w;
	return ret;
}

/// <summary>Returns the dot product between two quaternions.</summary>
UNIGINE_INLINE float dot(const quat &q0, const quat &q1)
{
	return q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
}

/// <summary>Returns the inverse of a quaternion.</summary>
UNIGINE_INLINE quat &inverse(quat &ret, const quat &q)
{
	quat n = normalize(q);
	ret.x = -n.x;
	ret.y = -n.y;
	ret.z = -n.z;
	ret.w = n.w;
	return ret;
}
/// <summary>Returns the inverse of a quaternion.</summary>
UNIGINE_INLINE quat inverse(const quat &q)
{
	quat ret;
	return inverse(ret, q);
}

/// <summary>Returns the conjugate of a given quaternion.</summary>
UNIGINE_INLINE quat &conjugate(quat &ret, const quat &q)
{
	ret.x = -q.x;
	ret.y = -q.y;
	ret.z = -q.z;
	ret.w = q.w;
	return ret;
}
/// <summary>Returns the conjugate of a given quaternion.</summary>
UNIGINE_INLINE quat conjugate(const quat &q)
{
	quat ret;
	return conjugate(ret, q);
}

/// <summary>Spherical interpolation between two given quaternions.</summary>
UNIGINE_INLINE quat &slerp(quat &ret, const quat &q0, const quat &q1, float k)
{
	if (k <= 0.0f)
		ret = q0;
	else if (k >= 1.0f)
		ret = q1;
	else
	{
		float k0, k1;
		float c = dot(q0, q1);
		float ac = abs(c);
		if (ac < 1.0f - Consts::EPS)
		{
			float angle = Math::acos(ac);
			float is = Math::rcp(sin(angle));
			k0 = sin(angle * (1.0f - k)) * is;
			k1 = sin(angle * k) * is;
		} else
		{
			k0 = 1.0f - k;
			k1 = k;
		}
		if (c < 0.0f)
			k1 = -k1;
		ret.x = q0.x * k0 + q1.x * k1;
		ret.y = q0.y * k0 + q1.y * k1;
		ret.z = q0.z * k0 + q1.z * k1;
		ret.w = q0.w * k0 + q1.w * k1;
	}
	return ret;
}
/// <summary>Spherical interpolation between two given quaternions.</summary>
UNIGINE_INLINE quat slerp(const quat &q0, const quat &q1, float k)
{
	quat ret;
	return slerp(ret, q0, q1, k);
}


/// <summary>Quaternion division.</summary>
UNIGINE_INLINE quat operator/(const quat &q0, const quat &q1)
{
	return q0 * inverse(q1);
}

/// <summary>Returns trotation angle of the quaternion for the given rotation axis, in degrees, within the [-180, 180] range.</summary>
UNIGINE_INLINE float quat::getAngle(const vec3 &axis) const
{
	vec3 v0, v1;
	mul(v0, *this, axis);
	add(v1, v0, axis);
	v1.normalize();

	float angle = dot(axis, v1);
	if (abs(angle) > Consts::EPS)
	{
		quat q0, q1;
		q0.set(-cross(v0, axis, v1));
		q0.w = angle;
		mul(q1, q0, *this);
		q1.normalize();
		q1.get(v0, angle);
	} else
	{
		get(v0, angle);
	}

	if (dot(v0, axis) < 0.0f)
		angle = -angle;

	return angle;
}

/// <summary>Returns the angle (in degrees) between the given first and second quaternions. The angle returned is the unsigned acute angle between the two quaternions. This means the smaller of the two possible angles is used.</summary>
UNIGINE_INLINE float getAngle(const quat &q0, const quat &q1)
{
	quat d = q1 * inverse(q0);
	float angle = acos(clamp(d.w, -1.0f, 1.0f)) * 2.0f * Consts::RAD2DEG;
	if (angle > 180.0f)
		angle = 360.0f - angle;
	return angle;
}

/// <summary>Ensures that the returned quaternion has a non-negative scalar part (w). If it is negative, the entire quaternion is negated; otherwise, it remains unchanged.</summary>
UNIGINE_INLINE quat &abs(quat &ret, const quat &q)
{
	ret = (q.w < 0.0f ? -q : q);
	return ret;
}

/// <summary>Ensures that the returned quaternion has a non-negative scalar part (w). If it is negative, the entire quaternion is negated; otherwise, it remains unchanged.</summary>
UNIGINE_INLINE quat abs(const quat &q)
{
	quat ret;
	return abs(ret, q);
}

/// <summary>Converts a quaternion into a rotation vector in 3D space by computing the quaternion's logarithm. It extracts the axis of rotation and scales it by the angle.</summary>
UNIGINE_INLINE vec3 &log(vec3 &ret, const quat &q)
{
	ret.x = q.x;
	ret.y = q.y;
	ret.z = q.z;

	float length = fsqrt(q.x * q.x + q.y * q.y + q.z * q.z);
	if (Consts::EPS < length)
	{
		// half angle and normalization
		float k = acos(clamp(q.w, -1.0f, 1.0f)) / length;
		mul(ret, ret, k);
	}

	return ret;
}

/// <summary>Converts a quaternion into a rotation vector in 3D space by computing the quaternion's logarithm. It extracts the axis of rotation and scales it by the angle.</summary>
UNIGINE_INLINE vec3 log(const quat &q)
{
	vec3 ret;
	return log(ret, q);
}

/// <summary>Converts a 3D rotation vector into a quaternion.</summary>
UNIGINE_INLINE quat &exp(quat &ret, const vec3 &v)
{
	float half_angle = v.length();

	if (half_angle < Consts::EPS)
	{
		ret.x = v.x;
		ret.y = v.y;
		ret.z = v.z;
		ret.w = 1.0f;
		ret.normalize();
	} else
	{
		float s, c;
		sincos(half_angle, s, c);
		s /= half_angle;

		ret.x = v.x * s;
		ret.y = v.y * s;
		ret.z = v.z * s;
		ret.w = c;
	}

	return ret;
}

/// <summary>Converts a 3D rotation vector into a quaternion.</summary>
UNIGINE_INLINE quat exp(const vec3 &v)
{
	quat ret;
	return exp(ret, v);
}

}
}
