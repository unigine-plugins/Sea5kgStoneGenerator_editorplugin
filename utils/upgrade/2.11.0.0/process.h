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

namespace Process {
	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/
	
	void material(Material m) {
		m.removeOption("depth_pre_pass");

		// particles upgrade
		if(m.getBaseMaterial() == "particles_base")
		{
			m.removeState("alpha");
			m.renameState("volume", "soft_interaction");
			m.renameParameter("volume_scale", "soft_interaction_scale");

			m.renameState("deferred", "deferred_buffers");

			string transparent_option = m.getOption("transparent");
			if(transparent_option == "1")
				m.renameParameter("deferred_threshold", "alpha_test_threshold");
			else
				m.renameParameter("deferred_threshold", "deferred_buffers_threshold");
			
			if(!m.xml.isArg("parent") && m.blend == NULL)
			{
				m.addBlend();
				m.blend.setSrc("one");
				m.blend.setDest("one");
			}
		}
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
		string type = xml.getArg("type","unknown");
		
		xml.removeArg("collider");
		xml.removeArg("latest");
		xml.removeArg("portal_culling_enabled");
		
		if (type == "ObjectParticles") {
			xmlRenameChild(xml, "intersection", "physics_intersection");
		}
		
		if (type == "PlayerActor") {
			xmlRenameChild(xml, "intersection_mask", "physics_intersection_mask");
		}
		
		if (type == "NodePivot") {
			xml.removeChild("pivot_transform");
			xml.removeChild("local_transform");
			
			xml.setArg("type", "NodeDummy");
		}
		
		if (type == "WorldPortal") {
			xml.removeChild("width");
			xml.removeChild("height");
			
			xml.setArg("type", "NodeDummy");
		}
		
		if (type == "WorldSector") {
			xml.removeChild("size");
			
			xml.setArg("type", "NodeDummy");
		}
		
		
		if (type == "WorldTransformPath") {
			xml.removeChild("radius");
		}
		
		if (type == "WorldTransformBone") {
			xml.removeChild("radius");
		}
		
		if (type == "WorldSwitcher") {
			xml.removeChild("point");
			xml.removeChild("size");
			xml.removeChild("offset");
		}
		
		if (type == "WorldExpression") {
			xml.removeChild("size");
			xml.removeChild("offset");
			
			if(xml.isChild("distance")) {
				xml.setArg("update_distance_limit", xml.getChildData("distance", "0"));
				xml.removeChild("distance");
			}
		}
		
		forloop(int i = 0; xml.getNumChildren())
			if(xml.getChild(i).getName() == "surface")
				surface(xml.getChild(i));
	}
	
	void surface(Xml xml) {
		
		if(!xml.isArg("intersection"))
			xml.setArg("physics_intersection", "1");
		
		if(xml.isArg("intersection_mask"))
			xml.setArg("physics_intersection_mask", xml.getArg("intersection_mask"));
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
		
		xmlRenameChild(xml, "intersection_mask", "physics_intersection_mask");
	}
	
	/******************************************************************************\
	*
	* Joints
	*
	\******************************************************************************/
	void joint(Xml xml) {
		
		xmlRenameChild(xml, "intersection_mask", "physics_intersection_mask");
	}
	
	/******************************************************************************\
	*
	* Render
	*
	\******************************************************************************/
	void render(Xml xml) {
		
		xmlRenameChild(xml, "render_landscape_terrain_culling_agressive ", "render_landscape_terrain_culling_aggressive");
		
		xmlDeleteChild(xml, "render_clutter_distance");
		xmlDeleteChild(xml, "render_landscape_cache_gpu_update_limit");
		
		// delete filmic settings to load by default
		xmlDeleteChild(xml, "render_filmic_shoulder_scale");
		xmlDeleteChild(xml, "render_filmic_linear_scale");
		xmlDeleteChild(xml, "render_filmic_linear_angle");
		xmlDeleteChild(xml, "render_filmic_toe_scale");
		xmlDeleteChild(xml, "render_filmic_toe_numerator");
		xmlDeleteChild(xml, "render_filmic_toe_denominator");
		xmlDeleteChild(xml, "render_filmic_white_level");
		xmlDeleteChild(xml, "render_filmic_saturation_recovery");
		
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
		xmlDeleteChild(xml, "skinned_legacy_mode");
		xmlDeleteChild(xml, "name");
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
	void meta(Xml xml, string file_name) {
		string source_filepath = extension(file_name, "");
		
		if(lower(extension(source_filepath)) == "fbx") {
			double unit_scale = 0.0;
			double original_unit_scale = 0.0;
			if(read_fbx(source_filepath, unit_scale, original_unit_scale)) {
				Xml scale_node = xml.find("* name=\"scale\"");
				if(scale_node != NULL) {
					double scale = double(scale_node.getData());
					scale = scale * (100.0 / original_unit_scale);
					scale_node.setData(string(scale));
				}
			}
		}
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
