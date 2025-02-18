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

#include "UnigineRender.h"
#include "UnigineGui.h"
#include "UnigineMaterial.h"
#include "UnigineMesh.h"
#include "UnigineMeshRender.h"
#include "UnigineNode.h"
#include "UnigineTextures.h"
#include "UnigineTileset.h"
#include "UnigineCurve2d.h"

namespace Unigine
{

class Body;
class BodyRigid;

class UNIGINE_API ObjectIntersection : public APIInterface
{
public:
	static bool convertible(ObjectIntersection *obj) { return obj != nullptr; }

	enum TYPE
	{
		OBJECT_INTERSECTION = 0,
		OBJECT_INTERSECTION_NORMAL,
		OBJECT_INTERSECTION_TEX_COORD,
		NUM_OBJECT_INTERSECTIONS,
	};
	static Ptr<ObjectIntersection> create();
	ObjectIntersection::TYPE getType() const;
	const char *getTypeName() const;
	void setPoint(const Math::Vec3 &point);
	Math::Vec3 getPoint() const;
	void setIndex(int index);
	int getIndex() const;
	void setInstance(int instance);
	int getInstance() const;
};
typedef Ptr<ObjectIntersection> ObjectIntersectionPtr;


class UNIGINE_API ObjectIntersectionNormal : public ObjectIntersection
{
public:
	static bool convertible(ObjectIntersection *obj) {
		if(!obj)
			return false;
		int type = obj->getType();
		switch(type)
		{
			case ObjectIntersection::OBJECT_INTERSECTION_NORMAL:
			case ObjectIntersection::OBJECT_INTERSECTION_TEX_COORD:
			return true;
		}
		return false;
	}
	static Ptr<ObjectIntersectionNormal> create();
	void setNormal(const Math::vec3 &normal);
	Math::vec3 getNormal() const;
};
typedef Ptr<ObjectIntersectionNormal> ObjectIntersectionNormalPtr;


class UNIGINE_API ObjectIntersectionTexCoord : public ObjectIntersectionNormal
{
public:
	static bool convertible(ObjectIntersection *obj) { return obj && obj->getType() == ObjectIntersection::OBJECT_INTERSECTION_TEX_COORD; }
	static Ptr<ObjectIntersectionTexCoord> create();
	void setTexCoord(const Math::vec4 &coord);
	Math::vec4 getTexCoord() const;
};
typedef Ptr<ObjectIntersectionTexCoord> ObjectIntersectionTexCoordPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Object : public Node
{
public:
	static bool convertible(Node *node) { return node && node->isObject(); }


	enum SURFACE_SHADOW_MODE
	{
		SURFACE_SHADOW_MODE_MIXED = 0,
		SURFACE_SHADOW_MODE_DYNAMIC,
	};

	enum SURFACE_LIGHTING_MODE
	{
		SURFACE_LIGHTING_MODE_STATIC = 0,
		SURFACE_LIGHTING_MODE_DYNAMIC,
		SURFACE_LIGHTING_MODE_ADVANCED,
	};
	using Node::getParent;
	using Node::setParent;
	using Node::isEnabled;
	using Node::setEnabled;
	using Node::getBoundSphere;
	using Node::getBoundBox;
	using Node::getWorldBoundBox;
	using Node::getWorldBoundSphere;
	bool setBody(const Ptr<Body> &body, bool update);
	void setBody(const Ptr<Body> &body);
	Ptr<Body> getBody() const;
	bool isVisibleCamera() const;
	bool isVisibleShadow() const;
	Ptr<BodyRigid> getBodyRigid() const;
	void flushBodyTransform();
	void setEnabled(bool enabled);
	bool isEnabled() const;
	int getNumSurfaces() const;
	const char *getSurfaceName(int surface) const;
	int findSurface(const char *name) const;
	void setEnabled(bool enabled, int surface);
	bool isEnabled(int surface) const;
	void setParent(int parent, int surface);
	int getParent(int surface) const;
	void setCastShadow(bool enabled, int surface);
	bool getCastShadow(int surface) const;
	void setCastWorldShadow(bool enabled, int surface);
	bool getCastWorldShadow(int surface) const;
	void setBakeToEnvProbe(bool enabled, int surface);
	bool getBakeToEnvProbe(int surface) const;
	void setBakeToGI(bool enabled, int surface);
	bool getBakeToGI(int surface) const;
	void setCastEnvProbeShadow(bool enabled, int surface);
	bool getCastEnvProbeShadow(int surface) const;
	void setShadowMode(Object::SURFACE_SHADOW_MODE mode, int surface);
	Object::SURFACE_SHADOW_MODE getShadowMode(int surface) const;
	void setPhysicsIntersection(bool enabled, int surface);
	bool getPhysicsIntersection(int surface) const;
	void setIntersection(bool enabled, int surface);
	bool getIntersection(int surface) const;
	void setCollision(bool enabled, int surface);
	bool getCollision(int surface) const;
	void setShadowMask(int mask, int surface);
	int getShadowMask(int surface) const;
	void setViewportMask(int mask, int surface);
	int getViewportMask(int surface) const;
	void setPhysicsIntersectionMask(int mask, int surface);
	int getPhysicsIntersectionMask(int surface) const;
	void setIntersectionMask(int mask, int surface);
	int getIntersectionMask(int surface) const;
	void setCollisionMask(int mask, int surface);
	int getCollisionMask(int surface) const;
	void setMinParent(int parent, int surface);
	int getMinParent(int surface) const;
	void setMinVisibleDistance(float distance, int surface);
	float getMinVisibleDistance(int surface) const;
	void setMinFadeDistance(float distance, int surface);
	float getMinFadeDistance(int surface) const;
	void setMaxParent(int parent, int surface);
	int getMaxParent(int surface) const;
	void setMaxVisibleDistance(float distance, int surface);
	float getMaxVisibleDistance(int surface) const;
	void setMaxFadeDistance(float distance, int surface);
	float getMaxFadeDistance(int surface) const;
	void setSoundOcclusionMask(int mask, int surface);
	int getSoundOcclusionMask(int surface) const;
	void setSoundOcclusion(float occlusion, int surface);
	float getSoundOcclusion(int surface) const;
	void setPhysicsFriction(float value, int surface);
	float getPhysicsFriction(int surface) const;
	void setPhysicsRestitution(float value, int surface);
	float getPhysicsRestitution(int surface) const;
	void setMaterialFilePath(const char *path, int surface);
	void setMaterialFilePath(const char *path, const char *pattern);
	String getMaterialFilePath(int surface) const;
	void setMaterialGUID(const UGUID &guid, int surface);
	void setMaterialGUID(const UGUID &guid, const char *pattern);
	UGUID getMaterialGUID(int surface) const;
	void setMaterial(const Ptr<Material> &mat, int surface);
	void setMaterial(const Ptr<Material> &mat, const char *pattern);
	Ptr<Material> getMaterial(int surface) const;
	Ptr<Material> getMaterialInherit(int surface);
	bool isMaterialInherited(int surface) const;
	void clearMaterialInherit(int surface);
	void setMaterialState(const char *name, int state, int surface);
	int getMaterialState(const char *name, int surface) const;
	void setMaterialTexture(const char *name, const char *texture, int surface);
	const char *getMaterialTexture(const char *name, int surface) const;
	void setMaterialParameterFloat4(const char *name, const Math::vec4 &parameter, int surface);
	Math::vec4 getMaterialParameterFloat4(const char *name, int surface) const;
	void setMaterialParameterFloat3(const char *name, const Math::vec3 &parameter, int surface);
	Math::vec3 getMaterialParameterFloat3(const char *name, int surface) const;
	void setMaterialParameterFloat2(const char *name, const Math::vec2 &parameter, int surface);
	Math::vec2 getMaterialParameterFloat2(const char *name, int surface) const;
	void setMaterialParameterFloat(const char *name, float parameter, int surface);
	float getMaterialParameterFloat(const char *name, int surface) const;
	void setMaterialParameterInt4(const char *name, const Math::ivec4 &parameter, int surface);
	Math::ivec4 getMaterialParameterInt4(const char *name, int surface) const;
	void setMaterialParameterInt3(const char *name, const Math::ivec3 &parameter, int surface);
	Math::ivec3 getMaterialParameterInt3(const char *name, int surface) const;
	void setMaterialParameterInt2(const char *name, const Math::ivec2 &parameter, int surface);
	Math::ivec2 getMaterialParameterInt2(const char *name, int surface) const;
	void setMaterialParameterInt(const char *name, int parameter, int surface);
	int getMaterialParameterInt(const char *name, int surface) const;
	UGUID getLostMaterialGUID(int surface) const;
	int setSurfaceProperty(const char *name, int surface);
	int setSurfaceProperty(const char *name, const char *pattern);
	int setSurfaceProperty(const UGUID &guid, int surface);
	int setSurfaceProperty(const UGUID &guid, const char *pattern);
	int setSurfaceProperty(const Ptr<Property> &property, int surface);
	int setSurfaceProperty(const Ptr<Property> &property, const char *pattern);
	void clearSurfaceProperty(int surface);
	Ptr<Property> getSurfaceProperty(int surface) const;
	const char *getSurfacePropertyName(int surface) const;
	Ptr<Property> getSurfacePropertyInherit(int surface);
	void clearSurfacePropertyInherit(int surface);
	bool isSurfacePropertyInherited(int surface) const;
	UGUID getLostSurfacePropertyGUID(int surface) const;
	int getSurfaceStatDrawCalls(int surface) const;
	int getSurfaceStatDrawCountViewport(int surface) const;
	int getSurfaceStatDrawCountReflection(int surface) const;
	int getSurfaceStatDrawCountShadow(int surface) const;
	long long getSurfaceStatFrame(int surface) const;
	Math::BoundBox getBoundBox(int surface) const;
	Math::BoundSphere getBoundSphere(int surface) const;
	bool getIntersection(const Math::Vec3 &p0, const Math::Vec3 &p1, Math::Vec3 *ret_point, Math::vec3 *ret_normal, Math::vec4 *ret_texcoord, int *ret_index, int *ret_instance, int surface) const;
	bool getIntersection(const Math::Vec3 &p0, const Math::Vec3 &p1, int mask, Math::Vec3 *ret_point, Math::vec3 *ret_normal, Math::vec4 *ret_texcoord, int *ret_index, int *ret_instance, int *ret_surface) const;
	bool getIntersection(const Math::Vec3 &p0, const Math::Vec3 &p1, int mask, const Ptr<ObjectIntersection> &v, int *ret_surface) const;
	bool getIntersection(const Math::Vec3 &p0, const Math::Vec3 &p1, int mask, const Ptr<ObjectIntersectionNormal> &v, int *ret_surface) const;
	bool getIntersection(const Math::Vec3 &p0, const Math::Vec3 &p1, int mask, const Ptr<ObjectIntersectionTexCoord> &v, int *ret_surface) const;
	bool getIntersection(const Math::Vec3 &p0, const Math::Vec3 &p1, const Ptr<ObjectIntersection> &v, int surface) const;
	bool getIntersection(const Math::Vec3 &p0, const Math::Vec3 &p1, const Ptr<ObjectIntersectionNormal> &v, int surface) const;
	bool getIntersection(const Math::Vec3 &p0, const Math::Vec3 &p1, const Ptr<ObjectIntersectionTexCoord> &v, int surface) const;
	int getNumTriangles(int surface) const;
	Math::WorldBoundBox getWorldBoundBox(int surface) const;
	Math::WorldBoundSphere getWorldBoundSphere(int surface) const;
	void render(Render::PASS pass, int surface);
	void setLightingMode(Object::SURFACE_LIGHTING_MODE mode, int surface);
	Object::SURFACE_LIGHTING_MODE getLightingMode(int surface) const;
};
typedef Ptr<Object> ObjectPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectDummy : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_DUMMY; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectDummy> create();
};
typedef Ptr<ObjectDummy> ObjectDummyPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectDynamic : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_DYNAMIC; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }


	enum
	{
		IMMUTABLE_VERTEX = 1 << 0,
		IMMUTABLE_INDICES = 1 << 1,
		DYNAMIC_VERTEX = 1 << 2,
		DYNAMIC_INDICES = 1 << 3,
		IMMUTABLE_ALL = (IMMUTABLE_VERTEX | IMMUTABLE_INDICES),
		DYNAMIC_ALL = (DYNAMIC_VERTEX | DYNAMIC_INDICES),
	};

	enum MODE
	{
		MODE_POINTS = 0,
		MODE_LINES,
		MODE_TRIANGLES,
		MODE_TRIANGLE_PATCHES,
		MODE_QUAD_PATCHES,
	};

	enum
	{
		TYPE_HALF = 0,
		TYPE_FLOAT,
		TYPE_UCHAR,
		TYPE_USHORT,
	};
	static Ptr<ObjectDynamic> create(int flags = 0);
	struct Attribute
	{
		int offset;
		int type;
		int size;
	};
	void setMaterialNodeType(Node::TYPE type);
	Node::TYPE getMaterialNodeType() const;
	void setInstancing(bool instancing);
	bool getInstancing() const;
	void setParameterBool(const char *name, bool value);
	void setParameterInt(const char *name, const int *value, int value_size);
	void setParameterFloat(const char *name, const float *value, int value_size);
	void setParameterFloatArray(const char *name, const float *value, int value_size, int num);
	void clearSurfaces();
	void addSurface(const char *name);
	void setSurfaceName(const char *name, int surface);
	void updateSurfaceBegin(int surface);
	void setSurfaceBegin(int begin, int surface);
	int getSurfaceBegin(int surface) const;
	void updateSurfaceEnd(int surface);
	void setSurfaceEnd(int end, int surface);
	int getSurfaceEnd(int surface) const;
	void setSurfaceMode(ObjectDynamic::MODE mode, int surface);
	ObjectDynamic::MODE getSurfaceMode(int surface) const;
	void setVertexFormat(const ObjectDynamic::Attribute *attributes, int attributes_size);
	int getVertexSize() const;
	int getNumAttributes() const;
	const ObjectDynamic::Attribute * getAttributes() const;
	void clearVertex();
	void allocateVertex(int num);
	void removeVertex(int num, int size, int indices);
	void setNumVertex(int vertex);
	int getNumVertex() const;
	void addVertex(const void *vertex);
	void setVertex(int num, const void *vertex);
	void addVertexArray(const void *vertex, int num_vertex);
	void setVertexArray(const void *vertex, int num_vertex);
	const void *getVertexArray() const;
	const void *getVertex(int num) const;
	void addVertexHalf(int attribute, const float *value, int value_size);
	void setVertexHalf(int attribute, const float *value, int value_size);
	void setVertexHalf(int vertex, int attribute, const float *value, int value_size);
	void addVertexFloat(int attribute, const float *value, int value_size);
	void setVertexFloat(int attribute, const float *value, int value_size);
	void setVertexFloat(int vertex, int attribute, const float *value, int value_size);
	void addVertexUChar(int attribute, const unsigned char *value, int value_size);
	void setVertexUChar(int attribute, const unsigned char *value, int value_size);
	void setVertexUChar(int vertex, int attribute, const unsigned char *value, int value_size);
	void addVertexUShort(int attribute, const unsigned short *value, int value_size);
	void setVertexUShort(int attribute, const unsigned short *value, int value_size);
	void setVertexUShort(int vertex, int attribute, const unsigned short *value, int value_size);
	void clearIndices();
	void allocateIndices(int num);
	void removeIndices(int num, int size);
	void setNumIndices(int indices);
	int getNumIndices() const;
	void addIndex(int index);
	void setIndex(int num, int index);
	void addIndicesArray(const int *indices, int indices_size);
	void setIndicesArray(const int *indices, int indices_size);
	const int *getIndicesArray() const;
	int getIndex(int num) const;
	void addTriangles(int num_triangles);
	void addTriangleFan(int num_vertex);
	void addTriangleStrip(int num_vertex);
	void addTriangleQuads(int num_quads);
	void addLineStrip(int num_vertex);
	void addPoints(int num_points);
	void setBoundBox(const Math::BoundBox &bb, int surface);
	void setBoundBox(const Math::BoundBox &bb);
	void flushVertex();
	void flushIndices();
};
typedef Ptr<ObjectDynamic> ObjectDynamicPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectMeshStatic : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_MESH_STATIC; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }


	enum LIGHTMAP_MODE
	{
		LIGHTMAP_MODE_UNIQUE = 0,
		LIGHTMAP_MODE_CUSTOM,
		LIGHTMAP_MODE_SURFACE,
	};

	enum LIGHTMAP_QUALITY
	{
		LIGHTMAP_QUALITY_GLOBAL = 0,
		LIGHTMAP_QUALITY_DRAFT,
		LIGHTMAP_QUALITY_LOW,
		LIGHTMAP_QUALITY_MEDIUM,
		LIGHTMAP_QUALITY_HIGH,
		LIGHTMAP_QUALITY_ULTRA,
	};

	enum SURFACE_CUSTOM_TEXTURE_MODE
	{
		SURFACE_CUSTOM_TEXTURE_MODE_UNIQUE = 0,
		SURFACE_CUSTOM_TEXTURE_MODE_SURFACE,
	};
	static Ptr<ObjectMeshStatic> create();
	static Ptr<ObjectMeshStatic> create(const char *path);
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
	void setLightmapEnabled(bool enabled, int surface);
	bool isLightmapEnabled(int surface) const;
	void setLightmapCompression(bool enabled, int surface);
	bool isLightmapCompression(int surface) const;
	void setLightmapQuality(ObjectMeshStatic::LIGHTMAP_QUALITY quality, int surface);
	ObjectMeshStatic::LIGHTMAP_QUALITY getLightmapQuality(int surface) const;
	void setLightmapMode(ObjectMeshStatic::LIGHTMAP_MODE mode, int surface);
	ObjectMeshStatic::LIGHTMAP_MODE getLightmapMode(int surface) const;
	void setLightmapSourceSurface(int source_surface, int surface);
	int getLightmapSourceSurface(int surface) const;
	void setLightmapTextureFilePath(const char *path, int surface);
	String getLightmapTextureFilePath(int surface) const;
	void setSurfaceCustomTextureEnabled(bool enabled, int surface);
	bool isSurfaceCustomTextureEnabled(int surface) const;
	void setSurfaceCustomTextureMode(ObjectMeshStatic::SURFACE_CUSTOM_TEXTURE_MODE mode, int surface);
	ObjectMeshStatic::SURFACE_CUSTOM_TEXTURE_MODE getSurfaceCustomTextureMode(int surface) const;
	void setSurfaceCustomTextureSourceSurface(int source_surface, int surface);
	int getSurfaceCustomTextureSourceSurface(int surface) const;
	void setSurfaceCustomTexturePath(const char *path, int surface);
	const char *getSurfaceCustomTexturePath(int surface) const;
	void setSurfaceCustomTexture(const Ptr<Texture> &texture, int surface);
	Ptr<Texture> getSurfaceCustomTexture(int surface) const;
};
typedef Ptr<ObjectMeshStatic> ObjectMeshStaticPtr;

