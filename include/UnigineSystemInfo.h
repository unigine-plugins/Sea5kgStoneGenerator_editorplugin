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
// DO NOT EDIT DIRECTLY. This is an auto-generated file. Your changes will be lost.

#pragma once

#include "UnigineBase.h"

namespace Unigine
{

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API SystemInfo
{
public:

	enum GPU_VENDOR
	{
		GPU_VENDOR_UNKNOWN = 0,
		GPU_VENDOR_AMD,
		GPU_VENDOR_NVIDIA,
		GPU_VENDOR_INTEL,
		GPU_VENDOR_ARM,
		GPU_VENDOR_APPLE,
		GPU_VENDOR_IMGTEC,
		GPU_VENDOR_QUALCOMM,
	};

	enum GPU_TYPE
	{
		GPU_TYPE_DISCRETE = 0,
		GPU_TYPE_INTEGRATED,
		GPU_TYPE_OTHER,
		GPU_TYPE_UNSUPPORTED,
	};

	enum PLATFORM_TYPE
	{
		PLATFORM_TYPE_WINDOWS,
		PLATFORM_TYPE_LINUX,
		PLATFORM_TYPE_XBOX_SERIES_S,
		PLATFORM_TYPE_XBOX_SERIES_X,
		PLATFORM_TYPE_PS5,
	};
	static const char *getBinaryInfo();
	static const char *getRevisionInfo();
	static const char *getOSInfo();
	static const char *getCPUInfo();
	static const char *getEngineInfo();
	static long long getMemoryFree();
	static long long getMemoryUsage();
	static long long getMemoryTotal();
	static long long getMemoryFreeCommitted();
	static long long getMemoryUsageCommitted();
	static long long getMemoryTotalCommitted();
	static int getCPUFrequency();
	static int getCPUCores();
	static int getCPUThreads();
	static bool hasMMX();
	static bool hasSSE();
	static bool hasSSE2();
	static bool hasSSE3();
	static bool hasSSE4();
	static bool hasSSE5();
	static bool hasAVX();
	static bool hasAVX2();
	static bool hasNeon();
	static bool hasHyperThreading();
	static void logInfo();
	static int getGPUCount();
	static int getGPUActive();
	static int findGPUByLuid(unsigned long long luid);
	static int findGPUByDeviceID(unsigned int device_id);
	static SystemInfo::GPU_TYPE getGPUType(int video_adapter_num = -1);
	static SystemInfo::GPU_VENDOR getGPUVendor(int video_adapter_num = -1);
	static int getGPUMemory(int video_adapter_num = -1);
	static int getGPUID(int video_adapter_num = -1);
	static unsigned int getGPUDeviceID(int video_adapter_num = -1);
	static unsigned long long getGPULuid(int video_adapter_num = -1);
	static const char *getGPUDescription(int video_adapter_num = -1);
	static const char *getGPUVendorName(int video_adapter_num = -1);
	static const char *getGPUDriver(int video_adapter_num = -1);
	static long long getGPUMemoryFree();
	static SystemInfo::PLATFORM_TYPE getPlatformType();
};

} // namespace Unigine
