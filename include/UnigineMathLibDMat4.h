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
#include "UnigineMathLibMat4.h"

#ifdef __GNUC__
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wreorder"
#endif

namespace Unigine
{
namespace Math
{

struct alignas(16) dmat4
{
	UNIGINE_INLINE constexpr dmat4(
		double m00_, double m10_, double m20_,
		double m01_, double m11_, double m21_,
		double m02_, double m12_, double m22_,
		double m03_, double m13_, double m23_,
		ConstexprTag)
		: m00(m00_), m10(m10_), m20(m20_)
		, m01(m01_), m11(m11_), m21(m21_)
		, m02(m02_), m12(m12_), m22(m22_)
		, m03(m03_), m13(m13_), m23(m23_)
	{
	}
	UNIGINE_INLINE constexpr dmat4(double v,ConstexprTag)
		: m00(v), m10(v), m20(v)
		, m01(v), m11(v), m21(v)
		, m02(v), m12(v), m22(v)
		, m03(v), m13(v), m23(v)
	{
	}
	/// <summary>Constructor. Initializes the matrix using the given source matrix values.</summary>
	UNIGINE_INLINE dmat4(
		double m00_, double m10_, double m20_,
		double m01_, double m11_, double m21_,
		double m02_, double m12_, double m22_,
		double m03_, double m13_, double m23_)
		: m00(m00_), m10(m10_), m20(m20_)
		, m01(m01_), m11(m11_), m21(m21_)
		, m02(m02_), m12(m12_), m22(m22_)
		, m03(m03_), m13(m13_), m23(m23_)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Default constructor. Produces an identity matrix.</summary>
	UNIGINE_INLINE dmat4()
		: m00(1.0f), m10(0.0f), m20(0.0f)
		, m01(0.0f), m11(1.0f), m21(0.0f)
		, m02(0.0f), m12(0.0f), m22(1.0f)
		, m03(0.0f), m13(0.0f), m23(0.0f)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the matrix by copying a given source matrix.</summary>
	UNIGINE_INLINE dmat4(const dmat4 &m)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m);
	}
	/// <summary>Constructor. Initializes the matrix using a given scalar value. </summary>
	UNIGINE_INLINE explicit dmat4(double v)
		: m00(v), m10(v), m20(v)
		, m01(v), m11(v), m21(v)
		, m02(v), m12(v), m22(v)
		, m03(v), m13(v), m23(v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
	}
	/// <summary>Constructor. Initializes the matrix using a given mat2 source matrix (2x2). The matrix elements are filled using corresponding elements of the source matrix.</summary>
	UNIGINE_INLINE explicit dmat4(const mat2 &m)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m);
	}
	/// <summary>Constructor. Initializes the matrix using a given mat3 source matrix (3x3). The matrix elements are filled using corresponding elements of the source matrix.</summary>
	UNIGINE_INLINE explicit dmat4(const mat3 &m)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m);
	}
	/// <summary>Constructor. Initializes the matrix using a given source mat4 matrix (4x4). The matrix elements are filled using corresponding elements of the source matrix.</summary>
	UNIGINE_INLINE explicit dmat4(const mat4 &m)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m);
	}
	/// <summary>Constructor. Initializes the matrix using a given source quaternion.</summary>
	UNIGINE_INLINE explicit dmat4(const quat &q)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(q);
	}
	/// <summary>Constructor. Initializes the matrix using the given source matrix values.</summary>
	/// <param name="m">The values of the matrix elements as an array of 12 elements.</param>
	/// <param name="transposed">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
	UNIGINE_INLINE explicit dmat4(const dmat4x3_values &m, int transposed = 0)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m, transposed);
	}
	/// <summary>Constructor. Initializes the matrix using the given source matrix values.</summary>
	/// <param name="m">The source value storing matrix values.</param>
	/// <param name="transposed">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
	UNIGINE_INLINE explicit dmat4(const mat4x3_values &m, int transposed = 0)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m, transposed);
	}
	/// <summary>Constructor. Initializes the matrix using the given source matrix values.</summary>
	/// <param name="m">The source value storing matrix values.</param>
	/// <param name="transposed">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
	UNIGINE_INLINE explicit dmat4(const dmat4x4_values &m, int transposed = 0)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m, transposed);
	}
	/// <summary>Constructor. Initializes the matrix using the given source matrix values.</summary>
	/// <param name="m">The source value storing matrix values.</param>
	/// <param name="transposed">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
	UNIGINE_INLINE explicit dmat4(const mat4x4_values &m, int transposed = 0)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m, transposed);
	}
	/// <summary>Constructor. Initializes the matrix using a given source mat3 matrix (3x3) and a dvec3 vector.</summary>
	UNIGINE_INLINE explicit dmat4(const mat3 &m, const dvec3 &v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(m, v);
	}
	/// <summary>Constructor. Initializes the matrix using a given quaternion and a dvec3 vector.</summary>
	UNIGINE_INLINE explicit dmat4(const quat &q, const dvec3 &v)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		set(q, v);
	}
	/// <summary>Constructor. Initializes the matrix using given three dvec3 vectors, each of them filling a column.</summary>
	UNIGINE_INLINE explicit dmat4(const dvec3 &c0, const dvec3 &c1, const dvec3 &c2, const dvec3 &c3)
	{
		UNIGINE_ASSERT_ALIGNED16(this);
		m00 = c0.x;
		m01 = c1.x;
		m02 = c2.x;
		m03 = c3.x;
		m10 = c0.y;
		m11 = c1.y;
		m12 = c2.y;
		m13 = c3.y;
		m20 = c0.z;
		m21 = c1.z;
		m22 = c2.z;
		m23 = c3.z;
	}

	/// <summary>Sets a new value of the matrix element specified by row and column.</summary>
	UNIGINE_INLINE void set(int row, int column, double v)
	{
		assert((unsigned int)row < 3 && "dmat4::set(): bad row");
		assert((unsigned int)column < 4 && "dmat4::set(): bad column");
		mat[column * 3 + row] = v;
	}
	/// <summary>Sets the values of the matrix elements using the specified 2x2 matrix (starting from the upper-left corner, other elements are set to zeros, with the last element of the main diagonal set to 1).</summary>
	UNIGINE_INLINE void set(const mat2 &m)
	{
		m00 = m.m00;
		m01 = m.m01;
		m02 = 0.0;
		m03 = 0.0;
		m10 = m.m10;
		m11 = m.m11;
		m12 = 0.0;
		m13 = 0.0;
		m20 = 0.0;
		m21 = 0.0;
		m22 = 1.0;
		m23 = 0.0;
	}
	/// <summary>Sets new matrix values using a given mat3 source matrix (3x3). The matrix elements are filled using corresponding elements of the source matrix.</summary>
	UNIGINE_INLINE void set(const mat3 &m)
	{
		m00 = m.m00;
		m01 = m.m01;
		m02 = m.m02;
		m03 = 0.0;
		m10 = m.m10;
		m11 = m.m11;
		m12 = m.m12;
		m13 = 0.0;
		m20 = m.m20;
		m21 = m.m21;
		m22 = m.m22;
		m23 = 0.0;
	}
	/// <summary>Sets new matrix values using a given mat4 source matrix (4x4). The matrix elements are filled using corresponding elements of the source matrix.</summary>
	UNIGINE_INLINE void set(const mat4 &m)
	{
		m00 = m.m00;
		m01 = m.m01;
		m02 = m.m02;
		m03 = m.m03;
		m10 = m.m10;
		m11 = m.m11;
		m12 = m.m12;
		m13 = m.m13;
		m20 = m.m20;
		m21 = m.m21;
		m22 = m.m22;
		m23 = m.m23;
	}
	/// <summary>Sets the matrix equal to the specified source matrix.</summary>
	UNIGINE_INLINE void set(const dmat4 &m)
	{
		sse.v0 = m.sse.v0;
		sse.v1 = m.sse.v1;
		sse.v2 = m.sse.v2;
		sse.v3 = m.sse.v3;
		sse.v4 = m.sse.v4;
		sse.v5 = m.sse.v5;
	}
	/// <summary>Sets new matrix values using a given source quaternion.</summary>
	UNIGINE_INLINE void set(const quat &q);

	/// <summary>Sets the matrix using an array of 12 elements.</summary>
	/// <param name="m">The values of the matrix elements as an array of 12 elements.</param>
	/// <param name="transposed">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
	UNIGINE_INLINE void set(const dmat4x3_values &m, int transposed = 0)
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
		} else
		{
			m00 = m[0];
			m01 = m[3];
			m02 = m[6];
			m03 = m[9];
			m10 = m[1];
			m11 = m[4];
			m12 = m[7];
			m13 = m[10];
			m20 = m[2];
			m21 = m[5];
			m22 = m[8];
			m23 = m[11];
		}
	}

	/// <summary>Sets the matrix using the argument with float values.</summary>
	/// <param name="m">The source value storing matrix values.</param>
	/// <param name="transposed">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
	UNIGINE_INLINE void set(const mat4x3_values &m, int transposed = 0)
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
		} else
		{
			m00 = m[0];
			m01 = m[3];
			m02 = m[6];
			m03 = m[9];
			m10 = m[1];
			m11 = m[4];
			m12 = m[7];
			m13 = m[10];
			m20 = m[2];
			m21 = m[5];
			m22 = m[8];
			m23 = m[11];
		}
	}

	/// <summary>Sets the matrix with using the argument with double values.</summary>
	/// <param name="m">The source value storing matrix values.</param>
	/// <param name="transposed">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
	UNIGINE_INLINE void set(const dmat4x4_values &m, int transposed = 0)
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
		}
	}

	/// <summary>Sets the matrix using the argument with float values.</summary>
	/// <param name="m">The source value storing matrix values.</param>
	/// <param name="transposed">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
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
		}
	}

	/// <summary>Sets new matrix values using a given source mat3 matrix (3x3) and a dvec3 vector.</summary>
	UNIGINE_INLINE void set(const mat3 &m, const dvec3 &v)
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
	}
	/// <summary>Sets new matrix values using a given quaternion and a dvec3 vector.</summary>
	UNIGINE_INLINE void set(const quat &q, const dvec3 &v);

	/// <summary>Returns the matrix values by filling the specified argument.</summary>
	/// <param name="m">The values of the matrix elements as an array of 12 elements.</param>
	/// <param name="transpose">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
	UNIGINE_INLINE void get(dmat4x3_values &m, int transpose = 0) const
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
		} else
		{
			m[0] = m00;
			m[4] = m01;
			m[8] = m02;
			m[1] = m03;
			m[5] = m10;
			m[9] = m11;
			m[2] = m12;
			m[6] = m13;
			m[10] = m20;
			m[3] = m21;
			m[7] = m22;
			m[11] = m23;
		}
	}
	/// <summary>Returns the matrix values by filling the specified argument.</summary>
	/// <param name="m">The value to store matrix double values.</param>
	/// <param name="transpose">If set to 0 (by default), the matrix is specified in the column-major style; if set to 1, the matrix is transposed.</param>
	UNIGINE_INLINE void get(dmat4x4_values &m, int transpose = 0) const
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
			m[12] = 0.0;
			m[13] = 0.0;
			m[14] = 0.0;
			m[15] = 1.0;
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
			m[3] = 0.0;
			m[7] = 0.0;
			m[11] = 0.0;
			m[15] = 1.0;
		}
	}

	/// <summary>Returns the values of the matrix elements as an array of 12 elements.</summary>
	UNIGINE_INLINE dmat4x3_values &get() { return mat; }
	/// <summary>Returns the values of the matrix elements as an array of 12 elements.</summary>
	UNIGINE_INLINE const dmat4x3_values &get() const { return mat; }
	/// <summary>Returns the value of an element at the specified row and column (zero-based).</summary>
	UNIGINE_INLINE double &get(int row, int column)
	{
		assert((unsigned int)row < 3 && "dmat4::get(): bad row");
		assert((unsigned int)column < 4 && "dmat4::get(): bad column");
		return mat[column * 3 + row];
	}
	/// <summary>Returns the value of an element at the specified row and column (zero-based).</summary>
	UNIGINE_INLINE double get(int row, int column) const
	{
		assert((unsigned int)row < 3 && "dmat4::get(): bad row");
		assert((unsigned int)column < 4 && "dmat4::get(): bad column");
		return mat[column * 3 + row];
	}

	/// <summary>Performs type conversion to double *.</summary>
	UNIGINE_INLINE operator double *() { return mat; }
	/// <summary>Performs type conversion to const double *.</summary>
	UNIGINE_INLINE operator const double *() const { return mat; }
	/// <summary>Performs type conversion to void *.</summary>
	UNIGINE_INLINE operator void *() { return mat; }
	/// <summary>Performs type conversion to const void *.</summary>
	UNIGINE_INLINE operator const void *() const { return mat; }

	/// <summary>Performs array access to the matrix item reference using given item index.</summary>
	UNIGINE_INLINE double &operator[](int i)
	{
		assert((unsigned int)i < 12 && "dmat4::operator[](): bad index");
		return mat[i];
	}
	/// <summary>Performs array access to the matrix item using given item index.</summary>
	UNIGINE_INLINE double operator[](int i) const
	{
		assert((unsigned int)i < 12 && "dmat4::operator[](): bad index");
		return mat[i];
	}

	/// <summary>Performs matrix assignment. Destination matrix = Source matrix.</summary>
	UNIGINE_INLINE dmat4 &operator=(const dmat4 &m) { set(m); return *this; }
	/// <summary>Performs matrix negation.</summary>
	UNIGINE_INLINE dmat4 operator-() const
	{
		dmat4 ret;
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
		return ret;
	}

	/// <summary>Performs scalar multiplication.</summary>
	UNIGINE_INLINE dmat4 &operator*=(double v);
	/// <summary>Performs matrix multiplication.</summary>
	UNIGINE_INLINE dmat4 &operator*=(const dmat4 &m);

	/// <summary>Performs matrix addition.</summary>
	UNIGINE_INLINE dmat4 &operator+=(const dmat4 &m);
	/// <summary>Performs matrix subtraction.</summary>
	UNIGINE_INLINE dmat4 &operator-=(const dmat4 &m);

	/// <summary>Sets the specified row of the matrix using a given dvec4 vector as a source.</summary>
	UNIGINE_INLINE void setRow(int row, const dvec4 &v)
	{
		assert(row < 4 && row >= 0 && "dmat4::setRow(): bad row");
		switch (row)
		{
			case 0:
				m00 = v.x;
				m01 = v.y;
				m02 = v.z;
				m03 = v.w;
				break;
			case 1:
				m10 = v.x;
				m11 = v.y;
				m12 = v.z;
				m13 = v.w;
				break;
			case 2:
				m20 = v.x;
				m21 = v.y;
				m22 = v.z;
				m23 = v.w;
				break;
		}
	}
	/// <summary>Sets the specified row of the matrix using a given three-component dvec3 vector as a source, the last element of the row remains as is.</summary>
	UNIGINE_INLINE void setRow3(int row, const dvec3 &v)
	{
		assert(row < 4 && row >= 0 && "dmat4::setRow3(): bad row");
		switch (row)
		{
			case 0:
				m00 = v.x;
				m01 = v.y;
				m02 = v.z;
				break;
			case 1:
				m10 = v.x;
				m11 = v.y;
				m12 = v.z;
				break;
			case 2:
				m20 = v.x;
				m21 = v.y;
				m22 = v.z;
				break;
		}
	}
	/// <summary>Returns the specified matrix row.</summary>
	UNIGINE_INLINE dvec4 getRow(int row) const
	{
		assert(row < 4 && row >= 0 && "dmat4::getRow(): bad row");
		switch (row)
		{
			case 0: return dvec4(m00, m01, m02, m03);
			case 1: return dvec4(m10, m11, m12, m13);
			case 2: return dvec4(m20, m21, m22, m23);
			case 3: return dvec4(0.0, 0.0, 0.0, 1.0);
		}
		return dvec4_zero;
	}
	/// <summary>Returns the first three elements of the specified matrix row.</summary>
	UNIGINE_INLINE dvec3 getRow3(int row) const
	{
		assert(row < 4 && row >= 0 && "dmat4::getRow3(): bad row");
		switch (row)
		{
			case 0: return dvec3(m00, m01, m02);
			case 1: return dvec3(m10, m11, m12);
			case 2: return dvec3(m20, m21, m22);
			case 3: return dvec3(0.0, 0.0, 0.0);
		}
		return dvec3_zero;
	}

	/// <summary>Sets the specified column of the matrix using a given dvec4 vector as a source.</summary>
	UNIGINE_INLINE void setColumn(int column, const dvec4 &v)
	{
		assert(column < 4 && column >= 0 && "dmat4::setColumn(): bad column");
		switch (column)
		{
			case 0:
				m00 = v.x;
				m10 = v.y;
				m20 = v.z;
				break;
			case 1:
				m01 = v.x;
				m11 = v.y;
				m21 = v.z;
				break;
			case 2:
				m02 = v.x;
				m12 = v.y;
				m22 = v.z;
				break;
			case 3:
				m03 = v.x;
				m13 = v.y;
				m23 = v.z;
				break;
		}
	}
	/// <summary>Sets the specified column of the matrix using a given three-component dvec3 vector as a source.</summary>
	UNIGINE_INLINE void setColumn3(int column, const dvec3 &v)
	{
		assert(column < 4 && column >= 0 && "dmat4::setColumn3(): bad column");
		switch (column)
		{
			case 0:
				m00 = v.x;
				m10 = v.y;
				m20 = v.z;
				break;
			case 1:
				m01 = v.x;
				m11 = v.y;
				m21 = v.z;
				break;
			case 2:
				m02 = v.x;
				m12 = v.y;
				m22 = v.z;
				break;
			case 3:
				m03 = v.x;
				m13 = v.y;
				m23 = v.z;
				break;
		}
	}
	/// <summary>Returns the specified matrix column.</summary>
	UNIGINE_INLINE dvec4 getColumn(int column) const
	{
		assert(column < 4 && column >= 0 && "dmat4::getColumn(): bad column");
		switch (column)
		{
			case 0: return dvec4(m00, m10, m20, 0.0);
			case 1: return dvec4(m01, m11, m21, 0.0);
			case 2: return dvec4(m02, m12, m22, 0.0);
			case 3: return dvec4(m03, m13, m23, 1.0);
		}
		return dvec4_zero;
	}
	/// <summary>Sets the specified column of the matrix using a given three-component dvec3 vector as a source.</summary>
	UNIGINE_INLINE dvec3 getColumn3(int column) const
	{
		assert(column < 4 && column >= 0 && "dmat4::getColumn3(): bad column");
		switch (column)
		{
			case 0: return dvec3(m00, m10, m20);
			case 1: return dvec3(m01, m11, m21);
			case 2: return dvec3(m02, m12, m22);
			case 3: return dvec3(m03, m13, m23);
		}
		return dvec3_zero;
	}

	/// <summary><para>Returns the normalized vector representing the X axis. To get the left vector, use matrix.getAxisX(); To get the right vector, use -matrix.getAxisX();</summary>
	UNIGINE_INLINE dvec3 getAxisX() const { return getColumn3(0).normalize(); }
	/// <summary><para>Returns the normalized vector representing the Y axis. To get the back vector, use matrix.getAxisY(); To get the forward vector, use -matrix.getAxisY();</summary>
	UNIGINE_INLINE dvec3 getAxisY() const { return getColumn3(1).normalize(); }
	/// <summary><para>Returns the normalized vector representing the Z axis. To get the up vector, use matrix.getAxisZ(); To get the down vector, use -matrix.getAxisZ();</summary>
	UNIGINE_INLINE dvec3 getAxisZ() const { return getColumn3(2).normalize(); }

	/// <summary>Sets all matrix elements equal to 0.</summary>
	UNIGINE_INLINE void setZero()
	{
		m00 = 0.0;
		m01 = 0.0;
		m02 = 0.0;
		m03 = 0.0;
		m10 = 0.0;
		m11 = 0.0;
		m12 = 0.0;
		m13 = 0.0;
		m20 = 0.0;
		m21 = 0.0;
		m22 = 0.0;
		m23 = 0.0;
	}
	/// <summary>Sets the matrix equal to the identity matrix.</summary>
	UNIGINE_INLINE void setIdentity()
	{
		m00 = 1.0;
		m01 = 0.0;
		m02 = 0.0;
		m03 = 0.0;
		m10 = 0.0;
		m11 = 1.0;
		m12 = 0.0;
		m13 = 0.0;
		m20 = 0.0;
		m21 = 0.0;
		m22 = 1.0;
		m23 = 0.0;
	}

	/// <summary>Fills the translation matrix using a given dvec3 source vector.</summary>
	UNIGINE_INLINE void setTranslate(const dvec3 &v)
	{
		m00 = 1.0;
		m01 = 0.0;
		m02 = 0.0;
		m03 = v.x;
		m10 = 0.0;
		m11 = 1.0;
		m12 = 0.0;
		m13 = v.y;
		m20 = 0.0;
		m21 = 0.0;
		m22 = 1.0;
		m23 = v.z;
	}
	/// <summary>Returns the three-component vec3 vector, representing the translation part of the matrix.</summary>
	UNIGINE_INLINE dvec3 getTranslate() const
	{
		return dvec3(m03, m13, m23);
	}

	/// <summary>Sets the values of the rotation component of the matrix using the specified rotation axis and angle (in degrees).</summary>
	UNIGINE_INLINE void setRotate(const dvec3 &axis, double angle)
	{
		double s, c;
		Math::sincos(angle * Consts::DEG2RAD, s, c);
		dvec3 v = normalize(axis);
		double xx = v.x * v.x;
		double yy = v.y * v.y;
		double zz = v.z * v.z;
		double xy = v.x * v.y;
		double yz = v.y * v.z;
		double zx = v.z * v.x;
		double xs = v.x * s;
		double ys = v.y * s;
		double zs = v.z * s;
		m00 = (1.0 - c) * xx + c;
		m01 = (1.0 - c) * xy - zs;
		m02 = (1.0 - c) * zx + ys;
		m03 = 0.0;
		m10 = (1.0 - c) * xy + zs;
		m11 = (1.0 - c) * yy + c;
		m12 = (1.0 - c) * yz - xs;
		m13 = 0.0;
		m20 = (1.0 - c) * zx - ys;
		m21 = (1.0 - c) * yz + xs;
		m22 = (1.0 - c) * zz + c;
		m23 = 0.0;
	}
	/// <summary>Returns the quaternion, representing the rotation part of the matrix.</summary>
	UNIGINE_INLINE quat getRotate() const;

	/// <summary>Sets a rotation matrix for rotating around the X-axis by a specified angle, defined in degrees.</summary>
	UNIGINE_INLINE void setRotateX(double angle)
	{
		double s, c;
		Math::sincos(angle * Consts::DEG2RAD, s, c);
		m00 = 1.0;
		m01 = 0.0;
		m02 = 0.0;
		m03 = 0.0;
		m10 = 0.0;
		m11 = c;
		m12 = -s;
		m13 = 0.0;
		m20 = 0.0;
		m21 = s;
		m22 = c;
		m23 = 0.0;
	}
	/// <summary>Sets a rotation matrix for rotating around the Y-axis by a specified angle, defined in degrees.</summary>
	UNIGINE_INLINE void setRotateY(double angle)
	{
		double s, c;
		Math::sincos(angle * Consts::DEG2RAD, s, c);
		m00 = c;
		m01 = 0.0;
		m02 = s;
		m03 = 0.0;
		m10 = 0.0;
		m11 = 1.0;
		m12 = 0.0;
		m13 = 0.0;
		m20 = -s;
		m21 = 0.0;
		m22 = c;
		m23 = 0.0;
	}
	/// <summary>Sets a rotation matrix for rotating around the Z-axis by a specified angle, defined in degrees.</summary>
	UNIGINE_INLINE void setRotateZ(double angle)
	{
		double s, c;
		Math::sincos(angle * Consts::DEG2RAD, s, c);
		m00 = c;
		m01 = -s;
		m02 = 0.0;
		m03 = 0.0;
		m10 = s;
		m11 = c;
		m12 = 0.0;
		m13 = 0.0;
		m20 = 0.0;
		m21 = 0.0;
		m22 = 1.0;
		m23 = 0.0;
	}

	/// <summary>Sets the values of the scaling component of the matrix using the specified 3D vector.</summary>
	/// <param name="v">Vector defining the scaling factors for X, Y, and Z axes.</param>
	UNIGINE_INLINE void setScale(const dvec3 &v)
	{
		m00 = v.x;
		m01 = 0.0;
		m02 = 0.0;
		m03 = 0.0;
		m10 = 0.0;
		m11 = v.y;
		m12 = 0.0;
		m13 = 0.0;
		m20 = 0.0;
		m21 = 0.0;
		m22 = v.z;
		m23 = 0.0;
	}
	/// <summary>Returns the three-component vec3 vector, representing the scaling part of the matrix.</summary>
	UNIGINE_INLINE vec3 getScale() const
	{
		mat3 rotate, rotation = mat3(*this);
		orthonormalize(rotate, rotation);
		float sx = rotate.m00 * rotation.m00 + rotate.m10 * rotation.m10 + rotate.m20 * rotation.m20;
		float sy = rotate.m01 * rotation.m01 + rotate.m11 * rotation.m11 + rotate.m21 * rotation.m21;
		float sz = rotate.m02 * rotation.m02 + rotate.m12 * rotation.m12 + rotate.m22 * rotation.m22;
		return vec3(sx, sy, sz);
	}

	/// <summary>Returns the determinant of the given matrix.</summary>
	UNIGINE_INLINE double determinant() const
	{
		double det = m00 * (m11 * m22 - m12 * m21);
		det -= m01 * (m10 * m22 - m12 * m20);
		det += m02 * (m10 * m21 - m11 * m20);
		return det;
	}

	/// <summary>Returns a hash obtained by mixing the hash values of matrix elements.</summary>
	UNIGINE_INLINE unsigned int hash() const
	{
		unsigned long long h = hashInteger(m00);
		h = hashCombine(h, m10);
		h = hashCombine(h, m20);
		h = hashCombine(h, m01);
		h = hashCombine(h, m11);
		h = hashCombine(h, m21);
		h = hashCombine(h, m03);
		h = hashCombine(h, m13);
		h = hashCombine(h, m23);
		return hashCast64To32(h);
	}

	#ifdef USE_SSE
		struct sse_data
		{
			__m128d v0;
			__m128d v1;
			__m128d v2;
			__m128d v3;
			__m128d v4;
			__m128d v5;
		};
	#endif

	union
	{
		struct
		{
			double m00, m10, m20;
			double m01, m11, m21;
			double m02, m12, m22;
			double m03, m13, m23;
		};
		double mat[12];

		#ifdef USE_SSE
			sse_data sse; // DO NOT TOUCH UNLESS ABSOLUTELY SURE
		#endif
	};
};

