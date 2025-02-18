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

#include <utils.h>

namespace Process
{
	void change_type_to_string(Xml parameter)
	{
		if (xmlGetArg(parameter, "type") != "string")
			xmlSetArg(parameter, "type", "string");
	}

	void migrate_fbx_parameters(Xml parameters)
	{
		if (parameters == NULL)
			return;

		forloop(int i = 0; parameters.getNumChildren())
		{
			Xml parameter = parameters.getChild(i);
			if (parameter.getName() == "parameter")
			{
				string name = xmlGetArg(parameter, "name");

				if (name == "import_materials_mode")
					migrate_fbx_import_materials_mode(parameter);
				else if (name == "workflow")
					migrate_fbx_workflow(parameter);
				else if (name == "resolution")
					migrate_fbx_resolution(parameter);
				else if (name == "up_axis" || name == "front_axis")
					migrate_fbx_axis(parameter);
			}
		}
	}

	void migrate_fbx_import_materials_mode(Xml parameter)
	{
		change_type_to_string(parameter);

		string data = parameter.getData();

		if (data == "0")
			parameter.setData("take_by_name_or_create");
		else if (data == "1")
			parameter.setData("overwrite");
		else if (data == "2")
			parameter.setData("take_by_name_not_create");
	}

	void migrate_fbx_workflow(Xml parameter)
	{
		change_type_to_string(parameter);

		string data = parameter.getData();

		if (data == "0")
			parameter.setData("metalness");
		else if (data == "1")
			parameter.setData("specular");
	}

	void migrate_fbx_resolution(Xml parameter)
	{
		change_type_to_string(parameter);

		string data = parameter.getData();

		if (data == "0")
			parameter.setData("32");
		else if (data == "1")
			parameter.setData("64");
		else if (data == "2")
			parameter.setData("128");
		else if (data == "3")
			parameter.setData("256");
		else if (data == "4")
			parameter.setData("512");
		else if (data == "5")
			parameter.setData("1024");
		else if (data == "6")
			parameter.setData("2048");
		else if (data == "7")
			parameter.setData("4096");
	}

	void migrate_fbx_axis(Xml parameter)
	{
		change_type_to_string(parameter);

		string data = parameter.getData();

		if (data == "0")
			parameter.setData("default");
		else if (data == "1")
			parameter.setData("x");
		else if (data == "2")
			parameter.setData("nx");
		else if (data == "3")
			parameter.setData("y");
		else if (data == "4")
			parameter.setData("ny");
		else if (data == "5")
			parameter.setData("z");
		else if (data == "6")
			parameter.setData("nz");
	}

	/******************************************************************************\
	*
	* Path
	*
	\******************************************************************************/

	void processPath(string data_path)
	{
		remove_file(data_path + ".editor2/settings/migration.cfg");
	}

	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/

	void material(Material m)
	{
		// water mesh upgrade
		if (m.getBaseMaterial() == "14b090efbf69a454b2033bac1ee2cfcc700e8b99")
		{
			// Unigine::water_mesh_base
			m.renameParameter("subsurface_diffuse_intensity", "subsurface_decals_intensity");
			m.renameParameter("diffuse_distortion", "decals_distortion");
			m.renameParameter("soft_intersection", "soft_interaction");

		} else if (m.getBaseMaterial() == "b7c07dfd4ce80edac55fcbfdd0befa02ccd20b88")
		{
			// Unigine::particles_base
			if (m.hasTexture("emission_color"))
			{
				Texture texture = m.textures["emission_color"];
				int num_saved_channels = texture.xml.getNumChildren();
				for (int j = 3; j < num_saved_channels; j++)
					texture.xml.removeChild(texture.xml.getChild(j));
			}
		}
	}

	/******************************************************************************\
	*
	* MaterialGraphs
	*
	\******************************************************************************/

	void materialGraph(MaterialGraph graph)
	{
		foreach(MaterialGraphNode node; graph.nodes)
		{
			materialNode(node);
		}
	}

