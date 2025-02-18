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
			"node.rotationLocalXYZ": 0,
			"node.light.shadowOffset": 0,
		);
		
		string renamed[] = (
			"property.stateToggle": "property.parameterToggle",
			"property.stateSwitch": "property.parameterSwitch",
			
			"node.object.property.stateToggle": "node.object.property.parameterToggle",
			"node.object.property.stateSwitch": "node.object.property.parameterToggle",
			
			"material.alphaTest": "material.transparent",
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
