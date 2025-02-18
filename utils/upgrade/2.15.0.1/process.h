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
#include <utils.h>

namespace Process
{
	int check_data_name(Xml x, string name)
	{
		if (x.getNumChildren() > 0 && x.getChild(0).getName() == name)
			return 1;
		return 0;
	}

	void update_data(Xml doc, string where)
	{
		Xml copy = new Xml();
		copy.copy(doc);

		doc.clearChildren();

		Xml user_data = doc.addChild(where);

		if (copy.getNumChildren() != 0)
		{
			for (int i = 0; i < copy.getNumChildren(); i++)
			{
				Xml child = user_data.addChild(copy.getChild(i).getName());
				child.copy(copy.getChild(i));
			}
		} else
			user_data.setData(copy.getData());

		delete copy;
	}

	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/

	// .basemat
	int unigine_base_materials[] =
	(
		// Objects
		"mesh_base" : "",
		"water_mesh_base" : "",
		"water_global_base" : "",
		"volume_shaft_base" : "",
		"volume_proj_base" : "",
		"volume_omni_base" : "",
		"volume_light_base" : "",
		"volume_fog_base" : "",
		"volume_cloud_base" : "",
		"terrain_global_base" : "",
		"sky_base" : "",
		"particles_base" : "",
		"landscape_terrain_detail_base" : "",
		"landscape_map" : "",
		"landscape_terrain_base" : "",
		"text_base" : "",
		"gui_base" : "",
		"grass_impostor_base" : "",
		"grass_base" : "",
		"decal_terrain_hole_base" : "",
		"decal_base" : "",
		"clouds_base" : "",
		"billboards_impostor_base" : "",
		"billboards_cloud_base" : "",
		"billboards_base" : "",

		// Post
		"post_hblur_2d" : "",
		"post_vblur_2d" : "",
		"post_hblur_cube" : "",
		"post_vblur_cube" : "",
		"post_hblur_gauss" : "",
		"post_vblur_gauss" : "",
		"post_hblur_mask" : "",
		"post_vblur_mask" : "",
		"post_blur_radial" : "",
		"post_color_correction" : "",
		"post_filter_wet" : "",
		"post_filter_rgb2rgbl" : "",
		"post_filter_rgb2yuv" : "",
		"post_sensor" : "",
		"post_filter_sobel" : "",
		"post_hblur_2d" : "",
		"post_vblur_2d" : "",
		"post_hblur_2d" : "",
		"post_vblur_2d" : "",
		"post_hblur_2d" : "",
		"render_composite_deferred" : "",
		"render_composite" : "",
	);

	// .basemat / .basebrush
	int editor_base_materials[] =
	(
		"brush" : "",
		"brush_erase" : "",
		"brush_smooth" : "",
	);

