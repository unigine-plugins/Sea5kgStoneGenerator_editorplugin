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

#ifndef __MIGRATION_MATERIALS_H__
#define __MIGRATION_MATERIALS_H__


#include <material.h>

namespace Materials {
	
	string data_paths[0];
	string remove_files[0];
	string core_materials[0];
	string addons_materials[0];
	
	Material materials[0];
	Material libraries_materials[];
	Material name_to_material[];
	
	Material base_materials[];
	
	string all_libraries[0];
	
	void add_material(Material mat) {
		materials.append(mat);
		name_to_material.append(mat.getName(), mat);
		libraries_materials.append(mat.getName() + mat.lib,mat);
		
		if(mat.isBaseMaterial())
			base_materials.append(mat.getName(), mat);
	}
	
	string materialGUID(Material material, string name) {
		if(material != NULL)
			return stringToGUID(name + material.lib);
		Log::error("can't find material \"%s\"", name);
		return stringToGUID(name);
	}
	
	string materialGUID(Material material) {
		if(material != NULL)
			return materialGUID(material, material.getName());
		Log::error("can't find material");
		return "";
	}
	
	void processPaths(string paths[]) {
		
		data_paths.copy(paths);
		
		Log::info("upgrading materials...");
		
		void _load_materials(string path, string container[]) {
			Xml xml = new Xml();
			if(xml.load(pathname(replace(__FILE__,"\\","/")) + path)) {
				forloop(int i = 0; xml.getNumChildren()) {
					Xml xml_mat = xml.getChild(i);
					add_material(new Material("", xml_mat));
					container.append(xml_mat.getArg("name"));
				}
			}
		}
		
		_load_materials("core_base_materials.xml", core_materials);
		_load_materials("core_override_materials.xml", core_materials);
		_load_materials("addons_base_materials.xml", addons_materials);
		
		Log::info("upgrading libraries to materials ...");
		upgrading_libraries_to_materials();
		
		Log::info("upgrading node materials to materials ...");
		upgrading_node_materials_to_materials();
		
		Log::info("generate guid materials ...");
		Material guid_to_name[];
		foreach(Material material; materials) {
			string guid = materialGUID(material);
			if(!material.isBaseMaterial())
				material.setGUID(guid);
			guid_to_name.append(guid, material.getName());
		}
		
		Log::info("update guid parent materials ...");
		string parents[];
		foreach(Material material; materials) {
			
			if(material.isBaseMaterial())
				continue;
			
			string name = material.getParentGUID();
			if(name == "")
				continue;
			
			Material parent = NULL;
			
			string name_lb = name + material.lib;
			if(libraries_materials.check(name_lb))
				parent = libraries_materials[name_lb];
			
			if(parent == NULL && name_to_material.check(name))
				parent = name_to_material[name];
			
			string guid = materialGUID(parent, name);
			material.setParentGUID(guid);
			parents.append(material.getGUID(),guid);
		}
		
		Log::info("update base materials ...");
		foreach(Material material; materials) {
			if(material.isBaseMaterial()) {
				foreachkey(string name; material.parameters)
					material.parameters[name].xml.removeArg("log10");
				
				Xml xml = material.xml;
				forloop(int i = 0; xml.getNumChildren()) {
					Xml xml_child = xml.getChild(i);
					string xml_name = xml_child.getName();
					
					int is_bind = xml_name == "bind";
					int is_shader = xml_name == "shader";
					
					if(is_shader || is_bind) {
						
						int num = xml_child.findArg("object");
						if(num != -1) {
							xml_child.setArgName(num, "node");
							xml_child.setArgValue(num, "object_" + xml_child.getArgValue(num));
							
							if(is_bind) {
								num = xml_child.findArg("to");
								if(num != -1)
									xml_child.setArgValue(num, "object_" + xml_child.getArgValue(num));
							}
						}
						
						num = xml_child.findArg("decal");
						if(num != -1) {
							xml_child.setArgName(num, "node");
							xml_child.setArgValue(num, "decal_" + xml_child.getArgValue(num));
							if(is_bind) {
								num = xml_child.findArg("to");
								if(num != -1)
									xml_child.setArgValue(num, "decal_" + xml_child.getArgValue(num));
							}
						}
					}
				}
			}
		}
		
		Log::info("update materials ...");
		foreach(Material material; materials) {
			if(!material.isBaseMaterial()) {
				
				string base_material = material.getParentGUID();
				while(base_material != "" && parents.check(base_material))
					base_material = parents[base_material];
				
				if(base_material == material.getParentGUID())
					xmlRemoveArg(material.xml, "parent");
				
				while (material.xml.isChild("bind"))
					material.xml.removeChild("bind");
				
				if(guid_to_name.check(base_material))
					base_material = guid_to_name[base_material];
				
				material.setBaseMaterial(base_material);
				
				if(base_materials.check(base_material)) {
					Material base_mat = base_materials[base_material];
					
					foreachkey(string name; material.states) {
						if(!base_mat.hasState(name))
							material.removeState(name);
						else
							material.states[name].xml.removeArg("hidden");
					}
					
					foreachkey(string name; material.textures) {
						if(!base_mat.hasTexture(name))
							material.removeTexture(name);
						else
							material.textures[name].xml.removeArg("hidden");
					}
					
					foreachkey(string name; material.parameters) {
						if(!base_mat.hasParameter(name))
							material.removeParameter(name);
						else
							material.parameters[name].xml.removeArg("hidden");
					}
				} else
					Log::error("can't find base material: %s", base_material);
				
			}
		}
		
		int name_count[];
		foreach(Material material; materials) {
			string name = material.getName();
			if(name_count.check(name))
				material.setName(format("%s_%d", name, name_count[name]++));
			else
				name_count.append(name,0);
		}
		
		save();
		cleanup();
	}
	
