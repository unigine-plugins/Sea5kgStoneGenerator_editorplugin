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

namespace Process {
	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/
	void material(Material m) {
		m.renameOption("light_mask", "shadow_mask");
	}
	
	/******************************************************************************\
	*
	* Property
	*
	\******************************************************************************/
	
	// local changes of the property file
	void propertyFile(Xml xml) {
	}

	// global changes that related to another properties
	void property(Properties::Property p) {
	}
	
	/******************************************************************************\
	*
	* Nodes
	*
	\******************************************************************************/
	void node(Xml xml) {
		string type = xml.getArg("type", "unknown");
		
		xmlRenameChild(xml, "reflection_mask", "reflection_viewport_mask");
		xmlRenameChild(xml, "light_mask", "shadow_mask");
		
		if(startsWith(type,"Object")) {
			forloop(int i = 0; xml.getNumChildren()) {
				Xml x = xml.getChild(i);
				string name = x.getName();
				if(name == "surface") {
					xmlRenameArg(x, "light_mask", "shadow_mask");
				}
			}
		}
		
		if (type == "LightOmni" || type == "LightProj") {
			if(xml.isChild("mode")) {
				Xml x = xml.getChild("mode");
				int data = x.getIntData();
				
				x.setIntData(0);
				if(data == 2)
				{
					x.setIntData(1);
					xml.setArg("enabled", "0");
					xmlSetChildValue(xml, "lens_flare_enabled", "0");
					xmlSetChildValue(xml, "shadow_mode", "1");
				}
			}
		}
		
		if (type == "LightWorld") {
			if(xml.isChild("shadow_sharpness"))
				xmlDeleteChild(xml, "shadow_sharpness");
		}
	}
	
	void surface(Xml xml) {
	}
	
	void surfaceProperty(Xml xml_surface, Xml xml_prop, Properties::Property prop) {
	}
	
