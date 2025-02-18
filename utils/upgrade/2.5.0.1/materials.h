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

/*
 */
namespace Materials {
	
	/*
	 */
	string MATERIALS_VERSION = "2.5.0.1";
	
	/*
	 */
	#include <materials/model.h>
	#include <materials/legacy.h>
	#include <materials/unigine20.h>
	
	/*
	 */
	string data_paths[0];
	Library libraries[0];
	string parents[];
	string materials[];
	
	NodeFile node_files[0];
	
	void processPaths(string paths[]) {
		
		data_paths.copy(paths);
		
		Log::info("upgrading materials...");
		
		if(!load_libraries() || !load_node_files()) {
			cleanup();
			return;
		}
		
		upgrade();
		
		save();
		
		cleanup();
	}
	
	int load_libraries() {
		
		foreach(string data_path; data_paths) {
			
			string files[0] = ();
			if(!findFilesByExt(files,data_path,".mat")) {
				return false;
			}
			
			foreach(string f; files) {
				
				if(skipFile(data_path,f)) continue;
				
				Library lib = Library::load(f);
				if(lib == NULL) {
					Log::error("failed to load \"%s\"",f);
					return false;
				}
				if(!lib.isEditable()) {
					Log::info("skipping non-editable library \"%s\"",f);
					delete lib;
					continue;
				}
				
				libraries.append(lib);
				
				foreach(Material m; lib.materials) {
					
					string name = m.getName();
					
					materials.append(name,m);
					
					if(parents.check(name)) {
						
						string message = format("duplicate material %s",name);
						
						if(m.getParent() != parents[name]) {
							if(parents[name] == "") {
								parents[name] = m.getParent();
							}
							message += format(", different parents, preferred \"%s\"",parents[name]);
						}
						
						Log::warning(message);
					} else {
						parents.append(name,m.getParent());
					}
				}
			}
		}
		
		return true;
	}
	
	int load_node_files() {
		
		foreach(string data_path; data_paths) {
			
			string files[0] = ();
			if(!findFilesByExt(files,data_path,".node|.world")) {
				return false;
			}
			
			foreach(string f; files) {
				
				if(skipFile(data_path,f)) continue;
				
				NodeFile node_file = NodeFile::load(f);
				if(node_file == NULL) {
					Log::error("failed to load \"%s\"",f);
					return false;
				}
				
				if(node_file.getVersion() < WorldsNodes::WORLD_VERSION) {
					node_files.append(node_file);
				} else {
					delete node_file;
				}
			}
		}
		
		return true;
	}
	
	void upgrade() {
		
		//
		foreach(Library lib; libraries) {
			
			if(lib.getVersion() >= MATERIALS_VERSION) continue;
			
			Log::info("upgrading \"%s\"",lib.path);
			
			string to_remove[0] = ();
			foreach(Material m; lib.materials) {
				
				string origin = get_origin(m);
				
				if(lib.getVersion() < "2.0") {
					upgrade_material_20(m,origin);
				}
				if(lib.getVersion() < "2.1") {
					
					if(origin == "post_filter_antialiasing") {
						to_remove.append(m.getName());
						continue;
					} else {
						upgrade_material_21(m,origin);
					}
				}
				if(lib.getVersion() < "2.2") {
					if(origin == "post_filter_reflection" || origin == "post_filter_scattering") {
						to_remove.append(m.getName());
						continue;
					} else {
						upgrade_material_22(m,origin);
					}
				}
				if(lib.getVersion() < "2.2.1") {
					upgrade_material_221(m,origin);
				}
				
				if(lib.getVersion() < "2.2.1.1") {
					upgrade_material_2211(m,origin);
				}
				
				if(lib.getVersion() < "2.2.1.4") {
					upgrade_material_2214(m,origin);
				}
				
				if(lib.getVersion() < "2.2.1.5") {
					upgrade_material_2215(m,origin);
				}
				
				if(lib.getVersion() < "2.4") {
					upgrade_material_24(m,origin);
				}
				
				if(lib.getVersion() < "2.4.1.1") {
					upgrade_material_2411(m,origin);
				}
				
				if(lib.getVersion() < "2.4.1.2") {
					upgrade_material_2412(m,origin);
				}
			}
			
			foreach(string name; to_remove) {
				lib.remove(name);
			}
		}
		
		foreach(NodeFile node_file; node_files) {
			
			Log::info("upgrading override materials in \"%s\"",node_file.path);
			
			foreach(Override override; node_file.overrides) {
				
				if(override.material == NULL) continue;
				
				if(override.getMaterialName() == "") {
					override.removeMaterialData();
					continue;
				}
				
				string origin = get_origin(override.material);
				
				if(node_file.getVersion() < "2.0") {
					upgrade_material_20(override.material,origin);
				}
				if(node_file.getVersion() < "2.1") {
					upgrade_material_21(override.material,origin);
				}
				if(node_file.getVersion() < "2.2") {
					upgrade_material_22(override.material,origin);
				}
				if(node_file.getVersion() < "2.2.1") {
					upgrade_material_221(override.material,origin);
				}
				if(node_file.getVersion() < "2.2.1.1") {
					upgrade_material_2211(override.material,origin);
				}
				if(node_file.getVersion() < "2.2.1.4") {
					upgrade_material_2214(override.material,origin);
				}
				if(node_file.getVersion() < "2.2.1.5") {
					upgrade_material_2215(override.material,origin);
				}
				if(node_file.getVersion() < "2.4") {
					upgrade_material_24(override.material,origin);
				}
				if(node_file.getVersion() < "2.4.1.1") {
					upgrade_material_2411(override.material,origin);
				}
				if(node_file.getVersion() < "2.4.1.2") {
					upgrade_material_2412(override.material,origin);
				}
				if(override.material.isEmpty()) {
					override.removeMaterialData();
				}
			}
		}
		
		// assigning new parents to orphaned materials
		foreach(Library lib; libraries) {
			foreach(Material m; lib.materials) {
				
				if(lib.getVersion() < "2.0") {
					if(Unigine20::removed_materials.check(m.getParent())) {
						string replacement = Unigine20::removed_materials[m.getParent()];
						m.setParent(replacement);
					}
				}
				
				if(lib.getVersion() < "2.2") {
					if(m.getParent() == "water_base") {
						m.setParent("water_mesh_base");
					}
					if(m.getParent() == "mesh_stem_base" || m.getParent() == "mesh_leaf_base") {
						m.setParent("mesh_base");
					}
				}
				
				if(lib.getVersion() < "2.2.") {
					if(m.getParent() == "water_base") {
						m.setParent("water_mesh_base");
					}
					if(m.getParent() == "mesh_stem_base" || m.getParent() == "mesh_leaf_base") {
						m.setParent("mesh_base");
					}
				}
				
				if(lib.getVersion() < "2.2.1.6") {
					if(m.getParent() == "post_deferred_color") m.setParent("post_deferred_albedo");
					if(m.getParent() == "post_deferred_specular") m.setParent("post_deferred_metalness");
					if(m.getParent() == "post_deferred_depth") m.setParent("post_deferred_opacity_depth");
					if(m.getParent() == "post_deferred_gloss") m.setParent("post_deferred_roughness");
				}
			}
		}
		
		foreach(NodeFile node_file; node_files) {
			foreach(Override s; node_file.overrides) {
				
				if(node_file.getVersion() < "2.0") {
					if(Unigine20::removed_materials.check(s.getMaterialName())) {
						string replacement = Unigine20::removed_materials[s.getMaterialName()];
						s.setMaterialName(replacement);
					}
				}
				
				if(node_file.getVersion() < "2.2") {
					if(s.getMaterialName() == "water_base") {
						s.setMaterialName("water_mesh_base");
					}
					if(s.getMaterialName() == "mesh_stem_base" || s.getMaterialName() == "mesh_leaf_base") {
						s.setMaterialName("mesh_base");
					}
				}
				
				if(node_file.getVersion() < "2.2.1.6") {
					if(s.getMaterialName() == "post_deferred_color") s.setMaterialName("post_deferred_albedo");
					if(s.getMaterialName() == "post_deferred_specular") s.setMaterialName("post_deferred_metalness");
					if(s.getMaterialName() == "post_deferred_depth") s.setMaterialName("post_deferred_opacity_depth");
					if(s.getMaterialName() == "post_deferred_gloss") s.setMaterialName("post_deferred_roughness");
				}
			}
		}
	}
	
