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

#include "UniginePtr.h"
#include "UnigineMathLib.h"
#include "UnigineAnimationParameters.h"
#include "UnigineNode.h"
#include "UnigineMaterial.h"
#include "UnigineXml.h"
#include "UnigineStreams.h"
#include "UnigineJson.h"
#include "UnigineWidgets.h"

namespace Unigine
{


class UNIGINE_API AnimationCurve : public APIInterface
{
public:
	static bool convertible(AnimationCurve *obj) { return obj != nullptr; }

	enum TYPE
	{
		ANIMATION_CURVE = 0,
		ANIMATION_CURVE_INT,
		ANIMATION_CURVE_FLOAT,
		ANIMATION_CURVE_DOUBLE,
		ANIMATION_CURVE_BOOL,
		ANIMATION_CURVE_SCALAR,
		ANIMATION_CURVE_QUAT,
		ANIMATION_CURVE_STRING,
		ANIMATION_CURVE_UGUID,
	};

	enum KEY_TYPE
	{
		KEY_TYPE_CONSTANT = 0,
		KEY_TYPE_LINEAR,
		KEY_TYPE_SMOOTH,
		KEY_TYPE_BREAK,
		NUM_KEY_TYPES,
	};
	AnimationCurve::TYPE getType() const;
	const char *getTypeName() const;
};
typedef Ptr<AnimationCurve> AnimationCurvePtr;


class UNIGINE_API AnimationCurveInt : public AnimationCurve
{
public:
	static bool convertible(AnimationCurve *obj) { return obj && obj->getType() == AnimationCurve::ANIMATION_CURVE_INT; }
	static Ptr<AnimationCurveInt> create();
	void copy(const Ptr<AnimationCurveInt> &curve);
	int getDefaultKeyValue() const;
	int addKey(float time, int value);
	int addKey(float time, int value, AnimationCurve::KEY_TYPE type);
	int addKey(float time, int value, AnimationCurve::KEY_TYPE type, const Math::vec2 &left_tangent, const Math::vec2 &right_tangent);
	void removeKey(int index);
	int moveKey(int index, float new_time);
	int getNumKeys() const;
	void setKeyType(int index, AnimationCurve::KEY_TYPE type);
	AnimationCurve::KEY_TYPE getKeyType(int index) const;
	float getKeyTime(int index) const;
	void setKeyValue(int index, int value);
	int getKeyValue(int index) const;
	void setKeyLeftTangent(int index, const Math::vec2 &left_tangent);
	Math::vec2 getKeyLeftTangent(int index) const;
	void setKeyRightTangent(int index, const Math::vec2 &right_tangent);
	Math::vec2 getKeyRightTangent(int index) const;
	void setTypeOfAllKeys(AnimationCurve::KEY_TYPE type);
	float getMinTime() const;
	float getMaxTime() const;
	void clear();
	int getValueByTime(float time);
	int getValueByNormalizedTime(float normalized_time);
	void save(const Ptr<Blob> &blob) const;
	void load(const Ptr<Blob> &blob);
};
typedef Ptr<AnimationCurveInt> AnimationCurveIntPtr;


class UNIGINE_API AnimationCurveFloat : public AnimationCurve
{
public:
	static bool convertible(AnimationCurve *obj) { return obj && obj->getType() == AnimationCurve::ANIMATION_CURVE_FLOAT; }
	static Ptr<AnimationCurveFloat> create();
	void copy(const Ptr<AnimationCurveFloat> &curve);
	float getDefaultKeyValue() const;
	int addKey(float time, float value);
	int addKey(float time, float value, AnimationCurve::KEY_TYPE type);
	int addKey(float time, float value, AnimationCurve::KEY_TYPE type, const Math::vec2 &left_tangent, const Math::vec2 &right_tangent);
	void removeKey(int index);
	int moveKey(int index, float new_time);
	int getNumKeys() const;
	void setKeyType(int index, AnimationCurve::KEY_TYPE type);
	AnimationCurve::KEY_TYPE getKeyType(int index) const;
	float getKeyTime(int index) const;
	void setKeyValue(int index, float value);
	float getKeyValue(int index) const;
	void setKeyLeftTangent(int index, const Math::vec2 &left_tangent);
	Math::vec2 getKeyLeftTangent(int index) const;
	void setKeyRightTangent(int index, const Math::vec2 &right_tangent);
	Math::vec2 getKeyRightTangent(int index) const;
	void setTypeOfAllKeys(AnimationCurve::KEY_TYPE type);
	float getMinTime() const;
	float getMaxTime() const;
	void clear();
	float getValueByTime(float time);
	float getValueByNormalizedTime(float normalized_time);
	void save(const Ptr<Blob> &blob) const;
	void load(const Ptr<Blob> &blob);
};
typedef Ptr<AnimationCurveFloat> AnimationCurveFloatPtr;


class UNIGINE_API AnimationCurveDouble : public AnimationCurve
{
public:
	static bool convertible(AnimationCurve *obj) { return obj && obj->getType() == AnimationCurve::ANIMATION_CURVE_DOUBLE; }
	static Ptr<AnimationCurveDouble> create();
	void copy(const Ptr<AnimationCurveDouble> &curve);
	double getDefaultKeyValue() const;
	int addKey(float time, double value);
	int addKey(float time, double value, AnimationCurve::KEY_TYPE type);
	int addKey(float time, double value, AnimationCurve::KEY_TYPE type, const Math::vec2 &left_tangent, const Math::vec2 &right_tangent);
	void removeKey(int index);
	int moveKey(int index, float new_time);
	int getNumKeys() const;
	void setKeyType(int index, AnimationCurve::KEY_TYPE type);
	AnimationCurve::KEY_TYPE getKeyType(int index) const;
	float getKeyTime(int index) const;
	void setKeyValue(int index, double value);
	double getKeyValue(int index) const;
	void setKeyLeftTangent(int index, const Math::vec2 &left_tangent);
	Math::vec2 getKeyLeftTangent(int index) const;
	void setKeyRightTangent(int index, const Math::vec2 &right_tangent);
	Math::vec2 getKeyRightTangent(int index) const;
	void setTypeOfAllKeys(AnimationCurve::KEY_TYPE type);
	float getMinTime() const;
	float getMaxTime() const;
	void clear();
	double getValueByTime(float time);
	double getValueByNormalizedTime(float normalized_time);
	void save(const Ptr<Blob> &blob) const;
	void load(const Ptr<Blob> &blob);
};
typedef Ptr<AnimationCurveDouble> AnimationCurveDoublePtr;


class UNIGINE_API AnimationCurveBool : public AnimationCurve
{
public:
	static bool convertible(AnimationCurve *obj) { return obj && obj->getType() == AnimationCurve::ANIMATION_CURVE_BOOL; }
	static Ptr<AnimationCurveBool> create();
	void copy(const Ptr<AnimationCurveBool> &curve);
	bool getDefaultKeyValue() const;
	int addKey(float time, bool value);
	int addKey(float time, bool value, AnimationCurve::KEY_TYPE type);
	int addKey(float time, bool value, AnimationCurve::KEY_TYPE type, const Math::vec2 &left_tangent, const Math::vec2 &right_tangent);
	void removeKey(int index);
	int moveKey(int index, float new_time);
	int getNumKeys() const;
	void setKeyType(int index, AnimationCurve::KEY_TYPE type);
	AnimationCurve::KEY_TYPE getKeyType(int index) const;
	float getKeyTime(int index) const;
	void setKeyValue(int index, bool value);
	bool getKeyValue(int index) const;
	void setKeyLeftTangent(int index, const Math::vec2 &left_tangent);
	Math::vec2 getKeyLeftTangent(int index) const;
	void setKeyRightTangent(int index, const Math::vec2 &right_tangent);
	Math::vec2 getKeyRightTangent(int index) const;
	void setTypeOfAllKeys(AnimationCurve::KEY_TYPE type);
	float getMinTime() const;
	float getMaxTime() const;
	void clear();
	bool getValueByTime(float time);
	bool getValueByNormalizedTime(float normalized_time);
	void save(const Ptr<Blob> &blob) const;
	void load(const Ptr<Blob> &blob);
};
typedef Ptr<AnimationCurveBool> AnimationCurveBoolPtr;


class UNIGINE_API AnimationCurveScalar : public AnimationCurve
{
public:
	static bool convertible(AnimationCurve *obj) { return obj && obj->getType() == AnimationCurve::ANIMATION_CURVE_SCALAR; }
	static Ptr<AnimationCurveScalar> create();
	void copy(const Ptr<AnimationCurveScalar> &curve);
	Math::Scalar getDefaultKeyValue() const;
	int addKey(float time, Math::Scalar value);
	int addKey(float time, Math::Scalar value, AnimationCurve::KEY_TYPE type);
	int addKey(float time, Math::Scalar value, AnimationCurve::KEY_TYPE type, const Math::vec2 &left_tangent, const Math::vec2 &right_tangent);
	void removeKey(int index);
	int moveKey(int index, float new_time);
	int getNumKeys() const;
	void setKeyType(int index, AnimationCurve::KEY_TYPE type);
	AnimationCurve::KEY_TYPE getKeyType(int index) const;
	float getKeyTime(int index) const;
	void setKeyValue(int index, Math::Scalar value);
	Math::Scalar getKeyValue(int index) const;
	void setKeyLeftTangent(int index, const Math::vec2 &left_tangent);
	Math::vec2 getKeyLeftTangent(int index) const;
	void setKeyRightTangent(int index, const Math::vec2 &right_tangent);
	Math::vec2 getKeyRightTangent(int index) const;
	void setTypeOfAllKeys(AnimationCurve::KEY_TYPE type);
	float getMinTime() const;
	float getMaxTime() const;
	void clear();
	Math::Scalar getValueByTime(float time);
	Math::Scalar getValueByNormalizedTime(float time);
	void save(const Ptr<Blob> &blob) const;
	void load(const Ptr<Blob> &blob);
};
typedef Ptr<AnimationCurveScalar> AnimationCurveScalarPtr;


class UNIGINE_API AnimationCurveQuat : public AnimationCurve
{
public:
	static bool convertible(AnimationCurve *obj) { return obj && obj->getType() == AnimationCurve::ANIMATION_CURVE_QUAT; }
	static Ptr<AnimationCurveQuat> create();
	void copy(const Ptr<AnimationCurveQuat> &curve);
	Math::quat getDefaultKeyValue() const;
	int addKey(float time, const Math::quat &value);
	void removeKey(int index);
	int moveKey(int index, float new_time);
	int getNumKeys() const;
	float getKeyTime(int index) const;
	void setKeyValue(int index, const Math::quat &value);
	Math::quat getKeyValue(int index) const;
	float getMinTime() const;
	float getMaxTime() const;
	void clear();
	Math::quat getValueByTime(float time);
	Math::quat getValueByNormalizedTime(float time);
	void save(const Ptr<Blob> &blob) const;
	void load(const Ptr<Blob> &blob);
};
typedef Ptr<AnimationCurveQuat> AnimationCurveQuatPtr;


class UNIGINE_API AnimationCurveString : public AnimationCurve
{
public:
	static bool convertible(AnimationCurve *obj) { return obj && obj->getType() == AnimationCurve::ANIMATION_CURVE_STRING; }
	static Ptr<AnimationCurveString> create();
	void copy(const Ptr<AnimationCurveString> &curve);
	String getDefaultKeyValue() const;
	int addKey(float time, const char *value);
	void removeKey(int index);
	int moveKey(int index, float new_time);
	int getNumKeys() const;
	float getKeyTime(int index) const;
	void setKeyValue(int index, const char *value);
	const char *getKeyValue(int index) const;
	float getMinTime() const;
	float getMaxTime() const;
	void clear();
	String getValueByTime(float time);
	String getValueByNormalizedTime(float time);
	void save(const Ptr<Blob> &blob) const;
	void load(const Ptr<Blob> &blob);
};
typedef Ptr<AnimationCurveString> AnimationCurveStringPtr;


class UNIGINE_API AnimationCurveUGUID : public AnimationCurve
{
public:
	static bool convertible(AnimationCurve *obj) { return obj && obj->getType() == AnimationCurve::ANIMATION_CURVE_UGUID; }
	static Ptr<AnimationCurveUGUID> create();
	void copy(const Ptr<AnimationCurveUGUID> &curve);
	UGUID getDefaultKeyValue() const;
	int addKey(float time, const UGUID &value);
	void removeKey(int index);
	int moveKey(int index, float new_time);
	int getNumKeys() const;
	float getKeyTime(int index) const;
	void setKeyValue(int index, const UGUID &value);
	UGUID getKeyValue(int index) const;
	float getMinTime() const;
	float getMaxTime() const;
	void clear();
	UGUID getValueByTime(float time);
	UGUID getValueByNormalizedTime(float time);
	void save(const Ptr<Blob> &blob) const;
	void load(const Ptr<Blob> &blob);
};
typedef Ptr<AnimationCurveUGUID> AnimationCurveUGUIDPtr;

class AnimationModifierInfo;
class AnimationTrack;

class UNIGINE_API AnimationModifier : public APIInterface
{
public:
	static bool convertible(AnimationModifier *obj) { return obj != nullptr; }

