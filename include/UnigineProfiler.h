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

#include "UnigineMathLib.h"
#include "UnigineGui.h"
#include "UnigineWidgets.h"

namespace Unigine
{

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Profiler
{
public:
	static bool isInitialized();
	static void setEnabled(bool enabled);
	static bool isEnabled();
	static void begin(const char *name);
	static void begin(const char *name, const Math::vec4 &color);
	static float end();
	static int beginMicro(const char *name, bool gpu = false);
	static void endMicro(int id);
	static float getValue(const char *name);
	static void setValue(const char *name, const char *units, int value, int max_value, float *arg5);
	static void setValue(const char *name, const char *units, float value, float max_value, float *arg5);
	static int getNumCounters();
	static int findCounter(const char *name);
	static const char *getCounterName(int num);
	static const char *getCounterText(int num);
	static Math::vec4 getCounterColor(int num);
	static float getCounterValue(int num);
	static long long getCounterFrame(int num);
	static bool isCounterActive(int num);
	static bool isCounterSeparator(int num);
	static const char *getMicroprofileUrl();
	static void setGui(const Ptr<Gui> &gui);
	static Ptr<Gui> getGui();
};


struct ScopedProfiler
{
	int id;
	ScopedProfiler(const char *name, bool gpu = false)
	{
		if (Profiler::isInitialized())
			id = Profiler::beginMicro(name, gpu);
		else
			id = -1;
	}
	~ScopedProfiler()
	{
		if (Profiler::isInitialized() && id != -1)
			Profiler::endMicro(id);
	}
};
#define UNIGINE_PROFILER_SCOPED(NAME) ::Unigine::ScopedProfiler UNIGINE_CONCATENATE(unigine_prof, __LINE__)(NAME)
#define UNIGINE_PROFILER_SCOPED_GPU(NAME) ::Unigine::ScopedProfiler UNIGINE_CONCATENATE(unigine_prof, __LINE__)(NAME, true)
#define UNIGINE_PROFILER_FUNCTION ::Unigine::ScopedProfiler UNIGINE_CONCATENATE(unigine_prof, __LINE__)(__FUNCTION__)
#define UNIGINE_PROFILER_FUNCTION_GPU ::Unigine::ScopedProfiler UNIGINE_CONCATENATE(unigine_prof, __LINE__)(__FUNCTION__, true)

} // namespace Unigine