class ObjectMeshSkinned;
template class UNIGINE_API EventInterfaceConnection<EventInterfaceInvoker<float, const Ptr<ObjectMeshSkinned> &>>;
template class UNIGINE_API EventInterfaceConnection<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>>;

class UNIGINE_API BonesRetargeting : public APIInterface
{
public:

	enum MODE
	{
		MODE_ANIMATION = 0,
		MODE_BIND,
		MODE_PROPORTION,
	};
	static Ptr<BonesRetargeting> create();
	static Ptr<BonesRetargeting> create(const char *src_mesh_path, const char *dst_mesh_path);
	bool loadBones(const char *src_mesh_path, const char *dst_mesh_path);
	bool loadBonesFromMeshes(const Ptr<Mesh> &src_mesh, const Ptr<Mesh> &dst_mesh);
	bool loadBonesFromObjects(const Ptr<ObjectMeshSkinned> &src_obj, const Ptr<ObjectMeshSkinned> &dst_obj);
	int getNumSrcBones() const;
	const char *getSrcBoneName(int index) const;
	int getNumDstBones() const;
	const char *getDstBoneName(int index) const;
	bool setNameMapping(const char *src_name, const char *dst_name);
	void findEqualNameMapping();
	void setBoneMode(const char *src_name, BonesRetargeting::MODE mode);
	BonesRetargeting::MODE getBoneMode(const char *src_name) const;
	float getBoneProportion(const char *src_name) const;
	void setBoneCustomProportion(const char *src_name, float proportion);
	float getBoneCustomProportion(const char *src_name) const;
	void removeBoneCustomProportion(const char *src_name);
	bool isBoneCustomProportion(const char *src_name) const;
	const char *getDstBoneBySrcBone(const char *src_name) const;
	const char *getSrcBoneByDstBone(const char *dst_name) const;
	UGUID getSrcMeshFileGUID() const;
	UGUID getDstMeshFileGUID() const;
	bool save(const char *path) const;
	bool load(const char *path);
};
typedef Ptr<BonesRetargeting> BonesRetargetingPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectMeshSkinned : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_MESH_SKINNED; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }


	enum BIND_MODE
	{
		BIND_MODE_OVERRIDE = 0,
		BIND_MODE_ADDITIVE,
	};

	enum NODE_SPACE
	{
		NODE_SPACE_WORLD = 0,
		NODE_SPACE_LOCAL,
	};

	enum BONE_SPACE
	{
		BONE_SPACE_WORLD = 0,
		BONE_SPACE_OBJECT,
		BONE_SPACE_LOCAL,
	};

	enum ANIM_FRAME_USES
	{
		ANIM_FRAME_USES_NONE = 0,
		ANIM_FRAME_USES_POSITION = 1 << 0,
		ANIM_FRAME_USES_ROTATION = 1 << 1,
		ANIM_FRAME_USES_SCALE = 1 << 2,
		ANIM_FRAME_USES_ALL = ANIM_FRAME_USES_POSITION | ANIM_FRAME_USES_ROTATION | ANIM_FRAME_USES_SCALE,
		ANIM_FRAME_USES_POSITION_AND_ROTATION = ANIM_FRAME_USES_POSITION | ANIM_FRAME_USES_ROTATION,
		ANIM_FRAME_USES_POSITION_AND_SCALE = ANIM_FRAME_USES_POSITION | ANIM_FRAME_USES_SCALE,
		ANIM_FRAME_USES_ROTATION_AND_SCALE = ANIM_FRAME_USES_ROTATION | ANIM_FRAME_USES_SCALE,
	};

	enum INTERPOLATION_ACCURACY
	{
		INTERPOLATION_ACCURACY_LOW = 0,
		INTERPOLATION_ACCURACY_MEDIUM,
		INTERPOLATION_ACCURACY_HIGH,
	};

	enum CHAIN_CONSTRAINT
	{
		CHAIN_CONSTRAINT_NONE = 0,
		CHAIN_CONSTRAINT_POLE_VECTOR,
		CHAIN_CONSTRAINT_BONE_ROTATIONS,
	};
	static Ptr<ObjectMeshSkinned> create();
	static Ptr<ObjectMeshSkinned> create(const char *path);
	void setMeshPath(const char *path);
	const char *getMeshPath() const;
	bool isLoaded() const;
	void setMeshProceduralMode(bool mode);
	bool isMeshProceduralMode() const;
	bool applyMeshProcedural(const Ptr<Mesh> &mesh);
	void setAnimPath(const char *path);
	const char *getAnimPath() const;
	void setFPSVisibleCamera(int camera);
	int getFPSVisibleCamera() const;
	void setFPSVisibleShadow(int shadow);
	int getFPSVisibleShadow() const;
	void setFPSInvisible(int invisible);
	int getFPSInvisible() const;
	void setUpdateDistanceLimit(float limit);
	float getUpdateDistanceLimit() const;
	void setQuaternion(bool quaternion);
	bool isQuaternion() const;
	void setControlled(bool controlled);
	bool isControlled() const;
	void setLoop(bool loop);
	bool isLoop() const;
	void setTime(float time);
	float getTime() const;
	void setSpeed(float speed);
	float getSpeed() const;
	void setInterpolationAccuracy(ObjectMeshSkinned::INTERPOLATION_ACCURACY accuracy);
	ObjectMeshSkinned::INTERPOLATION_ACCURACY getInterpolationAccuracy() const;
	void play();
	void stop();
	bool isPlaying() const;
	bool isStopped() const;
	bool getMesh(Ptr<Mesh> &mesh) const;
	bool getMeshSurface(const Ptr<Mesh> &mesh, int surface, int target = -1) const;
	int getNumVertex(int surface) const;
	Math::vec3 getVertex(int num, int surface, int target = 0) const;
	Math::vec3 getSkinnedVertex(int num, int surface) const;
	int getNumTangents(int surface) const;
	Math::quat getTangent(int num, int surface, int target = 0) const;
	Math::vec3 getNormal(int num, int surface, int target = 0) const;
	Math::quat getSkinnedTangent(int num, int index, int surface) const;
	Math::vec3 getSkinnedNormal(int num, int index, int surface) const;
	int getNumTexCoords0(int surface) const;
	Math::vec2 getTexCoord0(int num, int surface) const;
	int getNumTexCoords1(int surface) const;
	Math::vec2 getTexCoord1(int num, int surface) const;
	int getNumColors(int surface) const;
	Math::vec4 getColor(int num, int surface) const;
	int getNumCIndices(int surface) const;
	int getCIndex(int num, int surface) const;
	int getNumTIndices(int surface) const;
	int getTIndex(int num, int surface) const;
	int getNumSurfaceTargets(int surface) const;
	const char *getSurfaceTargetName(int surface, int target) const;
	int findSurfaceTarget(int surface, const char *name) const;
	void setSurfaceTargetEnabled(int surface, int target, bool enabled);
	int isSurfaceTargetEnabled(int surface, int target) const;
	void setSurfaceTargetWeight(int surface, int target, float weight);
	float getSurfaceTargetWeight(int surface, int target) const;
	int addLayer();
	void removeLayer(int layer);
	void setNumLayers(int layers);
	int getNumLayers() const;
	void setLayer(int layer, bool enabled, float weight);
	void setLayerEnabled(int layer, bool enabled);
	bool isLayerEnabled(int layer) const;
	void setLayerWeight(int layer, float weight);
	float getLayerWeight(int layer) const;
	void clearLayer(int layer);
	void importLayer(int layer);
	void copyLayer(int dest, int src);
	void inverseLayer(int dest, int src);
	void lerpLayer(int dest, int layer0, int layer1, float weight);
	void mulLayer(int dest, int layer0, int layer1, float weight = 1.0f);
	void setLayerBoneTransformEnabled(int layer, int bone, bool enabled);
	void setLayerBoneTransform(int layer, int bone, const Math::mat4 &transform);
	Math::mat4 getLayerBoneTransform(int layer, int bone) const;
	bool isLayerBoneTransform(int layer, int bone) const;
	void setLayerBonePosition(int layer, int bone, const Math::vec3 &position);
	Math::vec3 getLayerBonePosition(int layer, int bone) const;
	void setLayerBoneRotation(int layer, int bone, const Math::quat &rotation);
	Math::quat getLayerBoneRotation(int layer, int bone) const;
	void setLayerBoneScale(int layer, int bone, const Math::vec3 &scale);
	Math::vec3 getLayerBoneScale(int layer, int bone) const;
	void setLayerFrameUsesEnabled(int layer, bool enabled);
	bool isLayerFrameUsesEnabled(int layer) const;
	void setLayerBoneFrameUses(int layer, int bone, ObjectMeshSkinned::ANIM_FRAME_USES uses);
	ObjectMeshSkinned::ANIM_FRAME_USES getLayerBoneFrameUses(int layer, int bone) const;
	int getLayerNumFrames(int layer) const;
	float setLayerFrame(int layer, float frame, int from = -1, int to = -1);
	float getLayerFrame(int layer) const;
	int getLayerFrameFrom(int layer) const;
	int getLayerFrameTo(int layer) const;
	static void setRetargeting(const Ptr<BonesRetargeting> &bones_retargeting, const char *anim_path, const char *mesh_path);
	static void removeRetargeting(const char *anim_path, const char *mesh_path);
	static Ptr<BonesRetargeting> getRetargeting(const char *anim_path, const char *mesh_path);
	static bool isRetargeting(const char *anim_path, const char *mesh_path);
	long long getAnimationResourceID(const char *path) const;
	void setLayerAnimationFilePath(int layer, const char *path);
	String getLayerAnimationFilePath(int layer) const;
	void setLayerAnimationResourceID(int layer, long long resource_id) const;
	long long getLayerAnimationResourceID(int layer) const;
	int getNumBones() const;
	const char *getBoneName(int bone) const;
	int findBone(const char *name) const;
	int getBoneParent(int bone) const;
	int getNumBoneChildren(int bone) const;
	int getBoneChild(int bone, int child) const;
	Math::mat4 getBoneBindLocalTransform(int bone) const;
	Math::mat4 getBoneBindLocalITransform(int bone) const;
	Math::mat4 getBoneBindObjectTransform(int bone) const;
	Math::mat4 getBoneBindObjectITransform(int bone) const;
	void setBoneTransform(int bone, const Math::mat4 &transform);
	void setBoneTransformWithChildren(int bone, const Math::mat4 &transform);
	void setBoneTransforms(const int *bones, const Math::mat4 *transforms, int num_bones);
	Math::mat4 getBoneTransform(int bone) const;
	Math::mat4 getBoneSkiningTransform(int bone) const;
	void setBoneWorldTransform(int bone, const Math::Mat4 &transform);
	void setBoneWorldTransformWithChildren(int bone, const Math::Mat4 &transform);
	Math::Mat4 getBoneWorldTransform(int bone) const;
	Math::mat4 getBoneNotAdditionalBindLocalTransform(int bone) const;
	Math::mat4 getBoneNotAdditionalBindObjectTransform(int bone) const;
	Math::Mat4 getBoneNotAdditionalBindWorldTransform(int bone) const;
	void setBindNode(int bone, const Ptr<Node> &node);
	Ptr<Node> getBindNode(int bone) const;
	void removeBindNodeByBone(int bone);
	void removeBindNodeByNode(const Ptr<Node> &node);
	void removeAllBindNode();
	void setBindNodeSpace(int bone, ObjectMeshSkinned::NODE_SPACE space);
	ObjectMeshSkinned::NODE_SPACE getBindNodeSpace(int bone) const;
	void setBindBoneSpace(int bone, ObjectMeshSkinned::BONE_SPACE space);
	ObjectMeshSkinned::BONE_SPACE getBindBoneSpace(int bone) const;
	void setBindMode(int bone, ObjectMeshSkinned::BIND_MODE mode);
	ObjectMeshSkinned::BIND_MODE getBindMode(int bone) const;
	void setBindNodeOffset(int bone, const Math::Mat4 &offset);
	Math::Mat4 getBindNodeOffset(int bone) const;
	void addVisualizeBone(int bone);
	void removeVisualizeBone(int bone);
	void clearVisualizeBones();
	void setVisualizeAllBones(bool bones);
	bool isVisualizeAllBones() const;
	void addVisualizeLookAtChain(int chain_id);
	void removeVisualizeLookAtChain(int chain_id);
	void clearVisualizeLookAtChain();
	void addVisualizeIKChain(int chain_id);
	void removeVisualizeIKChain(int chain_id);
	void clearVisualizeIKChain();
	void addVisualizeConstraint(int constraint_index);
	void removeVisualizeConstraint(int constraint_index);
	void clearVisualizeConstraint();
	int addLookAtChain();
	void removeLookAtChain(int chain_id);
	int getNumLookAtChains() const;
	int getLookAtChainID(int num) const;
	void setLookAtChainEnabled(bool enabled, int chain_id);
	bool isLookAtChainEnabled(int chain_id) const;
	void setLookAtChainConstraint(ObjectMeshSkinned::CHAIN_CONSTRAINT constraint, int chain_id);
	ObjectMeshSkinned::CHAIN_CONSTRAINT getLookAtChainConstraint(int chain_id) const;
	void setLookAtChainWeight(float weight, int chain_id);
	float getLookAtChainWeight(int chain_id) const;
	int addLookAtChainBone(int bone, int chain_id);
	int addLookAtChainBone(const char *bone_name, int chain_id);
	int getLookAtChainNumBones(int chain_id) const;
	void removeLookAtChainBone(int bone_num, int chain_id);
	int getLookAtChainBone(int bone_num, int chain_id) const;
	void setLookAtChainBoneWeight(float weight, int bone_num, int chain_id);
	float getLookAtChainBoneWeight(int bone_num, int chain_id) const;
	void setLookAtChainBoneUp(const Math::Vec3 &up, int bone_num, int chain_id);
	Math::Vec3 getLookAtChainBoneUp(int bone_num, int chain_id) const;
	void setLookAtChainBoneAxis(const Math::Vec3 &axis, int bone_num, int chain_id);
	Math::Vec3 getLookAtChainBoneAxis(int bone_num, int chain_id) const;
	void setLookAtChainTargetPosition(const Math::Vec3 &position, int chain_id);
	Math::Vec3 getLookAtChainTargetPosition(int chain_id) const;
	void setLookAtChainTargetWorldPosition(const Math::Vec3 &position, int chain_id);
	Math::Vec3 getLookAtChainTargetWorldPosition(int chain_id) const;
	void setLookAtChainPolePosition(const Math::Vec3 &position, int chain_id);
	Math::Vec3 getLookAtChainPolePosition(int chain_id) const;
	void setLookAtChainPoleWorldPosition(const Math::Vec3 &position, int chain_id);
	Math::Vec3 getLookAtChainPoleWorldPosition(int chain_id) const;
	int addIKChain();
	void removeIKChain(int chain_id);
	int getNumIKChains() const;
	int getIKChainID(int num) const;
	void setIKChainEnabled(bool enabled, int chain_id);
	bool isIKChainEnabled(int chain_id) const;
	void setIKChainConstraint(ObjectMeshSkinned::CHAIN_CONSTRAINT constraint, int chain_id);
	ObjectMeshSkinned::CHAIN_CONSTRAINT getIKChainConstraint(int chain_id) const;
	void setIKChainWeight(float weight, int chain_id);
	float getIKChainWeight(int chain_id) const;
	int addIKChainBone(int bone, int chain_id);
	int addIKChainBone(const char *bone_name, int chain_id);
	int getIKChainNumBones(int chain_id) const;
	void removeIKChainBone(int bone_num, int chain_id);
	int getIKChainBone(int bone_num, int chain_id) const;
	void setIKChainTargetPosition(const Math::Vec3 &position, int chain_id);
	Math::Vec3 getIKChainTargetPosition(int chain_id) const;
	void setIKChainTargetWorldPosition(const Math::Vec3 &position, int chain_id);
	Math::Vec3 getIKChainTargetWorldPosition(int chain_id) const;
	void setIKChainPolePosition(const Math::Vec3 &position, int chain_id);
	Math::Vec3 getIKChainPolePosition(int chain_id) const;
	void setIKChainPoleWorldPosition(const Math::Vec3 &position, int chain_id);
	Math::Vec3 getIKChainPoleWorldPosition(int chain_id) const;
	void setIKChainUseEffectorRotation(bool use, int chain_id);
	bool isIKChainUseEffectorRotation(int chain_id) const;
	void setIKChainEffectorRotation(const Math::quat &rotation, int chain_id);
	Math::quat getIKChainEffectorRotation(int chain_id) const;
	void setIKChainEffectorWorldRotation(const Math::quat &rotation, int chain_id);
	Math::quat getIKChainEffectorWorldRotation(int chain_id) const;
	void setIKChainNumIterations(int num, int chain_id);
	int getIKChainNumIterations(int chain_id) const;
	void setIKChainTolerance(float tolerance, int chain_id);
	float getIKChainTolerance(int chain_id) const;
	int addBoneConstraint(int bone);
	int addBoneConstraint(const char *bone_name);
	void removeBoneConstraint(int constraint_num);
	int getNumBoneConstraints() const;
	int findBoneConstraint(int bone) const;
	int findBoneConstraint(const char *bone_name) const;
	void setBoneConstraintEnabled(bool enabled, int constraint_num);
	bool isBoneConstraintEnabled(int constraint_num) const;
	int getBoneConstraintBoneIndex(int constraint_num) const;
	void setBoneConstraintYawAxis(const Math::vec3 &axis, int constraint_num);
	Math::vec3 getBoneConstraintYawAxis(int constraint_num) const;
	void setBoneConstraintPitchAxis(const Math::vec3 &axis, int constraint_num);
	Math::vec3 getBoneConstraintPitchAxis(int constraint_num) const;
	void setBoneConstraintRollAxis(const Math::vec3 &axis, int constraint_num);
	Math::vec3 getBoneConstraintRollAxis(int constraint_num) const;
	void setBoneConstraintYawAngles(float min_angle, float max_angle, int constraint_num);
	float getBoneConstraintYawMinAngle(int constraint_num) const;
	float getBoneConstraintYawMaxAngle(int constraint_num) const;
	void setBoneConstraintPitchAngles(float min_angle, float max_angle, int constraint_num);
	float getBoneConstraintPitchMinAngle(int constraint_num) const;
	float getBoneConstraintPitchMaxAngle(int constraint_num) const;
	void setBoneConstraintRollAngles(float min_angle, float max_angle, int constraint_num);
	float getBoneConstraintRollMinAngle(int constraint_num) const;
	float getBoneConstraintRollMaxAngle(int constraint_num) const;
	void updateSkinned();
	void copyBoneTransforms(const Ptr<ObjectMeshSkinned> &src);
	bool isNeedUpdate() const;
	Event<float, const Ptr<ObjectMeshSkinned> &> &getEventUpdate();
	Event<const Ptr<ObjectMeshSkinned> &> &getEventBeginLookAtSolvers();
	Event<const Ptr<ObjectMeshSkinned> &> &getEventEndLookAtSolvers();
	Event<const Ptr<ObjectMeshSkinned> &> &getEventBeginIKSolvers();
	Event<const Ptr<ObjectMeshSkinned> &> &getEventEndIKSolvers();
	Event<const Ptr<ObjectMeshSkinned> &> &getEventBeginBoneConstraints();
	Event<const Ptr<ObjectMeshSkinned> &> &getEventEndBoneConstraints();