constexpr dmat4 dmat4_zero(0.0, ConstexprTag{});
constexpr dmat4 dmat4_one(1.0, ConstexprTag{});
constexpr dmat4 dmat4_identity(1.0, 0.0, 0.0,
							   0.0, 1.0, 0.0,
							   0.0, 0.0, 1.0,
							   0.0, 0.0, 0.0, ConstexprTag{});

/// <summary>Returns the translation matrix for the specified translation vector.</summary>
UNIGINE_INLINE dmat4 translate(const dvec3 &v)
{
	dmat4 ret;
	ret.setTranslate(v);
	return ret;
}
/// <summary>Returns the translation matrix for the specified translation vector.</summary>
UNIGINE_INLINE dmat4 translate(const dvec4 &v)
{
	dmat4 ret;
	ret.setTranslate(dvec3(v));
	return ret;
}
/// <summary>Returns the translation matrix for the specified translation vector.</summary>
UNIGINE_INLINE dmat4 translate(const dvec2 &v)
{
	dmat4 ret;
	ret.setTranslate(dvec3(v));
	return ret;
}
/// <summary>Returns the translation matrix for the specified translation values.</summary>
UNIGINE_INLINE dmat4 translate(double x, double y = 0.0, double z = 0.0)
{
	dmat4 ret;
	ret.setTranslate(dvec3(x, y, z));
	return ret;
}

