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

#ifndef __MIGRATION_PROCESS_H__
#define __MIGRATION_PROCESS_H__

#include <fbx_reader.h>

namespace Process
{
	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/
	
	void material(Material m)
	{
		if(m.getBaseMaterial() == "mesh_base")
		{
			m.renameTexture("parallax", "displacement");
			m.renameState("parallax", "displacement");
			
			m.removeState("lightmap_with_ambient");
			m.removeState("lightmap_mapping");
			m.removeState("vertex_lightmap");
			
			m.removeTexture("lightmap");
			
			m.removeParameter("lightmap_scale");
			m.removeParameter("lightmap_gamma");
			m.removeParameter("lightmap_uv_transform");
		}
		
		m.renameState("material_sun_shafts", "material_shadow_shafts");
		
		if(m.getBaseMaterial() == "clouds_base")
		{
			m.removeParameter("hgp_brightness");
			m.removeParameter("hgp_pow");
			m.removeParameter("translucence");
		}
	}
	
	/******************************************************************************\
	*
	* Property
	*
	\******************************************************************************/
	
	// local changes of the property file
	void propertyFile(Xml xml)
	{
	}
	
	// global changes that related to another properties
	void property(Properties::Property p)
	{
	}
	
	/******************************************************************************\
	*
	* Nodes
	*
	\******************************************************************************/
	
	void node(Xml xml)
	{
		forloop(int i = 0; xml.getNumChildren())
		{
			if(xml.getChild(i).getName() == "surface")
				surface(xml.getChild(i));
		}
		
		string type = xml.getArg("type");
		
		if(type == "WorldSwitcher" && xml.isArg("update_distance_limit"))
			xml.removeArg("update_distance_limit");
		
		if (type == "LightVoxelProbe") 
		{
			xml.removeChild("ambient_color");
			xml.removeChild("ambient_intensity");
			xml.removeChild("reflection_color");
			xml.removeChild("reflection_intensity");
			xml.removeChild("bake_sampling_resolution");
			xml.removeChild("bake_sampling_mip_offset");
			xml.removeChild("bake_sampling_mip_ofsset");
			xml.removeChild("bake_full_resolution_bounces");
			xml.removeChild("bake_num_rays");
			xml.removeChild("bake_caustic");
			xml.removeChild("bake_znear");
			xml.removeChild("bake_fix_light_bleeding_bounce");
			xml.removeChild("bake_fix_light_bleeding_intensity");
			xml.removeChild("bake_fix_light_bleeding_radius");
			xml.removeChild("bake_full_resolution_bounces");
		}
		
		if (type == "LightEnvironmentProbe")
		{
			xmlRenameChild(xml, "correct_roughness", "correct_roughness_mode");
			
			xml.removeChild("shadow_screen_space_step_size");
			xml.removeChild("reflection_intensity");
			xml.removeChild("reflection_color");
			xml.removeChild("ambient_intensity");
			xml.removeChild("ambient_color");
		}
	}
	
	void surface(Xml xml)
	{
		xmlRenameArg(xml, "bake_to_voxel_probe", "bake_to_gi");
	}
	
	void surfaceProperty(Xml xml_surface, Xml xml_prop, Properties::Property prop)
	{
	}
	
