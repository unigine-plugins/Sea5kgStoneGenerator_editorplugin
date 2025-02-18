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
		if(m.getBaseMaterial() == "mesh_base") {
			m.removeState("parallax_shadow");
		}
		
		if(m.getBaseMaterial() == "billboards_impostor_base" || m.getBaseMaterial() == "grass_impostor_base") {
			m.removeParameter("impostor_transform");
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
		if(xml.isArg("spatial")) {
			int portal_culling_enabled = xml.getIntArg("spatial");
			xml.removeArg("spatial");
			xml.setIntArg("portal_culling_enabled", portal_culling_enabled);
		}
		
		if(type == "LightOmni" || type == "LightProj") {
			if(xml.isChild("color_filter")) {
				Xml color_filter = xml.getChild("color_filter");
				vec4 color = color_filter.getVec4Data();
				color_filter.setData(vec4(color.x, color.y, color.z, 1.0f));
			}
		}
		
		if (type == "LightOmni" || type == "LightProj" || type == "LightWorld" || type == "LightVoxelProbe" || type == "LightEnvironmentProbe") {
			int num_temperature = xml.findChild("color_temperature");
			if (num_temperature == -1) {
				xmlRenameChild(xml, "color_filter", "color");
			} else {
				Xml child = xml.addChild("color_mode");
				child.setIntData(1);
			}
		}
		
		if (type == "LightOmni" || type == "LightProj" || type == "LightWorld") {
			if(xml.isChild("lens_flare_texture")) {
				Xml child = xml.getChild("lens_flare_texture");
				if (child.getData() == "core/textures/lens_flares_default.png")
					child.setData("core/textures/lens_flares_default.dds");
			}
		}
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
