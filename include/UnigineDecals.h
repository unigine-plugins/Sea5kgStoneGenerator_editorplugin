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

#include "UnigineMaterial.h"
#include "UnigineNode.h"
#include "UnigineMesh.h"

namespace Unigine
{

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Decal : public Node
{
public:
	static bool convertible(Node *node) { return node && node->isDecal(); }

	void setMaterialFilePath(const char *path);
	String getMaterialFilePath() const;
	void setMaterialGUID(const UGUID &materialguid);
	UGUID getMaterialGUID() const;
	void setMaterial(const Ptr<Material> &material);
	Ptr<Material> getMaterial() const;
	Ptr<Material> getMaterialInherit() const;
	void setRadius(float radius);
	float getRadius() const;
	void setMaxFadeDistance(float distance);
	float getMaxFadeDistance() const;
	void setMaxVisibleDistance(float distance);
	float getMaxVisibleDistance() const;
	void setMinFadeDistance(float distance);
	float getMinFadeDistance() const;
	void setMinVisibleDistance(float distance);
	float getMinVisibleDistance() const;
	void setOpacity(float opacity);
	float getOpacity() const;
	void setCastBakedGlobalIllumination(bool illumination);
	bool isCastBakedGlobalIllumination() const;
	void setViewportMask(int mask);
	int getViewportMask() const;
	void setIntersectionMask(int mask);
	int getIntersectionMask() const;
	int isMaterialInherited() const;
	int isTerrainHole() const;
	int inside(const Math::vec3 &p);
};
typedef Ptr<Decal> DecalPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API DecalMesh : public Decal
{
public:
	static Node::TYPE type() { return Node::DECAL_MESH; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<DecalMesh> create();
	static Ptr<DecalMesh> create(const char *path);
	Ptr<Mesh> getMeshCurrentRAM();
	Ptr<Mesh> getMeshForceRAM();
	Ptr<Mesh> getMeshAsyncRAM();
	Ptr<Mesh> getMeshProceduralRAM();
	Ptr<MeshRender> getMeshCurrentVRAM();
	Ptr<MeshRender> getMeshForceVRAM();
	Ptr<MeshRender> getMeshAsyncVRAM();
	Ptr<MeshRender> getMeshProceduralVRAM();
	bool loadAsyncRAM();
	bool loadAsyncVRAM();
	bool loadForceRAM();
	bool loadForceVRAM();
	bool asyncCalculateNodes(int surface);
	bool asyncCalculateEdges(int surface);
	void setMeshProceduralMode(bool mode);
	bool isMeshProceduralMode() const;
	bool applyMeshProcedural(const Ptr<Mesh> &mesh);
	bool isMeshNull() const;
	bool isMeshLoadedRAM() const;
	bool isMeshLoadedVRAM() const;
	void setMeshPath(const char *path);
	const char *getMeshPath() const;
	int getStatDrawCalls() const;
	int getStatDrawCountViewport() const;
	int getStatDrawCountReflection() const;
	int getStatDrawCountShadow() const;
	long long getStatFrame() const;
};
typedef Ptr<DecalMesh> DecalMeshPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API DecalOrtho : public Decal
{
public:
	static Node::TYPE type() { return Node::DECAL_ORTHO; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<DecalOrtho> create();
	void setHeight(float height);
	float getHeight() const;
	void setWidth(float width);
	float getWidth() const;
	void setZNear(float znear);
	float getZNear() const;
	Math::mat4 getProjection() const;
};
typedef Ptr<DecalOrtho> DecalOrthoPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API DecalProj : public Decal
{
public:
	static Node::TYPE type() { return Node::DECAL_PROJ; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<DecalProj> create();
	void setAspect(float aspect);
	float getAspect() const;
	void setFov(float fov);
	float getFov() const;
	void setZNear(float znear);
	float getZNear() const;
	Math::mat4 getProjection() const;
};
typedef Ptr<DecalProj> DecalProjPtr;

} // namespace Unigine
