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
		if(m.getBaseMaterial() == "sky_base") {
			m.removeState("surface");
			m.removeState("inscattering");
			m.removeState("ambient");
			m.removeState("light_world");
			m.removeState("volume");
			m.removeState("turbulence");
			m.removeState("geodetic");
			
			m.removeTexture("noise");
			m.removeTexture("volume");
			m.removeTexture("density");
			m.removeTexture("topology");
			m.removeTexture("opacity_depth");
			
			m.removeParameter("volume_0_color");
			m.removeParameter("volume_1_color");
			m.removeParameter("volume_01_scale");
			m.removeParameter("volume_alpha");
			m.removeParameter("volume_turbulence");
			m.removeParameter("volume_scale");
			m.removeParameter("shadow_scale");
		}
		
		if(m.getBaseMaterial() == "grass_impostor_base" || m.getBaseMaterial() == "billboards_impostor_base") {
			m.addState("ao_map","0");
			m.addState("shading_map","0");
			m.addState("microfiber_map","0");
			m.addState("specular_map","0");
			m.addState("translucent_map","0");
			
			m.addParameter("metalness","0.0");
			m.addParameter("roughness","1.0");
			m.addParameter("specular","0.0");
			m.addParameter("microfiber","0.0");
			m.addParameter("translucent","0.0");
			
			m.renameTexture("diffuse", "albedo");
			
			m.renameParameter("diffuse_color", "albedo_color");
			
			m.removeParameter("specular_color");
			m.removeParameter("gloss_scale");
			m.removeParameter("translucent_scale");
		}
		
		if(m.getBaseMaterial() == "mesh_base") {
			if(m.hasParameter("detail_mapping")) {
				int value = int(m.getParameterValue("detail_mapping"));
				if(value > 3)
					value++;
				m.addParameter("detail_mapping",string(value));
			}
			
			if(m.hasParameter("detail_mask_mapping")) {
				int value = int(m.getParameterValue("detail_mask_mapping"));
				if(value > 4)
					value++;
				m.addParameter("detail_mask_mapping",string(value));
			}
		}
	}
	
	/******************************************************************************\
	*
	* Nodes
	*
	\******************************************************************************/
	void node_new_parameters(Xml xml, string name) {
		string path = pathname(replace(__FILE__, "\\", "/")) + name;
		
		Xml xml_new = new Xml();
		if(!xml_new.load(path)) {
			Log::error("Process::node_new_parameters failed to load \"%s\"", path);
			delete xml_new;
			return;
		}
		xmlMergeChildren(xml_new, xml);
		delete xml_new;
	}
	
	void node(Xml xml) {
		// node type
		string type = xml.getArg("type","unknown");
		
		if(type == "LightEnvironmentProbe")
			xmlSetChildValue(xml, "ambient_enabled","1");
		
		if(type == "LightVoxelProbe")
			xmlSetChildValue(xml, "reflection_enabled","1");
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
		// joint type
		string type = xml.getArg("type", "unknown");
		
		if(type == "JointWheel")
			xmlDeleteChild(xml, "wheel_width");
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
		string removed[] = (
			"node.object.sky.minSlices": 0,
			"node.object.sky.maxSlices": 0,
			"node.object.sky.humidity": 0,
			"node.object.sky.transition": 0,
			"node.object.sky.extinction": 0,
			"node.object.sky.velocity": 0,
			"node.object.sky.offset": 0,
			"node.object.sky.layer": 0,
		);
		
		string renamed[] = (
		);
		
		for(int i = 0; i < xml.getNumChildren(); i++) {
			
			Xml x = xml.getChild(i);
			
			if(x.getName() != "parameter" || !x.isArg("type")) continue;
			
			if(removed.check(x.getArg("type"))) {
				delete xml.removeChild(x);
				i--;
			} else if(renamed.check(x.getArg("type"))) {
				x.setArg("type",renamed[x.getArg("type")]);
			}
		}
	}
	
	/******************************************************************************\
	*
	* Config
	*
	\******************************************************************************/
	void config(Xml xml) {
	}
	
}

#endif /* __MIGRATION_PROCESS_H__ */