	/******************************************************************************\
	*
	* Bodies
	*
	\******************************************************************************/
	void body(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Shapes
	*
	\******************************************************************************/
	void shape(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Joints
	*
	\******************************************************************************/
	void joint(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Render
	*
	\******************************************************************************/
	void render(Xml xml)
	{
		float saturation = 1.0f;
		if (xml.findChild("color_saturation") != -1)
		{
			saturation = xml.getChild("color_saturation").getFloatData();
			xml.removeChild("color_saturation");
		}
		
		xmlRenameChild(xml, "color_brightness", "color_correction_brightness");
		xmlRenameChild(xml, "color_contrast", "color_correction_contrast");
		xmlRenameChild(xml, "color_gamma", "color_correction_gamma");
		xmlRenameChild(xml, "color_white", "color_correction_white");
		xmlRenameChild(xml, "color_texture", "color_correction_lut");
		
		if (xml.findChild("color_correction") == -1)
		{
			Xml color_correction = xml.addChild("color_correction");
			
			for (int j = 0; j < 3; j++)
			{
				Xml channel = color_correction.addChild("curve");
				Xml keys = channel.addChild("keys");
				for (int i = 0; i <= 1; i++)
				{
					Xml key = keys.addChild("key");
					key.setVec2Arg("point", vec2(i, i));
					key.setVec2Arg("left_tangent", vec2(0.0f, 0.0f));
					key.setVec2Arg("right_tangent", vec2(0.0f, 0.0f));
				}
			}
			
			Xml keys = color_correction.addChild("curve").addChild("keys");
			for (int i = 0; i <= 1; i++)
			{
				Xml key = keys.addChild("key");
				key.setVec2Arg("point", vec2(i, saturation));
				key.setVec2Arg("left_tangent", vec2(0.0f, 0.0f));
				key.setVec2Arg("right_tangent", vec2(0.0f, 0.0f));
			}
		}
		
		xmlRenameChild(xml, "render_ssgi_ray_tracing_denoise", "render_ssgi_denoise");
		xmlRenameChild(xml, "render_ssgi_ray_tracing_threshold", "render_ssgi_threshold");
		
		Xml xml_new = new Xml();
		string path_render = pathname(replace(__FILE__, "\\", "/")) + "render.xml";
		if(xml_new.load(path_render)) 
		{
			for(int i = 0; i < xml.getNumChildren(); i++) 
			{
				Xml x = xml.getChild(i);
				if (xml_new.findChild(x.getName()) != -1)
					continue;
				delete xml.removeChild(x);
				i--;
			}
			
			xmlMergeChildren(xml_new, xml);
		}
		delete xml_new;
		
		//render panorama
		int panorama_to_viewport_modes[] = (
			1	:	1,
			2	:	3,
			3	:	8,
			4	:	2,
			5	:	4,
			6	:	8,
		);
		if(xml.isChild("render_panorama"))
		{
			int panorama_mode = xml.getChild("render_panorama").getIntData();
			xml.removeChild("render_panorama");
			
			if(panorama_mode != 0)
			{
				xmlSetChildValue(xml, "render_viewport_mode", panorama_to_viewport_modes[panorama_mode]);
				
				float fisheye_fov = 180.0f;
				if(panorama_mode == 6)
					fisheye_fov = 360.0f;
				xmlSetChildValue(xml, "render_panorama_fisheye_fov", fisheye_fov);
			}
		}
		// render stereo
		int stereo_to_viewport_modes[] = (
			1	:	9,
			2	:	10,
			3	:	11,
			4	:	12,
		);
		if(xml.isChild("render_stereo"))
		{
			int stereo_mode = xml.getChild("render_stereo").getIntData();
			xml.removeChild("render_stereo");
			if(stereo_mode != 0)
				xmlSetChildValue(xml, "render_viewport_mode", stereo_to_viewport_modes[stereo_mode]);
		}
		
		if(!xml.isChild("render_viewport_mode"))
			xml.setChildData("render_viewport_mode", 0);
	}
	
	/******************************************************************************\
	*
	* Sound
	*
	\******************************************************************************/
	void sound(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Physics
	*
	\******************************************************************************/
	void physics(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* World
	*
	\******************************************************************************/
	void world(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Track
	*
	\******************************************************************************/
	void track(Xml xml)
	{
		string removed[] = (
			"render.sunShafts.enabled":	0,
			"render.sunShafts.color":	0,
			"render.sunShafts.scale":	0,
			"render.sunShafts.length":	0,
			"render.sunShafts.attenuation":	0,
			"render.sunShafts.threshold":	0,
			"render.color.saturation":	0,
		);
		
		string renamed[] = (
			"render.color.brightness":	"render.colorCorrection.brightness",
			"render.color.contrast":	"render.colorCorrection.contrast",
			"render.color.gamma":		"render.colorCorrection.gamma",
			"render.color.white":		"render.colorCorrection.white",
			"render.color.texture":		"render.colorCorrection.texture"
		);
		
		for(int i = 0; i < xml.getNumChildren(); i++)
		{
			Xml x = xml.getChild(i);
			
			if(x.getName() != "parameter" || !x.isArg("type")) continue;
			string type = x.getArg("type");
			
			if(removed.check(type)) {
				delete xml.removeChild(x);
				i--;
			} else if(renamed.check(type))
			{
				xmlSetArg(x, "type", renamed[type]);
			}
			
			if(type == "material.stateToggle")
			{
				if(x.getArg("string") == "material_sun_shafts")
					xmlSetArg(x, "string", "material_shadow_shafts");
			}
		}
	}
	
	/******************************************************************************\
	*
	* Meta
	*
	\******************************************************************************/
	void meta(Xml xml, string file_name)
	{
	}
	
	/******************************************************************************\
	*
	* AppProjection
	*
	\******************************************************************************/
	void projectionBinary(string file_name)
	{
	}
	
	void projection(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Syncker
	*
	\******************************************************************************/
	void synckerBinary(string file_name)
	{
	}
	
	void syncker(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Configs
	*
	\******************************************************************************/
	void configBoot(Xml xml)
	{
	}
	void configControls(Xml xml)
	{
	}
	void configUser(Xml xml)
	{
		xmlRenameChild(xml, "show_messages", "console_onscreen");
	}
	
}

#endif /* __MIGRATION_PROCESS_H__ */
