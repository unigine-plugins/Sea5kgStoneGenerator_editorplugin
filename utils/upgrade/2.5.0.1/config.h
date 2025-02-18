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

#ifndef __MIGRATION_CONFIG_H__
#define __MIGRATION_CONFIG_H__

/*
 */
namespace Config {
	
	/*
	 */
	string CONFIG_VERSION = "2.5.0.1";
	
	/*
	 */
	void processFile(string file) {
		
		Xml xml = new Xml();
		
		if(!xml.load(file)) {
			Log::error("failed to load \"%s\"",file);
			delete xml;
			return;
		}
		
		string version = xml.getArg("version","1.00");
		if(version >= CONFIG_VERSION) {
			delete xml;
			return;
		}
		
		Log::info("upgrading \"%s\"",file);
		
		if(version < "2.0") {
			
			string removed[] = (
				"filesystem_data_memory": 0,
				"filesystem_files_memory": 0,
				"filesystem_images_memory": 0,
				"filesystem_meshes_memory": 0,
				"render_translucent": 0,
				"render_deferred": 0,
				"render_light_prob": 0,
				"render_glow": 0,
				"render_use_scissors": 0,
				"render_use_stencil": 0,
				"render_use_d32f": 0,
				"render_use_srgb": 0,
				"render_use_rgb10a2": 0,
				"render_use_phong_rim": 0,
				"render_use_environment": 0,
				"render_use_directional_lightmaps": 0,
				"render_use_shadow_kernel": 0,
				"render_simple_deferred": 0,
				"render_force_deferred": 0,
				"render_force_no_shadows": 0,
				"render_skip_reflection": 0,
				"render_skip_translucent": 0,
				"render_skip_deferred": 0,
				"render_skip_light_prob": 0,
				"render_skip_occlusion": 0,
				"render_skip_auxiliary": 0,
				"render_skip_refraction": 0,
				"render_skip_motion_blur": 0,
				"render_skip_scattering": 0,
				"render_skip_ambient_light": 0,
				"render_skip_opacity_ambient": 0,
				"render_skip_opacity_light": 0,
				"render_skip_decal_ambient": 0,
				"render_skip_decal_light": 0,
				"render_show_occlusion": 0,
				"render_manager_create_textures": 0,
				"render_manager_create_dummy_textures": 0,
				"d3d11_render_use_alpha_test_level_101": 0,
			);
			
			string renamed[] = (
				"render_use_queries": "render_queries",
				"render_volumetric": "render_shadow_shafts",
				"render_use_filmic": "render_filmic",
				"render_shaders": "render_shaders_quality",
				"render_textures": "render_textures_quality",
				"render_hdr": "render_exposure_mode", // not the same, but HDR also enabled exposure
			);
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
				
				Xml x = xml.getChild(i);
				
				if(x.getName() != "item") continue;
				
				string name = x.getArg("name");
				
				if(removed.check(name)) {
					delete xml.removeChild(x);
					i--;
				} else if(renamed.check(name)) {
					x.setArg("name",renamed[name]);
				} else if(name == "show_fps") {
					x.setArg("type","int");
				} else if(name == "render_force_no_shadows") {
					x.setArg("name","render_shadows");
					x.setData(string(!x.getIntData()));
				} else if(name == "render_occlusion") {
					x.setArg("name","render_ssao");
					x.setArg("type","bool");
				}
			}
		}
		
		if(version < "2.1") {
			
			Xml scattering = xml.find("/item name=\"render_scattering\"");
			if(scattering != NULL) {
				delete xml.removeChild(scattering);
			}
			
			// render_taa -> render_antialiasing, bool -> int, 1 -> 2
			Xml aa = xml.find("/item name=\"render_taa\"");
			if(aa != NULL) {
				aa.setArg("name","render_antialiasing");
				aa.setArg("type","int");
				if(aa.getData() == "1") {
					aa.setData("2");
				}
			}
		}
		