	int unigine_inherited_materials[] =
	(
		// Billboards
		"billboards_stars" : "",

		// Clouds
		"clouds_altocumulus" : "",
		"clouds_altostratus" : "",
		"clouds_cirrocumulus" : "",
		"clouds_cirrostratus" : "",
		"clouds_cirrus" : "",
		"clouds_cumulonimbus1" : "",
		"clouds_cumulonimbus2" : "",
		"clouds_cumulonimbus3" : "",
		"clouds_cumulus" : "",
		"clouds_nimbostratus" : "",
		"clouds_stratocumulus" : "",
		"clouds_stratus" : "",

		// Decal
		"decal_water" : "",

		// Particles (just in case)
		"particles_base_error" : "",

		// Sky (just in case)
		"sky_base_error" : "",

		// Volumetrics (just in case)
		"volume_fog_base_error" : "",
		"volume_light_base_error" : "",
		"volume_omni_base_error" : "",
		"volume_proj_base_error" : "",

		// Water
		"water_global_beaufort_0" : "",
		"water_global_beaufort_1" : "",
		"water_global_beaufort_2" : "",
		"water_global_beaufort_3" : "",
		"water_global_beaufort_4" : "",
		"water_global_beaufort_5" : "",
		"water_global_beaufort_6" : "",
		"water_global_beaufort_7" : "",
		"water_global_beaufort_8" : "",
		"water_global_beaufort_9" : "",
		"water_global_beaufort_10" : "",
		"water_global_beaufort_11" : "",
		"water_global_beaufort_12" : "",
		"water_mesh_base_error" : "", // Just in case

		// Sensor
		"post_sensor_green" : "",
		"post_sensor_heat" : "",
		"post_sensor_red" : "",
		"post_sensor_white" : "",

		// Debug
		"debug_albedo" : "",
		"debug_ambient_light" : "",
		"debug_auxiliary" : "",
		"debug_baked_lightmap" : "",
		"debug_baked_occlusion" : "",
		"debug_bent_normals" : "",
		"debug_bevel" : "",
		"debug_cubemaps" : "",
		"debug_curvature" : "",
		"debug_diffuse_lighting" : "",
		"debug_direct_light" : "",
		"debug_dof_mask" : "",
		"debug_f0" : "",
		"debug_highlights" : "",
		"debug_isrgb" : "",
		"debug_light_meter" : "",
		"debug_lights" : "",
		"debug_materials" : "",
		"debug_metalness" : "",
		"debug_microfiber" : "",
		"debug_normals" : "",
		"debug_opacity_depth" : "",
		"debug_reflections" : "",
		"debug_roughness" : "",
		"debug_scene_depth" : "",
		"debug_ssao" : "",
		"debug_ssgi" : "",
		"debug_ssr" : "",
		"debug_translucent" : "",
		"debug_velocity" : "",
		"debug_water_normal" : "",

		// For World Creaion
		"grid_for_world_creation" : "",

		// Building presets
		"buildings_preset_0": "",
		"buildings_preset_0_basement": "",
		"buildings_preset_0_level_1_blank": "",
		"buildings_preset_0_level_2_blank": "",
		"buildings_preset_0_level_2_complex": "",
		"buildings_preset_0_roof": "",
		
		"buildings_preset_1": "",
		"buildings_preset_1_basement": "",
		"buildings_preset_1_level_1_blank": "",
		"buildings_preset_1_level_2_blank": "",
		"buildings_preset_1_level_2_complex": "",
		"buildings_preset_1_roof": "",
	);

	int unigine_scriptable_materials[] =
	(
		// Sensor
		"post_sensor_green" : "",
		"post_sensor_heat" : "",
		"post_sensor_red" : "",
		"post_sensor_white" : "",

		// Debug
		"debug_albedo" : "",
		"debug_ambient_light" : "",
		"debug_auxiliary" : "",
		"debug_baked_lightmap" : "",
		"debug_baked_occlusion" : "",
		"debug_bent_normals" : "",
		"debug_bevel" : "",
		"debug_cubemaps" : "",
		"debug_curvature" : "",
		"debug_diffuse_lighting" : "",
		"debug_direct_light" : "",
		"debug_dof_mask" : "",
		"debug_f0" : "",
		"debug_highlights" : "",
		"debug_isrgb" : "",
		"debug_light_meter" : "",
		"debug_lights" : "",
		"debug_materials" : "",
		"debug_metalness" : "",
		"debug_microfiber" : "",
		"debug_normals" : "",
		"debug_opacity_depth" : "",
		"debug_reflections" : "",
		"debug_roughness" : "",
		"debug_scene_depth" : "",
		"debug_ssao" : "",
		"debug_ssgi" : "",
		"debug_ssr" : "",
		"debug_translucent" : "",
		"debug_velocity" : "",
		"debug_water_normal" : "",
	);

	int unigine_base_materials_now_manual_materials_new_guids[] =
	(
		"post_deferred_albedo" : "",
		"post_deferred_auxiliary" : "",
		"post_deferred_bent_normal" : "",
		"post_deferred_bevel" : "",
		"post_deferred_curvate" : "",
		"post_deferred_dof_mask" : "",
		"post_deferred_f0" : "",
		"post_deferred_metalness" : "",
		"post_deferred_microfiber" : "",
		"post_deferred_normal" : "",
		"post_deferred_occlusion" : "",
		"post_deferred_opacity_depth" : "",
		"post_deferred_roughness" : "",
		"post_deferred_scene_depth" : "",
		"post_deferred_ssao" : "",
		"post_deferred_translucent" : "",
		"post_deferred_velocity" : "",
		"post_deferred_water_normal" : "",
	);
	