	enum TYPE
	{
		ANIMATION_MODIFIER = 0,
		ANIMATION_MODIFIER_INT,
		ANIMATION_MODIFIER_BOOL,
		ANIMATION_MODIFIER_QUAT,
		ANIMATION_MODIFIER_SCALAR,
		ANIMATION_MODIFIER_FLOAT,
		ANIMATION_MODIFIER_DOUBLE,
		ANIMATION_MODIFIER_STRING,
		ANIMATION_MODIFIER_UGUID,
		ANIMATION_MODIFIER_IVEC2,
		ANIMATION_MODIFIER_IVEC3,
		ANIMATION_MODIFIER_IVEC4,
		ANIMATION_MODIFIER_VEC2,
		ANIMATION_MODIFIER_FVEC2,
		ANIMATION_MODIFIER_DVEC2,
		ANIMATION_MODIFIER_VEC3,
		ANIMATION_MODIFIER_FVEC3,
		ANIMATION_MODIFIER_DVEC3,
		ANIMATION_MODIFIER_VEC4,
		ANIMATION_MODIFIER_FVEC4,
		ANIMATION_MODIFIER_DVEC4,
		ANIMATION_MODIFIER_MAT4,
		ANIMATION_MODIFIER_NODE,
		ANIMATION_MODIFIER_BONES,
		ANIMATION_MODIFIER_TRACK,
	};
	Ptr<AnimationModifierInfo> getInfo() const;
	AnimationModifier::TYPE getType() const;
	const char *getTypeName() const;
	AnimParams::PARAM getParam() const;
	int getParamIndex() const;
	const char *getParamName() const;
	void setObjID(int objid);
	int getObjID() const;
	float getMinTime() const;
	float getMaxTime() const;
	float getDuration() const;
	void save(const Ptr<Blob> &blob) const;
	void load(const Ptr<Blob> &blob);
};
typedef Ptr<AnimationModifier> AnimationModifierPtr;


class UNIGINE_API AnimationModifierInfo : public APIInterface
{
public:
	AnimationModifier::TYPE getType() const;
	void setParam(AnimParams::PARAM param);
	AnimParams::PARAM getParam() const;
	void setParamIndex(int index);
	int getParamIndex() const;
	void setParamName(const char *name);
	const char *getParamName() const;
	void setObjID(int objid);
	int getObjID() const;
};
typedef Ptr<AnimationModifierInfo> AnimationModifierInfoPtr;


class UNIGINE_API AnimationModifierInt : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_INT; }
	static Ptr<AnimationModifierInt> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierInt> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierInt> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierInt> create(const char *param);
	static Ptr<AnimationModifierInt> create(const char *param, int param_index);
	static Ptr<AnimationModifierInt> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierInt> &modifier);
	int getDefaultValue() const;
	int getValueByTime(float time);
	int getValueByNormalizedTime(float normalized_time);
	void addValue(float time, int value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurve(const Ptr<AnimationCurveInt> &curve);
	Ptr<AnimationCurveInt> getCurve() const;
};
typedef Ptr<AnimationModifierInt> AnimationModifierIntPtr;


