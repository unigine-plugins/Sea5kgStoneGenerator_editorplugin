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
		m.renameState("material_sss", "material_sssss");
		
		// shadows soft
		if(m.hasState("soft_shadows")) {
			int value = m.getStateValue("soft_shadows");
			if(value != 0)
				value = m.getStateValue("soft_shadows_quality") + 1;
			
			m.addState("shadow_filter_mode", value);
		}
		m.removeState("soft_shadows");
		m.removeState("soft_shadows_quality");
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
		
		xmlRenameArg(xml, "clutter", "immovable");
		
		if(startsWith(type,"Light"))
			xmlRenameChild(xml, "shadow_softness", "shadow_filter");
		
		if(type == "WorldSplineGraph") {
			forloop(int i = 0; xml.getNumChildren()) {
				Xml segment_nodes = xml.getChild(i);
				if(segment_nodes.getName() == "segment_nodes") {
					
					forloop(int i = 0; segment_nodes.getNumChildren()) {
						Xml range = segment_nodes.getChild(i);
						if(range.getName() == "range") {
							xmlRenameArg(range, "max_delta_angle", "adaptive_angle_threshold");
						}
					}
				}
			}
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
		
		xmlRenameChild(xml, "render_materials", "pre_post_materials");
		
		// sss to sssss 
		xmlRenameChild(xml, "render_sss", "render_sssss");
		xmlRenameChild(xml, "render_sss_quality", "render_sssss_quality");
		xmlRenameChild(xml, "render_sss_resolution", "render_sssss_resolution");
		xmlRenameChild(xml, "render_sss_radius", "render_sssss_radius");
		xmlRenameChild(xml, "render_sss_color", "render_sssss_color");
		
		xmlRenameChild(xml, "render_taa_color_clamping", "render_taa_frames_by_color");
		xmlRenameChild(xml, "render_taa_velocity_clamping", "render_taa_frames_by_velocity");
		xmlRenameChild(xml, "render_taa_velocity_threshold", "render_taa_frames_velocity_threshold");
		xmlRenameChild(xml, "render_taa_max_frame_count", "render_taa_max_frames_by_velocity");
		xmlRenameChild(xml, "render_taa_min_frame_count", "render_taa_min_frames_by_velocity");
		
		xmlDeleteChild(xml, "render_lights_interleaved_fix_ghosting");
		
		// console_skip to console_flag values
		void changeValue(Xml xml, string param_old, string param) {
			if(xmlRenameChild(xml, param_old, param)) {
				int value = xml.getChildData(param, 0);
				if (value == 0)
					xmlUpdateChildValue(xml, param, "1");
				else if (value == 1)
					xmlUpdateChildValue(xml, param, "0");
			}
		}
		
		changeValue(xml, "render_skip_render_materials", "render_pre_post_materials_enabled");
		changeValue(xml, "render_skip_post_materials", "render_screen_space_effects");
		changeValue(xml, "render_skip_transparent", "render_transparent_enabled");
		changeValue(xml, "render_skip_transparent_ambient", "render_transparent_ambient");
		changeValue(xml, "render_skip_transparent_light", "render_transparent_light");
		changeValue(xml, "render_skip_transparent_deferred", "render_transparent_deferred");
		changeValue(xml, "render_skip_transparent_multiple_env_probes", "render_transparent_multiple_env_probes");
		changeValue(xml, "render_skip_clouds", "render_clouds_enabled");
		changeValue(xml, "render_skip_water", "render_water_enabled");
		changeValue(xml, "render_skip_lights", "render_lights_enabled");
		
		xmlDeleteChild(xml, "render_reflection_dynamic_blur");

		// shadows soft
		if(xml.isChild("render_shadows_soft")) {
			int shadows_soft_value = xml.getChildData("render_shadows_soft", 0);
			xmlRenameChild(xml, "render_shadows_soft", "render_shadows_filter_mode");
			if(shadows_soft_value != 0) {
				int shadows_soft_quality_value = xml.getChildData("render_shadows_soft_quality", 0);
				shadows_soft_quality_value++;
				Xml x = xml.getChild("render_shadows_filter_mode");
				x.setIntData(shadows_soft_quality_value);
			}
		}
		xmlDeleteChild(xml, "render_shadows_soft_quality");
		xmlDeleteChild(xml, "render_shadows_soft_noise");
		
		
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