	int unigine_base_materials_now_manual_materials_new_base[] =
	(
		"post_deferred_albedo"        : "Unigine::render_composite_deferred",
		"post_deferred_auxiliary"     : "Unigine::render_composite_deferred",
		"post_deferred_bent_normal"   : "Unigine::render_composite_deferred",
		"post_deferred_bevel"         : "Unigine::render_composite_deferred",
		"post_deferred_curvate"       : "Unigine::render_composite_deferred",
		"post_deferred_dof_mask"      : "Unigine::render_composite_deferred",
		"post_deferred_f0"            : "Unigine::render_composite_deferred",
		"post_deferred_metalness"     : "Unigine::render_composite_deferred",
		"post_deferred_microfiber"    : "Unigine::render_composite_deferred",
		"post_deferred_normal"        : "Unigine::render_composite_deferred",
		"post_deferred_occlusion"     : "Unigine::render_composite_deferred",
		"post_deferred_opacity_depth" : "Unigine::render_composite_deferred",
		"post_deferred_roughness"     : "Unigine::render_composite_deferred",
		"post_deferred_scene_depth"   : "Unigine::render_composite_deferred",
		"post_deferred_ssao"          : "Unigine::render_composite_deferred",
		"post_deferred_translucent"   : "Unigine::render_composite_deferred",
		"post_deferred_velocity"      : "Unigine::render_composite_deferred",
		"post_deferred_water_normal"  : "Unigine::render_composite_deferred",
	);

	int unigine_base_materials_now_manual_materials_new_names[] =
	(
		"post_deferred_albedo"        : "Unigine::debug_albedo",
		"post_deferred_auxiliary"     : "Unigine::debug_auxiliary",
		"post_deferred_bent_normal"   : "Unigine::debug_bent_normal",
		"post_deferred_bevel"         : "Unigine::debug_bevel",
		"post_deferred_curvate"       : "Unigine::debug_curvature",
		"post_deferred_dof_mask"      : "Unigine::debug_dof_mask",
		"post_deferred_f0"            : "Unigine::debug_f0",
		"post_deferred_metalness"     : "Unigine::debug_metalness",
		"post_deferred_microfiber"    : "Unigine::debug_microfiber",
		"post_deferred_normal"        : "Unigine::debug_normal",
		"post_deferred_occlusion"     : "Unigine::debug_occlusion",
		"post_deferred_opacity_depth" : "Unigine::debug_opacity_depth",
		"post_deferred_roughness"     : "Unigine::debug_roughness",
		"post_deferred_scene_depth"   : "Unigine::debug_scene_depth",
		"post_deferred_ssao"          : "Unigine::debug_ssao",
		"post_deferred_translucent"   : "Unigine::debug_translucent",
		"post_deferred_velocity"      : "Unigine::debug_velocity",
		"post_deferred_water_normal"  : "Unigine::debug_water_normal",
	);

	int user_migrated_materials[] = ( "" : "" );
	int editor_base_materials_by_old_guids[] = ( "" : "" );
	int unigine_base_materials_by_old_guids[] = ( "" : "" );
	int unigine_scriptable_materials_new_guid[] = ( "" : "" );
	int unigine_inherited_materials_by_old_guids[] = ( "" : "" );
	int unigine_base_materials_now_manual_materials_by_old_guids[] = ( "" : "" );

	int generated_guids = false;

	void generate_guids()
	{
		if (generated_guids == false)
		{
			generated_guids = true;

			forloop (int i = 0; unigine_base_materials.size())
			{
				string material = unigine_base_materials.key(i);

				unigine_base_materials[material] = stringToGUID("Unigine::" + material);
				unigine_base_materials_by_old_guids[stringToGUID(material)] = stringToGUID("Unigine::" + material);
			}
			
			forloop (int i = 0; editor_base_materials.size())
			{
				string material = editor_base_materials.key(i);

				editor_base_materials[material] = stringToGUID("Editor::" + material);
				editor_base_materials_by_old_guids[stringToGUID(material)] = stringToGUID("Editor::" + material);
			}


			forloop (int i = 0; unigine_inherited_materials.size())
			{
				string material = unigine_inherited_materials.key(i);

				unigine_inherited_materials[material] = stringToGUID("Unigine::" + material);
				unigine_inherited_materials_by_old_guids[stringToGUID(material)] = stringToGUID("Unigine::" + material);
			}
			
			// Special cases
			forloop (int i = 0; unigine_base_materials_now_manual_materials_new_names.size())
			{
				string key = unigine_base_materials_now_manual_materials_new_names.key(i);
				string material = unigine_base_materials_now_manual_materials_new_names[key];
				
				unigine_base_materials_now_manual_materials_new_guids[key] = stringToGUID(material);
				unigine_base_materials_now_manual_materials_by_old_guids[stringToGUID(key)] = stringToGUID(material);
			}

			forloop (int i = 0; unigine_scriptable_materials.size())
			{
				string key = unigine_scriptable_materials.key(i);

				unigine_scriptable_materials[key] = stringToGUID(key);
				unigine_scriptable_materials_new_guid[key] = stringToGUID("Unigine::" + key);
			}
		}
	}