		if(version < "2.1.1") {
			
			string removed[] = (
				"render_optimization_cleargbuffer",
				"render_optimization_normalbuffer",
				"render_rwtextures",
			);
			
			foreach(string name; removed) {
				Xml element = xml.find(format("/item name=\"%s\"",name));
				if(element != NULL) {
					delete xml.removeChild(element);
				}
			}
			
			// render_ssao_quality: bool -> int
			Xml ssao_quality = xml.find("/item name=\"render_ssao_quality\"");
			if(ssao_quality != NULL) {
				ssao_quality.setArg("type","int");
			}
		}
		
		if(version < "2.2") {
			
			string removed[] = (
				"render_water_resolution_low",
				"render_water_resolution_high",
				"render_ssao_cavity",
			);
			
			foreach(string name; removed) {
				Xml element = xml.find(format("/item name=\"%s\"",name));
				if(element != NULL) {
					delete xml.removeChild(element);
				}
			}
			
			Xml show_splits = xml.find("/item name=\"render_show_splits\"");
			if(show_splits != NULL) {
				show_splits.setArg("name","render_show_cascades");
			}
		}
		
		if(version < "2.2.1") {
			
			Xml render_reflection = xml.find("/item name=\"render_reflection\"");
			if(render_reflection != NULL) {
				render_reflection.setArg("name","render_reflection_dynamic");
			}
		}
		
		if(version < "2.2.3") {
			
			string removed[] = (
				"render_shadow_shafts_quality",
				"render_surface_ao",
				"shadow_shafts_attenuation",
				"render_logarithmic_depth",
				"render_deferred_transparent",
				"render_shader_defines",
				"gl_render_use_arb_compute_shader", // this was not removed, but we want to reset it to default (which is "1")
			);
			
			foreach(string name; removed) {
				Xml element = xml.find(format("/item name=\"%s\"",name));
				if(element != NULL) {
					delete xml.removeChild(element);
				}
			}
			
			// render_surface_light_map -> render_surface_lightmap
			Xml lightmap = xml.find("/item name=\"render_surface_light_map\"");
			if(lightmap != NULL) {
				lightmap.setArg("name","render_surface_lightmap");
			}
			
			// render_ssr_quality -> render_ssr_resolution
			Xml ssr_quality = xml.find("/item name=\"render_ssr_quality\"");
			if(ssr_quality != NULL) {
				// render_ssr_quality was renamed to render_ssr_resolution with extended values set
				// values were 0 for half and 1 for full resolution
				// became 0 for quad, 1 for half and 2 for full
				int value = ssr_quality.getIntData();
				value += 1;
				ssr_quality.setData(value);
				ssr_quality.setArg("name","render_ssr_resolution");
				ssr_quality.setArg("type","int");
			}
			
			Xml icase = xml.find("/item name=\"filesystem_icase\"");
			if(icase != NULL) {
				icase.setArg("type","int");
			}
		}
		
		if(version < "2.3") {
			
			string removed[] = (
				"render_taa_fix_blurring",
				"render_bloom_quality",
				"render_bokeh",
			);
			
			foreach(string name; removed) {
				Xml element = xml.find(format("/item name=\"%s\"",name));
				if(element != NULL) {
					delete xml.removeChild(element);
				}
			}
		}
		
		if(version < "2.3.1") {
			
			Xml lightmap = xml.find("/item name=\"render_surface_lightmap\"");
			if(lightmap != NULL) {
				lightmap.setArg("name","render_gbuffer_lightmap");
			}
		}
		