private:

	EventHolder<EventInterfaceInvoker<float, const Ptr<ObjectMeshSkinned> &>> event_update;
	EventInterfaceConnection<EventInterfaceInvoker<float, const Ptr<ObjectMeshSkinned> &>> event_update_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_begin_look_at_solvers;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_begin_look_at_solvers_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_end_look_at_solvers;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_end_look_at_solvers_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_begin_iksolvers;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_begin_iksolvers_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_end_iksolvers;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_end_iksolvers_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_begin_bone_constraints;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_begin_bone_constraints_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_end_bone_constraints;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<ObjectMeshSkinned> &>> event_end_bone_constraints_connection;
};
typedef Ptr<ObjectMeshSkinned> ObjectMeshSkinnedPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectMeshDynamic : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_MESH_DYNAMIC; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectMeshDynamic> create(const Ptr<Mesh> &mesh, int flags = 0);
	static Ptr<ObjectMeshDynamic> create(const char *path, int flags = 0);
	static Ptr<ObjectMeshDynamic> create(int flags = 0);
	struct Vertex
	{
		Math::vec3 xyz;
		Math::vec4 texcoord;
		Math::vec4 tangent;
		Math::vec4 color;
	};
	bool loadMesh(const char *path);
	bool saveMesh(const char *path);
	int setMesh(const Ptr<Mesh> &mesh);
	int getMesh(Ptr<Mesh> &mesh) const;
	void setMeshName(const char *name);
	const char *getMeshName() const;
	bool isUsageShared() const;
	bool isUniqueMesh() const;
	void putUniqueMesh();
	void setFPSVisibleCamera(int camera);
	int getFPSVisibleCamera() const;
	void setFPSVisibleShadow(int shadow);
	int getFPSVisibleShadow() const;
	void setFPSInvisible(int invisible);
	int getFPSInvisible() const;
	void setUpdateDistanceLimit(float limit);
	float getUpdateDistanceLimit() const;
	Ptr<ResourceExternalMemory> getExternalMemoryVertexBuffer() const;
	Ptr<ResourceExternalMemory> getExternalMemoryIndexBuffer() const;
	void clearSurfaces();
	void addSurface(const char *name);
	void setSurfaceName(const char *name, int surface);
	void removeSurface(int surface);
	void removeSurfaces(const char *name);
	void updateSurfaceBegin(int surface);
	void setSurfaceBegin(int begin, int surface);
	int getSurfaceBegin(int surface) const;
	void updateSurfaceEnd(int surface);
	void setSurfaceEnd(int end, int surface);
	int getSurfaceEnd(int surface) const;
	void clearVertex();
	void allocateVertex(int num);
	void removeVertex(int num, int size, int indices);
	void setNumVertex(int vertex);
	int getNumVertex() const;
	void addVertex(const Math::vec3 &xyz);
	void setVertex(int num, const Math::vec3 &xyz);
	void addVertexArray(const ObjectMeshDynamic::Vertex *vertex, int vertex_size);
	void setVertexArray(const ObjectMeshDynamic::Vertex *vertex, int vertex_size);
	const ObjectMeshDynamic::Vertex * getVertexArray() const;
	Math::vec3 getVertex(int num) const;
	void addTexCoord(const Math::vec4 &texcoord);
	void setTexCoord(int num, const Math::vec4 &texcoord);
	Math::vec4 getTexCoord(int num) const;
	void addTangent(const Math::quat &tangent);
	void setTangent(int num, const Math::quat &tangent);
	Math::quat getTangent(int num) const;
	Math::vec3 getNormal(int num) const;
	void addColor(const Math::vec4 &color);
	void setColor(int num, const Math::vec4 &color);
	Math::vec4 getColor(int num) const;
	void clearIndices();
	void allocateIndices(int num);
	void removeIndices(int num, int size);
	void setNumIndices(int indices);
	int getNumIndices() const;
	void addIndex(int index);
	void setIndex(int num, int index);
	void addIndicesArray(const int *indices, int indices_size);
	void setIndicesArray(const int *indices, int indices_size);
	const int *getIndicesArray() const;
	int getIndex(int num) const;
	void addTriangles(int num_triangles);
	void addTriangleFan(int num_vertex);
	void addTriangleStrip(int num_vertex);
	void addTriangleQuads(int num_quads);
	void setBoundBox(const Math::BoundBox &bb, int surface);
	void setBoundBox(const Math::BoundBox &bb);
	bool updateBounds();
	bool updateIndices();
	bool updateTangents();
	void flushVertex();
	void flushIndices();
	bool isFlushed() const;

	enum
	{
		// immutable flags
		USAGE_IMMUTABLE_VERTEX = 1 << 0,
		USAGE_IMMUTABLE_INDICES = 1 << 1,
		USAGE_IMMUTABLE_ALL = (USAGE_IMMUTABLE_VERTEX | USAGE_IMMUTABLE_INDICES),
		// dynamic flags
		USAGE_DYNAMIC_VERTEX = 1 << 2,
		USAGE_DYNAMIC_INDICES = 1 << 3,
		USAGE_DYNAMIC_ALL = (USAGE_DYNAMIC_VERTEX | USAGE_DYNAMIC_INDICES),
		// misc
		USAGE_MISC_SHARED = 1 << 6,
	};
};
typedef Ptr<ObjectMeshDynamic> ObjectMeshDynamicPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectMeshCluster : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_MESH_CLUSTER; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectMeshCluster> create();
	static Ptr<ObjectMeshCluster> create(const char *path);
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
	void setVisibleDistance(float distance);
	float getVisibleDistance() const;
	void setFadeDistance(float distance);
	float getFadeDistance() const;
	int getNumMeshes() const;
	void removeMeshTransform(int num);
	void removeMeshTransformFast(int num);
	int addMeshTransform();
	Math::mat4 getMeshTransform(int num) const;
	void setMeshTransform(int num, const Math::mat4 &transform);
	void createMeshes(const Vector<Math::Mat4> &world_transforms);
	void appendMeshes(const Vector<Math::Mat4> &world_transforms);
	void clearMeshes();
	bool getClusterTransforms(const Math::WorldBoundBox &bounds, Vector<Math::mat4> &transforms);
	bool getClusterWorldTransforms(const Math::WorldBoundBox &bounds, Vector<Math::Mat4> &transforms);
	bool getClusterWorldTransformsFromSphere(const Math::WorldBoundSphere &bounds, Vector<Math::Mat4> &transforms);
	bool detachClusterTransforms(const Math::WorldBoundBox &bb, Vector<Math::mat4> &transforms);
	bool detachClusterWorldTransforms(const Math::WorldBoundBox &bb, Vector<Math::Mat4> &transforms);
	bool detachClusterWorldTransformsFromSphere(const Math::WorldBoundSphere &bb, Vector<Math::Mat4> &transforms);
	bool removeClusterTransforms(const Math::WorldBoundBox &bb);
	bool removeClusterTransformsFromSphere(const Math::WorldBoundSphere &bb);
	bool getInstancesFromSphere(const Math::WorldBoundSphere &bb, Vector<int> &instances);
};
typedef Ptr<ObjectMeshCluster> ObjectMeshClusterPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectMeshClutter : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_MESH_CLUTTER; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	using Object::getCollision;
	using Object::setCollision;
	using Object::getIntersection;
	using Object::setIntersection;
	using Object::getIntersectionMask;
	using Object::setIntersectionMask;
	static Ptr<ObjectMeshClutter> create();
	static Ptr<ObjectMeshClutter> create(const char *path);
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
	void setCollision(bool collision);
	bool getCollision() const;
	void setOrientation(bool orientation);
	bool getOrientation() const;
	void setIntersection(bool intersection);
	bool getIntersection() const;
	void setIntersectionMask(int mask);
	int getIntersectionMask() const;
	void setVisibleDistance(float distance);
	float getVisibleDistance() const;
	void setFadeDistance(float distance);
	float getFadeDistance() const;
	int getSpawnCount() const;
	void setSeed(int seed);
	int getSeed() const;
	void setSizeX(float sizex);
	float getSizeX() const;
	void setSizeY(float sizey);
	float getSizeY() const;
	void setStep(float step);
	float getStep() const;
	void setDensity(float density);
	float getDensity() const;
	void setThreshold(float threshold);
	float getThreshold() const;
	void setAngle(float angle);
	float getAngle() const;
	void setMinScale(float mean, float spread);
	float getMinScaleMean() const;
	float getMinScaleSpread() const;
	void setMaxScale(float mean, float spread);
	float getMaxScaleMean() const;
	float getMaxScaleSpread() const;
	void setOffset(float mean, float spread);
	float getOffsetMean() const;
	float getOffsetSpread() const;
	void setMeshesRotation(const Math::vec3 &mean, const Math::vec3 &spread);
	Math::vec3 getMeshesRotationMean() const;
	Math::vec3 getMeshesRotationSpread() const;
	int setMaskImage(const Ptr<Image> &image, bool invalidate = true);
	int getMaskImage(const Ptr<Image> &image) const;
	void setMaskImageName(const char *image_name, bool invalidate);
	void setMaskImageName(const char *name);
	const char *getMaskImageName() const;
	void setMaskFlipX(int value);
	int getMaskFlipX() const;
	void setMaskFlipY(int value);
	int getMaskFlipY() const;
	void setMaskMinValue(int value);
	int getMaskMinValue() const;
	void setMaskMaxValue(int value);
	int getMaskMaxValue() const;
	int setMaskMesh(const Ptr<Mesh> &mesh, bool invalidate = true);
	int getMaskMesh(const Ptr<Mesh> &mesh) const;
	void setMaskMeshName(const char *mesh_name, bool invalidate);
	void setMaskMeshName(const char *name);
	const char *getMaskMeshName() const;
	void setTerrainMask(int mask);
	int getTerrainMask() const;
	void setMaskInverse(int inverse);
	int getMaskInverse() const;
	void setCutoutIntersectionMask(int mask);
	int getCutoutIntersectionMask() const;
	void setCutoutInverse(int inverse);
	int getCutoutInverse() const;
	void invalidate();
	void invalidate(const Math::WorldBoundBox &bounds);
	void createClutterTransforms();
	bool getClutterTransforms(Vector<Math::mat4> &transforms) const;
	bool getClutterWorldTransforms(Vector<Math::Mat4> &transforms) const;
	bool getClutterTransforms(const Math::WorldBoundBox &bounds, Vector<Math::mat4> &transforms, bool precise = true, bool force = true) const;
	bool getClutterWorldTransforms(const Math::WorldBoundBox &bounds, Vector<Math::Mat4> &transforms, bool precise = true, bool force = true) const;
	int getClutterLocalTransforms(const Math::BoundBox &bounds, Vector<Math::mat4> &transforms, int precise = 1, int force = 1) const;
	void setClutterExclude(const Math::WorldBoundBox &bounds, int exclude);
	void clearClutterExcludes();
};
typedef Ptr<ObjectMeshClutter> ObjectMeshClutterPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectMeshSplineCluster : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_MESH_SPLINE_CLUSTER; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	const char *getMeshPath() const;
	int getNumMeshes() const;
	Math::mat4 getMeshTransform(int num) const;
	bool getClusterTransforms(const Math::WorldBoundBox &bounds, Vector<Math::mat4> &transforms);
	bool getClusterWorldTransforms(const Math::WorldBoundBox &bounds, Vector<Math::Mat4> &transforms);
};
typedef Ptr<ObjectMeshSplineCluster> ObjectMeshSplineClusterPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectSky : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_SKY; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectSky> create();
	void setSpherical(bool spherical);
	bool isSpherical() const;
};
typedef Ptr<ObjectSky> ObjectSkyPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectGrass : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_GRASS; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	using Object::getIntersection;
	using Object::setIntersection;
	using Object::getIntersectionMask;
	using Object::setIntersectionMask;
	static Ptr<ObjectGrass> create();
	void setFieldMask(int mask);
	int getFieldMask() const;
	void setThinning(bool thinning);
	bool getThinning() const;
	void setVariation(bool variation);
	bool getVariation() const;
	void setOrientation(bool orientation);
	bool getOrientation() const;
	void setIntersection(bool intersection);
	bool getIntersection() const;
	void setIntersectionMask(int mask);
	int getIntersectionMask() const;
	void setNumTextures(int textures);
	int getNumTextures() const;
	int getSpawnCount() const;
	void setSeed(int seed);
	int getSeed() const;
	void setSizeX(float sizex);
	float getSizeX() const;
	void setSizeY(float sizey);
	float getSizeY() const;
	void setStep(float step);
	float getStep() const;
	void setSubdivision(int subdivision);
	int getSubdivision() const;
	void setDensity(float density);
	float getDensity() const;
	void setThreshold(float threshold);
	float getThreshold() const;
	void setAngle(float angle);
	float getAngle() const;
	void setProbability(const Math::vec4 &probability);
	Math::vec4 getProbability() const;
	void setMinBend(const Math::vec4 &mean, const Math::vec4 &spread);
	Math::vec4 getMinBendMean() const;
	Math::vec4 getMinBendSpread() const;
	void setMaxBend(const Math::vec4 &mean, const Math::vec4 &spread);
	Math::vec4 getMaxBendMean() const;
	Math::vec4 getMaxBendSpread() const;
	void setMinHeight(const Math::vec4 &mean, const Math::vec4 &spread);
	Math::vec4 getMinHeightMean() const;
	Math::vec4 getMinHeightSpread() const;
	void setMaxHeight(const Math::vec4 &mean, const Math::vec4 &spread);
	Math::vec4 getMaxHeightMean() const;
	Math::vec4 getMaxHeightSpread() const;
	void setAspect(const Math::vec4 &mean, const Math::vec4 &spread);
	Math::vec4 getAspectMean() const;
	Math::vec4 getAspectSpread() const;
	void setOffset(const Math::vec4 &mean, const Math::vec4 &spread);
	Math::vec4 getOffsetMean() const;
	Math::vec4 getOffsetSpread() const;
	void setRotation(const Math::vec4 &mean, const Math::vec4 &spread);
	Math::vec4 getRotationMean() const;
	Math::vec4 getRotationSpread() const;
	int setMaskImage(const Ptr<Image> &image, int invalidate = 1);
	int getMaskImage(const Ptr<Image> &image) const;
	void setMaskImageName(const char *image_name, int invalidate = 1);
	const char *getMaskImageName() const;
	void setMaskFlipX(int maskflipx);
	int getMaskFlipX() const;
	void setMaskFlipY(int maskflipy);
	int getMaskFlipY() const;
	void setMaskMinValue(int value);
	int getMaskMinValue() const;
	void setMaskMaxValue(int value);
	int getMaskMaxValue() const;
	int setMaskMesh(const Ptr<Mesh> &mesh, int invalidate = 1);
	int getMaskMesh(const Ptr<Mesh> &mesh) const;
	void setMaskMeshName(const char *mesh_name, int invalidate = 1);
	const char *getMaskMeshName() const;
	void setTerrainMasks(const Math::ivec4 &masks);
	Math::ivec4 getTerrainMasks() const;
	void setMaskInverse(bool inverse);
	bool getMaskInverse() const;
	void setCutoutIntersectionMask(int mask);
	int getCutoutIntersectionMask() const;
	void setCutoutInverse(bool inverse);
	bool getCutoutInverse() const;
	void invalidate();
	void invalidate(const Math::WorldBoundBox &bounds);
};
typedef Ptr<ObjectGrass> ObjectGrassPtr;