	int migrate_base_materials_to_inherited_materials(string old_parent, string old_base_name, string &new_base_name, string &new_parent)
	{
		new_base_name = old_base_name;

		// Search by name
		string value = unigine_scriptable_materials.find(old_parent, "");
		if (value != "")
		{
			new_parent = unigine_scriptable_materials_new_guid[value];
			string temp = unigine_base_materials_by_old_guids.find(old_base_name, "");
			new_base_name = unigine_base_materials_by_old_guids[temp];
		} else
		{
			value = unigine_base_materials_now_manual_materials_new_names.check(old_parent, "");
			if (value != "")
			{
				new_base_name = stringToGUID(unigine_base_materials_now_manual_materials_new_base[old_parent]);
				new_parent = unigine_base_materials_now_manual_materials_new_guids[old_parent];
			} else
			{
				// Search by guid
				value = unigine_base_materials_now_manual_materials_by_old_guids.check(old_parent, "");
				if (value != "")
				{
					// Convert GUID to name
					string material_name = unigine_inherited_materials.check(old_parent, "");

					new_base_name = stringToGUID(unigine_base_materials_now_manual_materials_new_base[material_name]);
					new_parent = value;
				} else
				{
					value = unigine_base_materials_now_manual_materials_new_names.check(old_base_name, "");
					if (value != "")
					{
						new_base_name = stringToGUID(unigine_base_materials_now_manual_materials_new_base[old_base_name]);
						new_parent = unigine_base_materials_now_manual_materials_new_guids[old_base_name];
					}
				}
			}
		}

		return (value != "");
	}

	int migrate_to_new_parent_material(string old_parent, string &new_parent_guid)
	{
		// Search by material's name
		string value = unigine_inherited_materials.check(old_parent, "");
		if (value != "")
		{
			new_parent_guid = value;
		} else
		{
			// Search by material's guid
			value = unigine_inherited_materials_by_old_guids.check(old_parent, "");
			if (value != "")
				new_parent_guid = value;
		}
		
		return (value != "");
	}

	int migrate_to_new_base_material(string old_base_name, string &new_base_name, string &new_base_guid)
	{
		new_base_name = old_base_name;

		// Search by material's name
		string value = unigine_base_materials.check(old_base_name, "");
		if (value != "")
		{
			new_base_guid = value;
			new_base_name = new_base_guid;
		} else 
		{
			// Search by material's name
			value = editor_base_materials.check(old_base_name, "");
			if (value != "")
			{
				new_base_guid = value;
				new_base_name = new_base_guid;
			} else 
			{
				// Search by material's guid
				value = editor_base_materials_by_old_guids.check(old_base_name, "");
				if (value != "")
				{
					new_base_guid = value;
					new_base_name = new_base_guid;
				} else {
					// Search by old base guid
					value = unigine_base_materials_by_old_guids.check(old_base_name, "");
					if (value != "")
					{
						new_base_guid = value;
						new_base_name = new_base_guid;
					}
				}
			}
		}

		return (value != "");
	}

