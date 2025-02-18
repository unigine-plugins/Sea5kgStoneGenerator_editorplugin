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

#include "UnigineBase.h"
#include "UniginePair.h"
#include "UnigineString.h"
#include "UnigineVector.h"
#include "UnigineSort.h"
#include <stdint.h>

#ifndef USE_SSE
	#define USE_SSE
#endif

#ifdef USE_SSE
	#include <emmintrin.h>
	#include <xmmintrin.h>
	#include <smmintrin.h>
#endif

#ifdef min
	#undef min
#endif
#ifdef max
	#undef max
#endif

#ifdef USE_SSE
	#define _MM_PERM2_X 0
	#define _MM_PERM2_Y 1
	#define _MM_PERM2_Z 2
	#define _MM_PERM2_W 3
	#define _MM_PERM2(X, Y, Z, W) _MM_SHUFFLE(_MM_PERM2_##W, _MM_PERM2_##Z, _MM_PERM2_##Y, _MM_PERM2_##X)
	#define _MM_SWIZZLE(V, X, Y, Z, W) _mm_shuffle_ps(V, V, _MM_PERM2(X, Y, Z, W))
	#define _MM_PERM22(X, Y) _MM_SHUFFLE2(_MM_PERM2_##Y, _MM_PERM2_##X)
	#define _MM_SWIZZLE2(V, X, Y) _mm_shuffle_pd(V, V, _MM_PERM22(X, Y))
#endif


namespace Unigine
{

namespace Math
{

//////////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////////
namespace Consts
{
	constexpr float PI = 3.141592654f;
	constexpr float PI2 = 6.283185308f;
	constexpr float PI05 = 1.570796327f;
	constexpr float IPI2 = 0.159154943f;
	constexpr float LOG2 = 0.693147181f;
	constexpr float LOG10 = 2.302585093f;
	constexpr float SQRT2 = 1.414213562f;
	constexpr float DEG2RAD = (PI / 180.0f);
	constexpr float RAD2DEG = (180.0f / PI);
	constexpr float EPS = 1e-6f;
	constexpr float INF = 1e+9f;
	constexpr float GOLDEN_RATIO = 1.618033989f;
	constexpr float GRAVITY = 9.80665f;

	constexpr double EPS_D = 1e-7;
	constexpr double DEG2RAD_D = 0.01745329251994329577;
	constexpr double RAD2DEG_D = 57.29577951308232087685;
	constexpr double IPI2_D = 0.15915494309189533576;
	constexpr double PI_D = 3.14159265358979323846;
	constexpr double PI05_D = 1.57079632679489661923;
}

enum AXIS
{
	AXIS_X = 0,	// positive axes
	AXIS_Y,
	AXIS_Z,
	AXIS_NX,	// negative axes
	AXIS_NY,
	AXIS_NZ,
};

struct half;
struct vec2;
struct vec3;
struct vec4;
struct dvec2;
struct dvec3;
struct dvec4;
struct hvec2;
struct hvec3;
struct hvec4;
struct ivec2;
struct ivec3;
struct ivec4;
struct bvec4;
struct svec4;
struct mat2;
struct mat3;
struct mat4;
struct dmat4;
struct quat;

using mat2x2_values = float[4];
using mat3x3_values = float[9];
using dmat4x3_values = double[12];
using dmat4x4_values = double[16];
using mat4x3_values = float[12];
using mat4x4_values = float[16];

#if defined(USE_DOUBLE) || defined(UNIGINE_DOUBLE)
	typedef double Scalar;
	typedef Unigine::Math::dvec2 Vec2;
	typedef Unigine::Math::dvec3 Vec3;
	typedef Unigine::Math::dvec4 Vec4;
	typedef Unigine::Math::dmat4 Mat4;
#else
	typedef float Scalar;
	typedef Unigine::Math::vec2 Vec2;
	typedef Unigine::Math::vec3 Vec3;
	typedef Unigine::Math::vec4 Vec4;
	typedef Unigine::Math::mat4 Mat4;
#endif

/// <summary>Performs an unsafe conversion of the matrix data array pointer to the corresponding type used to store elements of the matrix. Make sure that the number of elements and their positions in the pointed source array matches the target type, otherwise you may get wrong data or end up with a crash.</summary>
UNIGINE_INLINE mat2x2_values &unsafeToMat2x2(float *data) { return *reinterpret_cast<float(*)[4]>(data); }
/// <summary>Performs an unsafe conversion of the matrix data array pointer to the corresponding type used to store elements of the matrix. Make sure that the number of elements and their positions in the pointed source array matches the target type, otherwise you may get wrong data or end up with a crash.</summary>
UNIGINE_INLINE mat3x3_values &unsafeToMat3x3(float *data) { return *reinterpret_cast<float(*)[9]>(data); }
/// <summary>Performs an unsafe conversion of the matrix data array pointer to the corresponding type used to store elements of the matrix. Make sure that the number of elements and their positions in the pointed source array matches the target type, otherwise you may get wrong data or end up with a crash.</summary>
UNIGINE_INLINE dmat4x3_values &unsafeToDMat4x3(double *data) { return *reinterpret_cast<double(*)[12]>(data); }
/// <summary>Performs an unsafe conversion of the matrix data array pointer to the corresponding type used to store elements of the matrix. Make sure that the number of elements and their positions in the pointed source array matches the target type, otherwise you may get wrong data or end up with a crash.</summary>
UNIGINE_INLINE dmat4x4_values &unsafeToDMat4x4(double *data) { return *reinterpret_cast<double(*)[16]>(data); }
/// <summary>Performs an unsafe conversion of the matrix data array pointer to the corresponding type used to store elements of the matrix. Make sure that the number of elements and their positions in the pointed source array matches the target type, otherwise you may get wrong data or end up with a crash.</summary>
UNIGINE_INLINE mat4x3_values &unsafeToMat4x3(float *data) { return *reinterpret_cast<float(*)[12]>(data); }
/// <summary>Performs an unsafe conversion of the matrix data array pointer to the corresponding type used to store elements of the matrix. Make sure that the number of elements and their positions in the pointed source array matches the target type, otherwise you may get wrong data or end up with a crash.</summary>
UNIGINE_INLINE mat4x4_values &unsafeToMat4x4(float *data) { return *reinterpret_cast<float(*)[16]>(data); }

// Half float type
struct half
{
public:
	unsigned short h;

	UNIGINE_INLINE constexpr half(): h(0) {}
	UNIGINE_INLINE constexpr half(const half &h) : h(h.h) {}
	UNIGINE_INLINE constexpr explicit half(int i): h((unsigned short)i) {}
	/// <summary>Initializes a half (16-bit) float type value.</summary>
	UNIGINE_INLINE explicit half(float f) { setFloat(f); }

	/// <summary>Assignment operation.</summary>
	UNIGINE_INLINE half &operator=(half v) { h = v.h; return *this; }
	/// <summary>Assignment operation.</summary>
	UNIGINE_INLINE half &operator=(float f) { setFloat(f); return *this; }

	/// <summary>Type conversion to float type.</summary>
	UNIGINE_INLINE operator float() const { return getFloat(); }
	/// <summary>Type conversion to unsigned short type.</summary>
	UNIGINE_INLINE operator unsigned short() const { return h; }

	/// <summary>Sets the value using a given float value.</summary>
	UNIGINE_INLINE void setFloat(float f)
	{
		union
		{
			float f;
			unsigned int i;
		} value = {f};
		unsigned int i = value.i;
		unsigned int e = (i >> 23) & 0x00ff;
		unsigned int m = i & 0x007fffff;
		if (e <= 127 - 15)
			h = (unsigned short)(((m | 0x00800000) >> (127 - 14 - e)) >> 13);
		else
			h = (unsigned short)(i >> 13) & 0x3fff;
		h |= (unsigned short)(i >> 16) & 0xc000;
	}
	/// <summary>Returns the float value.</summary>
	UNIGINE_INLINE float getFloat() const
	{
		unsigned int i = (h << 16) & 0x80000000;
		unsigned int em = h & 0x7fff;
		if (em > 0x03ff)
		{
			i |= (em << 13) + ((127 - 15) << 23);
		} else
		{
			unsigned int m = em & 0x03ff;
			if (m != 0)
			{
				unsigned int e = (em >> 10) & 0x1f;
				while ((m & 0x0400) == 0)
				{
					m <<= 1;
					e--;
				}

				m &= 0x3ff;
				i |= ((e + (127 - 14)) << 23) | (m << 13);
			}
		}

		union
		{
			unsigned int i;
			float f;
		} value = {i};
		return value.f;
	}
};

//////////////////////////////////////////////////////////////////////////
// Type conversion
//////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
	#pragma warning(push)
	#pragma warning(disable : 4244) // don't warn about explicit conversions
#endif

union IntFloat
{
	IntFloat(int i): i(i) {}
	IntFloat(float f): f(f) {}
	IntFloat(unsigned int ui): ui(ui) {}

	int i;
	float f;
	unsigned int ui;
};
union LongDouble
{
	LongDouble(double d): d(d) {}
	LongDouble(long long l): l(l) {}
	LongDouble(unsigned long long ul): ul(ul) {}