	string get_origin(Material material) {
		
		string origin = material.getParent();
		
		while(origin != "" && parents.check(origin)) {
			origin = parents[origin];
		}
		
		return origin;
	}
	
	void upgrade_material_20(Material material,string origin) {
		
		// blend.src != none && blend.dest != none   =>   transparent = 1
		if(material.blend != NULL && material.blend.getSrc() != "none" && material.blend.getDest() != "none") {
			material.setOption("transparent","1");
		}
		
		// removing srgb format from textures
		foreach(Texture t; material.textures) {
			if(t.getFormat() == "srgb") {
				t.removeFormat();
			}
		}
		
		// removing srgb format and flag from parameters
		foreach(Parameter p; material.parameters) {
			if(p.getFormat() == "srgb") {
				p.removeFormat();
			}
			p.removeFlag("srgb");
		}
		
		// group -> order
		string group_option = material.getOption("group");
		if(group_option != "") {
			material.setOption("order",group_option); // yes, we want to overwrite it
		}
		
		// removing options
		foreachkey(string option; Unigine20::removed_options) {
			material.removeOption(option);
		}
		
		// at this point we leave alone materials created by user
		if(origin == "") return;
		
		//
		string new_origin = Unigine20::removed_materials.check(origin,origin);
		
		if(!Unigine20::materials.check(new_origin)) {
			Log::warning("ancestor %s not found for material %s",new_origin,material.getName());
			return;
		}
		
		int editable = !(material is OverrideMaterialProxy && material.isEmpty());
		
		if(group_option != "" || material.getParent() == origin && editable) {
			int group = (group_option != "" ? int(group_option) : 0);
			if(new_origin == "decal_base") {
				int decal_mask = (1 << group + 1) - 1; // 00000111
				material.setParameterValue("decal_mask",format("0x%x",decal_mask));
			} else if(Unigine20::parameters.check(new_origin + "@decal_mask")) {
				int decal_mask = 1 << group; // 00000100
				material.setParameterValue("decal_mask",format("0x%x",decal_mask));
			}
		}
		
		//
		float _specular_power_to_gloss_scale(float v) {
			return clamp(log10(v) / 2.0f,0.0f,1.0f);
		}
		
		// mesh_layer_base functionality was integrated to mesh_base
		if(origin == "mesh_layer_base") {
			
			if(material.hasParameter("base_transform")) {
				Log::warning("%s.base_transform is ignored",material.getName());
			}
			
			material.renameTexture("diffuse_0","diffuse");
			material.renameTexture("normal_0","normal");
			material.renameTexture("specular_0","specular");
			
			material.renameTexture("diffuse_1","detail_diffuse");
			material.renameTexture("normal_1","detail_normal");
			material.renameTexture("specular_1","detail_specular");
			
			material.renameTexture("mask","detail_mask");
			
			material.renameParameter("diffuse_0_color","diffuse_color");
			material.renameParameter("specular_0_color","specular_color");
			material.renameParameter("diffuse_0_scale","diffuse_scale");	// mesh_base migration knows what to do with it
			material.renameParameter("normal_0_scale","normal_scale");
			material.renameParameter("specular_0_power","specular_power");	// ... and with it!
			
			material.renameParameter("diffuse_1_color","s_detail_diffuse");
			
			// base_transform -> ???
			material.renameParameter("layer_0_transform","base_transform");
			material.renameParameter("layer_1_transform","detail_transform");
			material.renameParameter("mask_transform","detail_mask_transform");
			
			// s_detail_specular = (0.2 0.2 0.2)
			if(material.hasParameter("specular_1_color") || material.getParent() == origin && editable) {
				material.setParameterValue("s_detail_specular",string(Unigine20::PLASTIC_SPECULAR_COLOR));
			}
			
			// specular_1_power -> s_detail_gloss
			if(material.hasParameter("specular_1_power") || material.getParent() == origin && editable) {
				float specular_power = (material.hasParameter("specular_1_power") ? float(material.getParameterValue("specular_1_power")) : Legacy::DEFAULT_SPECULAR_POWER);
				float gloss_scale = _specular_power_to_gloss_scale(specular_power);
				material.renameParameter("specular_1_power","s_detail_gloss");
				material.setParameterValue("s_detail_gloss",gloss_scale);
			}
			
			if(material.hasState("detail") || material.getParent() == origin && editable) {
				material.setStateValue("detail",string(Unigine20::MESH_DETAIL_TEXTURE_MASK));
			}
		}
		
		// mesh_overlap_base functionality was integrated to mesh_base
		if(origin == "mesh_overlap_base") {
			
			material.renameTexture("overlap_diffuse","detail_diffuse");
			material.renameTexture("overlap_normal","detail_normal");
			material.renameTexture("overlap_specular","detail_specular");
			
			material.renameTexture("mask","detail_mask");
			
			material.renameParameter("base_diffuse_color","diffuse_color");
			material.renameParameter("base_specular_color","specular_color");
			material.renameParameter("base_diffuse_scale","diffuse_scale");		// mesh_base migration knows what to do with it
			material.renameParameter("base_normal_scale","normal_scale");
			material.renameParameter("base_specular_power","specular_power");	// ... and with it!
			
			material.renameParameter("overlap_diffuse_color","s_detail_diffuse");
			
			material.renameParameter("overlap_transform","detail_transform");
			material.renameParameter("mask_transform","detail_mask_transform");
			
			if(material.hasState("substitute")) {
				int substitute = int(material.getStateValue("substitute"));
				material.setParameterValue("detail_normal_substitute",substitute ? "1.0f" : "0.0f");
			}
			
			// s_detail_specular = (0.2 0.2 0.2)
			if(material.hasParameter("overlap_specular_color") || material.getParent() == origin && editable) {
				material.setParameterValue("overlap_specular_color",string(Unigine20::PLASTIC_SPECULAR_COLOR));
			}
			
			// overlap_specular_power -> s_detail_gloss
			if(material.hasParameter("overlap_specular_power") || material.getParent() == origin && editable) {
				float specular_power = (material.hasParameter("overlap_specular_power") ? float(material.getParameterValue("overlap_specular_power")) : Legacy::DEFAULT_SPECULAR_POWER);
				float gloss_scale = _specular_power_to_gloss_scale(specular_power);
				material.renameParameter("overlap_specular_power","s_detail_gloss");
				material.setParameterValue("s_detail_gloss",gloss_scale);
			}
			
			if(material.hasState("detail") || material.hasState("global") || material.getParent() == origin && editable) {
				int global = (material.hasState("global") ? int(material.getStateValue("global")) : false);
				int detail = Unigine20::MESH_DETAIL_OVERLAP_OBJECT;
				if(global) { // No, ternary operator doesn't work here. Because of "::", I suppose.
					detail = Unigine20::MESH_DETAIL_OVERLAP_WORLD;
				}
				material.setStateValue("detail",string(detail));
			}
		}
		
		// mesh_pbr_base -> mesh_base
		if(origin == "mesh_pbr_base") {
			
			material.renameTexture("emission_","emission");
			material.renameTexture("parallax_","parallax");
			material.renameParameter("gloss","gloss_scale");
			material.renameParameter("parallax_s","parallax_scale");
			
			if(material.hasState("additional_effect")) {
				int effect = int(material.getStateValue("additional_effect"));
				if(effect == Legacy::PBR_EFFECT_PARALLAX) {
					material.setStateValue("parallax",string(Unigine20::MESH_PARALLAX_DEFAULT));
				} else if(effect == Legacy::PBR_EFFECT_OPACITY_PARALLAX) {
					material.setStateValue("parallax",string(Unigine20::MESH_PARALLAX_CUTOUT));
				}
			}
		}
		
		// mesh_wire_base -> mesh_base with geometry_inflation="wire"
		if(material.getParent() == "mesh_wire_base") {
			material.setStateValue("geometry_inflation",string(Unigine20::MESH_GEOMETRY_INFLATION_WIRE));
			material.setParameterValue("vertex_balloon","1.5");
		}
		
		//
		if(new_origin == "mesh_base" || new_origin == "decal_base" || new_origin == "billboards_base") {
			
			//
			vec3 _normalize_color(vec3 color) {
				color.x = clamp(color.x,0.0f,1.0f);
				color.y = clamp(color.y,0.0f,1.0f);
				color.z = clamp(color.z,0.0f,1.0f);
				return color;
			}
			
			// diffuse_color migration
			if(material.hasParameter("diffuse_color") && material.hasParameter("diffuse_scale")) {
			
				vec4 diffuse_color = vec4(material.getParameterValue("diffuse_color"));
				float diffuse_scale = float(material.getParameterValue("diffuse_scale"));
				diffuse_color.xyz = _normalize_color(vec3(diffuse_color) * diffuse_scale);
				material.setParameterValue("diffuse_color",string(diffuse_color));
			}
			
			// specular_color = (0.2 0.2 0.2)
			if(material.hasParameter("specular_color") || material.getParent() == origin && editable) {
				material.setParameterValue("specular_color",string(Unigine20::PLASTIC_SPECULAR_COLOR));
			}
			
			// specular_power -> gloss_scale
			if(material.hasParameter("specular_power") || material.getParent() == origin && editable) {
				float specular_power = (material.hasParameter("specular_power") ? float(material.getParameterValue("specular_power")) : Legacy::DEFAULT_SPECULAR_POWER);
				float gloss_scale = _specular_power_to_gloss_scale(specular_power);
				material.renameParameter("specular_power","gloss_scale");
				material.setParameterValue("gloss_scale",gloss_scale);
			}
		}
		
		if(new_origin == "mesh_base" || new_origin == "decal_base") {
			
			// Some was removed, some became checkboxes. Anyway, we want defaults.
			material.removeState("light_spot");
			material.removeState("light_prob");
			material.removeState("light_omni");
			material.removeState("light_proj");
			material.removeState("light_world");
			
			//
			material.renameParameter("detail_diffuse","s_detail_diffuse_visible");
			material.renameParameter("detail_normal","s_detail_normal");
			material.renameParameter("detail_specular","s_detail_specular_visible");
		}
		
		if(new_origin == "mesh_base") {
			
			// workflow = "specular"
			if(material.getParent() == origin && origin != "mesh_pbr_base" && editable) {
				material.setStateValue("workflow",string(Unigine20::MESH_WORKFLOW_SPECULAR));
			}
			
			//
			if(material.hasState("ambient")) {
				
				int ambient = int(material.getStateValue("ambient"));
				
				// ambient = "lightmap"   =>   lightmap = "1"
				int is_lightmap = (origin == "mesh_pbr_base" ? (ambient == Legacy::PBR_AMBIENT_LIGHTMAP) : (ambient == Legacy::MESH_AMBIENT_LIGHTMAP));
				if(is_lightmap) {
					material.addState("lightmap","1");
					ambient = 0;
				}
				
				// ambient now is a checkbox
				ambient = clamp(ambient,0,1);
				material.setStateValue("ambient",string(ambient));
			}
			
			// Detail:
			// Overlay First -> Overlay + First UV
			// Overlay Second -> Overlay + Second UV
			// Multiply First -> Multiply + First UV
			// Multiply Second -> Multiply + Second UV
			if(material.hasState("detail") && origin != "mesh_layer_base" && origin != "mesh_overlap_base") {
				int detail = int(material.getStateValue("detail"));
				switch(detail) {
					case Legacy::MESH_DETAIL_OVERLAY_FIRST:
						material.setStateValue("detail",string(Unigine20::MESH_DETAIL_OVERLAY));
						// material.setStateValue("detail_map_uv",string(Unigine20::MESH_DETAIL_FIRST_UV));
						break;
					case Legacy::MESH_DETAIL_OVERLAY_SECOND:
						material.setStateValue("detail",string(Unigine20::MESH_DETAIL_OVERLAY));
						material.setStateValue("detail_map_uv",string(Unigine20::MESH_DETAIL_SECOND_UV));
						break;
					case Legacy::MESH_DETAIL_MULTIPLY_FIRST:
						material.setStateValue("detail",string(Unigine20::MESH_DETAIL_MULTIPLY));
						// material.setStateValue("detail_map_uv",string(Unigine20::MESH_DETAIL_FIRST_UV));
						break;
					case Legacy::MESH_DETAIL_MULTIPLY_SECOND:
						material.setStateValue("detail",string(Unigine20::MESH_DETAIL_MULTIPLY));
						material.setStateValue("detail_map_uv",string(Unigine20::MESH_DETAIL_SECOND_UV));
						break;
					default:
						// material.setStateValue("detail_map_uv",string(Unigine20::MESH_DETAIL_FIRST_UV));
				}
			}
		}
		
		if(new_origin == "decal_base") {
			
			if(material.blend != NULL) {
				
				if(material.blend.getSrc() == "zero" && material.blend.getDest() == "src_color") {
					material.setStateValue("blend",string(Unigine20::DECAL_BLEND_MULTIPLY));
				}
				
				// resetting blend to src="none" and dest="none" for all decals
				material.removeBlend();
			}
			
			//
			material.renameParameter("angle_threshold","decal_angle_threshold");
			material.renameParameter("angle_pow","decal_angle_pow");
			
			// substitute -> normal_substitute
			material.renameParameter("substitute","normal_substitute");
			
			// When substitute was not set it's implied "0", which is not default for normal_substitute, so we add it.
			if(!material.hasParameter("normal_substitute") && material.getParent() == origin) {
				 material.addParameter("normal_substitute","0");
			}
		}
		
		if(new_origin == "billboards_base") {
			
			if(material.hasState("ambient")) {
				
				int ambient = int(material.getStateValue("ambient"));
				
				// ambient = "0"   =>   environment = "0"
				if(ambient == Legacy::BILLBOARD_AMBIENT_NONE) {
					material.addState("environment","0");
				}
				// ambient = "1"   =>   environment = "1"
				else if(ambient == Legacy::BILLBOARD_AMBIENT_OPACITY) {
					material.setStateValue("ambient","1");
					material.addState("environment","1");
				}
				// ambient = "2"   =>   ambient = "1", environment = "0"
				// else if(ambient == Legacy::BILLBOARD_AMBIENT_TRANSPARENT) {
				else {
					material.setStateValue("ambient","1");
					material.addState("environment","0");
				}
			}
		}
		
		if(origin == "grass_base") {
			
			// "clutter" shape was temporarily removed
			// we force "billboard" shape to avoid engine crash
			if(material.hasState("shape") && int(material.getStateValue("shape")) == Legacy::GRASS_SHAPE_CLUTTER) {
				material.setStateValue("shape",string(Unigine20::GRASS_SHAPE_BILLBOARD));
			}
		}
		
		// removing states
		for(int i = 0; i < material.states.size(); i++) {
			
			string state_name = material.states.key(i);
			
			if(!Unigine20::states.check(new_origin + "@" + state_name)) {
				if(material.removeState(state_name)) {
					i--;
				}
			}
		}
		
		// removing textures
		for(int i = 0; i < material.textures.size(); i++) {
			
			string texture_name = material.textures.key(i);
			
			if(!Unigine20::textures.check(new_origin + "@" + texture_name)) {
				if(material.removeTexture(texture_name)) {
					i--;
				}
			}
		}
		
		// removing parameters
		for(int i = 0; i < material.parameters.size(); i++) {
			
			string parameter_name = material.parameters.key(i);
			
			if(!Unigine20::parameters.check(new_origin + "@" + parameter_name)) {
				if(material.removeParameter(parameter_name)) {
					i--;
				}
			}
		}
	}
	