class UNIGINE_API AnimationModifierBool : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_BOOL; }
	static Ptr<AnimationModifierBool> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierBool> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierBool> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierBool> create(const char *param);
	static Ptr<AnimationModifierBool> create(const char *param, int param_index);
	static Ptr<AnimationModifierBool> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierBool> &modifier);
	bool getDefaultValue() const;
	bool getValueByTime(float time);
	bool getValueByNormalizedTime(float normalized_time);
	void addValue(float time, bool value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurve(const Ptr<AnimationCurveBool> &curve);
	Ptr<AnimationCurveBool> getCurve() const;
};
typedef Ptr<AnimationModifierBool> AnimationModifierBoolPtr;


class UNIGINE_API AnimationModifierQuat : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_QUAT; }

	enum MODE
	{
		MODE_QUAT = 0,
		MODE_ANGLES_XYZ,
		MODE_ANGLES_ZYX,
	};
	static Ptr<AnimationModifierQuat> create(AnimationModifierQuat::MODE mode, AnimParams::PARAM param);
	static Ptr<AnimationModifierQuat> create(AnimationModifierQuat::MODE mode, AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierQuat> create(AnimationModifierQuat::MODE mode, AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierQuat> create(AnimationModifierQuat::MODE mode, const char *param);
	static Ptr<AnimationModifierQuat> create(AnimationModifierQuat::MODE mode, const char *param, int param_index);
	static Ptr<AnimationModifierQuat> create(AnimationModifierQuat::MODE mode, const char *param, const char *param_name);
	AnimationModifierQuat::MODE getMode() const;
	void copy(const Ptr<AnimationModifierQuat> &modifier);
	Math::quat getDefaultValue() const;
	Math::quat getValueByTime(float time);
	Math::quat getValueByNormalizedTime(float normalized_time);
	void addQuatValue(float time, const Math::quat &value);
	void addAnglesValue(float time, const Math::vec3 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setQuatCurve(const Ptr<AnimationCurveQuat> &curve);
	Ptr<AnimationCurveQuat> getQuatCurve() const;
	void setCurveX(const Ptr<AnimationCurveFloat> &curvex);
	Ptr<AnimationCurveFloat> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveFloat> &curvey);
	Ptr<AnimationCurveFloat> getCurveY() const;
	void setCurveZ(const Ptr<AnimationCurveFloat> &curvez);
	Ptr<AnimationCurveFloat> getCurveZ() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierQuat> AnimationModifierQuatPtr;


class UNIGINE_API AnimationModifierScalar : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_SCALAR; }
	static Ptr<AnimationModifierScalar> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierScalar> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierScalar> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierScalar> create(const char *param);
	static Ptr<AnimationModifierScalar> create(const char *param, int param_index);
	static Ptr<AnimationModifierScalar> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierScalar> &modifier);
	Math::Scalar getDefaultValue() const;
	Math::Scalar getValueByTime(float time);
	Math::Scalar getValueByNormalizedTime(float normalized_time);
	void addValue(float time, Math::Scalar value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurve(const Ptr<AnimationCurveScalar> &curve);
	Ptr<AnimationCurveScalar> getCurve() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierScalar> AnimationModifierScalarPtr;


class UNIGINE_API AnimationModifierFloat : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_FLOAT; }
	static Ptr<AnimationModifierFloat> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierFloat> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierFloat> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierFloat> create(const char *param);
	static Ptr<AnimationModifierFloat> create(const char *param, int param_index);
	static Ptr<AnimationModifierFloat> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierFloat> &modifier);
	float getDefaultValue() const;
	float getValueByTime(float time);
	float getValueByNormalizedTime(float normalized_time);
	void addValue(float time, float value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurve(const Ptr<AnimationCurveFloat> &curve);
	Ptr<AnimationCurveFloat> getCurve() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierFloat> AnimationModifierFloatPtr;


class UNIGINE_API AnimationModifierDouble : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_DOUBLE; }
	static Ptr<AnimationModifierDouble> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierDouble> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierDouble> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierDouble> create(const char *param);
	static Ptr<AnimationModifierDouble> create(const char *param, int param_index);
	static Ptr<AnimationModifierDouble> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierDouble> &modifier);
	double getDefaultValue() const;
	double getValueByTime(float time);
	double getValueByNormalizedTime(float normalized_time);
	void addValue(float time, double value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurve(const Ptr<AnimationCurveDouble> &curve);
	Ptr<AnimationCurveDouble> getCurve() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierDouble> AnimationModifierDoublePtr;


class UNIGINE_API AnimationModifierString : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_STRING; }
	static Ptr<AnimationModifierString> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierString> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierString> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierString> create(const char *param);
	static Ptr<AnimationModifierString> create(const char *param, int param_index);
	static Ptr<AnimationModifierString> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierString> &modifier);
	String getDefaultValue() const;
	String getValueByTime(float time);
	String getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const char *value);
	void setCurve(const Ptr<AnimationCurveString> &curve);
	Ptr<AnimationCurveString> getCurve() const;
};
typedef Ptr<AnimationModifierString> AnimationModifierStringPtr;


