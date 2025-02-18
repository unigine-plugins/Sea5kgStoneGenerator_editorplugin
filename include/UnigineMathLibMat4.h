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

#include "UnigineMathLibDVec2.h"
#include "UnigineMathLibDVec3.h"

#include "UnigineMathLibMat2.h"
#include "UnigineMathLibMat3.h"

#ifdef __GNUC__
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wreorder"
#endif

namespace Unigine
{
namespace Math
{

struct alignas(16) mat4
{
	UNIGINE_INLINE constexpr mat4(float v, ConstexprTag)
		: m00(v), m10(v), m20(v), m30(v)
		, m01(v), m11(v), m21(v), m31(v)
		, m02(v), m12(v), m22(v), m32(v)
		, m03(v), m13(v), m23(v), m33(v)
	{}
	UNIGINE_INLINE constexpr mat4(
		float m00_, float m10_, float m20_, float m30_,
		float m01_, float m11_, float m21_, float m31_,
		float m02_, float m12_, float m22_, float m32_,
		float m03_, float m13_, float m23_, float m33_
		, ConstexprTag)
		: m00(m00_), m10(m10_), m20(m20_), m30(m30_)
		, m01(m01_), m11(m11_), m21(m21_), m31(m31_)
		, m02(m02_), m12(m12_), m22(m22_), m32(m32_)
		, m03(m03_), m13(m13_), m23(m23_), m33(m33_)
	{}

	/// <summary>Default constructor. Produces an identity matrix.</summary>
	UNIGINE_INLINE mat4()
		: m00(1.0f), m10(0.0f), m20(0.0f), m30(0.0f)
		, m01(0.0f), m11(1.0f), m21(0.0f), m31(0.0f)
		, m02(0.0f), m12(0.0f), m22(1.0f), m32(0.0f)
		, m03(0.0f), m13(0.0f), m23(0.0f), m33(1.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the matrix using the given source matrix values.</summary>
	UNIGINE_INLINE mat4(
		float m00_, float m10_, float m20_, float m30_,
		float m01_, float m11_, float m21_, float m31_,
		float m02_, float m12_, float m22_, float m32_,
		float m03_, float m13_, float m23_, float m33_)
		: m00(m00_), m10(m10_), m20(m20_), m30(m30_)
		, m01(m01_), m11(m11_), m21(m21_), m31(m31_)
		, m02(m02_), m12(m12_), m22(m22_), m32(m32_)
		, m03(m03_), m13(m13_), m23(m23_), m33(m33_)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the matrix by copying a given source matrix.</summary>
	UNIGINE_INLINE mat4(const mat4 &m)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m);
	}
	/// <summary>Constructor. Initializes the matrix using a given scalar value. </summary>
	UNIGINE_INLINE explicit mat4(float v)
		: m00(v)
		, m10(v)
		, m20(v)
		, m30(v)
		, m01(v)
		, m11(v)
		, m21(v)
		, m31(v)
		, m02(v)
		, m12(v)
		, m22(v)
		, m32(v)
		, m03(v)
		, m13(v)
		, m23(v)
		, m33(v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the matrix using a given mat2 source matrix (2x2). The matrix elements are filled using corresponding elements of the source matrix.</summary>
	UNIGINE_INLINE explicit mat4(const mat2 &m)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m);
	}
	/// <summary>Constructor. Initializes the matrix using a given mat3 source matrix (3x3). The matrix elements are filled using corresponding elements of the source matrix.</summary>
	UNIGINE_INLINE explicit mat4(const mat3 &m)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m);
	}
	/// <summary>Constructor. Initializes the matrix using a given source dmat4 matrix. The matrix elements are filled using corresponding elements of the source matrix.</summary>
	UNIGINE_INLINE explicit mat4(const dmat4 &m)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m);
	}
	/// <summary>Constructor. Initializes the matrix using a given source quaternion.</summary>
	UNIGINE_INLINE explicit mat4(const quat &q)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(q);
	}
	/// <summary>Constructor. Initializes the matrix using the given source matrix values.</summary>
	/// <param name="m">The source value storing matrix values.</param>
	/// <param name="transposed">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
	UNIGINE_INLINE explicit mat4(const mat4x4_values &m, int transposed)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m, transposed);
	}
	/// <summary>Constructor. Initializes the matrix using the given source matrix values.</summary>
	UNIGINE_INLINE explicit mat4(const mat4x4_values &m)
		: m00(m[0])
		, m10(m[1])
		, m20(m[2])
		, m30(m[3])
		, m01(m[4])
		, m11(m[5])
		, m21(m[6])
		, m31(m[7])
		, m02(m[8])
		, m12(m[9])
		, m22(m[10])
		, m32(m[11])
		, m03(m[12])
		, m13(m[13])
		, m23(m[14])
		, m33(m[15])
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the matrix using the given source matrix values.</summary>
	/// <param name="m">The source value storing matrix values.</param>
	/// <param name="transposed">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
	UNIGINE_INLINE explicit mat4(const dmat4x4_values &m, int transpose)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m, transpose);
	}
	/// <summary>Constructor. Initializes the matrix using the given source matrix values.</summary>
	UNIGINE_INLINE explicit mat4(const dmat4x4_values &m)
		: m00(toFloat(m[0]))
		, m10(toFloat(m[1]))
		, m20(toFloat(m[2]))
		, m30(toFloat(m[3]))
		, m01(toFloat(m[4]))
		, m11(toFloat(m[5]))
		, m21(toFloat(m[6]))
		, m31(toFloat(m[7]))
		, m02(toFloat(m[8]))
		, m12(toFloat(m[9]))
		, m22(toFloat(m[10]))
		, m32(toFloat(m[11]))
		, m03(toFloat(m[12]))
		, m13(toFloat(m[13]))
		, m23(toFloat(m[14]))
		, m33(toFloat(m[15]))
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the matrix using a given source mat3 matrix (3x3) and a vec3 vector.</summary>
	UNIGINE_INLINE mat4(const mat3 &m, const vec3 &v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m, v);
	}
	/// <summary>Constructor. Initializes the matrix using a given quaternion and a vec3 vector.</summary>
	UNIGINE_INLINE mat4(const quat &q, const vec3 &v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(q, v);
	}
	/// <summary>Constructor. Initializes the matrix using given four vec4 vectors, each of them filling a column.</summary>
	UNIGINE_INLINE mat4(const vec4 &c0, const vec4 &c1, const vec4 &c2, const vec4 &c3)
	{
		setColumn(0, c0);
		setColumn(1, c1);
		setColumn(2, c2);
		setColumn(3, c3);
		UNIGINE_ASSERT_ALIGNED16(this);
	}

	/// <summary>Sets the element in the specified row and column using the specified value.</summary>
	UNIGINE_INLINE void set(int row, int column, float v)
	{
		assert((unsigned int)row < 4 && "mat4::set(): bad row");
		assert((unsigned int)column < 4 && "mat4::set(): bad column");
		mat[column * 4 + row] = v;
	}
	/// <summary>Sets the values of the matrix elements using the specified 2x2 matrix (starting from the upper-left corner, other elements are set to zeros, with the rest of the elements of the main diagonal set to 1).</summary>
	UNIGINE_INLINE void set(const mat2 &m)
	{
		m00 = m.m00;
		m01 = m.m01;
		m02 = 0.0f;
		m03 = 0.0f;
		m10 = m.m10;
		m11 = m.m11;
		m12 = 0.0f;
		m13 = 0.0f;
		m20 = 0.0f;
		m21 = 0.0f;
		m22 = 1.0f;
		m23 = 0.0f;
		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 1.0f;
	}
	/// <summary>Sets the values of the matrix elements using the specified 3x3 matrix (starting from the upper-left corner, other elements are set to zeros, with the last element of the main diagonal set to 1).</summary>
	UNIGINE_INLINE void set(const mat3 &m)
	{
		m00 = m.m00;
		m01 = m.m01;
		m02 = m.m02;
		m03 = 0.0f;
		m10 = m.m10;
		m11 = m.m11;
		m12 = m.m12;
		m13 = 0.0f;
		m20 = m.m20;
		m21 = m.m21;
		m22 = m.m22;
		m23 = 0.0f;
		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 1.0f;
	}
	/// <summary>Sets the values of the matrix elements using the specified 4x4 matrix.</summary>
	UNIGINE_INLINE void set(const mat4 &m)
	{
		sse.v0 = m.sse.v0;
		sse.v1 = m.sse.v1;
		sse.v2 = m.sse.v2;
		sse.v3 = m.sse.v3;
	}
	/// <summary>Sets the values of the matrix elements using the specified matrix.</summary>
	UNIGINE_INLINE void set(const dmat4 &m);
	/// <summary>Sets new matrix values using a given source quaternion.</summary>
	UNIGINE_INLINE void set(const quat &q);
	/// <summary>Sets the values of the matrix elements using the specified array of 16 elements.</summary>
	/// <param name="transposed">Flag that defines if the matrix should be transposed.</param>
	UNIGINE_INLINE void set(const mat4x4_values &m, int transposed = 0)
	{
		if (transposed)
		{
			m00 = m[0];
			m01 = m[1];
			m02 = m[2];
			m03 = m[3];
			m10 = m[4];
			m11 = m[5];
			m12 = m[6];
			m13 = m[7];
			m20 = m[8];
			m21 = m[9];
			m22 = m[10];
			m23 = m[11];
			m30 = m[12];
			m31 = m[13];
			m32 = m[14];
			m33 = m[15];
		} else
		{
			m00 = m[0];
			m01 = m[4];
			m02 = m[8];
			m03 = m[12];
			m10 = m[1];
			m11 = m[5];
			m12 = m[9];
			m13 = m[13];
			m20 = m[2];
			m21 = m[6];
			m22 = m[10];
			m23 = m[14];
			m30 = m[3];
			m31 = m[7];
			m32 = m[11];
			m33 = m[15];
		}
	}
	/// <summary>Sets the values of the matrix elements using the specified array of 16 double elements (double->float conversion is performed for each element).</summary>
	/// <param name="transposed">Flag that defines if the matrix should be transposed.</param>
	UNIGINE_INLINE void set(const dmat4x4_values &m, int transpose = 0)
	{
		if (transpose)
		{
			m00 = toFloat(m[0]);
			m01 = toFloat(m[1]);
			m02 = toFloat(m[2]);
			m03 = toFloat(m[3]);
			m10 = toFloat(m[4]);
			m11 = toFloat(m[5]);
			m12 = toFloat(m[6]);
			m13 = toFloat(m[7]);
			m20 = toFloat(m[8]);
			m21 = toFloat(m[9]);
			m22 = toFloat(m[10]);
			m23 = toFloat(m[11]);
			m30 = toFloat(m[12]);
			m31 = toFloat(m[13]);
			m32 = toFloat(m[14]);
			m33 = toFloat(m[15]);
		} else
		{
			m00 = toFloat(m[0]);
			m01 = toFloat(m[4]);
			m02 = toFloat(m[8]);
			m03 = toFloat(m[12]);
			m10 = toFloat(m[1]);
			m11 = toFloat(m[5]);
			m12 = toFloat(m[9]);
			m13 = toFloat(m[13]);
			m20 = toFloat(m[2]);
			m21 = toFloat(m[6]);
			m22 = toFloat(m[10]);
			m23 = toFloat(m[14]);
			m30 = toFloat(m[3]);
			m31 = toFloat(m[7]);
			m32 = toFloat(m[11]);
			m33 = toFloat(m[15]);
		}
	}
	/// <summary>Sets the values of the matrix elements using a combination of the specified 3x3 matrix(typically representing rotation and scaling), with a 3D vector (representing translation).</summary>
	/// <param name="m">Matrix representing rotation and scaling.</param>
	/// <param name="v">Vector representing translation.</param>
	UNIGINE_INLINE void set(const mat3 &m, const vec3 &v)
	{
		m00 = m.m00;
		m01 = m.m01;
		m02 = m.m02;
		m03 = v.x;
		m10 = m.m10;
		m11 = m.m11;
		m12 = m.m12;
		m13 = v.y;
		m20 = m.m20;
		m21 = m.m21;
		m22 = m.m22;
		m23 = v.z;
		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 1.0f;
	}
	UNIGINE_INLINE void set(const quat &q, const vec3 &v);

	/// <summary>Returns the values of the matrix elements as an array of 16 elements.</summary>
	/// <param name="transposed">Flag that defines if the matrix should be transposed.</param>
	UNIGINE_INLINE void get(mat4x4_values &m, int transpose = 0) const
	{
		if (transpose)
		{
			m[0] = m00;
			m[1] = m01;
			m[2] = m02;
			m[3] = m03;
			m[4] = m10;
			m[5] = m11;
			m[6] = m12;
			m[7] = m13;
			m[8] = m20;
			m[9] = m21;
			m[10] = m22;
			m[11] = m23;
			m[12] = m30;
			m[13] = m31;
			m[14] = m32;
			m[15] = m33;
		} else
		{
			m[0] = m00;
			m[4] = m01;
			m[8] = m02;
			m[12] = m03;
			m[1] = m10;
			m[5] = m11;
			m[9] = m12;
			m[13] = m13;
			m[2] = m20;
			m[6] = m21;
			m[10] = m22;
			m[14] = m23;
			m[3] = m30;
			m[7] = m31;
			m[11] = m32;
			m[15] = m33;
		}
	}
	/// <summary>Returns the values of the matrix elements as an array of 16 elements.</summary>
	UNIGINE_INLINE mat4x4_values &get() { return mat; }
	/// <summary>Returns the values of the matrix elements as an array of 16 elements.</summary>
	UNIGINE_INLINE const mat4x4_values &get() const { return mat; }
	/// <summary>Returns the value of an element at the specified row and column (zero-based).</summary>
	UNIGINE_INLINE float &get(int row, int column)
	{
		assert((unsigned int)row < 4 && "mat4::get(): bad row");
		assert((unsigned int)column < 4 && "mat4::get(): bad column");
		return mat[column * 4 + row];
	}
	/// <summary>Returns the value of an element at the specified row and column (zero-based).</summary>
	UNIGINE_INLINE float get(int row, int column) const
	{
		assert((unsigned int)row < 4 && "mat4::get(): bad row");
		assert((unsigned int)column < 4 && "mat4::get(): bad column");
		return mat[column * 4 + row];
	}

	/// <summary>Performs type conversion to float *.</summary>
	UNIGINE_INLINE operator float *() { return mat; }
	/// <summary>Performs type conversion to const float *.</summary>
	UNIGINE_INLINE operator const float *() const { return mat; }
	/// <summary>Performs type conversion to void *.</summary>
	UNIGINE_INLINE operator void *() { return mat; }
	/// <summary>Performs type conversion to const void *.</summary>
	UNIGINE_INLINE operator const void *() const { return mat; }

	/// <summary>Performs array access to the matrix item reference using given item index.</summary>
	UNIGINE_INLINE float &operator[](int i)
	{
		assert((unsigned int)i < 16 && "mat4::operator[](): bad index");
		return mat[i];
	}
	/// <summary>Performs array access to the matrix item using given item index.</summary>
	UNIGINE_INLINE float operator[](int i) const
	{
		assert((unsigned int)i < 16 && "mat4::operator[](): bad index");
		return mat[i];
	}

	/// <summary>Performs matrix assignment. Destination matrix = Source matrix.</summary>
	UNIGINE_INLINE mat4 &operator=(const mat4 &m)
	{
		set(m);
		return *this;
	}
	/// <summary>Performs matrix negation.</summary>
	UNIGINE_INLINE mat4 operator-() const
	{
		mat4 ret;
		ret.m00 = -m00;
		ret.m01 = -m01;
		ret.m02 = -m02;
		ret.m03 = -m03;
		ret.m10 = -m10;
		ret.m11 = -m11;
		ret.m12 = -m12;
		ret.m13 = -m13;
		ret.m20 = -m20;
		ret.m21 = -m21;
		ret.m22 = -m22;
		ret.m23 = -m23;
		ret.m30 = -m30;
		ret.m31 = -m31;
		ret.m32 = -m32;
		ret.m33 = -m33;
		return ret;
	}

	/// <summary>Performs scalar multiplication.</summary>
	UNIGINE_INLINE mat4 &operator*=(float v);
	/// <summary>Performs matrix multiplication.</summary>
	UNIGINE_INLINE mat4 &operator*=(const mat4 &m);
	/// <summary>Performs matrix addition.</summary>
	UNIGINE_INLINE mat4 &operator+=(const mat4 &m);
	/// <summary>Performs matrix subtraction.</summary>
	UNIGINE_INLINE mat4 &operator-=(const mat4 &m);

	/// <summary>Sets the values of the specified row using the specified 4D vector.</summary>
	UNIGINE_INLINE void setRow(int row, const vec4 &v)
	{
		assert(row < 4 && row >= 0 && "mat4::setRow(): bad row");
		mat[row + 0] = v.x;
		mat[row + 4] = v.y;
		mat[row + 8] = v.z;
		mat[row + 12] = v.w;
	}
	/// <summary>Sets the first three values of the specified row using the specified 3D vector.</summary>
	UNIGINE_INLINE void setRow3(int row, const vec3 &v)
	{
		assert(row < 4 && row >= 0 && "mat4::setRow3(): bad row");
		mat[row + 0] = v.x;
		mat[row + 4] = v.y;
		mat[row + 8] = v.z;
	}
	/// <summary>Returns the values of the specified row as a 4D vector.</summary>
	UNIGINE_INLINE vec4 getRow(int row) const
	{
		assert(row < 4 && row >= 0 && "mat4::getRow(): bad row");
		return vec4(mat[row + 0], mat[row + 4], mat[row + 8], mat[row + 12]);
	}
	/// <summary>Returns the first three values of the specified row as a 3D vector.</summary>
	UNIGINE_INLINE vec3 getRow3(int row) const
	{
		assert(row < 4 && row >= 0 && "mat4::getRow3(): bad row");
		return vec3(mat[row + 0], mat[row + 4], mat[row + 8]);
	}

	/// <summary>Sets the values of the specified column using the specified 4D vector.</summary>
	UNIGINE_INLINE void setColumn(int column, const vec4 &v)
	{
		assert(column < 4 && column >= 0 && "mat4::setColumn(): bad column");
		column *= 4;
		mat[column + 0] = v.x;
		mat[column + 1] = v.y;
		mat[column + 2] = v.z;
		mat[column + 3] = v.w;
	}
	/// <summary>Sets the first three values of the specified column using the specified 3D vector.</summary>
	UNIGINE_INLINE void setColumn3(int column, const vec3 &v)
	{
		assert(column < 4 && column >= 0 && "mat4::setColumn3(): bad column");
		column *= 4;
		mat[column + 0] = v.x;
		mat[column + 1] = v.y;
		mat[column + 2] = v.z;
	}
	/// <summary>Returns the values of the specified column as a 4D vector.</summary>
	UNIGINE_INLINE vec4 getColumn(int column) const
	{
		assert(column < 4 && column >= 0 && "mat4::getColumn(): bad column");
		return vec4(mat + column * 4);
	}
	/// <summary>Returns the first three values of the specified column as a 3D vector.</summary>
	UNIGINE_INLINE vec3 getColumn3(int column) const
	{
		assert(column < 4 && column >= 0 && "mat4::getColumn3(): bad column");
		return vec3(mat + column * 4);
	}

	/// <summary>Returns the X axis for the matrix (first column) as a normalized 3D vector.</summary>
	UNIGINE_INLINE vec3 getAxisX() const { return getColumn3(0).normalize(); }
	/// <summary>Returns the Y axis for the matrix (second column) as a normalized 3D vector.</summary>
	UNIGINE_INLINE vec3 getAxisY() const { return getColumn3(1).normalize(); }
	/// <summary>Returns the Z axis for the matrix (third column) as a normalized 3D vector.</summary>
	UNIGINE_INLINE vec3 getAxisZ() const { return getColumn3(2).normalize(); }

	/// <summary>Sets the elements of the main diagonal of the matrix using the specified 4D vector.</summary>
	UNIGINE_INLINE void setDiagonal(const vec4 &v)
	{
		m00 = v.x;
		m01 = 0.0f;
		m02 = 0.0f;
		m03 = 0.0f;
		m10 = 0.0f;
		m11 = v.y;
		m12 = 0.0f;
		m13 = 0.0f;
		m20 = 0.0f;
		m21 = 0.0f;
		m22 = v.z;
		m23 = 0.0f;
		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = v.w;
	}
	/// <summary>Returns the elements of the main diagonal of the matrix as a 4D vector.</summary>
	UNIGINE_INLINE vec4 getDiagonal() const { return vec4(m00, m11, m22, m33); }

	/// <summary>Sets all values of the matrix elements equal to zero.</summary>
	UNIGINE_INLINE void setZero()
	{
		m00 = 0.0f;
		m01 = 0.0f;
		m02 = 0.0f;
		m03 = 0.0f;
		m10 = 0.0f;
		m11 = 0.0f;
		m12 = 0.0f;
		m13 = 0.0f;
		m20 = 0.0f;
		m21 = 0.0f;
		m22 = 0.0f;
		m23 = 0.0f;
		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 0.0f;
	}
	/// <summary>Initializes the matrix as an identity matrix all values of the matrix elements equal to zero, except for the main diagonal elements set to 1.</summary>
	UNIGINE_INLINE void setIdentity()
	{
		m00 = 1.0f;
		m01 = 0.0f;
		m02 = 0.0f;
		m03 = 0.0f;
		m10 = 0.0f;
		m11 = 1.0f;
		m12 = 0.0f;
		m13 = 0.0f;
		m20 = 0.0f;
		m21 = 0.0f;
		m22 = 1.0f;
		m23 = 0.0f;
		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 1.0f;
	}

	/// <summary>Sets the values of the translation component of the matrix (last column) using the specified 3D vector, the fourth element is set to 1.</summary>
	UNIGINE_INLINE void setTranslate(const vec3 &v)
	{
		m00 = 1.0f;
		m01 = 0.0f;
		m02 = 0.0f;
		m03 = v.x;
		m10 = 0.0f;
		m11 = 1.0f;
		m12 = 0.0f;
		m13 = v.y;
		m20 = 0.0f;
		m21 = 0.0f;
		m22 = 1.0f;
		m23 = v.z;
		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 1.0f;
	}
	/// <summary>Returns the values of the translation component of the matrix (last column) as a 3D vector.</summary>
	UNIGINE_INLINE vec3 getTranslate() const { return vec3(m03, m13, m23); }

	/// <summary>Sets the values of the rotation component of the matrix using the specified rotation axis and angle (in degrees).</summary>
	UNIGINE_INLINE void setRotate(const vec3 &axis, float angle)
	{
		float s, c;
		Math::sincos(angle * Consts::DEG2RAD, s, c);
		vec3 v = normalize(axis);
		float xx = v.x * v.x;
		float yy = v.y * v.y;
		float zz = v.z * v.z;
		float xy = v.x * v.y;
		float yz = v.y * v.z;
		float zx = v.z * v.x;
		float xs = v.x * s;
		float ys = v.y * s;
		float zs = v.z * s;

		m00 = (1.0f - c) * xx + c;
		m01 = (1.0f - c) * xy - zs;
		m02 = (1.0f - c) * zx + ys;
		m03 = 0.0f;

		m10 = (1.0f - c) * xy + zs;
		m11 = (1.0f - c) * yy + c;
		m12 = (1.0f - c) * yz - xs;
		m13 = 0.0f;

		m20 = (1.0f - c) * zx - ys;
		m21 = (1.0f - c) * yz + xs;
		m22 = (1.0f - c) * zz + c;
		m23 = 0.0f;

		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 1.0f;
	}
	/// <summary>Returns the values of the rotation component of the matrix as a quaternion.</summary>
	UNIGINE_INLINE quat getRotate() const;

	/// <summary>Sets the values of the rotation component of the matrix using the specified angle of rotation around the X axis.</summary>
	/// <param name="angle">Angle of rotation around the X axis (in degrees).</param>
	UNIGINE_INLINE void setRotateX(float angle)
	{
		float s, c;
		Math::sincos(angle * Consts::DEG2RAD, s, c);

		m00 = 1.0f;
		m01 = 0.0f;
		m02 = 0.0f;
		m03 = 0.0f;

		m10 = 0.0f;
		m11 = c;
		m12 = -s;
		m13 = 0.0f;

		m20 = 0.0f;
		m21 = s;
		m22 = c;
		m23 = 0.0f;

		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 1.0f;
	}
	/// <summary>Sets the values of the rotation component of the matrix using the specified angle of rotation around the Y axis.</summary>
	/// <param name="angle">Angle of rotation around the Y axis (in degrees).</param>
	UNIGINE_INLINE void setRotateY(float angle)
	{
		float s, c;
		Math::sincos(angle * Consts::DEG2RAD, s, c);

		m00 = c;
		m01 = 0.0f;
		m02 = s;
		m03 = 0.0f;

		m10 = 0.0f;
		m11 = 1.0f;
		m12 = 0.0f;
		m13 = 0.0f;

		m20 = -s;
		m21 = 0.0f;
		m22 = c;
		m23 = 0.0f;

		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 1.0f;
	}
	/// <summary>Sets the values of the rotation component of the matrix using the specified angle of rotation around the Z axis.</summary>
	/// <param name="angle">Angle of rotation around the Z axis (in degrees).</param>
	UNIGINE_INLINE void setRotateZ(float angle)
	{
		float s, c;
		Math::sincos(angle * Consts::DEG2RAD, s, c);

		m00 = c;
		m01 = -s;
		m02 = 0.0f;
		m03 = 0.0f;

		m10 = s;
		m11 = c;
		m12 = 0.0f;
		m13 = 0.0f;

		m20 = 0.0f;
		m21 = 0.0f;
		m22 = 1.0f;
		m23 = 0.0f;

		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 1.0f;
	}

	/// <summary>Sets the values of the scaling component of the matrix using the specified 3D vector.</summary>
	/// <param name="v">Vector defining the scaling factors for X, Y, and Z axes.</param>
	UNIGINE_INLINE void setScale(const vec3 &v)
	{
		m00 = v.x;
		m01 = 0.0f;
		m02 = 0.0f;
		m03 = 0.0f;

		m10 = 0.0f;
		m11 = v.y;
		m12 = 0.0f;
		m13 = 0.0f;

		m20 = 0.0f;
		m21 = 0.0f;
		m22 = v.z;
		m23 = 0.0f;

		m30 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 1.0f;
	}
	/// <summary>Returns the values of the scaling component of the matrix as a 3D vector that contains scaling factors for X, Y, and Z axes.</summary>
	UNIGINE_INLINE vec3 getScale() const
	{
		mat3 rotate, rotation = mat3(*this);
		orthonormalize(rotate, rotation);
		float sx = rotate.m00 * rotation.m00 + rotate.m10 * rotation.m10 + rotate.m20 * rotation.m20;
		float sy = rotate.m01 * rotation.m01 + rotate.m11 * rotation.m11 + rotate.m21 * rotation.m21;
		float sz = rotate.m02 * rotation.m02 + rotate.m12 * rotation.m12 + rotate.m22 * rotation.m22;
		return vec3(sx, sy, sz);
	}

	/// <summary>Returns the trace of the matrix (sum of the main diagonal elements).</summary>
	UNIGINE_INLINE float trace() const { return m00 + m11 + m22 + m33; }
	/// <summary>Returns the determinant of the matrix.</summary>
	UNIGINE_INLINE float determinant() const
	{
		float det = m00 * (m11 * (m22 * m33 - m23 * m32) - m12 * (m21 * m33 - m23 * m31) + m13 * (m21 * m32 - m22 * m31));
		det -= m01 * (m10 * (m22 * m33 - m23 * m32) - m12 * (m20 * m33 - m23 * m30) + m13 * (m20 * m32 - m22 * m30));
		det += m02 * (m10 * (m21 * m33 - m23 * m31) - m11 * (m20 * m33 - m23 * m30) + m13 * (m20 * m31 - m21 * m30));
		det -= m03 * (m10 * (m21 * m32 - m22 * m31) - m11 * (m20 * m32 - m22 * m30) + m12 * (m20 * m31 - m21 * m30));
		return det;
	}
	/// <summary>Returns the determinant of the upper-left 3x3 part of the matrix.</summary>
	UNIGINE_INLINE float determinant3() const
	{
		float det = m00 * (m11 * m22 - m12 * m21);
		det -= m01 * (m10 * m22 - m12 * m20);
		det += m02 * (m10 * m21 - m11 * m20);
		return det;
	}

	#ifdef USE_SSE
		struct sse_data
		{
			__m128 v0;
			__m128 v1;
			__m128 v2;
			__m128 v3;
		};
	#endif

	union
	{
		struct
		{
			float m00, m10, m20, m30;
			float m01, m11, m21, m31;
			float m02, m12, m22, m32;
			float m03, m13, m23, m33;
		};
		float mat[16];

		#ifdef USE_SSE
			sse_data sse; // DO NOT TOUCH UNLESS ABSOLUTELY SURE
		#endif
	};
};