class TerrainDetail;
class TerrainDetailMask;
class ObjectLandscapeTerrain;

class UNIGINE_API TerrainDetail : public APIInterface
{
public:
	void setName(const char *name);
	const char *getName() const;
	void setEnabled(bool enabled);
	bool isEnabled() const;
	bool isActive() const;
	void setMinVisibleHeight(float height);
	float getMinVisibleHeight() const;
	void setMaxVisibleHeight(float height);
	float getMaxVisibleHeight() const;
	void setMinFadeHeight(float height);
	float getMinFadeHeight() const;
	void setMaxFadeHeight(float height);
	float getMaxFadeHeight() const;
	void setMinVisibleTexelSize(float size);
	float getMinVisibleTexelSize() const;
	void setMaxVisibleTexelSize(float size);
	float getMaxVisibleTexelSize() const;
	void setMinFadeTexelSize(float size);
	float getMinFadeTexelSize() const;
	void setMaxFadeTexelSize(float size);
	float getMaxFadeTexelSize() const;
	void setMaskByAlbedo(const Math::vec4 &albedo);
	Math::vec4 getMaskByAlbedo() const;
	void setMaskThreshold(float threshold);
	float getMaskThreshold() const;
	void setMaskContrast(float contrast);
	float getMaskContrast() const;
	void setDetailMask(const Ptr<TerrainDetailMask> &mask);
	Ptr<TerrainDetailMask> getDetailMask() const;
	void setMaterialFilePath(const char *path);
	String getMaterialFilePath() const;
	void setMaterialGUID(const UGUID &materialguid);
	UGUID getMaterialGUID() const;
	void setMaterial(const Ptr<Material> &material);
	Ptr<Material> getMaterial() const;
	Ptr<TerrainDetail> copy(const Ptr<TerrainDetail> &dest_detail) const;
	Ptr<TerrainDetail> clone() const;
};
typedef Ptr<TerrainDetail> TerrainDetailPtr;


class UNIGINE_API TerrainDetailMask : public APIInterface
{
public:
	void setName(const char *name);
	const char *getName() const;
	void setEnabled(bool enabled);
	bool isEnabled() const;
	void setDithering(float dithering);
	float getDithering() const;
	void setDefaultValue(float value);
	float getDefaultValue() const;
	void setMaskByAlbedo(const Math::vec4 &albedo);
	Math::vec4 getMaskByAlbedo() const;
	int getRenderOrder() const;
	void swapRenderOrder(const Ptr<TerrainDetailMask> &mask);
	Ptr<TerrainDetail> addDetail();
	int getNumDetails() const;
	Ptr<TerrainDetail> getDetail(int num) const;
	bool isDetail(const Ptr<TerrainDetail> &detail) const;
	int findDetailIndex(const char *name) const;
	Ptr<TerrainDetail> findDetail(const char *name) const;
	void setDetailIndex(const Ptr<TerrainDetail> &detail, int index);
	int getDetailIndex(const Ptr<TerrainDetail> &detail) const;
	void swapDetail(int num_0, int num_1);
	int getIndex() const;
};
typedef Ptr<TerrainDetailMask> TerrainDetailMaskPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectLandscapeTerrain : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_LANDSCAPE_TERRAIN; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectLandscapeTerrain> create();
	void setActiveTerrain(bool terrain);
	bool isActiveTerrain() const;
	void setIntersectionPrecision(float precision);
	float getIntersectionPrecision() const;
	int getNumDetailMasks() const;
	Ptr<TerrainDetailMask> getDetailMask(int num);
	Ptr<TerrainDetailMask> getDetailMaskSortRender(int num);
	Ptr<TerrainDetailMask> findDetailMask(const char *name);
	long long getLastStreamingFrame() const;
	void getDetailMasks(Vector<Ptr<TerrainDetailMask>> &masks);
	void getDetailMasksSortRender(Vector<Ptr<TerrainDetailMask>> &masks);
};
typedef Ptr<ObjectLandscapeTerrain> ObjectLandscapeTerrainPtr;


class UNIGINE_API LandscapeImages : public APIInterface
{
public:
	static Ptr<LandscapeImages> create(const Math::ivec2 &resolution);
	Ptr<Image> getHeight();
	Ptr<Image> getAlbedo();
	Ptr<Image> getMask(int num);
	Ptr<Image> getOpacityHeight();
	Ptr<Image> getOpacityMask(int num);
	Ptr<Image> get(int type);
	Math::ivec2 getResolution() const;
	void resize(const Math::ivec2 &new_resolution);
	Ptr<LandscapeImages> copy(const Ptr<LandscapeImages> &image) const;
	Ptr<LandscapeImages> clone();
};
typedef Ptr<LandscapeImages> LandscapeImagesPtr;


class UNIGINE_API LandscapeTextures : public APIInterface
{
public:
	static Ptr<LandscapeTextures> create(const Math::ivec2 &resolution);
	Ptr<Texture> getHeight() const;
	Ptr<Texture> getAlbedo() const;
	Ptr<Texture> getMask(int num);
	Ptr<Texture> getOpacityHeight() const;
	Ptr<Texture> getOpacityMask(int num);
	Ptr<Texture> get(int type);
	Ptr<RenderTarget> getRenderTarget() const;
	Math::ivec2 getResolution() const;
	int getNumMipmaps() const;
	void createMipmaps();
	void clearBuffers();
};
typedef Ptr<LandscapeTextures> LandscapeTexturesPtr;