class UNIGINE_API AnimationModifierUGUID : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_UGUID; }
	static Ptr<AnimationModifierUGUID> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierUGUID> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierUGUID> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierUGUID> create(const char *param);
	static Ptr<AnimationModifierUGUID> create(const char *param, int param_index);
	static Ptr<AnimationModifierUGUID> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierUGUID> &modifier);
	UGUID getDefaultValue() const;
	UGUID getValueByTime(float time);
	UGUID getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const UGUID &value);
	void setCurve(const Ptr<AnimationCurveUGUID> &curve);
	Ptr<AnimationCurveUGUID> getCurve() const;
};
typedef Ptr<AnimationModifierUGUID> AnimationModifierUGUIDPtr;


class UNIGINE_API AnimationModifierIVec2 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_IVEC2; }
	static Ptr<AnimationModifierIVec2> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierIVec2> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierIVec2> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierIVec2> create(const char *param);
	static Ptr<AnimationModifierIVec2> create(const char *param, int param_index);
	static Ptr<AnimationModifierIVec2> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierIVec2> &modifier);
	Math::ivec2 getDefaultValue() const;
	Math::ivec2 getValueByTime(float time);
	Math::ivec2 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::ivec2 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveInt> &curvex);
	Ptr<AnimationCurveInt> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveInt> &curvey);
	Ptr<AnimationCurveInt> getCurveY() const;
};
typedef Ptr<AnimationModifierIVec2> AnimationModifierIVec2Ptr;


class UNIGINE_API AnimationModifierIVec3 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_IVEC3; }
	static Ptr<AnimationModifierIVec3> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierIVec3> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierIVec3> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierIVec3> create(const char *param);
	static Ptr<AnimationModifierIVec3> create(const char *param, int param_index);
	static Ptr<AnimationModifierIVec3> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierIVec3> &modifier);
	Math::ivec3 getDefaultValue() const;
	Math::ivec3 getValueByTime(float time);
	Math::ivec3 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::ivec3 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveInt> &curvex);
	Ptr<AnimationCurveInt> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveInt> &curvey);
	Ptr<AnimationCurveInt> getCurveY() const;
	void setCurveZ(const Ptr<AnimationCurveInt> &curvez);
	Ptr<AnimationCurveInt> getCurveZ() const;
};
typedef Ptr<AnimationModifierIVec3> AnimationModifierIVec3Ptr;


class UNIGINE_API AnimationModifierIVec4 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_IVEC4; }
	static Ptr<AnimationModifierIVec4> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierIVec4> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierIVec4> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierIVec4> create(const char *param);
	static Ptr<AnimationModifierIVec4> create(const char *param, int param_index);
	static Ptr<AnimationModifierIVec4> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierIVec4> &modifier);
	Math::ivec4 getDefaultValue() const;
	Math::ivec4 getValueByTime(float time);
	Math::ivec4 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::ivec4 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveInt> &curvex);
	Ptr<AnimationCurveInt> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveInt> &curvey);
	Ptr<AnimationCurveInt> getCurveY() const;
	void setCurveZ(const Ptr<AnimationCurveInt> &curvez);
	Ptr<AnimationCurveInt> getCurveZ() const;
	void setCurveW(const Ptr<AnimationCurveInt> &curvew);
	Ptr<AnimationCurveInt> getCurveW() const;
};
typedef Ptr<AnimationModifierIVec4> AnimationModifierIVec4Ptr;


class UNIGINE_API AnimationModifierVec2 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_VEC2; }
	static Ptr<AnimationModifierVec2> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierVec2> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierVec2> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierVec2> create(const char *param);
	static Ptr<AnimationModifierVec2> create(const char *param, int param_index);
	static Ptr<AnimationModifierVec2> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierVec2> &modifier);
	Math::Vec2 getDefaultValue() const;
	Math::Vec2 getValueByTime(float time);
	Math::Vec2 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::Vec2 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveScalar> &curvex);
	Ptr<AnimationCurveScalar> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveScalar> &curvey);
	Ptr<AnimationCurveScalar> getCurveY() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierVec2> AnimationModifierVec2Ptr;


class UNIGINE_API AnimationModifierFVec2 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_FVEC2; }
	static Ptr<AnimationModifierFVec2> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierFVec2> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierFVec2> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierFVec2> create(const char *param);
	static Ptr<AnimationModifierFVec2> create(const char *param, int param_index);
	static Ptr<AnimationModifierFVec2> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierFVec2> &modifier);
	Math::vec2 getDefaultValue() const;
	Math::vec2 getValueByTime(float time);
	Math::vec2 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::vec2 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveFloat> &curvex);
	Ptr<AnimationCurveFloat> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveFloat> &curvey);
	Ptr<AnimationCurveFloat> getCurveY() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierFVec2> AnimationModifierFVec2Ptr;


class UNIGINE_API AnimationModifierDVec2 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_DVEC2; }
	static Ptr<AnimationModifierDVec2> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierDVec2> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierDVec2> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierDVec2> create(const char *param);
	static Ptr<AnimationModifierDVec2> create(const char *param, int param_index);
	static Ptr<AnimationModifierDVec2> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierDVec2> &modifier);
	Math::dvec2 getDefaultValue() const;
	Math::dvec2 getValueByTime(float time);
	Math::dvec2 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::dvec2 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveDouble> &curvex);
	Ptr<AnimationCurveDouble> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveDouble> &curvey);
	Ptr<AnimationCurveDouble> getCurveY() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierDVec2> AnimationModifierDVec2Ptr;


class UNIGINE_API AnimationModifierVec3 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_VEC3; }
	static Ptr<AnimationModifierVec3> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierVec3> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierVec3> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierVec3> create(const char *param);
	static Ptr<AnimationModifierVec3> create(const char *param, int param_index);
	static Ptr<AnimationModifierVec3> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierVec3> &modifier);
	Math::Vec3 getDefaultValue() const;
	Math::Vec3 getValueByTime(float time);
	Math::Vec3 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::Vec3 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveScalar> &curvex);
	Ptr<AnimationCurveScalar> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveScalar> &curvey);
	Ptr<AnimationCurveScalar> getCurveY() const;
	void setCurveZ(const Ptr<AnimationCurveScalar> &curvez);
	Ptr<AnimationCurveScalar> getCurveZ() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierVec3> AnimationModifierVec3Ptr;