	void materialNode(MaterialGraphNode node)
	{
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
	int is_light(string type)
	{
		return type == "LightWorld" || type == "LightProj" || type == "LightOmni"
			|| type == "LightVoxelProbe" || type == "LightEnvironmentProbe" || type == "LightPlanarProbe";
	}

	int is_immovable_supported(string node_type)
	{
		if (node_type == "ObjectMeshStatic") return 1;
		if (node_type == "ObjectMeshCluster") return 1;
		if (node_type == "ObjectBillboards") return 1;
		if (node_type == "ObjectVolumeBox") return 1;
		if (node_type == "ObjectVolumeSphere") return 1;
		if (node_type == "ObjectVolumeOmni") return 1;
		if (node_type == "ObjectVolumeProj") return 1;
		if (node_type == "ObjectGui") return 1;
		if (node_type == "ObjectGuiMesh") return 1;
		if (node_type == "ObjectText") return 1;

		return 0;
	}

	int has_movable_body(Xml xml)
	{
		if (!xml.isChild("body"))
			return 0;

		Xml body_xml = xml.getChild("body");

		if (body_xml.getArg("type") == "BodyDummy")
			return 0;

		return 1;
	}

	void node(Xml xml)
	{
		string type = xml.getArg("type");

		if (is_light(type))
		{
			xmlRenameChild(xml, "render_water", "render_on_water");
			xmlRenameChild(xml, "render_transparent", "render_on_transparent");

			if (type == "LightEnvironmentProbe")
			{
				xmlRenameChild(xml, "is_box_projection", "projection_mode");
				xmlRenameChild(xml, "is_local_space", "local_space");
				xmlRenameChild(xml, "is_sky_cutout", "sky_cutout");
				xmlRenameChild(xml, "is_cutout_by_shadow", "cutout_by_shadow");
				xmlRenameChild(xml, "use_sun_color", "multiply_by_sky_color");

				xmlRenameChild(xml, "is_box_gi", "box_ambient_parallax");

				xmlRenameChild(xml, "is_dynamic", "grab_mode");
				xmlRenameChild(xml, "render_faces_per_frame", "grab_dynamic_faces_per_frame");
				xmlRenameChild(xml, "reflection_viewport_mask", "grab_viewport_mask");
				xmlRenameChild(xml, "zfar", "grab_zfar");
				xmlRenameChild(xml, "znear", "grab_znear");
				xmlRenameChild(xml, "distance_scale", "grab_distance_scale");
				xmlDeleteChild(xml, "bake_mipmaps_quality");

				int num = xml.findChild("resolution");
				if (num != -1)
				{
					Xml resolution = xml.getChild(num);
					resolution.setName("grab_resolution");

					if (resolution.getIntData() == -1)
						resolution.setData(3);
				}

				num = xml.findChild("supersampling");
				if (num != -1)
				{
					Xml supersampling = xml.getChild(num);
					supersampling.setName("grab_supersampling");

					if (supersampling.getIntData() == -1)
						supersampling.setData(0);
				}

				xmlRenameChild(xml, "bake_visibility_emission", "grab_bake_visibility_emission");
				xmlRenameChild(xml, "bake_visibility_sky", "grab_bake_visibility_sky");
				xmlRenameChild(xml, "bake_visibility_light_world", "grab_bake_visibility_light_world");
				xmlRenameChild(xml, "bake_visibility_light_omni", "grab_bake_visibility_light_omni");
				xmlRenameChild(xml, "bake_visibility_light_proj", "grab_bake_visibility_light_proj");
				xmlRenameChild(xml, "bake_visibility_voxel_probe", "grab_bake_visibility_voxel_probe");
				xmlRenameChild(xml, "bake_visibility_environment_probe", "grab_bake_visibility_environment_probe");
				xmlRenameChild(xml, "bake_visibility_lightmap", "grab_bake_visibility_lightmap");

				xmlRenameChild(xml, "parallax", "sphere_reflection_parallax");

				num = xml.findChild("correct_roughness_mode");
				if (num != -1)
				{
					Xml correct_roughness_mode = xml.getChild(num);
					correct_roughness_mode.setName("grab_ggx_mipmaps_quality");

					int value = correct_roughness_mode.getIntData();

					// If project was created/migrated after 2.15. Before 2.15 there was clamp(x, 0, 4)
					if (value > 0)
						correct_roughness_mode.setData(value - 1);
				}
			}
		} else if (type == "ObjectWaterGlobal")
		{
			xmlRenameChild(xml, "diffuse_distortion", "decals_distortion");
			xmlRenameChild(xml, "soft_intersection", "soft_interaction");
			xmlRenameChild(xml, "diffuse_intensity", "decals_intensity");
			xmlRenameChild(xml, "subsurface_diffuse_intensity", "subsurface_decals_intensity");
		} else if (type == "ObjectGrass")
		{
			string intersection_mask = "-1";
			int num = xml.findChild("surface");
			if(num != -1)
			{
				Xml child = xml.getChild(num);
				intersection_mask = xmlGetArg(child, "intersection_mask", intersection_mask);
			}
			xmlSetChildValue(xml, "intersection_mask", intersection_mask);
		}

		if (xml.isArg("immovable") && (!is_immovable_supported(type) || has_movable_body(xml)))
		{
			xml.removeArg("immovable");
		}

		string intersection_supported[] = (
			"ObjectCloudLayer": 1,
			"ObjectExtern": 1,
			"ObjectGui": 1,
			"ObjectGuiMesh": 1,
			"ObjectLandscapeTerrain": 1,
			"ObjectMeshCluster": 1,
			"ObjectMeshClutter": 1,
			"ObjectMeshDynamic": 1,
			"ObjectMeshSkinned": 1,
			"ObjectMeshSplineCluster": 1,
			"ObjectMeshStatic": 1,
			"ObjectTerrainGlobal": 1,
			"ObjectWaterGlobal": 1,
		);

		string collision_supported[] = (
			"ObjectExtern": 1,
			"ObjectMeshStatic": 1,
			"ObjectMeshCluster": 1,
			"ObjectMeshClutter": 1,
			"ObjectMeshSkinned": 1,
			"ObjectMeshDynamic": 1,
			"ObjectMeshSplineCluster": 1,
			"ObjectTerrainGlobal": 1,
			"ObjectLandscapeTerrain": 1,
		);

		for (int i = 0; i < xml.getNumChildren(); i++)
		{
			Xml child = xml.getChild(i);
			if (child.getName() == "surface")
			{
				if(!child.isArg("intersection"))
					child.setArg("intersection", "1");
				else
					child.removeArg("intersection");

				if (!intersection_supported.check(type))
				{
					xmlRemoveArg(child, "intersection");
					xmlRemoveArg(child, "physics_intersection");
					xmlRemoveArg(child, "intersection_mask");
					xmlRemoveArg(child, "physics_intersection_mask");
				}

				if (!collision_supported.check(type))
				{
					xmlRemoveArg(child, "collision");
					xmlRemoveArg(child, "collision_mask");
				}
			}
		}
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
		int num = xml.findChild("render_environment_correct_roughness");
		if (num != -1)
		{
			Xml render_environment_correct_roughness = xml.getChild(num);
			render_environment_correct_roughness.setName("render_environment_ggx_mipmaps_quality");

			int value = render_environment_correct_roughness.getIntData();
			render_environment_correct_roughness.setData(max(0, value - 1));
		}

		xmlDeleteChild(xml, "render_streaming_destroy_duration");
		xmlDeleteChild(xml, "render_streaming_update_limit");
		xmlRenameChild(xml, "render_streaming_meshes_memory_limit", "render_streaming_meshes_limit_vram");
		xmlDeleteChild(xml, "render_streaming_use_memory_limit");
		xmlRenameChild(xml, "render_streaming_meshes_collision_prefetch", "render_streaming_meshes_prefetch_collision");
		xmlRenameChild(xml, "render_streaming_meshes_intersection_prefetch", "render_streaming_meshes_prefetch_intersection");

		num = xml.findChild("render_streaming_mode");
		if (num != -1)
		{
			Xml child = xml.getChild(num);
			child.setName("render_streaming_textures_mode");

			int value = child.getIntData();
			xmlSetChildValue(xml, "render_streaming_meshes_mode_vram", value);
		}

		Xml xml_new = new Xml();
		string path_render = pathname(replace(__FILE__, "\\", "/")) + "render.xml";
		if(xml_new.load(path_render))
		{
			for(int i = 0; i < xml.getNumChildren(); i++)
			{
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
	}

	/******************************************************************************\
	*
	* Track
	*
	\******************************************************************************/

	void track(Xml xml)
	{
	}

	/******************************************************************************\
	*
	* Meta
	*
	\******************************************************************************/
	void meta(Xml xml, string file_name)
	{
		Xml type = xmlGetChild(xml, "type");
		if (type != NULL && type.getData() == "fbx")
			migrate_fbx_parameters(xmlGetChild(xml, "parameters"));
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
		int console_id = xml.findChild("console");
		if (console_id != -1)
		{
			Xml console_xml = xml.getChild(console_id);

			int pso_log_id = console_xml.findChild("d3d12_pso_log");
			if (pso_log_id != -1)
				delete console_xml.removeChild(console_xml.getChild(pso_log_id));

			pso_log_id = console_xml.findChild("vk_pso_log");
			if (pso_log_id != -1)
				delete console_xml.removeChild(console_xml.getChild(pso_log_id));
		}
	}

	void configControls(Xml xml)
	{
	}

	void configUser(Xml xml)
	{
	}

	/******************************************************************************\
	*
	* Editor's hotkey preset
	*
	\******************************************************************************/
	void editorHotkeyPreset(Json json)
	{
	}

}

#endif /* __MIGRATION_PROCESS_H__ */