	void upgrade_material_21(Material material,string origin) {
		
		material.removeOption("light_blending");
		material.removeOption("post_scattering");
		material.removeOption("post_refraction");
		
		if(origin == "mesh_base") {
			
			if(material.getTextureValue("albedo") == "core/textures/common/metalness/material_ball_alb.dds") {
				material.setTextureValue("albedo","core/textures/material_ball/material_ball_alb.dds");
			}
			if(material.getTextureValue("normal") == "core/textures/common/material_ball_n.dds") {
				material.setTextureValue("normal","core/textures/material_ball/material_ball_n.dds");
			}
			if(material.getTextureValue("metalness") == "core/textures/common/metalness/material_ball_met.dds") {
				material.setTextureValue("metalness","core/textures/material_ball/material_ball_met.dds");
			}
			if(material.getTextureValue("ambient_occlusion") == "core/textures/common/materialball_ao.dds") {
				material.setTextureValue("ambient_occlusion","core/textures/material_ball/material_ball_a.dds");
			}
		}
		
		if(origin == "particles_base") {
			material.removeState("emission");
		}
		
		if(origin == "volume_fog_base") {
			material.removeState("noise");
			material.removeTexture("noise");
			material.removeParameter("noise_scale");
			material.removeParameter("noise_transform");
		}
		
		if(origin == "water_base") {
			material.removeState("reflection_shadow");
		}
		
		if(origin == "billboards_cloud_base") {
			material.removeParameter("cloud_scattering");
		}
		
		if(origin == "sky_base") {
			material.removeParameter("volume_scattering");
		}
	}
	