class UNIGINE_API AnimationModifierFVec3 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_FVEC3; }
	static Ptr<AnimationModifierFVec3> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierFVec3> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierFVec3> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierFVec3> create(const char *param);
	static Ptr<AnimationModifierFVec3> create(const char *param, int param_index);
	static Ptr<AnimationModifierFVec3> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierFVec3> &modifier);
	Math::vec3 getDefaultValue() const;
	Math::vec3 getValueByTime(float time);
	Math::vec3 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::vec3 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveFloat> &curvex);
	Ptr<AnimationCurveFloat> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveFloat> &curvey);
	Ptr<AnimationCurveFloat> getCurveY() const;
	void setCurveZ(const Ptr<AnimationCurveFloat> &curvez);
	Ptr<AnimationCurveFloat> getCurveZ() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierFVec3> AnimationModifierFVec3Ptr;


class UNIGINE_API AnimationModifierDVec3 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_DVEC3; }
	static Ptr<AnimationModifierDVec3> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierDVec3> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierDVec3> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierDVec3> create(const char *param);
	static Ptr<AnimationModifierDVec3> create(const char *param, int param_index);
	static Ptr<AnimationModifierDVec3> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierDVec3> &modifier);
	Math::dvec3 getDefaultValue() const;
	Math::dvec3 getValueByTime(float time);
	Math::dvec3 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::dvec3 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveDouble> &curvex);
	Ptr<AnimationCurveDouble> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveDouble> &curvey);
	Ptr<AnimationCurveDouble> getCurveY() const;
	void setCurveZ(const Ptr<AnimationCurveDouble> &curvez);
	Ptr<AnimationCurveDouble> getCurveZ() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierDVec3> AnimationModifierDVec3Ptr;


class UNIGINE_API AnimationModifierVec4 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_VEC4; }
	static Ptr<AnimationModifierVec4> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierVec4> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierVec4> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierVec4> create(const char *param);
	static Ptr<AnimationModifierVec4> create(const char *param, int param_index);
	static Ptr<AnimationModifierVec4> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierVec4> &modifier);
	Math::Vec4 getDefaultValue() const;
	Math::Vec4 getValueByTime(float time);
	Math::Vec4 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::Vec4 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveScalar> &curvex);
	Ptr<AnimationCurveScalar> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveScalar> &curvey);
	Ptr<AnimationCurveScalar> getCurveY() const;
	void setCurveZ(const Ptr<AnimationCurveScalar> &curvez);
	Ptr<AnimationCurveScalar> getCurveZ() const;
	void setCurveW(const Ptr<AnimationCurveScalar> &curvew);
	Ptr<AnimationCurveScalar> getCurveW() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierVec4> AnimationModifierVec4Ptr;


class UNIGINE_API AnimationModifierFVec4 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_FVEC4; }
	static Ptr<AnimationModifierFVec4> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierFVec4> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierFVec4> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierFVec4> create(const char *param);
	static Ptr<AnimationModifierFVec4> create(const char *param, int param_index);
	static Ptr<AnimationModifierFVec4> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierFVec4> &modifier);
	Math::vec4 getDefaultValue() const;
	Math::vec4 getValueByTime(float time);
	Math::vec4 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::vec4 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveFloat> &curvex);
	Ptr<AnimationCurveFloat> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveFloat> &curvey);
	Ptr<AnimationCurveFloat> getCurveY() const;
	void setCurveZ(const Ptr<AnimationCurveFloat> &curvez);
	Ptr<AnimationCurveFloat> getCurveZ() const;
	void setCurveW(const Ptr<AnimationCurveFloat> &curvew);
	Ptr<AnimationCurveFloat> getCurveW() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierFVec4> AnimationModifierFVec4Ptr;


class UNIGINE_API AnimationModifierDVec4 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_DVEC4; }
	static Ptr<AnimationModifierDVec4> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierDVec4> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierDVec4> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierDVec4> create(const char *param);
	static Ptr<AnimationModifierDVec4> create(const char *param, int param_index);
	static Ptr<AnimationModifierDVec4> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierDVec4> &modifier);
	Math::dvec4 getDefaultValue() const;
	Math::dvec4 getValueByTime(float time);
	Math::dvec4 getValueByNormalizedTime(float normalized_time);
	void addValue(float time, const Math::dvec4 &value, AnimationCurve::KEY_TYPE type = AnimationCurve::KEY_TYPE_LINEAR);
	void setCurveX(const Ptr<AnimationCurveDouble> &curvex);
	Ptr<AnimationCurveDouble> getCurveX() const;
	void setCurveY(const Ptr<AnimationCurveDouble> &curvey);
	Ptr<AnimationCurveDouble> getCurveY() const;
	void setCurveZ(const Ptr<AnimationCurveDouble> &curvez);
	Ptr<AnimationCurveDouble> getCurveZ() const;
	void setCurveW(const Ptr<AnimationCurveDouble> &curvew);
	Ptr<AnimationCurveDouble> getCurveW() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierDVec4> AnimationModifierDVec4Ptr;


class UNIGINE_API AnimationModifierMat4 : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_MAT4; }

	enum FOLLOW_MODE
	{
		FOLLOW_MODE_NONE = 0,
		FOLLOW_MODE_X,
		FOLLOW_MODE_Y,
		FOLLOW_MODE_Z,
	};
	static Ptr<AnimationModifierMat4> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierMat4> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierMat4> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierMat4> create(const char *param);
	static Ptr<AnimationModifierMat4> create(const char *param, int param_index);
	static Ptr<AnimationModifierMat4> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierMat4> &modifier);
	void addValue(float time, const Math::Mat4 &value);
	void setFollowMode(AnimationModifierMat4::FOLLOW_MODE mode);
	AnimationModifierMat4::FOLLOW_MODE getFollowMode() const;
	void setFollowPositionOffset(float offset);
	float getFollowPositionOffset() const;
	void updateUniformTime(bool enabled, bool force_update = false);
	bool isUniformTime() const;
};
typedef Ptr<AnimationModifierMat4> AnimationModifierMat4Ptr;


class UNIGINE_API AnimationModifierNode : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_NODE; }
	static Ptr<AnimationModifierNode> create(AnimParams::PARAM param);
	static Ptr<AnimationModifierNode> create(AnimParams::PARAM param, int param_index);
	static Ptr<AnimationModifierNode> create(AnimParams::PARAM param, const char *param_name);
	static Ptr<AnimationModifierNode> create(const char *param);
	static Ptr<AnimationModifierNode> create(const char *param, int param_index);
	static Ptr<AnimationModifierNode> create(const char *param, const char *param_name);
	void copy(const Ptr<AnimationModifierNode> &modifier);
	Ptr<Node> getDefaultValue() const;
	Ptr<Node> getValueByTime(float time);
	Ptr<Node> getValueByNormalizedTime(float normalized_time);
	void addValue(float time, int node_id);
	void setCurveID(const Ptr<AnimationCurveInt> &curveid);
	Ptr<AnimationCurveInt> getCurveID() const;
};
typedef Ptr<AnimationModifierNode> AnimationModifierNodePtr;