	void material(Material m)
	{
		// Fail-safe
		generate_guids();

		if (m.getBaseMaterial() == "volume_cloud_base")
		{
			m.renameState("use_sky_color", "use_environment_lighting");
			m.renameTexture("density", "density_3d");

			m.addTexture("density_2d");
			m.setTextureValue("density_2d", m.getTextureValue("density_3d"));
			
			if (m.hasState("samples"))
			{
				// From index for array of values [8, 16, 32, .., 256]
				// To value
				int value = int(m.getStateValue("samples"));
				m.setStateValue("samples", string(1 << (3 + value)));
			}
		} else if (m.getBaseMaterial() == "water_global_base")
		{
			m.removeParameter("chunk0");
			m.removeParameter("chunk1");
			m.removeParameter("chunk2");
			m.removeParameter("chunk3");
			m.removeParameter("chunk4");
			m.removeParameter("chunk5");
		} else if (m.getBaseMaterial() == "water_mesh_base")
		{
			m.removeParameter("chunk0");
			m.removeParameter("chunk1");
			m.removeParameter("chunk2");
			m.removeParameter("chunk3");
			m.removeParameter("chunk4");
			m.removeParameter("chunk5");
			
			m.renameParameter("coast_foam_intensity", "foam_contact_intensity");
			m.renameParameter("ambient_subsurface_intensity", "subsurface_ambient_intensity");
			m.renameParameter("wave_subsurface_intensity", "subsurface_wave_intensity");
			m.renameParameter("wave_foam_subsurface_intensity", "subsurface_wave_foam_intensity");
			m.renameParameter("diffuse_subsurface_intensity", "subsurface_diffuse_intensity");
			m.renameParameter("caustic_fade", "caustic_distance_fade");
			
			m.renameTexture("caustic_texture", "caustic");
			m.renameTexture("water_normal_detail_texture", "normal_detail");
			
		} else if (m.getBaseMaterial() == "mesh_base")
		{
			m.removeParameter("color");
			m.removeParameter("shading");
			m.removeParameter("detail_color");
			m.removeParameter("detail_shading");
			m.removeParameter("detail_color_visible");
			m.removeParameter("detail_shading_visible");
		} else if (m.getBaseMaterial() == "grass_impostor_base")
		{
			m.removeParameter("impostor_transform");
		} else if (m.getBaseMaterial() == "decal_base")
		{
			m.removeParameter("shading");
			m.removeParameter("visible");
			m.removeParameter("detail_shading");
			m.removeParameter("detail_shading_visible");
			m.removeParameter("fade");
		} else if (m.getBaseMaterial() == "billboardds_impostor_base")
		{
			m.removeParameter("impostor_transform");
		}

		m.removeOption("receive_shadow");
		m.removeOption("receive_world_shadow");

		if (m.isManualMaterial() == false)
		{
			string name = "empty";
			if (m.xml.isArg("name"))
			{
				name = m.xml.getArg("name");
				xmlRemoveArg(m.xml, "name");

				user_migrated_materials[name] = m.getGUID();
			} else
			{
				Log::warning("Process::material(): encountered material without name %s\n", m.getGUID());
			}


			string old_base_name = m.getBaseMaterial();
			string new_base_name = "";
			string old_base_guid = stringToGUID(old_base_name);
			string new_base_guid = "";
			int is_user_mat = true;
			if (migrate_to_new_base_material(old_base_name, new_base_name, new_base_guid))
			{
				m.setBaseMaterial(new_base_name);
				is_user_mat = false;
			}


			string old_parent_name = m.getParentGUID();
			string old_parent_guid = stringToGUID(old_parent_name);
			string new_parent_guid = "";
			if (migrate_base_materials_to_inherited_materials(old_parent_name, new_base_name, new_base_name, new_parent_guid))
			{
				m.setParentGUID(new_parent_guid);
				m.setBaseMaterial(new_base_name);

				is_user_mat = false;
			} else if (migrate_to_new_parent_material(old_parent_name, new_parent_guid))
				m.setParentGUID(new_parent_guid);
			else if (old_parent_guid == old_base_guid)
				m.setParentGUID(new_base_guid);

			// Use GUID of basemat name instead of name for user defined materials (both inherited and basemat)
			if (is_user_mat)
				m.setBaseMaterial(stringToGUID(old_base_name));
		}
	}
	
	/******************************************************************************\
	*
	* Property
	*
	\******************************************************************************/
	
	// local changes of the property file
	void propertyFile(Xml xml)
	{
	}
	
	// global changes that related to another properties
	void property(Properties::Property p)
	{
	}
	
	/******************************************************************************\
	*
	* Nodes
	*
	\******************************************************************************/
	
	int material_migrate_guid(string old_material, string &new_material)
	{
		new_material = old_material;

		// Search by material's GUID
		string value = unigine_base_materials_by_old_guids.check(old_material, "");
		if (value != "")
		{
			new_material = value;
		} else
		{
			// Search by material's name
			value = unigine_base_materials.check(old_material, "");
			if (value != "")
			{
				new_material = value;
			} else
			{
				// Search through possible parents by guid
				value = unigine_inherited_materials_by_old_guids.check(old_material, "");
				if (value != "")
				{
					new_material = value;
				} else
				{
					// Search by name
					value = unigine_inherited_materials.check(old_material, "");
					if (value != "")
						new_material = value;
				}
			}
		}
		
		return (value != "");
	}

	void migrate_scriptable_materials(Xml xml)
	{
		for (int j = 0; j < xml.getNumChildren(); j++)
		{
			Xml m = xml.getChild(j);

			string old_material = m.getArg("guid");
			string new_material = "";

			if (material_migrate_guid(old_material, new_material))
				m.setArg("guid", new_material);
		}
	}