	void upgrade_material_22(Material material,string origin) {
		
		material.removeOption("shadow_static");
		
		foreach(Texture t; material.textures) {
			if(t.getShader() != "" && t.getShader() != "fragment") {
				t.setShader("all");
			}
		}
		
		if(origin == "mesh_base") {
			
			material.renameParameter("refraction_scale","refraction_normal_map");
			
			if(material.hasTexture("ambient_occlusion") && material.getTextureValue("ambient_occlusion") != "core/textures/common/red.dds") {
				Material m = material;
				while(m != NULL && !m.hasState("ao_map")) {
					if(parents.check(m.getName())) {
						m = materials.check(parents[m.getName()],NULL);
					} else {
						m = NULL;
					}
				}
				if(m == NULL) {
					material.setStateValue("ao_map","1");
				}
			}
		}
		
		if(origin == "decal_base") {
			if(material.hasState("blend")) {
				int blend = int(material.getStateValue("blend"));
				if(blend > 0) blend--;
				material.setStateValue("blend",string(blend));
			}
		}
		
		if(origin == "water_base") {
			
			// keeping only "waves_radius" parameter, everything else is removed
			
			material.removeBlend();
			material.removeOption("order");
			material.removeOption("transparent");
			
			for(int i = 0; i < material.states.size(); i++) {
				string state_name = material.states.key(i);
				if(material.removeState(state_name)) i--;
			}
			
			for(int i = 0; i < material.textures.size(); i++) {
				string texture_name = material.textures.key(i);
				if(material.removeTexture(texture_name)) i--;
			}
			
			for(int i = 0; i < material.parameters.size(); i++) {
				string parameter_name = material.parameters.key(i);
				if(parameter_name == "waves_radius") continue;
				if(material.removeParameter(parameter_name)) i--;
			}
		}
		
		if(origin == "grass_base") {
			material.removeState("occlusion");
			material.removeParameter("occlusion_scale");
		}
		
		string names[0] = (
			"billboards_base",
			"grass_base",
			"grass_impostor_base",
			"mesh_base",
			"mesh_leaf_base",
			"mesh_stem_base",
			"mesh_tessellation_base",
			"particles_base",
			"volumetric",
		);
		
		if(names.find(origin) != -1) {
			material.removeState("volumetric");
		}
		
		if(material.getParent() == "mesh_stem_base") {
			material.setStateValue("workflow","1");
			material.setStateValue("vegetation","1");
			if(!material.hasState("animation")) material.setStateValue("animation","1");
		}
		
		if(material.getParent() == "mesh_leaf_base") {
			material.setOption("alpha_test","1");
			material.setStateValue("workflow","1");
			material.setStateValue("vegetation","1");
			if(!material.hasState("animation")) material.setStateValue("animation","1");
			material.setStateValue("shadow_offset_state","1");
		}
		
		if(origin == "mesh_stem_base") {
			
			material.renameParameter("detail_diffuse","s_detail_diffuse_visible");
			material.renameParameter("detail_normal","s_detail_normal");
			material.renameParameter("detail_specular","s_detail_specular_visible");
			
			if(material.hasState("detail") && material.getStateValue("detail") == "2") {
				material.setStateValue("detail","1");
				material.setStateValue("detail_map_uv","2");
			}
		}
		
		if(origin == "mesh_leaf_base") {
			
			material.removeState("spherize");
			
			material.removeParameter("occlusion_scale");
			material.removeParameter("spherize_offset");
			
			material.renameTexture("color","noise_3d_color_gradient");
		}
	}
	