/// <summary>4x4 matrix filled with zeros.</summary>
constexpr mat4 mat4_zero(0.0f, ConstexprTag{});
/// <summary>4x4 matrix filled with ones.</summary>
constexpr mat4 mat4_one(1.0f, ConstexprTag{});
/// <summary>4x4 identity matrix.</summary>
constexpr mat4 mat4_identity(1.0f, 0.0f, 0.0f, 0.0f,
							 0.0f, 1.0f, 0.0f, 0.0f,
							 0.0f, 0.0f, 1.0f, 0.0f,
							 0.0f, 0.0f, 0.0f, 1.0f, ConstexprTag{});

/// <summary>Returns the matrix after applying the translation specified as a 3D vector.</summary>
UNIGINE_INLINE mat4 translate(const vec3 &v)
{
	mat4 ret;
	ret.setTranslate(v);
	return ret;
}
/// <summary>Returns the matrix after applying the translation specified as a 4D vector.</summary>
UNIGINE_INLINE mat4 translate(const vec4 &v)
{
	mat4 ret;
	ret.setTranslate(vec3(v));
	return ret;
}
/// <summary>Returns the matrix after applying the translation specified as a 2D vector.</summary>
UNIGINE_INLINE mat4 translate(const vec2 &v)
{
	mat4 ret;
	ret.setTranslate(vec3(v));
	return ret;
}
/// <summary>Returns the matrix after applying the translation specified as offsets along the X, Y, and Z axis respectively.</summary>
UNIGINE_INLINE mat4 translate(float x, float y, float z)
{
	mat4 ret;
	ret.setTranslate(vec3(x, y, z));
	return ret;
}