/// <summary>Returns rotation matrix for the given angle around the given axis.</summary>
UNIGINE_INLINE dmat4 rotate(const dvec3 &axis, double angle)
{
	dmat4 ret;
	ret.setRotate(axis, angle);
	return ret;
}
/// <summary>Returns rotation matrix for the given angle around the given axis.</summary>
UNIGINE_INLINE dmat4 rotate(double x, double y, double z, double angle)
{
	return rotate(dvec3(x, y, z), angle);
}

/// <summary>Returns rotation matrix for the given angle around the X axis.</summary>
UNIGINE_INLINE dmat4 rotateX(double angle)
{
	dmat4 ret;
	ret.setRotateX(angle);
	return ret;
}
/// <summary>Returns rotation matrix for the given angle around the Y axis.</summary>
UNIGINE_INLINE dmat4 rotateY(double angle)
{
	dmat4 ret;
	ret.setRotateY(angle);
	return ret;
}
/// <summary>Returns rotation matrix for the given angle around the Z axis.</summary>
UNIGINE_INLINE dmat4 rotateZ(double angle)
{
	dmat4 ret;
	ret.setRotateZ(angle);
	return ret;
}

/// <summary>Returns the scaling matrix for the specified scaling vector.</summary>
UNIGINE_INLINE dmat4 scale(const dvec3 &v)
{
	dmat4 ret;
	ret.setScale(v);
	return ret;
}
/// <summary>Returns the scaling matrix for the specified scaling vector.</summary>
UNIGINE_INLINE dmat4 scale(double x, double y, double z)
{
	return scale(dvec3(x, y, z));
}
/// <summary>Returns the scaling matrix for the scaling vector (x, x, x).</summary>
UNIGINE_INLINE dmat4 scale(double x)
{
	return scale(dvec3(x, x, x));
}