	void upgrade_material_221(Material material,string origin) {
		
		if(origin == "water_base" || origin == "water_mesh_base") {
			
			if(material.hasParameter("m_underwater_fog_density")) {
				float intensity = float(material.getParameterValue("m_underwater_fog_density"));
				float transparency = 1.0f / intensity; // division by zero? never heard of it.
				material.renameParameter("m_underwater_fog_density","m_underwater_fog_transparency");
				material.setParameterValue("m_underwater_fog_transparency",string(transparency));
			}
		}
	}
	
	string original_transparent[];
	
	void upgrade_material_2211(Material material,string origin) {
		
		string get_option_transparent_recursive(Material material,string option) {
			if(material == NULL) return "";
			
			string name = material.getName();
			if(original_transparent.check(name)) return original_transparent[name];
			
			if(material.hasOption(option)) return material.getOption(option);
			
			string parent = material.getParent();
			if(parent == "") return "";
			
			return get_option_transparent_recursive(materials.check(parent,NULL),option);
		}
		
		if(origin == "water_global_base" || origin == "water_mesh_base") {
			material.removeOption("transparent");
		} else if(origin == "decal_base") {
			
			if(material.hasOption("alpha_test") && int(material.getOption("alpha_test"))) {
				material.setOption("transparent","1");
				material.setStateValue("angle","0");
			} else {
				material.removeOption("transparent");
			}
			
		} else {
			
			string option_transparent = get_option_transparent_recursive(material,"transparent");
			
			if(option_transparent == "") {
				
				string forward_materials[0] = (
					"billboards_cloud_base",
					"billboards_stars",
					"gui_base",
					"particles_base",
					"sky_base",
					"text_base",
					"volume_cloud_base",
					"volume_fog_base",
					"volume_light_base",
					"volume_omni_base",
					"volume_proj_base",
					"volume_shaft_base",
				);
				
				if(forward_materials.find(origin) == -1) {
					option_transparent = "0";
				} else {
					option_transparent = "1";
				}
			}
			
			original_transparent.append(material.getName(),option_transparent);
			
			int transparent = int(option_transparent);
			
			switch(transparent) {
				case 0: // Deferred
					
					if(material.hasOption("alpha_test") && int(material.getOption("alpha_test"))) {
						material.setOption("transparent","1");
					}
					
					break;
				case 1: // Forward
					material.setOption("transparent","2");
					break;
				case 2: // Deferred transparent
					material.addBlend();
					material.blend.setSrc("src_alpha");
					material.blend.setDest("one_minus_src_alpha");
					material.setOption("transparent","2");
					material.addState("multiple_environment_probes","1");
					
					break;
			}
		}
		
		material.removeOption("alpha_test");
		material.renameParameter("decal_mask","material_mask");
		
		if(origin == "decal_base") {
			
			// rename states
			material.renameState("fade","distance_fade");
			material.renameState("angle","angle_fade");
			material.renameState("detail_world_binding","detail_mapping");
			
			// remove states
			material.removeState("use_alpha");
			
			// modified states
			if(material.hasState("detail")) {
				
				int detail = int(material.getStateValue("detail"));
				
				switch(detail) {
					case 1: // overlay_0
						material.addState("detail_blend","1");
						break;
					case 2: // multiply_0
						material.addState("detail_blend","2");
						break;
				}
				
				detail = clamp(detail,0,1);
				material.setStateValue("detail",string(detail));
			}
			
			if(material.hasState("blend")) {
				
				int blend = int(material.getStateValue("blend"));
				
				switch(blend) {
					case 0: // alpha_blend
						material.addBlend();
						material.blend.setSrc("src_alpha");
						material.blend.setDest("one_minus_src_alpha");
						break;
					case 2: // multiply
						material.addBlend();
						material.blend.setSrc("dest_color");
						material.blend.setDest("zero");
						break;
				}
				
				material.removeState("blend");
			}
			
			// rename parameters
			material.renameParameter("diffuse_color","albedo");
			material.renameParameter("translucent_scale","translucent");
			material.renameParameter("base_transform","uv_transform");
			material.renameParameter("diffuse_visible","albedo_visible");
			material.renameParameter("specular_visible","metalness_visible");
			material.renameParameter("gloss_visible","roughness_visible");
			
			material.renameParameter("s_detail_diffuse","detail_albedo");
			material.renameParameter("s_detail_diffuse_visible","detail_albedo_visible");
			material.renameParameter("s_detail_specular_visible","detail_metalness_visible");
			material.renameParameter("s_detail_gloss_visible","detail_roughness_visible");
			material.renameParameter("s_detail_normal","detail_normal_visible");
			material.renameParameter("detail_transform","detail_uv_transform");
			
			material.renameParameter("decal_angle_threshold","angle_fade_threshold");
			material.renameParameter("decal_angle_pow","angle_fade_pow");
			
			material.renameParameter("fade_threshold","distance_fade_threshold");
			material.renameParameter("fade_pow","distance_fade_pow");
			
			material.addParameter("metalness_visible","0");
			
			//remove parameters
			material.removeParameter("specular_color");
			material.removeParameter("microfiber_visible");
			material.removeParameter("translucent_visible");
			material.removeParameter("s_detail_specular");
			material.removeParameter("s_detail_gloss");
			material.removeParameter("gloss_scale");
			
			//rename textures
			material.renameTexture("diffuse","albedo");
			material.renameTexture("detail_diffuse","detail_albedo");
			
			//remove textures
			material.removeTexture("specular");
			material.removeTexture("detail_specular");
			material.removeTexture("microfiber");
		
		}
		
		if(origin == "mesh_base") {
			
			// rename states
			material.renameState("base_map_uv","base_mapping");
			
			// remove states
			material.removeState("vertex_metalness");
			material.removeState("vertex_roughness");
			material.removeState("vertex_gloss");
			
			// modified states
			if(material.hasState("detail")) {
				
				int detail = int(material.getStateValue("detail"));
				
				void detail_mask() {
					material.addState("detail_blend","0");
					material.addState("detail_mask","1");
					
					material.renameParameter("mask_threshold","detail_visible_threshold");
					
					if(material.hasParameter("mask_value")) {
						float mask_value = float(material.getParameterValue("mask_value","0.5"));
						float detail_visible = (1.0f - mask_value) * 2.0f;
						material.addParameter("detail_visible",string(detail_visible));
					}
					
					material.addParameter("detail_albedo_color_visible","1");
					material.addParameter("detail_metalness_visible","1");
					material.addParameter("detail_roughness_visible","1");
					material.addParameter("detail_specular_visible","1");
					material.addParameter("detail_microfiber_visible","1");
					material.addParameter("detail_diffuse_color_visible","1");
					material.addParameter("detail_specular_color_visible","1");
					material.addParameter("detail_gloss_visible","1");
					material.addParameter("detail_normal_visible","1");
				}
				
				switch(detail) {
					case 1: // overlay_0
						material.addState("detail_blend","1");
						break;
					case 2: // multiply_0
						material.addState("detail_blend","2");
						break;
					case 3: // mask_0
						detail_mask();
						break;
					case 4: // overlap_0
						detail_mask();
						material.addState("detail_angle_fade","1");
						material.addState("detail_mapping","4");
						material.addState("detail_mask_mapping","5");
						break;
					case 5: // overlap_1
						detail_mask();
						material.addState("detail_angle_fade","2");
						material.addState("detail_mapping","5");
						material.addState("detail_mask_mapping","6");
						break;
				}
				
				detail = clamp(detail,0,1);
				material.setStateValue("detail",string(detail));
			}
			
			if(material.hasState("detail_map_uv")) {
				
				int mapping = int(material.getStateValue("detail_map_uv"));
				material.removeState("detail_map_uv");
				
				material.addState("detail_mapping",string(mapping + 1));
			}
			
			if(material.hasState("ao_map")) {
				int ao = int(material.getStateValue("ao_map"));
				
				if(ao > 0) {
					material.addState("ao_mapping",string(ao));
				}
				
				ao = clamp(ao,0,1);
				material.setStateValue("ao_map",string(ao));
			}
			
			int lightmap = 0;
			
			if(material.hasState("lightmap")) {
				lightmap = int(material.getStateValue("lightmap"));
				material.setStateValue("lightmap",string(clamp(lightmap,0,1)));
			}
			
			if(material.hasState("vertex_lightmap")) {
				int value = int(material.getStateValue("vertex_lightmap"));
				material.setStateValue("vertex_lightmap",string(clamp(value,0,1)));
				lightmap = max(lightmap,value);
			}
			
			if(lightmap == 2) {
				material.addState("lightmap_with_ambient","1");
			}
			
			// rename parameters
			material.renameParameter("ior","specular");
			material.renameParameter("gloss_scale","gloss");
			material.renameParameter("translucent_scale","translucent");
			material.renameParameter("alpha_scale","transparent");
			material.renameParameter("alpha_pow","transparent_pow");
			material.renameParameter("base_transform","uv_transform");
			
			material.renameParameter("s_detail_albedo","detail_albedo_color");
			material.renameParameter("s_detail_metalness","detail_metalness");
			material.renameParameter("s_detail_roughness","detail_roughness");
			
			material.renameParameter("s_detail_diffuse","detail_diffuse_color");
			material.renameParameter("s_detail_specular","detail_specular_color");
			material.renameParameter("s_detail_gloss","detail_gloss");
			
			material.renameParameter("s_detail_albedo_visible","detail_albedo_color_visible");
			material.renameParameter("s_detail_metalness_visible","detail_metalness_visible");
			material.renameParameter("s_detail_roughness_visible","detail_roughness_visible");
			material.renameParameter("s_detail_diffuse_visible","detail_diffuse_color_visible");
			material.renameParameter("s_detail_specular_visible","detail_specular_color_visible");
			material.renameParameter("s_detail_gloss_visible","detail_gloss_visible");
			material.renameParameter("s_detail_normal","detail_normal_visible");
			
			material.renameParameter("detail_transform","detail_uv_transform");
			material.renameParameter("detail_mask_transform","detail_mask_uv_transform");
			
			material.renameParameter("angle_value","detail_angle_fade");
			material.renameParameter("angle_threshold","detail_angle_fade_threshold");
			
			material.renameParameter("parallax_num_steps","parallax_max_layers");
			material.renameParameter("parallax_transform","parallax_cutout_uv_transform");
			
			material.renameParameter("noise_2d_transform","noise_2d_uv_transform");
			
			// remove parameters
			material.removeParameter("base_triplanar_power");
			material.removeParameter("detail_triplanar_power");
			material.removeParameter("mask_value");
			material.removeParameter("mask_threshold");
			material.removeParameter("detail_normal_substitute");
			
			// rename textures
			material.renameTexture("metalness","shading");
			material.renameTexture("detail_metalness","detail_shading");
			material.renameTexture("noise_3d_color_gradient","noise_3d_gradient");
		}
	
	}
	
