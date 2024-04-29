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
#include "UnigineCallback.h"
#include "UnigineTextures.h"
#include "UnigineViewport.h"
#include "UnigineInput.h"

namespace Unigine
{

class VRMixedReality;
class VREyeTracking;
//////////////////////////////////////////////////////////////////////////

class UNIGINE_API VR
{
public:
	static int isInitialized();

	enum API
	{
		API_NULL,
		API_VARJO,
		API_OPENVR,
	};

	enum VIEWPORT_TYPE
	{
		VIEWPORT_TYPE_CONTEXT,
		VIEWPORT_TYPE_FOCUS,
		VIEWPORT_TYPE_NUM,
	};

	enum EYE_TYPE
	{
		EYE_TYPE_LEFT,
		EYE_TYPE_RIGHT,
		EYE_TYPE_NUM,
	};

	enum
	{
		TOTAL_VIEWPORTS = 4,
	};

	enum MIRROR_MODE
	{
		MIRROR_MODE_BEGIN,
		MIRROR_MODE_BLACK_SCREEN = MIRROR_MODE_BEGIN,
		MIRROR_MODE_MONO_LEFT,
		MIRROR_MODE_MONO_RIGHT,
		MIRROR_MODE_STEREO,
		MIRROR_MODE_END = MIRROR_MODE_STEREO,
	};

	enum WINDOW_MODE
	{
		WINDOW_MODE_BEGIN,
		WINDOW_MODE_DISABLED = WINDOW_MODE_BEGIN,
		WINDOW_MODE_MAIN,
		WINDOW_MODE_END = WINDOW_MODE_MAIN,
	};

	enum TRACKING_SPACE
	{
		TRACKING_SPACE_BEGIN,
		TRACKING_SPACE_UNKNOWN = TRACKING_SPACE_BEGIN,
		TRACKING_SPACE_SEATED,
		TRACKING_SPACE_STANDING,
		TRACKING_SPACE_END = TRACKING_SPACE_STANDING,
	};
	static void setRenderEnabled(bool enabled);
	static bool isRenderEnabled();
	static void setPeripheralRenderingModeEnabled(bool enabled);
	static bool isPeripheralRenderingModeEnabled();
	static void setMirrorMode(VR::MIRROR_MODE mode);
	static VR::MIRROR_MODE getMirrorMode();
	static void setWindowMode(VR::WINDOW_MODE mode);
	static VR::WINDOW_MODE getWindowMode();
	static void setTrackingSpace(VR::TRACKING_SPACE space);
	static VR::TRACKING_SPACE getTrackingSpace();
	static void setMotionPrediction(bool prediction);
	static bool isMotionPrediction();
	static void setMotionPredictionVelocityPrecision(float precision);
	static float getMotionPredictionVelocityPrecision();
	static void setMotionPredictionVelocityTimeDelta(float delta);
	static float getMotionPredictionVelocityTimeDelta();
	static void setFoveatedRenderingEnabled(bool enabled);
	static bool isFoveatedRenderingEnabled();
	static const char *getApiName();
	static VR::API getApiType();
	static float getHMDRefreshRate();
	static Math::ivec2 getHMDResolution(VR::VIEWPORT_TYPE viewport_type = VR::VIEWPORT_TYPE_CONTEXT);
	static Math::Vec3 getHandtrackingOffset();
	static bool isPeripheralRenderingModeUsed();
	static bool hasFeatureMixedReality();
	static bool hasFeatureEyeTracking();
	static bool hasFeatureTrackingSpaceRaw();
	static bool hasFeatureMotionPrediction();
	static bool hasFeatureFoveatedRendering();
	static bool hasFeatureReportProximitySensor();
	static bool hasFeatureSupportForTreadmill();
	static bool hasFeatureSupportForBaseStations();
	static bool hasFeatureSupportForTrackers();
	static bool hasFeatureSupportForRenderModelComponents();
	static bool isHMDConnected();
	static bool isUsingFoveatedRendering();
	static Ptr<Viewport> getViewport();
	static bool isSteamVRRendersControllers();
	static void resetZeroPose();
	static Event<int> &getEventDeviceRenderModelChanged();
	static Event<> &getEventAudioSettingsChanged();
	static Event<bool> &getEventRenderModelsVisibility();
};

} // namespace Unigine