/// <summary>Returns the determinant of the given matrix.</summary>
UNIGINE_INLINE double determinant(const dmat4 &m) { return m.determinant(); }


/// <summary>Returns a value indicating whether all corresponding elements of the two given matrices are equal (element-wise conparison).</summary>
UNIGINE_INLINE int compare(const dmat4 &m0, const dmat4 &m1)
{
	return (compare(m0.m00, m1.m00) && compare(m0.m10, m1.m10) && compare(m0.m20, m1.m20) &&
			compare(m0.m01, m1.m01) && compare(m0.m11, m1.m11) && compare(m0.m21, m1.m21) &&
			compare(m0.m02, m1.m02) && compare(m0.m12, m1.m12) && compare(m0.m22, m1.m22) &&
			compare(m0.m03, m1.m03) && compare(m0.m13, m1.m13) && compare(m0.m23, m1.m23));
}
/// <summary>Returns a value indicating whether all corresponding elements of the two given matrices can be considered equal within a given tolerance (epsilon).</summary>
UNIGINE_INLINE int compare(const dmat4 &m0, const dmat4 &m1, double epsilon)
{
	return (compare(m0.m00, m1.m00, epsilon) && compare(m0.m10, m1.m10, epsilon) && compare(m0.m20, m1.m20, epsilon) &&
			compare(m0.m01, m1.m01, epsilon) && compare(m0.m11, m1.m11, epsilon) && compare(m0.m21, m1.m21, epsilon) &&
			compare(m0.m02, m1.m02, epsilon) && compare(m0.m12, m1.m12, epsilon) && compare(m0.m22, m1.m22, epsilon) &&
			compare(m0.m03, m1.m03, epsilon) && compare(m0.m13, m1.m13, epsilon) && compare(m0.m23, m1.m23, epsilon));
}
/// <summary>Matrix equal comparison.</summary>
UNIGINE_INLINE int operator==(const dmat4 &m0, const dmat4 &m1) { return compare(m0, m1); }
/// <summary>Matrix not equal comparison.</summary>
UNIGINE_INLINE int operator!=(const dmat4 &m0, const dmat4 &m1) { return !compare(m0, m1); }