class UNIGINE_API AnimationModifierBones : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_BONES; }
	static Ptr<AnimationModifierBones> create();
	void copy(const Ptr<AnimationModifierBones> &modifier);
	void setNumBones(int bones);
	int getNumBones() const;
	int getValueByTime(float time, Vector<Math::mat4> &transfroms);
	void addValue(float time, Vector<Math::mat4> &transfroms);
	void setCurvePosX(int bone_index, const Ptr<AnimationCurveFloat> &in_curve);
	Ptr<AnimationCurveFloat> getCurvePosX(int bone_index) const;
	void setCurvePosY(int bone_index, const Ptr<AnimationCurveFloat> &in_curve);
	Ptr<AnimationCurveFloat> getCurvePosY(int bone_index) const;
	void setCurvePosZ(int bone_index, const Ptr<AnimationCurveFloat> &in_curve);
	Ptr<AnimationCurveFloat> getCurvePosZ(int bone_index) const;
	void setCurveRot(int bone_index, const Ptr<AnimationCurveQuat> &in_curve);
	Ptr<AnimationCurveQuat> getCurveRot(int bone_index) const;
	void setCurveScaleX(int bone_index, const Ptr<AnimationCurveFloat> &in_curve);
	Ptr<AnimationCurveFloat> getCurveScaleX(int bone_index) const;
	void setCurveScaleY(int bone_index, const Ptr<AnimationCurveFloat> &in_curve);
	Ptr<AnimationCurveFloat> getCurveScaleY(int bone_index) const;
	void setCurveScaleZ(int bone_index, const Ptr<AnimationCurveFloat> &in_curve);
	Ptr<AnimationCurveFloat> getCurveScaleZ(int bone_index) const;
};
typedef Ptr<AnimationModifierBones> AnimationModifierBonesPtr;


class UNIGINE_API AnimationModifierTrack : public AnimationModifier
{
public:
	static bool convertible(AnimationModifier *obj) { return obj && obj->getType() == AnimationModifier::ANIMATION_MODIFIER_TRACK; }
	static Ptr<AnimationModifierTrack> create();
	void addTrack(const char *path, float begin_time);
	void setTrackTimeCurve(const Ptr<AnimationCurveFloat> &curve);
};
typedef Ptr<AnimationModifierTrack> AnimationModifierTrackPtr;


class UNIGINE_API AnimationMask : public APIInterface
{
public:
	static Ptr<AnimationMask> create();
	void addInfo(const Ptr<AnimationModifierInfo> &info);
	void removeInfo(const Ptr<AnimationModifierInfo> &info);
	bool containsInfo(const Ptr<AnimationModifierInfo> &info) const;
	bool isEmpty() const;
	int getNumModifiers() const;
	Ptr<AnimationModifierInfo> getInfoByIndex(int index) const;
};
typedef Ptr<AnimationMask> AnimationMaskPtr;


class UNIGINE_API AnimationFrame : public APIInterface
{
public:
	static Ptr<AnimationFrame> create();
	void copy(const Ptr<AnimationFrame> &frame);
	void clear();
	int getModifierInfos(Vector<Ptr<AnimationModifierInfo>> &infos);
	void interpolate(const Ptr<AnimationFrame> &frame, float k);
	void interpolate(const Ptr<AnimationFrame> &frame, float k, const Ptr<AnimationMask> &exclude_mask);
};
typedef Ptr<AnimationFrame> AnimationFramePtr;


class UNIGINE_API AnimationBind : public APIInterface
{
public:
	static bool convertible(AnimationBind *obj) { return obj != nullptr; }

	enum TYPE
	{
		ANIMATION_BIND = 0,
		ANIMATION_BIND_NODE,
		ANIMATION_BIND_PROPERTY_PARAMETER,
		ANIMATION_BIND_MATERIAL,
		ANIMATION_BIND_RUNTIME,
	};
	AnimationBind::TYPE getType() const;
	const char *getTypeName() const;
};
typedef Ptr<AnimationBind> AnimationBindPtr;


class UNIGINE_API AnimationBindNode : public AnimationBind
{
public:
	static bool convertible(AnimationBind *obj) { return obj && obj->getType() == AnimationBind::ANIMATION_BIND_NODE; }
	static Ptr<AnimationBindNode> create();
	void setNode(const Ptr<Node> &node);
	Ptr<Node> getNode() const;
	void setNodeDescription(int id, const char *name);
	int getNodeDescriptionID() const;
	const char *getNodeDescriptionName() const;
};
typedef Ptr<AnimationBindNode> AnimationBindNodePtr;


class UNIGINE_API AnimationBindPropertyParameter : public AnimationBind
{
public:
	static bool convertible(AnimationBind *obj) { return obj && obj->getType() == AnimationBind::ANIMATION_BIND_PROPERTY_PARAMETER; }

	enum ACCESS
	{
		ACCESS_FROM_ASSET = 0,
		ACCESS_FROM_NODE,
		ACCESS_FROM_SURFACE,
	};
	static Ptr<AnimationBindPropertyParameter> create();
	void setAccess(AnimationBindPropertyParameter::ACCESS access);
	AnimationBindPropertyParameter::ACCESS getAccess() const;
	void setPropertyDescription(const UGUID &guid, const UGUID &file_guid);
	UGUID getPropertyDescriptionGUID() const;
	UGUID getPropertyDescriptionFileGUID() const;
	void setNodeDescription(int id, const char *name);
	int getNodeDescriptionID() const;
	const char *getNodeDescriptionName() const;
	void setNodePropertyDescription(const char *name, int index);
	const char *getNodePropertyDescriptionName() const;
	int getNodePropertyDescriptionIndex() const;
	void setSurfaceDescription(const char *name, int index);
	const char *getSurfaceDescriptionName() const;
	int getSurfaceDescriptionIndex() const;
	void setParameterPath(const char *path);
	const char *getParameterPath() const;
	Ptr<Node> getNode() const;
	Ptr<Property> getProperty() const;
	Ptr<PropertyParameter> getPropertyParameter() const;
};
typedef Ptr<AnimationBindPropertyParameter> AnimationBindPropertyParameterPtr;


class UNIGINE_API AnimationBindMaterial : public AnimationBind
{
public:
	static bool convertible(AnimationBind *obj) { return obj && obj->getType() == AnimationBind::ANIMATION_BIND_MATERIAL; }