class LandscapeLayerMap;
//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Landscape
{
public:
	static bool isInitialized();

	enum TYPE_DATA
	{
		TYPE_DATA_HEIGHT = 0,
		TYPE_DATA_ALBEDO,
		TYPE_DATA_MASK_0,
		TYPE_DATA_MASK_1,
		TYPE_DATA_MASK_2,
		TYPE_DATA_MASK_3,
		TYPE_DATA_MASK_4,
		TYPE_DATA_MASK_5,
		TYPE_DATA_MASK_6,
		TYPE_DATA_MASK_7,
		TYPE_DATA_MASK_8,
		TYPE_DATA_MASK_9,
		TYPE_DATA_MASK_10,
		TYPE_DATA_MASK_11,
		TYPE_DATA_MASK_12,
		TYPE_DATA_MASK_13,
		TYPE_DATA_MASK_14,
		TYPE_DATA_MASK_15,
		TYPE_DATA_MASK_16,
		TYPE_DATA_MASK_17,
		TYPE_DATA_MASK_18,
		TYPE_DATA_MASK_19,
	};

	enum FLAGS_DATA
	{
		FLAGS_DATA_HEIGHT = 1 << 0,
		FLAGS_DATA_ALBEDO = 1 << 1,
		FLAGS_DATA_MASK_0 = 1 << 2,
		FLAGS_DATA_MASK_1 = 1 << 3,
		FLAGS_DATA_MASK_2 = 1 << 4,
		FLAGS_DATA_MASK_3 = 1 << 5,
		FLAGS_DATA_MASK_4 = 1 << 6,
		FLAGS_DATA_MASK_5 = 1 << 7,
		FLAGS_DATA_MASK_6 = 1 << 8,
		FLAGS_DATA_MASK_7 = 1 << 9,
		FLAGS_DATA_MASK_8 = 1 << 10,
		FLAGS_DATA_MASK_9 = 1 << 11,
		FLAGS_DATA_MASK_10 = 1 << 12,
		FLAGS_DATA_MASK_11 = 1 << 13,
		FLAGS_DATA_MASK_12 = 1 << 14,
		FLAGS_DATA_MASK_13 = 1 << 15,
		FLAGS_DATA_MASK_14 = 1 << 16,
		FLAGS_DATA_MASK_15 = 1 << 17,
		FLAGS_DATA_MASK_16 = 1 << 18,
		FLAGS_DATA_MASK_17 = 1 << 19,
		FLAGS_DATA_MASK_18 = 1 << 20,
		FLAGS_DATA_MASK_19 = 1 << 21,
	};

	enum TYPE_FILE_DATA
	{
		TYPE_FILE_DATA_HEIGHT,
		TYPE_FILE_DATA_ALBEDO,
		TYPE_FILE_DATA_MASK_0,
		TYPE_FILE_DATA_MASK_1,
		TYPE_FILE_DATA_MASK_2,
		TYPE_FILE_DATA_MASK_3,
		TYPE_FILE_DATA_MASK_4,
		TYPE_FILE_DATA_OPACITY_HEIGHT,
		TYPE_FILE_DATA_OPACITY_MASK_0,
		TYPE_FILE_DATA_OPACITY_MASK_1,
		TYPE_FILE_DATA_OPACITY_MASK_2,
		TYPE_FILE_DATA_OPACITY_MASK_3,
		TYPE_FILE_DATA_OPACITY_MASK_4,
	};

	enum FLAGS_FILE_DATA
	{
		FLAGS_FILE_DATA_HEIGHT = 1 << 0,
		FLAGS_FILE_DATA_ALBEDO = 1 << 1,
		FLAGS_FILE_DATA_MASK_0 = 1 << 2,
		FLAGS_FILE_DATA_MASK_1 = 1 << 3,
		FLAGS_FILE_DATA_MASK_2 = 1 << 4,
		FLAGS_FILE_DATA_MASK_3 = 1 << 5,
		FLAGS_FILE_DATA_MASK_4 = 1 << 6,
		FLAGS_FILE_DATA_OPACITY_HEIGHT = 1 << 7,
		FLAGS_FILE_DATA_OPACITY_MASK_0 = 1 << 8,
		FLAGS_FILE_DATA_OPACITY_MASK_1 = 1 << 9,
		FLAGS_FILE_DATA_OPACITY_MASK_2 = 1 << 10,
		FLAGS_FILE_DATA_OPACITY_MASK_3 = 1 << 11,
		FLAGS_FILE_DATA_OPACITY_MASK_4 = 1 << 12,
	};

	enum COMPRESSOR_TYPE
	{
		COMPRESSOR_TYPE_NONE = 0,
		COMPRESSOR_TYPE_JACKALLESS = 1,
		COMPRESSOR_TYPE_LZ4 = 2,
		COMPRESSOR_TYPE_ZLIB = 3,
	};

	enum BLENDING_MODE
	{
		ALPHA_BLEND = 0,
		ADDITIVE = 1,
		OVERLAY = 2,
		MULTIPLICATIVE = 3,
	};
	static Ptr<LandscapeTextures> getTemporaryTexture(const Math::ivec2 &resolution);
	static void releaseTemporaryTexture(const Ptr<LandscapeTextures> &texture);
	static bool terrainLoad(const Math::WorldBoundBox &bb);
	static bool render(const Ptr<LandscapeTextures> &buffers, const Math::Mat4 &transform, Math::Scalar texel_size, int padding);
	static bool render(const Ptr<LandscapeTextures> &buffers, const Math::Mat4 &transform, Math::Scalar texel_size);
	static bool render(const Vector<Ptr<LandscapeLayerMap>> &maps, const Ptr<LandscapeTextures> &buffers, const Math::Mat4 &transform, Math::Scalar texel_size, int padding);
	static bool render(const Vector<Ptr<LandscapeLayerMap>> &maps, const Ptr<LandscapeTextures> &buffers, const Math::Mat4 &transform, Math::Scalar texel_size);
	static int generateOperationID();
	static void asyncTextureDraw(int operation_id, const UGUID &file_guid, const Math::ivec2 &coord, const Math::ivec2 &resolution, int flags_file_data, const Vector<Math::WorldBoundBox> &bounds_preload);
	static void asyncTextureDraw(int operation_id, const UGUID &file_guid, const Math::ivec2 &coord, const Math::ivec2 &resolution, int flags_file_data);
	static void asyncTextureDraw(int operation_id, const UGUID &file_guid, const Math::ivec2 &coord, const Math::ivec2 &resolution);
	static void asyncTextureDraw(const UGUID &file_guid, const Math::ivec2 &coord, const Math::ivec2 &resolution, int flags_file_data, const Vector<Math::WorldBoundBox> &bounds_preload);
	static void asyncTextureDraw(const UGUID &file_guid, const Math::ivec2 &coord, const Math::ivec2 &resolution, int flags_file_data);
	static void asyncTextureDraw(const UGUID &file_guid, const Math::ivec2 &coord, const Math::ivec2 &resolution);
	static void asyncApplyDiff(int operation_id, const UGUID &file_guid, const char *path);
	static void asyncApplyDiff(const UGUID &file_guid, const char *path);
	static void asyncSaveFile(int operation_id, const UGUID &file_guid, const char *path_new_diff, const char *path_old_diff);
	static void asyncSaveFile(int operation_id, const UGUID &file_guid);
	static void asyncSaveFile(const UGUID &file_guid, const char *path_new_diff, const char *path_old_diff);
	static void asyncSaveFile(const UGUID &file_guid);
	static bool isFilesClosed();
	static void filesClose(const Vector<UGUID> &reload_files);
	static void filesClose();
	static void filesOpen();
	static Event<const UGUID &, int, const Ptr<LandscapeTextures> &, const Math::ivec2 &, int> &getEventTextureDraw();
	static Event<const UGUID &, int, const char *> &getEventApplyDiff();
	static Event<const UGUID &, int, const char *, const char *> &getEventSaveFile();
	static Ptr<ObjectLandscapeTerrain> getActiveTerrain();
};

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API LandscapeLayerMap : public Node
{
public:
	static Node::TYPE type() { return Node::LANDSCAPE_LAYER_MAP; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<LandscapeLayerMap> create();
	void setPath(const char *path);
	const char *getPath() const;
	UGUID getGUID();
	void setIntersectionBicubicFilter(bool filter);
	bool isIntersectionBicubicFilter() const;
	void setIntersection(bool intersection);
	bool isIntersection() const;
	void setCollision(bool collision);
	bool isCollision() const;
	void setCulling(bool culling);
	bool isCulling() const;
	void setOrder(int order);
	int getOrder() const;
	void setSize(const Math::Vec2 &size);
	Math::Vec2 getSize() const;
	void setFadeAttenuation(const Math::vec2 &attenuation);
	Math::vec2 getFadeAttenuation() const;
	void setHeightScale(float scale);
	float getHeightScale() const;
	Math::Vec2 getTexelSize() const;
	Math::ivec2 getResolution() const;
	bool isInit() const;
	Math::Vec2 getExtremumHeight(float precision = 1.0f);
	bool isEnabledHeight() const;
	bool isEnabledAlbedo() const;
	bool isEnabledMask(int mask) const;
	bool isEnabledOpacityHeight() const;
	bool isEnabledOpacityAlbedo() const;
	int isEnabledOpacityMask(int mask) const;
	Landscape::BLENDING_MODE getHeightBlending() const;
	Landscape::BLENDING_MODE getAlbedoBlending() const;
	Landscape::BLENDING_MODE getMaskBlending(int mask) const;
	Math::vec2 getHeightFadeAttenuation() const;
	Math::vec2 getAlbedoFadeAttenuation() const;
	Math::vec2 getMaskFadeAttenuation(int mask) const;
	bool isCompressed() const;
};
typedef Ptr<LandscapeLayerMap> LandscapeLayerMapPtr;


class UNIGINE_API LandscapeMapFileSettings : public APIInterface
{
public:
	static Ptr<LandscapeMapFileSettings> create();
	void setHeightBlending(Landscape::BLENDING_MODE blending);
	Landscape::BLENDING_MODE getHeightBlending() const;
	void setAlbedoBlending(Landscape::BLENDING_MODE blending);
	Landscape::BLENDING_MODE getAlbedoBlending() const;
	void setHeightFadeAttenuation(const Math::vec2 &attenuation);
	Math::vec2 getHeightFadeAttenuation() const;
	void setAlbedoFadeAttenuation(const Math::vec2 &attenuation);
	Math::vec2 getAlbedoFadeAttenuation() const;
	void setMaskBlending(int mask, Landscape::BLENDING_MODE blend);
	Landscape::BLENDING_MODE getMaskBlending(int mask) const;
	void setMaskFadeAttenuation(int mask, const Math::vec2 &fade_attenuation);
	Math::vec2 getMaskFadeAttenuation(int mask) const;
	void setEnabledHeight(bool height);
	bool isEnabledHeight() const;
	void setEnabledAlbedo(bool albedo);
	bool isEnabledAlbedo() const;
	void setEnabledMask(int mask, bool enabled);
	bool isEnabledMask(int mask) const;
	void setEnabledOpacityHeight(bool height);
	bool isEnabledOpacityHeight() const;
	void setEnabledOpacityAlbedo(bool albedo);
	bool isEnabledOpacityAlbedo() const;
	void setEnabledOpacityMask(int mask, bool enabled);
	bool isEnabledOpacityMask(int mask) const;
	Landscape::COMPRESSOR_TYPE getHeightCompressor() const;
	Landscape::COMPRESSOR_TYPE getAlbedoCompressor() const;
	Landscape::COMPRESSOR_TYPE getOpacityHeightCompressor() const;
	bool isCompressed() const;
	Landscape::COMPRESSOR_TYPE getMaskCompressor(int mask);
	Landscape::COMPRESSOR_TYPE getMaskOpacityCompressor(int mask);
	bool isEnabledAlbedoTextureCompression() const;
	bool isEnabledOpacityHeightTextureCompression() const;
	bool isEnabledMaskTextureCompression(int mask);
	bool isEnabledMaskOpacityTextureCompression(int mask);
	Math::ivec2 getTilesSize() const;
	Math::ivec2 getResolution() const;
	UGUID getGUID() const;
	bool isLoaded() const;
	bool load(const UGUID &guid);
	bool apply();
};
typedef Ptr<LandscapeMapFileSettings> LandscapeMapFileSettingsPtr;

class LandscapeMapFileCompression;
template class UNIGINE_API EventHolder<EventInterfaceInvoker<const Ptr<LandscapeMapFileCompression> &>>;
template class UNIGINE_API EventInterfaceConnection<EventInterfaceInvoker<const Ptr<LandscapeMapFileCompression> &>>;

class UNIGINE_API LandscapeMapFileCompression : public APIInterface
{
public:
	static Ptr<LandscapeMapFileCompression> create();
	bool isCompressing() const;
	bool isDecompressing() const;
	int getProgress() const;
	bool compress(bool is_safe);
	bool decompress(bool is_safe);
	void stop();
	void setHeightCompressor(Landscape::COMPRESSOR_TYPE compressor);
	Landscape::COMPRESSOR_TYPE getHeightCompressor() const;
	void setAlbedoCompressor(Landscape::COMPRESSOR_TYPE compressor);
	Landscape::COMPRESSOR_TYPE getAlbedoCompressor() const;
	void setOpacityHeightCompressor(Landscape::COMPRESSOR_TYPE compressor);
	Landscape::COMPRESSOR_TYPE getOpacityHeightCompressor() const;
	void setMaskCompressor(int mask, Landscape::COMPRESSOR_TYPE compressor_type);
	void setMaskOpacityCompressor(int mask, Landscape::COMPRESSOR_TYPE compressor_type);
	int getMaskCompressor(int mask);
	int getMaskOpacityCompressor(int mask);
	void setEnabledAlbedoTextureCompression(bool compression);
	bool isEnabledAlbedoTextureCompression() const;
	void setEnabledOpacityHeightTextureCompression(bool compression);
	bool isEnabledOpacityHeightTextureCompression() const;
	void setEnabledMaskTextureCompression(int mask, bool enable);
	void setEnabledMaskOpacityTextureCompression(int mask, bool enable);
	bool isEnabledMaskTextureCompression(int mask);
	bool isEnabledMaskOpacityTextureCompression(int mask);
	void setCompressorAll(Landscape::COMPRESSOR_TYPE compressor_type);
	void setCacheDirectory(const char *directory);
	const char *getCacheDirectory() const;
	void setGUID(const UGUID &guid);
	UGUID getGUID() const;
	Event<const Ptr<LandscapeMapFileCompression> &> &getEventBegin();
	Event<const Ptr<LandscapeMapFileCompression> &> &getEventProgress();
	Event<const Ptr<LandscapeMapFileCompression> &> &getEventEnd();

private:

	EventHolder<EventInterfaceInvoker<const Ptr<LandscapeMapFileCompression> &>> event_begin;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<LandscapeMapFileCompression> &>> event_begin_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<LandscapeMapFileCompression> &>> event_progress;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<LandscapeMapFileCompression> &>> event_progress_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<LandscapeMapFileCompression> &>> event_end;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<LandscapeMapFileCompression> &>> event_end_connection;
};
typedef Ptr<LandscapeMapFileCompression> LandscapeMapFileCompressionPtr;


class UNIGINE_API LandscapeFetch : public APIInterface
{
public:
	static Ptr<LandscapeFetch> create();
	Math::Vec3 getPosition() const;
	float getHeight() const;
	bool isIntersection() const;
	Math::vec3 getNormal() const;
	Math::vec4 getAlbedo() const;
	float getMask(int num) const;
	void setUses(int uses);
	int getUses() const;
	void setUsesHeight(bool height);
	bool isUsesHeight() const;
	void setUsesNormal(bool normal);
	bool isUsesNormal() const;
	void setUsesAlbedo(bool albedo);
	bool isUsesAlbedo() const;
	bool isUsesMask(int num) const;
	void setUsesMask(int num, bool value);
	void setHolesEnabled(bool enabled);
	bool isHolesEnabled() const;
	void setIntersectionPrecision(float precision);
	float getIntersectionPrecision() const;
	void setIntersectionPositionBegin(const Math::Vec3 &begin);
	Math::Vec3 getIntersectionPositionBegin() const;
	void setIntersectionPositionEnd(const Math::Vec3 &end);
	Math::Vec3 getIntersectionPositionEnd() const;
	void setFetchPosition(const Math::Vec2 &position);
	Math::Vec2 getFetchPosition() const;
	bool fetchForce(const Math::Vec2 &position);
	bool fetchForce();
	bool intersectionForce(const Math::Vec3 &p0, const Math::Vec3 &p1);
	bool intersectionForce();
	void fetchAsync(const Math::Vec2 &position, bool critical = false);
	void fetchAsync(bool critical = false);
	void intersectionAsync(const Math::Vec3 &p0, const Math::Vec3 &p1, bool critical = false);
	void intersectionAsync(bool critical = false);
	static void fetchForce(const Vector<Ptr<LandscapeFetch>> &fetches);
	static void intersectionForce(const Vector<Ptr<LandscapeFetch>> &fetches);
	static void fetchAsync(const Vector<Ptr<LandscapeFetch>> &fetches, bool critical = false);
	static void intersectionAsync(const Vector<Ptr<LandscapeFetch>> &fetches, bool critical = false);
	static void wait(const Vector<Ptr<LandscapeFetch>> &fetches);
	void wait();
	bool isAsyncCompleted() const;
	Event<> &getEventStart();
	Event<> &getEventEnd();
};
typedef Ptr<LandscapeFetch> LandscapeFetchPtr;

class LandscapeMapFileCreator;
template class UNIGINE_API EventHolder<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &, const Ptr<LandscapeImages> &, int, int>>;
template class UNIGINE_API EventInterfaceConnection<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &, const Ptr<LandscapeImages> &, int, int>>;
template class UNIGINE_API EventHolder<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &>>;
template class UNIGINE_API EventInterfaceConnection<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &>>;

class UNIGINE_API LandscapeMapFileCreator : public APIInterface
{
public:
	static Ptr<LandscapeMapFileCreator> create();
	void setResolution(const Math::ivec2 &resolution);
	Math::ivec2 getResolution() const;
	void setGrid(const Math::ivec2 &grid);
	Math::ivec2 getGrid() const;
	void setDownscaleFilter(Landscape::TYPE_FILE_DATA file_data_type, Image::FILTER filter);
	Image::FILTER getDownscaleFilter(Landscape::TYPE_FILE_DATA file_data_type) const;
	float getProgress() const;
	double getTimeSeconds() const;
	void setPath(const char *path);
	const char *getPath() const;
	Event<const Ptr<LandscapeMapFileCreator> &, const Ptr<LandscapeImages> &, int, int> &getEventCreate();
	Event<const Ptr<LandscapeMapFileCreator> &> &getEventProgress();
	Event<const Ptr<LandscapeMapFileCreator> &> &getEventBegin();
	Event<const Ptr<LandscapeMapFileCreator> &> &getEventEnd();
	bool run(bool is_empty = false, bool is_safe = true);

private:

	EventHolder<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &, const Ptr<LandscapeImages> &, int, int>> event_create;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &, const Ptr<LandscapeImages> &, int, int>> event_create_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &>> event_progress;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &>> event_progress_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &>> event_begin;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &>> event_begin_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &>> event_end;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<LandscapeMapFileCreator> &>> event_end_connection;
};
typedef Ptr<LandscapeMapFileCreator> LandscapeMapFileCreatorPtr;


class UNIGINE_API TerrainGlobalLod : public APIInterface
{
public:
	static bool convertible(TerrainGlobalLod *obj) { return obj != nullptr; }

	enum TYPE
	{
		TERRAIN_GLOBAL_LOD = 0,
		TERRAIN_GLOBAL_LOD_HEIGHT,
		NUM_TERRAIN_GLOBAL_LODS,
	};
	TerrainGlobalLod::TYPE getType() const;
	const char *getTypeName() const;
	void setEnabled(bool enabled);
	bool isEnabled() const;
	Ptr<Tileset> getTileset() const;
	void setPath(const char *path);
	const char *getPath() const;
	int renamePath(const char *new_path);
	void setTileDensity(float density);
	float getTileDensity() const;
	void setViewportMask(int mask);
	int getViewportMask() const;
	void setVisibleDistance(float distance);
	float getVisibleDistance() const;
	void setLoadDistance(float distance);
	float getLoadDistance() const;
	void setClearDistance(float distance);
	float getClearDistance() const;
	void reload();
};
typedef Ptr<TerrainGlobalLod> TerrainGlobalLodPtr;


class UNIGINE_API TerrainGlobalLodHeight : public TerrainGlobalLod
{
public:
	static bool convertible(TerrainGlobalLod *obj) { return obj && obj->getType() == TerrainGlobalLod::TERRAIN_GLOBAL_LOD_HEIGHT; }
	void setIntersection(bool intersection);
	bool isIntersection() const;
	void setCollision(bool collision);
	bool isCollision() const;
	void setCastShadows(bool shadows);
	bool isCastShadows() const;
	void setIntersectionMask(int mask);
	int getIntersectionMask() const;
	void setCollisionMask(int mask);
	int getCollisionMask() const;
};
typedef Ptr<TerrainGlobalLodHeight> TerrainGlobalLodHeightPtr;


class UNIGINE_API TerrainGlobalLods : public APIInterface
{
public:
	const char *getName() const;
	int getType() const;
	int getDataType() const;
	int getDataFormat() const;
	int getMaskFormat() const;
	void setNumLayers(int layers);
	int getNumLayers() const;
	int getNumLods() const;
	Ptr<TerrainGlobalLod> getLod(int num) const;
	int addLod();
	void insertLod(int num);
	void removeLod(int num);
	void clearLods();
	String getVideoMemoryUsage() const;
	int fetch(const Math::BoundSphere &bs, const Math::BoundBox &bb, int force = 0);
	int fetchData(double x, double y, Image::Pixel &ret_pixel, int layer, bool force);
};
typedef Ptr<TerrainGlobalLods> TerrainGlobalLodsPtr;


class UNIGINE_API TerrainGlobalDetail : public APIInterface
{
public:
	void setName(const char *name);
	const char *getName() const;
	void setEnabled(bool enabled);
	bool isEnabled() const;
	void setMaskNumber(int number);
	int getMaskNumber() const;
	void setMaskColor(const Math::vec4 &color);
	Math::vec4 getMaskColor() const;
	void setTransform(const Math::vec4 &transform);
	Math::vec4 getTransform() const;
	void setMinVisibleHeight(float height);
	float getMinVisibleHeight() const;
	void setMaxVisibleHeight(float height);
	float getMaxVisibleHeight() const;
	void setMinFadeHeight(float height);
	float getMinFadeHeight() const;
	void setMaxFadeHeight(float height);
	float getMaxFadeHeight() const;
	void setMinVisibleDistance(float distance);
	float getMinVisibleDistance() const;
	void setMaxVisibleDistance(float distance);
	float getMaxVisibleDistance() const;
	void setMinFadeDistance(float distance);
	float getMinFadeDistance() const;
	void setMaxFadeDistance(float distance);
	float getMaxFadeDistance() const;
	void setOverlap(bool overlap);
	bool isOverlap() const;
	void setDetail(bool detail);
	bool isDetail() const;
	void setTriplanar(bool triplanar);
	bool isTriplanar() const;
	void setBlendTriplanar(float triplanar);
	float getBlendTriplanar() const;
	void setMaskThreshold(float threshold);
	float getMaskThreshold() const;
	void setMaskWidth(float width);
	float getMaskWidth() const;
	void setMaskContrast(float contrast);
	float getMaskContrast() const;
	void setAlbedoTextureName(const char *name);
	const char *getAlbedoTextureName() const;
	void setRoughnessTextureName(const char *name);
	const char *getRoughnessTextureName() const;
	void setNormalTextureName(const char *name);
	const char *getNormalTextureName() const;
	void setHeightTextureName(const char *name);
	const char *getHeightTextureName() const;
	void setAlbedoColor(const Math::vec4 &color);
	Math::vec4 getAlbedoColor() const;
	void setRoughness(float roughness);
	float getRoughness() const;
	void setAlbedoScale(float scale);
	float getAlbedoScale() const;
	void setRoughnessScale(float scale);
	float getRoughnessScale() const;
	void setNormalScale(float scale);
	float getNormalScale() const;
	void setDisplacement(float displacement);
	float getDisplacement() const;
	void setDisplacementOffset(float offset);
	float getDisplacementOffset() const;
};
typedef Ptr<TerrainGlobalDetail> TerrainGlobalDetailPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectTerrainGlobal : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_TERRAIN_GLOBAL; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectTerrainGlobal> create();
	void clear();
	int fetchTopologyData(double x, double y, Math::Vec3 &ret_point, Math::vec3 &ret_normal, Math::vec3 &ret_up, int force = 0);
	Ptr<TerrainGlobalLods> getHeightLods();
	Ptr<TerrainGlobalLods> getAlbedoLods();
	Ptr<TerrainGlobalLods> getNormalLods();
	Ptr<TerrainGlobalLods> getMaskLods();
	int addMask(const char *name);
	void removeMask(int num);
	void resizeMasks(int size);
	int getNumMasks() const;
	void swapMask(int num_0, int num_1);
	int cloneMask(int num);
	void setMaskName(int num, const char *name);
	const char *getMaskName(int num) const;
	void replaceMasks(const Vector<String> &names);
	int getNumDetails() const;
	Ptr<TerrainGlobalDetail> getDetail(int num);
	int addDetail(const char *name);
	void removeDetail(int num);
	void resizeDetails(int size);
	void swapDetail(int num_0, int num_1);
	int cloneDetail(int num);
	void setAlbedoTextureArrayName(const char *name);
	const char *getAlbedoTextureArrayName() const;
	Ptr<Texture> getAlbedoTextureArray() const;
	void setNormalTextureArrayName(const char *name);
	const char *getNormalTextureArrayName() const;
	Ptr<Texture> getNormalTextureArray() const;
	void setHeightTextureArrayName(const char *name);
	const char *getHeightTextureArrayName() const;
	Ptr<Texture> getHeightTextureArray() const;
	void setForceIntersection(bool intersection);
	bool isForceIntersection() const;
};
typedef Ptr<ObjectTerrainGlobal> ObjectTerrainGlobalPtr;