	int upgrading_libraries_to_materials() {
		
		foreach(string data_path; data_paths) {
			string files[0] = ();
			if(!findFilesByExt(files,data_path,".mat"))
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
				
				if(xml.getName() == "materials") {
					
					string library_path = withoutExtension(file);
					
					remove_files.append(file);
					Log::info("upgrading library \"%s\"", library);
					all_libraries.append(library);
					
					forloop(int i = 0; xml.getNumChildren()) {
						Xml xml_mat = xml.getChild(i);
						if(xml.isArg("version"))
							xml_mat.setArg("version", xml.getArg("version"));
						if(xml.isArg("editable"))
							xml_mat.setArg("editable", xml.getArg("editable"));
						
						string name = xml_mat.getArg("name");
						if(name == "")
							name = "empty";
						
						string path = format("%s/%s.mat", library_path, name);
						
						if(!xml_mat.isArg("parent") || xml_mat.isChild("shader")) {
							xml_mat.setName("base_material");
							path = format("%s/%s.basemat", library_path, name);
						}
						
						Material mat = new Material(path, xml_mat);
						mat.lib = library;
						add_material(mat);
					}
				}
			}
		}
	}
	
	int upgrading_node_materials_to_materials() {
		
		int override_material_count[];
		
		foreach(string data_path; data_paths) {
			string files[0] = ();
			if(!findFilesByExt(files,data_path,".node|.world"))
				continue;
			
			foreach(string file; files) {
				if(skipFile(data_path,file))
					continue;
				
				Xml xml_node = new Xml();
				if(!xml_node.load(file)) {
					delete xml_node;
					continue;
				}
				
				string libraries[0];
				libraries.clear();
				forloop(int i = 0; xml_node.getNumChildren()) {
					Xml child = xml_node.getChild(i);
					if(child.getName() == "materials") {
						forloop(int i = 0; child.getNumChildren()) {
							string lib = child.getChild(i).getData();
							string abs_lib = absname(data_path,lib);
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
				xmlDeleteChild(xml_node, "materials");
				
				string materials_path = withoutExtension(file) + "_materials";
				
				void upgrading_node(Xml xml) {
					
					Material create_material(Xml xml, string name_material, Material parent) {
						
						if(name_material == "")
							name_material = "empty";
						
						Xml xml_mat = new Xml();
						xml_mat.copy(xml);
						
						xml_mat.setArg("parent", parent.getName());
						
						if(parent.isBaseMaterial()) {
							xml_mat.setArg("base_material", parent.getName());
							xml_mat.setArg("version", "2.5.0.1");
						} else {
							xml_mat.setArg("base_material", parent.getBaseMaterial());
							xml_mat.setArg("version", parent.getVersion());
						}
						
						if(!override_material_count.check(name_material))
							override_material_count.append(name_material, 0);
						else {
							int count = (override_material_count[name_material]++);
							name_material = format("%s_%d", name_material, count);
						}
						
						xml_mat.setArg("name", name_material);
						
						string path = format("%s/%s.mat",materials_path, name_material);
						
						Material material = new Material(path, xml_mat);
						material.lib = parent.lib;
						add_material(material);
						return material;
					}
					
					Material find_material(string name_material) {
						Material mat = NULL;
						foreach(string lib; libraries)
							if(libraries_materials.check(name_material + lib))
								mat = libraries_materials[name_material + lib];
						
						if(mat == NULL) {
							if(name_to_material.check(name_material))
								mat = name_to_material[name_material];
						}
						
						return mat;
					}
					
					if(xml.getName() == "data")
						return;
					
					Material mat = NULL;
					string name_material = "";
					
					if(xml.getName() == "node") {
						string node_type = xml.getArg("type", "");
						int is_decal = node_type == "DecalProj" || node_type == "DecalOrtho" || node_type == "DecalMesh";
						
						int num = xml.findChild("material");
						if(num != -1 && is_decal) {
							Xml xml_mat = xml.getChild(num);
							num = xml_mat.findArg("name");
							if(num != -1) {
								name_material = xml_mat.getArgValue(num);
								mat = find_material(name_material);
								if(mat != NULL) {
									string name_new_material = xml.getArg("name", node_type);
									mat = create_material(xml_mat, name_new_material, mat);
									name_material = mat.getName();
								}
							} else {
								name_material = xml_mat.getData();
								mat = find_material(name_material);
							}
						}
					} else if(xml.getName() == "surface") {
						int num = xml.findArg("material");
						if(num != -1) {
							name_material = xml.getArgValue(num);
							mat = find_material(name_material);
							
							int num = xml.findChild("material");
							if(num != -1 && (mat != NULL)) {
								string name_surface = xml.getArg("name", "");
								string name_node_type = xml.getParent().getArg("type", "");
								string name_node = xml.getParent().getArg("name", name_node_type);
								string name_new_material = format("%s_%s", name_node, name_surface);
								
								mat = create_material(xml.getChild(num), name_new_material, mat);
								name_material = mat.getName();
							}
						}
					} else if(xml.getName() == "billboard") {
						int num = xml.findArg("material");
						if(num != -1) {
							name_material = xml.getArgValue(num);
							mat = find_material(name_material);
							
							int num = xml.findChild("material");
							if(num != -1 && (mat != NULL)) {
								string name_node_type = xml.getParent().getArg("type", "");
								string name_node = xml.getParent().getArg("name", name_node_type);
								string name_new_material = name_node;
								
								mat = create_material(xml.getChild(num), name_new_material, mat);
								name_material = mat.getName();
							}
						}
					}
					
					if(name_material != "") {
						xmlDeleteChild(xml,"material");
						if(mat != NULL)
							xml.setArg("material", materialGUID(mat, name_material));
						else {
							xml.setArg("material", stringToGUID(name_material));
							Log::error("%s can't find material \"%s\"",file, name_material);
						}
					}
					
					forloop(int i = 0; xml.getNumChildren())
						upgrading_node(xml.getChild(i));
				}
				
				upgrading_node(xml_node);
				
				xml_node.save(file);
			}
		}
		
		return true;
	}
	
	void upgrade() {
		foreach(Material m; materials) {
			if(m.getVersion() >= ENGINE_VERSION || m.getPath() == "")
				continue;
		}
	}
	
	void save() {
		foreach(Material m; materials) {
			if(m.getVersion() >= ENGINE_VERSION || m.getPath() == "")
				continue;
			m.setVersion(ENGINE_VERSION);
			
			string dir_mat = dirname(m.getPath());
			if(!is_dir(dir_mat))
				mkdir(dir_mat);
			
			if(!m.save())
				Log::error("failed to save \"%s\"", m.path);
		}
		
		foreach(string file; remove_files)
			remove_file(file);
	}
	
	void cleanup() {
		materials.delete();
	}

} /* namespace Materials */

#endif /* __MIGRATION_MATERIALS_H__ */
