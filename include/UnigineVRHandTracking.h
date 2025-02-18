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

class VRHand;

class UNIGINE_API VRBone : public APIInterface
{
public:

	enum TYPE
	{
		TYPE_PALM,
		TYPE_WRIST,
		TYPE_THUMB_METACARPAL,
		TYPE_THUMB_PROXIMAL,
		TYPE_THUMB_DISTAL,
		TYPE_THUMB_TIP,
		TYPE_INDEX_METACARPAL,
		TYPE_INDEX_PROXIMAL,
		TYPE_INDEX_INTERMEDIATE,
		TYPE_INDEX_DISTAL,
		TYPE_INDEX_TIP,
		TYPE_MIDDLE_METACARPAL,
		TYPE_MIDDLE_PROXIMAL,
		TYPE_MIDDLE_INTERMEDIATE,
		TYPE_MIDDLE_DISTAL,
		TYPE_MIDDLE_TIP,
		TYPE_RING_METACARPAL,
		TYPE_RING_PROXIMAL,
		TYPE_RING_INTERMEDIATE,
		TYPE_RING_DISTAL,
		TYPE_RING_TIP,
		TYPE_LITTLE_METACARPAL,
		TYPE_LITTLE_PROXIMAL,
		TYPE_LITTLE_INTERMEDIATE,
		TYPE_LITTLE_DISTAL,
		TYPE_LITTLE_TIP,
		NUM_TYPES,
	};
	const char *getName() const;
	VRBone::TYPE getType() const;
	bool isTransformValid() const;
	bool isVelocityValid() const;
	Math::mat4 getTransform() const;
	Math::Mat4 getWorldTransform() const;
	Math::vec3 getWorldLinearVelocity() const;
	Math::vec3 getWorldAngularVelocity() const;
	Math::vec3 getWorldAngularAcceleration() const;
	float getRadius() const;
	Ptr<VRBone> getParent() const;
	int getNumChildren() const;
	Ptr<VRBone> getChild(int i);
	Ptr<VRHand> getHand() const;
	void renderBasis() const;
	void renderVelocity() const;
	void renderVisualizer(const Math::vec4 &color) const;
};
typedef Ptr<VRBone> VRBonePtr;


class UNIGINE_API VRHand : public APIInterface
{
public:

	enum TYPE
	{
		TYPE_LEFT = 0,
		TYPE_RIGHT,
		NUM_TYPES,
	};
	VRHand::TYPE getType() const;
	Ptr<VRBone> getRootBone() const;
	Ptr<VRBone> getBone(VRBone::TYPE type);
	void renderVisualizer() const;
	bool isHoldingController() const;
	bool isActive() const;
};
typedef Ptr<VRHand> VRHandPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API VRHandTracking
{
public:
	static bool isInitialized();
	static Ptr<VRHand> getHandLeft();
	static Ptr<VRHand> getHandRight();
	static void setVisualizerEnabled(bool enabled);
	static bool isVisualizerEnabled();
	static void setShowBasis(bool basis);
	static bool isShowBasis();
	static void setShowVelocity(bool velocity);
	static bool isShowVelocity();
	static void setShowBoneSizes(bool sizes);
	static bool isShowBoneSizes();
};

} // namespace Unigine
