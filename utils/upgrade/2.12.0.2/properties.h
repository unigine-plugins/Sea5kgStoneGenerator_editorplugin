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

#ifndef __MIGRATION_PROPERTIES_H__
#define __MIGRATION_PROPERTIES_H__

#include <property.h>

namespace Properties {
	
	string data_paths[0];			// paths to all files in data folder (.prop|.mat|.cfg...)
	Property properties[0];			// all properties
	Property guid_to_property[];	// <guid_property, Property>
	
	void processPaths(string paths[]) {
		
		data_paths.copy(paths);

		Log::info("migrate properties ...");
		
		// migrate .prop files and load it to the Property objects
		load_properties();
		
		// find parents of properties
		find_parents_of_properties();
		
		// migrate property objects
		foreach(Property p; properties) {
			Process::property(p);
		}
		
		// save and cleanup
		save();
		cleanup();
	}
	
	int load_properties() {
		
		foreach(string data_path; data_paths) {
			string files[0] = ();
			if(!findFilesByExt(files, data_path, ".prop"))
				continue;
			
			foreach(string file; files) {
				if(skipFile(data_path, file))
					continue;
				
				Xml xml = new Xml();
				if(!xml.load(file)) {
					delete xml;
					continue;
				}
				
				// migrate XML file
				Process::propertyFile(xml);
				
				// add property
				if(xml.getName() == "property") {
					string prop_path = absname(data_path + "/", file);
					Property prop = new Property(prop_path, xml);
					add_property(prop);
				}
			}
		}
	}
	
	void add_property(Property prop) {
		properties.append(prop);
		guid_to_property.append(prop.getGUID(), prop);
	}
	
	void find_parents_of_properties() {
		foreach(Property p; properties) {
			
			Property prop = NULL;
			string guid_name = p.getParentGUID();
			if(guid_to_property.check(guid_name))
				prop = guid_to_property[guid_name];
			
			if(prop != NULL)
				p.setParent(prop);
		}
	}
	
	void save() {
		foreach(Property p; properties) {

			p.setVersion(ENGINE_VERSION);
			
			// save .prop files
			if(!p.save())
				Log::error("failed to save \"%s\"", p.path);
		}
	}
	
	void cleanup() {
		properties.delete();
	}

} /* namespace Properties */

#endif /* __MIGRATION_PROPERTIES_H__ */