class UNIGINE_API ParticleModifier : public APIInterface
{
public:
	static bool convertible(ParticleModifier *obj) { return obj != nullptr; }

	enum TYPE
	{
		PARTICLE_MODIFIER_SCALAR = 0,
		PARTICLE_MODIFIER_VECTOR,
	};

	enum MODE
	{
		MODE_CONSTANT = 0,
		MODE_RANDOM_BETWEEN_TWO_CONSTANTS,
		MODE_CURVE,
		MODE_RANDOM_BETWEEN_TWO_CURVES,
		NUM_MODES,
	};
	bool isSignedValues() const;
	bool saveState(const Ptr<Stream> &stream) const;
	bool restoreState(const Ptr<Stream> &stream);
	bool save(const Ptr<Xml> &xml) const;
	bool load(const Ptr<Xml> &xml);
	long long getSystemMemoryUsage() const;
	ParticleModifier::TYPE getType() const;
	void setMode(ParticleModifier::MODE mode);
	ParticleModifier::MODE getMode() const;
};
typedef Ptr<ParticleModifier> ParticleModifierPtr;


class UNIGINE_API ParticleModifierScalar : public ParticleModifier
{
public:
	static bool convertible(ParticleModifier *obj) { return obj && obj->getType() == ParticleModifier::PARTICLE_MODIFIER_SCALAR; }
	void setCurveScale(float scale);
	float getCurveScale() const;
	void setConstant(float constant);
	float getConstant() const;
	void setConstantMin(float val);
	float getConstantMin() const;
	void setConstantMax(float val);
	float getConstantMax() const;
	void setCurve(const Ptr<Curve2d> &curve);
	Ptr<Curve2d> getCurve() const;
	void setCurveMin(const Ptr<Curve2d> &val);
	Ptr<Curve2d> getCurveMin() const;
	void setCurveMax(const Ptr<Curve2d> &val);
	Ptr<Curve2d> getCurveMax() const;
	float getMaxValue() const;
	float getMinValue() const;
};
typedef Ptr<ParticleModifierScalar> ParticleModifierScalarPtr;


