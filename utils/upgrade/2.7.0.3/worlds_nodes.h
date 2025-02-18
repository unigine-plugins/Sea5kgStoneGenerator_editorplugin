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

#ifndef __MIGRATION_WORLDS_NODES_H__
#define __MIGRATION_WORLDS_NODES_H__

namespace WorldsNodes {
	
	string data_catalog;
	string current_file;
	
	string get_save_name(string name) {
		if(is_file(data_catalog + name))
			return data_catalog + name;
		return findFile(data_catalog,name);
	}
	
	void rename_child(Xml xml,string from,string to) {
		
		int num = xml.findChild(from);
		
		if(num != -1) {
			xml.getChild(num).setName(to);
		}
	}
	
	void processFile(string name) {
		
		current_file = name;
		
		Xml xml = new Xml();
		
		if(!xml.load(name)) {
			delete xml;
			return;
		}
		
		Log::info("upgrading \"%s\"",name);
		xml.setArg("version",ENGINE_VERSION);
		
		if(pathExtensionCompare(name, ".world")) {
			
			Process::world(xml);
			
			Xml editor_element = xml.find("editor");
			
			if(editor_element != NULL) {
				
				for(int i = 0; i < editor_element.getNumChildren(); i++) {
					
					Xml x = editor_element.getChild(i);
					if(x.getName() == "node") {
						processNodes(x);
						if(x == NULL) i--;
					}
				}
			}
			
			Xml render_element = xml.find("render");
			if(render_element != NULL)
				Process::render(render_element);
		} else if(pathExtensionCompare(name, ".node")) {
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
				
				Xml x = xml.getChild(i);
				if(x.getName() == "node") {
					processNodes(x);
					if(x == NULL) i--;
				}
			}
		} else if(pathExtensionCompare(name, ".render_settings")) {
			
			Xml render_element = xml.find("render");
			if(render_element != NULL)
				Process::render(render_element);
		}else if(pathExtensionCompare(name, ".settings")) {
			
			Xml render_element = xml.find("render");
			if(render_element != NULL)
				Process::render(render_element);
		}
		
		xml.save(name);
		delete xml;
	}
	
	void processNodes(Xml xml) {
		
		Process::node(xml);
		
		// processing child nodes
		for(int i = 0; i < xml.getNumChildren(); i++) {
			
			Xml x = xml.getChild(i);
			string name = x.getName();
			
			if(name == "node")
				processNodes(x);
				if(x == NULL) i--;
			else if(name == "body")
				Process::body(x);
		}
	}
	
}

#endif /* __MIGRATION_WORLDS_NODES_H__ */
