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

#include "UnigineBase.h"

/**
 * Unigine namespace.
 */
namespace Unigine
{

#ifdef _LINUX
	#ifdef Time
		#undef Time
	#endif
#endif

class Time
{
public:
	enum
	{
		CLOCKS_PER_SECOND = 1'000'000,
	};
	UNIGINE_INLINE static double microsecondsToNanoseconds(long long microseconds) { return (double)microseconds / (1'000 * CLOCKS_PER_SECOND); }
	UNIGINE_INLINE static double microsecondsToMilliseconds(long long microseconds) { return (double)(microseconds * 1'000) / CLOCKS_PER_SECOND; }
	UNIGINE_INLINE static double microsecondsToSeconds(long long microseconds) { return (double)microseconds / CLOCKS_PER_SECOND; }

	UNIGINE_INLINE static double millisecondsToNanoseconds(double milliseconds) { return milliseconds * 1'000'000.0; }
	UNIGINE_INLINE static double millisecondsToMicroseconds(double milliseconds) { return milliseconds * 1'000.0; }
	UNIGINE_INLINE static double millisecondsToSeconds(double milliseconds) { return milliseconds / 1'000.0; }

	UNIGINE_INLINE static double secondsToNanoseconds(double seconds) { return seconds * 1'000'000'000.0; }
	UNIGINE_INLINE static double secondsToMicroseconds(double seconds) { return seconds * 1'000'000.0; }
	UNIGINE_INLINE static double secondsToMilliseconds(double seconds) { return seconds * 1'000.0; }

	UNIGINE_INLINE static double hertzToNanoseconds(double hertz) { return 1'000'000'000.0 / hertz; }
	UNIGINE_INLINE static double hertzToMicroseconds(double hertz) { return 1'000'000.0 / hertz; }
	UNIGINE_INLINE static double hertzToMilliseconds(double hertz) { return 1'000.0 / hertz; }
	UNIGINE_INLINE static double hertzToSeconds(double hertz) { return 1.0 / hertz; }

	/**
	 * Returns CPU clocks counter.
	 *
	 * @return CPU clocks counter.
	 */
	UNIGINE_API static long long getClock();

	/**
	 * Returns time in microseconds.
	 *
	 * @return Time in microseconds.
	 */
	UNIGINE_API static long long get();

	/**
	 * Returns time in seconds.
	 *
	 * @return Time in seconds.
	 */
	UNIGINE_INLINE static double getSeconds() { return microsecondsToSeconds(get()); }

	/**
	 * Returns time in milliseconds.
	 *
	 * @return Time in milliseconds.
	 */
	UNIGINE_INLINE static double getMilliseconds() { return microsecondsToMilliseconds(get()); }
};

struct Timer
{
	long long begin_time{0};

	// return elapsed time
	UNIGINE_INLINE void begin() { begin_time = Time::get(); }
	UNIGINE_INLINE long long end() const { return Time::get() - begin_time; }
	UNIGINE_INLINE double endSeconds() const { return Time::microsecondsToSeconds(end()); }
	UNIGINE_INLINE double endMilliseconds() const { return Time::microsecondsToMilliseconds(end()); }

	UNIGINE_INLINE long long getBeginTime() const { return begin_time; }
};

} // namespace Unigine