		if(version < "2.4") {
			
			string removed[] = (
				"render_ssr_scale",
				"render_ssr_stretching",
				"render_ssr_roughness_quality",
				"render_ssr_normal_threshold",
				"render_ssr_depth_threshold",
				"render_ssr_near",
				"render_ssr_near_quality",
				"render_ssr_near_distance_scale",
				"render_ssr_far",
				"render_ssr_far_quality",
				"render_ssr_far_distance_scale",
			);
			
			foreach(string name; removed) {
				Xml element = xml.find(format("/item name=\"%s\"",name));
				if(element != NULL) {
					delete xml.removeChild(element);
				}
			}
			
			// values were 0 for half and 1 for full resolution
			// became 0 for quarter, 1 for half and 2 for full
			Xml ssao_resolution = xml.find("/item name=\"render_ssao_resolution\"");
			if(ssao_resolution != NULL) {
				int value = ssao_resolution.getIntData() + 1;
				ssao_resolution.setData(value);
				ssao_resolution.setArg("type","int");
			}
			
			// values were 0 for half and 1 for full resolution
			// became 0 for quarter, 1 for half and 2 for full
			Xml bloom_resolution = xml.find("/item name=\"render_bloom_resolution\"");
			if(bloom_resolution != NULL) {
				int value = bloom_resolution.getIntData() + 1;
				bloom_resolution.setData(value);
				bloom_resolution.setArg("type","int");
			}
			
			Xml queries = xml.find("/item name=\"render_queries\"");
			if(queries != NULL) {
				queries.setData(0);
				queries.setArg("type","int");
			}
		}
		
