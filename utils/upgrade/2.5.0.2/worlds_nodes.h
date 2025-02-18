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

/*
*/
namespace WorldsNodes {
	
	string data_catalog;
	string current_file;
	
	/*
	 */
	string get_save_name(string name) {
		if(is_file(data_catalog + name))
			return data_catalog + name;
		return findFile(data_catalog,name);
	}
	
	/*
	 */
	void rename_child(Xml xml,string from,string to) {
		
		int num = xml.findChild(from);
		
		if(num != -1) {
			xml.getChild(num).setName(to);
		}
	}
	
	/*
	 */
	void processFile(string name) {
		
		current_file = name;
		
		Xml xml = new Xml();
		
		if(!xml.load(name)) {
			delete xml;
			return;
		}
		
		string version = xml.getArg("version","1.00");
		
		Log::info("upgrading \"%s\"",name);
		xml.setArg("version",ENGINE_VERSION);
		
		if(getExtension(name) == ".world") {
			
			process_world(xml,version);
			
			Xml editor_element = xml.find("editor");
			
			if(editor_element != NULL) {
				
				for(int i = 0; i < editor_element.getNumChildren(); i++) {
					
					Xml x = editor_element.getChild(i);
					if(x.getName() == "node") {
						process_node(x,version);
						if(x == NULL) i--;
					}
				}
			}
			
			Xml render_element = xml.find("render");
			if(render_element != NULL)
				process_render(render_element,version);
		}
		
		if(getExtension(name) == ".node") {
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
				
				Xml x = xml.getChild(i);
				if(x.getName() == "node") {
					process_node(x,version);
					if(x == NULL)
						i--;
				}
			}
		}
		
		xml.save(name);
		
		delete xml;
	}
	
	/******************************************************************************\
	*
	* Nodes
	*
	\******************************************************************************/
	void process_node(Xml xml,string version) {
		
		// node type
		string type = xml.getArg("type","unknown");
		
		xml.removeArg("prefab_id");
		xml.removeArg("linked_to_prefab_id");
		xml.removeArg("prefab");
		
		if(type == "WorldSplineGraph") {
			
			int num = xml.findChild("prefab_nodes");
			if(num != -1) {
				Xml x = xml.getChild(num);
				x.setName("source_nodes");
				forloop(int i = 0; x.getNumChildren()) {
					Xml child = x.getChild(i);
					if(child.getName() == "prefab")
						child.setName("source");
				}
			}
		}
		
		if(type == "ObjectTerrainGlobal") {
			
			int num = xml.findChild("lods_height");
			if(num != -1) {
				Xml lods_height = xml.getChild(num);
				forloop(int i = 0; lods_height.getNumChildren()) {
					Xml lod = lods_height.getChild(i);
					rename_child(lod, "height_lods_intersection", "intersection");
					rename_child(lod, "height_lods_collision", "collision");
					rename_child(lod, "height_lods_intersection_mask", "intersection_mask");
					rename_child(lod, "height_lods_collision_mask", "collision_mask");
				}
			}
			
			forloop(int i = 0; xml.getNumChildren()) {
				Xml child = xml.getChild(i);
				if(child.getName() == "detail")
					rename_child(child, "mask_conrast", "mask_contrast");
			}
			
			rename_child(xml,"lods_detail_masks", "lods_masks");
			rename_child(xml,"detail_masks", "masks");
		}
		
		// processing child nodes
		for(int i = 0; i < xml.getNumChildren(); i++) {
			
			Xml x = xml.getChild(i);
			string name = x.getName();
			
			if(name == "node") {
				process_node(x,version);
				if(x == NULL) i--;
			} else if(name == "body") {
				process_body(x,version);
			}
		}
	}
	
	/******************************************************************************\
	*
	* Bodies
	*
	\******************************************************************************/
	void process_body(Xml xml,string version) {
		
	}
	
	/******************************************************************************\
	*
	* Render
	*
	\******************************************************************************/
	void process_render(Xml xml,string version) {
		
	}
	
	/******************************************************************************\
	*
	* World
	*
	\******************************************************************************/
	void process_world(Xml xml,string version) {
		
	}
	
} /* namespace WorldsNodes */

#endif /* __MIGRATION_WORLDS_NODES_H__ */