/// <summary>Returns the matrix after applying the rotation around the specified axis at an angle given in degrees.</summary>
/// <param name="axis">Axis around which rotation is performed.</param>
/// <param name="angle">Angle of rotation (in degrees).</param>
UNIGINE_INLINE mat4 rotate(const vec3 &axis, float angle)
{
	mat4 ret;
	ret.setRotate(axis, angle);
	return ret;
}
/// <summary>Returns the transformation matrix for rotation around the specified axis at an angle given in degrees.</summary>
/// <param name="x">X coordinate of the rotation axis.</param>
/// <param name="y">Y coordinate of the rotation axis.</param>
/// <param name="z">Z coordinate of the rotation axis.</param>
/// <param name="angle">Angle of rotation (in degrees).</param>
UNIGINE_INLINE mat4 rotate(float x, float y, float z, float angle)
{
	return rotate(vec3(x, y, z), angle);
}

/// <summary>Returns the matrix after applying the rotation around the X axis at the specified angle.</summary>
/// <param name="angle">Angle of rotation (in degrees).</param>
UNIGINE_INLINE mat4 rotateX(float angle)
{
	mat4 ret;
	ret.setRotateX(angle);
	return ret;
}
/// <summary>Returns the matrix after applying the rotation around the Y axis at the specified angle.</summary>
/// <param name="angle">Angle of rotation (in degrees).</param>
UNIGINE_INLINE mat4 rotateY(float angle)
{
	mat4 ret;
	ret.setRotateY(angle);
	return ret;
}
/// <summary>Returns the matrix after applying the rotation around the Z axis at the specified angle.</summary>
/// <param name="angle">Angle of rotation (in degrees).</param>
UNIGINE_INLINE mat4 rotateZ(float angle)
{
	mat4 ret;
	ret.setRotateZ(angle);
	return ret;
}

/// <summary>Returns the matrix after applying scaling using the factors specified as a 3D vector.</summary>
/// <param name="v">3D vector representing scale factors for X, Y, and Z axis.</param>
UNIGINE_INLINE mat4 scale(const vec3 &v)
{
	mat4 ret;
	ret.setScale(v);
	return ret;
}
/// <summary>Returns the matrix after applying scaling using the factors specified for X, Y, and Z axis respectively.</summary>
UNIGINE_INLINE mat4 scale(float x, float y, float z)
{
	return scale(vec3(x, y, z));
}
/// <summary>Returns the matrix after applying uniform scaling using the specified factor.</summary>
/// <param name="x">Scale factor for X, Y, and Z axis.</param>
UNIGINE_INLINE mat4 scale(float x)
{
	return scale(vec3(x, x, x));
}

/// <summary>Returns the trace of the specified matrix (sum of the main diagonal elements).</summary>
UNIGINE_INLINE float trace(const mat4 &m) { return m.trace(); }
/// <summary>Returns the determinant of the specified matrix.</summary>
UNIGINE_INLINE float determinant(const mat4 &m) { return m.determinant(); }
/// <summary>Returns the determinant of the upper-left 3x3 part of the specified matrix.</summary>
UNIGINE_INLINE float determinant3(const mat4 &m) { return m.determinant3(); }

/// <summary>Returns a value indicating whether all corresponding elements of the two given matrices are equal (element-wise conparison).</summary>
UNIGINE_INLINE int compare(const mat4 &m0, const mat4 &m1)
{
	return (compare(m0.m00, m1.m00) && compare(m0.m10, m1.m10) && compare(m0.m20, m1.m20) && compare(m0.m30, m1.m30) &&
			compare(m0.m01, m1.m01) && compare(m0.m11, m1.m11) && compare(m0.m21, m1.m21) && compare(m0.m31, m1.m31) &&
			compare(m0.m02, m1.m02) && compare(m0.m12, m1.m12) && compare(m0.m22, m1.m22) && compare(m0.m32, m1.m32) &&
			compare(m0.m03, m1.m03) && compare(m0.m13, m1.m13) && compare(m0.m23, m1.m23) && compare(m0.m33, m1.m33));
}
/// <summary>Returns a value indicating whether all corresponding elements of the two given matrices can be considered equal within a given tolerance (epsilon). When dealing with floating-point numbers, a threshold for "closeness" is used to determine if two values can be considered equal due to the nature of floating-point arithmetic.</summary>
UNIGINE_INLINE int compare(const mat4 &m0, const mat4 &m1, float epsilon)
{
	return (compare(m0.m00, m1.m00, epsilon) && compare(m0.m10, m1.m10, epsilon) && compare(m0.m20, m1.m20, epsilon) && compare(m0.m30, m1.m30, epsilon) &&
			compare(m0.m01, m1.m01, epsilon) && compare(m0.m11, m1.m11, epsilon) && compare(m0.m21, m1.m21, epsilon) && compare(m0.m31, m1.m31, epsilon) &&
			compare(m0.m02, m1.m02, epsilon) && compare(m0.m12, m1.m12, epsilon) && compare(m0.m22, m1.m22, epsilon) && compare(m0.m32, m1.m32, epsilon) &&
			compare(m0.m03, m1.m03, epsilon) && compare(m0.m13, m1.m13, epsilon) && compare(m0.m23, m1.m23, epsilon) && compare(m0.m33, m1.m33, epsilon));
}
/// <summary>Matrix equal comparison.</summary>
UNIGINE_INLINE int operator==(const mat4 &m0, const mat4 &m1) { return compare(m0, m1); }
/// <summary>Matrix not equal comparison.</summary>
UNIGINE_INLINE int operator!=(const mat4 &m0, const mat4 &m1) { return !compare(m0, m1); }

