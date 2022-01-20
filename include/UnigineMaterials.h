/* Copyright (C) 2005-2021, UNIGINE. All rights reserved.
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
#include "UnigineGUID.h"

namespace Unigine
{

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Materials
{
protected:
	

public:
	static int isInitialized(); 

	enum LOADING_MODE
	{
		LOADING_MODE_FAST = 0,
		LOADING_MODE_FULL_MATERIALS,
		LOADING_MODE_FULL_MATERIALS_SHADERS,
	};
	static void setLoadingMode(Materials::LOADING_MODE mode);
	static Materials::LOADING_MODE getLoadingMode();
	static Ptr<Material> loadMaterial(const char *path);
	static int getNumMaterials();
	static Ptr<Material> getMaterial(int num);
	static const char *getMaterialName(int num);
	static bool isManualMaterial(const char *name);
	static bool isBaseMaterial(const char *name);
	static bool isMaterial(const char *name);
	static bool isMaterial(const UGUID & guid);
	static Ptr<Material> findMaterial(const char *name);
	static Ptr<Material> findManualMaterial(const char *name);
	static Ptr<Material> findBaseMaterial(const char *name);
	static Ptr<Material> findMaterialByGUID(const UGUID & guid);
	static Ptr<Material> findMaterialByFileGUID(const UGUID & guid);
	static Ptr<Material> findMaterialByPath(const char *path);
	static bool removeMaterial(const UGUID & guid, bool remove_file = false, bool remove_children = true);
	static bool replaceMaterial(const Ptr<Material> &material, const Ptr<Material> &new_material);
	static bool saveMaterials();
	static void compileShaders(const Vector< Ptr<Material> > &materials);
	static void compileShaders();
	static void setPrecompileAllShaders(bool shaders);
	static bool isPrecompileAllShaders();
	static void reloadMaterials();
	static void destroyShaders();
	static void destroyTextures();
	static void createShaders();
};

} // namespace Unigine
