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
		
		// .prop files
		Log::info("upgrading properties ...");
		upgrading_properties();
		
		// find parents of properties
		find_parents_of_properties();
		
		// change data\sounds\sound_01.oga to guid://4cb01e72275f97 of inherited
		// properties (because base property is already changed)
		replace_path_to_guid_of_inherited_properties();
		
		// .node|.world files
		Log::info("upgrading node/world properties...");
		upgrading_node_world_properties();
		
		save();
		cleanup();
	}
	
	int upgrading_properties() {
		
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
	
	void replace_path_to_guid_of_inherited_properties() {
		foreach(Property p; properties) {
			p.migrateProperty();
		}
	}
	
	int upgrading_node_world_properties() {
		
		for(int z = 0; z < data_paths.size(); z++) {
			string files[0] = ();
			if(!findFilesByExt(files, data_paths[z], ".node|.world"))
				continue;
			
			foreach(string file; files) {
				if(skipFile(data_paths[z], file))
					continue;
				
				Xml xml_node = new Xml();
				if(!xml_node.load(file)) {
					delete xml_node;
					continue;
				}
								
				// upgrade <properties> / <property>
				void upgrading_node(Xml xml) {
					
					// customer data
					if(xml.getName() == "data")
						return;
					
					Property prop = NULL;
					
					// NODE
					if(xml.getName() == "node") {
						
						// find <properties> tag
						int num = xml.findChild("properties");
						if(num != -1) {
							Xml x = xml.getChild(num);
							
							for(int i = 0; i < x.getNumChildren(); i++)
							{
								Xml xx = x.getChild(i);
								if(xx.getName() == "property")
								{
									// find property
									string guid_name = xx.getArg("parent");
									if(guid_to_property.check(guid_name))
										prop = guid_to_property[guid_name];
									
									// check parameters
									if(prop != NULL)
									{
										for(int k = 0; k < xx.getNumChildren(); k++)
										{
											Xml xp = xx.getChild(k);
											if(prop.getParameterType(xp.getArg("name")) == "file")
											{
												// migrate path to guid!
												string path = xp.getData();
												if(strlen(path) > 1) {
													UGUID guid = FileSystem::getFastGUID(path);
													if(guid == NULL)
														guid = FileSystem::getGUID(path, false);
													
													if(guid != NULL && !guid.isEmpty())
														xml.setData(guid.getFileSystemString());
												}
											}
										}
									}
								}
							}
						}
					}
					
					// SURFACE
					if(xml.getName() == "surface") {
						
						// find <property> tag
						int num = xml.findChild("property");
						if(num != -1) {
							Xml x = xml.getChild(num);
							
							// find property
							string guid_name = xml.getArg("property");
							if(guid_to_property.check(guid_name))
								prop = guid_to_property[guid_name];
							
							// check parameters
							if(prop != NULL)
							{
								for(int k = 0; k < x.getNumChildren(); k++)
								{
									Xml xp = x.getChild(k);
									if(prop.getParameterType(xp.getArg("name")) == "file")
									{
										// migrate path to guid!
										string path = xp.getData();
										if(strlen(path) > 1) {
											UGUID guid = FileSystem::getFastGUID(path);
											if(guid == NULL)
												guid = FileSystem::getGUID(path, false);
											
											if(guid != NULL && !guid.isEmpty())
												xml.setData(guid.getFileSystemString());
										}
									}
								}
							}
						
						}
						
					}
					
					forloop(int i = 0; xml.getNumChildren())
						upgrading_node(xml.getChild(i));
				}
				
				upgrading_node(xml_node);
				
				// save .node/.world files
				xml_node.save(file);
			}
		}
		
		return true;
	}
	
	void save() {
		foreach(Property p; properties) {
			// change version
			if(p.getVersion() >= ENGINE_VERSION || p.getPath() == "")
				continue;
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