	int i[2];
	double d;
	long long l;
	unsigned int ui[2];
	unsigned long long ul;
};

/// <summary>Returns an integer corresponding to the bits of the argument value.</summary>
UNIGINE_INLINE int floatToIntBits(float v) { IntFloat i(v); return i.i; }
/// <summary>Returns an unsigned integer corresponding to the bits of the argument value.</summary>
UNIGINE_INLINE unsigned int floatToUIntBits(float v) { IntFloat i(v); return i.ui; }
/// <summary>Returns the float corresponding to the given bits.</summary>
UNIGINE_INLINE float intBitsToFloat(int v) { IntFloat i(v); return i.f; }
/// <summary>Returns the float corresponding to the given bits.</summary>
UNIGINE_INLINE float intBitsToFloat(unsigned int v) { IntFloat i(v); return i.f; }

/// <summary>Returns a long long value corresponding to the given value.</summary>
UNIGINE_INLINE long long floatToLongBits(double v) { LongDouble i(v); return i.l; }
/// <summary>Returns a long long value corresponding to the given value.</summary>
UNIGINE_INLINE unsigned long long floatToULongBits(double v) { LongDouble i(v); return i.ul; }
/// <summary>Returns a double value corresponding to the given value.</summary>
UNIGINE_INLINE double longBitsToFloat(long long v) { LongDouble i(v); return i.d; }
/// <summary>Returns a double value corresponding to the given value.</summary>
UNIGINE_INLINE double longBitsToFloat(unsigned long long v) { LongDouble i(v); return i.d; }

/// <summary>Returns a conversion of two unsigned integer values to a unsigned long long value.</summary>
UNIGINE_INLINE unsigned long long doubleIntToLong(unsigned int a1, unsigned int a2)
{
	unsigned long long b = a2;
	b = b << 32;
	b = b | a1;
	return b;
}

UNIGINE_INLINE float doubleHalfToFloat(half a1, half a2)
{
	union doubleHalf
	{
		struct
		{
			half h1;
			half h2;
		} h;
		float f;
	};
	doubleHalf d = {{a1, a2}};
	return d.f;
}

/// <summary>Converts an integer value to a float value.</summary>
UNIGINE_INLINE constexpr float itof(int v) { return static_cast<float>(v); }
/// <summary>Converts a float value to an integer value.</summary>
UNIGINE_INLINE constexpr int ftoi(float v) { return static_cast<int>(v); }
/// <summary>Converts a float value to a char value.</summary>
UNIGINE_INLINE constexpr char ftoc(float v) { return static_cast<char>(v); }
/// <summary>Converts an integer value to a double value.</summary>
UNIGINE_INLINE constexpr double itod(int v) { return static_cast<double>(v); }
/// <summary>Converts a double value to an integer value.</summary>
UNIGINE_INLINE constexpr int dtoi(double v) { return static_cast<int>(v); }
/// <summary>Converts a double value to an integer value.</summary>
UNIGINE_INLINE constexpr float dtof(double v) { return static_cast<float>(v); }
/// <summary>Converts an integer value to a scalar value (float or double, depending on the precision).</summary>
UNIGINE_INLINE constexpr Scalar itos(int v) { return static_cast<Scalar>(v); }
/// <summary>Converts a scalar value (float or double, depending on the precision) to an integer value.</summary>
UNIGINE_INLINE constexpr int stoi(Scalar v) { return static_cast<int>(v); }
/// <summary>Converts a long value to a float value.</summary>
UNIGINE_INLINE constexpr float ltof(long long v) { return static_cast<float>(v); }
/// <summary>Converts a float value to a long value.</summary>
UNIGINE_INLINE constexpr long long ftol(float v) { return static_cast<long long>(v); }
/// <summary>Converts a long value to a double value.</summary>
UNIGINE_INLINE constexpr double ltod(long long v) { return static_cast<double>(v); }
/// <summary>Converts a double value to a long value.</summary>
UNIGINE_INLINE constexpr long long dtol(double v) { return static_cast<long long>(v); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, float>::value, void>::type>
UNIGINE_INLINE constexpr float toFloat(const T &value) { return static_cast<float>(value); }
/// <summary>Converts the agrument to a float value.</summary>
UNIGINE_INLINE float toFloat(half value) { return value.getFloat(); }
/// <summary>Converts the agrument to a float value.</summary>
UNIGINE_INLINE float toFloat(const String &value) { return value.getFloat(); }
/// <summary>Converts the agrument to a float value.</summary>
UNIGINE_INLINE float toFloat(const char *value) { return String::atof(value); }

template<typename T>
/// <summary>Converts the agrument to a half value.</summary>
UNIGINE_INLINE half toHalf(const T &value) { return half(toFloat(value)); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, double>::value, void>::type>
UNIGINE_INLINE constexpr double toDouble(const T &value) { return static_cast<double>(value); }
/// <summary>Converts the agrument to a double value.</summary>
UNIGINE_INLINE double toDouble(half value) { return static_cast<double>(value.getFloat()); }
/// <summary>Converts the agrument to a double value.</summary>
UNIGINE_INLINE double toDouble(const String &value) { return value.getDouble(); }
/// <summary>Converts the agrument to a double value.</summary>
UNIGINE_INLINE double toDouble(const char *value) { return String::atod(value); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, Scalar>::value, void>::type>
UNIGINE_INLINE constexpr Scalar toScalar(const T &value) { return static_cast<Scalar>(value); }
/// <summary>Converts the agrument to a Scalar value.</summary>
UNIGINE_INLINE Scalar toScalar(half value) { return static_cast<Scalar>(value.getFloat()); }
/// <summary>Converts the agrument to a Scalar value.</summary>
UNIGINE_INLINE Scalar toScalar(const String &value) { return static_cast<Scalar>(value.getDouble()); }
/// <summary>Converts the agrument to a Scalar value.</summary>
UNIGINE_INLINE Scalar toScalar(const char *value) { return static_cast<Scalar>(String::atod(value)); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, int>::value, void>::type>
UNIGINE_INLINE constexpr int toInt(const T &value) { return static_cast<int>(value); }
/// <summary>Converts the agrument to an integer value.</summary>
UNIGINE_INLINE int toInt(half value) { return static_cast<int>(value.getFloat()); }
/// <summary>Converts the agrument to an integer value.</summary>
UNIGINE_INLINE int toInt(const String &value) { return value.getInt(); }
/// <summary>Converts the agrument to an integer value.</summary>
UNIGINE_INLINE int toInt(const char *value) { return String::atoi(value); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, unsigned int>::value, void>::type>
UNIGINE_INLINE constexpr unsigned int toUInt(const T &value) { return static_cast<unsigned int>(value); }
/// <summary>Converts the agrument to an unsigned integer value.</summary>
UNIGINE_INLINE unsigned int toUInt(half value) { return static_cast<unsigned int>(value.getFloat()); }
/// <summary>Converts the agrument to an unsigned integer value.</summary>
UNIGINE_INLINE unsigned int toUInt(const String &value) { return toUInt(value.getInt()); }
/// <summary>Converts the agrument to an unsigned integer value.</summary>
UNIGINE_INLINE unsigned int toUInt(const char *value) { return toUInt(String::atoi(value)); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, char>::value, void>::type>
UNIGINE_INLINE constexpr char toChar(const T &value) { return static_cast<char>(value); }
/// <summary>Converts the agrument to a character value.</summary>
UNIGINE_INLINE char toChar(half value) { return static_cast<char>(value.getFloat()); }
/// <summary>Converts the agrument to a character value.</summary>
UNIGINE_INLINE char toChar(const String &value) { return toChar(value.getInt()); }
/// <summary>Converts the agrument to a character value.</summary>
UNIGINE_INLINE char toChar(const char *value) { return toChar(String::atoi(value)); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, short>::value, void>::type>
UNIGINE_INLINE constexpr short toShort(const T &value) { return static_cast<T>(value); }
/// <summary>Converts the agrument to a short value.</summary>
UNIGINE_INLINE short toShort(half value) { return static_cast<short>(value.getFloat()); }
/// <summary>Converts the agrument to a short value.</summary>
UNIGINE_INLINE short toShort(const String &value) { return toShort(value.getInt()); }
/// <summary>Converts the agrument to a short value.</summary>
UNIGINE_INLINE short toShort(const char *value) { return toShort(String::atoi(value)); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, unsigned char>::value, void>::type>
UNIGINE_INLINE constexpr unsigned char toUChar(const T &value) { return static_cast<unsigned char>(value); }
/// <summary>Converts the agrument to an unsigned character value.</summary>
UNIGINE_INLINE unsigned char toUChar(half value) { return static_cast<unsigned char>(value.getFloat()); }
/// <summary>Converts the agrument to an unsigned character value.</summary>
UNIGINE_INLINE unsigned char toUChar(const String &value) { return toUChar(value.getInt()); }
/// <summary>Converts the agrument to an unsigned character value.</summary>
UNIGINE_INLINE unsigned char toUChar(const char *value) { return toUChar(String::atoi(value)); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, unsigned short>::value, void>::type>
UNIGINE_INLINE constexpr unsigned short toUShort(const T &value) { return static_cast<unsigned short>(value); }
/// <summary>Converts the agrument to an unsigned short value.</summary>
UNIGINE_INLINE unsigned short toUShort(half value) { return static_cast<unsigned short>(value.getFloat()); }
/// <summary>Converts the agrument to an unsigned short value.</summary>
UNIGINE_INLINE unsigned short toUShort(const String &value) { return toUShort(value.getInt()); }
/// <summary>Converts the agrument to an unsigned short value.</summary>
UNIGINE_INLINE unsigned short toUShort(const char *value) { return toUShort(String::atoi(value)); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, unsigned long long>::value, void>::type>
UNIGINE_INLINE constexpr unsigned long long toULong(const T &value) { return static_cast<unsigned long long>(value); }
/// <summary>Converts the agrument to an unsigned long value.</summary>
UNIGINE_INLINE unsigned long long toULong(half value) { return static_cast<unsigned long long>(value.getFloat()); }
/// <summary>Converts the agrument to an unsigned long value.</summary>
UNIGINE_INLINE unsigned long long toULong(const String &value) { return toULong(value.getInt()); }
/// <summary>Converts the agrument to an unsigned long value.</summary>
UNIGINE_INLINE unsigned long long toULong(const char *value) { return toULong(String::atoi(value)); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, long long>::value, void>::type>
UNIGINE_INLINE constexpr long long toLong(const T &value) { return static_cast<long long>(value); }
/// <summary>Converts the agrument to a long value.</summary>
UNIGINE_INLINE long long toLong(half value) { return static_cast<long long>(value.getFloat()); }
/// <summary>Converts the agrument to a long value.</summary>
UNIGINE_INLINE long long toLong(const String &value) { return toLong(value.getInt()); }
/// <summary>Converts the agrument to a long value.</summary>
UNIGINE_INLINE long long toLong(const char *value) { return toLong(String::atoi(value)); }

template<typename T, typename = typename std::enable_if<std::is_convertible<T, int>::value, void>::type> // pointers are convertible to bool, so use int
UNIGINE_INLINE constexpr bool toBool(const T &value) { return static_cast<bool>(value); }
/// <summary>Converts the agrument to a boolean value.</summary>
UNIGINE_INLINE bool toBool(half value) { return toInt(value) != 0; }
/// <summary>Converts the agrument to a boolean value.</summary>
UNIGINE_INLINE bool toBool(const String &value) { return value.getBool(); }
/// <summary>Converts the agrument to a boolean value.</summary>
UNIGINE_INLINE bool toBool(const char *value) { return String::atob(value); }

#if defined(_MSC_VER)
	#pragma warning(pop)
#endif

//////////////////////////////////////////////////////////////////////////
// Bits
//////////////////////////////////////////////////////////////////////////

template <class Type>
struct Bits
{
public:
	enum
	{
		Capacity = sizeof(Type) * 8
	};

	/// <summary>Constructor. Initializes the bit structure.</summary>
	UNIGINE_INLINE Bits(): data(0) {}
	/// <summary>Constructor. Initializes the bit structure with the data of the specified type.</summary>
	UNIGINE_INLINE Bits(Type data_) : data(data_) {}
	UNIGINE_INLINE ~Bits() {}

	/// <summary>Sets the value to the bit with a given index.</summary>
	UNIGINE_INLINE void set(int index, int value)
	{
		assert(index < Capacity && "Bits::set(): bad index");
		if (value)
			data |= 1ULL << index;
		else
			data &= ~(1ULL << index);
	}
	/// <summary>Sets the value to the bit with a given index.</summary>
	UNIGINE_INLINE void set(int index, bool value)
	{
		assert(index < Capacity && "Bits::set(): bad index");
		if (value)
			data |= 1ULL << index;
		else
			data &= ~(1ULL << index);
	}

	/// <summary>Returns the value of the bit with a given index.</summary>
	UNIGINE_INLINE bool get(int index) const
	{
		assert(index < Capacity && "Bits::get(): bad index");
		return ((data >> index) & 0x01) != 0;
	}
	/// <summary>Returns the value of the bit with a given index.</summary>
	UNIGINE_INLINE bool operator[](int index) const { return get(index); }

	/// <summary>Sets the bit structure using the specified mask.</summary>
	UNIGINE_INLINE void set(Type mask) { data = mask; }
	/// <summary>Returns the bit structure as a variable of the original type.</summary>
	UNIGINE_INLINE Type get() const { return data; }

	/// <summary>Returns the capacity of the structure in bits.</summary>
	UNIGINE_INLINE int size() const { return (int)Capacity; }
	/// <summary>Clears the structure.</summary>
	UNIGINE_INLINE void clear() { data = 0; }

	Type data;
};

template <int Capacity = 128>
class BitStream
{
public:
	/// <summary>Constructor. Initializes the bit buffer.</summary>
	UNIGINE_INLINE BitStream()
		: length(0)
		, buffer(0)
		, num_bits(0)
	{	}
	UNIGINE_INLINE ~BitStream() {}

	/// <summary>Returns the pointer to the constant bit buffer.</summary>
	UNIGINE_INLINE const unsigned char *get() const { return data; }
	/// <summary>Returns the pointer to the bit buffer.</summary>
	UNIGINE_INLINE unsigned char *get() { return data; }
	/// <summary>Returns the size of the structure in bytes.</summary>
	UNIGINE_INLINE int size() const { return length + 1; }

	/// <summary>Clears the buffer.</summary>
	UNIGINE_INLINE void clear()
	{
		length = 0;
		buffer = 0;
		num_bits = 0;
	}

	/// <summary>Aligns the buffer.</summary>
	UNIGINE_INLINE void align()
	{
		buffer = 0;
		num_bits = 0;
	}

	// unsigned bits
	/// <summary>Returns the unsigned data from the buffer.</summary>
	/// <param name="num">Number of bits to return.</param>
	int readUBits(int num)
	{
		int ret = 0;
		int ret_bits = 0;
		if (num > num_bits)
		{
			ret = buffer;
			num -= num_bits;
			ret_bits = num_bits;
			while (num > 8)
			{
				assert(length + 1 < Capacity && "BitStream::readUBits(): data underflow");
				ret |= data[length++] << ret_bits;
				ret_bits += 8;
				num -= 8;
			}
			if (num > 0)
			{
				num_bits = 8;
				assert(length + 1 < Capacity && "BitStream::readUBits(): data underflow");
				buffer = data[length++];
			}
		}
		if (num > 0)
		{
			ret |= (buffer & ((1 << num) - 1)) << ret_bits;
			num_bits -= num;
			buffer >>= num;
		}
		return ret;
	}
	/// <summary>Writes the specified number of bits from the given value to the buffer.</summary>
	/// <param name="value">Data to be written.</param>
	/// <param name="num">Number of bits to be written from value.</param>
	void writeUBits(int value, int num)
	{
		while (num > 8)
		{
			buffer |= (value & 0xff) << num_bits;
			assert(length + 1 < Capacity && "BitStream::writeUBits(): data overflow");
			data[length++] = buffer;
			buffer >>= 8;
			value >>= 8;
			num -= 8;
		}
		if (num > 0)
		{
			buffer |= value << num_bits;
			data[length] = buffer;
			num_bits += num;
			if (num_bits >= 8)
			{
				assert(length + 1 < Capacity && "BitStream::writeUBits(): data overflow");
				data[length++] = buffer;
				num_bits -= 8;
				buffer >>= 8;
			}
		}
	}

	// signed bits
	/// <summary>Reads the signed data from the buffer.</summary>
	/// <param name="num">Number of bits to be read.</param>
	UNIGINE_INLINE int readBits(int num)
	{
		int ret = readUBits(num);
		if (ret & (1 << (num - 1)))
			return ret - (1 << num);
		return ret;
	}
	/// <summary>Writes the signed data to the buffer.</summary>
	/// <param name="value">Data to be written.</param>
	/// <param name="num">Number of bits to be written from value.</param>
	UNIGINE_INLINE void writeBits(int value, int num)
	{
		if (value < 0)
			value += (1 << num);
		writeUBits(value, num);
	}

private:
	int length;
	int buffer;
	int num_bits;
	unsigned char data[Capacity];
};

//////////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////////

/// <summary>Returns the square root of the argument.</summary>
UNIGINE_INLINE float fsqrt(float v) { return ::sqrtf(v); }
/// <summary>Returns the square root of the argument.</summary>
UNIGINE_INLINE double dsqrt(double v) { return ::sqrt(v); }
/// <summary>Returns the square root of the argument.</summary>
UNIGINE_INLINE Scalar ssqrt(Scalar v)
{
	#if defined(USE_DOUBLE) || defined(UNIGINE_DOUBLE)
		return dsqrt(v);
	#else
		return fsqrt(v);
	#endif
}
/// <summary>Returns an approximation of the square root.</summary>
UNIGINE_INLINE float sqrtFast(float v)
{
	IntFloat i = v;
	i.i = 0x5f3759df - (i.i >> 1);
	v = i.f * v;
	return v * (1.5f - (i.f * v * 0.5f));
}

/// <summary>Returns the inverted square root of the argument.</summary>
UNIGINE_INLINE float rsqrt(float v)
{
	return (v < 1e-18f) ? Consts::INF : 1.0f / ::sqrtf(v);
}
/// <summary>Returns the inverted square root of the argument.</summary>
UNIGINE_INLINE double rsqrt(double v)
{
	return (v < 1e-18) ? Consts::INF : 1.0 / ::sqrt(v);
}
/// <summary>Returns an approximation of the inverted square root.</summary>
UNIGINE_INLINE float rsqrtFast(float v)
{
	#ifdef USE_SSE
		_mm_store_ss(&v, _mm_rsqrt_ss(_mm_set_ss(v)));
		return v;
	#else
		IntFloat i = v;
		i.i = 0x5f3759df - (i.i >> 1);
		return i.f * (1.5f - (i.f * i.f * v * 0.5f));
	#endif
}
/// <summary>Returns the sine of the given argument.</summary>
UNIGINE_INLINE float sin(float a) { return ::sinf(a); }
/// <summary>Returns the sine of the given argument.</summary>
UNIGINE_INLINE double sin(double a) { return ::sin(a); }
/// <summary>Returns the approximated, but calculated more quickly, sine of the given argument.</summary>
UNIGINE_INLINE float sinFast(float a)
{
	a *= Consts::IPI2;
	a -= 0.5f + ::floorf(a);
	a *= 16.f * (abs(a) - 0.5f);
	a += 0.225f * a * (abs(a) - 1.0f);

	return a;
}

/// <summary>Returns the approximated, but calculated more quickly, sine of the given argument in range [-pi*0.5, pi*0.5].</summary>
UNIGINE_INLINE float sinFastFixed(float a)
{
	float a2 = a * a;
	return a * (((((-2.39e-08f * a2 + 2.7526e-06f) * a2 - 1.98409e-04f) * a2 + 0.0083333315f) * a2 - 0.1666666664f) * a2 + 1.0f);
}

/// <summary>Returns the cosine of the given argument.</summary>
UNIGINE_INLINE float cos(float a) { return ::cosf(a); }
/// <summary>Returns the cosine of the given argument.</summary>
UNIGINE_INLINE double cos(double a) { return ::cos(a); }
/// <summary>Returns the approximated, but calculated more quickly, cosine of the given argument.</summary>
UNIGINE_INLINE float cosFast(float a)
{
	a *= Consts::IPI2;
	a -= 0.25f + ::floorf(a + 0.25f);
	a *= 16.f * (abs(a) - 0.5f);
	a += 0.225f * a * (abs(a) - 1.0f);

	return a;
}

/// <summary>Returns the approximated, but calculated more quickly, cosine of the given argument in range [-pi*0.5, pi*0.5].</summary>
UNIGINE_INLINE float cosFastFixed(float a)
{
	float a2 = a * a;
	return (((((-2.605e-07f * a2 + 2.47609e-05f) * a2 - 0.0013888397f) * a2 + 0.0416666418f) * a2 - 0.4999999963f) * a2 + 1.0f);
}

/// <summary>Returns the tangent of the given argument.</summary>
UNIGINE_INLINE float tan(float a) { return ::tanf(a); }
/// <summary>Returns the tangent of the given argument.</summary>
UNIGINE_INLINE double tan(double a) { return ::tan(a); }

/// <summary>Returns the arcsine of the given argument - the angle in radians, whose sine is equal to the argument. a == sin(asin(a)) for every value of a that is within asin()'s range.</summary>
UNIGINE_INLINE float asin(float v) { return ::asinf(v); }
/// <summary>Returns the arcsine of the given argument - the angle in radians, whose sine is equal to the argument. a == sin(asin(a)) for every value of a that is within asin()'s range.</summary>
UNIGINE_INLINE double asin(double v) { return ::asin(v); }
/// <summary>Returns the approximated, but calculated more quickly, arcsine of the given argument.</summary>
UNIGINE_INLINE float asinFast(float v)
{
	return Consts::PI05 - (((((((-0.0012624911f * v + 0.0066700901f) * v - 0.0170881256f) * v + 0.0308918810f) * v - 0.0501743046f) * v + 0.0889789874f) * v - 0.2145988016f) * v + 1.5707963050f) * Math::fsqrt(1.0f - v);
}

/// <summary>Returns the arccosine of the given argument - the angle in radians, whose cosine is equal to the argument. a == cos(acos(a)) for every value of a that is within acos()'s range.</summary>
UNIGINE_INLINE float acos(float v) { return ::acosf(v); }
/// <summary>Returns the arccosine of the given argument - the angle in radians, whose cosine is equal to the argument. a == cos(acos(a)) for every value of a that is within acos()'s range.</summary>
UNIGINE_INLINE double acos(double v) { return ::acos(v); }
/// <summary>Returns the approximated, but calculated more quickly, arccosine of the given argument.</summary>
UNIGINE_INLINE float acosFast(float v)
{
	return (((((((-0.0012624911f * v + 0.0066700901f) * v - 0.0170881256f) * v + 0.0308918810f) * v - 0.0501743046f) * v + 0.0889789874f) * v - 0.2145988016f) * v + 1.5707963050f) * Math::fsqrt(1.0f - v);
}

/// <summary>Returns the arctangent of the given argument - the angle in radians, whose tangent is equal to the argument. a == tan(atan(a)) for every value of a that is within atan()'s range.</summary>
UNIGINE_INLINE float atan(float v) { return ::atanf(v); }
/// <summary>Returns the arctangent of the given argument - the angle in radians, whose tangent is equal to the argument. a == tan(atan(a)) for every value of a that is within atan()'s range.</summary>
UNIGINE_INLINE double atan(double v) { return ::atan(v); }

/// <summary>Returns the arctangent of two arguments (x and y). It is similar to calculating the arctangent of y / x, except that the signs of both arguments are used to determine the quadrant of the result.</summary>
UNIGINE_INLINE float atan2(float y, float x) { return ::atan2f(y, x); }
/// <summary>Returns the arctangent of two arguments (x and y). It is similar to calculating the arctangent of y / x, except that the signs of both arguments are used to determine the quadrant of the result.</summary>
UNIGINE_INLINE double atan2(double y, double x) { return ::atan2(y, x); }

/// <summary>Calculates sine and cosine values for the specified angle value given in radians and puts them to &s (sine) and &c (cosine) arguments.</summary>
UNIGINE_INLINE void sincos(float angle, float &s, float &c)
{
	#if _LINUX
		double res_0, res_1;
		asm volatile("fsincos"
					 : "=t"(res_0), "=u"(res_1)
					 : "0"(angle));
		s = (float)res_1;
		c = (float)res_0;
	#else
		s = toFloat(sin(angle));
		c = toFloat(cos(angle));
	#endif
}
/// <summary>Calculates sine and cosine values for the specified angle value given in radians and puts them to &s (sine) and &c (cosine) arguments.</summary>
UNIGINE_INLINE void sincos(double angle, double &s, double &c)
{
	#if _LINUX
		asm volatile("fsincos"
					 : "=t"(c), "=u"(s)
					 : "0"(angle));
	#else
		s = sin(angle);
		c = cos(angle);
	#endif
}
/// <summary>Calculates approximated sine and cosine values for the specified angle value given in radians and puts them to &s (sine) and &c (cosine) arguments.</summary>
UNIGINE_INLINE void sincosFast(float a, float &s, float &c)
{
	if (a < 0.0f)
		a -= toInt(a * (1.0f / Consts::PI2)) * Consts::PI2 - Consts::PI2;
	else if (a >= Consts::PI2)
		a -= toInt(a * (1.0f / Consts::PI2)) * Consts::PI2;
	c = 1.0f;
	s = Consts::PI - a;
	if (s < -Consts::PI05)
		s = -Consts::PI - s;
	else if (s > Consts::PI05)
		s = Consts::PI - s;
	else
		c = -1.0f;
	float a2 = s * s;
	s *= ((0.00761f * a2 - 0.16605f) * a2 + 1.0f);
	c *= ((0.03705f * a2 - 0.49670f) * a2 + 1.0f);
}


/// <summary>Returns the sign of the argument value: 1.0 if v >= 0.0 ; -1.0 if v < 0.0.</summary>
UNIGINE_INLINE float sign(float v)
{
	return IntFloat((IntFloat(v).ui & 0x80000000) | 0x3f800000).f;
}
/// <summary>Returns the sign of the argument value: 1.0 if v >= 0.0 ; -1.0 if v < 0.0.</summary>
UNIGINE_INLINE double sign(double v) { return (v >= 0.0) ? 1.0 : -1.0; }
/// <summary>Returns the sign of the argument value: 0 if the value is positive or zero, -1, if the value is negative.</summary>
UNIGINE_INLINE int signMask(int v) { return v >> 31; }

/// <summary>Returns the absolute value of the argument.</summary>
UNIGINE_INLINE int abs(int v) { return (v >= 0) ? v : -v; }
/// <summary>Returns the absolute value of the argument.</summary>
UNIGINE_INLINE long long abs(long long v) { return (v >= 0) ? v : -v; }
/// <summary>Returns the absolute value of the argument.</summary>
UNIGINE_INLINE float abs(float v) { return (v >= 0) ? v : -v; }
/// <summary>Returns the absolute value of the argument.</summary>
UNIGINE_INLINE double abs(double v) { return (v >= 0) ? v : -v; }

/// <summary>Rounds an argument to the nearest integer value.</summary>
UNIGINE_INLINE float round(float v) { return ::roundf(v); }
/// <summary>Rounds an argument to the nearest integer value.</summary>
UNIGINE_INLINE double round(double v) { return ::round(v); }
/// <summary>Rounds an argument to the nearest integer value by adding 0.5 to the argument and discarding the decimal part. This method works for positive numbers but doesn't handle rounding in the traditional way for negative values.</summary>
UNIGINE_INLINE int roundFast(float v)
{
	// Actually this is the fastest code we could get.
	// Both SSE intrinsics and raw assembler didn't give any performance gain on supported systems.
	return static_cast<int>(v + 0.5f);
}

/// <summary>Ceiling function that returns the smallest integer value that is not less than the argument.</summary>
UNIGINE_INLINE float ceil(float v) { return ::ceilf(v); }
/// <summary>Ceiling function that returns the smallest integer value that is not less than the argument.</summary>
UNIGINE_INLINE double ceil(double v) { return ::ceil(v); }

/// <summary>Returns the smallest value that's greater than or equal to the argument, stored as an integer.</summary>
UNIGINE_INLINE int ceilInt(float v) { return toInt(::ceilf(v)); }
/// <summary>Returns the smallest value that's greater than or equal to the argument, stored as an integer.</summary>
UNIGINE_INLINE int ceilInt(double v) { return toInt(::ceil(v)); }

/// <summary>Rounds an argument down to the nearest integer.</summary>
UNIGINE_INLINE float floor(float v) { return ::floorf(v); }
/// <summary>Rounds an argument down to the nearest integer.</summary>
UNIGINE_INLINE double floor(double v) { return ::floor(v); }

/// <summary>Returns the largest value that is less than or equal to the argument, stored as an integer.</summary>
UNIGINE_INLINE int floorInt(float v) { return toInt(::floorf(v)); }
/// <summary>Returns the largest value that is less than or equal to the argument, stored as an integer.</summary>
UNIGINE_INLINE int floorInt(double v) { return toInt(::floor(v)); }

/// <summary>Returns the fractional part of the argument. This is calculated as v - floor(v). 1.75 -> 0.75. -1.75 -> 0.25.</summary>
UNIGINE_INLINE float frac(float v) { return v - ::floorf(v); }
/// <summary>Returns the fractional part of the argument. This is calculated as v - floor(v). 1.75 -> 0.75. -1.75 -> 0.25.</summary>
UNIGINE_INLINE double frac(double v) { return v - ::floor(v); }

/// <summary>Returns the base-2 logarithm of the argument.</summary>
UNIGINE_INLINE float log2(float v) { return ::logf(v) * (1.0f / Consts::LOG2); }
/// <summary>Returns the base-2 logarithm of the argument.</summary>
UNIGINE_INLINE double log2(double v) { return ::log(v) * (1.0 / Consts::LOG2); }
/// <summary>Returns the base-2 logarithm of the argument.</summary>
UNIGINE_INLINE int log2(int v)
{
	int ret = 0;
	if (v >= 1 << 16)
	{
		v >>= 16;
		ret |= 16;
	}
	if (v >= 1 << 8)
	{
		v >>= 8;
		ret |= 8;
	}
	if (v >= 1 << 4)
	{
		v >>= 4;
		ret |= 4;
	}
	if (v >= 1 << 2)
	{
		v >>= 2;
		ret |= 2;
	}
	if (v >= 1 << 1)
		ret |= 1;
	return ret;
}
/// <summary>Returns the approximated (quicker calculated) base-2 logarithm of the argument.</summary>
UNIGINE_INLINE float log2Fast(float v)
{
	int i = IntFloat(v).i;
	int e = ((i >> 23) & 0xff) - 127;
	v = IntFloat((i & 0x007fffff) | 0x3f800000).f;
	return toFloat(e) + (v - 1.0f) * (((((-0.034436006f * v + 0.31821337f) * v - 1.2315303f) * v + 2.5988452f) * v - 3.3241990f) * v + 3.1157899f);
}

/// <summary>Returns the natural logarithm of the argument.</summary>
UNIGINE_INLINE float log(float v) { return ::logf(v); }
/// <summary>Returns the natural logarithm of the argument.</summary>
UNIGINE_INLINE double log(double v) { return ::log(v); }
/// <summary>Returns the approximated (quicker calculated) natural logarithm of the argument.</summary>
UNIGINE_INLINE float logFast(float v) { return log2Fast(v) * Consts::LOG2; }

/// <summary>Returns the base-10 logarithm of the argument.</summary>
UNIGINE_INLINE float log10(float v) { return ::logf(v) * (1.0f / Consts::LOG10); }
/// <summary>Returns the base-10 logarithm of the argument.</summary>
UNIGINE_INLINE double log10(double v) { return ::log(v) * (1.0f / Consts::LOG10); }

/// <summary>Returns the reciprocal of the specified argument.</summary>
UNIGINE_INLINE float rcp(float v) { return 1.0f / v; }
/// <summary>Returns the reciprocal of the specified argument.</summary>
UNIGINE_INLINE double rcp(double v) { return 1.0 / v; }
/// <summary>Returns the approximated (quicker calculated) reciprocal of the specified argument.</summary>
UNIGINE_INLINE float rcpFast(float v)
{
#ifdef USE_SSE
	_mm_store_ss(&v, _mm_rcp_ss(_mm_set_ss(v)));
	return v;
#else
	IntFloat i = v;
	i.i = 0x7f000000 - i.i;
	return i.f * (2.0f - v * i.f);
#endif
}

/// <summary>Returns 2 raised to the power specified in the argument.</summary>
UNIGINE_INLINE float exp2(float v) { return ::expf(v * Consts::LOG2); }
/// <summary>Returns 2 raised to the power specified in the argument.</summary>
UNIGINE_INLINE double exp2(double v) { return ::exp(v * Consts::LOG2); }
/// <summary>Returns fast-calculated 2 raised to the power specified in the argument.</summary>
UNIGINE_INLINE float exp2Fast(float v)
{
	int i = toInt(v - 0.5f);
	v = v - toFloat(i);
	return IntFloat((i + 127) << 23).f * (((((0.0018775767f * v + 0.0089893397f) * v + 0.055826318f) * v + 0.24015361f) * v + 0.69315308f) * v + 0.99999994f);
}

/// <summary>Returns e raised to the power specified in the argument.</summary>
UNIGINE_INLINE float exp(float v) { return ::expf(v); }
/// <summary>Returns e raised to the power specified in the argument.</summary>
UNIGINE_INLINE double exp(double v) { return ::exp(v); }
/// <summary>Returns fast-calculated e raised to the power specified in the argument.</summary>
UNIGINE_INLINE float expFast(float v) { return exp2Fast(v * (1.0f / Consts::LOG2)); }

/// <summary>Returns the value of the x argument raised to the y power.</summary>
UNIGINE_INLINE float pow(float x, float y) { return ::powf(x, y); }
/// <summary>Returns the value of the x argument raised to the y power.</summary>
UNIGINE_INLINE double pow(double x, double y) { return ::pow(x, y); }
/// <summary>Returns the fast-calculated value of the x argument raised to the y power. Doesn't perform the check that the first argument is a negative value.</summary>
UNIGINE_INLINE float powFast(float x, float y) { return exp2Fast(log2Fast(x) * y); }

/// <summary>Returns the squared argument (raised to the power of 2).</summary>
UNIGINE_INLINE float pow2(float x) { return x * x; }
/// <summary>Returns the squared argument (raised to the power of 2).</summary>
UNIGINE_INLINE double pow2(double x) { return x * x; }
/// <summary>Returns the squared argument (raised to the power of 2).</summary>
UNIGINE_INLINE int pow2(int x) { return x * x; }

/// <summary>Returns the next power of 2 greater than or equal to a given argument.</summary>
UNIGINE_INLINE unsigned long long nextPow2(unsigned long long n)
{
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n |= n >> 32;
	return ++n;
}

/// <summary>Converts RGB color value to sRGB format.</summary>
UNIGINE_INLINE float srgb(float x) { return pow(x, 2.2f); }
/// <summary>Converts sRGB color value to RGB format.</summary>
UNIGINE_INLINE float isrgb(float x) { return pow(x, 1.0f / 2.2f); }

/// <summary>Returns the floating-point remainder of the division operation: x/y.</summary>
UNIGINE_INLINE float mod(float x, float y) { return ::fmodf(x, y); }
/// <summary>Returns the floating-point remainder of the division operation: x/y.</summary>
UNIGINE_INLINE double mod(double x, double y) { return ::fmod(x, y); }

/// <summary>Returns the result of multiplication of the first value by the second value and addition of the third value (a * b + c).</summary>
UNIGINE_INLINE float mad(float a, float b, float c) { return a * b + c; }
/// <summary>Returns the result of multiplication of the first value by the second value and addition of the third value (a * b + c).</summary>
UNIGINE_INLINE double mad(double a, double b, double c) { return a * b + c; }

/// <summary>Returns one of the two argument values (v0 and v1) based on the sign of a condition (c).</summary>
UNIGINE_INLINE int select(int c, int v0, int v1)
{
	int mask = signMask(c | -c);
	return (v0 & mask) | (v1 & ~mask);
}
/// <summary>Returns one of the two argument values (v0 and v1) based on the sign of a condition (c).</summary>
UNIGINE_INLINE float select(int c, float v0, float v1)
{
	int mask = signMask(c | -c);
	return IntFloat((IntFloat(v0).i & mask) | (IntFloat(v1).i & ~mask)).f;
}
/// <summary>Returns one of the two argument values (v0 and v1) based on the sign of a condition (c).</summary>
UNIGINE_INLINE float select(float c, float v0, float v1)
{
	int mask = signMask(IntFloat(c).i);
	return IntFloat((IntFloat(v0).i & mask) | (IntFloat(v1).i & ~mask)).f;
}

/// <summary>Rounds up to the nearest power of two value.</summary>
UNIGINE_INLINE int npot(int v)
{
	int i = 1;
	while (i < v)
		i += i;
	return i;
}
/// <summary>Checks if the argument value is a power of two by using bitwise operations.</summary>
UNIGINE_INLINE int ispot(int v) { return ((v - 1) & v) == 0; }
/// <summary>Returns the integer square root of the argument value by using bitwise operations.</summary>
UNIGINE_INLINE int isqrt(int v)
{
	int ret = 0;
	int bit = 1 << 30;
	for (; bit > v; bit >>= 2)
		;
	for (; bit != 0; bit >>= 2)
	{
		if (v >= ret + bit)
		{
			v -= ret + bit;
			ret = (ret >> 1) + bit;
		} else
		{
			ret = ret >> 1;
		}
	}
	return ret;
}

/// <summary>Performs integer division of x by y with rounding up.</summary>
UNIGINE_INLINE int udiv(int x, int y) { return x / y + (x % y != 0); }
/// <summary>Compares two values to determine if they can be considered equal within a given tolerance (epsilon).</summary>
UNIGINE_INLINE bool compare(float v0, float v1, float epsilon = Consts::EPS) { return abs(v0 - v1) < epsilon; }
/// <summary>Compares two values to determine if they can be considered equal within a given tolerance (epsilon).</summary>
UNIGINE_INLINE bool compare(double v0, double v1, double epsilon = Consts::EPS) { return abs(v0 - v1) < epsilon; }
/// <summary>Checks if the two values are exactly equal.</summary>
UNIGINE_INLINE bool compare(int v0, int v1) { return v0 == v1; }
/// <summary>Checks if the two values are exactly equal.</summary>
UNIGINE_INLINE bool compare(long long v0, long long v1) { return v0 == v1; }

template <typename T>
/// <summary>Checks if the two arguments are exactly equal.</summary>
UNIGINE_INLINE bool compare(const Pair<T, T> &p0, const Pair<T, T> &p1)
{
	return compare(p0.first, p1.first) && compare(p0.second, p1.second);
}

template<typename T, typename = typename std::enable_if<std::is_same<T, float>::value || std::is_same<T, double>::value, void>::type>
/// <summary>Returns a value that indicates whether the argument is not a number (NaN).</summary>
UNIGINE_INLINE bool isNan(T value)
{
	#if defined(__GNUC__)
		// special for -ffast-math
		return __isnan(value) != 0;
	#else
		using namespace std;
		return isnan(value);
	#endif
}

template<typename T, typename = typename std::enable_if<std::is_same<T, float>::value || std::is_same<T, double>::value, void>::type>
/// <summary>Returns a value that indicates whether the argument evaluates to negative or positive infinity.</summary>
UNIGINE_INLINE bool isInf(T value)
{
	#if defined(__GNUC__)
		// special for -ffast-math
		return __isinf(value) != 0;
	#else
		using namespace std;
		return isinf(value);
	#endif
}

template<typename T, typename = typename std::enable_if<std::is_same<T, float>::value || std::is_same<T, double>::value, void>::type>
/// <summary>Checks if the given value is a finite number, meaning it is neither NaN nor infinity (positive or negative).</summary>
UNIGINE_INLINE bool isFinite(T value)
{
	return !isNan(value) && !isInf(value);
}

/// <summary>Compares the arguments and returns the minimum value.</summary>
UNIGINE_INLINE float min(float v0, float v1) { return (v0 < v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the minimum value.</summary>
UNIGINE_INLINE double min(double v0, double v1) { return (v0 < v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the minimum value.</summary>
UNIGINE_INLINE int min(int v0, int v1) { return (v0 < v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the minimum value.</summary>
UNIGINE_INLINE char min(char v0, char v1) { return (v0 < v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the minimum value.</summary>
UNIGINE_INLINE size_t min(size_t v0, size_t v1) { return (v0 < v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the minimum value.</summary>
UNIGINE_INLINE long long min(long long v0, long long v1) { return (v0 < v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the minimum value.</summary>
UNIGINE_INLINE long int min(long int v0, long int v1) { return (v0 < v1) ? v0 : v1; }

/// <summary>Compares the arguments and returns the maximum value.</summary>
UNIGINE_INLINE float max(float v0, float v1) { return (v0 > v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the maximum value.</summary>
UNIGINE_INLINE double max(double v0, double v1) { return (v0 > v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the maximum value.</summary>
UNIGINE_INLINE int max(int v0, int v1) { return (v0 > v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the maximum value.</summary>
UNIGINE_INLINE char max(char v0, char v1) { return (v0 > v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the maximum value.</summary>
UNIGINE_INLINE size_t max(size_t v0, size_t v1) { return (v0 > v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the maximum value.</summary>
UNIGINE_INLINE long long max(long long v0, long long v1) { return (v0 > v1) ? v0 : v1; }
/// <summary>Compares the arguments and returns the maximum value.</summary>
UNIGINE_INLINE long int max(long int v0, long int v1) { return (v0 > v1) ? v0 : v1; }

/// <summary>Returns the value clamped within the specified v0 and v1 limits.</summary>
UNIGINE_INLINE float clamp(float v, float v0, float v1) { return (v < v0) ? v0 : ((v > v1) ? v1 : v); }
/// <summary>Returns the value clamped within the specified v0 and v1 limits.</summary>
UNIGINE_INLINE double clamp(double v, double v0, double v1) { return (v < v0) ? v0 : ((v > v1) ? v1 : v); }
/// <summary>Returns the value clamped within the specified v0 and v1 limits.</summary>
UNIGINE_INLINE int clamp(int v, int v0, int v1) { return (v < v0) ? v0 : ((v > v1) ? v1 : v); }
/// <summary>Returns the value clamped within the specified v0 and v1 limits.</summary>
UNIGINE_INLINE char clamp(char v, char v0, char v1) { return (v < v0) ? v0 : ((v > v1) ? v1 : v); }
/// <summary>Returns the value clamped within the specified v0 and v1 limits.</summary>
UNIGINE_INLINE size_t clamp(size_t v, size_t v0, size_t v1) { return (v < v0) ? v0 : ((v > v1) ? v1 : v); }
/// <summary>Returns the value clamped within the specified v0 and v1 limits.</summary>
UNIGINE_INLINE long long clamp(long long v, long long v0, long long v1) { return (v < v0) ? v0 : ((v > v1) ? v1 : v); }
/// <summary>Returns the value clamped within the specified v0 and v1 limits.</summary>
UNIGINE_INLINE long int clamp(long int v, long int v0, long int v1) { return (v < v0) ? v0 : ((v > v1) ? v1 : v); }

/// <summary>Returns the value clamped within the range of [0.0f, 1.0f].</summary>
UNIGINE_INLINE float saturate(float v) { return (v < 0.0f) ? 0.0f : ((v > 1.0f) ? 1.0f : v); }
/// <summary>Returns the value clamped within the range of [0.0f, 1.0f].</summary>
UNIGINE_INLINE double saturate(double v) { return (v < 0.0) ? 0.0 : ((v > 1.0) ? 1.0 : v); }

/// <summary>Returns the interpolated value according to the following formula: v0 * (1.0f - k) + k.</summary>
UNIGINE_INLINE float lerpOne(float v0, float k) { return v0 * (1.0f - k) + k; }
/// <summary>Returns the interpolated value according to the following formula: v0 * (1.0f - k) + k.</summary>
UNIGINE_INLINE double lerpOne(double v0, double k) { return v0 * (1.0 - k) + k; }

/// <summary>Returns the interpolated value according to the following formula: v0 * (1.0f - k).</summary>
UNIGINE_INLINE float lerpZero(float v0, float k) { return v0 * (1.0f - k); }
/// <summary>Returns the interpolated value according to the following formula: v0 * (1.0f - k).</summary>
UNIGINE_INLINE double lerpZero(double v0, double k) { return v0 * (1.0 - k); }

/// <summary>Returns the interpolated value according to the following formula: v0 + (v 1 - v 0) * k .</summary>
UNIGINE_INLINE float lerp(float v0, float v1, float k) { return v0 + (v1 - v0) * k; }
/// <summary>Returns the interpolated value according to the following formula: v0 + (v 1 - v 0) * k .</summary>
UNIGINE_INLINE double lerp(double v0, double v1, double k) { return v0 + (v1 - v0) * k; }
/// <summary>Returns the interpolated value according to the following formula: v0 + (v 1 - v 0) * k .</summary>
UNIGINE_INLINE int lerp(int v0, int v1, int k) { return v0 + (((v1 - v0) * k) >> 16); }
/// <summary>Returns the interpolated value according to the following formula: v0 + (v 1 - v 0) * k .</summary>
UNIGINE_INLINE long long lerp(long long v0, long long v1, long long k) { return v0 + (v1 - v0) * k; }

/// <summary>Returns the value calculated according to the following formula: (v - v0) / (v1 - v0) clamped within 0.0f and 1.0f.</summary>
UNIGINE_INLINE float inverseLerp(float v0, float v1, float v) { return saturate((v - v0) / (v1 - v0)); }
/// <summary>Returns the value calculated according to the following formula: (v - v0) / (v1 - v0) clamped within 0.0f and 1.0f.</summary>
UNIGINE_INLINE double inverseLerp(double v0, double v1, double v) { return saturate((v - v0) / (v1 - v0)); }

/// <summary>Checks whether the value a is greater than or equal to b.</summary>
UNIGINE_INLINE bool step(float a, float b) { return a >= b; }

/// <summary>Performs overlay A over B with blending coefficient.</summary>
UNIGINE_INLINE float overlay(float a, float b, float x) { return max(lerp(a, lerp(1.0f - 2.0f * (1.0f - a) * (1.0f - b), 2.0f * a * b, toFloat(step(a, 0.5f))), x), 0.0f); }

/// <summary>Returns a smooth Hermite interpolation between 0 and 1, if x is in range [0, 1].</summary>
UNIGINE_INLINE float smoothstep(float x) { return x * x * (3.0f - 2.0f * x); }
/// <summary>Returns a smooth Hermite interpolation between 0 and 1, if x is in range [0, 1].</summary>
UNIGINE_INLINE double smoothstep(double x) { return x * x * (3.0 - 2.0 * x); }

/// <summary>Returns a smooth Hermite interpolation between 0 and 1 if x is in range [edge0, edge1].</summary>
UNIGINE_INLINE float smoothstep(float edge0, float edge1, float x)
{
	float t = saturate((x - edge0) / (edge1 - edge0));
	return t * t * (3.0f - 2.0f * t);
}
/// <summary>Returns a smooth Hermite interpolation between 0 and 1 if x is in range [edge0, edge1].</summary>
UNIGINE_INLINE double smoothstep(double edge0, double edge1, double x)
{
	double t = saturate((x - edge0) / (edge1 - edge0));
	return t * t * (3.0 - 2.0 * t);
}

/// <summary>Returns a smooth interpolation between 0 and 1 using a fifth-order polynomial function, if x is in range [0, 1].</summary>
UNIGINE_INLINE float smootherstep(float x) { return x * x * x * (x * (x * 6.0f - 15.0f) + 10.0f); }
/// <summary>Returns a smooth interpolation between 0 and 1 using a fifth-order polynomial function, if x is in range [0, 1].</summary>
UNIGINE_INLINE double smootherstep(double x) { return x * x * x * (x * (x * 6.0 - 15.0) + 10.0); }

/// <summary>Returns a smooth interpolation between 0 and 1 using a fifth-order polynomial function, if x is in range [edge0, edge1].</summary>
UNIGINE_INLINE float smootherstep(float edge0, float edge1, float x)
{
	float t = saturate((x - edge0) / (edge1 - edge0));
	return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}
/// <summary>Returns a smooth interpolation between 0 and 1 using a fifth-order polynomial function, if x is in range [edge0, edge1].</summary>
UNIGINE_INLINE double smootherstep(double edge0, double edge1, double x)
{
	double t = saturate((x - edge0) / (edge1 - edge0));
	return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

/// <summary>Normalizes an input angle to the range (−180, 180).</summary>
UNIGINE_INLINE float normalizeAngle(float angle)
{
	if (angle >= 180.0f)
		angle = mod(angle + 180.0f, 360.0f) - 180.0f;
	else if (angle <= -180.0f)
		angle = -mod(-angle - 180.0f, 360.0f) + 180.0f;
	return angle;
}

/// <summary>Returns the result of a component-wise multiplication of a 3-component vector (v0) with a scalar value (v1) by storing it in the array (ret).</summary>
UNIGINE_INLINE float *mul3(float *UNIGINE_RESTRICT ret, const float *UNIGINE_RESTRICT v0, float v1)
{
	ret[0] = v0[0] * v1;
	ret[1] = v0[1] * v1;
	ret[2] = v0[2] * v1;
	return ret;
}
/// <summary>Returns the result of a component-wise addition of three components of vectors by storing it in the array (ret).</summary>
UNIGINE_INLINE float *add3(float *UNIGINE_RESTRICT ret, const float *UNIGINE_RESTRICT v0, const float *UNIGINE_RESTRICT v1)
{
	ret[0] = v0[0] + v1[0];
	ret[1] = v0[1] + v1[1];
	ret[2] = v0[2] + v1[2];
	return ret;
}
/// <summary>Returns the result of a component-wise subtraction of three components of vectors by storing it in the array (ret).</summary>
UNIGINE_INLINE float *sub3(float *UNIGINE_RESTRICT ret, const float *UNIGINE_RESTRICT v0, const float *UNIGINE_RESTRICT v1)
{
	ret[0] = v0[0] - v1[0];
	ret[1] = v0[1] - v1[1];
	ret[2] = v0[2] - v1[2];
	return ret;
}
/// <summary>Returns the cross product of three components of vectors by storing it in the array (ret).</summary>
UNIGINE_INLINE float *cross3(float *UNIGINE_RESTRICT ret, const float *UNIGINE_RESTRICT v0, const float *UNIGINE_RESTRICT v1)
{
	ret[0] = v0[1] * v1[2] - v0[2] * v1[1];
	ret[1] = v0[2] * v1[0] - v0[0] * v1[2];
	ret[2] = v0[0] * v1[1] - v0[1] * v1[0];
	return ret;
}

/// <summary>Returns the dot product between a 2-component vector v and another 2-component vector defined by (x, y).</summary>
UNIGINE_INLINE float dot2(const float *v, float x, float y)
{
	return v[0] * x + v[1] * y;
}
/// <summary>Returns the dot product between a 3-component vector v and another 3-component vector defined by (x, y, z).</summary>
UNIGINE_INLINE float dot3(const float *v, float x, float y, float z)
{
	return v[0] * x + v[1] * y + v[2] * z;
}

/// <summary>Normalizes a 2-component vector, making it a unit vector (a vector with a length of 1) while preserving its direction.</summary>
UNIGINE_INLINE void normalize2(float *v)
{
	float ilength = 1.0f / sqrtf(v[0] * v[0] + v[1] * v[1]);
	v[0] = v[0] * ilength;
	v[1] = v[1] * ilength;
}
/// <summary>Normalizes a 3-component vector, making it a unit vector (a vector with a length of 1) while preserving its direction.</summary>
UNIGINE_INLINE void normalize3(float *v)
{
	float ilength = 1.0f / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] * ilength;
	v[1] = v[1] * ilength;
	v[2] = v[2] * ilength;
}

template <typename Type>
/// <summary>Extracts a specific bit from an integer value and returns it as a boolean.</summary>
UNIGINE_INLINE bool getBit(Type value, int bit) { return (((value) >> (bit)) & 0x01ULL); }

/// <summary>Checks if any of the bits specified in bits are set in mask.</summary>
UNIGINE_INLINE bool checkMask(const int mask, const int bits)
{
	return (mask & bits) != 0;
}
/// <summary>Checks if any of the bits specified in bits are set in mask.</summary>
UNIGINE_INLINE bool checkMask(const unsigned int mask, const unsigned int bits)
{
	return (mask & bits) != 0;
}
/// <summary>Checks if any of the bits specified in bits are set in mask.</summary>
UNIGINE_INLINE bool checkMask(const unsigned int mask, const int bits)
{
	return (mask & bits) != 0;
}
/// <summary>Checks if any of the bits specified in bits are set in mask.</summary>
UNIGINE_INLINE bool checkMask(const int mask, const unsigned int bits)
{
	return (mask & bits) != 0;
}

/// <summary>Returns the value that corresponds to the input value remapped within the limits of the output range.</summary>
UNIGINE_INLINE float reRange(float in, float in_range_min, float in_range_max, float out_range_min, float out_range_max)
{
	float temp = ((out_range_max - out_range_min) / (in_range_max - in_range_min));
	return in * temp + (out_range_min - in_range_min * temp);
}

/// <summary>Returns the value that corresponds to the input value remapped within the limits of the output range.</summary>
UNIGINE_INLINE double reRange(double in, double in_range_min, double in_range_max, double out_range_min, double out_range_max)
{
	double temp = ((out_range_max - out_range_min) / (in_range_max - in_range_min));
	return in * temp + (out_range_min - in_range_min * temp);
}

/// <summary>Checks if the input value is within the specified range.</summary>
constexpr bool checkRange(double value, double range_min, double range_max) { return value >= range_min && value <= range_max; }
/// <summary>Checks if the input value is within the specified range.</summary>
constexpr bool checkRange(float value, float range_min, float range_max) { return value >= range_min && value <= range_max; }
/// <summary>Checks if the input value is within the specified range.</summary>
constexpr bool checkRange(long long value, long long range_min, long long range_max) { return value >= range_min && value <= range_max; }
/// <summary>Checks if the input value is within the specified range.</summary>
constexpr bool checkRange(int value, int range_min, int range_max) { return value >= range_min && value <= range_max; }
/// <summary>Checks if the input value is within the specified range.</summary>
constexpr bool checkRange(short value, short range_min, short range_max) { return value >= range_min && value <= range_max; }
/// <summary>Checks if the input value is within the specified range.</summary>
constexpr bool checkRange(char value, char range_min, char range_max) { return value >= range_min && value <= range_max; }

// bezier curve
UNIGINE_INLINE float bezier_func(const float *curve, float k0)
{
	float k1 = 1.0f - k0;
	float k00 = k0 * k0;
	float k11 = k1 * k1;
	return curve[0] * k11 * k1 + (curve[1] * k11 * k0 + curve[2] * k00 * k1) * 3.0f + curve[3] * k00 * k0;
}
UNIGINE_INLINE double bezier_func(const double *curve, double k0)
{
	double k1 = 1.0 - k0;
	double k00 = k0 * k0;
	double k11 = k1 * k1;
	return curve[0] * k11 * k1 + (curve[1] * k11 * k0 + curve[2] * k00 * k1) * 3.0 + curve[3] * k00 * k0;
}
/// <summary>Calculates the value of a cubic Bezier function for the specified time.</summary>
/// <param name="times">Coordinates of the four points of the curve along the horizontal T (times) axis in range [0.0f, 1.0f].</param>
/// <param name="values">Coordinates of the four points of the curve along the vertical V (values) axis in the range [0.0f, 1.0f].</param>
/// <param name="time">Time in the range [0, 1], for which the value of the Bezier function is to be calculated.</param>
UNIGINE_INLINE float bezier(const float *times, const float *values, float time)
{
	float k0 = 0.0f;
	float k1 = 1.0f;
	float t1 = bezier_func(times, k1) - time;
	if (Math::abs(t1) < Consts::EPS)
		return bezier_func(values, k1);
	float t0 = bezier_func(times, k0) - time;
	if (Math::abs(t0) < Consts::EPS || t0 * t1 > 0.0f)
		return bezier_func(values, k0);
	for (int i = 0; i < 20; i++)
	{
		float k = (k0 + k1) * 0.5f;
		float t = bezier_func(times, k) - time;
		float v = t0 * t;
		if (v < 0.0f)
		{
			k1 = k;
			t1 = t;
		} else if (v > 0.0f)
		{
			k0 = k;
			t0 = t;
		} else
			return bezier_func(values, k);
	}
	float k = (k0 + k1) * 0.5f;
	return bezier_func(values, k);
}
/// <summary>Calculates the value of a cubic Bezier function for the specified time.</summary>
/// <param name="times">Coordinates of the four points of the curve along the horizontal T (times) axis in range [0.0f, 1.0f].</param>
/// <param name="values">Coordinates of the four points of the curve along the vertical V (values) axis in the range [0.0f, 1.0f].</param>
/// <param name="time">Time in the range [0, 1], for which the value of the Bezier function is to be calculated.</param>
UNIGINE_INLINE double bezier(const float *times, const double *values, float time)
{
	float k0 = 0.0f;
	float k1 = 1.0f;
	float t1 = bezier_func(times, k1) - time;
	if (Math::abs(t1) < Consts::EPS)
		return bezier_func(values, k1);
	float t0 = bezier_func(times, k0) - time;
	if (Math::abs(t0) < Consts::EPS || t0 * t1 > 0.0f)
		return bezier_func(values, k0);
	for (int i = 0; i < 20; i++)
	{
		float k = (k0 + k1) * 0.5f;
		float t = bezier_func(times, k) - time;
		float v = t0 * t;
		if (v < 0.0f)
		{
			k1 = k;
			t1 = t;
		} else if (v > 0.0f)
		{
			k0 = k;
			t0 = t;
		} else
			return bezier_func(values, k);
	}
	float k = (k0 + k1) * 0.5f;
	return bezier_func(values, k);
}

// 32bit hash
/// <summary>Computes a hash value from an input value.</summary>
UNIGINE_INLINE unsigned int hashInteger(unsigned int v)
{
	v ^= 0xdeadbeef;
	v ^= v >> 16;
	v *= 0x85ebca6b;
	v ^= v >> 13;
	v *= 0xc2b2ae35;
	v ^= v >> 16;
	return v;
}

/// <summary>Mixes two hashes.</summary>
UNIGINE_INLINE unsigned int hashMixer(unsigned int hash_0, unsigned int hash_1)
{
	hash_0 ^= 0x85ebca6b;
	hash_0 = hash_0 ^ ((hash_1 ^ 0xc2b2ae35) + 0x9e3779b9 + ((hash_1 ^ 0x85ebca6b) << 16) + (hash_1 >> 12));
	hash_0 = hash_0 * 1664525 + 1013904223;
	return hash_0;
}
/// <summary>Combines the provided hash with a hash of the specified value.</summary>
UNIGINE_INLINE unsigned int hashCombine(unsigned int hash, unsigned int value)
{
	return hashMixer(hash, hashInteger(value));
}
/// <summary>Computes a hash value from an input value.</summary>
UNIGINE_INLINE unsigned int hashInteger(float value) { return hashInteger(floatToUIntBits(value)); }
/// <summary>Combines the provided hash with a hash of the specified value.</summary>
UNIGINE_INLINE unsigned int hashCombine(unsigned int hash, float value) { return hashCombine(hash, floatToUIntBits(value)); }
/// <summary>Computes a hash value from an input value.</summary>
UNIGINE_INLINE unsigned int hashInteger(int value) { return hashInteger(toUInt(value)); }
/// <summary>Combines the provided hash with a hash of the specified value.</summary>
UNIGINE_INLINE unsigned int hashCombine(unsigned int hash, int value) { return hashCombine(hash, toUInt(value)); }

// 64bit hash
/// <summary>Computes a hash value from an input value.</summary>
UNIGINE_INLINE unsigned long long hashInteger(unsigned long long v)
{
	v ^= 0x2127599bf4325c37ULL;
	v ^= v >> 33;
	v *= 0xff51afd7ed558ccdULL;
	v ^= v >> 33;
	v *= 0xc4ceb9fe1a85ec53ULL;
	v ^= v >> 33;
	return v;
}
/// <summary>Mixes two hashes.</summary>
UNIGINE_INLINE unsigned long long hashMixer(unsigned long long hash_0, unsigned long long hash_1)
{
	hash_0 ^= 0xc4ceb9fe1a85ec53ULL;
	hash_0 = hash_0 ^ ((hash_1 ^ 0xff51afd7ed558ccdULL) + 0x9ddfea08eb382d69ULL + ((hash_1 ^ 0x2127599bf4325c37ULL) << 16) + (hash_1 >> 12));
	return hash_0 * 1664525 + 1013904223;
}
/// <summary>Combines the provided hash with a hash of the specified value.</summary>
UNIGINE_INLINE unsigned long long hashCombine(unsigned long long hash, unsigned long long value)
{
	return hashMixer(hash, hashInteger(value));
}
/// <summary>Computes a hash value from an input value.</summary>
UNIGINE_INLINE unsigned long long hashInteger(double value) { return hashInteger(floatToULongBits(value)); }
/// <summary>Combines the provided hash with a hash of the specified value.</summary>
UNIGINE_INLINE unsigned long long hashCombine(unsigned long long hash, double value) { return hashCombine(hash, floatToULongBits(value)); }
/// <summary>Computes a hash value from an input value.</summary>
UNIGINE_INLINE unsigned long long hashInteger(long long value) { return hashInteger(toULong(value)); }
/// <summary>Combines the provided hash with a hash of the specified value.</summary>
UNIGINE_INLINE unsigned long long hashCombine(unsigned long long hash, long long value) { return hashCombine(hash, toULong(value)); }

/// <summary>Casts the 64-bit hash value to the 32-bit hash value.</summary>
UNIGINE_INLINE unsigned int hashCast64To32(unsigned long long value) { return static_cast<unsigned int>(value % UINT_MAX); }

// alignment
template<class A, class B>
inline A makeAligned(A location, B align_value)
{
	return (align_value && (location % align_value) ? location + (align_value - location % align_value) : location);
}

// SSE
#ifdef USE_SSE
UNIGINE_INLINE __m128 _mm_rcp_ss_nr(__m128 v)
{
	__m128 iv = _mm_rcp_ss(v);
	iv = _mm_sub_ss(_mm_add_ss(iv, iv), _mm_mul_ss(v, _mm_mul_ss(iv, iv)));
	return _mm_sub_ss(_mm_add_ss(iv, iv), _mm_mul_ss(v, _mm_mul_ss(iv, iv)));
}

UNIGINE_INLINE __m128 _mm_rsqrt_ps_nr(__m128 v)
{
	__m128 iv = _mm_rsqrt_ps(v);
	__m128 nr = _mm_mul_ps(_mm_mul_ps(v, iv), iv);
	return _mm_mul_ps(_mm_mul_ps(_mm_set1_ps(0.5f), iv), _mm_sub_ps(_mm_set1_ps(3.0f), nr));
}

#define _mm_dot33_ps(v0, v1) _mm_dp_ps(v0, v1, 0x7f)
#define _mm_dot44_ps(v0, v1) _mm_dp_ps(v0, v1, 0xff)

UNIGINE_INLINE __m128 _mm_normalize3_ps(__m128 v)
{
	return _mm_mul_ps(v, _MM_SWIZZLE(_mm_rsqrt_ss(_mm_dp_ps(v, v, 0x7f)), X, X, X, X));
}

UNIGINE_INLINE __m128 _mm_normalize4_ps(__m128 v)
{
	return _mm_mul_ps(v, _MM_SWIZZLE(_mm_rsqrt_ss(_mm_dp_ps(v, v, 0xff)), X, X, X, X));
}

UNIGINE_INLINE __m128 _mm_cross_ps(__m128 v0, __m128 v1)
{
	__m128 v0_yzxw = _MM_SWIZZLE(v0, Y, Z, X, W);
	__m128 v1_yzxw = _MM_SWIZZLE(v1, Y, Z, X, W);
	__m128 v2 = _mm_sub_ps(_mm_mul_ps(v0, v1_yzxw), _mm_mul_ps(v1, v0_yzxw));
	return _MM_SWIZZLE(v2, Y, Z, X, W);
}

#endif // USE_SSE

} // end namespace Math

namespace MathLib
{
using Math::AXIS;
}

} // end namespace Unigine