	void upgrade_material_2214(Material material,string origin) {
		if(origin == "terrain_base") {
			material.renameParameter("diffuse_color","albedo_color");
			material.renameParameter("occlusion_on_diffuse","occlusion_on_albedo");
			
			if(material.hasParameter("gloss_scale")) {
				float gloss_scale = float(material.getParameterValue("gloss_scale"));
				material.setParameterValue("gloss_scale",1.0f - gloss_scale);
				
				material.renameParameter("gloss_scale","roughness");
			}
			
			material.removeParameter("specular_color");
		}
	}
	
	void upgrade_material_2215(Material material,string origin) {
		if(origin == "water_base" || origin == "water_mesh_base") {
			material.removeParameter("m_bottom_coloration_scale");
			material.removeParameter("m_bottom_coloration_offset");
		}
	}
	
	void upgrade_material_24(Material material,string origin) {
		if(origin == "terrain_base") {
			material.renameState("ambient_occlusion","ao_map");
			material.renameState("invert_occlusion","invert_ao_map");
		}
	}
	
	void upgrade_material_2411(Material material,string origin) {
		if(origin == "water_global_base" || startsWith(origin,"water_global_beaufort_")) {
			material.renameParameter("m_max_tessellation_factor","max_tessellation_factor");
			material.renameParameter("m_tessellation_pow","tessellation_pow");
			material.renameParameter("m_tessellation_distance","tessellation_distance");
			material.renameParameter("m_procedural_normal_blur","procedural_normal_blur");
			material.renameParameter("m_procedural_normal_easing","procedural_normal_easing");
			material.renameParameter("m_geometry_contraction_force","geometry_contraction_force");
			material.renameParameter("m_geometry_contraction_normal_blur","geometry_contraction_normal_blur");
			material.renameParameter("m_geometry_contraction_normal_easing","geometry_contraction_normal_easing");
			material.renameParameter("m_procedural_fragment_scale","procedural_fragment_scale");
			material.renameParameter("m_wave0_uv_transform","wave0_uv_transform");
			material.renameParameter("m_wave0_height_scale","wave0_height_scale");
			material.renameParameter("m_wave1_uv_transform","wave1_uv_transform");
			material.renameParameter("m_wave1_height_scale","wave1_height_scale");
			material.renameParameter("m_wave2_uv_transform","wave2_uv_transform");
			material.renameParameter("m_wave2_height_scale","wave2_height_scale");
			material.renameParameter("m_detail0_uv_transform","detail0_uv_transform");
			material.renameParameter("m_detail0_intensity","detail0_intensity");
			material.renameParameter("m_detail1_uv_transform","detail1_uv_transform");
			material.renameParameter("m_detail1_intensity","detail1_intensity");
			material.renameParameter("m_foam0_uv_size","foam0_uv_size");
			material.renameParameter("m_foam0_uv_speed","foam0_uv_speed");
			material.renameParameter("m_foam1_uv_size","foam1_uv_size");
			material.renameParameter("m_foam1_uv_speed","foam1_uv_speed");
			material.renameParameter("m_wave_foam_contrast","wave_foam_contrast");
			material.renameParameter("m_wave_foam_intensity","wave_foam_intensity");
			material.renameParameter("m_coast_foam_intensity","coast_foam_intensity");
			material.renameParameter("m_subsurface_color","subsurface_color");
			material.renameParameter("m_ambient_subsurface_intensity","ambient_subsurface_intensity");
			material.renameParameter("m_wave_subsurface_intensity","wave_subsurface_intensity");
			material.renameParameter("m_wave_foam_subsurface_intensity","wave_foam_subsurface_intensity");
			material.renameParameter("m_diffuse_subsurface_intensity","diffuse_subsurface_intensity");
			material.renameParameter("m_underwater_fog_transparency","underwater_fog_transparency");
			material.renameParameter("m_underwater_fog_color","underwater_fog_color");
			material.renameParameter("m_underwater_fog_depth","underwater_fog_depth");
			material.renameParameter("m_underwater_fog_offset","underwater_fog_offset");
			material.renameParameter("m_underwater_dof_distance","underwater_dof_distance");
			material.renameParameter("m_underwater_fog_environment_influence","underwater_fog_environment_influence");
			material.renameParameter("m_underwater_fog_sun_influence","underwater_fog_sun_influence");
			material.renameParameter("m_underwater_shaft_intensity","underwater_shaft_intensity");
			material.renameParameter("m_waterline_size","waterline_size");
			material.renameParameter("m_reflection_roughness","reflection_roughness");
			material.renameParameter("m_refraction_scale","refraction_scale");
			material.renameParameter("m_diffuse_distortion","diffuse_distortion");
			material.renameParameter("m_soft_intersection","soft_intersection");
			material.renameParameter("m_caustic_uv_transform","caustic_uv_transform");
			material.renameParameter("m_caustic_fade","caustic_fade");
			material.renameParameter("m_caustic_animation_speed","caustic_animation_speed");
			material.renameParameter("m_caustic_brightness","caustic_brightness");
			material.renameParameter("m_shoreline_run_speed","shoreline_run_speed");
			material.renameParameter("m_shoreline_wave_tiling","shoreline_wave_tiling");
			material.renameParameter("m_shoreline_exp","shoreline_exp");
			material.renameParameter("m_shoreline_foam_stretching","shoreline_foam_stretching");
			material.renameParameter("m_shoreline_mask_tiling","shoreline_mask_tiling");
			material.renameParameter("m_shoreline_wave_mod","shoreline_wave_mod");
			material.renameParameter("m_shoreline_falloff","shoreline_falloff");
			material.renameParameter("m_shoreline_beaufort_falloff","shoreline_beaufort_falloff");
			material.renameParameter("m_shoreline_foam_intensity","shoreline_foam_intensity");
			material.renameParameter("m_shoreline_foam_exp","shoreline_foam_exp");
			material.renameParameter("m_shoreline_front_exp","shoreline_front_exp");
			material.renameParameter("m_shoreline_wetness_intensity","shoreline_wetness_intensity");
			material.renameParameter("m_shoreline_wetness_distance","shoreline_wetness_distance");
			material.renameParameter("m_shoreline_wetness_offset","shoreline_wetness_offset");
		}
		if(origin == "water_mesh_base") {
			material.renameParameter("m_detail0_uv_transform","detail0_uv_transform");
			material.renameParameter("m_detail0_intensity","detail0_intensity");
			material.renameParameter("m_detail1_uv_transform","detail1_uv_transform");
			material.renameParameter("m_detail1_intensity","detail1_intensity");
			material.renameParameter("m_detail2_uv_transform","detail2_uv_transform");
			material.renameParameter("m_detail2_intensity","detail2_intensity");
			material.renameParameter("m_detail3_uv_transform","detail3_uv_transform");
			material.renameParameter("m_detail3_intensity","detail3_intensity");
			material.renameParameter("m_detail4_uv_transform","detail4_uv_transform");
			material.renameParameter("m_detail4_intensity","detail4_intensity");
			material.renameParameter("m_foam0_uv_size","foam0_uv_size");
			material.renameParameter("m_foam0_uv_speed","foam0_uv_speed");
			material.renameParameter("m_foam1_uv_size","foam1_uv_size");
			material.renameParameter("m_foam1_uv_speed","foam1_uv_speed");
			material.renameParameter("m_coast_foam_intensity","coast_foam_intensity");
			material.renameParameter("m_subsurface_color","subsurface_color");
			material.renameParameter("m_wave_subsurface_intensity","wave_subsurface_intensity");
			material.renameParameter("m_ambient_subsurface_intensity","ambient_subsurface_intensity");
			material.renameParameter("m_wave_foam_subsurface_intensity","wave_foam_subsurface_intensity");
			material.renameParameter("m_diffuse_subsurface_intensity","diffuse_subsurface_intensity");
			material.renameParameter("m_underwater_fog_transparency","underwater_fog_transparency");
			material.renameParameter("m_underwater_fog_depth","underwater_fog_depth");
			material.renameParameter("m_underwater_fog_offset","underwater_fog_offset");
			material.renameParameter("m_underwater_fog_color","underwater_fog_color");
			material.renameParameter("m_underwater_fog_environment_influence","underwater_fog_environment_influence");
			material.renameParameter("m_underwater_fog_sun_influence","underwater_fog_sun_influence");
			material.renameParameter("m_reflection_roughness","reflection_roughness");
			material.renameParameter("m_refraction_scale","refraction_scale");
			material.renameParameter("m_diffuse_distortion","diffuse_distortion");
			material.renameParameter("m_soft_intersection","soft_intersection");
			material.renameParameter("m_caustic_uv_transform","caustic_uv_transform");
			material.renameParameter("m_caustic_fade","caustic_fade");
			material.renameParameter("m_caustic_animation_speed","caustic_animation_speed");
			material.renameParameter("m_caustic_brightness","caustic_brightness");
		}
	}
	