		if(version < "2.4.1.1") {
			
			string removed[] = (
				"tessellation_scale",
				"tessellation_factor",
				"tessellation_distance",
				
				"render_ssr_scale",
				"render_ssr_stretching",
				"render_ssr_noise",
				
				"render_motion_blur_quality",
				"motion_blur_depth_falloff",
				
				"render_profiler",
				
				"render_use_format_depth_d32f",
			);
			
			string renamed[] = (
				
				"render_specular_light": "render_lights_specular",
				
				"render_filter": "render_textures_filter",
				"render_anisotropy": "render_textures_anisotropy",
				
				"render_haze": "render_environment_haze",
				
				"budget": "render_budget",
				
				"render_soft_shadows_quality": "render_shadows_soft_quality",
				"render_lerp_cascades": "render_shadows_world_lerp_cascades",
				"render_omni_shadow_jitter": "render_shadows_omni_jitter",
				"render_soft_shadows": "render_shadows_soft",
				
				"render_world_light_per_forward_object": "render_lights_world_per_forward_object",
				"render_omni_lights_per_forward_object": "render_lights_omni_per_forward_object",
				"render_proj_lights_per_forward_object": "render_lights_proj_per_forward_object",
				"render_env_probes_per_forward_object": "render_lights_env_per_forward_object",
				
				"render_use_format_rg11b10": "render_screen_precision",
				
				"render_shadows_d32f": "render_shadows_precision",
				
				"distance_scale": "render_distance_scale",
				"field_distance": "render_field_distance",
				"light_distance": "render_light_distance",
				"decal_distance": "render_decal_distance",
				"object_distance": "render_object_distance",
				"clutter_distance": "render_clutter_distance",
				"shadow_distance": "render_shadow_distance",
				"reflection_distance": "render_reflection_distance",
				
				"taa_preserve_details": "render_taa_preserve_details",
				"taa_frame_count": "render_taa_frame_count",
				"taa_velocity_threshold": "render_taa_velocity_threshold",
				"taa_max_frame_count": "render_taa_max_frame_count",
				"taa_min_frame_count": "render_taa_min_frame_count",
				
				"animation_stem": "render_animation_stem",
				"animation_leaf": "render_animation_leaf",
				"animation_scale": "render_animation_scale",
				"animation_wind": "render_animation_wind",
				
				"reflection_color": "render_reflection_color",
				"wireframe_color": "render_wireframe_color",
				"background_color": "render_background_color",
				
				"ssao_radius": "render_ssao_radius",
				"ssao_intensity": "render_ssao_intensity",
				"ssao_intensity_lighted_side": "render_ssao_intensity_lighted_side",
				
				"ssgi_radius": "render_ssgi_radius",
				"ssgi_intensity": "render_ssgi_intensity",
				"ssgi_normal_threshold": "render_ssgi_normal_threshold",
				
				"sss_radius": "render_sss_radius",
				"sss_color": "render_sss_color",
				
				"refraction_dispersion": "render_refraction_dispersion",
				
				"motion_blur_velocity_scale": "render_motion_blur_velocity_scale",
				"motion_blur_max_velocity": "render_motion_blur_max_velocity",
				
				"sharpen_intensity": "render_sharpen_intensity",
				
				"fxaa_intensity": "render_fxaa_intensity",
				
				"shadow_shafts_exposure": "render_shadow_shafts_exposure",
				"shadow_shafts_length": "render_shadow_shafts_length",
				
				"dof_focal_distance": "render_dof_focal_distance",
				"dof_chromatic_aberration": "render_dof_chromatic_aberration",
				"dof_blur": "render_dof_blur",
				"dof_far_distance": "render_dof_far_distance",
				"dof_far_focal_offset": "render_dof_far_focal_offset",
				"dof_near_distance": "render_dof_near_distance",
				"dof_near_focal_offset": "render_dof_near_focal_offset",
				
				"camera_effects_threshold": "render_camera_effects_threshold",
				"dirt_scale": "render_dirt_scale",
				
				"exposure_mode": "render_exposure_mode",
				"exposure": "render_exposure",
				"exposure_adaptation": "render_exposure_adaptation",
				
				"bloom_scale": "render_bloom_scale",
				"bloom_power": "render_bloom_power",
				
				"filmic_shoulder_scale": "render_filmic_shoulder_scale",
				"filmic_linear_scale": "render_filmic_linear_scale",
				"filmic_linear_angle": "render_filmic_linear_angle",
				"filmic_toe_scale": "render_filmic_toe_scale",
				"filmic_toe_numerator": "render_filmic_toe_numerator",
				"filmic_toe_denominator": "render_filmic_toe_denominator",
				"filmic_white_level": "render_filmic_white_level",
				
				"cross_color": "render_cross_color",
				"cross_scale": "render_cross_scale",
				"cross_shafts": "render_cross_shafts",
				"cross_length": "render_cross_length",
				"cross_angle": "render_cross_angle",
				"cross_threshold": "render_cross_threshold",
				
				"sun_shafts_color": "render_sun_shafts_color",
				"sun_shafts_scale": "render_sun_shafts_scale",
				"sun_shafts_length": "render_sun_shafts_length",
				"sun_shafts_attenuation": "render_sun_shafts_attenuation",
				"sun_shafts_threshold": "render_sun_shafts_threshold",
				
				"lens_color": "render_lens_color",
				"lens_scale": "render_lens_scale",
				"lens_length": "render_lens_length",
				"lens_radius": "render_lens_radius",
				"lens_threshold": "render_lens_threshold",
				"lens_dispersion": "render_lens_dispersion",
				
				"fade_color": "render_fade_color",
				
				"render_queries": "render_occlusion_queries",
				"render_queries_num_frames": "render_occlusion_queries_num_frames",
				"render_show_number": "render_show_textures_offset",
				"render_show_offset": "render_show_textures_number",
			);
			
			foreach(string name; removed) {
				Xml element = xml.find(format("/item name=\"%s\"",name));
				if(element != NULL) {
					delete xml.removeChild(element);
				}
			}
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
				
				Xml x = xml.getChild(i);
				
				if(x.getName() != "item") continue;
				
				string name = x.getArg("name");
				
				if(renamed.check(name)) {
					x.setArg("name",renamed[name]);
				}
			}
		}
		
		xml.setArg("version",CONFIG_VERSION);
		
		xml.save(file);
		delete xml;
	}
	
} /* namespace Config */

#endif /* __MIGRATION_CONFIG_H__ */
