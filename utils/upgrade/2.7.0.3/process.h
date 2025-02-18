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
	
	void path_to_guid(Xml xml) {
		
		// exclude name
		if(	xml.getName() == "position" ||
			xml.getName() == "transform" ||
			xml.getName() == "vertex" ||
			xml.getName() == "indices" ||
			xml.getName() == "keys_x" ||
			xml.getName() == "keys_y" ||
			xml.getName() == "keys_z" ||
			xml.getName() == "surface" ||
			xml.getName() == "billboards" ||
			xml.getName() == "variables" ||
			xml.getName() == "density" ||
			xml.getName() == "min_height_spread" ||
			xml.getName() == "max_height_spread" ||
			xml.getName() == "aspect_mean" ||
			xml.getName() == "aspect_spread" ||
			xml.getName() == "offset_mean" ||
			xml.getName() == "enabled" ||
			xml.getName() == "properties"
		)
			return;
		
		string path = xml.getData();
		if(strlen(path) > 1) {
			UGUID guid = FileSystem::getFastGUID(path);
			if(guid == NULL)
				guid = FileSystem::getGUID(path, false);
			
			if(guid != NULL && !guid.isEmpty())
				xml.setData(guid.getFileSystemString());
		}
		
		for(int i = 0; i < xml.getNumArgs(); i++) {
			string path = xml.getArgValue(i);
			if(strlen(path) <= 1)
				continue;
			
			if(	xml.getArgName(i) == "type" ||
				xml.getArgName(i) == "collider" ||
				xml.getArgName(i) == "id"
				)
				continue;
			
			UGUID guid = FileSystem::getFastGUID(path);
			if(guid == NULL)
				guid = FileSystem::getGUID(path, false);
			if(guid != NULL && !guid.isEmpty())
				xml.setArgValue(i, guid.getFileSystemString());
		}
		
		for(int i = 0; i < xml.getNumChildren(); i++)
			path_to_guid(xml.getChild(i));
	}
	
	
	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/
	void material(Material m) {
		path_to_guid(m.xml);
		if(m.getBaseMaterial() == "render_composite_deferred") {
			m.removeState("lights");
		}
	}
	
	/******************************************************************************\
	*
	* Nodes
	*
	\******************************************************************************/
	void node(Xml xml) {
		path_to_guid(xml);
		
		// node type
		string type = xml.getArg("type","unknown");
		
		if(type == "LightOmni" || type == "LightProj" || type == "LightWorld") {
			if(xml.isChild("lens_flare_fade_smoothness"))
				xmlRenameChild(xml, "lens_flare_fade_smoothness", "lens_flare_occlusion_fade");
			
			if(xml.isChild("lens_flare_vignette_smoothness"))
				xmlRenameChild(xml, "lens_flare_vignette_smoothness", "lens_flare_occlusion_fade_border");
			
			if(xml.isChild("lens_flare_light_color_effect"))
				xmlRenameChild(xml, "lens_flare_light_color_effect", "lens_flare_use_light_color");
			
			if(xml.isChild("lens_flare_billboards")) {
				Xml xml_child = xml.getChild("lens_flare_billboards");
				int num = xml_child.getIntArg("num");
				
				for(int i = 0; i < num; i++) {
					if(xml_child.isChild("billboard")) {
						Xml c = xml_child.getChild(i);
						if(c.isArg("rotation")) xmlRenameArg(c, "rotation", "rotate");
						if(c.isArg("lower_left_uv")) xmlRenameArg(c, "lower_left_uv", "uv_lower_left");
						if(c.isArg("upper_right_uv")) xmlRenameArg(c, "upper_right_uv", "uv_upper_right");
						if(c.isArg("offset_size")) xmlRenameArg(c, "offset_size", "offset_scale");
					}
				}
			}
		}
		
		if(type == "LightEnvironmentProbe") {
			if(xml.isChild("is_sun_light_color"))
				xmlRenameChild(xml, "is_sun_light_color", "use_sun_color");
			
			if(xml.isChild("reflection_update")) {
				int value = xml.getChildData("reflection_update",0);
				if(value == -1)
					value = 0;
				value++;
				xmlRenameChild(xml, "reflection_update", "render_faces_per_frame");
				xmlUpdateChildValue(xml,"render_faces_per_frame", value);
			}
			
			xmlDeleteChild(xml, "grab_offset");
		}
		
		if(type == "LightVoxelProbe") {
			if(xml.isChild("sun_color_influence"))
				xmlRenameChild(xml, "sun_color_influence", "use_sun_color");
		}
		
		// surface property migration
		for(int i = 0; i < xml.getNumChildren(); i++) { // <node>
			
			Xml x = xml.getChild(i); // <surface>, <transform>, ...
			string name = x.getName();
			int prop_num = x.findChild("property");
			
			if(name == "surface" && prop_num != -1) {
				Xml x_prop = x.getChild(prop_num); // <property>
				
				for(int k = 0; k < x_prop.getNumChildren(); k++) {
					Xml x_param = x_prop.getChild(k); // <options>, <state>, <parameter>
					
					// "options" migration
					if(x_param.getName() == "options") {
						if(x_param.isArg("intersection")) {
							Xml new_param = x_prop.addChild("parameter");
							new_param.setName("parameter");
							new_param.setArg("name", "intersection");
							new_param.setData(x_param.getArg("intersection"));
						}
						
						if(x_param.isArg("collision")) {
							Xml new_param = x_prop.addChild("parameter");
							new_param.setName("parameter");
							new_param.setArg("name", "collision");
							new_param.setData(x_param.getArg("collision"));
						}
						
						x_prop.removeChild(x_param);
						k--;
						continue;
					}
					
					// "state" migration
					if(x_param.getName() == "state")
						x_param.setName("parameter");
				}
			}
		}
	}
	
	/******************************************************************************\
	*
	* Bodies
	*
	\******************************************************************************/
	void body(Xml xml) {
		path_to_guid(xml);
	}
	
	/******************************************************************************\
	*
	* Render
	*
	\******************************************************************************/
	void render(Xml xml) {
		path_to_guid(xml);
		
		//antialiasing -> taa & fxaa
		if(xml.isChild("render_antialiasing")) {
			
			if(xml.isChild("render_fxaa") || xml.isChild("render_taa")) {
				xmlDeleteChild(xml, "render_antialiasing");
			} else {
				
				int value = xml.getChildData("render_antialiasing",0);
				xmlDeleteChild(xml, "render_antialiasing");
				
				xml.addChild("render_taa");
				xml.addChild("render_fxaa");
				
				xmlUpdateChildValue(xml,"render_fxaa", "0");
				xmlUpdateChildValue(xml,"render_taa", "0");
				
				if(value == 1)
					xmlUpdateChildValue(xml,"render_fxaa", "1");
				if(value == 2)
					xmlUpdateChildValue(xml,"render_taa", "1");
			}
		}
		
		int value = xml.getChildData("render_fxaa",0);
		if(!value)
			xmlUpdateChildValue(xml,"render_fxaa", "0");
		
		value = xml.getChildData("render_taa",0);
		if(!value)
			xmlUpdateChildValue(xml,"render_taa", "0");
		
		
		xmlDeleteChild(xml, "render_lights_specular");
	}
	
	/******************************************************************************\
	*
	* World
	*
	\******************************************************************************/
	void world(Xml xml) {
		path_to_guid(xml);
	}
	
	/******************************************************************************\
	*
	* Track
	*
	\******************************************************************************/
	void track(Xml xml) {
		path_to_guid(xml);
	}
	
	/******************************************************************************\
	*
	* Config
	*
	\******************************************************************************/
	void config(Xml xml) {
		path_to_guid(xml);
	}
	
}

#endif /* __MIGRATION_PROCESS_H__ */