/// <summary>Returns the result of element-wise multiplication of a 4x4 matrix by the specified float value.</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Float multiplier.</param>
UNIGINE_INLINE mat4 &mul(mat4 &ret, const mat4 &m, float v)
{
	#ifdef USE_SSE
		__m128 temp = _mm_set1_ps(v);
		ret.sse.v0 = _mm_mul_ps(m.sse.v0, temp);
		ret.sse.v1 = _mm_mul_ps(m.sse.v1, temp);
		ret.sse.v2 = _mm_mul_ps(m.sse.v2, temp);
		ret.sse.v3 = _mm_mul_ps(m.sse.v3, temp);
	#else
		ret.m00 = m.m00 * v;
		ret.m01 = m.m01 * v;
		ret.m02 = m.m02 * v;
		ret.m03 = m.m03 * v;
		ret.m10 = m.m10 * v;
		ret.m11 = m.m11 * v;
		ret.m12 = m.m12 * v;
		ret.m13 = m.m13 * v;
		ret.m20 = m.m20 * v;
		ret.m21 = m.m21 * v;
		ret.m22 = m.m22 * v;
		ret.m23 = m.m23 * v;
		ret.m30 = m.m30 * v;
		ret.m31 = m.m31 * v;
		ret.m32 = m.m32 * v;
		ret.m33 = m.m33 * v;
	#endif
	return ret;
}
/// <summary>Returns the result of matrix multiplication.</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m0">Matrix to be multiplied.</param>
/// <param name="m1">Multiplier matrix.</param>
UNIGINE_INLINE mat4 &mul(mat4 &ret, const mat4 &m0, const mat4 &m1)
{
	#ifdef USE_SSE
		__m128 m0_col0 = m0.sse.v0;
		__m128 m0_col1 = m0.sse.v1;
		__m128 m0_col2 = m0.sse.v2;
		__m128 m0_col3 = m0.sse.v3;

		__m128 m1_col0 = m1.sse.v0;
		__m128 m1_col1 = m1.sse.v1;
		__m128 m1_col2 = m1.sse.v2;
		__m128 m1_col3 = m1.sse.v3;

		__m128 res_0 = _mm_mul_ps(m0_col0, _MM_SWIZZLE(m1_col0, X, X, X, X));
		__m128 res_1 = _mm_mul_ps(m0_col1, _MM_SWIZZLE(m1_col0, Y, Y, Y, Y));
		__m128 res_2 = _mm_mul_ps(m0_col2, _MM_SWIZZLE(m1_col0, Z, Z, Z, Z));
		__m128 res_3 = _mm_mul_ps(m0_col3, _MM_SWIZZLE(m1_col0, W, W, W, W));
		ret.sse.v0 = _mm_add_ps(_mm_add_ps(res_0, res_1), _mm_add_ps(res_2, res_3));
		res_0 = _mm_mul_ps(m0_col0, _MM_SWIZZLE(m1_col1, X, X, X, X));
		res_1 = _mm_mul_ps(m0_col1, _MM_SWIZZLE(m1_col1, Y, Y, Y, Y));
		res_2 = _mm_mul_ps(m0_col2, _MM_SWIZZLE(m1_col1, Z, Z, Z, Z));
		res_3 = _mm_mul_ps(m0_col3, _MM_SWIZZLE(m1_col1, W, W, W, W));
		ret.sse.v1 = _mm_add_ps(_mm_add_ps(res_0, res_1), _mm_add_ps(res_2, res_3));
		res_0 = _mm_mul_ps(m0_col0, _MM_SWIZZLE(m1_col2, X, X, X, X));
		res_1 = _mm_mul_ps(m0_col1, _MM_SWIZZLE(m1_col2, Y, Y, Y, Y));
		res_2 = _mm_mul_ps(m0_col2, _MM_SWIZZLE(m1_col2, Z, Z, Z, Z));
		res_3 = _mm_mul_ps(m0_col3, _MM_SWIZZLE(m1_col2, W, W, W, W));
		ret.sse.v2 = _mm_add_ps(_mm_add_ps(res_0, res_1), _mm_add_ps(res_2, res_3));
		res_0 = _mm_mul_ps(m0_col0, _MM_SWIZZLE(m1_col3, X, X, X, X));
		res_1 = _mm_mul_ps(m0_col1, _MM_SWIZZLE(m1_col3, Y, Y, Y, Y));
		res_2 = _mm_mul_ps(m0_col2, _MM_SWIZZLE(m1_col3, Z, Z, Z, Z));
		res_3 = _mm_mul_ps(m0_col3, _MM_SWIZZLE(m1_col3, W, W, W, W));
		ret.sse.v3 = _mm_add_ps(_mm_add_ps(res_0, res_1), _mm_add_ps(res_2, res_3));
	#else
		ret.m00 = m0.m00 * m1.m00 + m0.m01 * m1.m10 + m0.m02 * m1.m20 + m0.m03 * m1.m30;
		ret.m10 = m0.m10 * m1.m00 + m0.m11 * m1.m10 + m0.m12 * m1.m20 + m0.m13 * m1.m30;
		ret.m20 = m0.m20 * m1.m00 + m0.m21 * m1.m10 + m0.m22 * m1.m20 + m0.m23 * m1.m30;
		ret.m30 = m0.m30 * m1.m00 + m0.m31 * m1.m10 + m0.m32 * m1.m20 + m0.m33 * m1.m30;
		ret.m01 = m0.m00 * m1.m01 + m0.m01 * m1.m11 + m0.m02 * m1.m21 + m0.m03 * m1.m31;
		ret.m11 = m0.m10 * m1.m01 + m0.m11 * m1.m11 + m0.m12 * m1.m21 + m0.m13 * m1.m31;
		ret.m21 = m0.m20 * m1.m01 + m0.m21 * m1.m11 + m0.m22 * m1.m21 + m0.m23 * m1.m31;
		ret.m31 = m0.m30 * m1.m01 + m0.m31 * m1.m11 + m0.m32 * m1.m21 + m0.m33 * m1.m31;
		ret.m02 = m0.m00 * m1.m02 + m0.m01 * m1.m12 + m0.m02 * m1.m22 + m0.m03 * m1.m32;
		ret.m12 = m0.m10 * m1.m02 + m0.m11 * m1.m12 + m0.m12 * m1.m22 + m0.m13 * m1.m32;
		ret.m22 = m0.m20 * m1.m02 + m0.m21 * m1.m12 + m0.m22 * m1.m22 + m0.m23 * m1.m32;
		ret.m32 = m0.m30 * m1.m02 + m0.m31 * m1.m12 + m0.m32 * m1.m22 + m0.m33 * m1.m32;
		ret.m03 = m0.m00 * m1.m03 + m0.m01 * m1.m13 + m0.m02 * m1.m23 + m0.m03 * m1.m33;
		ret.m13 = m0.m10 * m1.m03 + m0.m11 * m1.m13 + m0.m12 * m1.m23 + m0.m13 * m1.m33;
		ret.m23 = m0.m20 * m1.m03 + m0.m21 * m1.m13 + m0.m22 * m1.m23 + m0.m23 * m1.m33;
		ret.m33 = m0.m30 * m1.m03 + m0.m31 * m1.m13 + m0.m32 * m1.m23 + m0.m33 * m1.m33;
	#endif
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 2D vector and a 4x4 matrix. This operation assumes that 2D vector is represented in homogeneous coordinates, so it treats the vector as if it were a 3D point (z=0 and w=1).</summary>
/// <param name="ret">Reference to a 2D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE vec2 &mul(vec2 &ret, const mat4 &m, const vec2 &v)
{
	ret.x = m.m00 * v.x + m.m01 * v.y + m.m03;
	ret.y = m.m10 * v.x + m.m11 * v.y + m.m13;
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 2D vector and a 4x4 matrix. This operation assumes that 2D vector is represented in homogeneous coordinates, so it treats the vector as if it were a 3D point (z=0 and w=1).</summary>
/// <param name="ret">Reference to a 2D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE vec2 &mul(vec2 &ret, const vec2 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y + m.m30;
	ret.y = m.m01 * v.x + m.m11 * v.y + m.m31;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3D vector and a 4x4 matrix. This operation assumes w=1 for the vector.</summary>
/// <param name="ret">Reference to a 3D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE vec3 &mul(vec3 &ret, const mat4 &m, const vec3 &v)
{
	#ifdef USE_SSE
		__m128 vec = v.vec;
		__m128 res_0 = _mm_mul_ps(m.sse.v0, _MM_SWIZZLE(vec, X, X, X, X));
		__m128 res_1 = _mm_mul_ps(m.sse.v1, _MM_SWIZZLE(vec, Y, Y, Y, Y));
		__m128 res_2 = _mm_mul_ps(m.sse.v2, _MM_SWIZZLE(vec, Z, Z, Z, Z));
		ret = _mm_add_ps(_mm_add_ps(res_0, res_1), _mm_add_ps(res_2, m.sse.v3));
	#else
		float x = v.x;
		float y = v.y;
		float z = v.z;
		ret.x = m.m00 * x + m.m01 * y + m.m02 * z + m.m03;
		ret.y = m.m10 * x + m.m11 * y + m.m12 * z + m.m13;
		ret.z = m.m20 * x + m.m21 * y + m.m22 * z + m.m23;
	#endif
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 3D vector and a 4x4 matrix. This operation assumes w=1 for the vector.</summary>
/// <param name="ret">Reference to a 3D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE vec3 &mul(vec3 &ret, const vec3 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y + m.m20 * v.z + m.m30;
	ret.y = m.m01 * v.x + m.m11 * v.y + m.m21 * v.z + m.m31;
	ret.z = m.m02 * v.x + m.m12 * v.y + m.m22 * v.z + m.m32;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 4D vector and a 4x4 matrix.</summary>
/// <param name="ret">Reference to a 4D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE vec4 &mul(vec4 &ret, const mat4 &m, const vec4 &v)
{
	#ifdef USE_SSE
		const __m128 vec = v.vec;
		const __m128 res_0 = _mm_mul_ps(m.sse.v0, _MM_SWIZZLE(vec, X, X, X, X));
		const __m128 res_1 = _mm_mul_ps(m.sse.v1, _MM_SWIZZLE(vec, Y, Y, Y, Y));
		const __m128 res_2 = _mm_mul_ps(m.sse.v2, _MM_SWIZZLE(vec, Z, Z, Z, Z));
		const __m128 res_3 = _mm_mul_ps(m.sse.v3, _MM_SWIZZLE(vec, W, W, W, W));
		ret = _mm_add_ps(_mm_add_ps(res_0, res_1), _mm_add_ps(res_2, res_3));
	#else
		float x = v.x;
		float y = v.y;
		float z = v.z;
		float w = v.w;
		ret.x = m.m00 * x + m.m01 * y + m.m02 * z + m.m03 * w;
		ret.y = m.m10 * x + m.m11 * y + m.m12 * z + m.m13 * w;
		ret.z = m.m20 * x + m.m21 * y + m.m22 * z + m.m23 * w;
		ret.w = m.m30 * x + m.m31 * y + m.m32 * z + m.m33 * w;
	#endif
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 4D vector and a 4x4 matrix.</summary>
/// <param name="ret">Reference to a 4D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE vec4 &mul(vec4 &ret, const vec4 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y + m.m20 * v.z + m.m30 * v.w;
	ret.y = m.m01 * v.x + m.m11 * v.y + m.m21 * v.z + m.m31 * v.w;
	ret.z = m.m02 * v.x + m.m12 * v.y + m.m22 * v.z + m.m32 * v.w;
	ret.w = m.m03 * v.x + m.m13 * v.y + m.m23 * v.z + m.m33 * v.w;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 2D vector and a 4x4 matrix. This operation assumes that 2D vector is represented in homogeneous coordinates, so it treats the vector as if it were a 3D point (z=0 and w=1).</summary>
/// <param name="ret">Reference to a 2D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE dvec2 &mul(dvec2 &ret, const mat4 &m, const dvec2 &v)
{
	ret.x = m.m00 * v.x + m.m01 * v.y + m.m03;
	ret.y = m.m10 * v.x + m.m11 * v.y + m.m13;
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 2D vector and a 4x4 matrix. This operation assumes that 2D vector is represented in homogeneous coordinates, so it treats the vector as if it were a 3D point (z=0 and w=1).</summary>
/// <param name="ret">Reference to a 2D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE dvec2 &mul(dvec2 &ret, const dvec2 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y + m.m30;
	ret.y = m.m01 * v.x + m.m11 * v.y + m.m31;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3D vector and a 4x4 matrix. This operation assumes w=1 for the vector.</summary>
/// <param name="ret">Reference to a 3D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE dvec3 &mul(dvec3 &ret, const mat4 &m, const dvec3 &v)
{
	ret.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03;
	ret.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13;
	ret.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23;
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 3D vector and a 4x4 matrix. This operation assumes w=1 for the vector.</summary>
/// <param name="ret">Reference to a 3D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE dvec3 &mul(dvec3 &ret, const dvec3 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y + m.m20 * v.z + m.m30;
	ret.y = m.m01 * v.x + m.m11 * v.y + m.m21 * v.z + m.m31;
	ret.z = m.m02 * v.x + m.m12 * v.y + m.m22 * v.z + m.m32;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 4D vector and a 4x4 matrix.</summary>
/// <param name="ret">Reference to a 4D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE dvec4 &mul(dvec4 &ret, const mat4 &m, const dvec4 &v)
{
	ret.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03 * v.w;
	ret.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13 * v.w;
	ret.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23 * v.w;
	ret.w = m.m30 * v.x + m.m31 * v.y + m.m32 * v.z + m.m33 * v.w;
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 4D vector and a 4x4 matrix.</summary>
/// <param name="ret">Reference to a 4D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE dvec4 &mul(dvec4 &ret, const dvec4 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y + m.m20 * v.z + m.m30 * v.w;
	ret.y = m.m01 * v.x + m.m11 * v.y + m.m21 * v.z + m.m31 * v.w;
	ret.z = m.m02 * v.x + m.m12 * v.y + m.m22 * v.z + m.m32 * v.w;
	ret.w = m.m03 * v.x + m.m13 * v.y + m.m23 * v.z + m.m33 * v.w;
	return ret;
}
UNIGINE_INLINE mat4 operator*(const mat4 &m, float v)
{
	mat4 ret;
	return mul(ret, m, v);
}
UNIGINE_INLINE vec2 operator*(const mat4 &m, const vec2 &v)
{
	vec2 ret;
	return mul(ret, m, v);
}
UNIGINE_INLINE vec2 operator*(const vec2 &v, const mat4 &m)
{
	vec2 ret;
	return mul(ret, v, m);
}
UNIGINE_INLINE vec3 operator*(const mat4 &m, const vec3 &v)
{
	vec3 ret;
	return mul(ret, m, v);
}
UNIGINE_INLINE vec3 operator*(const vec3 &v, const mat4 &m)
{
	vec3 ret;
	return mul(ret, v, m);
}
UNIGINE_INLINE vec4 operator*(const mat4 &m, const vec4 &v)
{
	vec4 ret;
	return mul(ret, m, v);
}
UNIGINE_INLINE vec4 operator*(const vec4 &v, const mat4 &m)
{
	vec4 ret;
	return mul(ret, v, m);
}
UNIGINE_INLINE dvec2 operator*(const mat4 &m, const dvec2 &v)
{
	dvec2 ret;
	return mul(ret, m, v);
}
UNIGINE_INLINE dvec2 operator*(const dvec2 &v, const mat4 &m)
{
	dvec2 ret;
	return mul(ret, v, m);
}
UNIGINE_INLINE dvec3 operator*(const mat4 &m, const dvec3 &v)
{
	dvec3 ret;
	return mul(ret, m, v);
}
UNIGINE_INLINE dvec3 operator*(const dvec3 &v, const mat4 &m)
{
	dvec3 ret;
	return mul(ret, v, m);
}
UNIGINE_INLINE dvec4 operator*(const mat4 &m, const dvec4 &v)
{
	dvec4 ret;
	return mul(ret, m, v);
}
UNIGINE_INLINE dvec4 operator*(const dvec4 &v, const mat4 &m)
{
	dvec4 ret;
	return mul(ret, v, m);
}
UNIGINE_INLINE mat4 operator*(const mat4 &m0, const mat4 &m1)
{
	mat4 ret;
	return mul(ret, m0, m1);
}
UNIGINE_INLINE mat4 &mat4::operator*=(float v)
{
	return mul(*this, *this, v);
}
UNIGINE_INLINE mat4 &mat4::operator*=(const mat4 &m)
{
	return mul(*this, mat4(*this), m);
}

/// <summary>Returns the result of matrix-vector multiplication for a 2D vector and a 4x4 matrix. The method only considers the top-left 2x2 portion of the matrix.</summary>
/// <param name="ret">Reference to a 2D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE vec2 &mul3(vec2 &ret, const mat4 &m, const vec2 &v)
{
	ret.x = m.m00 * v.x + m.m01 * v.y;
	ret.y = m.m10 * v.x + m.m11 * v.y;
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 2D vector and a 4x4 matrix. The method only considers the top-left 2x2 portion of the matrix.</summary>
/// <param name="ret">Reference to a 2D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE vec2 &mul3(vec2 &ret, const vec2 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y;
	ret.y = m.m01 * v.x + m.m11 * v.y;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3D vector and a 4x4 matrix. The method only considers the top-left 3x3 portion of the matrix.</summary>
/// <param name="ret">Reference to a 3D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE vec3 &mul3(vec3 &ret, const mat4 &m, const vec3 &v)
{
	#ifdef USE_SSE
		const __m128 vec = v.vec;
		const __m128 res_0 = _mm_mul_ps(m.sse.v0, _MM_SWIZZLE(vec, X, X, X, X));
		const __m128 res_1 = _mm_mul_ps(m.sse.v1, _MM_SWIZZLE(vec, Y, Y, Y, Y));
		const __m128 res_2 = _mm_mul_ps(m.sse.v2, _MM_SWIZZLE(vec, Z, Z, Z, Z));
		ret = _mm_add_ps(_mm_add_ps(res_0, res_1), res_2);
	#else
		float x = v.x;
		float y = v.y;
		float z = v.z;
		ret.x = m.m00 * x + m.m01 * y + m.m02 * z;
		ret.y = m.m10 * x + m.m11 * y + m.m12 * z;
		ret.z = m.m20 * x + m.m21 * y + m.m22 * z;
	#endif
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 3D vector and a 4x4 matrix. The method only considers the top-left 3x3 portion of the matrix.</summary>
/// <param name="ret">Reference to a 3D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE vec3 &mul3(vec3 &ret, const vec3 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y + m.m20 * v.z;
	ret.y = m.m01 * v.x + m.m11 * v.y + m.m21 * v.z;
	ret.z = m.m02 * v.x + m.m12 * v.y + m.m22 * v.z;
	return ret;
}
/// <summary>Transforms a 3D vector using a 4x4 matrix ignoring the fourth component of both the vector and the matrix (only the first three components are modified). Can be used to apply rotations and scalings to 3D points or direction vectors, ensuring the fourth component does not interfere with the transformation; is often used in physics simulations and animations where the position is irrelevant to certain calculations; useful in rendering calculations, where only 3D transformations are required without affecting the homogenous coordinate.</summary>
/// <param name="ret">Reference to a vector to receive the result.</param>
/// <param name="m">Transformation matrix.</param>
/// <param name="v">Vector to be transformed by the matrix.</param>
UNIGINE_INLINE vec4 &mul3(vec4 &ret, const mat4 &m, const vec4 &v)
{
	#ifdef USE_SSE
		const __m128 vec = v.vec;
		const __m128 res_0 = _mm_mul_ps(m.sse.v0, _MM_SWIZZLE(vec, X, X, X, X));
		const __m128 res_1 = _mm_mul_ps(m.sse.v1, _MM_SWIZZLE(vec, Y, Y, Y, Y));
		const __m128 res_2 = _mm_mul_ps(m.sse.v2, _MM_SWIZZLE(vec, Z, Z, Z, Z));
		ret = _mm_add_ps(_mm_add_ps(res_0, res_1), res_2);
	#else
		float x = v.x;
		float y = v.y;
		float z = v.z;
		ret.x = m.m00 * x + m.m01 * y + m.m02 * z;
		ret.y = m.m10 * x + m.m11 * y + m.m12 * z;
		ret.z = m.m20 * x + m.m21 * y + m.m22 * z;
	#endif
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 4D vector and a 4x4 matrix (only the first three components are modified).</summary>
/// <param name="ret">Reference to a 4D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE vec4 &mul3(vec4 &ret, const vec4 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y + m.m20 * v.z;
	ret.y = m.m01 * v.x + m.m11 * v.y + m.m21 * v.z;
	ret.z = m.m02 * v.x + m.m12 * v.y + m.m22 * v.z;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 2D vector and a 4x4 matrix. The method only considers the top-left 2x2 portion of the matrix.</summary>
/// <param name="ret">Reference to a 2D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE dvec2 &mul3(dvec2 &ret, const mat4 &m, const dvec2 &v)
{
	ret.x = m.m00 * v.x + m.m01 * v.y;
	ret.y = m.m10 * v.x + m.m11 * v.y;
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 2D vector and a 4x4 matrix. The method only considers the top-left 2x2 portion of the matrix.</summary>
/// <param name="ret">Reference to a 2D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE dvec2 &mul3(dvec2 &ret, const dvec2 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y;
	ret.y = m.m01 * v.x + m.m11 * v.y;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3D vector and a 4x4 matrix. The method only considers the top-left 3x3 portion of the matrix.</summary>
/// <param name="ret">Reference to a 3D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE dvec3 &mul3(dvec3 &ret, const mat4 &m, const dvec3 &v)
{
	ret.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z;
	ret.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z;
	ret.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z;
	return ret;
}

/// <summary>Returns the result of vector-matrix multiplication for a 3D vector and a 4x4 matrix. The method only considers the top-left 3x3 portion of the matrix.</summary>
/// <param name="ret">Reference to a 3D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE dvec3 &mul3(dvec3 &ret, const dvec3 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y + m.m20 * v.z;
	ret.y = m.m01 * v.x + m.m11 * v.y + m.m21 * v.z;
	ret.z = m.m02 * v.x + m.m12 * v.y + m.m22 * v.z;
	return ret;
}
/// <summary>Transforms a 3D vector using a 4x4 matrix ignoring the fourth component of both the vector and the matrix (only the first three components are modified). Can be used to apply rotations and scalings to 3D points or direction vectors, ensuring the fourth component does not interfere with the transformation; is often used in physics simulations and animations where the position is irrelevant to certain calculations; useful in rendering calculations, where only 3D transformations are required without affecting the homogenous coordinate.</summary>
/// <param name="ret">Reference to a vector to receive the result.</param>
/// <param name="m">Transformation matrix.</param>
/// <param name="v">Vector to be transformed by the matrix.</param>
UNIGINE_INLINE dvec4 &mul3(dvec4 &ret, const mat4 &m, const dvec4 &v)
{
	ret.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z;
	ret.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z;
	ret.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z;
	return ret;
}

/// <summary>Returns the result of vector-matrix multiplication for a 4D vector and a 4x4 matrix (only the first three components are modified).</summary>
/// <param name="ret">Reference to a 4D vector to receive the result.</param>
/// <param name="m">Matrix to be multiplied.</param>
/// <param name="v">Vector to be multiplied.</param>
UNIGINE_INLINE dvec4 &mul3(dvec4 &ret, const dvec4 &v, const mat4 &m)
{
	ret.x = m.m00 * v.x + m.m10 * v.y + m.m20 * v.z;
	ret.y = m.m01 * v.x + m.m11 * v.y + m.m21 * v.z;
	ret.z = m.m02 * v.x + m.m12 * v.y + m.m22 * v.z;
	return ret;
}
/// <summary>Performs matrix multiplication m0 x m1. The method only considers the top-left 3x3 portions of the matrices (the rest of the elements in the resulting matrix are set to zero, except for the last diagonal element which is set to 1).</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m0">First matrix to be multiplied by the second matrix.</param>
/// <param name="m1">Second matrix by which the first one is to be multiplied.</param>
UNIGINE_INLINE mat4 &mul3(mat4 &ret, const mat4 &m0, const mat4 &m1)
{
	ret.m00 = m0.m00 * m1.m00 + m0.m01 * m1.m10 + m0.m02 * m1.m20;
	ret.m10 = m0.m10 * m1.m00 + m0.m11 * m1.m10 + m0.m12 * m1.m20;
	ret.m20 = m0.m20 * m1.m00 + m0.m21 * m1.m10 + m0.m22 * m1.m20;
	ret.m30 = 0.0f;
	ret.m01 = m0.m00 * m1.m01 + m0.m01 * m1.m11 + m0.m02 * m1.m21;
	ret.m11 = m0.m10 * m1.m01 + m0.m11 * m1.m11 + m0.m12 * m1.m21;
	ret.m21 = m0.m20 * m1.m01 + m0.m21 * m1.m11 + m0.m22 * m1.m21;
	ret.m31 = 0.0f;
	ret.m02 = m0.m00 * m1.m02 + m0.m01 * m1.m12 + m0.m02 * m1.m22;
	ret.m12 = m0.m10 * m1.m02 + m0.m11 * m1.m12 + m0.m12 * m1.m22;
	ret.m22 = m0.m20 * m1.m02 + m0.m21 * m1.m12 + m0.m22 * m1.m22;
	ret.m32 = 0.0f;
	ret.m03 = 0.0f;
	ret.m13 = 0.0f;
	ret.m23 = 0.0f;
	ret.m33 = 1.0f;
	return ret;
}

/// <summary>Performs matrix multiplication m0 x m1.</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m0">First matrix to be multiplied by the second matrix.</param>
/// <param name="m1">Second matrix by which the first one is to be multiplied.</param>
UNIGINE_INLINE mat4 &mul4(mat4 &ret, const mat4 &m0, const mat4 &m1)
{
	#ifdef USE_SSE
		__m128 m0_col0 = m0.sse.v0;
		__m128 m0_col1 = m0.sse.v1;
		__m128 m0_col2 = m0.sse.v2;
		__m128 m0_col3 = m0.sse.v3;

		__m128 m1_col0 = m1.sse.v0;
		__m128 m1_col1 = m1.sse.v1;
		__m128 m1_col2 = m1.sse.v2;
		__m128 m1_col3 = m1.sse.v3;

		__m128 res_0 = _mm_mul_ps(m0_col0, _MM_SWIZZLE(m1_col0, X, X, X, X));
		__m128 res_1 = _mm_mul_ps(m0_col1, _MM_SWIZZLE(m1_col0, Y, Y, Y, Y));
		__m128 res_2 = _mm_mul_ps(m0_col2, _MM_SWIZZLE(m1_col0, Z, Z, Z, Z));
		ret.sse.v0 = _mm_add_ps(_mm_add_ps(res_0, res_1), res_2);

		res_0 = _mm_mul_ps(m0_col0, _MM_SWIZZLE(m1_col1, X, X, X, X));
		res_1 = _mm_mul_ps(m0_col1, _MM_SWIZZLE(m1_col1, Y, Y, Y, Y));
		res_2 = _mm_mul_ps(m0_col2, _MM_SWIZZLE(m1_col1, Z, Z, Z, Z));
		ret.sse.v1 = _mm_add_ps(_mm_add_ps(res_0, res_1), res_2);

		res_0 = _mm_mul_ps(m0_col0, _MM_SWIZZLE(m1_col2, X, X, X, X));
		res_1 = _mm_mul_ps(m0_col1, _MM_SWIZZLE(m1_col2, Y, Y, Y, Y));
		res_2 = _mm_mul_ps(m0_col2, _MM_SWIZZLE(m1_col2, Z, Z, Z, Z));
		ret.sse.v2 = _mm_add_ps(_mm_add_ps(res_0, res_1), res_2);

		res_0 = _mm_mul_ps(m0_col0, _MM_SWIZZLE(m1_col3, X, X, X, X));
		res_1 = _mm_mul_ps(m0_col1, _MM_SWIZZLE(m1_col3, Y, Y, Y, Y));
		res_2 = _mm_mul_ps(m0_col2, _MM_SWIZZLE(m1_col3, Z, Z, Z, Z));
		ret.sse.v3 = _mm_add_ps(_mm_add_ps(res_0, res_1), _mm_add_ps(res_2, m0_col3));
	#else
		ret.m00 = m0.m00 * m1.m00 + m0.m01 * m1.m10 + m0.m02 * m1.m20;
		ret.m10 = m0.m10 * m1.m00 + m0.m11 * m1.m10 + m0.m12 * m1.m20;
		ret.m20 = m0.m20 * m1.m00 + m0.m21 * m1.m10 + m0.m22 * m1.m20;
		ret.m30 = 0.0f;
		ret.m01 = m0.m00 * m1.m01 + m0.m01 * m1.m11 + m0.m02 * m1.m21;
		ret.m11 = m0.m10 * m1.m01 + m0.m11 * m1.m11 + m0.m12 * m1.m21;
		ret.m21 = m0.m20 * m1.m01 + m0.m21 * m1.m11 + m0.m22 * m1.m21;
		ret.m31 = 0.0f;
		ret.m02 = m0.m00 * m1.m02 + m0.m01 * m1.m12 + m0.m02 * m1.m22;
		ret.m12 = m0.m10 * m1.m02 + m0.m11 * m1.m12 + m0.m12 * m1.m22;
		ret.m22 = m0.m20 * m1.m02 + m0.m21 * m1.m12 + m0.m22 * m1.m22;
		ret.m32 = 0.0f;
		ret.m03 = m0.m00 * m1.m03 + m0.m01 * m1.m13 + m0.m02 * m1.m23 + m0.m03;
		ret.m13 = m0.m10 * m1.m03 + m0.m11 * m1.m13 + m0.m12 * m1.m23 + m0.m13;
		ret.m23 = m0.m20 * m1.m03 + m0.m21 * m1.m13 + m0.m22 * m1.m23 + m0.m23;
		ret.m33 = 1.0f;
	#endif
	return ret;
}
/// <summary>Multiplies the specified matrix by a given 3D vector (matrix-vector multiplication).</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to be multiplied by the vector.</param>
/// <param name="v">Vector-multiplier.</param>
UNIGINE_INLINE mat4 &mult(mat4 &ret, const mat4 &m, const vec3 &v)
{
	#ifdef USE_SSE
		__m128 vec = v.vec;
		ret.sse.v0 = m.sse.v0;
		ret.sse.v1 = m.sse.v1;
		ret.sse.v2 = m.sse.v2;
		__m128 res_0 = _mm_mul_ps(m.sse.v0, _MM_SWIZZLE(vec, X, X, X, X));
		__m128 res_1 = _mm_mul_ps(m.sse.v1, _MM_SWIZZLE(vec, Y, Y, Y, Y));
		__m128 res_2 = _mm_mul_ps(m.sse.v2, _MM_SWIZZLE(vec, Z, Z, Z, Z));
		ret.sse.v3 = _mm_add_ps(_mm_add_ps(res_0, res_1), _mm_add_ps(res_2, m.sse.v3));
	#else
		ret.m00 = m.m00;
		ret.m01 = m.m01;
		ret.m02 = m.m02;
		ret.m10 = m.m10;
		ret.m11 = m.m11;
		ret.m12 = m.m12;
		ret.m20 = m.m20;
		ret.m21 = m.m21;
		ret.m22 = m.m22;
		ret.m30 = m.m30;
		ret.m31 = m.m31;
		ret.m32 = m.m32;
		ret.m03 = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03;
		ret.m13 = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13;
		ret.m23 = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23;
		ret.m33 = m.m33;
	#endif
	return ret;
}

/// <summary>Performs matrix addition m0+m1 (element-wise).</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m0">First matrix to which the second matrix will be added.</param>
/// <param name="m1">Second matrix that will be added to the first.</param>
UNIGINE_INLINE mat4 &add(mat4 &ret, const mat4 &m0, const mat4 &m1)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_add_ps(m0.sse.v0, m1.sse.v0);
		ret.sse.v1 = _mm_add_ps(m0.sse.v1, m1.sse.v1);
		ret.sse.v2 = _mm_add_ps(m0.sse.v2, m1.sse.v2);
		ret.sse.v3 = _mm_add_ps(m0.sse.v3, m1.sse.v3);
	#else
		ret.m00 = m0.m00 + m1.m00;
		ret.m01 = m0.m01 + m1.m01;
		ret.m02 = m0.m02 + m1.m02;
		ret.m03 = m0.m03 + m1.m03;
		ret.m10 = m0.m10 + m1.m10;
		ret.m11 = m0.m11 + m1.m11;
		ret.m12 = m0.m12 + m1.m12;
		ret.m13 = m0.m13 + m1.m13;
		ret.m20 = m0.m20 + m1.m20;
		ret.m21 = m0.m21 + m1.m21;
		ret.m22 = m0.m22 + m1.m22;
		ret.m23 = m0.m23 + m1.m23;
		ret.m30 = m0.m30 + m1.m30;
		ret.m31 = m0.m31 + m1.m31;
		ret.m32 = m0.m32 + m1.m32;
		ret.m33 = m0.m33 + m1.m33;
	#endif
	return ret;
}
UNIGINE_INLINE mat4 operator+(const mat4 &m0, const mat4 &m1)
{
	mat4 ret;
	return add(ret, m0, m1);
}
UNIGINE_INLINE mat4 &mat4::operator+=(const mat4 &m)
{
	return add(*this, *this, m);
}

/// <summary>Performs matrix subtraction m0-m1 (element-wise).</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m0">First matrix from which the second matrix will be subtracted.</param>
/// <param name="m1">Second matrix that will be subtracted from the first.</param>
UNIGINE_INLINE mat4 &sub(mat4 &ret, const mat4 &m0, const mat4 &m1)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_sub_ps(m0.sse.v0, m1.sse.v0);
		ret.sse.v1 = _mm_sub_ps(m0.sse.v1, m1.sse.v1);
		ret.sse.v2 = _mm_sub_ps(m0.sse.v2, m1.sse.v2);
		ret.sse.v3 = _mm_sub_ps(m0.sse.v3, m1.sse.v3);
	#else
		ret.m00 = m0.m00 - m1.m00;
		ret.m01 = m0.m01 - m1.m01;
		ret.m02 = m0.m02 - m1.m02;
		ret.m03 = m0.m03 - m1.m03;
		ret.m10 = m0.m10 - m1.m10;
		ret.m11 = m0.m11 - m1.m11;
		ret.m12 = m0.m12 - m1.m12;
		ret.m13 = m0.m13 - m1.m13;
		ret.m20 = m0.m20 - m1.m20;
		ret.m21 = m0.m21 - m1.m21;
		ret.m22 = m0.m22 - m1.m22;
		ret.m23 = m0.m23 - m1.m23;
		ret.m30 = m0.m30 - m1.m30;
		ret.m31 = m0.m31 - m1.m31;
		ret.m32 = m0.m32 - m1.m32;
		ret.m33 = m0.m33 - m1.m33;
	#endif
	return ret;
}
UNIGINE_INLINE mat4 operator-(const mat4 &m0, const mat4 &m1)
{
	mat4 ret;
	return sub(ret, m0, m1);
}
UNIGINE_INLINE mat4 &mat4::operator-=(const mat4 &m)
{
	return sub(*this, *this, m);
}

/// <summary>Projects a 3D point from homogeneous coordinates (given by a 4x4 transformation matrix) into normalized device coordinates (NDC).</summary>
/// <param name="ret">Reference to a 3D vector to receive the result.</param>
/// <param name="m">Transformation matrix, typically the combined view and projection matrix.</param>
/// <param name="v">3D vector representing the original point (in world coordinates) to be projected.</param>
UNIGINE_INLINE vec3 &proj(vec3 &ret, const mat4 &m, const vec3 &v)
{
	#ifdef USE_SSE
		__m128 vec = v.vec;
		__m128 res_0 = _mm_mul_ps(m.sse.v0, _MM_SWIZZLE(vec, X, X, X, X));
		__m128 res_1 = _mm_mul_ps(m.sse.v1, _MM_SWIZZLE(vec, Y, Y, Y, Y));
		__m128 res_2 = _mm_mul_ps(m.sse.v2, _MM_SWIZZLE(vec, Z, Z, Z, Z));
		__m128 res_3 = _mm_add_ps(_mm_add_ps(res_0, res_1), _mm_add_ps(res_2, m.sse.v3));
		ret = _mm_div_ps(res_3, _MM_SWIZZLE(res_3, W, W, W, W));
	#else
		float x = v.x;
		float y = v.y;
		float z = v.z;
		float iw = rcp(m.m30 * x + m.m31 * y + m.m32 * z + m.m33);
		ret.x = (m.m00 * x + m.m01 * y + m.m02 * z + m.m03) * iw;
		ret.y = (m.m10 * x + m.m11 * y + m.m12 * z + m.m13) * iw;
		ret.z = (m.m20 * x + m.m21 * y + m.m22 * z + m.m23) * iw;
	#endif
	return ret;
}
/// <summary>Projects a 4D point from homogeneous coordinates (given by a 4x4 transformation matrix) into normalized device coordinates (NDC).</summary>
/// <param name="ret">Reference to a 4D vector to receive the result.</param>
/// <param name="m">Transformation matrix, typically the combined view and projection matrix.</param>
/// <param name="v">4D vector representing the original point (in world coordinates) to be projected.</param>
UNIGINE_INLINE vec4 &proj(vec4 &ret, const mat4 &m, const vec4 &v)
{
	#ifdef USE_SSE
		__m128 vec = v.vec;
		__m128 res_0 = _mm_mul_ps(m.sse.v0, _MM_SWIZZLE(vec, X, X, X, X));
		__m128 res_1 = _mm_mul_ps(m.sse.v1, _MM_SWIZZLE(vec, Y, Y, Y, Y));
		__m128 res_2 = _mm_mul_ps(m.sse.v2, _MM_SWIZZLE(vec, Z, Z, Z, Z));
		__m128 res_3 = _mm_mul_ps(m.sse.v3, _MM_SWIZZLE(vec, W, W, W, W));
		__m128 res_4 = _mm_add_ps(_mm_add_ps(res_0, res_1), _mm_add_ps(res_2, res_3));
		ret = _mm_div_ps(res_4, _MM_SWIZZLE(res_4, W, W, W, W));
	#else
		float x = v.x;
		float y = v.y;
		float z = v.z;
		float w = v.w;
		float iw = rcp(m.m30 * x + m.m31 * y + m.m32 * z + m.m33 * w);
		ret.x = (m.m00 * x + m.m01 * y + m.m02 * z + m.m03 * w) * iw;
		ret.y = (m.m10 * x + m.m11 * y + m.m12 * z + m.m13 * w) * iw;
		ret.z = (m.m20 * x + m.m21 * y + m.m22 * z + m.m23 * w) * iw;
		ret.w = 1.0f;
	#endif
	return ret;
}
/// <summary>Projects a 3D point from homogeneous coordinates (given by a 4x4 transformation matrix) into normalized device coordinates (NDC).</summary>
/// <param name="ret">Reference to a 3D vector to receive the result.</param>
/// <param name="m">Transformation matrix, typically the combined view and projection matrix.</param>
/// <param name="v">3D vector representing the original point (in world coordinates) to be projected.</param>
UNIGINE_INLINE dvec3 &proj(dvec3 &ret, const mat4 &m, const dvec3 &v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	double iw = Math::rcp(m.m30 * x + m.m31 * y + m.m32 * z + m.m33);
	ret.x = (m.m00 * x + m.m01 * y + m.m02 * z + m.m03) * iw;
	ret.y = (m.m10 * x + m.m11 * y + m.m12 * z + m.m13) * iw;
	ret.z = (m.m20 * x + m.m21 * y + m.m22 * z + m.m23) * iw;
	return ret;
}
/// <summary>Projects a 4D point from homogeneous coordinates (given by a 4x4 transformation matrix) into normalized device coordinates (NDC).</summary>
/// <param name="ret">Reference to a 4D vector to receive the result.</param>
/// <param name="m">Transformation matrix, typically the combined view and projection matrix.</param>
/// <param name="v">4D vector representing the original point (in world coordinates) to be projected.</param>
UNIGINE_INLINE dvec4 &proj(dvec4 &ret, const mat4 &m, const dvec4 &v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	double w = v.w;
	double iw = Math::rcp(m.m30 * x + m.m31 * y + m.m32 * z + m.m33 * w);
	ret.x = (m.m00 * x + m.m01 * y + m.m02 * z + m.m03 * w) * iw;
	ret.y = (m.m10 * x + m.m11 * y + m.m12 * z + m.m13 * w) * iw;
	ret.z = (m.m20 * x + m.m21 * y + m.m22 * z + m.m23 * w) * iw;
	ret.w = 1.0f;
	return ret;
}

/// <summary>Orthonormalizes the specified matrix - normalizes its direction vectors and ensures they are orthogonal.</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to be orthonormalized.</param>
UNIGINE_INLINE mat4 &orthonormalize(mat4 &ret, const mat4 &m)
{
	#ifdef USE_SSE
		__m128 m_col0 = m.sse.v0;
		__m128 m_col1 = m.sse.v1;

		__m128 x_yzx = _MM_SWIZZLE(m_col0, Y, Z, X, W);
		__m128 x_zxy = _MM_SWIZZLE(m_col0, Z, X, Y, W);
		__m128 y_yzx = _MM_SWIZZLE(m_col1, Y, Z, X, W);
		__m128 y_zxy = _MM_SWIZZLE(m_col1, Z, X, Y, W);
		__m128 z = _mm_sub_ps(_mm_mul_ps(x_yzx, y_zxy), _mm_mul_ps(x_zxy, y_yzx));
		__m128 z_yzx = _MM_SWIZZLE(z, Y, Z, X, W);
		__m128 z_zxy = _MM_SWIZZLE(z, Z, X, Y, W);
		__m128 y = _mm_sub_ps(_mm_mul_ps(z_yzx, x_zxy), _mm_mul_ps(z_zxy, x_yzx));
		__m128 col_0 = _mm_mul_ps(m_col0, m_col0);
		__m128 col_1 = _mm_mul_ps(y, y);
		__m128 col_2 = _mm_mul_ps(z, z);
		__m128 res_0 = _mm_shuffle_ps(col_0, col_1, _MM_PERM2(X, Y, X, Y));
		__m128 res_1 = _mm_shuffle_ps(col_0, col_1, _MM_PERM2(Z, W, Z, W));
		__m128 res_2 = _mm_shuffle_ps(col_2, col_2, _MM_PERM2(X, Y, X, Y));
		__m128 res_3 = _mm_shuffle_ps(col_2, col_2, _MM_PERM2(Z, W, Z, W));
		__m128 row_0 = _mm_shuffle_ps(res_0, res_2, _MM_PERM2(X, Z, X, Z));
		__m128 row_1 = _mm_shuffle_ps(res_0, res_2, _MM_PERM2(Y, W, Y, W));
		__m128 row_2 = _mm_shuffle_ps(res_1, res_3, _MM_PERM2(X, Z, X, Z));
		__m128 ilength = _mm_rsqrt_ps_nr(_mm_add_ps(_mm_add_ps(row_0, row_1), row_2));
		ret.sse.v0 = _mm_mul_ps(m_col0, _MM_SWIZZLE(ilength, X, X, X, X));
		ret.sse.v1 = _mm_mul_ps(y, _MM_SWIZZLE(ilength, Y, Y, Y, Y));
		ret.sse.v2 = _mm_mul_ps(z, _MM_SWIZZLE(ilength, Z, Z, Z, Z));
		ret.sse.v3 = m.sse.v3;
	#else
		vec3 x = vec3(m.m00, m.m10, m.m20);
		vec3 y = vec3(m.m01, m.m11, m.m21);
		vec3 z = cross(x, y);
		cross(y, z, x);
		x.normalize();
		y.normalize();
		z.normalize();
		ret.m00 = x.x;
		ret.m01 = y.x;
		ret.m02 = z.x;
		ret.m03 = m.m03;
		ret.m10 = x.y;
		ret.m11 = y.y;
		ret.m12 = z.y;
		ret.m13 = m.m13;
		ret.m20 = x.z;
		ret.m21 = y.z;
		ret.m22 = z.z;
		ret.m23 = m.m23;
		ret.m30 = m.m30;
		ret.m31 = m.m31;
		ret.m32 = m.m32;
		ret.m33 = m.m33;
	#endif
	return ret;
}
/// <summary>Orthonormalizes the specified matrix - normalizes its direction vectors and ensures they are orthogonal.</summary>
/// <param name="m">Matrix to be orthonormalized.</param>
UNIGINE_INLINE mat4 orthonormalize(const mat4 &m)
{
	mat4 ret;
	return orthonormalize(ret, m);
}

/// <summary>Returns inverse of the specified matrix. The inverse of a matrix is a matrix that if multiplied by the original would result in identity matrix: AA' = A'A = I.</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to be inverted.</param>
UNIGINE_INLINE mat4 &inverse(mat4 &ret, const mat4 &m)
{
	#ifdef USE_SSE
		__m128 m_col0 = m.sse.v0;
		__m128 m_col1 = m.sse.v1;
		__m128 m_col2 = m.sse.v2;
		__m128 m_col3 = m.sse.v3;

		__m128 res_0 = _mm_shuffle_ps(m_col0, m_col1, _MM_PERM2(X, Y, X, Y));
		__m128 res_1 = _mm_shuffle_ps(m_col0, m_col1, _MM_PERM2(Z, W, Z, W));
		__m128 res_2 = _mm_shuffle_ps(m_col2, m_col3, _MM_PERM2(X, Y, X, Y));
		__m128 res_3 = _mm_shuffle_ps(m_col2, m_col3, _MM_PERM2(Z, W, Z, W));
		__m128 row_0 = _mm_shuffle_ps(res_0, res_2, _MM_PERM2(X, Z, X, Z));
		__m128 row_1 = _mm_shuffle_ps(res_2, res_0, _MM_PERM2(Y, W, Y, W));
		__m128 row_2 = _mm_shuffle_ps(res_1, res_3, _MM_PERM2(X, Z, X, Z));
		__m128 row_3 = _mm_shuffle_ps(res_3, res_1, _MM_PERM2(Y, W, Y, W));
		__m128 temp = _mm_mul_ps(row_2, row_3);
		temp = _MM_SWIZZLE(temp, Y, X, W, Z);
		res_0 = _mm_mul_ps(row_1, temp);
		res_1 = _mm_mul_ps(row_0, temp);
		temp = _MM_SWIZZLE(temp, Z, W, X, Y);
		res_0 = _mm_sub_ps(_mm_mul_ps(row_1, temp), res_0);
		res_1 = _mm_sub_ps(_mm_mul_ps(row_0, temp), res_1);
		res_1 = _MM_SWIZZLE(res_1, Z, W, X, Y);
		temp = _mm_mul_ps(row_1, row_2);
		temp = _MM_SWIZZLE(temp, Y, X, W, Z);
		res_0 = _mm_add_ps(_mm_mul_ps(row_3, temp), res_0);
		res_3 = _mm_mul_ps(row_0, temp);
		temp = _MM_SWIZZLE(temp, Z, W, X, Y);
		res_0 = _mm_sub_ps(res_0, _mm_mul_ps(row_3, temp));
		res_3 = _mm_sub_ps(_mm_mul_ps(row_0, temp), res_3);
		res_3 = _MM_SWIZZLE(res_3, Z, W, X, Y);
		temp = _mm_mul_ps(row_3, _MM_SWIZZLE(row_1, Z, W, X, Y));
		temp = _MM_SWIZZLE(temp, Y, X, W, Z);
		row_2 = _MM_SWIZZLE(row_2, Z, W, X, Y);
		res_0 = _mm_add_ps(_mm_mul_ps(row_2, temp), res_0);
		res_2 = _mm_mul_ps(row_0, temp);
		temp = _MM_SWIZZLE(temp, Z, W, X, Y);
		res_0 = _mm_sub_ps(res_0, _mm_mul_ps(row_2, temp));
		res_2 = _mm_sub_ps(_mm_mul_ps(row_0, temp), res_2);
		res_2 = _MM_SWIZZLE(res_2, Z, W, X, Y);
		temp = _mm_mul_ps(row_0, row_1);
		temp = _MM_SWIZZLE(temp, Y, X, W, Z);
		res_2 = _mm_add_ps(_mm_mul_ps(row_3, temp), res_2);
		res_3 = _mm_sub_ps(_mm_mul_ps(row_2, temp), res_3);
		temp = _MM_SWIZZLE(temp, Z, W, X, Y);
		res_2 = _mm_sub_ps(_mm_mul_ps(row_3, temp), res_2);
		res_3 = _mm_sub_ps(res_3, _mm_mul_ps(row_2, temp));
		temp = _mm_mul_ps(row_0, row_3);
		temp = _MM_SWIZZLE(temp, Y, X, W, Z);
		res_1 = _mm_sub_ps(res_1, _mm_mul_ps(row_2, temp));
		res_2 = _mm_add_ps(_mm_mul_ps(row_1, temp), res_2);
		temp = _MM_SWIZZLE(temp, Z, W, X, Y);
		res_1 = _mm_add_ps(_mm_mul_ps(row_2, temp), res_1);
		res_2 = _mm_sub_ps(res_2, _mm_mul_ps(row_1, temp));
		temp = _mm_mul_ps(row_0, row_2);
		temp = _MM_SWIZZLE(temp, Y, X, W, Z);
		res_1 = _mm_add_ps(_mm_mul_ps(row_3, temp), res_1);
		res_3 = _mm_sub_ps(res_3, _mm_mul_ps(row_1, temp));
		temp = _MM_SWIZZLE(temp, Z, W, X, Y);
		res_1 = _mm_sub_ps(res_1, _mm_mul_ps(row_3, temp));
		res_3 = _mm_add_ps(_mm_mul_ps(row_1, temp), res_3);
		__m128 det = _mm_mul_ps(row_0, res_0);
		det = _mm_add_ps(det, _MM_SWIZZLE(det, Y, X, W, Z));
		det = _mm_add_ss(det, _MM_SWIZZLE(det, Z, W, X, Y));
		temp = _MM_SWIZZLE(_mm_rcp_ss_nr(det), X, X, X, X);
		ret.sse.v0 = _mm_mul_ps(res_0, temp);
		ret.sse.v1 = _mm_mul_ps(res_1, temp);
		ret.sse.v2 = _mm_mul_ps(res_2, temp);
		ret.sse.v3 = _mm_mul_ps(res_3, temp);
	#else
		float temp[12];
		temp[0] = m.m22 * m.m33;
		temp[1] = m.m23 * m.m32;
		temp[2] = m.m21 * m.m33;
		temp[3] = m.m23 * m.m31;
		temp[4] = m.m21 * m.m32;
		temp[5] = m.m22 * m.m31;
		temp[6] = m.m20 * m.m33;
		temp[7] = m.m23 * m.m30;
		temp[8] = m.m20 * m.m32;
		temp[9] = m.m22 * m.m30;
		temp[10] = m.m20 * m.m31;
		temp[11] = m.m21 * m.m30;
		ret.m00 = temp[0] * m.m11 + temp[3] * m.m12 + temp[4] * m.m13;
		ret.m00 -= temp[1] * m.m11 + temp[2] * m.m12 + temp[5] * m.m13;
		ret.m10 = temp[1] * m.m10 + temp[6] * m.m12 + temp[9] * m.m13;
		ret.m10 -= temp[0] * m.m10 + temp[7] * m.m12 + temp[8] * m.m13;
		ret.m20 = temp[2] * m.m10 + temp[7] * m.m11 + temp[10] * m.m13;
		ret.m20 -= temp[3] * m.m10 + temp[6] * m.m11 + temp[11] * m.m13;
		ret.m30 = temp[5] * m.m10 + temp[8] * m.m11 + temp[11] * m.m12;
		ret.m30 -= temp[4] * m.m10 + temp[9] * m.m11 + temp[10] * m.m12;
		ret.m01 = temp[1] * m.m01 + temp[2] * m.m02 + temp[5] * m.m03;
		ret.m01 -= temp[0] * m.m01 + temp[3] * m.m02 + temp[4] * m.m03;
		ret.m11 = temp[0] * m.m00 + temp[7] * m.m02 + temp[8] * m.m03;
		ret.m11 -= temp[1] * m.m00 + temp[6] * m.m02 + temp[9] * m.m03;
		ret.m21 = temp[3] * m.m00 + temp[6] * m.m01 + temp[11] * m.m03;
		ret.m21 -= temp[2] * m.m00 + temp[7] * m.m01 + temp[10] * m.m03;
		ret.m31 = temp[4] * m.m00 + temp[9] * m.m01 + temp[10] * m.m02;
		ret.m31 -= temp[5] * m.m00 + temp[8] * m.m01 + temp[11] * m.m02;
		temp[0] = m.m02 * m.m13;
		temp[1] = m.m03 * m.m12;
		temp[2] = m.m01 * m.m13;
		temp[3] = m.m03 * m.m11;
		temp[4] = m.m01 * m.m12;
		temp[5] = m.m02 * m.m11;
		temp[6] = m.m00 * m.m13;
		temp[7] = m.m03 * m.m10;
		temp[8] = m.m00 * m.m12;
		temp[9] = m.m02 * m.m10;
		temp[10] = m.m00 * m.m11;
		temp[11] = m.m01 * m.m10;
		ret.m02 = temp[0] * m.m31 + temp[3] * m.m32 + temp[4] * m.m33;
		ret.m02 -= temp[1] * m.m31 + temp[2] * m.m32 + temp[5] * m.m33;
		ret.m12 = temp[1] * m.m30 + temp[6] * m.m32 + temp[9] * m.m33;
		ret.m12 -= temp[0] * m.m30 + temp[7] * m.m32 + temp[8] * m.m33;
		ret.m22 = temp[2] * m.m30 + temp[7] * m.m31 + temp[10] * m.m33;
		ret.m22 -= temp[3] * m.m30 + temp[6] * m.m31 + temp[11] * m.m33;
		ret.m32 = temp[5] * m.m30 + temp[8] * m.m31 + temp[11] * m.m32;
		ret.m32 -= temp[4] * m.m30 + temp[9] * m.m31 + temp[10] * m.m32;
		ret.m03 = temp[2] * m.m22 + temp[5] * m.m23 + temp[1] * m.m21;
		ret.m03 -= temp[4] * m.m23 + temp[0] * m.m21 + temp[3] * m.m22;
		ret.m13 = temp[8] * m.m23 + temp[0] * m.m20 + temp[7] * m.m22;
		ret.m13 -= temp[6] * m.m22 + temp[9] * m.m23 + temp[1] * m.m20;
		ret.m23 = temp[6] * m.m21 + temp[11] * m.m23 + temp[3] * m.m20;
		ret.m23 -= temp[10] * m.m23 + temp[2] * m.m20 + temp[7] * m.m21;
		ret.m33 = temp[10] * m.m22 + temp[4] * m.m20 + temp[9] * m.m21;
		ret.m33 -= temp[8] * m.m21 + temp[11] * m.m22 + temp[5] * m.m20;
		float idet = rcp(m.m00 * ret.m00 + m.m01 * ret.m10 + m.m02 * ret.m20 + m.m03 * ret.m30);
		ret.m00 *= idet;
		ret.m10 *= idet;
		ret.m20 *= idet;
		ret.m30 *= idet;
		ret.m01 *= idet;
		ret.m11 *= idet;
		ret.m21 *= idet;
		ret.m31 *= idet;
		ret.m02 *= idet;
		ret.m12 *= idet;
		ret.m22 *= idet;
		ret.m32 *= idet;
		ret.m03 *= idet;
		ret.m13 *= idet;
		ret.m23 *= idet;
		ret.m33 *= idet;
	#endif
	return ret;
}
/// <summary>Returns inverse of the specified matrix. The inverse of a matrix is a matrix that if multiplied by the original would result in identity matrix: AA' = A'A = I.</summary>
/// <param name="m">Matrix to be inverted.</param>
UNIGINE_INLINE mat4 inverse(const mat4 &m)
{
	mat4 ret;
	return inverse(ret, m);
}

/// <summary>Inverts a matrix that consists of a 3×4 sub-matrix (upper-left) and a translation vector. The last row of the matrix is ignored. Compared to the inverse() function, this one is a bit faster and, which is more important, more stable. A matrix suitable for such inversion looks like this:
/// m00	m10	m20	m30
/// m01	m11	m21	m31
/// m02	m12	m22	m32
/// 0	0	0	1</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to be inverted.</param>
UNIGINE_INLINE mat4 &inverse4(mat4 &ret, const mat4 &m)
{
	float det = m.m00 * (m.m11 * m.m22 - m.m12 * m.m21);
	det -= m.m01 * (m.m10 * m.m22 - m.m12 * m.m20);
	det += m.m02 * (m.m10 * m.m21 - m.m11 * m.m20);

	float idet = 1.0f / det;

	ret.m00 = (m.m11 * m.m22 - m.m12 * m.m21) * idet;
	ret.m10 = -(m.m10 * m.m22 - m.m12 * m.m20) * idet;
	ret.m20 = (m.m10 * m.m21 - m.m11 * m.m20) * idet;
	ret.m30 = 0.0f;

	ret.m01 = -(m.m01 * m.m22 - m.m02 * m.m21) * idet;
	ret.m11 = (m.m00 * m.m22 - m.m02 * m.m20) * idet;
	ret.m21 = -(m.m00 * m.m21 - m.m01 * m.m20) * idet;
	ret.m31 = 0.0f;

	ret.m02 = (m.m01 * m.m12 - m.m02 * m.m11) * idet;
	ret.m12 = -(m.m00 * m.m12 - m.m02 * m.m10) * idet;
	ret.m22 = (m.m00 * m.m11 - m.m01 * m.m10) * idet;
	ret.m32 = 0.0f;

	ret.m03 = -(ret.m00 * m.m03 + ret.m01 * m.m13 + ret.m02 * m.m23);
	ret.m13 = -(ret.m10 * m.m03 + ret.m11 * m.m13 + ret.m12 * m.m23);
	ret.m23 = -(ret.m20 * m.m03 + ret.m21 * m.m13 + ret.m22 * m.m23);
	ret.m33 = 1.0f;
	return ret;
}
/// <summary>Inverts a matrix that consists of a 3×4 sub-matrix (upper-left) and a translation vector. The last row of the matrix is ignored. Compared to the inverse() function, this one is a bit faster and, which is more important, more stable. A matrix suitable for such inversion looks like this:
/// m00	m10	m20	m30
/// m01	m11	m21	m31
/// m02	m12	m22	m32
/// 0	0	0	1</summary>
/// <param name="m">Matrix to be inverted.</param>
UNIGINE_INLINE mat4 inverse4(const mat4 &m)
{
	mat4 ret;
	return inverse4(ret, m);
}

/// <summary>Extracts and returns the rotation component from the specified transformation matrix. It effectively removes any translation, scaling, or shearing components, ensuring that the resulting matrix only contains the rotation data.</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to extract the rotation component from.</param>
UNIGINE_INLINE mat4 &rotation(mat4 &ret, const mat4 &m)
{
	ret.m00 = m.m00;
	ret.m01 = m.m01;
	ret.m02 = m.m02;
	ret.m03 = 0.0f;
	ret.m10 = m.m10;
	ret.m11 = m.m11;
	ret.m12 = m.m12;
	ret.m13 = 0.0f;
	ret.m20 = m.m20;
	ret.m21 = m.m21;
	ret.m22 = m.m22;
	ret.m23 = 0.0f;
	ret.m30 = 0.0f;
	ret.m31 = 0.0f;
	ret.m32 = 0.0f;
	ret.m33 = 1.0f;
	return ret;
}
/// <summary>Extracts and returns the rotation component from the specified transformation matrix. It effectively removes any translation, scaling, or shearing components, ensuring that the resulting matrix only contains the rotation data.</summary>
/// <param name="m">Matrix to extract the rotation component from.</param>
UNIGINE_INLINE mat4 rotation(const mat4 &m)
{
	mat4 ret;
	return rotation(ret, m);
}

/// <summary>Transposes the specified transformation matrix. Transposing a matrix involves swapping its rows with its columns, effectively flipping it along its diagonal.</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to be transposed.</param>
UNIGINE_INLINE mat4 &transpose(mat4 &ret, const mat4 &m)
{
	#ifdef USE_SSE
		__m128 m_col0 = m.sse.v0;
		__m128 m_col1 = m.sse.v1;
		__m128 m_col2 = m.sse.v2;
		__m128 m_col3 = m.sse.v3;

		__m128 res_0 = _mm_shuffle_ps(m_col0, m_col1, _MM_PERM2(X, Y, X, Y));
		__m128 res_1 = _mm_shuffle_ps(m_col0, m_col1, _MM_PERM2(Z, W, Z, W));
		__m128 res_2 = _mm_shuffle_ps(m_col2, m_col3, _MM_PERM2(X, Y, X, Y));
		__m128 res_3 = _mm_shuffle_ps(m_col2, m_col3, _MM_PERM2(Z, W, Z, W));
		ret.sse.v0 = _mm_shuffle_ps(res_0, res_2, _MM_PERM2(X, Z, X, Z));
		ret.sse.v1 = _mm_shuffle_ps(res_0, res_2, _MM_PERM2(Y, W, Y, W));
		ret.sse.v2 = _mm_shuffle_ps(res_1, res_3, _MM_PERM2(X, Z, X, Z));
		ret.sse.v3 = _mm_shuffle_ps(res_1, res_3, _MM_PERM2(Y, W, Y, W));
	#else
		ret.m00 = m.m00;
		ret.m01 = m.m10;
		ret.m02 = m.m20;
		ret.m03 = m.m30;
		ret.m10 = m.m01;
		ret.m11 = m.m11;
		ret.m12 = m.m21;
		ret.m13 = m.m31;
		ret.m20 = m.m02;
		ret.m21 = m.m12;
		ret.m22 = m.m22;
		ret.m23 = m.m32;
		ret.m30 = m.m03;
		ret.m31 = m.m13;
		ret.m32 = m.m23;
		ret.m33 = m.m33;
	#endif
	return ret;
}
/// <summary>Transposes the specified transformation matrix. Transposing a matrix involves swapping its rows with its columns, effectively flipping it along its diagonal.</summary>
/// <param name="m">Matrix to be transposed.</param>
UNIGINE_INLINE mat4 transpose(const mat4 &m)
{
	mat4 ret;
	return transpose(ret, m);
}

/// <summary>Returns a partial transpose of the specified transformation matrix, where only the upper-left 3x3 submatrix (the rotational part) is transposed. The translation components and the rest of the matrix remain unchanged. Transposing a matrix involves swapping its rows with its columns, effectively flipping it along its diagonal.</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to be transposed.</param>
UNIGINE_INLINE mat4 &transpose3(mat4 &ret, const mat4 &m)
{
	ret.m00 = m.m00;
	ret.m01 = m.m10;
	ret.m02 = m.m20;
	ret.m03 = m.m03;
	ret.m10 = m.m01;
	ret.m11 = m.m11;
	ret.m12 = m.m21;
	ret.m13 = m.m13;
	ret.m20 = m.m02;
	ret.m21 = m.m12;
	ret.m22 = m.m22;
	ret.m23 = m.m23;
	ret.m30 = m.m30;
	ret.m31 = m.m31;
	ret.m32 = m.m32;
	ret.m33 = m.m33;
	return ret;
}
/// <summary>Returns a partial transpose of the specified transformation matrix, where only the upper-left 3x3 submatrix (the rotational part) is transposed. The translation components and the rest of the matrix remain unchanged. Transposing a matrix involves swapping its rows with its columns, effectively flipping it along its diagonal.</summary>
/// <param name="m">Matrix to be transposed.</param>
UNIGINE_INLINE mat4 transpose3(const mat4 &m)
{
	mat4 ret;
	return transpose3(ret, m);
}

/// <summary>Returns an orthographic projection matrix for the specified boundaries of the orthographic view volume.</summary>
/// <param name="l">Left boundary of the view volume.</param>
/// <param name="r">Right boundary of the view volume.</param>
/// <param name="b">Bottom boundary of the view volume.</param>
/// <param name="t">Top boundary of the view volume.</param>
/// <param name="n">Near boundary of the view volume.</param>
/// <param name="f">Far boundary of the view volume.</param>
UNIGINE_INLINE mat4 ortho(float l, float r, float b, float t, float n, float f)
{
	float rl = r - l;
	float tb = t - b;
	rl = max(abs(rl), Consts::EPS) * sign(rl);
	tb = max(abs(tb), Consts::EPS) * sign(tb);
	float fn = max(f - n, Consts::EPS);
	return mat4(
		2.0f / rl, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / tb, 0.0f, 0.0f,
		0.0f, 0.0f, -2.0f / fn, 0.0f,
		- (r + l) / rl, -(t + b) / tb, -(f + n) / fn, 1.0f
	);
}
/// <summary>Returns a perspective projection matrix defining a view frustum for the specified boundaries.</summary>
/// <param name="l">Left boundary of the near clipping plane.</param>
/// <param name="r">Right boundary of the near clipping plane.</param>
/// <param name="b">Bottom boundary of the near clipping plane.</param>
/// <param name="t">Top boundary of the near clipping plane.</param>
/// <param name="n">Distance to the near clipping plane (must be positive).</param>
/// <param name="f">Distance to the far clipping plane.</param>
UNIGINE_INLINE mat4 frustum(float l, float r, float b, float t, float n, float f)
{
	float rl = r - l;
	float tb = t - b;
	rl = max(abs(rl), Consts::EPS) * sign(rl);
	tb = max(abs(tb), Consts::EPS) * sign(tb);
	float fn = max(f - n, Consts::EPS);
	return mat4(
		2.0f * n / rl, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f * n / tb, 0.0f, 0.0f,
		(r + l) / rl, (t + b) / tb, -(f + n) / fn, -1.0f,
		0.0f, 0.0f, -2.0f * f * n / fn, 0.0f
	);
}
/// <summary>Returns a perspective projection matrix based on a specified field of view (FOV), aspect ratio, and near and far clipping planes.</summary>
/// <param name="fov">Field of view (in degrees), usually along the vertical axis of the camera.</param>
/// <param name="aspect">Aspect ratio of the viewport (width/height).</param>
/// <param name="n">Distance to the near clipping plane.</param>
/// <param name="f">Distance to the far clipping plane.</param>
UNIGINE_INLINE mat4 perspective(float fov, float aspect, float n, float f)
{
	float h = 1.0f;
	float w = aspect;
	if (!compare(fov, 90.0f))
	{
		h = max(tan(fov * Consts::DEG2RAD * 0.5f), Consts::EPS);
		w = max(h * aspect, Consts::EPS);
	}
	float fn = max(f - n, Consts::EPS);
	return mat4(
		1.0f / w, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / h, 0.0f, 0.0f,
		0.0f, 0.0f, -(f + n) / fn, -1.0f,
		0.0f, 0.0f, -2.0f * f * n / fn, 0.0f
	);
}

/// <summary>Returns a reflection matrix based on a given 4D vector representing a plane. This reflection matrix can be used to reflect objects across the specified plane in 3D space.</summary>
/// <param name="plane">4D vector representing a reflection plane: A 4D vector (A, B, C, D) representing a plane, where: A,B,C are the components of the normal vector of the plane, and D is the distance of the plane from the origin.</param>
UNIGINE_INLINE mat4 reflect(const vec4 &plane)
{
	float x = plane.x;
	float y = plane.y;
	float z = plane.z;
	float x2 = x * 2.0f;
	float y2 = y * 2.0f;
	float z2 = z * 2.0f;
	return mat4(
		1.0f - x * x2,	-x * y2,		-x * z2,		0.0f,
		-y * x2,		1.0f - y * y2,	-y * z2,		0.0f,
		-z * x2,		-z * y2,		1.0f - z * z2,	0.0f,
		-plane.w * x2,	-plane.w * y2,	-plane.w * z2,	1.0f
	);
}

/// <summary>Computes a local coordinate system (or basis) consisting of three perpendicular vectors (x, y, z) based on the input position, target, and up vectors, as well as the axis specified. This is commonly used to generate a reference frame in 3D space, such as for transforming or orienting objects.</summary>
/// <param name="position">3D vector representing the position of the camera or object.</param>
/// <param name="target">3D vector representing the target point (what the object is looking at or aiming for).</param>
/// <param name="up">3D vector representing the "up" direction, which helps define the orientation of the basis.</param>
/// <param name="axis">Dominant axis to use for the basis, one of the following values: AXIS_X, AXIS_Y, AXIS_Z, AXIS_NX, AXIS_NY, AXIS_NZ.</param>
/// <param name="x">Reference to a 3D vector to store the X axis of the calculated basis.</param>
/// <param name="y">Reference to a 3D vector to store the Y axis of the calculated basis.</param>
/// <param name="z">Reference to a 3D vector to store the Z axis of the calculated basis.</param>
UNIGINE_INLINE void calculate_basis(const vec3 &position, const vec3 &target, const vec3 &up, int axis, vec3 &x, vec3 &y, vec3 &z)
{
	switch (axis)
	{
		case AXIS_X:
			x = normalize(target - position);
			y = normalize(cross(up, x));
			z = normalize(cross(x, y));
			break;
		case AXIS_Y:
			y = normalize(target - position);
			x = normalize(cross(y, up));
			z = normalize(cross(x, y));
			break;
		case AXIS_Z:
			z = normalize(target - position);
			x = normalize(cross(up, z));
			y = normalize(cross(z, x));
			break;
		case AXIS_NX:
			x = normalize(position - target);
			y = normalize(cross(up, x));
			z = normalize(cross(x, y));
			break;
		case AXIS_NY:
			y = normalize(position - target);
			x = normalize(cross(y, up));
			z = normalize(cross(x, y));
			break;
		case AXIS_NZ:
			z = normalize(position - target);
			x = normalize(cross(up, z));
			y = normalize(cross(z, x));
			break;
	}
}
/// <summary>Returns the a transformation matrix, which puts an object to the specified position and sets it orientation to the specified target point. The forward direction vector is oriented along the specified axis (negative Z, by default). This function is similar to the lookAt() function, but instead of creating a view matrix for a camera, it creates a model matrix for positioning and orienting an object. This can be used to position objects in world space, aligning them to look at a target while maintaining a specific orientation relative to the "up" direction.</summary>
/// <param name="position">Coordinates of the object's position.</param>
/// <param name="target">Coordinates of the target point position.</param>
/// <param name="up">Direction of the up vector relative to the object.</param>
/// <param name="axis">Axis along which the forward direction vector is oriented (which axis should face the target). One of the AXIS_* values (by default it's AXIS_NZ).</param>
UNIGINE_INLINE mat4 setTo(const vec3 &position, const vec3 &target, const vec3 &up, int axis = AXIS_NZ)
{
	mat4 ret;
	vec3 x, y, z;
	calculate_basis(position, target, up, axis, x, y, z);
	ret.m00 = x.x;
	ret.m01 = y.x;
	ret.m02 = z.x;
	ret.m03 = position.x;
	ret.m10 = x.y;
	ret.m11 = y.y;
	ret.m12 = z.y;
	ret.m13 = position.y;
	ret.m20 = x.z;
	ret.m21 = y.z;
	ret.m22 = z.z;
	ret.m23 = position.z;
	ret.m30 = 0.0f;
	ret.m31 = 0.0f;
	ret.m32 = 0.0f;
	ret.m33 = 1.0f;
	return ret;
}
/// <summary>Returns a view matrix for the given eye point, target point, up and forward direction vectors. The forward direction vector is oriented along the specified axis (negative Z, by default). This function is used to create a view matrix that positions and orients a camera or object in 3D space to "look at" a given target point.</summary>
/// <param name="position">Coordinates of the eye point position.</param>
/// <param name="target">Coordinates of the target point position.</param>
/// <param name="up">Direction of the up vector.</param>
/// <param name="axis">Axis along which the forward direction vector is oriented (which axis should face the target). One of the AXIS_* values (by default it's AXIS_NZ).</param>
UNIGINE_INLINE mat4 lookAt(const vec3 &position, const vec3 &target, const vec3 &up, int axis = AXIS_NZ)
{
	mat4 ret, m0, m1;
	vec3 x, y, z;
	calculate_basis(position, target, up, axis, x, y, z);
	m0.m00 = x.x;
	m0.m01 = x.y;
	m0.m02 = x.z;
	m0.m03 = 0.0f;
	m0.m10 = y.x;
	m0.m11 = y.y;
	m0.m12 = y.z;
	m0.m13 = 0.0f;
	m0.m20 = z.x;
	m0.m21 = z.y;
	m0.m22 = z.z;
	m0.m23 = 0.0f;
	m0.m30 = 0.0f;
	m0.m31 = 0.0f;
	m0.m32 = 0.0f;
	m0.m33 = 1.0f;
	m1.setTranslate(-position);
	return mul(ret, m0, m1);
}

/// <summary>Returns a transformation matrix (cube viewing matrix) for the specified face of a cube map. Cube maps are often used in rendering for environment mapping, reflection, or skyboxes. Each face of a cube map corresponds to one of the six directions: positive and negative X, Y, and Z axes.</summary>
/// <param name="face">Face number, one of the following: 0 (X+), 1 (X-), 2 (Y+), 3 (Y-), 4 (Z+),5 (Z-).</param>
UNIGINE_INLINE const mat4 &cubeTransform(int face)
{
	static const mat4 transforms[6] = {
		rotateY(90.0f) * rotateX(180.0f),	// 0 X+
		rotateY(-90.0f) * rotateX(180.0f),	// 1 X-
		rotateX(-90.0f),					// 2 Y+
		rotateX(90.0f),						// 3 Y-
		rotateX(180.0f),					// 4 Z+
		rotateZ(180.0f),					// 5 Z-
	};
	assert(face <= 5 && face >= 0 && "cubeTransform(): bad face number");
	return transforms[face];
}

/// <summary>Returns the oblique projection matrix for the specified projection matrix to account for the specified clipping plane. This type of projection is known as oblique projection because it "clips" objects based on an arbitrary plane in space, not necessarily aligned with the view frustum. This can be useful for advanced rendering techniques like reflections or stenciling, where you may want to clip the scene or reflect it across a specific plane.</summary>
/// <param name="projection">Input projection matrix.</param>
/// <param name="plane">A 4D vector representing the equation of the clipping plane (a, b, c, d), the plane equation is ax + by + cz + d = 0.</param>
UNIGINE_INLINE mat4 obliqueProjection(const mat4 &projection, const vec4 &plane)
{
	mat4 ret, transform;
	vec4 v = plane * inverse(projection);

	float z = Math::abs(v.z);
	if (z > 1.0f)
		v /= z;

	v.w -= 1.0f;
	if (v.z < 0.0f)
		v = -v;

	transform.setIdentity();
	transform.setRow(2, v);
	return mul(ret, transform, projection);
}
/// <summary>Returns the reverse depth projection matrix — the projection matrix in which the elements that store the near and far clipping planes are multiplied by -1.</summary>
/// <param name="projection">Input projection matrix.</param>
UNIGINE_INLINE mat4 reverseDepthProjection(const mat4 &projection)
{
	mat4 ret = projection;
	ret.m20 *= -1.0f;
	ret.m21 *= -1.0f;
	ret.m22 *= -1.0f;
	ret.m23 *= -1.0f;
	return ret;
}

/// <summary>Returns a symmetric projection matrix for the specified input projection matrix. Symmetric projection ensures that the view frustum is symmetric about the x and y axes, based on the original frustum dimensions. This could be useful in cases where asymmetry in the projection matrix might cause issues, such as distortion in the rendered scene or when performing specific visual effects (e.g., mirroring or aligning views). The result is a projection matrix that maintains the same depth-related behavior as the original one but ensures symmetry in the x and y directions.</summary>
/// <param name="projection">Input projection matrix.</param>
UNIGINE_INLINE mat4 symmetryProjection(const mat4 &projection)
{
	float r = (projection.m02 + 1.0f) / projection.m00;
	float t = (projection.m12 + 1.0f) / projection.m11;
	float l = r - 2.0f / projection.m00;
	float b = t - 2.0f / projection.m11;
	float w = max(abs(r), abs(l));
	float h = max(abs(t), abs(b));

	return mat4 (
		1.0f / w, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / h, 0.0f, 0.0f,
		0.0f, 0.0f, projection.m22, -1.0f,
		0.0f, 0.0f, projection.m23, 0.0f
	);
}

/// <summary>Decomposes a given perspective projection matrix, extracting the field of view angle (FOV).</summary>
/// <param name="projection">Perspective projection matrix.</param>
UNIGINE_INLINE float decomposePerspectiveFov(const mat4 &projection)
{
	return 2.0f * atan(1.0f/projection.m11) * Consts::RAD2DEG;
}

/// <summary>Returns a value indicating if the specified projection matrix represents an orthographic projection.</summary>
UNIGINE_INLINE bool isOrthoProjection(const mat4 &projection) { return projection.m32 == 0.0f; }
/// <summary>Returns a value indicating if the specified projection matrix represents a perspective projection.</summary>
UNIGINE_INLINE bool isPerspectiveProjection(const mat4 &projection) { return projection.m32 != 0.0f; }

/// <summary>Decomposes a given projection matrix (perspective or orthographic), extracting both near and far clipping planes.</summary>
/// <param name="projection">Source projection matrix.</param>
/// <param name="znear">Reference to a variable to receive the near clipping plane distance value.</param>
/// <param name="zfar">Reference to a variable to receive the far clipping plane distance value.</param>
UNIGINE_INLINE void decomposeProjection(const mat4 &projection, float &znear, float &zfar)
{
	if (isOrthoProjection(projection))
	{
		znear = (projection.m23 + 1.0f) / projection.m22;
		zfar = (projection.m23 - 1.0f) / projection.m22;
	} else
	{
		znear = projection.m23 / (projection.m22 - 1.0f);
		zfar = projection.m23 / (projection.m22 + 1.0f);
	}
}

/// <summary>Decomposes a given projection matrix (perspective or orthographic), extracting both near and far clipping planes along with the field of view angle (FOV).</summary>
/// <param name="projection">Source projection matrix.</param>
/// <param name="znear">Reference to a variable to receive the near clipping plane distance value.</param>
/// <param name="zfar">Reference to a variable to receive the far clipping plane distance value.</param>
/// <param name="fov">Reference to a variable to receive the FOV value.</param>
UNIGINE_INLINE void decomposeProjection(const mat4 &projection, float &znear, float &zfar, float &fov)
{
	if (isOrthoProjection(projection))
	{
		znear = (projection.m23 + 1.0f) / projection.m22;
		zfar = (projection.m23 - 1.0f) / projection.m22;
		fov = 0.0f;
	} else
	{
		znear = projection.m23 / (projection.m22 - 1.0f);
		zfar = projection.m23 / (projection.m22 + 1.0f);
		fov = decomposePerspectiveFov(projection);
	}
}

/// <summary>Modifies a given projection matrix (projection) based on the near and far clipping planes (znear and zfar) and returns the updated matrix. It handles both orthographic and perspective projection types.</summary>
/// <param name="projection">Initial projection matrix (orthographic or perspective).</param>
/// <param name="znear">Distance to the near clipping plane.</param>
/// <param name="zfar">Distance to the far clipping plane.</param>
UNIGINE_INLINE mat4 composeProjection(const mat4 &projection, float znear, float zfar)
{
	mat4 proj = projection;
	if (isOrthoProjection(projection))
	{
		proj.m22 = -2.0f / (zfar - znear);
		proj.m23 = -(zfar + znear) / (zfar - znear);
	} else
	{
		proj.m22 = -(zfar + znear) / (zfar - znear);
		proj.m23 = -2.0f * zfar * znear / (zfar - znear);
	}

	return proj;
}

/// <summary>Composes a rotation matrix from the corresponding Euler angles. The Euler angles are specified in the axis rotation sequence - XYZ. It is an order of the rings in the three-axis gimbal set: X axis used as the outer ring (independent ring), while Z axis as the inner one (its rotation depends on other 2 rings). When we talk about axes in UNIGINE we assume that: X axis points to the right (pitch angle), Y axis points forward (roll angle), Z axis points up (yaw angle).</summary>
/// <param name="r">Vector, containing Euler angles, in degrees - (yaw, roll, pitch).</param>
UNIGINE_INLINE mat4 composeRotationXYZ(const vec3 &r);
/// <summary>Composes a rotation matrix from the corresponding Euler angles. The Euler angles are specified in the axis rotation sequence - XZY. It is an order of the rings in the three-axis gimbal set: X axis used as the outer ring (independent ring), while Y axis as the inner one (its rotation depends on other 2 rings). When we talk about axes in UNIGINE we assume that: X axis points to the right (pitch angle), Y axis points forward (roll angle), Z axis points up (yaw angle).</summary>
/// <param name="r">Vector, containing Euler angles, in degrees - (yaw, roll, pitch).</param>
UNIGINE_INLINE mat4 composeRotationXZY(const vec3 &r);
/// <summary>Composes a rotation matrix from the corresponding Euler angles. The Euler angles are specified in the axis rotation sequence - YXZ. It is an order of the rings in the three-axis gimbal set: Y axis used as the outer ring (independent ring), while Z axis as the inner one (its rotation depends on other 2 rings). When we talk about axes in UNIGINE we assume that: X axis points to the right (pitch angle), Y axis points forward (roll angle), Z axis points up (yaw angle).</summary>
/// <param name="r">Vector, containing Euler angles, in degrees - (yaw, roll, pitch).</param>
UNIGINE_INLINE mat4 composeRotationYXZ(const vec3 &r);
/// <summary>Composes a rotation matrix from the corresponding Euler angles. The Euler angles are specified in the axis rotation sequence - YZX. It is an order of the rings in the three-axis gimbal set: Y axis used as the outer ring (independent ring), while X axis as the inner one (its rotation depends on other 2 rings). When we talk about axes in UNIGINE we assume that: X axis points to the right (pitch angle), Y axis points forward (roll angle), Z axis points up (yaw angle).</summary>
/// <param name="r">Vector, containing Euler angles, in degrees - (yaw, roll, pitch).</param>
UNIGINE_INLINE mat4 composeRotationYZX(const vec3 &r);
/// <summary>Composes a rotation matrix from the corresponding Euler angles. The Euler angles are specified in the axis rotation sequence - ZXY. It is an order of the rings in the three-axis gimbal set: Z axis used as the outer ring (independent ring), while Y axis as the inner one (its rotation depends on other 2 rings). When we talk about axes in UNIGINE we assume that: X axis points to the right (pitch angle), Y axis points forward (roll angle), Z axis points up (yaw angle).</summary>
/// <param name="r">Vector, containing Euler angles, in degrees - (yaw, roll, pitch).</param>
UNIGINE_INLINE mat4 composeRotationZXY(const vec3 &r);
/// <summary>Composes a rotation matrix from the corresponding Euler angles. The Euler angles are specified in the axis rotation sequence - ZYX. It is an order of the rings in the three-axis gimbal set: Z axis used as the outer ring (independent ring), while X axis as the inner one (its rotation depends on other 2 rings). When we talk about axes in UNIGINE we assume that: X axis points to the right (pitch angle), Y axis points forward (roll angle), Z axis points up (yaw angle).</summary>
/// <param name="r">Vector, containing Euler angles, in degrees - (yaw, roll, pitch).</param>
UNIGINE_INLINE mat4 composeRotationZYX(const vec3 &r);

/// <summary>Decomposes a given transformation matrix into vectors representing translation and scale and a quaternion representing rotation.</summary>
/// <param name="m">Source transformation matrix to be decomposed.</param>
/// <param name="position">Reference to a 3D vector to receive the translation component.</param>
/// <param name="rot">Reference to a quaternion to receive the rotation component.</param>
/// <param name="scale">Reference to a 3D vector to receive the scale component.</param>
UNIGINE_INLINE void decomposeTransform(const mat4 &m, vec3 &position, quat &rot, vec3 &scale);
/// <summary>Decomposes a given transformation matrix into a vector representing translation and uniform scale and a quaternion representing rotation.</summary>
/// <param name="m">Source transformation matrix to be decomposed.</param>
/// <param name="position">Reference to a 4D vector (X, Y, Z, W) to receive translation and uniform scale components. (X, Y, Z) - represent translation, W = (scale.X + scale.Y + scale.z) / 3.</param>
/// <param name="rot">Reference to a quaternion to receive the rotation component.</param>
UNIGINE_INLINE void decomposeTransform(const mat4 &m, vec4 &position, quat &rot);

/// <summary>Returns the transformation matrix for the specified position, rotation and scale.</summary>
/// <param name="ret">Reference to a matric to receive the result.</param>
/// <param name="position">3D vector representing translation.</param>
/// <param name="rot">Quaternion representing rotation.</param>
/// <param name="scale">3D vector representing scale.</param>
UNIGINE_INLINE mat4 &composeTransform(mat4 &ret, const vec3 &position, const quat &rot, const vec3 &scale);
/// <summary>Returns the transformation matrix for the specified position and rotation.</summary>
/// <param name="ret">Reference to a matric to receive the result.</param>
/// <param name="position">4D vector (X, Y, Z, W) containing translation and uniform scale components. (X, Y, Z) - represent translation, W = (scale.X + scale.Y + scale.z) / 3.</param>
/// <param name="rot">Quaternion representing rotation.</param>
UNIGINE_INLINE mat4 &composeTransform(mat4 &ret, const vec4 &position, const quat &rot);

/// <summary>Returns the matrix interpolated component-wise according to the following formula: M0[i,j] + (M1[i,j] - M0[i,j]) * k.</summary>
/// <param name="ret">Reference to a matrix to receive the interpolation result.</param>
/// <param name="m0">First matrix (lower limit of the interpolation range).</param>
/// <param name="m1">Second matrix (upper limit of the interpolation range).</param>
/// <param name="k">Interpolation coefficient used to interpolate a value between M0 and M1(componentwise).</param>
UNIGINE_INLINE mat4 &lerp(mat4 &ret, const mat4 &m0, const mat4 &m1, float k);
/// <summary>Returns the matrix interpolated component-wise according to the following formula: M0[i,j] + (M1[i,j] - M0[i,j]) * k.</summary>
/// <param name="m0">First matrix (lower limit of the interpolation range).</param>
/// <param name="m1">Second matrix (upper limit of the interpolation range).</param>
/// <param name="k">Interpolation coefficient used to interpolate a value between M0 and M1(componentwise).</param>
UNIGINE_INLINE mat4 lerp(const mat4 &m0, const mat4 &m1, float k)
{
	mat4 ret;
	return lerp(ret, m0, m1, k);
}

}
}

#ifdef __GNUC__
	#pragma GCC diagnostic pop
#endif
