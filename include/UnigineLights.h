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

#include "UnigineNode.h"
#include "UnigineMathLib.h"
#include "UnigineImage.h"
#include "UnigineTextures.h"
#include "UnigineRender.h"

namespace Unigine
{


class UNIGINE_API LightLensFlare : public APIInterface
{
public:
	void setName(const char *name);
	const char *getName() const;
	void setSize(float size);
	float getSize() const;
	void setOffset(float offset);
	float getOffset() const;
	void setOffsetScale(float scale);
	float getOffsetScale() const;
	void setUVLowerLeft(const Math::vec2 &left);
	Math::vec2 getUVLowerLeft() const;
	void setUVUpperRight(const Math::vec2 &right);
	Math::vec2 getUVUpperRight() const;
	void setRotate(bool rotate);
	bool isRotate() const;
	void setColor(const Math::vec4 &color);
	Math::vec4 getColor() const;
	void setIntensity(float intensity);
	float getIntensity() const;
};
typedef Ptr<LightLensFlare> LightLensFlarePtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Light : public Node
{
public:
	static bool convertible(Node *node) { return node && node->isLight(); }


	enum SHAPE
	{
		SHAPE_DEFAULT = -1,
		SHAPE_POINT,
		SHAPE_SPHERE,
		SHAPE_CAPSULE,
		SHAPE_RECTANGLE,
	};

	enum MODE
	{
		MODE_DYNAMIC = 0,
		MODE_STATIC,
	};

	enum SHADOW_MODE
	{
		SHADOW_MODE_MIXED = 0,
		SHADOW_MODE_STATIC,
	};

	enum COLOR_MODE
	{
		COLOR_MODE_CLASSIC = 0,
		COLOR_MODE_TEMPERATURE,
	};

	enum SHADOW_FILTER
	{
		SHADOW_FILTER_GLOBAL = -1,
		SHADOW_FILTER_DISABLED,
		SHADOW_FILTER_LOW,
		SHADOW_FILTER_MEDIUM,
		SHADOW_FILTER_HIGH,
		SHADOW_FILTER_ULTRA,
	};

	enum SHADOW_PENUMBRA
	{
		SHADOW_PENUMBRA_GLOBAL = -1,
		SHADOW_PENUMBRA_DISABLED,
		SHADOW_PENUMBRA_LOW,
		SHADOW_PENUMBRA_MEDIUM,
		SHADOW_PENUMBRA_HIGH,
		SHADOW_PENUMBRA_ULTRA,
	};

	enum SHADOW_RESOLUTION
	{
		SHADOW_RESOLUTION_MODE_DEFAULT = -1,
		SHADOW_RESOLUTION_MODE_64,
		SHADOW_RESOLUTION_MODE_128,
		SHADOW_RESOLUTION_MODE_256,
		SHADOW_RESOLUTION_MODE_512,
		SHADOW_RESOLUTION_MODE_1024,
		SHADOW_RESOLUTION_MODE_2048,
		SHADOW_RESOLUTION_MODE_4096,
		SHADOW_RESOLUTION_MODE_8192,
		SHADOW_RESOLUTION_MODE_16384,
	};

	enum SHADOW_COLOR_MODE
	{
		SHADOW_COLOR_MODE_IES = 0,
		SHADOW_COLOR_MODE_SIMPLE,
	};
	Ptr<LightLensFlare> getLensFlare(int num);
	Math::vec4 calculateFinalColor() const;
	void setLensFlaresEnabled(bool enabled);
	bool isLensFlaresEnabled() const;
	void setLensFlaresTextureName(const char *name);
	const char *getLensFlaresTextureName() const;
	void setLensFlaresIntensity(float intensity);
	float getLensFlaresIntensity() const;
	void setLensFlaresOcclusionFade(float fade);
	float getLensFlaresOcclusionFade() const;
	void setLensFlaresOcclusionFadeBorder(float border);
	float getLensFlaresOcclusionFadeBorder() const;
	void setLensFlaresWorldPositionOffset(const Math::vec3 &offset);
	Math::vec3 getLensFlaresWorldPositionOffset() const;
	void setLensFlaresUseLightColor(bool color);
	bool isLensFlaresUseLightColor() const;
	void allocateLensFlares(int num);
	int getNumLensFlares() const;
	void addLensFlare();
	void removeLensFlare(int num);
	void cloneLensFlare(int num);
	void clearLensFlares();
	void setVisibleDistance(float distance);
	float getVisibleDistance() const;
	void setFadeDistance(float distance);
	float getFadeDistance() const;
	void setShadowDistance(float distance);
	float getShadowDistance() const;
	void setShadowFadeDistance(float distance);
	float getShadowFadeDistance() const;
	void setRenderOnWater(bool water);
	bool isRenderOnWater() const;
	void setRenderOnTransparent(bool transparent);
	bool isRenderOnTransparent() const;
	void setShadowMask(int mask);
	int getShadowMask() const;
	void setViewportMask(int mask);
	int getViewportMask() const;
	void setColorMode(Light::COLOR_MODE mode);
	Light::COLOR_MODE getColorMode() const;
	void setColor(const Math::vec4 &color);
	Math::vec4 getColor() const;
	void setIntensity(float intensity);
	float getIntensity() const;
	void setLux(float lux);
	float getLux() const;
	void setColorTemperature(float temperature);
	float getColorTemperature() const;
	void setColorFilter(const Math::vec4 &filter);
	Math::vec4 getColorFilter() const;
	void setAttenuationPower(float power);
	float getAttenuationPower() const;
	void setShadow(bool shadow);
	bool getShadow() const;
	void setShadowResolution(Light::SHADOW_RESOLUTION resolution);
	Light::SHADOW_RESOLUTION getShadowResolution() const;
	void setShadowBias(float bias);
	float getShadowBias() const;
	void setShadowNormalBias(float bias);
	float getShadowNormalBias() const;
	void setMode(Light::MODE mode);
	Light::MODE getMode() const;
	void setShadowMode(Light::SHADOW_MODE mode);
	Light::SHADOW_MODE getShadowMode() const;
	void setShadowFilterMode(Light::SHADOW_FILTER mode);
	Light::SHADOW_FILTER getShadowFilterMode() const;
	void setShadowFilter(float filter);
	float getShadowFilter() const;
	void setShadowPenumbraMode(Light::SHADOW_PENUMBRA mode);
	Light::SHADOW_PENUMBRA getShadowPenumbraMode() const;
	void setShadowPenumbra(float penumbra);
	float getShadowPenumbra() const;
	Ptr<Texture> getDynamicDepthTexture() const;
	void setBakedDepthTextureFilePath(const char *path);
	String getBakedDepthTextureFilePath() const;
	Ptr<Texture> getBakedDepthTexture() const;
	Ptr<Texture> getDynamicShadowColorTexture() const;
	void setShadowColorTextureMode(Light::SHADOW_COLOR_MODE mode);
	Light::SHADOW_COLOR_MODE getShadowColorTextureMode() const;
	Ptr<Texture> getShadowTexture() const;
	void setShadowScreenSpace(bool space);
	bool isShadowScreenSpace() const;
	void setShadowScreenSpaceNumRays(int rays);
	int getShadowScreenSpaceNumRays() const;
	void setShadowScreenSpaceNumSteps(int steps);
	int getShadowScreenSpaceNumSteps() const;
	void setShadowScreenSpaceNoiseRay(float ray);
	float getShadowScreenSpaceNoiseRay() const;
	void setShadowScreenSpaceNoiseStep(float step);
	float getShadowScreenSpaceNoiseStep() const;
	void setShadowScreenSpaceStepSizeFarDistance(float distance);
	float getShadowScreenSpaceStepSizeFarDistance() const;
	void setShadowScreenSpaceStepSizeNearDistance(float distance);
	float getShadowScreenSpaceStepSizeNearDistance() const;
	void setShadowScreenSpaceStepSizeNear(float val);
	float getShadowScreenSpaceStepSizeNear() const;
	void setShadowScreenSpaceStepSizeFar(float val);
	float getShadowScreenSpaceStepSizeFar() const;
	void setShadowScreenSpaceThresholdNearDistance(float distance);
	float getShadowScreenSpaceThresholdNearDistance() const;
	void setShadowScreenSpaceThresholdFarDistance(float distance);
	float getShadowScreenSpaceThresholdFarDistance() const;
	void setShadowScreenSpaceThresholdNear(float val);
	float getShadowScreenSpaceThresholdNear() const;
	void setShadowScreenSpaceThresholdFar(float val);
	float getShadowScreenSpaceThresholdFar() const;
	void setShadowScreenSpaceSoftness(float softness);
	float getShadowScreenSpaceSoftness() const;
	void setShadowScreenSpaceTranslucentDepth(float depth);
	float getShadowScreenSpaceTranslucentDepth() const;
	void setShadowScreenSpaceTranslucentDepthPerspectiveCompensation(float compensation);
	float getShadowScreenSpaceTranslucentDepthPerspectiveCompensation() const;
	void setShadowScreenSpaceTranslucentViewBias(float bias);
	float getShadowScreenSpaceTranslucentViewBias() const;
	bool saveStateLight(const Ptr<Stream> &stream) const;
	bool restoreStateLight(const Ptr<Stream> &stream);
	bool saveStateLensFlares(const Ptr<Stream> &stream) const;
	bool restoreStateLensFlares(const Ptr<Stream> &stream);
};
typedef Ptr<Light> LightPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API LightVoxelProbe : public Light
{
public:
	static Node::TYPE type() { return Node::LIGHT_VOXEL_PROBE; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }


	enum BAKE_INTERNAL_VOLUME
	{
		BAKE_INTERNAL_VOLUME_HALF = 0,
		BAKE_INTERNAL_VOLUME_FULL,
	};

	enum BAKE_QUALITY
	{
		BAKE_QUALITY_DRAFT = 0,
		BAKE_QUALITY_LOW,
		BAKE_QUALITY_MEDIUM,
		BAKE_QUALITY_HIGH,
		BAKE_QUALITY_ULTRA,
	};

	enum BLEND
	{
		BLEND_ALPHA_BLEND,
		BLEND_ADDITIVE,
		BLEND_MULTIPLICATIVE,
	};
	static Ptr<LightVoxelProbe> create();
	void setBoxSize(const Math::vec3 &size);
	Math::vec3 getBoxSize() const;
	void setVoxelSize(float size);
	float getVoxelSize() const;
	void setAttenuationDistance(const Math::vec3 &distance);
	Math::vec3 getAttenuationDistance() const;
	void setAttenuationPower(float power);
	float getAttenuationPower() const;
	void setUseSkyColor(bool color);
	bool isUseSkyColor() const;
	void setBlendMode(LightVoxelProbe::BLEND mode);
	LightVoxelProbe::BLEND getBlendMode() const;
	void setAmbientBias(float bias);
	float getAmbientBias() const;
	void setAmbientCubicFiltering(bool filtering);
	bool isAmbientCubicFiltering() const;
	void setReflectionEnabled(bool enabled);
	bool isReflectionEnabled() const;
	void setReflectionVisibilityRoughnessMin(float val);
	float getReflectionVisibilityRoughnessMin() const;
	void setReflectionVisibilityRoughnessMax(float val);
	float getReflectionVisibilityRoughnessMax() const;
	void setReflectionBias(float bias);
	float getReflectionBias() const;
	void setReflectionCubicFiltering(bool filtering);
	bool isReflectionCubicFiltering() const;
	void setBakeViewportMask(int mask);
	int getBakeViewportMask() const;
	void setBakeQuality(LightVoxelProbe::BAKE_QUALITY quality);
	LightVoxelProbe::BAKE_QUALITY getBakeQuality() const;
	void setBakeZFar(float zfar);
	float getBakeZFar() const;
	void setBakeInternalVolume(LightVoxelProbe::BAKE_INTERNAL_VOLUME volume);
	LightVoxelProbe::BAKE_INTERNAL_VOLUME getBakeInternalVolume() const;
	void setBakeVisibilityEmission(bool emission);
	bool isBakeVisibilityEmission() const;
	void setBakeVisibilitySky(bool sky);
	bool isBakeVisibilitySky() const;
	void setBakeVisibilityLightWorld(bool world);
	bool isBakeVisibilityLightWorld() const;
	void setBakeVisibilityLightOmni(bool omni);
	bool isBakeVisibilityLightOmni() const;
	void setBakeVisibilityLightProj(bool proj);
	bool isBakeVisibilityLightProj() const;
	void setBakeVisibilityVoxelProbe(bool probe);
	bool isBakeVisibilityVoxelProbe() const;
	void setBakeVisibilityEnvironmentProbe(bool probe);
	bool isBakeVisibilityEnvironmentProbe() const;
	void setBakeVisibilityLightmap(bool lightmap);
	bool isBakeVisibilityLightmap() const;
	void setTextureFilePath(const char *path);
	String getTextureFilePath() const;
	Math::ivec3 getResolution();
	size_t getVideoMemoryUsage();
};
typedef Ptr<LightVoxelProbe> LightVoxelProbePtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API LightEnvironmentProbe : public Light
{
public:
	static Node::TYPE type() { return Node::LIGHT_ENVIRONMENT_PROBE; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }


	enum PROJECTION_MODE
	{
		PROJECTION_MODE_SPHERE = 0,
		PROJECTION_MODE_BOX,
		PROJECTION_MODE_RAYMARCHING,
	};

	enum SECONDARY_BOUNCE_PROJECTION_MODE
	{
		SECONDARY_BOUNCE_PROJECTION_MODE_SPHERE = 0,
		SECONDARY_BOUNCE_PROJECTION_MODE_RAYMARCHING,
	};

	enum LAST_STEP_MODE
	{
		LAST_STEP_MODE_ENVIRONMENT_PROBE = 0,
		LAST_STEP_MODE_ONLY_SKY,
	};

	enum SPECULAR_BRDF_MODE
	{
		SPECULAR_BRDF_MODE_BLINN = 0,
		SPECULAR_BRDF_MODE_GGX,
	};

	enum GRAB_MODE
	{
		GRAB_MODE_BAKED = 0,
		GRAB_MODE_DYNAMIC,
	};

	enum GRAB_RESOLUTION
	{
		GRAB_RESOLUTION_MODE_32,
		GRAB_RESOLUTION_MODE_64,
		GRAB_RESOLUTION_MODE_128,
		GRAB_RESOLUTION_MODE_256,
		GRAB_RESOLUTION_MODE_512,
		GRAB_RESOLUTION_MODE_1024,
		GRAB_RESOLUTION_MODE_2048,
		GRAB_RESOLUTION_MODE_4096,
	};

	enum GRAB_SUPERSAMPLING
	{
		GRAB_SUPERSAMPLING_MODE_1,
		GRAB_SUPERSAMPLING_MODE_2,
		GRAB_SUPERSAMPLING_MODE_4,
		GRAB_SUPERSAMPLING_MODE_8,
	};

	enum GRAB_DYNAMIC_FACES_PER_FRAME
	{
		GRAB_DYNAMIC_FACES_PER_FRAME_MODE_1,
		GRAB_DYNAMIC_FACES_PER_FRAME_MODE_2,
		GRAB_DYNAMIC_FACES_PER_FRAME_MODE_3,
		GRAB_DYNAMIC_FACES_PER_FRAME_MODE_4,
		GRAB_DYNAMIC_FACES_PER_FRAME_MODE_5,
		GRAB_DYNAMIC_FACES_PER_FRAME_MODE_6,
	};
	static Ptr<LightEnvironmentProbe> create(const Math::vec4 &color, const Math::vec3 &attenuation_distance, const char *name = 0);
	void setProjectionMode(LightEnvironmentProbe::PROJECTION_MODE mode);
	LightEnvironmentProbe::PROJECTION_MODE getProjectionMode() const;
	void setAmbientEnabled(bool enabled);
	bool isAmbientEnabled() const;
	void setAmbientContrast(float contrast);
	float getAmbientContrast() const;
	void setSpecularEnabled(bool enabled);
	bool isSpecularEnabled() const;
	void setLocalSpace(bool space);
	bool isLocalSpace() const;
	void setSkyCutout(bool cutout);
	bool isSkyCutout() const;
	void setMultiplyBySkyColor(bool color);
	bool isMultiplyBySkyColor() const;
	void setCutoutByShadow(bool shadow);
	bool isCutoutByShadow() const;
	void setAdditiveBlending(bool blending);
	bool isAdditiveBlending() const;
	void setAttenuationDistance(const Math::vec3 &distance);
	Math::vec3 getAttenuationDistance() const;
	void setTextureFilePath(const char *path);
	String getTextureFilePath() const;
	void setSrgbModified(bool modified);
	bool isSrgbModified() const;
	void setReflectionCubicFiltering(bool filtering);
	bool isReflectionCubicFiltering() const;
	void setBoxAmbientParallax(float parallax);
	float getBoxAmbientParallax() const;
	void setBoxGlossCorners(float corners);
	float getBoxGlossCorners() const;
	void setBoxSize(const Math::vec3 &size);
	Math::vec3 getBoxSize() const;
	void setSphereReflectionParallax(float parallax);
	float getSphereReflectionParallax() const;
	void setRaymarchingNoiseFramesNumber(int number);
	int getRaymarchingNoiseFramesNumber() const;
	void setRaymarchingSecondaryBounceProjectionMode(LightEnvironmentProbe::SECONDARY_BOUNCE_PROJECTION_MODE mode);
	LightEnvironmentProbe::SECONDARY_BOUNCE_PROJECTION_MODE getRaymarchingSecondaryBounceProjectionMode() const;
	void setRaymarchingLastStepMode(LightEnvironmentProbe::LAST_STEP_MODE mode);
	LightEnvironmentProbe::LAST_STEP_MODE getRaymarchingLastStepMode() const;
	void setRaymarchingAmbientOcclusionIntensity(float intensity);
	float getRaymarchingAmbientOcclusionIntensity() const;
	void setRaymarchingAmbientOcclusionRadius(float radius);
	float getRaymarchingAmbientOcclusionRadius() const;
	void setRaymarchingDiffuseStepSize(float size);
	float getRaymarchingDiffuseStepSize() const;
	void setRaymarchingDiffuseNumRays(int rays);
	int getRaymarchingDiffuseNumRays() const;
	void setRaymarchingDiffuseNumSteps(int steps);
	int getRaymarchingDiffuseNumSteps() const;
	void setRaymarchingDiffuseThreshold(float threshold);
	float getRaymarchingDiffuseThreshold() const;
	void setRaymarchingDiffuseThresholdBinarySearch(float search);
	float getRaymarchingDiffuseThresholdBinarySearch() const;
	void setRaymarchingDiffuseThresholdOcclusion(float occlusion);
	float getRaymarchingDiffuseThresholdOcclusion() const;
	void setRaymarchingDiffuseMipOffset(float offset);
	float getRaymarchingDiffuseMipOffset() const;
	void setRaymarchingDiffuseInformationLostRaysMultiplier(float multiplier);
	float getRaymarchingDiffuseInformationLostRaysMultiplier() const;
	void setRaymarchingDiffuseReconstructionSamples(int samples);
	int getRaymarchingDiffuseReconstructionSamples() const;
	void setRaymarchingDiffusePerspectiveCompensation(float compensation);
	float getRaymarchingDiffusePerspectiveCompensation() const;
	void setRaymarchingDiffuseNonLinearStepSize(float size);
	float getRaymarchingDiffuseNonLinearStepSize() const;
	void setRaymarchingDiffuseTranslucenceAnisotropy(float anisotropy);
	float getRaymarchingDiffuseTranslucenceAnisotropy() const;
	void setRaymarchingSpecularStepSize(float size);
	float getRaymarchingSpecularStepSize() const;
	void setRaymarchingSpecularNumRays(int rays);
	int getRaymarchingSpecularNumRays() const;
	void setRaymarchingSpecularNumSteps(int steps);
	int getRaymarchingSpecularNumSteps() const;
	void setRaymarchingSpecularNumStepsRoughnessThreshold(float threshold);
	float getRaymarchingSpecularNumStepsRoughnessThreshold() const;
	void setRaymarchingSpecularThreshold(float threshold);
	float getRaymarchingSpecularThreshold() const;
	void setRaymarchingSpecularThresholdBinarySearch(float search);
	float getRaymarchingSpecularThresholdBinarySearch() const;
	void setRaymarchingSpecularThresholdOcclusion(float occlusion);
	float getRaymarchingSpecularThresholdOcclusion() const;
	void setRaymarchingSpecularMipOffset(float offset);
	float getRaymarchingSpecularMipOffset() const;
	void setRaymarchingSpecularInformationLostRaysMultiplier(float multiplier);
	float getRaymarchingSpecularInformationLostRaysMultiplier() const;
	void setRaymarchingSpecularReplaceWithDiffuseRoughnessThreshold(float threshold);
	float getRaymarchingSpecularReplaceWithDiffuseRoughnessThreshold() const;
	void setRaymarchingSpecularReconstructionSamples(int samples);
	int getRaymarchingSpecularReconstructionSamples() const;
	void setRaymarchingSpecularPerspectiveCompensation(float compensation);
	float getRaymarchingSpecularPerspectiveCompensation() const;
	void setRaymarchingSpecularNonLinearStepSize(float size);
	float getRaymarchingSpecularNonLinearStepSize() const;
	void setRaymarchingSpecularBRDF(LightEnvironmentProbe::SPECULAR_BRDF_MODE raymarchingspecularbrdf);
	LightEnvironmentProbe::SPECULAR_BRDF_MODE getRaymarchingSpecularBRDF() const;
	void setGrabMode(LightEnvironmentProbe::GRAB_MODE mode);
	LightEnvironmentProbe::GRAB_MODE getGrabMode() const;
	void setGrabGGXMipmapsQuality(Render::GGX_MIPMAPS_QUALITY quality);
	Render::GGX_MIPMAPS_QUALITY getGrabGGXMipmapsQuality() const;
	void setGrabResolution(LightEnvironmentProbe::GRAB_RESOLUTION resolution);
	LightEnvironmentProbe::GRAB_RESOLUTION getGrabResolution() const;
	void setGrabSupersampling(LightEnvironmentProbe::GRAB_SUPERSAMPLING supersampling);
	LightEnvironmentProbe::GRAB_SUPERSAMPLING getGrabSupersampling() const;
	void setGrabDistanceScale(float scale);
	float getGrabDistanceScale() const;
	void setGrabEnvironmentAmbientIntensity(float intensity);
	float getGrabEnvironmentAmbientIntensity() const;
	void setGrabEnvironmentReflectionIntensity(float intensity);
	float getGrabEnvironmentReflectionIntensity() const;
	void setGrabZNear(float znear);
	float getGrabZNear() const;
	void setGrabZFar(float zfar);
	float getGrabZFar() const;
	void setGrabViewportMask(int mask);
	int getGrabViewportMask() const;
	void setGrabByBakeLighting(bool lighting);
	bool isGrabByBakeLighting() const;
	void setGrabDynamicFacesPerFrame(LightEnvironmentProbe::GRAB_DYNAMIC_FACES_PER_FRAME frame);
	LightEnvironmentProbe::GRAB_DYNAMIC_FACES_PER_FRAME getGrabDynamicFacesPerFrame() const;
	void setGrabBakeVisibilityEmission(bool emission);
	bool isGrabBakeVisibilityEmission() const;
	void setGrabBakeVisibilitySky(bool sky);
	bool isGrabBakeVisibilitySky() const;
	void setGrabBakeVisibilityLightWorld(bool world);
	bool isGrabBakeVisibilityLightWorld() const;
	void setGrabBakeVisibilityLightOmni(bool omni);
	bool isGrabBakeVisibilityLightOmni() const;
	void setGrabBakeVisibilityLightProj(bool proj);
	bool isGrabBakeVisibilityLightProj() const;
	void setGrabBakeVisibilityVoxelProbe(bool probe);
	bool isGrabBakeVisibilityVoxelProbe() const;
	void setGrabBakeVisibilityEnvironmentProbe(bool probe);
	bool isGrabBakeVisibilityEnvironmentProbe() const;
	void setGrabBakeVisibilityLightmap(bool lightmap);
	bool isGrabBakeVisibilityLightmap() const;
};
typedef Ptr<LightEnvironmentProbe> LightEnvironmentProbePtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API LightPlanarProbe : public Light
{
public:
	static Node::TYPE type() { return Node::LIGHT_PLANAR_PROBE; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }


	enum REFLECTION_RESOLUTION
	{
		REFLECTION_RESOLUTION_MODE_HEIGHT,
		REFLECTION_RESOLUTION_MODE_HALF_HEIGHT,
		REFLECTION_RESOLUTION_MODE_QUART_HEIGHT,
		REFLECTION_RESOLUTION_MODE_128,
		REFLECTION_RESOLUTION_MODE_256,
		REFLECTION_RESOLUTION_MODE_512,
		REFLECTION_RESOLUTION_MODE_1024,
		REFLECTION_RESOLUTION_MODE_2048,
		REFLECTION_RESOLUTION_MODE_4096,
	};
	static Ptr<LightPlanarProbe> create();
	void setProjectionSize(const Math::vec3 &size);
	Math::vec3 getProjectionSize() const;
	void setAttenuationDistance(const Math::vec3 &distance);
	Math::vec3 getAttenuationDistance() const;
	void setRoughnessSamples(int samples);
	int getRoughnessSamples() const;
	void setReflectionResolution(LightPlanarProbe::REFLECTION_RESOLUTION resolution);
	LightPlanarProbe::REFLECTION_RESOLUTION getReflectionResolution() const;
	void setTwoSided(bool sided);
	bool isTwoSided() const;
	void setStereoPerEyeEnabled(bool enabled);
	bool isStereoPerEyeEnabled() const;
	void setDistanceScale(float scale);
	float getDistanceScale() const;
	void setReflectionDistance(float distance);
	float getReflectionDistance() const;
	void setReflectionViewportMask(int mask);
	int getReflectionViewportMask() const;
	int getVisibilitySkipFlags() const;
	void setZNear(float znear);
	float getZNear() const;
	void setZFar(float zfar);
	float getZFar() const;
	void setReflectionVisibilityRoughnessMin(float val);
	float getReflectionVisibilityRoughnessMin() const;
	void setReflectionVisibilityRoughnessMax(float val);
	float getReflectionVisibilityRoughnessMax() const;
	void setVisibilitySky(bool sky);
	bool isVisibilitySky() const;
	void setParallax(float parallax);
	float getParallax() const;
	void setNoiseIntensity(float intensity);
	float getNoiseIntensity() const;
	void setReflectionOffset(float offset);
	float getReflectionOffset() const;
};
typedef Ptr<LightPlanarProbe> LightPlanarProbePtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API LightOmni : public Light
{
public:
	static Node::TYPE type() { return Node::LIGHT_OMNI; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<LightOmni> create(const Math::vec4 &color, float attenuation_distance, const char *name = 0);
	void setAttenuationDistance(float distance);
	float getAttenuationDistance() const;
	void setNearAttenuationDistance(float distance);
	float getNearAttenuationDistance() const;
	void setNearAttenuationGradientLength(float length);
	float getNearAttenuationGradientLength() const;
	void setShadowNearClippingDistance(float distance);
	float getShadowNearClippingDistance() const;
	void setShapeRadius(float radius);
	float getShapeRadius() const;
	void setShapeLength(float length);
	float getShapeLength() const;
	void setShapeHeight(float height);
	float getShapeHeight() const;
	void setShapeType(Light::SHAPE type);
	Light::SHAPE getShapeType() const;
	Math::vec3 getSize() const;
	Math::vec2 getShadowDepthRange() const;
	void setTextureFilePath(const char *path);
	String getTextureFilePath() const;
	int setTextureImage(const Ptr<Image> &image, bool dynamic = false);
	int getTextureImage(const Ptr<Image> &image) const;
	void setTexture(const Ptr<Texture> &texture);
	Ptr<Texture> getTexture() const;
	void setShadowSideEnabled(int side, int enable);
	int isShadowSideEnabled(int side) const;
};
typedef Ptr<LightOmni> LightOmniPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API LightProj : public Light
{
public:
	static Node::TYPE type() { return Node::LIGHT_PROJ; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<LightProj> create(const Math::vec4 &color, float attenuation_distance, float fov, const char *name = 0);
	void setAttenuationDistance(float distance);
	float getAttenuationDistance() const;
	void setNearAttenuationDistance(float distance);
	float getNearAttenuationDistance() const;
	void setNearAttenuationGradientLength(float length);
	float getNearAttenuationGradientLength() const;
	void setShadowNearClippingDistance(float distance);
	float getShadowNearClippingDistance() const;
	void setShapeType(Light::SHAPE type);
	Light::SHAPE getShapeType() const;
	void setShapeRadius(float radius);
	float getShapeRadius() const;
	void setShapeLength(float length);
	float getShapeLength() const;
	void setShapeHeight(float height);
	float getShapeHeight() const;
	void setFov(float fov);
	float getFov() const;
	void setPenumbra(float penumbra);
	float getPenumbra() const;
	void setIESRelativeToFov(bool fov);
	bool isIESRelativeToFov() const;
	Math::vec2 getShadowDepthRange() const;
	Math::mat4 getProjection() const;
	Math::mat4 getShadowProjection() const;
	void setTextureFilePath(const char *path);
	String getTextureFilePath() const;
	int setTextureImage(const Ptr<Image> &image, bool dynamic = false);
	int getTextureImage(const Ptr<Image> &image) const;
	void setTexture(const Ptr<Texture> &texture);
	Ptr<Texture> getTexture() const;
};
typedef Ptr<LightProj> LightProjPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API LightWorld : public Light
{
public:
	static Node::TYPE type() { return Node::LIGHT_WORLD; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }


	enum SHADOW_CASCADE_MODE
	{
		SHADOW_CASCADE_MODE_DYNAMIC,
		SHADOW_CASCADE_MODE_STATIC,
	};

	enum SCATTERING
	{
		SCATTERING_NONE = 0,
		SCATTERING_SUN,
		SCATTERING_MOON,
	};
	static Ptr<LightWorld> create(const Math::vec4 &color);
	void setScattering(LightWorld::SCATTERING scattering);
	LightWorld::SCATTERING getScattering() const;
	void setDisableAngle(float angle);
	float getDisableAngle() const;
	void setShadowCascadeMode(LightWorld::SHADOW_CASCADE_MODE mode);
	LightWorld::SHADOW_CASCADE_MODE getShadowCascadeMode() const;
	void setNumShadowCascades(int cascades);
	int getNumShadowCascades() const;
	void setOneCascadePerFrame(bool frame);
	bool isOneCascadePerFrame() const;
	void setShadowCascadeBorder(int num, float r);
	float getShadowCascadeBorder(int num) const;
	Math::vec2 getRenderShadowDepthRange() const;
	Math::Mat4 getRenderShadowCascadeModelview(int num) const;
	Math::mat4 getRenderShadowCascadeProjection(int num) const;
	void updateRenderShadowCascadeMatrices(const Math::Vec3 &camera_position, float zfar);
	void setShadowHeight(float height);
	float getShadowHeight() const;
	void setShadowWidth(float width);
	float getShadowWidth() const;
	void setShadowZFar(float zfar);
	float getShadowZFar() const;
	void setMode(int mode);
	int getMode() const;
};
typedef Ptr<LightWorld> LightWorldPtr;

} // namespace Unigine
