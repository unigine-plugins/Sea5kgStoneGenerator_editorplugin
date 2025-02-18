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
#include "UniginePtr.h"
#include "UnigineMathLib.h"
#include "UnigineTextures.h"
#include "UnigineViewport.h"

namespace Unigine
{


class UNIGINE_API VRMarkerObject : public APIInterface
{
public:

	enum
	{
		MARKER_POSE_FLAGS_TRACING_OK = 0x1,
		MARKER_POSE_FLAGS_TRACING_LOST = 0x2,
		MARKER_POSE_FLAGS_TRACING_DISCONNECTED = 0x4,
		MARKER_POSE_FLAGS_HAS_POSITION = 0x8,
		MARKER_POSE_FLAGS_HAS_ROTATION = 0x10,
		MARKER_POSE_FLAGS_HAS_VELOCITY = 0x20,
		MARKER_POSE_FLAGS_HAS_ANGULAR_VELOCITY = 0x40,
		MARKER_POSE_FLAGS_HAS_ACCELERATION = 0x80,
		MARKER_POSE_FLAGS_HAS_CONFIDENCE = 0x100,
	};
	int getID() const;
	Math::mat4 getTransform() const;
	Math::Mat4 getWorldTransform() const;
	Math::Vec3 getSize() const;
	Math::Vec3 getVelocity() const;
	Math::Vec3 getAngularVelocity() const;
	Math::Vec3 getAcceleration() const;
	long long getRawTimestamp() const;
	double getConfidence() const;
	int getPoseFlags() const;
	void setDynamic(bool dynamic);
	bool isDynamic() const;
	void setLifetime(float lifetime);
	float getLifetime() const;
	void renderVisualizer() const;
};
typedef Ptr<VRMarkerObject> VRMarkerObjectPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API VRMixedReality
{
public:
	static bool isInitialized();
	static void applySettings();
	static void setChromaKeyEnabled(bool enabled);
	static bool isChromaKeyEnabled();
	static void setDepthTestEnabled(bool enabled);
	static bool isDepthTestEnabled();
	static void setAlphaBlendEnabled(bool enabled);
	static bool isAlphaBlendEnabled();
	static void setVideoEnabled(bool enabled);
	static bool isVideoEnabled();
	static void setDepthTestRangeEnabled(bool enabled);
	static bool isDepthTestRangeEnabled();
	static void setDepthTestRange(const Math::vec2 &range);
	static Math::vec2 getDepthTestRange();
	static int getChromaKeyConfigNum();
	static bool isChromaKeyConfigEnabled(int index);
	static void setChromaKeyConfigEnabled(int index, bool enabled);
	static Math::vec3 getChromaKeyConfigFalloff(int index);
	static void setChromaKeyConfigFalloff(int index, const Math::vec3 &falloff);
	static Math::vec3 getChromaKeyConfigTargetColor(int index);
	static void setChromaKeyConfigTargetColor(int index, const Math::vec3 &target_color);
	static Math::vec3 getChromaKeyConfigTolerance(int index);
	static void setChromaKeyConfigTolerance(int index, const Math::vec3 &tolerance);
	static void applyChromaKeySettings(int index);

	enum BLEND_MASKING_MODE
	{
		BLEND_MASKING_MODE_BEGIN,
		BLEND_MASKING_MODE_DISABLED = BLEND_MASKING_MODE_BEGIN,
		BLEND_MASKING_MODE_RESTRICT_VIDEO_TO_MASK,
		BLEND_MASKING_MODE_RESTRICT_VR_TO_MASK,
		BLEND_MASKING_MODE_RESTRICT_VR_TO_CHROMAKEY_REDUCED_BY_MASK,
		BLEND_MASKING_MODE_END = BLEND_MASKING_MODE_RESTRICT_VR_TO_CHROMAKEY_REDUCED_BY_MASK,
	};
	static void setBlendMaskingMode(VRMixedReality::BLEND_MASKING_MODE mode);
	static VRMixedReality::BLEND_MASKING_MODE getBlendMaskingMode();
	static void setBlendMaskingDebugEnabled(bool enabled);
	static bool isBlendMaskingDebugEnabled();
	static bool isBlendMaskingUsed();
	static Ptr<Texture> getCurrentBlendMaskColorBuffer();
	static bool cameraConfigLock();
	static void cameraConfigUnlock();

	enum CAMERA_PROPERTY_MODE
	{
		CAMERA_PROPERTY_MODE_DISABLED,
		CAMERA_PROPERTY_MODE_AUTO,
		CAMERA_PROPERTY_MODE_MANUAL,
	};

	enum CAMERA_EXPOSURE_TIME
	{
		CAMERA_EXPOSURE_TIME_UNKNWON,
		CAMERA_EXPOSURE_TIME_BEGIN,
		CAMERA_EXPOSURE_TIME_VALUE_91_MS = CAMERA_EXPOSURE_TIME_BEGIN,
		CAMERA_EXPOSURE_TIME_VALUE_125_MS,
		CAMERA_EXPOSURE_TIME_VALUE_250_MS,
		CAMERA_EXPOSURE_TIME_VALUE_500_MS,
		CAMERA_EXPOSURE_TIME_VALUE_1000_MS,
		CAMERA_EXPOSURE_TIME_VALUE_2000_MS,
		CAMERA_EXPOSURE_TIME_VALUE_4000_MS,
		CAMERA_EXPOSURE_TIME_VALUE_8000_MS,
		CAMERA_EXPOSURE_TIME_END = CAMERA_EXPOSURE_TIME_VALUE_8000_MS,
	};
	static void setCameraExposureTimeRaw(double raw);
	static double getCameraExposureTimeRaw();
	static void setCameraExposureTime(VRMixedReality::CAMERA_EXPOSURE_TIME time);
	static VRMixedReality::CAMERA_EXPOSURE_TIME getCameraExposureTime();
	static Vector<double> getCameraSupportedRawExposureTimes();
	static void setCameraExposureTimeMode(VRMixedReality::CAMERA_PROPERTY_MODE mode);
	static VRMixedReality::CAMERA_PROPERTY_MODE getCameraExposureTimeMode();

	enum CAMERA_WHITE_BALANCE
	{
		CAMERA_WHITE_BALANCE_UNKNWON,
		CAMERA_WHITE_BALANCE_BEGIN,
		CAMERA_WHITE_BALANCE_VALUE_2000_K = CAMERA_WHITE_BALANCE_BEGIN,
		CAMERA_WHITE_BALANCE_VALUE_3000_K,
		CAMERA_WHITE_BALANCE_VALUE_3500_K,
		CAMERA_WHITE_BALANCE_VALUE_4200_K,
		CAMERA_WHITE_BALANCE_VALUE_5000_K,
		CAMERA_WHITE_BALANCE_VALUE_5400_K,
		CAMERA_WHITE_BALANCE_VALUE_6500_K,
		CAMERA_WHITE_BALANCE_VALUE_8000_K,
		CAMERA_WHITE_BALANCE_VALUE_12000_K,
		CAMERA_WHITE_BALANCE_END = CAMERA_WHITE_BALANCE_VALUE_12000_K,
	};
	static void setCameraWhiteBalanceRaw(int raw);
	static int getCameraWhiteBalanceRaw();
	static void setCameraWhiteBalance(VRMixedReality::CAMERA_WHITE_BALANCE balance);
	static VRMixedReality::CAMERA_WHITE_BALANCE getCameraWhiteBalance();
	static Vector<int> getCameraSupportedRawWhiteBalances();
	static void setCameraWhiteBalanceMode(VRMixedReality::CAMERA_PROPERTY_MODE mode);
	static VRMixedReality::CAMERA_PROPERTY_MODE getCameraWhiteBalanceMode();

	enum CAMERA_ISO
	{
		CAMERA_ISO_UNKNWON,
		CAMERA_ISO_BEGIN,
		CAMERA_ISO_GAIN_100 = CAMERA_ISO_BEGIN,
		CAMERA_ISO_GAIN_200,
		CAMERA_ISO_GAIN_400,
		CAMERA_ISO_GAIN_800,
		CAMERA_ISO_GAIN_1600,
		CAMERA_ISO_GAIN_3200,
		CAMERA_ISO_GAIN_6400,
		CAMERA_ISO_END = CAMERA_ISO_GAIN_6400,
	};
	static void setCameraISORaw(int raw);
	static int getCameraISORaw();
	static void setCameraISO(VRMixedReality::CAMERA_ISO cameraiso);
	static VRMixedReality::CAMERA_ISO getCameraISO();
	static Vector<int> getCameraSupportedRawISO();
	static void setCameraISOMode(VRMixedReality::CAMERA_PROPERTY_MODE mode);
	static VRMixedReality::CAMERA_PROPERTY_MODE getCameraISOMode();

	enum CAMERA_FLICKER_COMPENSATION
	{
		CAMERA_FLICKER_COMPENSATION_UNKNWON,
		CAMERA_FLICKER_COMPENSATION_BEGIN,
		CAMERA_FLICKER_COMPENSATION_FREQ_50_HZ = CAMERA_FLICKER_COMPENSATION_BEGIN,
		CAMERA_FLICKER_COMPENSATION_FREQ_60_HZ,
		CAMERA_FLICKER_COMPENSATION_END = CAMERA_FLICKER_COMPENSATION_FREQ_60_HZ,
	};
	static void setCameraFlickerCompensationRaw(int raw);
	static int getCameraFlickerCompensationRaw();
	static void setCameraFlickerCompensation(VRMixedReality::CAMERA_FLICKER_COMPENSATION compensation);
	static VRMixedReality::CAMERA_FLICKER_COMPENSATION getCameraFlickerCompensation();
	static Vector<int> getCameraSupportedRawFlickerCompensations();
	static int getCameraMinSharpness();
	static int getCameraMaxSharpness();
	static void setCameraSharpness(int sharpness);
	static int getCameraSharpness();
	static void setCameraVSTReprojectionDistance(float distance);
	static float getCameraVSTReprojectionDistance();
	static void setCameraVSTReprojectionMode(VRMixedReality::CAMERA_PROPERTY_MODE mode);
	static VRMixedReality::CAMERA_PROPERTY_MODE getCameraVSTReprojectionMode();
	static void setViewOffset(float offset);
	static float getViewOffset();
	static void setMarkerTrackingEnabled(bool enabled);
	static bool isMarkerTrackingEnabled();
	static Ptr<VRMarkerObject> getMarkerObject(short index);
	static Ptr<VRMarkerObject> getMarkerObjectByID(short marker_id);
	static short getNumMarkerObjectVisible();

	enum CUBEMAP_MODE
	{
		CUBEMAP_MODE_BEGIN,
		CUBEMAP_MODE_DISABLED = CUBEMAP_MODE_BEGIN,
		CUBEMAP_MODE_ENVIRONMENT_OVERLAP,
		CUBEMAP_MODE_ENVIRONMENT_PRESET_0,
		CUBEMAP_MODE_ENVIRONMENT_PRESET_1,
		CUBEMAP_MODE_ENVIRONMENT_PRESET_2,
		CUBEMAP_MODE_END = CUBEMAP_MODE_ENVIRONMENT_PRESET_2,
	};
	static void setCubemapMode(VRMixedReality::CUBEMAP_MODE mode);
	static VRMixedReality::CUBEMAP_MODE getCubemapMode();
	static void setCubemapGGXQuality(Render::GGX_MIPMAPS_QUALITY quality);
	static Render::GGX_MIPMAPS_QUALITY getCubemapGGXQuality();

	enum OVERRIDE_COLOR_CORRECTION_MODE
	{
		OVERRIDE_COLOR_CORRECTION_MODE_BEGIN,
		OVERRIDE_COLOR_CORRECTION_MODE_DISABLED = OVERRIDE_COLOR_CORRECTION_MODE_BEGIN,
		OVERRIDE_COLOR_CORRECTION_MODE_EXPOSURE,
		OVERRIDE_COLOR_CORRECTION_MODE_EXPOSURE_WHITE_BALANCE,
		OVERRIDE_COLOR_CORRECTION_MODE_END = OVERRIDE_COLOR_CORRECTION_MODE_EXPOSURE_WHITE_BALANCE,
	};
	static void setOverrideColorCorrectionMode(VRMixedReality::OVERRIDE_COLOR_CORRECTION_MODE mode);
	static VRMixedReality::OVERRIDE_COLOR_CORRECTION_MODE getOverrideColorCorrectionMode();
	static Event<> &getEventDeviceConnected();
	static Event<> &getEventDeviceDisconnected();
	static Event<> &getEventChromakeyUpdate();
	static Event<> &getEventCameraPropertyUpdateExposureTime();
	static Event<> &getEventCameraPropertyUpdateWhiteBalance();
	static Event<> &getEventCameraPropertyUpdateISO();
	static Event<> &getEventCameraPropertyUpdateFlickerCompensation();
	static Event<> &getEventCameraPropertyUpdateSharpness();
	static Event<> &getEventCameraPropertyUpdateVSTReprojection();
};

} // namespace Unigine