class UNIGINE_API ParticleModifierVector : public ParticleModifier
{
public:
	static bool convertible(ParticleModifier *obj) { return obj && obj->getType() == ParticleModifier::PARTICLE_MODIFIER_VECTOR; }
	void setConstant(const Math::vec3 &constant);
	Math::vec3 getConstant() const;
	void setConstantMin(const Math::vec3 &val);
	Math::vec3 getConstantMin() const;
	void setConstantMax(const Math::vec3 &val);
	Math::vec3 getConstantMax() const;
	void setCurveScale(float scale);
	float getCurveScale() const;
	void setCurveX(const Ptr<Curve2d> &curvex);
	Ptr<Curve2d> getCurveX() const;
	void setCurveY(const Ptr<Curve2d> &curvey);
	Ptr<Curve2d> getCurveY() const;
	void setCurveZ(const Ptr<Curve2d> &curvez);
	Ptr<Curve2d> getCurveZ() const;
	void setCurveXMin(const Ptr<Curve2d> &xmin);
	Ptr<Curve2d> getCurveXMin() const;
	void setCurveYMin(const Ptr<Curve2d> &ymin);
	Ptr<Curve2d> getCurveYMin() const;
	void setCurveZMin(const Ptr<Curve2d> &zmin);
	Ptr<Curve2d> getCurveZMin() const;
	void setCurveXMax(const Ptr<Curve2d> &xmax);
	Ptr<Curve2d> getCurveXMax() const;
	void setCurveYMax(const Ptr<Curve2d> &ymax);
	Ptr<Curve2d> getCurveYMax() const;
	void setCurveZMax(const Ptr<Curve2d> &zmax);
	Ptr<Curve2d> getCurveZMax() const;
	Math::vec3 getMaxValue() const;
	Math::vec3 getMinValue() const;
};
typedef Ptr<ParticleModifierVector> ParticleModifierVectorPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectParticles : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_PARTICLES; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }


	enum SCREEN_SIZE_MODE
	{
		SCREEN_SIZE_MODE_NONE = 0,
		SCREEN_SIZE_MODE_WIDTH,
		SCREEN_SIZE_MODE_HEIGHT,
	};
	void setScreenSizeMode(ObjectParticles::SCREEN_SIZE_MODE mode);
	ObjectParticles::SCREEN_SIZE_MODE getScreenSizeMode() const;
	void setScreenMinSize(float size);
	float getScreenMinSize() const;
	void setScreenMaxSize(float size);
	float getScreenMaxSize() const;
	using Object::getIntersection;
	using Object::setIntersection;
	using Object::getCollision;
	using Object::setCollision;
	static Ptr<ObjectParticles> create();
	void setFPSVisibleCamera(int camera);
	int getFPSVisibleCamera() const;
	void setFPSVisibleShadow(int shadow);
	int getFPSVisibleShadow() const;
	void setFPSInvisible(int invisible);
	int getFPSInvisible() const;
	void setUpdateDistanceLimit(float limit);
	float getUpdateDistanceLimit() const;
	void setSeed(unsigned int seed);
	unsigned int getSeed() const;
	void setParticlesType(int type);
	int getParticlesType() const;
	void setWarming(int warming);
	int getWarming() const;
	void setMaxWarmingTime(float time);
	float getMaxWarmingTime() const;
	void setDepthSort(int sort);
	int getDepthSort() const;
	void setVariationX(int variationx);
	int getVariationX() const;
	void setVariationY(int variationy);
	int getVariationY() const;
	void setTextureAtlas(int atlas);
	int getTextureAtlas() const;
	void setTextureAtlasSize(const Math::ivec2 &size);
	Math::ivec2 getTextureAtlasSize() const;
	void setPhysicsIntersectionEnabled(bool enabled);
	bool isPhysicsIntersectionEnabled() const;
	void setPhysicsIntersectionMask(int mask);
	int getPhysicsIntersectionMask() const;
	void setCollisionEnabled(bool enabled);
	bool isCollisionEnabled() const;
	void setCollisionMask(int mask);
	int getCollisionMask() const;
	void setCulling(int culling);
	int getCulling() const;
	void setClearOnEnable(bool enable);
	bool isClearOnEnable() const;
	void setNumberPerSpawn(int spawn);
	int getNumberPerSpawn() const;
	void setSpawnRate(float rate);
	float getSpawnRate() const;
	void setSpawnScale(float scale);
	float getSpawnScale() const;
	void setSpawnThreshold(float threshold);
	float getSpawnThreshold() const;
	void clearParticles();
	int getNumParticles() const;
	float getParticleRadius(int num) const;
	Math::Vec3 getParticlePosition(int num) const;
	Math::vec3 getParticleVelocity(int num) const;
	void getParticleTransforms(Vector<Math::Mat4> &transforms) const;
	void setPhysicalMask(int mask);
	int getPhysicalMask() const;
	void setParticlesFieldMask(int mask);
	int getParticlesFieldMask() const;
	void setPhysicalMass(float mass);
	float getPhysicalMass() const;
	void setRestitution(float restitution);
	float getRestitution() const;
	void setRoughness(float roughness);
	float getRoughness() const;
	void setEmitterType(int type);
	int getEmitterType() const;
	void setProceduralRendering(bool rendering);
	bool isProceduralRendering() const;
	void setProceduralPositioning(int positioning);
	int getProceduralPositioning() const;
	void setProceduralParenting(int parenting);
	int getProceduralParenting() const;
	void setProceduralTextureResolution(const Math::vec3 &res);
	Math::vec3 getProceduralTextureResolution() const;
	void setEmitterEnabled(bool enabled);
	bool isEmitterEnabled() const;
	void setEmitterBased(bool based);
	bool isEmitterBased() const;
	void setEmitterShift(bool shift);
	bool isEmitterShift() const;
	void setEmitterContinuous(bool continuous);
	bool isEmitterContinuous() const;
	void setEmitterSequence(int sequence);
	int getEmitterSequence() const;
	void setEmitterLimitPerSpawn(int spawn);
	int getEmitterLimitPerSpawn() const;
	void setEmitterSync(int sync);
	int getEmitterSync() const;
	void setEmitterSize(const Math::vec3 &size);
	Math::vec3 getEmitterSize() const;
	void setEmitterVelocity(const Math::vec3 &velocity);
	Math::vec3 getEmitterVelocity() const;
	void addEmitterSpark(const Math::Vec3 &point, const Math::vec3 &normal, const Math::vec3 &velocity);
	void setDelay(float mean, float spread);
	float getDelayMean() const;
	float getDelaySpread() const;
	void setPeriod(float mean, float spread);
	float getPeriodMean() const;
	float getPeriodSpread() const;
	void setDuration(float mean, float spread);
	float getDurationMean() const;
	float getDurationSpread() const;
	void setLife(float mean, float spread);
	float getLifeMean() const;
	float getLifeSpread() const;
	Ptr<ParticleModifierScalar> getAngleOverTimeModifier() const;
	Ptr<ParticleModifierScalar> getRotationOverTimeModifier() const;
	Ptr<ParticleModifierScalar> getRadiusOverTimeModifier() const;
	Ptr<ParticleModifierScalar> getGrowthOverTimeModifier() const;
	Ptr<ParticleModifierScalar> getLengthStretchOverTimeModifier() const;
	Ptr<ParticleModifierScalar> getLengthFlatteningOverTimeModifier() const;
	Ptr<ParticleModifierScalar> getVelocityOverTimeModifier() const;
	Ptr<ParticleModifierScalar> getLinearDampingOverTimeModifier() const;
	Ptr<ParticleModifierVector> getDirectionOverTimeModifier() const;
	Ptr<ParticleModifierVector> getPositionOverTimeModifier() const;
	Ptr<ParticleModifierVector> getGravityOverTimeModifier() const;
	int getNumContacts() const;
	Math::Vec3 getContactPoint(int num) const;
	Math::vec3 getContactNormal(int num) const;
	Math::vec3 getContactVelocity(int num) const;
	Ptr<Object> getContactObject(int num) const;
	Math::Vec3 getWorldOffset() const;
	int saveStateSelf(const Ptr<Stream> &stream) const;
	int restoreStateSelf(const Ptr<Stream> &stream);
	Math::BoundBox getBoundBoxParticles() const;
	Math::BoundBox getBoundBoxSimulation() const;
	Math::WorldBoundBox getWorldBoundBoxParticles() const;

	enum SYNC_MODE
	{
		SYNC_MODE_NONE = 0,
		SYNC_MODE_MASTER,
		SYNC_MODE_SLAVE,
	};
	void setSyncMode(ObjectParticles::SYNC_MODE mode);
	ObjectParticles::SYNC_MODE getSyncMode() const;
	void takeSyncData(const Ptr<Stream> &stream);
	void applySyncData(const Ptr<Stream> &stream);

	enum
	{
		TYPE_BILLBOARD = 0,
		TYPE_FLAT,
		TYPE_POINT,
		TYPE_LENGTH,
		TYPE_RANDOM,
		TYPE_ROUTE,
		TYPE_CHAIN,
	};

	enum
	{
		EMITTER_POINT = 0,
		EMITTER_SPHERE,
		EMITTER_CYLINDER,
		EMITTER_BOX,
		EMITTER_RANDOM,
		EMITTER_SPARK,
	};
};
typedef Ptr<ObjectParticles> ObjectParticlesPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectBillboards : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_BILLBOARDS; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectBillboards> create();
	void setDepthSort(int sort);
	int getDepthSort() const;
	void clearBillboards();
	void allocateBillboards(int num);
	int addBillboard(float width, float height);
	void removeBillboard(int num);
	int getNumBillboards() const;
	void setBillboardPosition(int num, const Math::vec3 &position);
	Math::vec3 getBillboardPosition(int num) const;
	void setTexCoord(int num, const Math::vec4 &texcoord);
	Math::vec4 getTexCoord(int num) const;
	void setWidth(int num, float width);
	float getWidth(int num) const;
	void setHeight(int num, float height);
	float getHeight(int num) const;
	void setAngle(int num, float angle);
	float getAngle(int num) const;
	void setNormal(int num, const Math::vec3 &normal);
	Math::vec3 getNormal(int num) const;
	int saveStateSelf(const Ptr<Stream> &stream) const;
	int restoreStateSelf(const Ptr<Stream> &stream);
	int saveStateBillboards(const Ptr<Stream> &stream) const;
	int restoreStateBillboards(const Ptr<Stream> &stream);
};
typedef Ptr<ObjectBillboards> ObjectBillboardsPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectVolumeBox : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_VOLUME_BOX; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectVolumeBox> create(const Math::vec3 &size);
	void setSize(const Math::vec3 &size);
	Math::vec3 getSize() const;
};
typedef Ptr<ObjectVolumeBox> ObjectVolumeBoxPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectVolumeSphere : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_VOLUME_SPHERE; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectVolumeSphere> create(const Math::vec3 &radius);
	void setRadius(const Math::vec3 &radius);
	Math::vec3 getRadius() const;
};
typedef Ptr<ObjectVolumeSphere> ObjectVolumeSpherePtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectVolumeOmni : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_VOLUME_OMNI; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectVolumeOmni> create(float width, float height, float radius);
	void setSize(float width, float height);
	float getWidth() const;
	float getHeight() const;
	void setRadius(float radius);
	float getRadius() const;
	void setAttenuation(float attenuation);
	float getAttenuation() const;
};
typedef Ptr<ObjectVolumeOmni> ObjectVolumeOmniPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectVolumeProj : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_VOLUME_PROJ; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectVolumeProj> create(float width, float height, float fov);
	void setSize(float size);
	float getSize() const;
	void setRadius(float radius);
	float getRadius() const;
	void setFov(float fov);
	float getFov() const;
	void setStep(float step);
	float getStep() const;
	void setVelocity(float velocity);
	float getVelocity() const;
	void setVolumeRotation(float rotation);
	float getVolumeRotation() const;
};
typedef Ptr<ObjectVolumeProj> ObjectVolumeProjPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectGui : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_GUI; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }


	enum
	{
		MOUSE_STANDARD = 0,
		MOUSE_VIRTUAL,
	};
	static Ptr<ObjectGui> create(float width, float height, const char *name = 0);
	Ptr<Gui> getGui() const;
	void setBillboard(bool billboard);
	bool isBillboard() const;
	void setBackground(bool background);
	bool isBackground() const;
	void setDepthTest(bool test);
	bool isDepthTest() const;
	void setMouseShow(bool show);
	bool isMouseShow() const;
	void setMouseMode(int mode);
	int getMouseMode() const;
	void setMouse(const Math::Vec3 &p0, const Math::Vec3 &p1, int mouse_buttons, bool mouse_show);
	void setControlDistance(float distance);
	float getControlDistance() const;
	void setPolygonOffset(float offset);
	float getPolygonOffset() const;
	void setPhysicalSize(float width, float height);
	float getPhysicalWidth() const;
	float getPhysicalHeight() const;
	void setScreenSize(int width, int height);
	int getScreenWidth() const;
	int getScreenHeight() const;
};
typedef Ptr<ObjectGui> ObjectGuiPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectGuiMesh : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_GUI_MESH; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }


	enum
	{
		MOUSE_STANDARD = 0,
		MOUSE_VIRTUAL,
	};
	static Ptr<ObjectGuiMesh> create();
	static Ptr<ObjectGuiMesh> create(const char *mesh_path, const char *name = 0);
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
	Ptr<Gui> getGui() const;
	void setMouseShow(bool show);
	bool isMouseShow() const;
	void setBackground(bool background);
	bool isBackground() const;
	void setMouseMode(int mode);
	int getMouseMode() const;
	void setMouse(const Math::Vec3 &p0, const Math::Vec3 &p1, int mouse_buttons, bool mouse_show);
	void setControlDistance(float distance);
	float getControlDistance() const;
	void setScreenSize(int width, int height);
	int getScreenWidth() const;
	int getScreenHeight() const;
};
typedef Ptr<ObjectGuiMesh> ObjectGuiMeshPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectWaterMesh : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_WATER_MESH; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectWaterMesh> create();
	static Ptr<ObjectWaterMesh> create(const Ptr<Mesh> &mesh);
	static Ptr<ObjectWaterMesh> create(const char *path);
	int loadMesh(const char *path);
	int saveMesh(const char *path);
	int setMesh(const Ptr<Mesh> &mesh);
	int getMesh(Ptr<Mesh> &mesh) const;
	int setMeshPath(const char *path, bool force_load = false);
	const char *getMeshPath() const;
	void setFieldMask(int mask);
	int getFieldMask() const;
	void setWave(int num, const Math::vec4 &wave);
	Math::vec4 getWave(int num) const;
	void setWaveAngle(int num, float angle);
	float getWaveAngle(int num) const;
	void setWaveSpeed(int num, float speed);
	float getWaveSpeed(int num) const;
	void setWaveLength(int num, float length);
	float getWaveLength(int num) const;
	void setWaveHeight(int num, float height);
	float getWaveHeight(int num) const;
	float getHeight(const Math::Vec3 &position) const;
	Math::vec3 getNormal(const Math::Vec3 &position) const;
};
typedef Ptr<ObjectWaterMesh> ObjectWaterMeshPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectText : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_TEXT; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectText> create();
	static Ptr<ObjectText> create(const char *font_name);
	static Ptr<ObjectText> create(const char *font_name, const char *text);
	void setFontName(const char *name);
	const char *getFontName() const;
	void setFontRich(int rich);
	int getFontRich() const;
	void setFontSize(int size);
	int getFontSize() const;
	void setFontResolution(int resolution);
	int getFontResolution() const;
	void setFontHSpacing(int hspacing);
	int getFontHSpacing() const;
	void setFontVSpacing(int vspacing);
	int getFontVSpacing() const;
	void setFontOutline(int outline);
	int getFontOutline() const;
	void setDepthTest(int test);
	int getDepthTest() const;
	void setText(const char *text);
	const char *getText() const;
	void setTextColor(const Math::vec4 &color);
	Math::vec4 getTextColor() const;
	void setTextWrapWidth(float width);
	float getTextWrapWidth() const;
	float getTextWidth() const;
	float getTextHeight() const;
	float getTextAspect() const;
	int getTextNumLines() const;
};
typedef Ptr<ObjectText> ObjectTextPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectWaterGlobal : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_WATER_GLOBAL; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectWaterGlobal> create();
	void setActiveWater(bool water);
	bool isActiveWater() const;
	void setAnimationTime(float time);
	float getAnimationTime() const;
	float getMeanLevel() const;
	void setWindDirectionAngle(float angle);
	float getWindDirectionAngle() const;
	void setWindAffect(float affect);
	float getWindAffect() const;
	void setWavesSpeedScale(float scale);
	float getWavesSpeedScale() const;

	enum STEEPNESS_QUALITY
	{
		STEEPNESS_QUALITY_LOW,
		STEEPNESS_QUALITY_MEDIUM,
		STEEPNESS_QUALITY_HIGH,
		STEEPNESS_QUALITY_ULTRA,
		STEEPNESS_QUALITY_EXTREME,
	};
	float fetchHeight(const Math::Vec3 &position) const;
	Math::vec3 fetchNormal(const Math::Vec3 &position) const;
	void setFetchAmplitudeThreshold(float threshold);
	float getFetchAmplitudeThreshold() const;
	void setFetchSteepnessQuality(ObjectWaterGlobal::STEEPNESS_QUALITY quality);
	ObjectWaterGlobal::STEEPNESS_QUALITY getFetchSteepnessQuality() const;
	using Object::getIntersection;
	void setIntersectionPrecision(float precision);
	float getIntersectionPrecision() const;
	void setIntersectionAmplitudeThreshold(float threshold);
	float getIntersectionAmplitudeThreshold() const;
	void setIntersectionSteepnessQuality(ObjectWaterGlobal::STEEPNESS_QUALITY quality);
	ObjectWaterGlobal::STEEPNESS_QUALITY getIntersectionSteepnessQuality() const;
	int getPhysicsFieldMask() const;
	int getVisualFieldMask() const;
	void takeSyncData(const Ptr<Stream> &stream);
	void applySyncData(const Ptr<Stream> &stream);

	enum WAVES_MODE
	{
		WAVES_MODE_MANUAL,
		WAVES_MODE_LAYERS,
		WAVES_MODE_BEAUFORTS,
	};
	void setWavesMode(ObjectWaterGlobal::WAVES_MODE mode);
	ObjectWaterGlobal::WAVES_MODE getWavesMode() const;
	int addWave(float length, float amplitude, float steepness, float direction_angle, float phase);
	void removeWave(int index);
	int getNumWaves() const;
	float getWaveLength(int index) const;
	void setWaveLength(int index, float value);
	float getWaveAmplitude(int index) const;
	void setWaveAmplitude(int index, float value);
	float getWaveSteepness(int index) const;
	void setWaveSteepness(int index, float value);
	float getWaveDirectionAngle(int index) const;
	void setWaveDirectionAngle(int index, float value);
	float getWavePhaseOffset(int index) const;
	void setWavePhaseOffset(int index, float value);
	int addLayer();
	void removeLayer(int layer);
	int getNumLayers() const;
	void swapLayer(int num_0, int num_1);
	void setLayerEnabled(int layer, bool enabled);
	bool isLayerEnabled(int layer) const;
	int getLayerNumWaves(int layer) const;
	void setLayerNumWaves(int layer, int num);
	Math::vec2 getLayerLengthRange(int layer) const;
	void setLayerLengthRange(int layer, const Math::vec2 &value);
	Math::vec2 getLayerAmplitudeRange(int layer) const;
	void setLayerAmplitudeRange(int layer, const Math::vec2 &value);
	float getLayerSteepnessScale(int layer) const;
	void setLayerSteepnessScale(int layer, float value);
	float getLayerDirectionAngleVariance(int layer) const;
	void setLayerDirectionAngleVariance(int layer, float value);
	float getLayerWeight(int layer) const;
	void setLayerWeight(int layer, float value);
	const char *getLayerName(int layer) const;
	void setLayerName(int layer, const char *value);
	void setBeaufort(float beaufort);
	float getBeaufort() const;
	void setGeometryNormalIntensity(float intensity);
	float getGeometryNormalIntensity() const;
	void setTextureNormalBlur(float blur);
	float getTextureNormalBlur() const;
	void setTextureNormalIntensity(float intensity);
	float getTextureNormalIntensity() const;
	void setDetailTexturePath(const char *path);
	const char *getDetailTexturePath() const;
	void setDetail0UVSize(const Math::vec2 &size);
	Math::vec2 getDetail0UVSize() const;
	void setDetail0UVSpeed(const Math::vec2 &speed);
	Math::vec2 getDetail0UVSpeed() const;
	void setDetail0Intensity(float intensity);
	float getDetail0Intensity() const;
	void setDetail1UVSize(const Math::vec2 &size);
	Math::vec2 getDetail1UVSize() const;
	void setDetail1UVSpeed(const Math::vec2 &speed);
	Math::vec2 getDetail1UVSpeed() const;
	void setDetail1Intensity(float intensity);
	float getDetail1Intensity() const;
	void setDistantWavesTexturePath(const char *path);
	const char *getDistantWavesTexturePath() const;
	void setDistantWavesUVTransform(const Math::vec4 &transform);
	Math::vec4 getDistantWavesUVTransform() const;
	void setDistantWavesIntensity(float intensity);
	float getDistantWavesIntensity() const;
	void setDistantWavesBlendDistanceStart(float start);
	float getDistantWavesBlendDistanceStart() const;
	void setDistantWavesBlendDistanceEnd(float end);
	float getDistantWavesBlendDistanceEnd() const;
	void setDistantWavesBlendMin(float val);
	float getDistantWavesBlendMin() const;
	void setDistantWavesBlendMax(float val);
	float getDistantWavesBlendMax() const;
	void setFoamTexturePath(const char *path);
	const char *getFoamTexturePath() const;
	void setFoam0UVScale(float scale);
	float getFoam0UVScale() const;
	void setFoam0UVSpeed(float speed);
	float getFoam0UVSpeed() const;
	void setFoam1UVScale(float scale);
	float getFoam1UVScale() const;
	void setFoam1UVSpeed(float speed);
	float getFoam1UVSpeed() const;
	void setFoamPeakContrast(float contrast);
	float getFoamPeakContrast() const;
	void setFoamPeakIntensity(float intensity);
	float getFoamPeakIntensity() const;
	void setFoamWhitecapContrast(float contrast);
	float getFoamWhitecapContrast() const;
	void setFoamWhitecapIntensity(float intensity);
	float getFoamWhitecapIntensity() const;
	void setFoamWindContrast(float contrast);
	float getFoamWindContrast() const;
	void setFoamWindIntensity(float intensity);
	float getFoamWindIntensity() const;
	void setFoamContactIntensity(float intensity);
	float getFoamContactIntensity() const;
	void setFoamTextureAffect(float affect);
	float getFoamTextureAffect() const;
	void setSubsurfaceColor(const Math::vec4 &color);
	Math::vec4 getSubsurfaceColor() const;
	void setSubsurfaceAmbientIntensity(float intensity);
	float getSubsurfaceAmbientIntensity() const;
	void setSubsurfaceWaveIntensity(float intensity);
	float getSubsurfaceWaveIntensity() const;
	void setSubsurfaceWaveFoamIntensity(float intensity);
	float getSubsurfaceWaveFoamIntensity() const;
	void setSubsurfaceDecalsIntensity(float intensity);
	float getSubsurfaceDecalsIntensity() const;
	void setDepthLUTTexturePath(const char *path);
	const char *getDepthLUTTexturePath() const;
	void setUnderwaterFogColor(const Math::vec4 &color);
	Math::vec4 getUnderwaterFogColor() const;
	void setUnderwaterFogTransparency(float transparency);
	float getUnderwaterFogTransparency() const;
	void setUnderwaterFogDepth(float depth);
	float getUnderwaterFogDepth() const;
	void setUnderwaterFogOffset(float offset);
	float getUnderwaterFogOffset() const;
	void setUnderwaterFogEnvironmentInfluence(float influence);
	float getUnderwaterFogEnvironmentInfluence() const;
	void setUnderwaterFogSunInfluence(float influence);
	float getUnderwaterFogSunInfluence() const;
	void setUnderwaterShaftIntensity(float intensity);
	float getUnderwaterShaftIntensity() const;
	void setWaterlineSize(float size);
	float getWaterlineSize() const;
	void setUnderwaterDOF(bool underwaterdof);
	bool isUnderwaterDOF() const;
	void setUnderwaterDofDistance(float distance);
	float getUnderwaterDofDistance() const;
	void setPlanarReflection(bool reflection);
	bool isPlanarReflection() const;

	enum PLANAR_REFLECTION_SIZE
	{
		PLANAR_REFLECTION_SIZE_RESOLUTION_128 = 0,
		PLANAR_REFLECTION_SIZE_RESOLUTION_256,
		PLANAR_REFLECTION_SIZE_RESOLUTION_512,
		PLANAR_REFLECTION_SIZE_RESOLUTION_1024,
		PLANAR_REFLECTION_SIZE_RESOLUTION_2048,
		PLANAR_REFLECTION_SIZE_RESOLUTION_4096,
		PLANAR_REFLECTION_SIZE_RESOLUTION_HEIGHT_QUART,
		PLANAR_REFLECTION_SIZE_RESOLUTION_HEIGHT_HALF,
		PLANAR_REFLECTION_SIZE_RESOLUTION_HEIGHT,
	};
	void setPlanarReflectionMapSizeType(ObjectWaterGlobal::PLANAR_REFLECTION_SIZE type);
	ObjectWaterGlobal::PLANAR_REFLECTION_SIZE getPlanarReflectionMapSizeType() const;
	void setPlanarReflectionDistance(float distance);
	float getPlanarReflectionDistance() const;
	void setPlanarReflectionPivotOffset(const Math::vec3 &offset);
	Math::vec3 getPlanarReflectionPivotOffset() const;
	void setPlanarReflectionViewportMask(int mask);
	int getPlanarReflectionViewportMask() const;
	void setReflectionRoughness(float roughness);
	float getReflectionRoughness() const;
	void setReflectionOcclusion(float occlusion);
	float getReflectionOcclusion() const;
	void setReflectionOcclusionSlope(float slope);
	float getReflectionOcclusionSlope() const;
	void setCaustics(bool caustics);
	bool isCaustics() const;
	void setCausticsDistortion(bool distortion);
	bool isCausticsDistortion() const;
	void setCausticsTexturePath(const char *path);
	const char *getCausticsTexturePath() const;
	void setCausticUVTransform(const Math::vec4 &transform);
	Math::vec4 getCausticUVTransform() const;
	void setCausticDistanceFade(float fade);
	float getCausticDistanceFade() const;
	void setCausticAnimationSpeed(float speed);
	float getCausticAnimationSpeed() const;
	void setCausticBrightness(float brightness);
	float getCausticBrightness() const;
	void setFieldHeightEnabled(bool enabled);
	bool isFieldHeightEnabled() const;
	void setFieldHeightFoamContrast(float contrast);
	float getFieldHeightFoamContrast() const;
	void setFieldHeightFoamIntensity(float intensity);
	float getFieldHeightFoamIntensity() const;
	void setFieldHeightSteepness(float steepness);
	float getFieldHeightSteepness() const;
	void setFieldShorelineEnabled(bool enabled);
	bool isFieldShorelineEnabled() const;
	void setFieldShorelineHighPrecision(bool precision);
	bool isFieldShorelineHighPrecision() const;
	void setFieldShorelineNormal(bool normal);
	bool isFieldShorelineNormal() const;
	void setFieldShorelineGeometry(bool geometry);
	bool isFieldShorelineGeometry() const;
	void setFieldShorelineFoam(bool foam);
	bool isFieldShorelineFoam() const;
	void setFieldShorelineLUTTexturePath(const char *path);
	const char *getFieldShorelineLUTTexturePath() const;
	void setFieldShorelineWaveSpeed(float speed);
	float getFieldShorelineWaveSpeed() const;
	void setFieldShorelineWaveTiling(float tiling);
	float getFieldShorelineWaveTiling() const;
	void setFieldShorelineWaveHeight(float height);
	float getFieldShorelineWaveHeight() const;
	void setFieldShorelineWaveFalloff(float falloff);
	float getFieldShorelineWaveFalloff() const;
	void setFieldShorelineWaveExponent(float exponent);
	float getFieldShorelineWaveExponent() const;
	void setFieldShorelineWaveFrontExponent(float exponent);
	float getFieldShorelineWaveFrontExponent() const;
	void setFieldShorelineFoamStretching(float stretching);
	float getFieldShorelineFoamStretching() const;
	void setFieldShorelineFoamIntensity(float intensity);
	float getFieldShorelineFoamIntensity() const;
	void setFieldShorelineFoamExponent(float exponent);
	float getFieldShorelineFoamExponent() const;
	void setFieldShorelineMaskTiling(float tiling);
	float getFieldShorelineMaskTiling() const;
	void setFieldShorelineBeaufortFalloff(float falloff);
	float getFieldShorelineBeaufortFalloff() const;
	void setShorelineWetnessIntensity(float intensity);
	float getShorelineWetnessIntensity() const;
	void setShorelineWetnessDistance(float distance);
	float getShorelineWetnessDistance() const;
	void setShorelineWetnessOffset(float offset);
	float getShorelineWetnessOffset() const;
	void setAuxiliary(bool auxiliary);
	bool isAuxiliary() const;
	void setAuxiliaryColor(const Math::vec4 &color);
	Math::vec4 getAuxiliaryColor() const;
	void setRefractionScale(float scale);
	float getRefractionScale() const;
	void setDecalsDistortion(float distortion);
	float getDecalsDistortion() const;
	void setDecalsSoftInteraction(float interaction);
	float getDecalsSoftInteraction() const;
	void setSoftInteraction(float interaction);
	float getSoftInteraction() const;
	void setFieldSpacerEnabled(bool enabled);
	bool isFieldSpacerEnabled() const;
};
typedef Ptr<ObjectWaterGlobal> ObjectWaterGlobalPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectCloudLayer : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_CLOUD_LAYER; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectCloudLayer> create();
	void setIntersectionThreshold(float threshold);
	float getIntersectionThreshold() const;
	void setIntersectionAccuracy(float accuracy);
	float getIntersectionAccuracy() const;
	void setAnimationCoverageOffset(const Math::vec4 &offset);
	Math::vec4 getAnimationCoverageOffset() const;
	void setAnimationNoiseOffset(const Math::vec4 &offset);
	Math::vec4 getAnimationNoiseOffset() const;
	void refreshCloudsRegionMask();
	float getDensity(const Math::Vec3 &world_point) const;
};
typedef Ptr<ObjectCloudLayer> ObjectCloudLayerPtr;

