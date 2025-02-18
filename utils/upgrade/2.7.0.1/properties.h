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
	string remove_files[0];			// .prop libraries that we should remove after migration will be done

	Property properties[0];			// all properties
	Property libraries_properties[];// <String(name_property + its_library_name), Property>
	Property name_to_property[];	// <name_property, Property>
	
	string all_libraries[0];		// path to all libraries (absolute names)
	
	///////////////////////////////////////////////////////////////////////////////////////////
	// first stage of migration
	///////////////////////////////////////////////////////////////////////////////////////////
	
	void processPaths1(string in_assets_paths[], string in_data_paths[]) {
		
		Log::info("upgrading asset.prop files...");
		
		for(int j = 0; j < in_assets_paths.size(); j++) {
			// check "assets" folder
			if(!is_dir(in_assets_paths[j]))
				continue;
			
			// ok, "assets" folder is exist
			// but is exists assets.prop file in the data folder?
			string file = in_data_paths[j] + "assets.prop";
			if(!is_file(file))
				continue;
			
			// ok, properties are exist in current pair assets/data folders
			// let's start first stage of migration
			Xml xml = new Xml();
			if(!xml.load(file)) {
				delete xml;
				continue;
			}
			
			string library = absname(in_data_paths[j] + "/", file);
			if(xml.getName() == "properties") {
				
				Log::info("upgrading library \"%s\"", library);
				all_libraries.append(library);
				
				string editable = xml.isArg("editable") ? xml.getArg("editable") : "1"; // editable by default
				
				// look inside assets.prop...
				int prop_start = properties.size();
				forloop(int i = 0; xml.getNumChildren()) {
					
					Xml xml_ = xml.getChild(i); // property in assets.prop file
					
					// Plan:
					// 1) Find the same property in the "assets" folder
					// 2) Change inside it "editable" flag
					// 3) Make Property object from it
					// 4) Copy final migrated result to assets and data folders both
					
					string name = xml_.getArg("name");
					string path = findProperty(name, in_assets_paths[j]); // 1)
					
					if(name == "")
						Log::error("There is property without name in library \"%s\"!", library);
					else if(path == "")
						Log::error("Can't find property with name \"%s\" in \"assets\" folder!", name);
					else {
						// load prop in assets folder
						Xml xml_prop = new Xml();
						if(!xml_prop.load(path)) {
							delete xml_prop;
							continue;
						}
						
						// 2)
						if(editable == "0")
							xml_prop.setArg("editable", editable);
						
						// 3) add property
						Property prop = new Property(path, xml_prop);
						prop.lib = library;
						add_property(prop);
						
						if(is_file(path + ".asset")) {
							remove_file(path + ".asset");
						}
						
						// set parent (if exist)
						if(xml_prop.isArg("parent")) {
							string parent_name = xml_prop.getArg("parent");
							if(parent_name == "node_base" ||
								parent_name == "surface_base")
								prop.setManual(1); // set manual to base properties
							else {
								// find parent in current library
								forloop(int k = prop_start; properties.size()) {
									Property prev_property = properties[k];
									if(prev_property.getName() == parent_name) {
										prop.setParent(prev_property); // set
										break;
									}
								}
							}
						} else
							prop.setManual(1); // set manual to base properties
					}
				}
			}
			
			// remove assets.prop
			remove_file(file);
		}
	}
	
	string findProperty(string name, string folder) {
		string files[0] = ();
		if(!findFilesByExt(files, folder, ".prop"))
			return "";
			
		foreach(string file; files) {
			if(skipFile(folder,file))
				continue;
			
			Xml xml = new Xml();
			if(!xml.load(file)) {
				delete xml;
				continue;
			}
				
			if(xml.getName() == "property" && 
				xml.isArg("name") &&
				xml.getArg("name") == name)
				return file;
		}
		
		return "";
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////
	// second stage of migration
	///////////////////////////////////////////////////////////////////////////////////////////
	
	void processPaths2(string paths[]) {

		data_paths.copy(paths);
		
		// .prop files
		Log::info("upgrading libraries to properties ...");
		upgrading_libraries_to_properties();
		
		// find manual properties (with new parameters)
		for(int i=0; i<properties.size(); i++) {
			if(properties[i].hasUniqueParameters())
				properties[i].setManualAllParents(1); // set manual
		}
		
		// fix path duplicates
		int path_count[];
		foreach(Property property; properties) {
			string file_and_ext = property.getPath();
			string file = withoutExtension(file_and_ext);
			if(path_count.check(file)) {
				property.setPath(format("%s_%d.prop", file, path_count[file]++));
				
				string file_and_ext2 = property.path2;
				if(file_and_ext2 != "") {
					string file2 = withoutExtension(file_and_ext2);
					property.path2 = format("%s_%d.prop", file2, path_count[file] - 1);
				}
			} else
				path_count.append(file,0);
		}
		
		// guids: name
		Log::info("generate guid properties ...");
		foreach(Property property; properties) {
			string guid = propertyGUID(property);
			if(!property.isManual())
				property.setGUID(guid); // manual's doesn't have "guid" argument
		}
		
		// guids: parent
		Log::info("update guid parent properties ...");
		string parents[];
		foreach(Property property; properties) {
			
			// argument "parent" is exist?
			if(property.isBaseProperty())
				continue;
			
			// skip properties where "parent" doesn't exist
			// (but "parent_name" may be)
			string name = property.getParentGUID();
			if(name == "")
				continue;
			
			// so, there is updating NOT manual property only
			Property parent = property.getParent();
			
			// find parent in the same library as the current property
			// string name_and_lib = name + property.lib;
			// if(libraries_properties.check(name_and_lib))
			//	parent = libraries_properties[name_and_lib];
			
			// if parent exists in another library
			// if(parent == NULL && name_to_property.check(name))
			//	parent = name_to_property[name];
			
			// apply parent GUID
			if(parent != NULL && parent.isManual()) {
				// parent="manual guid"
				string guid = stringToGUID(parent.getName());
				property.setParentGUID(guid);
			} else if(parent != NULL) {
				// parent="usual name+lib guid"
				string guid = propertyGUID(parent, name);
				property.setParentGUID(guid);
				parents.append(property.getGUID(),guid);
			}
		}
		
		// .node|.world files
		Log::info("upgrading node properties to properties ...");
		upgrading_node_properties_to_properties();
		
		save();
		cleanup();
	}
	
	int upgrading_libraries_to_properties() {
		
		foreach(string data_path; data_paths) {
			string files[0] = ();
			if(!findFilesByExt(files,data_path,".prop"))
				continue;
			
			foreach(string file; files) {
				if(skipFile(data_path,file))
					continue;
				
				Xml xml = new Xml();
				if(!xml.load(file)) {
					delete xml;
					continue;
				}
				
				string library = absname(data_path + "/", file);
				
				// LIBRARY, EDITOR1
				if(xml.getName() == "properties") {
					
					string library_path = withoutExtension(file);
					
					remove_files.append(file);
					Log::info("upgrading library \"%s\"", library);
					all_libraries.append(library);
					
					int prop_start = properties.size();
					forloop(int i = 0; xml.getNumChildren()) {
						Xml xml_prop = xml.getChild(i);
						
						// copy arguments from library to property
						if(xml.isArg("version"))
							xml_prop.setArg("version", xml.getArg("version"));
						if(xml.isArg("editable") && xml.getArg("editable") == "0")
							xml_prop.setArg("editable", xml.getArg("editable"));
						
						string name = xml_prop.getArg("name");
						if(name == "")
							Log::error("There is property without name in library \"%s\"!", library);
						else {
							// path = folder where library exist + name of the property
							string path = format("%s/%s.prop", library_path, name);
							
							// add property
							Property prop = new Property(path, xml_prop);
							prop.lib = library;
							add_property(prop);
							
							// set parent (if exist)
							if(xml_prop.isArg("parent")) {
								string parent_name = xml_prop.getArg("parent");
								if(parent_name == "node_base" ||
									parent_name == "surface_base")
									prop.setManual(1); // set manual to base properties
								else {
									// find parent in current library
									forloop(int k = prop_start; properties.size()) {
										Property prev_property = properties[k];
										if(prev_property.getName() == parent_name) {
											prop.setParent(prev_property); // set
											break;
										}
									}
								}
							} else
								prop.setManual(1); // set manual to base properties
						}
					}
				}
				// SINGLE PROPERTY ASSET, EDITOR2
				else if(xml.getName() == "property") {
					
					// nothing to do? It is impossible in the migration stage?
					
					/*
					Log::info("upgrading property file \"%s\"", library);
					
					// add property
					Property prop = new Property(path, xml_prop);
					prop.lib = library;
					add_property(prop);
					*/
				}
			}
		}
	}
	
	void add_property(Property prop) {
		properties.append(prop);
		name_to_property.append(prop.getName(), prop);
		libraries_properties.append(prop.getName() + prop.lib,prop);
	}
	
	int upgrading_node_properties_to_properties() {
		
		// add both assets and data folders
		string all_paths[0];
		int is_asset[0];
		for(int i=0; i < data_paths.size(); i++) {
			all_paths.append(data_paths[i]); // data
			is_asset.append(0);
			
			string asset_path = data_paths[i] + "../assets/";
			if(is_dir(asset_path)) {
				all_paths.append(asset_path); // assets
				is_asset.append(1);
			}
		}
		
		for(int z = 0; z < all_paths.size(); z++) {
			string files[0] = ();
			if(!findFilesByExt(files,all_paths[z],".node|.world"))
				continue;
			
			foreach(string file; files) {
				if(skipFile(all_paths[z],file))
					continue;
				
				Xml xml_node = new Xml();
				if(!xml_node.load(file)) {
					delete xml_node;
					continue;
				}
				
				// store list of libraries in the beginning of the file
				string libraries[0];
				libraries.clear();
				forloop(int i = 0; xml_node.getNumChildren()) {
					Xml child = xml_node.getChild(i);
					if(child.getName() == "properties") {
						forloop(int i = 0; child.getNumChildren()) {
							string lib = child.getChild(i).getData();
							string abs_lib = absname(all_paths[z],lib);
							if(all_libraries.find(abs_lib) != -1) {
								libraries.append(abs_lib);
							} else {
								string name_lib = basename(lib);
								foreach(string path; all_libraries) {
									if(basename(path) == name_lib) {
										libraries.append(path);
										continue;
									}
								}
							}
						}
					}
				}
				// remove "properties" from the beginning of the .world/.node file
				xmlDeleteChild(xml_node, "properties");
				
				// upgrade argument property="name" in nodes/surfaces
				void upgrading_node(Xml xml) {
					
					// // //
					Property find_property(string name_property) {
						Property prop = NULL;
						
						// looking for property in the libraries that were specified in this .world/.node file
						foreach(string lib; libraries)
							if(libraries_properties.check(name_property + lib))
								prop = libraries_properties[name_property + lib];
						
						// :( try to find at least some property with a similar name
						if(prop == NULL) {
							if(name_to_property.check(name_property))
								prop = name_to_property[name_property];
						}
						
						return prop;
					}
					// // //
					
					// customer data
					if(xml.getName() == "data")
						return;
					
					Property prop = NULL;
					string name_property = "";
					
					// NODE
					if(xml.getName() == "node") {
						// find property
						int num = xml.findArg("property");
						if(num != -1) {
							name_property = xml.getArgValue(num);
							prop = find_property(name_property);
							xml.removeArg("property");
							
							// convert name to guid (find correct parent)
							string guid_property = "";
							if(name_property == "node_base" || name_property == "surface_base")
								guid_property = stringToGUID(name_property);
							else {
								if(prop != NULL)
									guid_property = prop.isManual() ? stringToGUID(prop.getName()) : propertyGUID(prop, name_property);
								else {
									guid_property = stringToGUID(name_property);
									Log::error("%s can't find property \"%s\"", file, name_property);
								}
							}
							
							// create "properties" child
							Xml xml_properties = xml.addChild("properties");
														
							// find overrides
							int num = xml.findChild("property");
							if(num != -1 && (prop != NULL)) {
								
								// fix inherited property
								Xml xp = xml.getChild(num); // <property> child
								for(int k = 0; k < xp.getNumChildren(); k++) {
									Xml x = xp.getChild(k);
									if(x.getName() == "state")
										x.setName("parameter");
								}
								
								// make copy of the parameters
								Xml xpc = xml_properties.addChild("property");
								xpc.setArg("parent", guid_property);
								xpc.setArg("guid", getRandomGUID());
								for(int k = 0; k < xp.getNumChildren(); k++) {
									Xml x = xp.getChild(k);
									Xml xc = xpc.addChild("parameter");
									xc.setData(x.getData());
									
									for(int z = 0; z < x.getNumArgs(); z++)
										xc.setArg(x.getArgName(z), x.getArgValue(z));
								}
								
								// remove old
								xml.removeChild(xp);
							} else {
								Xml xml_property = xml_properties.addChild("property");
								xml_property.setArg("parent", guid_property);
								xml_property.setArg("guid", getRandomGUID());
							}
						}
					}
					
					// SURFACE
					if(xml.getName() == "surface") {
						// find property
						int num = xml.findArg("property");
						if(num != -1) {
							name_property = xml.getArgValue(num);
							prop = find_property(name_property);
							
							// convert name to guid (find correct parent)
							if(name_property == "node_base" || name_property == "surface_base")
								xml.setArg("property", stringToGUID(name_property));
							else {
								if(prop != NULL)
									xml.setArg("property", prop.isManual() ? stringToGUID(prop.getName()) : propertyGUID(prop, name_property));
								else {
									xml.setArg("property", stringToGUID(name_property));
									Log::error("%s can't find property \"%s\"", file, name_property);
								}
							}
							
							// find overrides
							int num = xml.findChild("property");
							if(num != -1 && (prop != NULL)) {
								
								// fix inherited property
								Xml xp = xml.getChild(num);
								for(int k = 0; k < xp.getNumChildren(); k++) {
									Xml x = xp.getChild(k);
									if(x.getName() == "state")
										x.setName("parameter");
								}
							}
						}
					}
					
					forloop(int i = 0; xml.getNumChildren())
						upgrading_node(xml.getChild(i));
				}
				
				upgrading_node(xml_node);
				
				if(is_asset[z])
					xml_node.setArg("version", "2.7.0.1"); // modify asset
				xml_node.save(file);
			}
		}
		
		return true;
	}
	
	string propertyGUID(Property property, string name) {
		if(property != NULL)
			return stringToGUID(name + property.lib);
		Log::error("can't find property \"%s\"", name);
		return stringToGUID(name);
	}
	
	string propertyGUID(Property property) {
		if(property != NULL)
			return propertyGUID(property, property.getName());
		Log::error("can't find property");
		return "";
	}
	
	void save() {
		foreach(Property p; properties) {
			// change version
			if(p.getVersion() >= ENGINE_VERSION || p.getPath() == "")
				continue;
			p.setVersion(ENGINE_VERSION);
			
			// make directories for the new properties
			string dir_prop = dirname(p.getPath());
			if(!is_dir(dir_prop))
				mkdir(dir_prop);
			
			if(p.path2 != "") {
				string dir_prop = dirname(p.path2);
				if(!is_dir(dir_prop))
					mkdir(dir_prop);
			}
			
			// save to .prop files
			if(!p.save())
				Log::error("failed to save \"%s\"", p.path);
		}
		
		// remove libraries
		foreach(string file; remove_files)
			remove_file(file);
	}
	
	void cleanup() {
		properties.delete();
	}

} /* namespace Properties */

#endif /* __MIGRATION_PROPERTIES_H__ */
