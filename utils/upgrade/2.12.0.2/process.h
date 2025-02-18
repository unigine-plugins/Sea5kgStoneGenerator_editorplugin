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

#include <fbx_reader.h>

namespace Process {
	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/
	
	void material(Material m) {
		m.removeOption("offset");
	}
	
	/******************************************************************************\
	*
	* Property
	*
	\******************************************************************************/
	
	// local changes of the property file
	void propertyFile(Xml xml) {
	}

	// global changes that related to another properties
	void property(Properties::Property p) {
	}
	
	/******************************************************************************\
	*
	* Nodes
	*
	\******************************************************************************/

	void node(Xml xml) {
		string type = xml.getArg("type");
		
		if (type == "LightWorld" || type == "LightProj" || type == "LightOmni"
		|| type == "LightEnvironmentProbe" || type == "LightVoxelProbe") 
		{
			if(xml.isChild("shadow_screen_space_step_size"))
			{
				string step_size = xml.getChildData("shadow_screen_space_step_size", "0");
				xml.addChild("shadow_screen_space_step_size_near").setData(step_size);
				xml.addChild("shadow_screen_space_step_size_far").setData(step_size);
				xml.removeChild("shadow_screen_space_step_size");
			}
			
			if(xml.isChild("shadow_screen_space_threshold"))
			{
				string step_size = xml.getChildData("shadow_screen_space_threshold", "0");
				xml.addChild("shadow_screen_space_threshold_near").setData(step_size);
				xml.addChild("shadow_screen_space_threshold_far").setData(step_size);
				xml.removeChild("shadow_screen_space_threshold");
			}
		}
	}
	
	void surface(Xml xml) {
	}
	
	void surfaceProperty(Xml xml_surface, Xml xml_prop, Properties::Property prop) {
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
	}
	
