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

#ifndef __MIGRATION_MATERIALS_LEGACY_H__
#define __MIGRATION_MATERIALS_LEGACY_H__

/*
 */
namespace Legacy {
	
	enum {
		MESH_AMBIENT_SKIP			= 0,
		MESH_AMBIENT_OPACITY		= 1,
		MESH_AMBIENT_TRANSPARENT	= 2,
		MESH_AMBIENT_LIGHTMAP		= 3,
	};
	
	enum {
		MESH_DETAIL_DISABLED		= 0,
		MESH_DETAIL_OVERLAY_FIRST	= 1,
		MESH_DETAIL_OVERLAY_SECOND	= 2,
		MESH_DETAIL_MULTIPLY_FIRST	= 3,
		MESH_DETAIL_MULTIPLY_SECOND	= 4,
	};
	
	enum {
		PBR_AMBIENT_NONE		= 0,
		PBR_AMBIENT_DEFAULT		= 1,
		PBR_AMBIENT_LIGHTMAP	= 2,
	};
	
	enum {
		BILLBOARD_AMBIENT_NONE			= 0,
		BILLBOARD_AMBIENT_OPACITY		= 1,
		BILLBOARD_AMBIENT_TRANSPARENT	= 2,
	};
	
	enum {
		PBR_EFFECT_NONE				= 0,
		PBR_EFFECT_MICROFIBER		= 1,
		PBR_EFFECT_PARALLAX			= 2,
		PBR_EFFECT_OPACITY_PARALLAX	= 3,
	};
	
	enum {
		GRASS_SHAPE_DEFAULT = 0,
		GRASS_SHAPE_BILLBOARD = 1,
		GRASS_SHAPE_CLUTTER = 2,
	};
	
	float DEFAULT_SPECULAR_POWER = 16.0f;
}

#endif /* __MIGRATION_MATERIALS_LEGACY_H__ */