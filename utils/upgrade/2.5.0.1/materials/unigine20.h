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

#ifndef __MIGRATION_MATERIALS_UNIGINE20_H__
#define __MIGRATION_MATERIALS_UNIGINE20_H__

#include <materials/unigine20_cache.generated.h>

/*
 */
namespace Unigine20 {
	
	enum {
		MESH_DETAIL_DISABLED		= 0,
		MESH_DETAIL_OVERLAY			= 1,
		MESH_DETAIL_MULTIPLY		= 2,
		MESH_DETAIL_TEXTURE_MASK	= 3,
		MESH_DETAIL_OVERLAP_OBJECT	= 4,
		MESH_DETAIL_OVERLAP_WORLD	= 5,
	};
	
	enum {
		MESH_DETAIL_FIRST_UV		= 0,
		MESH_DETAIL_SECOND_UV		= 1,
	};
	
	enum {
		MESH_WORKFLOW_METALNESS = 0,
		MESH_WORKFLOW_SPECULAR = 1,
	};
	
	enum {
		MESH_GEOMETRY_INFLATION_NONE	= 0,
		MESH_GEOMETRY_INFLATION_WIRE	= 1,
		MESH_GEOMETRY_INFLATION_BALLOON	= 2,
	};
	
	enum {
		MESH_PARALLAX_NONE		= 0,
		MESH_PARALLAX_DEFAULT	= 1,
		MESH_PARALLAX_CUTOUT	= 2,
	};
	
	enum {
		DECAL_BLEND_NOISE		= 0,
		DECAL_BLEND_ALPHA		= 1,
		DECAL_BLEND_OVERLAY		= 2,
		DECAL_BLEND_MULTIPLY	= 3,
	};
	
	enum {
		GRASS_SHAPE_DEFAULT = 0,
		GRASS_SHAPE_BILLBOARD = 1,
	};
	
	vec4 PLASTIC_SPECULAR_COLOR = vec4(0.2f,0.2f,0.2f,1.0f);
}

#endif /* __MIGRATION_MATERIALS_UNIGINE20_H__ */