	/******************************************************************************\
	*
	* Render
	*
	\******************************************************************************/
	void render(Xml xml) {
		xmlRenameChild(xml, "render_clouds_fix_tiling", "render_clouds_fix_coverage_tiling");
		
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
	void conf_config(Xml src_xml, string name, int autosave) {
		Xml xml = new Xml();
		xml.setName("config");
		xml.setArg("version", ENGINE_VERSION);
		xml.setBoolArg("autosave", autosave);

		for(int i = 0; i < src_xml.getNumChildren(); i++) {
			Xml x = src_xml.getChild(i);
			string param_name = x.getArg("name");
			Xml xml_param = xml.addChild(param_name);
			xml_param.setData(x.getData());
		}

		xml.save(name + ".config");
	}

	void conf_boot(Xml src_xml, string name, int autosave) {
		string params[] = (
			"gui_path",
			"engine_log",
			"system_script",
			"editor_script",
			"cache_path",
			"system_cache",
			"editor_cache",
			"video_app",
			"sound_app",
			"extern_define",
			"console_command",
			"plugin_paths",
			"extern_plugins",
		);

		string console_params[] = (
			"async_log_mode",
			"async_log_priority",
			"console_font",
			"console_size",
			"filesystem_mmap",
			"gl_async_buffer",
			"gl_async_buffer_indices",
			"gl_async_buffer_synchronization",
			"gl_render_skip_errors",
			"gl_use_debug_info",
			"materials_loading_mode",
			"process_priority",
			"profiler_font",
			"profiler_size",
			"splash_screen",
			"starting_world",
			"textures_cache_preload",
			"video_adapter",
			"video_debug",
			"video_fullscreen",
			"video_height",
			"video_mode",
			"video_quad_buffer",
			"video_resizable",
			"video_surround",
			"video_surround_border",
			"video_vsync",
			"video_width",
			"world_manager_images_memory",
			"world_manager_meshes_memory",
		);

		Xml xml = new Xml();
		xml.setName("boot");
		xml.setArg("version", ENGINE_VERSION);
		xml.setBoolArg("autosave", autosave);

		foreach(string param; params) {
			Xml src_xml_param = src_xml.find(format("/item name=\"%s\"", param));
			if(src_xml_param != NULL) {
				Xml xml_param = xml.addChild(param);
				xml_param.setData(src_xml_param.getData());
				delete src_xml.removeChild(src_xml_param);
			}
		}

		Xml xml_console = xml.addChild("console");
		string conf_path = substr(name, strlen(getCurrDataPath()));
		xml_console.addChild("config").setData(conf_path + ".config");
		xml_console.addChild("user_config").setData(conf_path + ".user");
		xml_console.addChild("controls_config").setData(conf_path + ".controls");
		foreach(string param; console_params) {
			Xml src_xml_param = src_xml.find(format("/item name=\"%s\"", param));
			if(src_xml_param != NULL) {
				Xml xml_param = xml_console.addChild(param);
				xml_param.setData(src_xml_param.getData());
				delete src_xml.removeChild(src_xml_param);
			}
		}

		xml.save(name + ".boot");
	}

	void conf_user(Xml src_xml, string name, int autosave) {
		string params[] = (
			"console_key",
			"microprofile_dump_frames",
			"microprofile_webserver_frames",
			"physics_show_collision_surfaces",
			"physics_show_contacts",
			"physics_show_joints",
			"physics_show_shapes",
			"render_show_alpha_test",
			"render_show_ambient",
			"render_show_cascades",
			"render_show_decals",
			"render_show_dynamic",
			"render_show_geodetic_pivot",
			"render_show_landscape_albedo",
			"render_show_landscape_mask",
			"render_show_landscape_terrain_vt_streaming,"
			"render_show_mipmaps",
			"render_show_occluder",
			"render_show_queries",
			"render_show_scissors",
			"render_show_textures",
			"render_show_textures_number",
			"render_show_textures_offset",
			"render_show_transparent",
			"render_show_triangles",
			"show_fps",
			"show_messages",
			"show_profiler",
			"show_profiler_charts",
			"show_visualizer",
			"video_extension",
			"visualizer_fix_flicker",
			"world_handler_3d",
			"world_handler_distance",
			"world_show_handler",
			"world_show_spatial",
			"world_show_visualizer",
			"console_bindings",
		);

		Xml xml = new Xml();
		xml.setName("user");
		xml.setArg("version", ENGINE_VERSION);
		xml.setBoolArg("autosave", autosave);

		foreach(string param; params) {
			Xml src_xml_param = src_xml.find(format("/item name=\"%s\"", param));
			if(src_xml_param != NULL) {
				Xml xml_param = xml.addChild(param);
				xml_param.setData(src_xml_param.getData());
				delete src_xml.removeChild(src_xml_param);
			}
		}

		xml.save(name + ".user");
	}

	void conf_controls(Xml src_xml, string name, int autosave) {
		string params[] = (
			"controls_always_run",
			"controls_mouse_handle",
			"controls_mouse_inverse",
			"controls_mouse_sensitivity",
		);

		Xml xml = new Xml();
		xml.setName("controls");
		xml.setArg("version", ENGINE_VERSION);
		xml.setBoolArg("autosave", autosave);
		
		foreach(string param; params) {
			Xml src_xml_param = src_xml.find(format("/item name=\"%s\"", param));
			if(src_xml_param != NULL) {
				Xml xml_param = xml.addChild(param);
				xml_param.setData(src_xml_param.getData());
				delete src_xml.removeChild(src_xml_param);
			}
		}

		int num_states = 32;

		// keys
		Xml xml_keys = xml.addChild("keys");
		for(int i = 0; i < num_states; i++)
		{
			Xml src_xml_param = src_xml.find(format("/item name=\"%s\"", "controls_key_" + i));
			Xml xml_param = xml_keys.addChild("0");
			if(src_xml_param != NULL) {
				xml_param.setName(src_xml_param.getData());
				delete src_xml.removeChild(src_xml_param);
			}
		}

		// buttons
		Xml xml_buttons = xml.addChild("buttons");
		for(int i = 0; i < num_states; i++)
		{
			Xml src_xml_param = src_xml.find(format("/item name=\"%s\"", "controls_button_" + i));
			Xml xml_param = xml_buttons.addChild("0");
			if(src_xml_param != NULL) {
				xml_param.setName(src_xml_param.getData());
				delete src_xml.removeChild(src_xml_param);
			}
		}

		xml.save(name + ".controls");
	}

	void config(Xml xml) {
		string file = xml.getLoadPath();
		string name = basename(file);
		string config_path = substr(file, 0, strlen(file) - strlen(name));
		config_path = getDirPath(config_path) + "configs/";
		if(!is_dir(config_path))
			mkdir(config_path);

		string new_name = withoutExtension(name);
		if (new_name == "unigine")
			new_name = "default";
		string new_path = config_path + new_name;

		int autosave = 1;
		Xml xml_readonly = xml.find(format("/item name=\"%s\"", "config_readonly"));
		if(xml_readonly != NULL) {
			autosave = !xml_readonly.getBoolData();
			delete xml.removeChild(xml_readonly);
		}
		
		conf_boot(xml, new_path, autosave);
		conf_user(xml, new_path, autosave);
		conf_controls(xml, new_path, autosave);
		conf_config(xml, new_path, autosave);
	}
	
	/******************************************************************************\
	*
	* Meta
	*
	\******************************************************************************/
	void meta(Xml xml, string file_name) {
	}
	
	/******************************************************************************\
	*
	* AppProjection
	*
	\******************************************************************************/
	void projectionBinary(string file_name) {
	}
	
	void projection(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Syncker
	*
	\******************************************************************************/
	void synckerBinary(string file_name) {
	}
	
	void syncker(Xml xml) {
	}
}

#endif /* __MIGRATION_PROCESS_H__ */
