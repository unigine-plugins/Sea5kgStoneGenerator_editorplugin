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
	
	/*
	 */
	string WORLD_VERSION = "2.5.0.1";
	
	/*
	 */
	string data_catalog;
	string current_file;
	
	string flipped_heights_images[];
	
	/*
	 */
	void processPath(string path) {
		
		data_catalog = path;
		
		string files[0] = ();
		findFiles(files,data_catalog);
		
		foreach(string file; files) {
			
			if(skipFile(path,file)) continue;
			
			string ext = lower(getExtension(file));
			
			if(ext == ".node" || ext == ".world") {
				process_file(file);
			}
		}
	}
	
	/*
	 */
	string get_save_name(string name) {
		if(is_file(data_catalog + name)) {
			return data_catalog + name;
		}
		return findFile(data_catalog,name);
	}
	
	/*
	 */
	void process_file(string name) {
		
		current_file = name;
		
		Xml xml = new Xml();
		
		if(!xml.load(name)) {
			delete xml;
			return;
		}
		
		string version = xml.getArg("version","1.00");
		if(version >= WORLD_VERSION) {
			delete xml;
			return;
		}
		
		xml.setArg("version",WORLD_VERSION);
		
		Log::info("upgrading \"%s\"",name);
		
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
			if(render_element != NULL) {
				process_render(render_element,version);
			}
		}
		
		if(getExtension(name) == ".node") {
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
				
				Xml x = xml.getChild(i);
				if(x.getName() == "node") {
					process_node(x,version);
					if(x == NULL) i--;
				}
			}
		}
		
		xml.save(name);
		delete xml;
	}
	
	/*
	 */
	void delete_child(Xml xml,string name) {
		if(xml.isChild(name)) {
			delete xml.removeChild(name);
		}
	}
	
	/*
	 */
	void update_child_value(Xml xml,string name,string value) {
		
		int num = xml.findChild(name);
		
		if(num != -1) {
			xml.getChild(num).setData(value);
		}
	}
	
	/*
	 */
	void set_child_value(Xml xml,string name,string value) {
		
		int num = xml.findChild(name);
		
		if(num != -1) {
			xml.getChild(num).setData(value);
		} else {
			xml.setChildData(name,value);
		}
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
	void remove_arg(Xml xml,string arg) {
		if(xml.isArg(arg)) {
			xml.removeArg(arg);
		}
	}
	
	/******************************************************************************\
	*
	* Nodes
	*
	\******************************************************************************/
	
	/*
	 */
	void process_node(Xml xml,string version) {
		
		// node type
		string type = xml.getArg("type","unknown");
		
		/* 20140709
		 */
		if(version < "1.20") {
			
			// immovable argument
			remove_arg(xml,"immovable");
			
			// object surfaces
			if(startsWith(type,"Object")) {
				forloop(int i = 0; xml.getNumChildren()) {
					Xml x = xml.getChild(i);
					string name = x.getName();
					if(name == "surface") {
						remove_arg(x,"max_shadow_split");
					}
				}
			}
			
			// ObjectMesh to ObjectMeshStatic
			if(type == "ObjectMesh") {
				xml.setArg("type","ObjectMeshStatic");
			}
			
			// ObjectMesh <mesh> to <mesh_name>
			if(type == "ObjectMesh" || type == "ObjectMeshCluster" || type == "ObjectMeshClutter" || type == "ObjectGuiMesh") {
				if(xml.isChild("mesh")) xml.getChild("mesh").setName("mesh_name");
			}
			
			// ObjectGui <gui> to <gui_name>
			if(type == "ObjectGui" || type == "ObjectGuiMesh") {
				if(xml.isChild("gui")) xml.getChild("gui").setName("gui_name");
			}
			
			// ObjectTerrain <terrain> to <terrain_name>
			if(type == "ObjectTerrain") {
				if(xml.isChild("terrain")) xml.getChild("terrain").setName("terrain_name");
				if(xml.isChild("flatness_threshold")) {
					Log::warning("ObjectTerrain <flatness_threshold> can't be recalculated");
					delete xml.removeChild("flatness_threshold");
				}
			}
			
			// ObjectMeshSkinned <mesh> to <mesh_name>, <animation> to <anim_name>
			if(type == "ObjectMeshSkinned") {
				if(xml.isChild("mesh")) {
					Xml x = xml.getChild("mesh");
					x.setData(getNewFileName(x.getData()));
					x.setName("mesh_name");
				}
				if(xml.isChild("animation")) {
					Xml x = xml.getChild("animation");
					x.setData(getNewFileName(x.getData()));
					x.setName("anim_name");
				}
			}
			
			// ObjectMeshDynamic interleaved to multiple arrays
			if(type == "ObjectMeshDynamic" || type == "ObjectWaterMesh") {
				if(xml.isChild("vertex")) {
					Xml x = xml.getChild("vertex");
					int num_vertex = x.getArg("num_vertex",0);
					float src[0];
					x.getFloatArrayData(src);
					if(src.size() == num_vertex * 14) {
						delete xml.removeChild(x);
						float vertex[0],texcoord[0],tangent[0];
						forloop(int i = 0; num_vertex) {
							int j = i * 14;
							vertex.append(src[j + 0]);
							vertex.append(src[j + 1]);
							vertex.append(src[j + 2]);
							texcoord.append(src[j + 3]);
							texcoord.append(src[j + 4]);
							texcoord.append(src[j + 5]);
							texcoord.append(src[j + 6]);
							vec3 n = vec3(src[j + 7],src[j + 8],src[j + 9]);
							vec4 t = vec4(src[j + 10],src[j + 11],src[j + 12],src[j + 13]);
							t = orthoTangent(t,n);
							tangent.append(t.x);
							tangent.append(t.y);
							tangent.append(t.z);
							tangent.append(t.w);
						}
						xml.addChild("vertex",format("type=float num_vertex=%d offset=0 size=3",num_vertex)).setFloatArrayData(vertex);
						xml.addChild("vertex",format("type=float num_vertex=%d offset=16 size=4",num_vertex)).setFloatArrayData(texcoord);
						xml.addChild("vertex",format("type=float num_vertex=%d offset=32 size=4",num_vertex)).setFloatArrayData(tangent);
					} else {
						Log::error("can't upgrade %s",type);
					}
				}
			}
			
			// ObjectDynamic <dynamic> to <flags>
			if(type == "ObjectDynamic" || type == "ObjectMeshDynamic") {
				if(xml.isChild("dynamic")) {
					Xml x = xml.getChild("dynamic");
					int data = x.getIntData();
					if(data) x.setIntData(3);
					else x.setIntData(0);
					x.setName("flags");
				}
			}
			
			// DecalDeferredMesh interleaved to multiple arrays
			if(type == "DecalDeferredMesh") {
				if(xml.isChild("vertex")) {
					Xml x = xml.getChild("vertex");
					int num_vertex = x.getArg("num_vertex",0);
					float src[0];
					x.getFloatArrayData(src);
					if(src.size() == num_vertex * 12) {
						float vertex[0],texcoords[0],tangents[0];
						forloop(int i = 0; num_vertex) {
							int j = i * 12;
							vertex.append(src[j + 0]);
							vertex.append(src[j + 1]);
							vertex.append(src[j + 2]);
							texcoords.append(src[j + 3]);
							texcoords.append(src[j + 4]);
							texcoords.append(0.0f);
							texcoords.append(0.0f);
							vec3 n = vec3(src[j + 5],src[j + 6],src[j + 7]);
							vec4 t = vec4(src[j + 8],src[j + 9],src[j + 10],src[j + 11]);
							t = orthoTangent(t,n);
							tangents.append(t.x);
							tangents.append(t.y);
							tangents.append(t.z);
							tangents.append(t.w);
						}
						x.setData("");
						x.addChild("vertex").setFloatArrayData(vertex);
						x.addChild("texcoords").setFloatArrayData(texcoords);
						x.addChild("tangents").setFloatArrayData(tangents);
					} else {
						Log::error("can't upgrade %s",type);
					}
				}
			}
			
			// WorldTransform <spline> to <path_name>
			if(type == "WorldTransform") {
				if(xml.isChild("spline")) {
					Xml x = xml.getChild("spline");
					x.setData(replace(x.getData(),".spline",".path"));
					x.setName("path_name");
				}
			}
			
			// SoundSource <sample> to <sample_name>, <stream> to <sample_stream>
			if(type == "SoundSource") {
				if(xml.isChild("sample")) xml.getChild("sample").setName("sample_name");
				if(xml.isChild("stream")) xml.getChild("stream").setName("sample_stream");
			}
		}
		
		/* 20140721
		 */
		if(version < "1.21") {
			
			// ObjectTerrain materials
			if(type == "ObjectTerrain") {
				
				string diffuse_textures[0];
				string normal_textures[0];
				
				string surface_masks[0];
				ivec4 surface_materials[0];
				
				// create material texture
				int create_texture_array(string names[],string &name) {
					if(is_file(dirname(get_save_name(names[0])) + name)) {
						name = dirname(names[0]) + name;
						return 1;
					}
					Log::info("creating \"%s\" texture",dirname(get_save_name(names[0])) + name);
					int width = -1;
					int height = -1;
					int format = -1;
					int mipmaps = -1;
					Image image = class_manage(new Image());
					foreach(string name; names) {
						if(strlen(name) == 0) continue;
						if(image.info(get_save_name(name)) == 0) continue;
						if(image.getType() != IMAGE_2D) {
							Log::error("wrong \"%s\" texture type %s",name,image.getTypeName());
							continue;
						}
						width = max(width,image.getWidth());
						height = max(height,image.getHeight());
						format = max(format,image.getFormat());
						mipmaps = max(mipmaps,image.getNumMipmaps());
					}
					if(width == -1 || height == -1 || format == -1 || mipmaps == -1) return 0;
					image.create2DArray(width,height,names.size(),format,mipmaps);
					Image src = class_manage(new Image());
					forloop(int i = 0; names.size()) {
						string name = names[i];
						if(strlen(name) == 0) continue;
						if(src.load(get_save_name(name)) == 0) continue;
						if(src.getType() != IMAGE_2D) continue;
						if(src.resize(width,height) == 0 && (src.decompress() == 0 || src.resize(width,height) == 0)) continue;
						if(src.getNumMipmaps() != mipmaps && src.createMipmaps() == 0) continue;
						if(src.convertToFormat(format) == 0) continue;
						image.copy(src,i);
					}
					int saved = image.save(dirname(get_save_name(names[0])) + name);
					name = dirname(names[0]) + name;
					return saved;
				}
				
				// index texture name
				string get_index_name(Xml xml) {
					string name = xml.getChildData("diffuse_texture","");
					name = xml.getChildData("normal_texture",name);
					name = xml.getChildData("mask_texture",name);
					name = re_replace(name,"_d|_n|_m","_i");
					return name;
				}
				
				// create index texture
				int create_index_texture(string name,ivec4 material) {
					Image image = class_manage(new Image());
					if(material.w != -1) image.create2D(4,4,IMAGE_FORMAT_RGBA8);
					else if(material.z != -1) image.create2D(4,4,IMAGE_FORMAT_RGB8);
					else if(material.y != -1) image.create2D(4,4,IMAGE_FORMAT_RG8);
					else if(material.x != -1) image.create2D(4,4,IMAGE_FORMAT_R8);
					if(material.x != -1) image.set(0,material.x);
					if(material.y != -1) image.set(1,material.y);
					if(material.z != -1) image.set(2,material.z);
					if(material.w != -1) image.set(3,material.w);
					return image.isLoaded() && image.save(name);
				}
				
				// terrain material
				if(xml.isChild("material")) {
					Xml x = xml.getChild("material");
					
					// process materials
					forloop(int i = 0; x.getNumChildren()) {
						Xml xml = x.getChild(i);
						string name = xml.getName();
						
						// material
						if(name == "material") {
							if(xml.isChild("detail")) {
								int detail = xml.getChildData("detail",0);
								if(detail == 2) xml.setChildData("overlap",1);
								delete xml.removeChild("detail");
							}
							if(xml.isChild("overlap_value")) xml.getChild("overlap_value").setName("mask_value");
							if(xml.isChild("overlap_threshold")) xml.getChild("overlap_threshold").setName("mask_threshold");
							diffuse_textures.append(xml.getChildData("diffuse_texture",""));
							normal_textures.append(xml.getChildData("normal_texture",""));
						}
						// surface
						else if(name == "surface") {
							ivec4 materials = ivec4(-1);
							if(xml.isChild("materials")) {
								string data[0];
								Xml x = xml.getChild("materials");
								x.getStringArrayData(data);
								forloop(int j = 0; min(x.getArg("num",4),data.size())) {
									materials[j] = int(data[j]);
								}
								delete xml.removeChild("materials");
							}
							surface_masks.append(xml.getChildData("mask_texture",""));
							surface_materials.append(materials);
						}
					}
					
					// create index textures
					if(surface_materials.size()) {
						int counter[0];
						ivec4 histogram[0];
						foreach(ivec4 material; surface_materials) {
							int index = histogram.find(material);
							if(index == -1) {
								histogram.append(material);
								counter.append(-1);
							} else {
								counter[index]--;
							}
						}
						counter.sort(histogram);
						ivec4 material = ivec4(-1);
						if(counter[0] < -1) {
							material = histogram[0];
							string name = get_index_name(x);
							string path = data_catalog + name;
							if(create_index_texture(path,material)) {
								Log::info("creating \"%s\" texture for %d surfaces %s",path,-counter[0],string(material));
								x.setChildData("index_texture",name);
							}
						}
						// process materials
						forloop(int i = 0, j = 0; x.getNumChildren()) {
							Xml xml = x.getChild(i);
							string name = xml.getName();
							if(name == "surface") {
								if(surface_materials[j] != material) {
									string name = get_index_name(xml);
									string path = data_catalog + name;
									if(create_index_texture(path,surface_materials[j])) {
										Log::info("Creating \"%s\" texture %s",path,string(surface_materials[j]));
										xml.setChildData("index_texture",name);
									}
								}
								j++;
							}
						}
					}
					
					// create material textures
					if(diffuse_textures.size()) {
						string name = "terrain_array_d.dds";
						if(create_texture_array(diffuse_textures,name)) x.setChildData("diffuse_texture_array",name);
					}
					if(normal_textures.size()) {
						string name = "terrain_array_n.dds";
						if(create_texture_array(normal_textures,name)) x.setChildData("normal_texture_array",name);
					}
				}
				
				// terrain material
				if(xml.isChild("surface")) {
					Xml x = xml.getChild("surface");
					if(x.isChild("material")) delete x.removeChild("material");
				}
			}
		}
		
		/* 20150827
		 */
		if(version < "2.0") {
			
			// object surfaces
			if(startsWith(type,"Object")) {
				forloop(int i = 0; xml.getNumChildren()) {
					Xml x = xml.getChild(i);
					string name = x.getName();
					if(name == "surface") {
						remove_arg(x,"decal");
						remove_arg(x,"decal_mask");
						remove_arg(x,"receive_shadow");
						remove_arg(x,"receive_world_shadow");
					}
				}
			}
			
			// lights
			if(type == "LightWorld" || type == "LightOmni" || type == "LightProj") {
				
				delete_child(xml,"deferred_distance");
				delete_child(xml,"deferred");
				delete_child(xml,"diffuse_scale");
				delete_child(xml,"normal_scale");
				delete_child(xml,"specular_scale");
				delete_child(xml,"specular_power");
				delete_child(xml,"shadow_ambient");
				delete_child(xml,"translucent");
				delete_child(xml,"translucent_size");
				delete_child(xml,"translucent_bias");
			}
			
			if(type == "LightSpot") {
				
				xml.setArg("type","LightOmni");
				
				string name = xml.getArg("name","LightSpot");
				name = replace(name,"LightSpot","LightOmni");
				xml.setArg("name",name);
				
				if(xml.isChild("radius")) {
					string radius = xml.getChildData("radius","10");
					radius = format("%s %s %s",radius,radius,radius);
					update_child_value(xml,"radius",radius);
				}
				
				set_child_value(xml,"shadow","0");
				
				delete_child(xml,"deferred_distance");
				delete_child(xml,"deferred");
				delete_child(xml,"diffuse_scale");
				delete_child(xml,"specular_scale");
				delete_child(xml,"specular_power");
			}
			
			if(type == "LightProb") {
				
				if(xml.isChild("node")) {
					
					xml.setArg("type","NodeDummy");
					
					delete_child(xml,"deferred_distance");
					delete_child(xml,"radius");
					delete_child(xml,"coefficients");
					delete_child(xml,"light_mask");
					delete_child(xml,"viewport_mask");
					delete_child(xml,"color");
					delete_child(xml,"multiplier");
					delete_child(xml,"shadow");
				} else {
					
					delete xml.getParent().removeChild(xml);
					return;
				}
			}
			
			// decals
			if(type == "DecalObjectOmni") {
				
				xml.setArg("type","NodeDummy");
				
				remove_arg(xml,"dynamic");
				remove_arg(xml,"two_sided");
				
				string transform = xml.getChildData("transform","");
				
				string properties[] = (
					"viewport_mask": "",
					"radius": "",
					"znear": "",
					"life_time": "",
					"fade_time": "",
					"min_visible_distance": "",
					"min_fade_distance": "",
					"max_visible_distance": "",
					"max_fade_distance": "",
					"texcoord": "",
					"material": "",
				);
				
				Xml children_nodes[0] = ();
				
				for(int i = 0; i < xml.getNumChildren(); i++) {
					
					Xml x = xml.getChild(i);
					
					if(x.getName() == "node") {
						children_nodes.append(x);
						xml.removeChild(x);
						i--;
					} else if(properties.check(x.getName())) {
						properties[x.getName()] = x.getData();
					}
				}
				
				xml.clearChildren();
				
				if(transform != "") xml.setChildData("transform",transform);
				
				string transforms[0] = (
					"1 0 0 0.0 0 1 0 0.0 0 0 1 0.0 0 0 0 1.0",
					"1 0 0 0.0 0 0 1 0.0 0 -1 0 0.0 0 0 0 1.0",
					"1 0 0 0.0 0 0 -1 0.0 0 1 0 0.0 0 0 0 1.0",
					"0 0 -1 0.0 0 1 0 0.0 1 0 0 0.0 0 0 0 1.0",
					"0 0 1 0.0 0 1 0 0.0 -1 0 0 0.0 0 0 0 1.0",
					"1 0 0 0.0 0 -1 0 0.0 0 0 -1 0.0 0 0 0 1.0",
				);
				
				foreach(string t; transforms) {
					Xml proj = xml.addChild("node");
					proj.setArg("type","DecalProj");
					proj.setChildData("transform",t);
					proj.setChildData("fov","90");
					proj.setChildData("aspect","1");
					foreachkey(string p; properties) {
						if(properties[p] != "") proj.setChildData(p,properties[p]);
					}
				}
				
				foreach(Xml x; children_nodes) {
					xml.addChild(class_remove(x));
				}
			}
			
			if(type == "DecalObjectProj") {
				
				xml.setArg("type","DecalProj");
				
				remove_arg(xml,"dynamic");
				remove_arg(xml,"two_sided");
				delete_child(xml,"decal_mask");
				delete_child(xml,"light_mask");
				delete_child(xml,"offset");
				delete_child(xml,"object_decal");
			}
			
			if(type == "DecalTerrainProj" || type == "DecalDeferredProj") {
				
				xml.setArg("type","DecalProj");
				
				delete_child(xml,"decal_mask");
				delete_child(xml,"light_mask");
			}
			
			if(type == "DecalObjectOrtho") {
				
				xml.setArg("type","DecalOrtho");
				
				remove_arg(xml,"dynamic");
				remove_arg(xml,"two_sided");
				delete_child(xml,"decal_mask");
				delete_child(xml,"light_mask");
				delete_child(xml,"offset");
				delete_child(xml,"object_decal");
			}
			
			if(type == "DecalTerrainOrtho" || type == "DecalDeferredOrtho") {
				
				xml.setArg("type","DecalOrtho");
				
				delete_child(xml,"decal_mask");
				delete_child(xml,"light_mask");
			}
			
			if(type == "DecalDeferredMesh") {
				
				xml.setArg("type","DecalMesh");
				
				delete_child(xml,"decal_mask");
				delete_child(xml,"light_mask");
			}
			
			//
			if(type == "ObjectGrass" || type == "ObjectMeshClutter") {
				delete_child(xml,"spawn_rate");
			}
			
			// ObjectBillboard -> ObjectBillboards
			if(type == "ObjectBillboard") {
				
				xml.setArg("type","ObjectBillboards");
				
				string width = xml.getChildData("width","1");
				string height = xml.getChildData("height","1");
				string texcoord = xml.getChildData("texcoord","1 1 0 0");
				int axis_x = int(xml.getChildData("axis_x","0"));
				int axis_z = int(xml.getChildData("axis_z","0"));
				int screen = int(xml.getChildData("screen","0"));
				
				delete_child(xml,"width");
				delete_child(xml,"height");
				delete_child(xml,"offset");
				delete_child(xml,"axis_x");
				delete_child(xml,"axis_z");
				delete_child(xml,"screen");
				delete_child(xml,"texcoord");
				
				xml.addChild("billboards","num_billboards=\"1\"").setData(format("0 0 0 %s %s %s 0",texcoord,width,height));
				
				Xml surface_element = xml.find("surface");
				if(surface_element != NULL) {
					
					surface_element.setArg("name","billboards");
					
					if(axis_x || axis_z || screen) {
						Xml material_element = surface_element.find("material");
						if(material_element == NULL) {
							material_element = surface_element.addChild("material");
						}
						if(axis_x) {
							material_element.addChild("state","name=\"axis_x\"").setData("1");
						}
						if(axis_z) {
							material_element.addChild("state","name=\"axis_z\"").setData("1");
						}
						if(screen) {
							material_element.addChild("state","name=\"screen\"").setData("1");
						}
					}
				}
				
				Xml generator_element = xml.addChild("data").addChild("generator");
				generator_element.setChildData("count","16");
				generator_element.setChildData("atlas_width","1");
				generator_element.setChildData("atlas_height","1");
				generator_element.setChildData("radius_mean","1");
				generator_element.setChildData("radius_spread","0");
				generator_element.setChildData("aspect_mean","1");
				generator_element.setChildData("aspect_spread","0");
				generator_element.setChildData("angle_mean","0");
				generator_element.setChildData("angle_spread","0");
				generator_element.addChild("mesh");
			}
			
		}
		
		/* 20151119
		 */
		if(version < "2.1") {
			
			if(type == "LightEnvironmentProbe") {
				if(xml.getChildData("texture","") == "core/textures/common/reflection.dds") {
					update_child_value(xml,"texture","core/textures/common/environment_default.dds");
				}
			}
		}
		
		/* 20160126
		 */
		if(version < "2.2") {
			
			if(type == "LightEnvironmentProbe" || type == "LightOmni" || type == "LightProj" || type == "LightWorld") {
				rename_child(xml,"attenuation","attenuation_power");
				rename_child(xml,"multiplier","intensity");
			}
			
			if(type == "LightEnvironmentProbe") {
				rename_child(xml,"radius","attenuation_distance");
			}
			
			if(type == "LightProj") {
				if(xml.getChildData("texture","") == "core/textures/light_base_proj.dds") {
					update_child_value(xml,"texture","");
				} else if(xml.getChildData("texture","") != "") {
					update_child_value(xml,"penumbra","0");
				}
			}
			
			if(type == "LightOmni" || type == "LightProj") {
				int num = xml.findChild("radius");
				if(num != -1) {
					Xml element = xml.getChild(num);
					vec3 radius = element.getVec3Data();
					float attenuation_distance = (abs(radius.x) + abs(radius.y) + abs(radius.z)) / 3.0f;
					element.setName("attenuation_distance");
					element.setData(attenuation_distance);
				}
			}
			
			if(type == "LightOmni" || type == "LightProj") {
				rename_child(xml,"shadow_size","shadow_resolution");
				delete_child(xml,"shadow_bias"); // logic was changed, resetting to default
				delete_child(xml,"shadow_slope"); // replaced with "shadow_normal_bias", we want default value
				delete_child(xml,"shadow_softness"); // logic was changed, resetting to default
			}
			
			if(type == "LightWorld") {
				rename_child(xml,"shadow_size","shadow_resolution");
				delete_child(xml,"shadow_range"); // obsolete
				delete_child(xml,"shadow_distribute"); // obsolete, replaced with cascades
				delete_child(xml,"num_shadow_splits"); // obsolete, replaced with cascades
				delete_child(xml,"shadow_bias"); // ignored, so might be removed
				delete_child(xml,"shadow_slope"); // replaced with "shadow_normal_bias" which is ignored, so might be removed
				delete_child(xml,"shadow_softness"); // ignored, so might be removed
			}
			
			if(type == "ObjectWater") {
				Xml transform = xml.find("transform");
				if(transform == NULL) {
					transform = new Xml("transform");
					transform.setData("1 0 0 0.0 0 1 0 0.0 0 0 1 0.0 0 0 0 1.0");
				} else {
					xml.removeChild(transform);
				}
				for(int i = xml.getNumChildren() - 1; i >= 0; i--) {
					delete xml.removeChild(xml.getChild(i));
				}
				Xml surface = new Xml("surface");
				surface.setArg("name","water_surface");
				surface.setArg("material","water_global_base");
				surface.setArg("property","surface_base");
				
				xml.setArg("type","ObjectWaterGlobal");
				xml.addChild(class_remove(surface));
				xml.addChild(class_remove(transform));
			}
			
			if(type == "ObjectWaterMesh") {
				Xml volume = xml.find("surface name=\"volume\"");
				if(volume != NULL) {
					delete xml.removeChild(volume);
				}
			}
		}
		
		if(version < "2.2.1.3") {
			
			if(type == "ObjectTerrain") {
				
				if(xml.isChild("material")) {
					
					Xml xml_materials = xml.getChild("material");
					
					Xml layers_xml[0];
					int layers_map[];
					
					int num_material = 0;
					// process materials
					for(int i = 0; i < xml_materials.getNumChildren(); i++) {
						Xml xml_material = xml_materials.getChild(i);
						string name = xml_material.getName();
						
						// material
						if(name == "material") {
							
							if(xml_material.isChild("transform") == 0) {
								xml_material.addChild("transform").setVec4Data(vec4(1.0f,1.0f,0.0f,0.0f));
							}
							
							if(xml_material.isChild("overlap") == 0) {
								xml_material.addChild("overlap").setIntData(0);
							}
							
							if(xml_material.isChild("mask_value") == 0) {
								xml_material.addChild("mask_value").setFloatData(0.5f);
							}
							
							if(xml_material.isChild("mask_width") == 0) {
								xml_material.addChild("mask_width").setFloatData(0.5f);
							}
							
							if(xml_material.isChild("mask_threshold") == 0) {
								xml_material.addChild("mask_threshold").setFloatData(0.5f);
							}
							
							if(xml_material.isChild("normal_scale") == 0) {
								xml_material.addChild("normal_scale").setFloatData(0.5f);
							}
							
							if(xml_material.isChild("diffuse_scale")) {
								Xml x = xml_material.getChild("diffuse_scale");
								x.setName("albedo_scale");
							} else {
								xml_material.addChild("albedo_scale").setFloatData(0.5f);
							}
							
							if(xml_material.isChild("diffuse_texture")) {
								Xml x = xml_material.getChild("diffuse_texture");
								x.setName("albedo_texture");
								
								Xml xml_height = xml_material.addChild("height_texture");
								xml_height.setData(x.getData());
							}
							
							if(xml_material.isChild("specular_texture")) {
								delete xml_material.removeChild("specular_texture");
							}
							
							if(xml_material.isChild("specular_scale")) {
								delete xml_material.removeChild("specular_scale");
							}
							
							int detail = !xml_material.getChildData("mask_base",0);
							xml_material.addChild("detail").setIntData(detail);
							
							if(xml_material.isChild("mask_base")) {
								delete xml_material.removeChild("mask_base");
							}
							
							int parent = xml_material.getChildData("parent",-1);
							
							if(parent < 0) {
								xml_materials.removeChild(xml_material);
								i--;
								
								Xml xml_layer = xml_materials.addChild("layer");
								xml_layer.addChild("name").setData("layer" + string(layers_xml.size()));
								xml_layer.addChild(class_remove(xml_material));
								
								layers_xml.append(xml_layer);
								layers_map.append(num_material,layers_xml.size() - 1);
							}
							
							num_material++;
						}
					}
					
					int save_image(Image image,string name,int format) {
						image.convertToFormat(format);
						image.save(name);
						Log::info("save \"%s\" texture",name);
					}
					
					// create material texture
					int create_textures(Xml xml) {
						
						if(xml.isChild("diffuse_texture")) {
							Xml x = xml.getChild("diffuse_texture");
							x.setName("albedo_texture");
						}
						
						string mask_texture_file = "";
						string index_texture_file = "";
						
						if(xml.isChild("mask_texture")) {
							Xml x = xml.getChild("mask_texture");
							mask_texture_file = get_save_name(x.getData());
						}
						
						if(xml.isChild("index_texture")) {
							Xml x = xml.getChild("index_texture");
							index_texture_file = get_save_name(x.getData());
							delete xml.removeChild(x);
						}
						
						Log::info("Creating \"%s\" texture",mask_texture_file);
						
						if(is_file(mask_texture_file) == 0) return;
						
						if(migrated_files.find(mask_texture_file) > 0) return;
						migrated_files.append(mask_texture_file);
						
						Image mask = class_manage(new Image());
						
						if(mask.load(mask_texture_file) == 0) return;
						
						if(mask.isCompressedFormat()) {
							mask.decompress();
						}
						
						// create mask
						Image src = new Image(mask);
						int width = mask.getWidth();
						int height = mask.getHeight();
						
						if(is_file(index_texture_file)) {
							
							Image index = class_manage(new Image());
							if(index.load(index_texture_file) == 0) return;
							
							if(index.isCombinedFormat()) {
								index.decompress();
							}
							
							int num_layers = layers_xml.size();
							
							mask.create2DArray(width,height,num_layers,IMAGE_FORMAT_R8);
							
							// 2d images
							if(src.getType() == IMAGE_2D && index.getType() == IMAGE_2D) {
								for(int y = 0; y < height; y++) {
									int Y = (index.getHeight() * y) / height;
									
									for(int x = 0; x < width; x++) {
										int X = (index.getWidth() * x) / width;
										
										ivec4 p0 = ivec4(src.get2D(x,y) * 255.0f);
										ivec4 p1 = ivec4(index.get2D(X,Y) * 255.0f);
										
										for(int i = 0; i < index.getNumChannels(); i++) {
											int value = p0[i];
											int layer = layers_map[p1[i]];
											if(value && layer < num_layers) mask.set2DArray(x,y,layer,value);
										}
									}
								}
							} else {
								
								for(int y = 0; y < height; y++) {
									int Y = (index.getHeight() * y) / height;
									
									for(int x = 0; x < width; x++) {
										int X = (index.getWidth() * x) / width;
										
										for(int i = 0; i < index.getNumLayers(); i++) {
											ivec4 p0 = ivec4(src.get2DArray(x,y,i) * 255.0f);
											ivec4 p1 = ivec4(index.get2DArray(X,Y,i) * 255.0f);
											
											for(int j = 0; j < index.getNumChannels(); j++) {
												int value = p0[j];
												int layer = layers_map[p1[j]];
												if(value && layer < num_layers) mask.set2DArray(x,y,layer,value);
											}
										}
									}
								}
							}
							
							remove(index_texture_file);
						} else {
							
							mask.create2DArray(width,height,src.getNumChannels(),IMAGE_FORMAT_R8);
							
							for(int y = 0; y < height; y++) {
								for(int x = 0; x < width; x++) {
									ivec4 p0 = ivec4(src.get2D(x,y) * 255.0f);
									
									for(int i = 0; i < src.getNumChannels(); i++) {
										int value = p0[i];
										if(value) mask.set2DArray(x,y,i,value);
									}
								}
							}
						}
						
						save_image(mask,mask_texture_file,IMAGE_FORMAT_ATI1);
					}
					
					// process materials
					for(int i = 0; i < xml_materials.getNumChildren(); i++) {
						Xml xml_material = xml_materials.getChild(i);
						string name = xml_material.getName();
						
						if(name == "material") {
							if(xml_material.isChild("parent")) {
								int parent = xml_material.getChildData("parent",0);
								delete xml_material.removeChild("parent");
								xml_materials.removeChild(xml_material);
								layers_xml[layers_map[parent]].addChild(class_remove(xml_material));
								i--;
							}
						}
						else if(name == "surface") {
							create_textures(xml_material);
						}
					}
					
					string albedo_textures[0];
					for(int i = 0; i < layers_xml.size(); i++) {
						Xml layer_xml = layers_xml[i];
						for(int j = 0; j < layer_xml.getNumChildren(); j++) {
							Xml xml = layer_xml.getChild(j);
							if(xml.getName() != "material") continue;
							albedo_textures.append(get_save_name(xml.getChildData("albedo_texture","")));
						}
					}
					
					create_textures(xml_materials);
					
					if(xml_materials.isChild("diffuse_texture_array")) {
						Xml x = xml_materials.getChild("diffuse_texture_array");
						x.setName("albedo_texture_array");
						
						string source_file = x.getData();
						string dir_name = dirname(source_file);
						string base_name = basename(source_file);
						
						string albedo_file = replace(base_name,"diffuse","albedo");
						albedo_file = replace(albedo_file,"_d.","_al.");
						albedo_file = dir_name + albedo_file;
						x.setData(albedo_file);
						
						string height_file = replace(base_name,"diffuse","height");
						height_file = replace(height_file,"_d.","_h.");
						height_file = dir_name + height_file;
						
						x = xml_materials.addChild("height_texture_array");
						x.setData(height_file);
						
						source_file = get_save_name(source_file);
						albedo_file = dirname(source_file) + basename(albedo_file);
						height_file = dirname(source_file) + basename(height_file);
						
						if(is_file(source_file) && !is_file(height_file)) {
							
							Image source_image = class_manage(new Image());
							source_image.info(source_file);
							int size = source_image.getHeight();
							int num_mipmaps = source_image.getNumMipmaps();
							
							Log::info("creating \"%s\" texture",albedo_file);
							
							Image albedo_image = class_manage(new Image());
							albedo_image.create2DArray(size,size,num_material,IMAGE_FORMAT_RGBA8,num_mipmaps);
							
							Image layer = class_manage(new Image());
							for(int i = 0; i < num_material; i++) {
								
								if(is_file(albedo_textures[i]) == 0) continue;
								if(layer.load(albedo_textures[i]) == 0) continue;
								if(layer.getType() != IMAGE_2D) continue;
								if(layer.convertToFormat(IMAGE_FORMAT_RGBA8) == 0) continue;
								if(layer.resize(size,size) == 0) continue;
								if(layer.getNumMipmaps() != num_mipmaps && layer.createMipmaps() == 0) continue;
								
								albedo_image.copy(layer,i);
							}
							
							Log::info("creating \"%s\" texture",height_file);
							Image height_image = class_manage(new Image(albedo_image));
							height_image.swap(0,3);
							
							albedo_image.set(3,255);
							
							save_image(height_image,height_file,IMAGE_FORMAT_ATI1);
							save_image(albedo_image,albedo_file,IMAGE_FORMAT_DXT5);
							
							remove(source_file);
						}
					}
					
					if(xml_materials.isChild("specular_texture_array")) {
						Xml x = xml_materials.getChild("specular_texture_array");
						remove(get_save_name(x.getData()));
						delete xml_materials.removeChild(x);
					}
				}
			}
		}
		
		if(version < "2.2.1.4") {
			
			if(type == "ObjectTerrain") {
				Xml surface_element = xml.find("surface");
				if(surface_element != NULL) {
					Xml material_element = surface_element.find("material");
					if(material_element != NULL) {
						Xml child_state = material_element.find("state name=\"child\"");
						Xml detail_state = material_element.find("state name=\"detail\"");
						if(child_state != NULL) delete material_element.removeChild(child_state);
						if(detail_state != NULL) delete material_element.removeChild(detail_state);
					}
				}
			}
		}
		
		if(version < "2.2.1.5") {
			if(type == "LightOmni" || type == "LightProj" || type == "LightEnvironmentProbe") {
				int num = xml.findChild("attenuation_power");
				if(num != -1) {
					Xml element = xml.getChild(num);
					float attenuation_power = element.getFloatData() * 0.4f;
					element.setFloatData(attenuation_power);
				} else {
					xml.addChild("attenuation_power").setFloatData(0.4f);
				}
			}
		}
		
		if(version < "2.2.1.7") {
			if(type == "DecalMesh" && xml.isChild("vertex")) {
				
				Mesh read_decal_mesh(Xml xml) {
					
					Xml vertex_element = xml.find("vertex");
					if(	!vertex_element.isArg("num_vertex")		||
						!vertex_element.isChild("vertex")		||
						!vertex_element.isChild("texcoords")	||
						!vertex_element.isChild("tangents")		) {
						return NULL;
					}
					
					float vertices[0] = ();
					float texcoords[0] = ();
					float tangents[0] = ();
					int num_vertex = vertex_element.getIntArg("num_vertex");
					vertex_element.find("vertex").getFloatArrayData(vertices);
					vertex_element.find("texcoords").getFloatArrayData(texcoords);
					vertex_element.find("tangents").getFloatArrayData(tangents);
					
					int num_indices = 0;
					int indices[0] = ();
					Xml indices_element = xml.find("indices");
					if(indices_element != NULL) {
						num_indices = indices_element.getIntArg("num_indices");
						indices_element.getIntArrayData(indices);
					}
					
					if(	vertices.size() != num_vertex * 3	||
						texcoords.size() != num_vertex * 4	||
						tangents.size() != num_vertex * 4	) {
						return NULL;
					}
					
					Mesh mesh = new Mesh();
					mesh.addSurface("decal");
					
					mesh.setNumVertex(num_vertex,0,0);
					mesh.setNumTexCoords0(num_vertex,0);
					mesh.setNumTexCoords1(num_vertex,0);
					mesh.setNumTangents(num_vertex,0,0);
					
					forloop(int i = 0; num_vertex) {
						vec3 v = vec3(vertices[i * 3 + 0],vertices[i * 3 + 1],vertices[i * 3 + 2]);
						mesh.setVertex(i,v,0,0);
					}
					forloop(int i = 0; num_vertex) {
						vec3 v1 = vec3(texcoords[i * 4 + 0],texcoords[i * 4 + 1],0.0f);
						vec3 v2 = vec3(texcoords[i * 4 + 2],texcoords[i * 4 + 3],0.0f);
						mesh.setTexCoord0(i,v1,0);
						mesh.setTexCoord1(i,v2,0);
					}
					forloop(int i = 0; num_vertex) {
						vec4 v = vec4(tangents[i * 4 + 0],tangents[i * 4 + 1],tangents[i * 4 + 2],tangents[i * 4 + 3]);
						mesh.setTangent(i,quat(v),0,0);
					}
					
					mesh.setNumIndices(num_indices,0);
					forloop(int i = 0; num_indices) {
						mesh.setIndex(i,indices[i],0);
					}
					
					mesh.createBounds();
					
					return mesh;
				}
				
				//
				Mesh mesh = read_decal_mesh(xml);
				if(mesh != NULL) {
					
					string save_dir = withoutExtension(current_file) + "_decal_meshes/";
					mkdir(save_dir,1);
					
					string save_name;
					if(xml.getArg("name") != "") {
						save_name = xml.getArg("name");
					} else if(xml.getArg("id") != "") {
						save_name =  xml.getArg("id");
					} else {
						save_name = "decal_mesh";
					}
					
					string save_file = getUniqueFileName(save_dir + save_name + ".mesh");
					Log::info("generating mesh file \"%s\" for DecalMesh \"%s\"...",save_file,xml.getArg("name"));
					
					mesh.save(save_file);
					delete mesh;
					
					delete_child(xml,"vertex");
					delete_child(xml,"indices");
					xml.setChildData("mesh_name",relname(data_catalog,save_file));
				}
			}
		}
		
		if(version < "2.3") {
			if(type == "WorldExtern" && xml.getIntArg("class_id",-1) == 42) {
				int num = xml.findChild("blink_frequency");
				if(num != -1) {
					Xml element = xml.getChild(num);
					float blink_frequency = element.getFloatData();
					
					xml.removeChild(element);
					delete element;
					
					float blink_pulse_period = (blink_frequency == 0.0f) ? 0.0f : 1.0f / blink_frequency;
					float blink_pulse_width = blink_pulse_period * 0.5f;
					
					xml.addChild("blink_pulse_period").setFloatData(blink_pulse_period);
					xml.addChild("blink_pulse_width").setFloatData(blink_pulse_width);
				}
				
				num = xml.findChild("blink_duration");
				if(num != -1) {
					Xml element = xml.getChild(num);
					float blink_duration = element.getFloatData();
					
					xml.removeChild(element);
					delete element;
					
					xml.addChild("blink_enabled_period").setFloatData(blink_duration);
					xml.addChild("blink_disabled_period").setFloatData(blink_duration);
				}
				
				num = xml.findChild("blink_offset");
				if(num != -1) {
					Xml element = xml.getChild(num);
					float blink_offset = element.getFloatData();
					
					xml.removeChild(element);
					delete element;
					
					xml.addChild("blink_pulse_offset").setFloatData(blink_offset);
				}
			}
		}
		
		if(version < "2.3.1") {
			if(type == "GeodeticPivot") {
				int num = xml.findChild("origin_basis");
				if(num != -1) {
					Xml element = xml.getChild(num);
					int basis = int(element.getData());
					if(basis == 2) basis = 1;
					element.setIntData(basis);
				}
			}
			
			if(type == "WorldOccluderTerrain") {
				int num = xml.findChild("heights_image");
				if(num != -1) {
					string path = get_save_name(xml.getChild(num).getData());
					if(!flipped_heights_images.check(path)) {
						Image image = class_manage(new Image(path));
						if(image.isLoaded()) {
							image.flipY();
							image.save(path);
							
							flipped_heights_images[path] = 1;
							Log::info("Flip Y \"%s\" texture",path);
						}
					}
				}
			}
		}
		
		if(version < "2.4") {
			if(type == "GeodeticPivot") {
				delete_child(xml,"mode");
				delete_child(xml,"region_width");
				delete_child(xml,"region_height");
				delete_child(xml,"region_texture_resolution");
				delete_child(xml,"new_origin");
				delete_child(xml,"new_semimajor_axis");
				delete_child(xml,"new_flattening");
				delete_child(xml,"new_mode");
				delete_child(xml,"new_region_width");
				delete_child(xml,"new_region_height");
				delete_child(xml,"new_region_texture_resolution");
				delete_child(xml,"texture_name");
			}
		}
		
		if(version < "2.4.1.1") {
			
			if(type == "LightWorld" || type == "LightOmni" || type == "LightProj")
				delete_child(xml,"shadow_offset");
			
			if(type == "LightWorld")
				delete_child(xml,"shadow_cascade_offset");
		}
		
		if(version < "2.5") {
			if(type == "ObjectTerrainGlobal") {
				
				void process_lods(Xml root) {
					if(root == NULL) return;
					
					Json json = new Json();
					
					forloop(int i = 0; root.getNumChildren()) {
						Xml lod_element = root.getChild(i);
						Xml path_element = lod_element.find("path");
						
						if(path_element == NULL) continue;
						string path = path_element.getData();
						
						if(json.load(get_save_name(path)) == 0) continue;
						Json density_element = json.getChild("resolution");
						if(density_element == NULL) continue;
						if(density_element.isNumber() == 0) continue;
						
						lod_element.addChild("density").setFloatData(density_element.getNumber());
						remove(get_save_name(path));
						
						path_element.setData(dirname(path));
					}
					
					delete json;
				}
				
				process_lods(xml.find("lods_height"));
				process_lods(xml.find("lods_albedo"));
				process_lods(xml.find("lods_normal"));
			}
		}
		
		if(version < "2.5.0.1") {
			if(type == "ObjectGrass")
				delete_child(xml,"shadow_radius");
			if(type == "ObjectMeshCluster")
				delete_child(xml,"shadow_radius");
			if(type == "ObjectMeshClutter")
				delete_child(xml,"shadow_radius");
			if(type == "ObjectTerrain")
				delete_child(xml,"shadow_radius");
			if(type == "WorldCluster")
				delete_child(xml,"shadow_radius");
			if(type == "WorldCluster")
				delete_child(xml,"shadow_radius");
		}
		
		if(version < "2.5.0.1") {
			if(type == "WorldExtern" && xml.getIntArg("class_id",-1) == 42) {
				float size = 1.0f;
				float intensity = 1.0f;
				vec4 color = vec4_one;
				float max_visible_distance = INFINITY;
				
				int num = xml.findChild("size");
				if(num != -1) {
					Xml element = xml.getChild(num);
					size = element.getFloatData();
					
					xml.removeChild(element);
					delete element;
				}
				
				num = xml.findChild("intensity");
				if(num != -1) {
					Xml element = xml.getChild(num);
					intensity = element.getFloatData();
					
					xml.removeChild(element);
					delete element;
				}
				
				num = xml.findChild("color");
				if(num != -1) {
					Xml element = xml.getChild(num);
					color = element.getVec4Data();
					
					xml.removeChild(element);
					delete element;
				}
				
				num = xml.findChild("max_visible_distance");
				if(num != -1) {
					Xml element = xml.getChild(num);
					max_visible_distance = element.getFloatData();
					
					xml.removeChild(element);
					delete element;
				}
				
				string billboard_args = format("material=\"sim_light_base\" size=\"%f\"", size);
				
				if(max_visible_distance != INFINITY) {
					billboard_args += format(" max_visible_distance=\"%f\"", max_visible_distance);
				}
				
				Xml billboard_element = xml.addChild("billboard", billboard_args);
				Xml material_element = NULL;
				if(intensity != 1.0f) {
					if(material_element == NULL) {
						material_element = billboard_element.addChild("material");
					}
					Xml intensity_element = material_element.addChild("parameter", "name=\"emission_scale\"");
					intensity_element.setFloatData(intensity);
				}
				
				if(color != vec4_one) {
					if(material_element == NULL) {
						material_element = billboard_element.addChild("material");
					}
					Xml color_element = material_element.addChild("parameter", "name=\"emission_color\"");
					color_element.setVec4Data(color);
				}
			}
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
	
	/*
	 */
	void process_body(Xml xml,string version) {
		
		// node type
		string type = xml.getArg("type","unknown");
		
		/* 20140709
		 */
		if(version < "1.20") {
			
			// BodyCloth interleaved to multiple arrays
			if(type == "BodyCloth") {
				if(xml.isChild("vertex")) {
					Xml x = xml.getChild("vertex");
					int num_vertex = x.getArg("num_vertex",0);
					float src[0];
					x.getFloatArrayData(src);
					if(src.size() == num_vertex * 4) {
						x.setData("");
						x.addChild("texcoords").setFloatArrayData(src);
					} else {
						Log::error("can't upgrade %s",type);
					}
				}
				if(xml.isChild("triangles")) {
					Xml x = xml.getChild("triangles");
					int num_triangles = x.getArg("num_triangles",0);
					int src[0];
					x.getIntArrayData(src);
					if(src.size() == num_triangles * 6) {
						delete xml.removeChild(x);
						int pindices[0],tindices[0];
						forloop(int i = 0; num_triangles) {
							int j = i * 6;
							pindices.append(src[j + 0]);
							pindices.append(src[j + 1]);
							pindices.append(src[j + 2]);
							tindices.append(src[j + 3]);
							tindices.append(src[j + 4]);
							tindices.append(src[j + 5]);
						}
						xml.addChild("pindices",format("num_pindices=%d",num_triangles * 3)).setIntArrayData(pindices);
						xml.addChild("tindices",format("num_tindices=%d",num_triangles * 3)).setIntArrayData(tindices);
					} else {
						Log::error("can't upgrade %s",type);
					}
				}
			}
		}
	}
	
	/******************************************************************************\
	*
	* Render
	*
	\******************************************************************************/
	
	/*
	 */
	void process_render(Xml xml,string version) {
		
		/* 20150827
		 */
		if(version < "2.0") {
			
			delete_child(xml,"glow_threshold");
			delete_child(xml,"glow_small_exposure");
			delete_child(xml,"glow_medium_exposure");
			delete_child(xml,"glow_large_exposure");
			
			delete_child(xml,"occlusion_ambient_screen_radius");
			delete_child(xml,"occlusion_ambient_sample_radius");
			delete_child(xml,"occlusion_ambient_perspective");
			delete_child(xml,"occlusion_ambient_attenuation");
			delete_child(xml,"occlusion_ambient_threshold");
			delete_child(xml,"occlusion_ambient_emitter");
			delete_child(xml,"occlusion_ambient_receiver");
			delete_child(xml,"occlusion_ambient_power");
			delete_child(xml,"occlusion_light_screen_radius");
			delete_child(xml,"occlusion_light_sample_radius");
			delete_child(xml,"occlusion_light_perspective");
			delete_child(xml,"occlusion_light_attenuation");
			delete_child(xml,"occlusion_light_threshold");
			delete_child(xml,"occlusion_light_emitter");
			delete_child(xml,"occlusion_light_receiver");
			delete_child(xml,"occlusion_light_scale");
			delete_child(xml,"occlusion_light_power");
			
			delete_child(xml,"motion_blur_linear_scale");
			delete_child(xml,"motion_blur_angular_scale");
			delete_child(xml,"motion_blur_velocity_scale"); // resetting to default
			delete_child(xml,"motion_blur_max_velocity"); // resetting to default
			
			delete_child(xml,"hdr_small_exposure");
			delete_child(xml,"hdr_medium_exposure");
			delete_child(xml,"hdr_large_exposure");
			
			rename_child(xml,"occlusion_ambient_radius","ssao_radius");
			rename_child(xml,"occlusion_ambient_scale","ssao_scale");
			rename_child(xml,"volumetric_exposure","shadow_shafts_exposure");
			rename_child(xml,"volumetric_length","shadow_shafts_length");
			rename_child(xml,"volumetric_attenuation","shadow_shafts_attenuation");
			rename_child(xml,"hdr_threshold","camera_effects_threshold");
			rename_child(xml,"hdr_exposure","exposure");
			rename_child(xml,"hdr_adaptation","exposure_adaptation");
			rename_child(xml,"hdr_min_luminance","exposure_min_luminance");
			rename_child(xml,"hdr_max_luminance","exposure_max_luminance");
			rename_child(xml,"hdr_bright_exposure","exposure_bright_exposure");
			rename_child(xml,"hdr_filmic_shoulder_scale","filmic_shoulder_scale");
			rename_child(xml,"hdr_filmic_linear_scale","filmic_linear_scale");
			rename_child(xml,"hdr_filmic_linear_angle","filmic_linear_angle");
			rename_child(xml,"hdr_filmic_toe_scale","filmic_toe_scale");
			rename_child(xml,"hdr_filmic_toe_numerator","filmic_toe_numerator");
			rename_child(xml,"hdr_filmic_toe_denominator","filmic_toe_denominator");
			rename_child(xml,"hdr_filmic_white_level","filmic_white_level");
			rename_child(xml,"hdr_cross_enabled","render_cross");
			rename_child(xml,"hdr_cross_color","cross_color");
			rename_child(xml,"hdr_cross_scale","cross_scale");
			rename_child(xml,"hdr_cross_shafts","cross_shafts");
			rename_child(xml,"hdr_cross_length","cross_length");
			rename_child(xml,"hdr_cross_angle","cross_angle");
			rename_child(xml,"hdr_cross_threshold","cross_threshold");
			rename_child(xml,"hdr_bokeh_enabled","render_bokeh");
			rename_child(xml,"hdr_bokeh_color","bokeh_color");
			rename_child(xml,"hdr_bokeh_scale","bokeh_scale");
			rename_child(xml,"hdr_bokeh_far_size","bokeh_far_size");
			rename_child(xml,"hdr_bokeh_far_power","bokeh_far_power");
			rename_child(xml,"hdr_bokeh_near_size","bokeh_near_size");
			rename_child(xml,"hdr_bokeh_near_power","bokeh_near_power");
			rename_child(xml,"hdr_bokeh_threshold","bokeh_threshold");
			rename_child(xml,"hdr_bokeh_texture_name","bokeh_texture_name");
			rename_child(xml,"hdr_shaft_enabled","render_sun_shafts");
			rename_child(xml,"hdr_shaft_color","sun_shafts_color");
			rename_child(xml,"hdr_shaft_scale","sun_shafts_scale");
			rename_child(xml,"hdr_shaft_length","sun_shafts_length");
			rename_child(xml,"hdr_shaft_attenuation","sun_shafts_attenuation");
			rename_child(xml,"hdr_shaft_threshold","sun_shafts_threshold");
			rename_child(xml,"hdr_lens_enabled","render_lens");
			rename_child(xml,"hdr_lens_color","lens_color");
			rename_child(xml,"hdr_lens_scale","lens_scale");
			rename_child(xml,"hdr_lens_length","lens_length");
			rename_child(xml,"hdr_lens_radius","lens_radius");
			rename_child(xml,"hdr_lens_threshold","lens_threshold");
			rename_child(xml,"hdr_lens_dispersion","lens_dispersion");
			rename_child(xml,"hdr_lens_texture_name","dirt_texture_name");
			
			//
			if(xml.getChildData("environment_texture","") == "core/textures/common/environment.dds") {
				set_child_value(xml,"environment_texture","core/textures/common/environment_default.dds");
			}
			
			// halving shadow distance
			if(xml.isChild("shadow_distance")) {
				float shadow_distance = float(xml.getChildData("shadow_distance",""));
				shadow_distance /= 2.0f;
				update_child_value(xml,"shadow_distance",string(shadow_distance));
			}
		}
		
		/* 20150911
		 */
		if(version < "2.1") {
			
			delete_child(xml,"ambient_color");
			delete_child(xml,"background_color");
			
			delete_child(xml,"environment_texture");
			delete_child(xml,"environment_exposure");
			
			delete_child(xml,"scattering_sun_color");
			delete_child(xml,"scattering_ray_color");
			delete_child(xml,"scattering_mie_color");
			delete_child(xml,"scattering_inner_angle");
			delete_child(xml,"scattering_outer_angle");
			delete_child(xml,"scattering_refractive");
			delete_child(xml,"scattering_density");
			delete_child(xml,"scattering_depolarization");
			delete_child(xml,"scattering_turbidity");
			delete_child(xml,"scattering_direction");
			delete_child(xml,"scattering_ground");
			delete_child(xml,"scattering_areal");
			delete_child(xml,"scattering_ray_height");
			delete_child(xml,"scattering_mie_height");
			delete_child(xml,"scattering_greenstein");
			delete_child(xml,"scattering_angularity");
			delete_child(xml,"scattering_threshold");
			delete_child(xml,"scattering_energy");
			delete_child(xml,"scattering_power");
			delete_child(xml,"scattering_sun");
			delete_child(xml,"scattering_ray");
			delete_child(xml,"scattering_mie");
			
			delete_child(xml,"render_scattering");
			
			// render_taa = 0 -> render_antialiasing = 0; render_taa = 1 -> render_antialiasing = 2
			if(xml.isChild("render_taa")) {
				Xml aa = xml.getChild("render_taa");
				aa.setName("render_antialiasing");
				if(aa.getData() == "1") {
					aa.setData("2");
				}
			}
		}
		
		/* 20160126
		 */
		if(version < "2.2") {
			
			delete_child(xml,"render_spherical_cascades");
			delete_child(xml,"render_water_resolution_low");
			delete_child(xml,"render_water_resolution_high");
			delete_child(xml,"render_ssao_cavity");
			delete_child(xml,"ssao_blur");
			delete_child(xml,"ssao_cavity_scale");
			
			rename_child(xml,"ssao_scale","ssao_intensity");
		}
		
		/* 20160404
		 */
		if(version < "2.2.1") {
			
			rename_child(xml,"render_reflection","render_reflection_dynamic");
			
			if(xml.isChild("fxaa_sample_offset")) {
				float value = xml.getChildData("fxaa_sample_offset",0.0f);
				value = 1.0f - value;
				rename_child(xml,"fxaa_sample_offset","fxaa_intensity");
				set_child_value(xml,"fxaa_intensity",value);
			}
		}
		
		/* 20160628
		 */
		if(version < "2.2.1.4") {
			
			delete_child(xml,"render_shadow_shafts_quality");
			delete_child(xml,"render_surface_ao");
			delete_child(xml,"shadow_shafts_attenuation");
			delete_child(xml,"render_logarithmic_depth");
			delete_child(xml,"render_deferred_transparent");
			delete_child(xml,"render_shader_defines");
			delete_child(xml,"gl_render_use_arb_compute_shader"); // this was not removed, but we want to reset it to default (which is "1")
			
			rename_child(xml,"render_surface_light_map","render_surface_lightmap");
			
			if(xml.isChild("render_ssr_quality")) {
				// render_ssr_quality was renamed to render_ssr_resolution with extended values set
				// values were 0 for half and 1 for full resolution
				// became 0 for quad, 1 for half and 2 for full
				int value = xml.getChildData("render_ssr_quality",0);
				value += 1;
				rename_child(xml,"render_ssr_quality","render_ssr_resolution");
				set_child_value(xml,"render_ssr_resolution",value);
			}
		}
		
		/* 20160801
		 */
		if(version < "2.3") {
			delete_child(xml,"dof_far_blur_range");
			delete_child(xml,"dof_far_blur_radius");
			delete_child(xml,"dof_far_blur_power");
			delete_child(xml,"dof_far_focal_range");
			delete_child(xml,"dof_far_focal_scale");
			delete_child(xml,"dof_far_focal_power");
			delete_child(xml,"dof_near_blur_range");
			delete_child(xml,"dof_near_blur_radius");
			delete_child(xml,"dof_near_blur_power");
			delete_child(xml,"dof_near_focal_range");
			delete_child(xml,"dof_near_focal_scale");
			delete_child(xml,"dof_near_focal_power");
			delete_child(xml,"dof_smoothness_ring");
			
			delete_child(xml,"render_bokeh");
			delete_child(xml,"bokeh_color");
			delete_child(xml,"bokeh_scale");
			delete_child(xml,"bokeh_far_size");
			delete_child(xml,"bokeh_far_power");
			delete_child(xml,"bokeh_near_size");
			delete_child(xml,"bokeh_near_power");
			delete_child(xml,"bokeh_threshold");
			delete_child(xml,"bokeh_texture_name");
			
			delete_child(xml,"render_bloom_quality");
			delete_child(xml,"exposure_bright_exposure");
		}
		
		if(version < "2.3.1") {
			rename_child(xml,"render_surface_lightmap","render_gbuffer_lightmap");
		}
		
		if(version < "2.4") {
			delete_child(xml,"render_ssr_scale");
			delete_child(xml,"render_ssr_stretching");
			delete_child(xml,"render_ssr_roughness_quality");
			delete_child(xml,"render_ssr_normal_threshold");
			delete_child(xml,"render_ssr_depth_threshold");
			delete_child(xml,"render_ssr_near");
			delete_child(xml,"render_ssr_near_quality");
			delete_child(xml,"render_ssr_near_distance_scale");
			delete_child(xml,"render_ssr_far");
			delete_child(xml,"render_ssr_far_quality");
			delete_child(xml,"render_ssr_far_distance_scale");
			
			// values were 0 for half and 1 for full resolution
			// became 0 for quarter, 1 for half and 2 for full
			if(xml.isChild("render_ssao_resolution")) {
				int value = xml.getChildData("render_ssao_resolution",0) + 1;
				set_child_value(xml,"render_ssao_resolution",value);
			}
			
			// values were 0 for half and 1 for full resolution
			// became 0 for quarter, 1 for half and 2 for full
			if(xml.isChild("render_bloom_resolution")) {
				int value = xml.getChildData("render_bloom_resolution",0) + 1;
				set_child_value(xml,"render_bloom_resolution",value);
			}
			
			if(xml.isChild("render_queries")) {
				set_child_value(xml,"render_queries",0);
			}
		}
		
		if(version < "2.4.1.1") {
			
			delete_child(xml,"tessellation_scale");
			delete_child(xml,"tessellation_factor");
			delete_child(xml,"tessellation_distance");
			delete_child(xml,"render_ssr_scale");
			delete_child(xml,"render_ssr_stretching");
			delete_child(xml,"render_ssr_noise");
			delete_child(xml,"render_motion_blur_quality");
			delete_child(xml,"motion_blur_depth_falloff");
			delete_child(xml,"render_profiler");
			delete_child(xml,"render_use_format_depth_d32f");
			
			rename_child(xml,"render_specular_light", "render_lights_specular");
			
			rename_child(xml,"render_filter", "render_textures_filter");
			rename_child(xml,"render_anisotropy", "render_textures_anisotropy");
			
			rename_child(xml,"render_haze", "render_environment_haze");
			
			rename_child(xml,"budget", "render_budget");
			
			rename_child(xml,"render_soft_shadows_quality", "render_shadows_soft_quality");
			rename_child(xml,"render_lerp_cascades", "render_shadows_world_lerp_cascades");
			rename_child(xml,"render_omni_shadow_jitter", "render_shadows_omni_jitter");
			rename_child(xml,"render_soft_shadows", "render_shadows_soft");
			
			rename_child(xml,"render_world_light_per_forward_object", "render_lights_forward_per_object_world");
			rename_child(xml,"render_omni_lights_per_forward_object", "render_lights_forward_per_object_omni");
			rename_child(xml,"render_proj_lights_per_forward_object", "render_lights_forward_per_object_proj");
			rename_child(xml,"render_env_probes_per_forward_object", "render_lights_forward_per_object_env");
			
			rename_child(xml,"render_use_format_rg11b10", "render_screen_precision");
			
			rename_child(xml,"render_shadows_d32f", "render_shadows_precision");
			
			rename_child(xml,"distance_scale", "render_distance_scale");
			rename_child(xml,"field_distance", "render_field_distance");
			rename_child(xml,"light_distance", "render_light_distance");
			rename_child(xml,"decal_distance", "render_decal_distance");
			rename_child(xml,"object_distance", "render_object_distance");
			rename_child(xml,"clutter_distance", "render_clutter_distance");
			rename_child(xml,"shadow_distance", "render_shadow_distance");
			rename_child(xml,"reflection_distance", "render_reflection_distance");
			
			rename_child(xml,"taa_preserve_details", "render_taa_preserve_details");
			rename_child(xml,"taa_frame_count", "render_taa_frame_count");
			rename_child(xml,"taa_velocity_threshold", "render_taa_velocity_threshold");
			rename_child(xml,"taa_max_frame_count", "render_taa_max_frame_count");
			rename_child(xml,"taa_min_frame_count", "render_taa_min_frame_count");
			
			rename_child(xml,"animation_stem", "render_animation_stem");
			rename_child(xml,"animation_leaf", "render_animation_leaf");
			rename_child(xml,"animation_scale", "render_animation_scale");
			rename_child(xml,"animation_wind", "render_animation_wind");
			
			rename_child(xml,"reflection_color", "render_reflection_color");
			rename_child(xml,"wireframe_color", "render_wireframe_color");
			rename_child(xml,"background_color", "render_background_color");
			
			rename_child(xml,"ssao_radius", "render_ssao_radius");
			rename_child(xml,"ssao_intensity", "render_ssao_intensity");
			rename_child(xml,"ssao_intensity_lighted_side", "render_ssao_intensity_lighted_side");
			
			rename_child(xml,"ssgi_radius", "render_ssgi_radius");
			rename_child(xml,"ssgi_intensity", "render_ssgi_intensity");
			rename_child(xml,"ssgi_normal_threshold", "render_ssgi_normal_threshold");
			
			rename_child(xml,"sss_radius", "render_sss_radius");
			rename_child(xml,"sss_color", "render_sss_color");
			
			rename_child(xml,"refraction_dispersion", "render_refraction_dispersion");
			
			rename_child(xml,"motion_blur_velocity_scale", "render_motion_blur_velocity_scale");
			rename_child(xml,"motion_blur_max_velocity", "render_motion_blur_max_velocity");
			
			rename_child(xml,"sharpen_intensity", "render_sharpen_intensity");
			
			rename_child(xml,"fxaa_intensity", "render_fxaa_intensity");
			
			rename_child(xml,"shadow_shafts_exposure", "render_shadow_shafts_exposure");
			rename_child(xml,"shadow_shafts_length", "render_shadow_shafts_length");
			
			rename_child(xml,"dof_focal_distance", "render_dof_focal_distance");
			rename_child(xml,"dof_chromatic_aberration", "render_dof_chromatic_aberration");
			rename_child(xml,"dof_blur", "render_dof_blur");
			rename_child(xml,"dof_far_distance", "render_dof_far_distance");
			rename_child(xml,"dof_far_focal_offset", "render_dof_far_focal_offset");
			rename_child(xml,"dof_near_distance", "render_dof_near_distance");
			rename_child(xml,"dof_near_focal_offset", "render_dof_near_focal_offset");
			
			rename_child(xml,"camera_effects_threshold", "render_camera_effects_threshold");
			rename_child(xml,"dirt_scale", "render_dirt_scale");
			
			rename_child(xml,"exposure_mode", "render_exposure_mode");
			rename_child(xml,"exposure", "render_exposure");
			rename_child(xml,"exposure_adaptation", "render_exposure_adaptation");
			
			rename_child(xml,"bloom_scale", "render_bloom_scale");
			rename_child(xml,"bloom_power", "render_bloom_power");
			
			rename_child(xml,"filmic_shoulder_scale", "render_filmic_shoulder_scale");
			rename_child(xml,"filmic_linear_scale", "render_filmic_linear_scale");
			rename_child(xml,"filmic_linear_angle", "render_filmic_linear_angle");
			rename_child(xml,"filmic_toe_scale", "render_filmic_toe_scale");
			rename_child(xml,"filmic_toe_numerator", "render_filmic_toe_numerator");
			rename_child(xml,"filmic_toe_denominator", "render_filmic_toe_denominator");
			rename_child(xml,"filmic_white_level", "render_filmic_white_level");
			
			rename_child(xml,"cross_color", "render_cross_color");
			rename_child(xml,"cross_scale", "render_cross_scale");
			rename_child(xml,"cross_shafts", "render_cross_shafts");
			rename_child(xml,"cross_length", "render_cross_length");
			rename_child(xml,"cross_angle", "render_cross_angle");
			rename_child(xml,"cross_threshold", "render_cross_threshold");
			
			rename_child(xml,"sun_shafts_color", "render_sun_shafts_color");
			rename_child(xml,"sun_shafts_scale", "render_sun_shafts_scale");
			rename_child(xml,"sun_shafts_length", "render_sun_shafts_length");
			rename_child(xml,"sun_shafts_attenuation", "render_sun_shafts_attenuation");
			rename_child(xml,"sun_shafts_threshold", "render_sun_shafts_threshold");
			
			rename_child(xml,"lens_color", "render_lens_color");
			rename_child(xml,"lens_scale", "render_lens_scale");
			rename_child(xml,"lens_length", "render_lens_length");
			rename_child(xml,"lens_radius", "render_lens_radius");
			rename_child(xml,"lens_threshold", "render_lens_threshold");
			rename_child(xml,"lens_dispersion", "render_lens_dispersion");
			
			rename_child(xml,"render_queries", "render_occlusion_queries");
			rename_child(xml,"render_queries_num_frames", "render_occlusion_queries_num_frames");
			rename_child(xml,"render_show_number", "render_show_textures_offset");
			rename_child(xml,"render_show_offset", "render_show_textures_number");
			
			rename_child(xml,"fade_color", "render_fade_color");
		}
	}
	
	/******************************************************************************\
	*
	* World
	*
	\******************************************************************************/
	
	/*
	 */
	void process_world(Xml xml,string version) {
		
		/* 20150903
		 */
		if(version < "2.0") {
			
			Xml editor_element = xml.find("editor");
			
			if(editor_element != NULL) {
				
				Xml reflection_probe = editor_element.addChild("node");
				reflection_probe.setArg("type","LightEnvironmentProbe");
				reflection_probe.setChildData("radius","1e+009 1e+009 1e+009");
				reflection_probe.setChildData("reflection_update","-1");
				reflection_probe.setChildData("texture","core/textures/common/reflection.dds");
				reflection_probe.setChildData("transform","1 0 0 0.0 0 1 0 0.0 0 0 1 0.0 0 0 0 1.0");
			}
		}
	}
	
} /* namespace WorldsNodes */

#endif /* __MIGRATION_WORLDS_NODES_H__ */