/// <summary>Returns the result of a component-wise multiplication of a matrix by a scalar value by saving it in the ret argument.</summary>
UNIGINE_INLINE dmat4 &mul(dmat4 &ret, const dmat4 &m, double v)
{
	#ifdef USE_SSE
		__m128d temp = _mm_set1_pd(v);
		ret.sse.v0 = _mm_mul_pd(m.sse.v0, temp);
		ret.sse.v1 = _mm_mul_pd(m.sse.v1, temp);
		ret.sse.v2 = _mm_mul_pd(m.sse.v2, temp);
		ret.sse.v3 = _mm_mul_pd(m.sse.v3, temp);
		ret.sse.v4 = _mm_mul_pd(m.sse.v4, temp);
		ret.sse.v5 = _mm_mul_pd(m.sse.v5, temp);
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
	#endif
	return ret;
}
/// <summary>Returns the result of a multiplication of two matrices by saving it in the ret argument.</summary>
UNIGINE_INLINE dmat4 &mul(dmat4 &ret, const dmat4 &m0, const dmat4 &m1)
{
	#ifdef USE_SSE
		__m128d m0_col0 = m0.sse.v0;
		__m128d m0_col1 = m0.sse.v1;
		__m128d m0_col2 = m0.sse.v2;
		__m128d m0_col3 = m0.sse.v3;
		__m128d m0_col4 = m0.sse.v4;
		__m128d m0_col5 = m0.sse.v5;

		__m128d m1_col0 = m1.sse.v0;
		__m128d m1_col1 = m1.sse.v1;
		__m128d m1_col2 = m1.sse.v2;
		__m128d m1_col3 = m1.sse.v3;
		__m128d m1_col4 = m1.sse.v4;
		__m128d m1_col5 = m1.sse.v5;

		__m128d col_01 = _mm_shuffle_pd(m0_col0, m0_col1, _MM_PERM22(Y, X));
		__m128d col_12 = _mm_shuffle_pd(m0_col1, m0_col2, _MM_PERM22(Y, X));
		__m128d col_34 = _mm_shuffle_pd(m0_col3, m0_col4, _MM_PERM22(Y, X));

		__m128d res_0 = _mm_mul_pd(m0_col0, _MM_SWIZZLE2(m1_col0, X, X));
		__m128d res_1 = _mm_mul_pd(col_12, _MM_SWIZZLE2(m1_col0, Y, Y));
		__m128d res_2 = _mm_mul_pd(m0_col3, _MM_SWIZZLE2(m1_col1, X, X));
		ret.sse.v0 = _mm_add_pd(_mm_add_pd(res_0, res_1), res_2);

		res_0 = _mm_mul_pd(col_01, _MM_SWIZZLE2(m1_col1, Y, Y));
		res_1 = _mm_mul_pd(m0_col2, _MM_SWIZZLE2(m1_col2, X, X));
		res_2 = _mm_mul_pd(col_34, _MM_SWIZZLE2(m1_col2, Y, Y));
		ret.sse.v2 = _mm_add_pd(_mm_add_pd(res_0, res_1), res_2);

		res_0 = _mm_mul_pd(m0_col0, _MM_SWIZZLE2(m1_col3, X, X));
		res_1 = _mm_mul_pd(col_12, _MM_SWIZZLE2(m1_col3, Y, Y));
		res_2 = _mm_mul_pd(m0_col3, _MM_SWIZZLE2(m1_col4, X, X));
		ret.sse.v3 = _mm_add_pd(_mm_add_pd(res_0, res_1), res_2);

		res_0 = _mm_mul_pd(col_01, _MM_SWIZZLE2(m1_col4, Y, Y));
		res_1 = _mm_mul_pd(m0_col2, _MM_SWIZZLE2(m1_col5, X, X));
		res_2 = _mm_mul_pd(col_34, _MM_SWIZZLE2(m1_col5, Y, Y));
		ret.sse.v5 = _mm_add_pd(_mm_add_pd(res_0, res_1), _mm_add_pd(res_2, m0_col5));

		ret.m20 = m0.m20 * m1.m00 + m0.m21 * m1.m10 + m0.m22 * m1.m20;
		ret.m01 = m0.m00 * m1.m01 + m0.m01 * m1.m11 + m0.m02 * m1.m21;
		ret.m22 = m0.m20 * m1.m02 + m0.m21 * m1.m12 + m0.m22 * m1.m22;
		ret.m03 = m0.m00 * m1.m03 + m0.m01 * m1.m13 + m0.m02 * m1.m23 + m0.m03;
	#else
		ret.m00 = m0.m00 * m1.m00 + m0.m01 * m1.m10 + m0.m02 * m1.m20;
		ret.m10 = m0.m10 * m1.m00 + m0.m11 * m1.m10 + m0.m12 * m1.m20;
		ret.m20 = m0.m20 * m1.m00 + m0.m21 * m1.m10 + m0.m22 * m1.m20;
		ret.m01 = m0.m00 * m1.m01 + m0.m01 * m1.m11 + m0.m02 * m1.m21;
		ret.m11 = m0.m10 * m1.m01 + m0.m11 * m1.m11 + m0.m12 * m1.m21;
		ret.m21 = m0.m20 * m1.m01 + m0.m21 * m1.m11 + m0.m22 * m1.m21;
		ret.m02 = m0.m00 * m1.m02 + m0.m01 * m1.m12 + m0.m02 * m1.m22;
		ret.m12 = m0.m10 * m1.m02 + m0.m11 * m1.m12 + m0.m12 * m1.m22;
		ret.m22 = m0.m20 * m1.m02 + m0.m21 * m1.m12 + m0.m22 * m1.m22;
		ret.m03 = m0.m00 * m1.m03 + m0.m01 * m1.m13 + m0.m02 * m1.m23 + m0.m03;
		ret.m13 = m0.m10 * m1.m03 + m0.m11 * m1.m13 + m0.m12 * m1.m23 + m0.m13;
		ret.m23 = m0.m20 * m1.m03 + m0.m21 * m1.m13 + m0.m22 * m1.m23 + m0.m23;
	#endif
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 2D vector. This operation assumes that 2D vector is represented in homogeneous coordinates, so it treats the vector as if it were a 3D point (z=0 and w=1).</summary>
UNIGINE_INLINE vec2 &mul(vec2 &ret, const dmat4 &m, const vec2 &v)
{
	float x = v.x;
	float y = v.y;
	ret.x = (float)(m.m00 * x + m.m01 * y + m.m03);
	ret.y = (float)(m.m10 * x + m.m11 * y + m.m13);
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 2D vector and a 3x4 matrix. This operation assumes that 2D vector is represented in homogeneous coordinates, so it treats the vector as if it were a 3D point (z=0 and w=1).</summary>
UNIGINE_INLINE vec2 &mul(vec2 &ret, const vec2 &v, const dmat4 &m)
{
	float x = v.x;
	float y = v.y;
	ret.x = (float)(m.m00 * x + m.m10 * y);
	ret.y = (float)(m.m01 * x + m.m11 * y);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 3D vector. This operation assumes w=1 for the vector.</summary>
UNIGINE_INLINE vec3 &mul(vec3 &ret, const dmat4 &m, const vec3 &v)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	ret.x = (float)(m.m00 * x + m.m01 * y + m.m02 * z + m.m03);
	ret.y = (float)(m.m10 * x + m.m11 * y + m.m12 * z + m.m13);
	ret.z = (float)(m.m20 * x + m.m21 * y + m.m22 * z + m.m23);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3D vector and a 3x4 matrix. This operation assumes w=1 for the vector.</summary>
UNIGINE_INLINE vec3 &mul(vec3 &ret, const vec3 &v, const dmat4 &m)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	ret.x = (float)(m.m00 * x + m.m10 * y + m.m20 * z);
	ret.y = (float)(m.m01 * x + m.m11 * y + m.m21 * z);
	ret.z = (float)(m.m02 * x + m.m12 * y + m.m22 * z);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 4D vector.</summary>
UNIGINE_INLINE vec4 &mul(vec4 &ret, const dmat4 &m, const vec4 &v)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	float w = v.w;
	ret.x = (float)(m.m00 * x + m.m01 * y + m.m02 * z + m.m03 * w);
	ret.y = (float)(m.m10 * x + m.m11 * y + m.m12 * z + m.m13 * w);
	ret.z = (float)(m.m20 * x + m.m21 * y + m.m22 * z + m.m23 * w);
	ret.w = w;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 4D vector and a 3x4 matrix.</summary>
UNIGINE_INLINE vec4 &mul(vec4 &ret, const vec4 &v, const dmat4 &m)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	float w = v.w;
	ret.x = (float)(m.m00 * x + m.m10 * y + m.m20 * z);
	ret.y = (float)(m.m01 * x + m.m11 * y + m.m21 * z);
	ret.z = (float)(m.m02 * x + m.m12 * y + m.m22 * z);
	ret.w = (float)(m.m03 * x + m.m13 * y + m.m23 * z + w);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 2D vector. This operation assumes that 2D vector is represented in homogeneous coordinates, so it treats the vector as if it were a 3D point (z=0 and w=1).</summary>
UNIGINE_INLINE vec2 &mul(vec2 &ret, const dmat4 &m, const dvec2 &v)
{
	double x = v.x;
	double y = v.y;
	ret.x = (float)(m.m00 * x + m.m01 * y + m.m03);
	ret.y = (float)(m.m10 * x + m.m11 * y + m.m13);
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 2D vector and a 3x4 matrix. This operation assumes that 2D vector is represented in homogeneous coordinates, so it treats the vector as if it were a 3D point (z=0 and w=1).</summary>
UNIGINE_INLINE vec2 &mul(vec2 &ret, const dvec2 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	ret.x = (float)(m.m00 * x + m.m10 * y);
	ret.y = (float)(m.m01 * x + m.m11 * y);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 3D vector. This operation assumes w=1 for the vector.</summary>
UNIGINE_INLINE vec3 &mul(vec3 &ret, const dmat4 &m, const dvec3 &v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = (float)(m.m00 * x + m.m01 * y + m.m02 * z + m.m03);
	ret.y = (float)(m.m10 * x + m.m11 * y + m.m12 * z + m.m13);
	ret.z = (float)(m.m20 * x + m.m21 * y + m.m22 * z + m.m23);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3D vector and a 3x4 matrix. This operation assumes w=1 for the vector.</summary>
UNIGINE_INLINE vec3 &mul(vec3 &ret, const dvec3 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = (float)(m.m00 * x + m.m10 * y + m.m20 * z);
	ret.y = (float)(m.m01 * x + m.m11 * y + m.m21 * z);
	ret.z = (float)(m.m02 * x + m.m12 * y + m.m22 * z);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 4D vector.</summary>
UNIGINE_INLINE vec4 &mul(vec4 &ret, const dmat4 &m, const dvec4 &v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	double w = v.w;
	ret.x = (float)(m.m00 * x + m.m01 * y + m.m02 * z + m.m03 * w);
	ret.y = (float)(m.m10 * x + m.m11 * y + m.m12 * z + m.m13 * w);
	ret.z = (float)(m.m20 * x + m.m21 * y + m.m22 * z + m.m23 * w);
	ret.w = (float)w;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 4D vector and a 3x4 matrix.</summary>
UNIGINE_INLINE vec4 &mul(vec4 &ret, const dvec4 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	double w = v.w;
	ret.x = (float)(m.m00 * x + m.m10 * y + m.m20 * z);
	ret.y = (float)(m.m01 * x + m.m11 * y + m.m21 * z);
	ret.z = (float)(m.m02 * x + m.m12 * y + m.m22 * z);
	ret.w = (float)(m.m03 * x + m.m13 * y + m.m23 * z + w);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 2D vector. This operation assumes that 2D vector is represented in homogeneous coordinates, so it treats the vector as if it were a 3D point (z=0 and w=1).</summary>
UNIGINE_INLINE dvec2 &mul(dvec2 &ret, const dmat4 &m, const dvec2 &v)
{
	double x = v.x;
	double y = v.y;
	ret.x = m.m00 * x + m.m01 * y + m.m03;
	ret.y = m.m10 * x + m.m11 * y + m.m13;
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 2D vector and a 3x4 matrix. This operation assumes that 2D vector is represented in homogeneous coordinates, so it treats the vector as if it were a 3D point (z=0 and w=1).</summary>
UNIGINE_INLINE dvec2 &mul(dvec2 &ret, const dvec2 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	ret.x = m.m00 * x + m.m10 * y;
	ret.y = m.m01 * x + m.m11 * y;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 3D vector. This operation assumes w=1 for the vector.</summary>
UNIGINE_INLINE dvec3 &mul(dvec3 &ret, const dmat4 &m, const dvec3 &v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = m.m00 * x + m.m01 * y + m.m02 * z + m.m03;
	ret.y = m.m10 * x + m.m11 * y + m.m12 * z + m.m13;
	ret.z = m.m20 * x + m.m21 * y + m.m22 * z + m.m23;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3D vector and a 3x4 matrix. This operation assumes w=1 for the vector.</summary>
UNIGINE_INLINE dvec3 &mul(dvec3 &ret, const dvec3 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = m.m00 * x + m.m10 * y + m.m20 * z;
	ret.y = m.m01 * x + m.m11 * y + m.m21 * z;
	ret.z = m.m02 * x + m.m12 * y + m.m22 * z;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 4D vector.</summary>
UNIGINE_INLINE dvec4 &mul(dvec4 &ret, const dmat4 &m, const dvec4 &v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	double w = v.w;
	ret.x = m.m00 * x + m.m01 * y + m.m02 * z + m.m03 * w;
	ret.y = m.m10 * x + m.m11 * y + m.m12 * z + m.m13 * w;
	ret.z = m.m20 * x + m.m21 * y + m.m22 * z + m.m23 * w;
	ret.w = w;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 4D vector and a 3x4 matrix.</summary>
UNIGINE_INLINE dvec4 &mul(dvec4 &ret, const dvec4 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	double w = v.w;
	ret.x = m.m00 * x + m.m10 * y + m.m20 * z;
	ret.y = m.m01 * x + m.m11 * y + m.m21 * z;
	ret.z = m.m02 * x + m.m12 * y + m.m22 * z;
	ret.w = m.m03 * x + m.m13 * y + m.m23 * z + w;
	return ret;
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dmat4 operator*(const dmat4 &m, double v)
{
	dmat4 ret;
	return mul(ret, m, v);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec2 operator*(const dmat4 &m, const vec2 &v)
{
	vec2 ret;
	return mul(ret, m, v);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec2 operator*(const vec2 &v, const dmat4 &m)
{
	vec2 ret;
	return mul(ret, v, m);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec3 operator*(const dmat4 &m, const vec3 &v)
{
	vec3 ret;
	return mul(ret, m, v);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec3 operator*(const vec3 &v, const dmat4 &m)
{
	vec3 ret;
	return mul(ret, v, m);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec4 operator*(const dmat4 &m, const vec4 &v)
{
	vec4 ret;
	return mul(ret, m, v);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE vec4 operator*(const vec4 &v, const dmat4 &m)
{
	vec4 ret;
	return mul(ret, v, m);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dvec2 operator*(const dmat4 &m, const dvec2 &v)
{
	dvec2 ret;
	return mul(ret, m, v);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dvec2 operator*(const dvec2 &v, const dmat4 &m)
{
	dvec2 ret;
	return mul(ret, v, m);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dvec3 operator*(const dmat4 &m, const dvec3 &v)
{
	dvec3 ret;
	return mul(ret, m, v);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dvec3 operator*(const dvec3 &v, const dmat4 &m)
{
	dvec3 ret;
	return mul(ret, v, m);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dvec4 operator*(const dmat4 &m, const dvec4 &v)
{
	dvec4 ret;
	return mul(ret, m, v);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dvec4 operator*(const dvec4 &v, const dmat4 &m)
{
	dvec4 ret;
	return mul(ret, v, m);
}
/// <summary>Multiplication operator.</summary>
UNIGINE_INLINE dmat4 operator*(const dmat4 &m0, const dmat4 &m1)
{
	dmat4 ret;
	return mul(ret, m0, m1);
}
/// <summary>Performs scalar multiplication.</summary>
UNIGINE_INLINE dmat4 &dmat4::operator*=(double v)
{
	return mul(*this, *this, v);
}
/// <summary>Performs matrix multiplication.</summary>
UNIGINE_INLINE dmat4 &dmat4::operator*=(const dmat4 &m)
{
	return mul(*this, dmat4(*this), m);
}


/// <summary>Returns the result of matrix-vector multiplication for a 2D vector and a 3x4 matrix. The method only considers the top-left 2x2 portion of the matrix.</summary>
UNIGINE_INLINE vec2 &mul3(vec2 &ret, const dmat4 &m, const vec2 &v)
{
	float x = v.x;
	float y = v.y;
	ret.x = (float)(m.m00 * x + m.m01 * y);
	ret.y = (float)(m.m10 * x + m.m11 * y);
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 3x4 matrix and a 2D vector. The method only considers the top-left 2x2 portion of the matrix.</summary>
UNIGINE_INLINE vec2 &mul3(vec2 &ret, const vec2 &v, const dmat4 &m)
{
	float x = v.x;
	float y = v.y;
	ret.x = (float)(m.m00 * x + m.m10 * y);
	ret.y = (float)(m.m01 * x + m.m11 * y);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3D vector and a 3x4 matrix. The method only considers the top-left 3x3 portion of the matrix.</summary>
UNIGINE_INLINE vec3 &mul3(vec3 &ret, const dmat4 &m, const vec3 &v)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	ret.x = (float)(m.m00 * x + m.m01 * y + m.m02 * z);
	ret.y = (float)(m.m10 * x + m.m11 * y + m.m12 * z);
	ret.z = (float)(m.m20 * x + m.m21 * y + m.m22 * z);
	return ret;
}
//// <summary>Returns the result of vector-matrix multiplication for a 3x4 matrix and a 3D vector. The method only considers the top-left 3x3 portion of the matrix.</summary>
UNIGINE_INLINE vec3 &mul3(vec3 &ret, const vec3 &v, const dmat4 &m)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	ret.x = (float)(m.m00 * x + m.m10 * y + m.m20 * z);
	ret.y = (float)(m.m01 * x + m.m11 * y + m.m21 * z);
	ret.z = (float)(m.m02 * x + m.m12 * y + m.m22 * z);
	return ret;
}
/// <summary>Transforms a 3D vector using a 3x4 matrix ignoring the fourth component of both the vector and the matrix (only the first three components are modified). Can be used to apply rotations and scalings to 3D points or direction vectors, ensuring the fourth component does not interfere with the transformation; is often used in physics simulations and animations where the position is irrelevant to certain calculations; useful in rendering calculations, where only 3D transformations are required without affecting the homogenous coordinate.</summary>
UNIGINE_INLINE vec4 &mul3(vec4 &ret, const dmat4 &m, const vec4 &v)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	ret.x = (float)(m.m00 * x + m.m01 * y + m.m02 * z);
	ret.y = (float)(m.m10 * x + m.m11 * y + m.m12 * z);
	ret.z = (float)(m.m20 * x + m.m21 * y + m.m22 * z);
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 4D vector and a 3x4 matrix (only the first three components are modified).</summary>
UNIGINE_INLINE vec4 &mul3(vec4 &ret, const vec4 &v, const dmat4 &m)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	ret.x = (float)(m.m00 * x + m.m10 * y + m.m20 * z);
	ret.y = (float)(m.m01 * x + m.m11 * y + m.m21 * z);
	ret.z = (float)(m.m02 * x + m.m12 * y + m.m22 * z);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 2D vector. The method only considers the top-left 2x2 portion of the matrix.</summary>
UNIGINE_INLINE vec2 &mul3(vec2 &ret, const dmat4 &m, const dvec2 &v)
{
	double x = v.x;
	double y = v.y;
	ret.x = (float)(m.m00 * x + m.m01 * y);
	ret.y = (float)(m.m10 * x + m.m11 * y);
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 2D vector and a 3x4 matrix. The method only considers the top-left 2x2 portion of the matrix.</summary>
UNIGINE_INLINE vec2 &mul3(vec2 &ret, const dvec2 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	ret.x = (float)(m.m00 * x + m.m10 * y);
	ret.y = (float)(m.m01 * x + m.m11 * y);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 3D vector. The method only considers the top-left 3x3 portion of the matrix.</summary>
UNIGINE_INLINE vec3 &mul3(vec3 &ret, const dmat4 &m, const dvec3 &v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = (float)(m.m00 * x + m.m01 * y + m.m02 * z);
	ret.y = (float)(m.m10 * x + m.m11 * y + m.m12 * z);
	ret.z = (float)(m.m20 * x + m.m21 * y + m.m22 * z);
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 3D vector and a 3x4 matrix. The method only considers the top-left 3x3 portion of the matrix.</summary>
UNIGINE_INLINE vec3 &mul3(vec3 &ret, const dvec3 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = (float)(m.m00 * x + m.m10 * y + m.m20 * z);
	ret.y = (float)(m.m01 * x + m.m11 * y + m.m21 * z);
	ret.z = (float)(m.m02 * x + m.m12 * y + m.m22 * z);
	return ret;
}
/// <summary>Transforms a 3D vector using a 3x4 matrix ignoring the fourth component of both the vector and the matrix (only the first three components are modified). Can be used to apply rotations and scalings to 3D points or direction vectors, ensuring the fourth component does not interfere with the transformation; is often used in physics simulations and animations where the position is irrelevant to certain calculations; useful in rendering calculations, where only 3D transformations are required without affecting the homogenous coordinate.</summary>
UNIGINE_INLINE vec4 &mul3(vec4 &ret, const dmat4 &m, const dvec4 &v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = (float)(m.m00 * x + m.m01 * y + m.m02 * z);
	ret.y = (float)(m.m10 * x + m.m11 * y + m.m12 * z);
	ret.z = (float)(m.m20 * x + m.m21 * y + m.m22 * z);
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 4D vector and a 3x4 matrix (only the first three components are modified).</summary>
UNIGINE_INLINE vec4 &mul3(vec4 &ret, const dvec4 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = (float)(m.m00 * x + m.m10 * y + m.m20 * z);
	ret.y = (float)(m.m01 * x + m.m11 * y + m.m21 * z);
	ret.z = (float)(m.m02 * x + m.m12 * y + m.m22 * z);
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 2D vector. The method only considers the top-left 2x2 portion of the matrix.</summary>
UNIGINE_INLINE dvec2 &mul3(dvec2 &ret, const dmat4 &m, const dvec2 &v)
{
	double x = v.x;
	double y = v.y;
	ret.x = m.m00 * x + m.m01 * y;
	ret.y = m.m10 * x + m.m11 * y;
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 2D vector and a 3x4 matrix. The method only considers the top-left 2x2 portion of the matrix.</summary>
UNIGINE_INLINE dvec2 &mul3(dvec2 &ret, const dvec2 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	ret.x = m.m00 * x + m.m10 * y;
	ret.y = m.m01 * x + m.m11 * y;
	return ret;
}
/// <summary>Returns the result of matrix-vector multiplication for a 3x4 matrix and a 3D vector. The method only considers the top-left 3x3 portion of the matrix.</summary>
UNIGINE_INLINE dvec3 &mul3(dvec3 &ret, const dmat4 &m, const dvec3 &v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = m.m00 * x + m.m01 * y + m.m02 * z;
	ret.y = m.m10 * x + m.m11 * y + m.m12 * z;
	ret.z = m.m20 * x + m.m21 * y + m.m22 * z;
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 3D vector and a 3x4 matrix. The method only considers the top-left 3x3 portion of the matrix.</summary>
UNIGINE_INLINE dvec3 &mul3(dvec3 &ret, const dvec3 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = m.m00 * x + m.m10 * y + m.m20 * z;
	ret.y = m.m01 * x + m.m11 * y + m.m21 * z;
	ret.z = m.m02 * x + m.m12 * y + m.m22 * z;
	return ret;
}
/// <summary>Transforms a 3D vector using a 3x4 matrix ignoring the fourth component of both the vector and the matrix (only the first three components are modified). Can be used to apply rotations and scalings to 3D points or direction vectors, ensuring the fourth component does not interfere with the transformation; is often used in physics simulations and animations where the position is irrelevant to certain calculations; useful in rendering calculations, where only 3D transformations are required without affecting the homogenous coordinate.</summary>
UNIGINE_INLINE dvec4 &mul3(dvec4 &ret, const dmat4 &m, const dvec4 &v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = m.m00 * x + m.m01 * y + m.m02 * z;
	ret.y = m.m10 * x + m.m11 * y + m.m12 * z;
	ret.z = m.m20 * x + m.m21 * y + m.m22 * z;
	return ret;
}
/// <summary>Returns the result of vector-matrix multiplication for a 4D vector and a 3x4 matrix (only the first three components are modified).</summary>
UNIGINE_INLINE dvec4 &mul3(dvec4 &ret, const dvec4 &v, const dmat4 &m)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	ret.x = m.m00 * x + m.m10 * y + m.m20 * z;
	ret.y = m.m01 * x + m.m11 * y + m.m21 * z;
	ret.z = m.m02 * x + m.m12 * y + m.m22 * z;
	return ret;
}
/// <summary>Performs matrix multiplication m0 x m1. The method only considers the top-left 3x3 portions of the matrices.</summary>
UNIGINE_INLINE dmat4 &mul3(dmat4 &ret, const dmat4 &m0, const dmat4 &m1)
{
	#ifdef USE_SSE
		__m128d m0_col0 = m0.sse.v0;
		__m128d m0_col1 = m0.sse.v1;
		__m128d m0_col2 = m0.sse.v2;
		__m128d m0_col3 = m0.sse.v3;
		__m128d m0_col4 = m0.sse.v4;

		__m128d m1_col0 = m1.sse.v0;
		__m128d m1_col1 = m1.sse.v1;
		__m128d m1_col2 = m1.sse.v2;
		__m128d m1_col3 = m1.sse.v3;
		__m128d m1_col4 = m1.sse.v4;

		__m128d col_01 = _mm_shuffle_pd(m0_col0, m0_col1, _MM_PERM22(Y, X));
		__m128d col_12 = _mm_shuffle_pd(m0_col1, m0_col2, _MM_PERM22(Y, X));
		__m128d col_34 = _mm_shuffle_pd(m0_col3, m0_col4, _MM_PERM22(Y, X));

		__m128d res_0 = _mm_mul_pd(m0_col0, _MM_SWIZZLE2(m1_col0, X, X));
		__m128d res_1 = _mm_mul_pd(col_12, _MM_SWIZZLE2(m1_col0, Y, Y));
		__m128d res_2 = _mm_mul_pd(m0_col3, _MM_SWIZZLE2(m1_col1, X, X));
		ret.sse.v0 = _mm_add_pd(_mm_add_pd(res_0, res_1), res_2);

		res_0 = _mm_mul_pd(col_01, _MM_SWIZZLE2(m1_col1, Y, Y));
		res_1 = _mm_mul_pd(m0_col2, _MM_SWIZZLE2(m1_col2, X, X));
		res_2 = _mm_mul_pd(col_34, _MM_SWIZZLE2(m1_col2, Y, Y));
		ret.sse.v2 = _mm_add_pd(_mm_add_pd(res_0, res_1), res_2);

		res_0 = _mm_mul_pd(m0_col0, _MM_SWIZZLE2(m1_col3, X, X));
		res_1 = _mm_mul_pd(col_12, _MM_SWIZZLE2(m1_col3, Y, Y));
		res_2 = _mm_mul_pd(m0_col3, _MM_SWIZZLE2(m1_col4, X, X));
		ret.sse.v3 = _mm_add_pd(_mm_add_pd(res_0, res_1), res_2);

		ret.m20 = m0.m20 * m1.m00 + m0.m21 * m1.m10 + m0.m22 * m1.m20;
		ret.m01 = m0.m00 * m1.m01 + m0.m01 * m1.m11 + m0.m02 * m1.m21;
		ret.m22 = m0.m20 * m1.m02 + m0.m21 * m1.m12 + m0.m22 * m1.m22;
	#else
		ret.m00 = m0.m00 * m1.m00 + m0.m01 * m1.m10 + m0.m02 * m1.m20;
		ret.m10 = m0.m10 * m1.m00 + m0.m11 * m1.m10 + m0.m12 * m1.m20;
		ret.m20 = m0.m20 * m1.m00 + m0.m21 * m1.m10 + m0.m22 * m1.m20;
		ret.m01 = m0.m00 * m1.m01 + m0.m01 * m1.m11 + m0.m02 * m1.m21;
		ret.m11 = m0.m10 * m1.m01 + m0.m11 * m1.m11 + m0.m12 * m1.m21;
		ret.m21 = m0.m20 * m1.m01 + m0.m21 * m1.m11 + m0.m22 * m1.m21;
		ret.m02 = m0.m00 * m1.m02 + m0.m01 * m1.m12 + m0.m02 * m1.m22;
		ret.m12 = m0.m10 * m1.m02 + m0.m11 * m1.m12 + m0.m12 * m1.m22;
		ret.m22 = m0.m20 * m1.m02 + m0.m21 * m1.m12 + m0.m22 * m1.m22;
	#endif
	return ret;
}

/// <summary>Returns the result of matrix multiplication.</summary>
UNIGINE_INLINE dmat4 &mul4(dmat4 &ret, const dmat4 &m0, const dmat4 &m1)
{
	return mul(ret, m0, m1);
}
/// <summary>Multiplies the specified matrix by a given 3D vector (matrix-vector multiplication).</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to be multiplied by the vector.</param>
/// <param name="v">Vector-multiplier.</param>
UNIGINE_INLINE dmat4 &mult(dmat4 &ret, const dmat4 &m, const dvec3 &v)
{
	ret.m00 = m.m00;
	ret.m01 = m.m01;
	ret.m02 = m.m02;
	ret.m10 = m.m10;
	ret.m11 = m.m11;
	ret.m12 = m.m12;
	ret.m20 = m.m20;
	ret.m21 = m.m21;
	ret.m22 = m.m22;
	ret.m03 = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03;
	ret.m13 = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13;
	ret.m23 = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23;
	return ret;
}

/// <summary>Performs matrix addition (element-wise).</summary>
UNIGINE_INLINE dmat4 &add(dmat4 &ret, const dmat4 &m0, const dmat4 &m1)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_add_pd(m0.sse.v0, m1.sse.v0);
		ret.sse.v1 = _mm_add_pd(m0.sse.v1, m1.sse.v1);
		ret.sse.v2 = _mm_add_pd(m0.sse.v2, m1.sse.v2);
		ret.sse.v3 = _mm_add_pd(m0.sse.v3, m1.sse.v3);
		ret.sse.v4 = _mm_add_pd(m0.sse.v4, m1.sse.v4);
		ret.sse.v5 = _mm_add_pd(m0.sse.v5, m1.sse.v5);
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
	#endif
	return ret;
}
/// <summary>Performs matrix addition (element-wise).</summary>
UNIGINE_INLINE dmat4 operator+(const dmat4 &m0, const dmat4 &m1)
{
	dmat4 ret;
	return add(ret, m0, m1);
}
/// <summary>Performs matrix addition (element-wise).</summary>
UNIGINE_INLINE dmat4 &dmat4::operator+=(const dmat4 &m)
{
	return add(*this, *this, m);
}

/// <summary>Performs matrix subtraction (element-wise).</summary>
UNIGINE_INLINE dmat4 &sub(dmat4 &ret, const dmat4 &m0, const dmat4 &m1)
{
	#ifdef USE_SSE
		ret.sse.v0 = _mm_sub_pd(m0.sse.v0, m1.sse.v0);
		ret.sse.v1 = _mm_sub_pd(m0.sse.v1, m1.sse.v1);
		ret.sse.v2 = _mm_sub_pd(m0.sse.v2, m1.sse.v2);
		ret.sse.v3 = _mm_sub_pd(m0.sse.v3, m1.sse.v3);
		ret.sse.v4 = _mm_sub_pd(m0.sse.v4, m1.sse.v4);
		ret.sse.v5 = _mm_sub_pd(m0.sse.v5, m1.sse.v5);
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
	#endif
	return ret;
}
/// <summary>Performs matrix subtraction (element-wise).</summary>
UNIGINE_INLINE dmat4 &dmat4::operator-=(const dmat4 &m)
{
	return sub(*this, *this, m);
}
/// <summary>Performs matrix subtraction (element-wise).</summary>
UNIGINE_INLINE dmat4 operator-(const dmat4 &m0, const dmat4 &m1)
{
	dmat4 ret;
	return sub(ret, m0, m1);
}

/// <summary>Orthonormalizes the specified matrix - normalizes its direction vectors and ensures they are orthogonal.</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to be orthonormalized.</param>
UNIGINE_INLINE dmat4 &orthonormalize(dmat4 &ret, const dmat4 &m)
{
	dvec3 x = dvec3(m.m00, m.m10, m.m20);
	dvec3 y = dvec3(m.m01, m.m11, m.m21);
	dvec3 z = cross(x, y);
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
	return ret;
}
/// <summary>Orthonormalizes the specified matrix - normalizes its direction vectors and ensures they are orthogonal.</summary>
/// <param name="m">Matrix to be orthonormalized.</param>
UNIGINE_INLINE dmat4 orthonormalize(const dmat4 &m)
{
	dmat4 ret;
	return orthonormalize(ret, m);
}

/// <summary>Returns inverse of the specified matrix. The inverse of a matrix is a matrix that if multiplied by the original would result in identity matrix: AA' = A'A = I.</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to be inverted.</param>
UNIGINE_INLINE dmat4 &inverse(dmat4 &ret, const dmat4 &m)
{
	double idet = Math::rcp(determinant(m));
	ret.m00 = (m.m11 * m.m22 - m.m12 * m.m21) * idet;
	ret.m10 = -(m.m10 * m.m22 - m.m12 * m.m20) * idet;
	ret.m20 = (m.m10 * m.m21 - m.m11 * m.m20) * idet;
	ret.m01 = -(m.m01 * m.m22 - m.m02 * m.m21) * idet;
	ret.m11 = (m.m00 * m.m22 - m.m02 * m.m20) * idet;
	ret.m21 = -(m.m00 * m.m21 - m.m01 * m.m20) * idet;
	ret.m02 = (m.m01 * m.m12 - m.m02 * m.m11) * idet;
	ret.m12 = -(m.m00 * m.m12 - m.m02 * m.m10) * idet;
	ret.m22 = (m.m00 * m.m11 - m.m01 * m.m10) * idet;
	ret.m03 = -(ret.m00 * m.m03 + ret.m01 * m.m13 + ret.m02 * m.m23);
	ret.m13 = -(ret.m10 * m.m03 + ret.m11 * m.m13 + ret.m12 * m.m23);
	ret.m23 = -(ret.m20 * m.m03 + ret.m21 * m.m13 + ret.m22 * m.m23);
	return ret;
}
/// <summary>Returns inverse of the specified matrix. The inverse of a matrix is a matrix that if multiplied by the original would result in identity matrix: AA' = A'A = I.</summary>
/// <param name="m">Matrix to be inverted.</param>
UNIGINE_INLINE dmat4 inverse(const dmat4 &m)
{
	dmat4 ret;
	return inverse(ret, m);
}

/// <summary>Inverts a matrix that consists of a 3×4 sub-matrix (upper-left) and a translation vector. The last row of the matrix is ignored. Compared to the inverse() function, this one is a bit faster and, which is more important, more stable. A matrix suitable for such inversion looks like this:
/// m00	m10	m20	m30
/// m01	m11	m21	m31
/// m02	m12	m22	m32
/// 0	0	0	1</summary>
/// <param name="ret">Reference to a matrix to receive the result.</param>
/// <param name="m">Matrix to be inverted.</param>
UNIGINE_INLINE dmat4 &inverse4(dmat4 &ret, const dmat4 &m)
{
	return inverse(ret, m);
}
/// <summary>Inverts a matrix that consists of a 3×4 sub-matrix (upper-left) and a translation vector. The last row of the matrix is ignored. Compared to the inverse() function, this one is a bit faster and, which is more important, more stable. A matrix suitable for such inversion looks like this:
/// m00	m10	m20	m30
/// m01	m11	m21	m31
/// m02	m12	m22	m32
/// 0	0	0	1</summary>
UNIGINE_INLINE dmat4 inverse4(const dmat4 &m)
{
	dmat4 ret;
	return inverse4(ret, m);
}

/// <summary>Returns the rotation matrix for the given source matrix ignoring the translation column.</summary>
UNIGINE_INLINE dmat4 &rotation(dmat4 &ret, const dmat4 &m)
{
	ret.m00 = m.m00;
	ret.m01 = m.m01;
	ret.m02 = m.m02;
	ret.m03 = 0.0;
	ret.m10 = m.m10;
	ret.m11 = m.m11;
	ret.m12 = m.m12;
	ret.m13 = 0.0;
	ret.m20 = m.m20;
	ret.m21 = m.m21;
	ret.m22 = m.m22;
	ret.m23 = 0.0;
	return ret;
}
/// <summary>Returns the rotation matrix for the given source matrix ignoring the translation column.</summary>
UNIGINE_INLINE dmat4 rotation(const dmat4 &m)
{
	dmat4 ret;
	return rotation(ret, m);
}

/// <summary>Reflects a given vector about a plane with the specified normal vector.</summary>
UNIGINE_INLINE dmat4 reflect(const dvec4 &plane)
{
	dmat4 ret;
	double x = plane.x;
	double y = plane.y;
	double z = plane.z;
	double x2 = x * 2.0;
	double y2 = y * 2.0;
	double z2 = z * 2.0;
	ret.m00 = 1.0 - x * x2;
	ret.m01 = -y * x2;
	ret.m02 = -z * x2;
	ret.m03 = -plane.w * x2;
	ret.m10 = -x * y2;
	ret.m11 = 1.0 - y * y2;
	ret.m12 = -z * y2;
	ret.m13 = -plane.w * y2;
	ret.m20 = -x * z2;
	ret.m21 = -y * z2;
	ret.m22 = 1.0 - z * z2;
	ret.m23 = -plane.w * z2;
	return ret;
}

/// <summary>Computes a local coordinate system (or basis) consisting of three perpendicular vectors (x, y, z) based on the input position, target, and up vectors, as well as the axis specified. This is commonly used to generate a reference frame in 3D space, such as for transforming or orienting objects.</summary>
/// <param name="position">3D vector representing the position of the camera or object.</param>
/// <param name="target">3D vector representing the target point (what the object is looking at or aiming for).</param>
/// <param name="up">3D vector representing the "up" direction, which helps define the orientation of the basis.</param>
/// <param name="axis">Dominant axis to use for the basis, one of the following values: AXIS_X, AXIS_Y, AXIS_Z, AXIS_NX, AXIS_NY, AXIS_NZ.</param>
/// <param name="x">Reference to a 3D vector to store the X axis of the calculated basis.</param>
/// <param name="y">Reference to a 3D vector to store the Y axis of the calculated basis.</param>
/// <param name="z">Reference to a 3D vector to store the Z axis of the calculated basis.</param>
UNIGINE_INLINE void calculate_basis(const dvec3 &position, const dvec3 &target, const vec3 &up, int axis, vec3 &x, vec3 &y, vec3 &z)
{
	switch (axis)
	{
		case AXIS_X:
			x = normalize(vec3(target - position));
			y = normalize(cross(up, x));
			z = normalize(cross(x, y));
			break;
		case AXIS_Y:
			y = normalize(vec3(target - position));
			x = normalize(cross(y, up));
			z = normalize(cross(x, y));
			break;
		case AXIS_Z:
			z = normalize(vec3(target - position));
			x = normalize(cross(up, z));
			y = normalize(cross(z, x));
			break;
		case AXIS_NX:
			x = normalize(vec3(position - target));
			y = normalize(cross(up, x));
			z = normalize(cross(x, y));
			break;
		case AXIS_NY:
			y = normalize(vec3(position - target));
			x = normalize(cross(y, up));
			z = normalize(cross(x, y));
			break;
		case AXIS_NZ:
			z = normalize(vec3(position - target));
			x = normalize(cross(up, z));
			y = normalize(cross(z, x));
			break;
	}
}
/// <summary>Returns the transformation matrix, which puts an object to the specified position and sets it orientation to the specified target point. At that, the forward direction vector is pointed along the specified axis (negative Z, by default). This function is similar to the lookAt() function, but instead of creating a view matrix for a camera, it creates a model matrix for positioning and orienting an object. This can be used to position objects in world space, aligning them to look at a target while maintaining a specific orientation relative to the "up" direction.</summary>
/// <param name="position">Position of the eye point.</param>
/// <param name="target">Position of the target point.</param>
/// <param name="up">Direction of the up vector.</param>
/// <param name="axis">Axis along which the forward direction vector is pointed. The default is negative Z.</param>
UNIGINE_INLINE dmat4 setTo(const dvec3 &position, const dvec3 &target, const vec3 &up, int axis = AXIS_NZ)
{
	dmat4 ret;
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
	return ret;
}
/// <summary>Returns the viewing matrix for the given eye point, target point, up and forward direction vectors. The forward direction vector is pointed along the specified axis (negative Z, by default). This function is used to create a view matrix that positions and orients a camera or object in 3D space to "look at" a given target point.</summary>
/// <param name="position">Position of the eye point.</param>
/// <param name="target">Position of the target point.</param>
/// <param name="up">Direction of the up vector.</param>
/// <param name="axis">Axis along which the forward direction vector is pointed. The default is negative Z.</param>
UNIGINE_INLINE dmat4 lookAt(const dvec3 &position, const dvec3 &target, const vec3 &up, int axis = AXIS_NZ)
{
	dmat4 ret, m0, m1;
	vec3 x, y, z;
	calculate_basis(position, target, up, axis, x, y, z);
	m0.m00 = x.x;
	m0.m01 = x.y;
	m0.m02 = x.z;
	m0.m03 = 0.0;
	m0.m10 = y.x;
	m0.m11 = y.y;
	m0.m12 = y.z;
	m0.m13 = 0.0;
	m0.m20 = z.x;
	m0.m21 = z.y;
	m0.m22 = z.z;
	m0.m23 = 0.0;
	m1.setTranslate(-position);
	return mul(ret, m0, m1);
}

/// <summary>Interpolates the matrix component values according to the formula v0 + (v1 - v0) * k and saves the result in the ret argument.</summary>
UNIGINE_INLINE dmat4 &lerp(dmat4 &ret, const dmat4 &m0, const dmat4 &m1, double k);
/// <summary>Returns the matrix component values interpolated according to the formula v0 + (v1 - v0) * k.</summary>
UNIGINE_INLINE dmat4 lerp(const dmat4 &m0, const dmat4 &m1, double k)
{
	dmat4 ret;
	return lerp(ret, m0, m1, k);
}

/// <summary>Decomposes a given transformation matrix into the vectors representing position and scale and a quaternion representing rotation.</summary>
UNIGINE_INLINE void decomposeTransform(const dmat4 &m, dvec3 &position, quat &rot, vec3 &scale);
/// <summary>Returns the transformation matrix for the specified position, rotation and scale.</summary>
UNIGINE_INLINE dmat4 &composeTransform(dmat4 &ret, const dvec3 &position, const quat &rot, const vec3 &scale);

}
}

#ifdef __GNUC__
	#pragma GCC diagnostic pop
#endif