	void upgrade_material_2412(Material material,string origin) {
		if(origin == "particles_base") {
			if(material.hasState("disable_receive_shadow")) {
				int value = int(material.getStateValue("disable_receive_shadow"));
				material.setStateValue("disable_receive_shadow",string(clamp(1 - value,0,1)));
				material.renameState("disable_receive_shadow","shadow");
			}
			
			if(material.hasState("disable_receive_world_shadow")) {
				int value = int(material.getStateValue("disable_receive_world_shadow"));
				material.setStateValue("disable_receive_world_shadow",string(clamp(1 - value,0,1)));
				material.renameState("disable_receive_world_shadow","world_shadow");
			}
			
			if(material.hasState("disable_soft_shadows")) {
				int value = int(material.getStateValue("disable_soft_shadows"));
				material.setStateValue("disable_soft_shadows",string(clamp(1 - value,0,1)));
				material.renameState("disable_soft_shadows","soft_shadows");
			}
			
			if(material.hasState("receive_lighting")) {
				int value = int(material.getStateValue("receive_lighting"));
				if(value == 1) {
					material.addParameter("emission_scale","0");
				}else {
					material.addParameter("emission_scale","1");
				}
				material.removeState("receive_lighting");
			}
		}
	}
	
	void save() {
		
		foreach(Library lib; libraries) {
		
			if(lib.getVersion() >= MATERIALS_VERSION) continue;
			
			lib.setVersion(MATERIALS_VERSION);
			
			if(!lib.save()) {
				Log::error("failed to save \"%s\"",lib.path);
			}
		}
		
		foreach(NodeFile node_file; node_files) {
			if(!node_file.save()) {
				Log::error("failed to save \"%s\"",node_file.path);
			}
		}
	}
	
	void cleanup() {
		materials.clear();
		parents.clear();
		libraries.delete();
		node_files.delete();
	}
	
} /* namespace Materials */

#endif /* __MIGRATION_MATERIALS_H__ */