	enum ACCESS
	{
		ACCESS_FROM_ASSET = 0,
		ACCESS_FROM_SURFACE,
	};
	static Ptr<AnimationBindMaterial> create();
	void setAccess(AnimationBindMaterial::ACCESS access);
	AnimationBindMaterial::ACCESS getAccess() const;
	void setMaterialDescription(const UGUID &guid, const UGUID &file_guid);
	UGUID getMaterialDescriptionGUID() const;
	UGUID getMaterialDescriptionFileGUID() const;
	void setObjectDescription(int id, const char *name);
	int getObjectDescriptionID() const;
	const char *getObjectDescriptionName() const;
	void setSurfaceDescription(const char *name, int index);
	const char *getSurfaceDescriptionName() const;
	int getSurfaceDescriptionIndex() const;
	Ptr<Object> getObject() const;
	Ptr<Material> getMaterial() const;
};
typedef Ptr<AnimationBindMaterial> AnimationBindMaterialPtr;


class UNIGINE_API AnimationBindRuntime : public AnimationBind
{
public:
	static bool convertible(AnimationBind *obj) { return obj && obj->getType() == AnimationBind::ANIMATION_BIND_RUNTIME; }
	static Ptr<AnimationBindRuntime> create();
	void setWidget(const Ptr<Widget> &widget);
	Ptr<Widget> getWidget() const;
};
typedef Ptr<AnimationBindRuntime> AnimationBindRuntimePtr;

class AnimationPlayback;

class UNIGINE_API AnimationObject : public APIInterface
{
public:
	static bool convertible(AnimationObject *obj) { return obj != nullptr; }

	enum TYPE
	{
		ANIMATION_OBJECT = 0,
		ANIMATION_OBJECT_NODE,
		ANIMATION_OBJECT_MATERIAL,
		ANIMATION_OBJECT_PROPERTY_PARAMETER,
		ANIMATION_OBJECT_RUNTIME,
		ANIMATION_OBJECT_TRACK,
	};
	AnimationObject::TYPE getType() const;
	const char *getTypeName() const;
	int getID() const;
	void setName(const char *name);
	const char *getName() const;
};
typedef Ptr<AnimationObject> AnimationObjectPtr;


class UNIGINE_API AnimationObjectNode : public AnimationObject
{
public:
	static bool convertible(AnimationObject *obj) { return obj && obj->getType() == AnimationObject::ANIMATION_OBJECT_NODE; }
	static Ptr<AnimationObjectNode> create(const char *name);
	void setBind(const Ptr<AnimationBindNode> &bind);
	Ptr<AnimationBindNode> getBind() const;
	void setPlaybackOverriddenBind(const Ptr<AnimationPlayback> &playback, const Ptr<AnimationBindNode> &bind);
	Ptr<AnimationBindNode> getPlaybackOverriddenBind(const Ptr<AnimationPlayback> &playback);
};
typedef Ptr<AnimationObjectNode> AnimationObjectNodePtr;


class UNIGINE_API AnimationObjectMaterial : public AnimationObject
{
public:
	static bool convertible(AnimationObject *obj) { return obj && obj->getType() == AnimationObject::ANIMATION_OBJECT_MATERIAL; }
	static Ptr<AnimationObjectMaterial> create(const char *name);
	void setBind(const Ptr<AnimationBindMaterial> &bind);
	Ptr<AnimationBindMaterial> getBind() const;
	void setPlaybackOverriddenBind(const Ptr<AnimationPlayback> &playback, const Ptr<AnimationBindMaterial> &bind);
	Ptr<AnimationBindMaterial> getPlaybackOverriddenBind(const Ptr<AnimationPlayback> &playback);
};
typedef Ptr<AnimationObjectMaterial> AnimationObjectMaterialPtr;


class UNIGINE_API AnimationObjectPropertyParameter : public AnimationObject
{
public:
	static bool convertible(AnimationObject *obj) { return obj && obj->getType() == AnimationObject::ANIMATION_OBJECT_PROPERTY_PARAMETER; }
	static Ptr<AnimationObjectPropertyParameter> create(const char *name);
	void setBind(const Ptr<AnimationBindPropertyParameter> &bind);
	Ptr<AnimationBindPropertyParameter> getBind() const;
	void setPlaybackOverriddenBind(const Ptr<AnimationPlayback> &playback, const Ptr<AnimationBindPropertyParameter> &bind);
	Ptr<AnimationBindPropertyParameter> getPlaybackOverriddenBind(const Ptr<AnimationPlayback> &playback);
};
typedef Ptr<AnimationObjectPropertyParameter> AnimationObjectPropertyParameterPtr;


class UNIGINE_API AnimationObjectRuntime : public AnimationObject
{
public:
	static bool convertible(AnimationObject *obj) { return obj && obj->getType() == AnimationObject::ANIMATION_OBJECT_RUNTIME; }
	static Ptr<AnimationObjectRuntime> create(const char *name);
	void setBind(const Ptr<AnimationBindRuntime> &bind);
	Ptr<AnimationBindRuntime> getBind() const;
	void setPlaybackOverriddenBind(const Ptr<AnimationPlayback> &playback, const Ptr<AnimationBindRuntime> &bind);
	Ptr<AnimationBindRuntime> getPlaybackOverriddenBind(const Ptr<AnimationPlayback> &playback);
};
typedef Ptr<AnimationObjectRuntime> AnimationObjectRuntimePtr;


class UNIGINE_API AnimationObjectTrack : public AnimationObject
{
public:
	static bool convertible(AnimationObject *obj) { return obj && obj->getType() == AnimationObject::ANIMATION_OBJECT_TRACK; }
	static Ptr<AnimationObjectTrack> create(const char *name);
};
typedef Ptr<AnimationObjectTrack> AnimationObjectTrackPtr;


class UNIGINE_API AnimationTrack : public APIInterface
{
public:
	static Ptr<AnimationTrack> create();
	static Ptr<AnimationTrack> create(const char *name);
	void copy(const Ptr<AnimationTrack> &track);
	void clear();
	UGUID getGUID() const;
	void setName(const char *name);
	const char *getName() const;
	bool containsObject(const Ptr<AnimationObject> &anim_obj);
	int getNumObjects() const;
	Ptr<AnimationObject> getObject(int index) const;
	int addObject(const Ptr<AnimationObject> &anim_obj);
	void removeObject(const Ptr<AnimationObject> &anim_obj);
	void addObjectModifier(const Ptr<AnimationObject> &anim_obj, const Ptr<AnimationModifier> &modifier);
	bool updateObjectModifier(const Ptr<AnimationObject> &anim_obj, const Ptr<AnimationModifier> &modifier);
	void removeObjectModifier(const Ptr<AnimationObject> &anim_obj, const Ptr<AnimationModifier> &modifier);
	int getObjectModifiers(const Ptr<AnimationObject> &anim_obj, Vector<Ptr<AnimationModifier>> &out_modifiers) const;
	void addObjectModifier(const char *anim_obj_name, const Ptr<AnimationModifier> &modifier);
	void addSingletonModifier(const Ptr<AnimationModifier> &modifier);
	bool updateSingletonModifier(const Ptr<AnimationModifier> &modifier);
	void removeSingletonModifier(const Ptr<AnimationModifier> &modifier);
	int getSingletonModifiers(Vector<Ptr<AnimationModifier>> &out_modifiers) const;
	float getDuration() const;
	void setManualDuration(float duration);
	float getManualDuration() const;
	Ptr<AnimationFrame> getFrame(float time);
	Ptr<AnimationFrame> getFrameByNormalizedTime(float time);
	void setEventCurve(const Ptr<AnimationCurveInt> &curve);
	Ptr<AnimationCurveInt> getEventCurve() const;
	void *addEventCallback(CallbackBase1<int> *func);
	bool removeEventCallback(void *id);
	void clearEventCallbacks();
	const char *getPath() const;
};
typedef Ptr<AnimationTrack> AnimationTrackPtr;