	/* Remove this old thing
			<settings>
				<item name="save_camera">1</item>
			</settings>
	*/
	void remove_editor_settings(Xml xml)
	{
		Xml settings = xmlGetChild(xml, "settings");
		if (settings != NULL)
		{
			for (int i = 0; i < settings.getNumChildren(); i++)
			{
				Xml item = settings.getChild(i);
				if (xmlGetArg(item, "name") == "save_camera")
				{
					delete settings.removeChild(item);
					i--;
				}
			}
			
			if (settings.getNumChildren() == 0)
				delete xml.removeChild("settings");
		}
	}

	void migrate_post_and_debug_materials(Xml xml, string materials, string &result[])
	{
		string material_list[128];
		strsplit(materials, ",", material_list);
		
		for (int i = 0; i < material_list.size(); i++)
		{
			string old_name = material_list[i];
			string old_guid = stringToGUID(old_name);
			string new_guid = "";
			
			// Search by material guid
			if (material_migrate_guid(old_guid, new_guid) == 0)
			{
				// Search by material name
				if (material_migrate_guid(old_name, new_guid) == 0)
				{
					// Search by migrated materials
					string guid = user_migrated_materials.check(old_name, "");
					
					if (guid != "")
					{
						new_guid = guid;
					} else
					{
						new_guid = old_name;
						
						guid = unigine_base_materials_now_manual_materials_new_guids.check(old_name, "");
						if (guid != "")
						{
							result.append(guid);
							// Don't add if migrated to debug materials
							continue;
						}
					}
				}
			}
			
			Xml m = xml.addChild("material");
			m.setArg("guid", new_guid);
			m.setArg("enabled", "1");
		}
	}

	void node(Xml xml)
	{
		// We might not encounter surfaces or materials to migrate
		generate_guids();

		string type = xml.getArg("type");
		int player_type_list[] = ( "PlayerSpectator", "PlayerActor", "PlayerDummy", "Player", "PlayerPersecutor" );
		int is_player = (player_type_list.find(type) != -1);
		int is_voxel_probe = (type == "LightVoxelProbe");

		for (int i = 0; i < xml.getNumChildren(); i++)
		{
			Xml child = xml.getChild(i);
			if (child.getName() == "data")
			{
				remove_editor_settings(child);

				if (type == "ObjectBillboards" && check_data_name(child, "generator"))
					update_data(child, "unigine_editor");
				else if (type == "ObjectMeshCluster" && check_data_name(child, "cluster_editor"))
					update_data(child, "unigine_editor");
				else
					update_data(child, "user");
			} else if (is_player)
			{
				if (child.getName() == "scriptable_materials")
				{
					migrate_scriptable_materials(child);
				} else if (child.getName() == "post_materials")
				{
					string result[128];
					Xml scriptable_materials = xmlAddChild(xml, "scriptable_materials");
					migrate_post_and_debug_materials(scriptable_materials, child.getData(), result);
				}
			} else if (is_voxel_probe && (child.getName() == "use_sun_color"))
			{
				child.setName("use_sky_color");
			} else if (child.getName() == "surface")
			{
				if (child.isArg("material"))
				{
					string old_material = child.getArg("material");
					string new_material = "";

					if (material_migrate_guid(old_material, new_material))
						child.setArg("material", new_material);
				}
			}
		}

		if (type == "ObjectLandscapeTerrain")
		{
			for (int j = 0; j < xml.getNumChildren(); j++)
			{
				Xml detail_mask = xml.getChild(j);
				Xml detail = xmlGetChild(detail_mask, "detail");

				if (detail != NULL)
				{
					string old_material = detail.getArg("material");
					string new_material = "";
					if (material_migrate_guid(old_material, new_material))
						detail.setArg("material", new_material);
				}
			}
		}

		if (xml.isArg("material"))
		{
			string old_name = xml.getArg("material");
			string new_name = "";
			if (material_migrate_guid(old_name, new_name))
				xml.setArg("material", new_name);
		}

		xmlDeleteChild(xml, "post_materials");
	}

	void surfaceProperty(Xml xml_surface, Xml xml_prop, Properties::Property prop)
	{
	}
	