class ObjectExternBase;
//////////////////////////////////////////////////////////////////////////

class UNIGINE_API ObjectExtern : public Object
{
public:
	static Node::TYPE type() { return Node::OBJECT_EXTERN; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<ObjectExtern> create(int class_id);
	ObjectExternBase *getObjectExtern() const;
	int getClassID() const;
	void setMaterialNodeType(int type);
	int getMaterialNodeType() const;
};
typedef Ptr<ObjectExtern> ObjectExternPtr;


class UNIGINE_API  ObjectExternBase : public virtual Base
{
public:
	ObjectExternBase();
	ObjectExternBase(void *object);
	virtual ~ObjectExternBase();
	virtual int getClassID() = 0;
	Ptr<Node> getNode() const;
	Ptr<Object> getObject() const;
	Ptr<ObjectExtern> getObjectExtern() const;
	typedef ObjectExternBase *(*ConstructorFunc)(void *object);
	static void addClassID(int class_id, ConstructorFunc func);
	template <class Type> static void addClassID(int class_id) { addClassID(class_id, constructor<Type>); }
	virtual int getNumSurfaces() = 0;
	virtual const char *getSurfaceName(int surface) = 0;
	virtual int findSurface(const char *name);
	void updateSurfaces() const;
	void resizeSurfaces() const;
	virtual void updateEnabled(int surface);
	virtual void updateEnabled();
	virtual int getResource(int surface);
	virtual int getOrder(const Math::Vec3 &camera, int surface);
	virtual int getSequence(const Math::Vec3 &camera, int surface);
	virtual float getTransparentDistance(const Math::Vec3 &camera, int surface);
	virtual bool hasLods();
	virtual int getCollision(const Math::BoundBox &bb, Vector<int> &surfaces);
	virtual int getCollision(const Math::Vec3 &p0, const Math::Vec3 &p1, Vector<int> &surfaces);
	virtual int getIntersection(const Math::Vec3 &p0, const Math::Vec3 &p1, Math::Vec3 *ret_point, Math::vec3 *ret_normal, Math::vec4 *ret_texcoord, int *ret_index, int *ret_instance, int surface);
	virtual int getRandomPoint(Math::vec3 &ret_point, Math::vec3 &ret_normal, Math::vec3 &ret_velocity, int surface);
	virtual int getNumTriangles(int surface);
	virtual const Math::BoundBox &getBoundBox(int surface) = 0;
	virtual const Math::BoundSphere &getBoundSphere(int surface) = 0;
	virtual bool hasCreate();
	virtual void create(int surface);
	virtual bool hasRender();
	virtual void render(Render::PASS pass, int surface);
	virtual bool hasShadow();
	virtual void renderShadow(Render::PASS pass, int surface);
	virtual void updateTransform();
	virtual void update(float ifps);
	virtual void flush(float) final {} // This method was given a more meaningful name "preRender", please override it instead.
	virtual void preRender(float ifps);
	virtual const Math::BoundBox &getBoundBox() = 0;
	virtual const Math::BoundSphere &getBoundSphere() = 0;
	virtual void renderHandler();
	virtual void renderVisualizer();
	virtual void copy(ObjectExternBase *object, int is_root);
	virtual void swap(ObjectExternBase *object);
	virtual int loadWorld(const Ptr<Xml> &xml);
	virtual int saveWorld(const Ptr<Xml> &xml);
	virtual int saveState(const Ptr<Stream> &stream);
	virtual int restoreState(const Ptr<Stream> &stream);
	virtual void setUpdateDistanceLimit(float distance);
	virtual float getUpdateDistanceLimit();
	virtual void setForceUpdate(bool enabled);
	virtual bool isForceUpdate();
	static void savePointer(const StreamPtr &stream, ObjectExternBase *object);
	static ObjectExternBase *restorePointer(const StreamPtr &stream);

private:
	template <class Type> static ObjectExternBase *constructor(void *object) { return new Type(object); }
	struct ObjectExternData;
	ObjectExternData *data;
};
typedef Ptr<ObjectExternBase> ObjectExternBasePtr;

} // namespace Unigine