class UNIGINE_API AnimationPlayback : public APIInterface
{
public:
	static Ptr<AnimationPlayback> create();
	int getNumObjects() const;
	Ptr<AnimationObject> getObject(int index) const;
	bool containsObject(const Ptr<AnimationObject> &anim_obj) const;
	void clear();
	void apply(float time);
	void apply(const Ptr<AnimationFrame> &frame);
	void play();
	void pause();
	void stop();
	bool isPlaying() const;
	bool isStopped() const;
	float getDuration() const;
	void setTime(float time, float from = -1.0f, float to = -1.0f);
	float getTime() const;
	void setSpeed(float speed);
	float getSpeed() const;
	void setLoop(bool loop);
	bool isLoop() const;
	void setTimeFrom(float from);
	float getTimeFrom() const;
	void setTimeTo(float to);
	float getTimeTo() const;
	void setTrack(const Ptr<AnimationTrack> &track);
	Ptr<AnimationTrack> getTrack() const;
	int addLayer();
	int addLayer(const Ptr<AnimationTrack> &track);
	void removeLayer(int index);
	int getNumLayers() const;
	int addLayerTrack(int layer_index);
	int addLayerTrack(int layer_index, const Ptr<AnimationTrack> &track);
	void removeLayerTrack(int layer_index, int track_index);
	int getNumLayerTracks(int layer_index) const;
	void setLayerTrack(int layer_index, int track_index, const Ptr<AnimationTrack> &track);
	Ptr<AnimationTrack> getLayerTrack(int layer_index, int track_index) const;
	void setLayerTrackBeginTime(int layer_index, int track_index, float offest);
	float getLayerTrackBeginTime(int layer_index, int track_index) const;
	void setLayerTrackSpeed(int layer_index, int track_index, float speed);
	float getLayerTrackSpeed(int layer_index, int track_index) const;
	void setLayerTrackApplyBefore(int layer_index, int track_index, bool is_apply);
	bool isLayerTrackApplyBefore(int layer_index, int track_index) const;
	void setLayerTrackApplyAfter(int layer_index, int track_index, bool is_apply);
	bool isLayerTrackApplyAfter(int layer_index, int track_index) const;
	void setLayerTrackWeightCurve(int layer_index, int track_index, const Ptr<AnimationCurveFloat> &curve);
	Ptr<AnimationCurveFloat> getLayerTrackWeightCurve(int layer_index, int track_index) const;
	void setLayerTrackLinearFade(int layer_index, int track_index, float effect_time, bool use_fade_in, bool use_fade_out);
	float getLayerTrackDuration(int layer_index, int track_index) const;
	float getLayerTrackEndTime(int layer_index, int track_index) const;
	float getLayerDuration(int layer_index) const;
};
typedef Ptr<AnimationPlayback> AnimationPlaybackPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Animations
{
public:
	static bool isInitialized();

	enum RESULT
	{
		RESULT_TRACK_ERROR = 0,
		RESULT_NEW_TRACK_LOADED,
		RESULT_TRACK_IS_ALREADY_LOADED,
		RESULT_TRACK_RELOADED,
		RESULT_TRACK_SAVED,
		RESULT_TRACK_UNLOADED,
		RESULT_PLAYBACK_ERROR,
		RESULT_NEW_PLAYBACK_LOADED,
		RESULT_PLAYBACK_IS_ALREADY_LOADED,
		RESULT_PLAYBACK_SAVED,
	};
	static int getNumObjects();
	static Ptr<AnimationObject> getObjectByIndex(int index);
	static Ptr<AnimationObject> getObjectByID(int id);
	static bool containsObject(int id);
	static int getObjectIndex(const Ptr<AnimationObject> &obj);
	static void loadTracks();
	static void unloadTracks();
	static void reloadTracks();
	static Animations::RESULT loadTrack(const char *path);
	static Animations::RESULT reloadTrack(const char *path);
	static Animations::RESULT saveTrack(const Ptr<AnimationTrack> &track, const char *path);
	static Animations::RESULT saveTrackPrecomputed(const Ptr<AnimationTrack> &track, int num_frames, bool is_looped_frames, const char *path);
	static int getNumTracks();
	static Ptr<AnimationTrack> getTrackByIndex(int index);
	static Ptr<AnimationTrack> getTrackByGUID(const UGUID &guid);
	static Ptr<AnimationTrack> getTrackByFileGUID(const UGUID &guid);
	static Ptr<AnimationTrack> getTrackByPath(const char *path);
	static bool containsTrack(const UGUID &guid);
	static int getTrackIndex(const Ptr<AnimationTrack> &track);
	static void loadPlaybacks();
	static Animations::RESULT loadPlayback(const char *path);
	static Animations::RESULT savePlayback(const Ptr<AnimationPlayback> &playback, const char *path);
	static int getNumPlaybacks();
	static Ptr<AnimationPlayback> getPlaybackByIndex(int index);
	static Ptr<AnimationPlayback> getPlaybackByGUID(const UGUID &guid);
	static Ptr<AnimationPlayback> getPlaybackByFileGUID(const UGUID &guid);
	static Ptr<AnimationPlayback> getPlaybackByPath(const char *path);
	static bool containsPlayback(const UGUID &guid);
	static int getPlaybackIndex(const Ptr<AnimationPlayback> &playback);
	static int getClasses(Vector<String> &out_classes);
	static int getSingletonClasses(Vector<String> &out_classes);
	static const char *getParentClass(const char *class_name);
	static int getDerivedClasses(const char *class_name, Vector<String> &out_classes);
	static int getClassParameters(const char *class_name, Vector<int> &out_parameters);
	static const char *getParameterName(AnimParams::PARAM param);
	static AnimationModifier::TYPE getParameterModifierType(AnimParams::PARAM param);
	static AnimParams::PARAM getParameterByName(const char *param_name);
	static void convertToUanims(const char *folder_path, const Vector<String> &playbacks);
	static void convertToUanims(const Vector<String> &tracks, const Vector<String> &playbacks);
	static void checkUtrackTypes();
	static bool animToBonesModifier(const char *anim_path, const Ptr<AnimationModifierBones> &out_modifier, float duration);
	static Event<const Ptr<AnimationObject> &> &getEventObjectAdded();
	static Event<const Ptr<AnimationObject> &> &getEventObjectRemoved();
	static Event<const Ptr<AnimationTrack> &> &getEventTrackAdded();
	static Event<const Ptr<AnimationTrack> &> &getEventTrackRemoved();
};

} // namespace Unigine