	/******************************************************************************\
	*
	* Bodies
	*
	\******************************************************************************/
	void body(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Shapes
	*
	\******************************************************************************/
	void shape(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Joints
	*
	\******************************************************************************/
	void joint(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Render
	*
	\******************************************************************************/
	void render(Xml xml)
	{
		// Fail-safe
		generate_guids();

		xmlRenameChild(xml, "render_filmic", "render_tonemapper");
		xmlRenameChild(xml, "render_streaming_upadte_limit", "render_streaming_update_limit");
		xmlRenameChild(xml, "render_ssr_denoise_gussian_sigma", "render_ssr_denoise_gaussian_sigma");

		string debug_materials_list[256];
		for(int i = 0; i < xml.getNumChildren(); i++) 
		{
			Xml x = xml.getChild(i);
			string name = x.getName();

			if (name == "post_materials") // Post -> Scriptable
			{
				// Debug materials have been migrated from Post materials to Debug materials
				// So we keep track of them
				Xml target = xmlAddChild(xml, "scriptable_materials");
				migrate_post_and_debug_materials(target, x.getData(), debug_materials_list);
			} else if (name == "render_debug_materials") // Old Debug -> New Debug Scriptable
			{
				Xml target = xmlAddChild(xml, "debug_materials");

				// Assume that post_materials will be first
				for (int i = 0; i < debug_materials_list.size(); i++)
				{
					string guid = debug_materials_list[i];
					if (guid == "")
						continue;

					Xml m = target.addChild("material");
					m.setArg("guid", guid);
					m.setArg("enabled", "1");
				}

				string empty[128];
				migrate_post_and_debug_materials(target, x.getData(), empty);
			} else if (name == "scriptable_materials") // Migrate GUIDs for Scriptable Materials
			{
				migrate_scriptable_materials(x);
			}
		}

		xmlDeleteChild(xml, "render_debug_materials");
		xmlDeleteChild(xml, "post_materials");

		Xml x = xmlGetChild(xml, "composite_material");
		if (x != NULL)
		{
			string old_name = x.getData();
			string new_guid = "";
			if (material_migrate_guid(old_name, new_guid))
				x.setData(new_guid);
			else
				x.setData(old_name);
		}

		x = xmlGetChild(xml, "render_composite_deferred_material");
		if (x != NULL)
		{
			string old_name = x.getData();
			xmlDeleteChild(xml, "render_composite_deferred_material");
			x = xml.addChild("composite_deferred_material_guid");

			string new_guid = "";
			if (material_migrate_guid(old_name, new_guid))
				x.setData(new_guid);
			else
				x.setData(old_name);
		}

		//Xml xml_new = new Xml();
		//string path_render = pathname(replace(__FILE__, "\\", "/")) + "render.xml";
		//if(xml_new.load(path_render)) 
		//{
		//	for(int i = 0; i < xml.getNumChildren(); i++) 
		//	{
		//		Xml x = xml.getChild(i);
		//		
		//		// TODO: remove in next version after fix En-7009
		//		if (x.getName() == "scriptable_materials")
		//			continue;
		//		
		//		if (xml_new.findChild(x.getName()) != -1)
		//			continue;
		//		delete xml.removeChild(x);
		//		i--;
		//	}
		//	
		//	xmlMergeChildren(xml_new, xml);
		//}
		//delete xml_new;
	}
	
	/******************************************************************************\
	*
	* Sound
	*
	\******************************************************************************/
	void sound(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Physics
	*
	\******************************************************************************/
	void physics(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* World
	*
	\******************************************************************************/
	void world(Xml xml)
	{
		Xml old_data = NULL;
		Xml old_editor = NULL;

		for (int i = 0; i < xml.getNumChildren(); i++)
		{
			Xml child = xml.getChild(i);
			if (child.getName() == "data")
			{
				old_data = child;
			} else if (child.getName() == "editor")
			{
				old_editor = child;
			}
		}

		if (old_data != NULL)
		{
			remove_editor_settings(old_data);
			update_data(old_data, "user");
		}

		if (old_editor != NULL)
		{
			remove_editor_settings(old_editor);
			for (int i = 0; i < old_editor.getNumChildren(); i++)
			{
				Xml child = old_editor.getChild(i);
				remove_editor_settings(child);
				if (child.getName() == "data")
				{
					update_data(child, "unigine_editor");
					break;
				}
			}
		}
	}
	
	/******************************************************************************\
	*
	* Track
	*
	\******************************************************************************/
	string migrate_tracker_material(string old_name)
	{
		string new_base_name = "";
		string new_base_guid = "";
		string new_parent_guid = "";
		if (migrate_to_new_base_material(old_name, new_base_name, new_base_guid))
			return new_base_guid;
		else if (migrate_to_new_parent_material(old_name, new_parent_guid))
			return new_parent_guid;
		
		// Search by migrated materials
		string new_guid = user_migrated_materials.check(old_name, "");
		if (new_guid != "")
			return new_guid;
		
		return old_name;
	}

	int migrate_post_and_debug_material_tracker(string materials, string &new_material)
	{
		string material_list[128];
		strsplit(materials, ",", material_list);

		new_material = materials;
		if (material_list.size() == 0)
			return false;

		// We migrate only first material from the list
		string old_name = material_list[0];
		string old_guid = stringToGUID(old_name);
		new_material = old_name;

		// Search by material guid
		if (material_migrate_guid(old_guid, new_material) == 0)
		{
			// Search by material name
			if (material_migrate_guid(old_name, new_material) == 0)
				// Search by migrated materials
			{
				string guid = user_migrated_materials.check(old_name, "");

				if (guid != "")
				{
					new_material = guid;
					return true;
				} else
				{
					guid = unigine_base_materials_now_manual_materials_new_guids.check(old_name, "");
					if (guid != "")
					{
						new_material = materials[0];
						return true;
					}
				}
			} else
			{
				return true;
			}
		} else
		{
			return true;
		}

		return false;
	}

	void migrate_post_and_debug_material_tracker_keys(Xml param)
	{
		for (int i = 0; i < param.getNumChildren(); i++)
		{
			Xml key = param.getChild(i);
			
			if (key.getName() != "key")
				continue;
			
			string old_material = key.getData();
			string new_material = "";
			if (migrate_post_and_debug_material_tracker(old_material, new_material))
				key.setData("guid://" + new_material);
		}
	}

	void track(Xml xml)
	{
		// Fail-safe
		generate_guids();

		for (int i = 0; i < xml.getNumChildren(); i++)
		{
			Xml param = xml.getChild(i);

			if (!param.isArg("type"))
				continue;

			string type = param.getArg("type");

			if (startsWith(type, "material"))
			{
				if (type == "material.offset")
				{
					delete xml.removeChild(param);
					i--;
				} else
				{
					if (param.isArg("name"))
					{
						string old_name = param.getArg("name");
						xmlRemoveArg(param, "name");
						param.setArg("guid", migrate_tracker_material(old_name));
					}
				}
			} else if (type == "node.object.material")
			{
				migrate_post_and_debug_material_tracker_keys(param);
			} else if (type == "render.postMaterials")
			{
				param.setArg("type", "render.scriptableMaterial");
				migrate_post_and_debug_material_tracker_keys(param);
			} else if(type == "game.player.postMaterials")
			{
				param.setArg("type", "game.player.scriptableMaterial");
				migrate_post_and_debug_material_tracker_keys(param);
			}
		}
	}

	/******************************************************************************\
	*
	* Meta
	*
	\******************************************************************************/
	void meta(Xml xml, string file_name)
	{
	}
	
	/******************************************************************************\
	*
	* AppProjection
	*
	\******************************************************************************/
	void projectionBinary(string file_name)
	{
	}
	
	void projection(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Syncker
	*
	\******************************************************************************/
	void synckerBinary(string file_name)
	{
	}
	
	void syncker(Xml xml)
	{
	}
	
	/******************************************************************************\
	*
	* Configs
	*
	\******************************************************************************/
	void configBoot(Xml xml)
	{
	}
	void configControls(Xml xml)
	{
	}
	void configUser(Xml xml)
	{
		xmlDeleteChild(xml, "render_show_mipmaps");
	}

	/******************************************************************************\
	*
	* Sandworm
	*
	\******************************************************************************/
	void sandworm(Sandworm::Scene scene)
	{
		// 1 - Object Landscape Terrain
		Sandworm::ExportSceneParameters export_parameters = scene.parameters.export_parameters;
		if (export_parameters.getParameter("export_format") == 1)
		{
			Json to_generate_json = new Json("to_generate");
			to_generate_json.addChild("elevations").setBool(true);
			to_generate_json.addChild("imageries").setBool(true);
			to_generate_json.addChild("details").setBool(true);
			to_generate_json.addChild("landcovers").setBool(true);
			to_generate_json.addChild("vectors").setBool(true);
			string value = to_generate_json.getFormattedSubTree();
			scene.parameters.generation_parameters.addParameter("to_generate", Sandworm::STRING, value);
		}

		Sandworm::Source vector_source = scene.findSource(Sandworm::Vector);
		scene.process(vector_source);

		Sandworm::Source mask_source = scene.findSource(Sandworm::Mask);
		scene.process(mask_source);
	}
}

#endif /* __MIGRATION_PROCESS_H__ */