	/******************************************************************************\
	*
	* Bodies
	*
	\******************************************************************************/
	void body(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Shapes
	*
	\******************************************************************************/
	void shape(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Joints
	*
	\******************************************************************************/
	void joint(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Render
	*
	\******************************************************************************/
	void render(Xml xml) {
		Xml xml_new = new Xml();
		
		string path_render = pathname(replace(__FILE__, "\\", "/")) + "render.xml";
		if(xml_new.load(path_render)) {
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
				Xml x = xml.getChild(i);
				if (xml_new.findChild(x.getName()) != -1)
					continue;
				delete xml.removeChild(x);
				i--;
			}
			
			xmlMergeChildren(xml_new, xml);
		}
		
		delete xml_new;
		
		xmlDeleteChild(xml, "render_shadows_omni_jitter");
		xmlDeleteChild(xml, "render_shadows_precision");
		
		xmlDeleteChild(xml, "render_lights_upscaling");
		
		xmlDeleteChild(xml, "render_streaming_tasks_per_frames");
		xmlDeleteChild(xml, "render_streaming_checking_duration");
		
		xmlDeleteChild(xml, "render_manager_create_meshes");
		xmlDeleteChild(xml, "render_manager_create_textures");
		
		xmlDeleteChild(xml, "render_manager_resource_check");
		xmlDeleteChild(xml, "render_manager_resource_update");
		xmlDeleteChild(xml, "render_manager_texture_upload_chunk");
		xmlDeleteChild(xml, "render_manager_texture_upload_frametime_part");
		
		xmlRenameChild(xml, "render_manager_create_shaders", "render_shaders_preload");
		xmlRenameChild(xml, "render_manager_meshes_memory", "render_streaming_meshes_memory_limit");
		xmlRenameChild(xml, "render_manager_textures_memory", "render_streaming_textures_memory_limit");
		
		if(xml.isChild("render_shadows_soft_quality")) {
			int value = xml.getChildData("render_shadows_soft_quality", 0);
			if (value == 0)
				xmlUpdateChildValue(xml, "render_shadows_soft_quality", "1");
			else if (value == 1)
				xmlUpdateChildValue(xml, "render_shadows_soft_quality", "2");
		}
		
	}
	
	/******************************************************************************\
	*
	* Sound
	*
	\******************************************************************************/
	void sound(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Physics
	*
	\******************************************************************************/
	void physics(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* World
	*
	\******************************************************************************/
	void world(Xml xml) {
		if(!xml.isChild("skinned_legacy_mode"))
		{
			Xml legacy_mode = xml.addChild("skinned_legacy_mode");
			legacy_mode.setIntData(1);
		}
	}
	
	/******************************************************************************\
	*
	* Track
	*
	\******************************************************************************/
	void track(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Config
	*
	\******************************************************************************/
	void config(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Meta
	*
	\******************************************************************************/
	void meta(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* AppProjection
	*
	\******************************************************************************/
	void projectionBinary(string file_name) {
		Log::info("upgrading \"%s\"", file_name);
		Xml xml = new Xml("app_projection");
		xml.setArg("version", ENGINE_VERSION);
		File file = new File(file_name, "rb");
		if (file.isOpened())
		{
			int version = file.readChar();
			if (version == 2)
			{
				int is_cfg = endsWith(file_name, ".cfg");
			
				int size = 1;
				if (is_cfg)
					size = file.readInt();

				for (int i = 0; i < size; i++)
				{
					Xml x = xml.addChild("projection");
					if (is_cfg)
						x.setArg("name", file.readString());
					
					// warp
					Xml x_warp = x.addChild("warp");
					file.readInt(); // warp_size
					Xml x_points = x_warp.addChild("points");
					x_points.setIntArg("columns", file.readInt());
					x_points.setIntArg("rows", file.readInt());
					int points_size = file.readInt();
					for (int k = 0; k < points_size; k++)
					{
						Xml x_point = x_points.addChild("point");
						x_point.setVec2Data(file.readVec2());
						x_point.setIntArg("type", file.readInt());
					}
					Xml x_handles = x_warp.addChild("handles");
					int handles_size = file.readInt();
					for (int k = 0; k < handles_size; k++)
					{
						Xml x_handle = x_handles.addChild("handle");
						x_handle.setVec2Data(file.readVec2());
					}
		
					int selection_size = file.readInt();
					for (int k = 0; k < selection_size; k++)
						file.readInt();
					
					Xml xp = x_warp.addChild("angle"); xp.setIntData(file.readInt());
					xp = x_warp.addChild("flip_horizontal"); xp.setIntData(file.readInt());
					xp = x_warp.addChild("flip_vertical"); xp.setIntData(file.readInt());
					xp = x_warp.addChild("debug_fill_color"); xp.setIntData(file.readChar());
					xp = x_warp.addChild("debug_show_grid"); xp.setIntData(file.readChar());
					xp = x_warp.addChild("upscale"); xp.setFloatData(file.readFloat());

					// blend
					Xml x_blend = x.addChild("blend");
					file.readInt(); // blend_size
					Xml x_masks = x_blend.addChild("masks");
					int masks_size = file.readInt();
					for (int k = 0; k < masks_size; k++)
					{
						Xml x_mask = x_masks.addChild("mask");
						x_mask.setArg("name", file.readString());
						x_mask.setIntArg("enabled", file.readChar());
						x_mask.setVec4Arg("color", file.readVec4());
						int mask_points_size = file.readInt();
						for (int j = 0; j < mask_points_size; j++)
						{
							Xml x_point = x_mask.addChild("point");
							x_point.setVec2Data(file.readVec2());
							x_point.setIntArg("type", file.readChar());
							x_point.setVec2Arg("handle_left", file.readVec2());
							x_point.setVec2Arg("handle_right", file.readVec2());
						}
						x_mask.setIntArg("smooth", file.readInt());
						x_mask.setFloatArg("size", file.readFloat());
						x_mask.setFloatArg("outer_alpha", file.readFloat());
						x_mask.setFloatArg("inner_alpha", file.readFloat());
						x_mask.setFloatArg("power", file.readFloat());
					}
					
					Xml xb = x_blend.addChild("gamma"); xb.setFloatData(file.readFloat());
					xb = x_blend.addChild("border_left"); xb.setVec3Data(file.readVec3());
					xb = x_blend.addChild("border_right"); xb.setVec3Data(file.readVec3());
					xb = x_blend.addChild("border_top"); xb.setVec3Data(file.readVec3());
					xb = x_blend.addChild("border_bottom"); xb.setVec3Data(file.readVec3());
					
					int multiply_size = file.readInt();
					Blob multiply_texture = new Blob();
					file.readStream(multiply_texture, multiply_size);
					delete multiply_texture;

					// color
					Xml x_color = x.addChild("color");
					Xml x_scale = x_color.addChild("scale"); x_scale.setVec4Data(file.readVec4());
					Xml x_bias = x_color.addChild("bias"); x_bias.setVec4Data(file.readVec4());
					Xml x_brightness = x_color.addChild("brightness"); x_brightness.setVec4Data(file.readVec4());
				}
			}
			file.close();
		}
		delete file;
		
		xml.save(file_name);
		delete xml;
	}
	
	void projection(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Syncker
	*
	\******************************************************************************/
	void synckerBinary(string file_name) {
	}
	
	void syncker(Xml xml) {
	}
}

#endif /* __MIGRATION_PROCESS_H__ */
