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
// DO NOT EDIT DIRECTLY. This is an auto-generated file. Your changes will be lost.

#pragma once

#include "UnigineBase.h"
#include "UniginePtr.h"
#include "UnigineMathLib.h"
#include "UnigineTextures.h"
#include "UnigineViewport.h"

namespace Unigine
{

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API VREyeTracking
{
public:
	static int isInitialized();

	enum STATUS
	{
		STATUS_INVALID,
		STATUS_ADJUST,
		STATUS_VALID,
	};

	enum EYE_STATUS
	{
		EYE_STATUS_INVALID,
		EYE_STATUS_VISIBLE,
		EYE_STATUS_COMPENSATED,
		EYE_STATUS_TRACKED,
	};
	static bool isValid();
	static void requestCalibration();
	static Math::Vec3 getFocusWorldPosition();
	static Math::vec3 getGazeWorldDirection();
	static Math::Vec3 getLeftEyeWorldPosition();
	static Math::vec3 getLeftEyeWorldDirection();
	static float getLeftPupilDiameter();
	static float getLeftPupilIrisDiameterRatio();
	static float getLeftIrisDiameter();
	static float getLeftOpenness();
	static VREyeTracking::EYE_STATUS getLeftStatus();
	static float getRightPupilDiameter();
	static float getRightPupilIrisDiameterRatio();
	static float getRightIrisDiameter();
	static float getRightOpenness();
	static Math::Vec3 getRightEyeWorldPosition();
	static Math::vec3 getRightEyeWorldDirection();
	static VREyeTracking::EYE_STATUS getRightStatus();
	static float getIPD();
	static long long getRawCaptureTime();
	static double getFocusDistance();
	static double getStability();
	static VREyeTracking::STATUS getStatus();
	static long long getRawFrame();
	static void setVisualizerEnabled(bool enabled);
	static bool isVisualizerEnabled();
};

} // namespace Unigine
