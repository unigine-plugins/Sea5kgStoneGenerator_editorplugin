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
	/******************************************************************************\
	*
	* Path
	*
	\******************************************************************************/

	void processPath(string data_path)
	{
	}

	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/

	void material(Material m)
	{
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

	void node(Xml xml)
	{
		string type = xml.getArg("type");

		// En-9481
		if (type == "LightVoxelProbe")
			xmlRenameChild(xml, "additive_blending", "blend_mode");
		//

		// En-9454
		if (type == "LightEnvironmentProbe")
		{
			xmlRenameChild(xml, "raymarching_diffuse_reconstruction_samples_screen", "raymarching_diffuse_reconstruction_samples");
			xmlRenameChild(xml, "raymarching_specular_reconstruction_samples_screen", "raymarching_specular_reconstruction_samples");
			xmlDeleteChild(xml, "raymarching_diffuse_reconstruction_samples_cubemap");
			xmlDeleteChild(xml, "raymarching_specular_reconstruction_samples_cubemap");
		}
		//
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
		// En-9468
		xmlRenameChild(xml, "render_lights_interleaved_catmull_resampling", "render_direct_lighting_catmull_resampling");
		xmlRenameChild(xml, "render_lights_interleaved_color_clamping", "render_direct_lighting_color_clamping");
		xmlRenameChild(xml, "render_lights_interleaved_samples", "render_direct_lighting_samples");

		int num = xml.findChild("render_lights_interleaved");
		if (num != -1)
		{
			Xml child = xml.getChild(num);
			child.setName("render_direct_lighting_interleaved");

			int value = child.getIntData();
			xmlSetChildValue(xml, "render_indirect_lighting_interleaved", value);
		}
		//

		// En-9321, En-9322
		xmlDeleteChild(xml, "render_shaders_preload");
		//

		xmlDeleteChild(xml, "render_denoise_denoise_by_velocity_threshold");

		// WARNING: update render.xml and uncomment this before migration running!
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

	void migrate_texture_parameters(Xml parameters)
	{
		if (parameters == NULL)
			return;

		for(int i = 0; i < parameters.getNumChildren(); i++)
		{
			Xml parameter = parameters.getChild(i);
			if (parameter.getName() == "parameter")
			{
				string name = xmlGetArg(parameter, "name");
				if (name == "preset_name")
				{
					string preset_name = parameter.getData();
					if (preset_name == "mask (r)")
						parameter.setData("mask veg (r)");
					else if (preset_name == "mask (rg)")
						parameter.setData("mask veg (rg)");
				}
				else if (name == "mipmap_radius" || name == "mipmap_intensity")
				{
					parameters.removeChild(parameter);
					i--;
				}
			}
		}

		// En-7152
		add_parameter(parameters, "float", "sharpness_intensity", "0.25");
		add_parameter(parameters, "float", "sharpness_radius", "1");
		add_parameter(parameters, "int", "blur_radius", "1");
		add_parameter(parameters, "bool", "mipmap_sharp_only_lightness", "1");
		//
	}

	void add_parameter(Xml parameters, string type, string name, string default_value)
	{
		for (int i = 0; i < parameters.getNumChildren(); i++)
		{
			Xml p = parameters.getChild(i);
			if (p.getName() == "parameter" && xmlGetArg(p, "name") == name)
				return;
		}

		Xml param = parameters.addChild("parameter");
		param.setArg("type", type);
		param.setArg("name", name);
		param.setData(default_value);
	}

	void meta(Xml xml, string file_name)
	{
		Xml type = xmlGetChild(xml, "type");
		if (type != NULL && type.getData() == "texture")
			migrate_texture_parameters(xmlGetChild(xml, "parameters"));
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
		// En-9321, En-9322
		int console_id = xml.findChild("console");
		if (console_id != -1)
		{
			Xml console_xml = xml.getChild(console_id);

			int num = console_xml.findChild("materials_loading_mode");
			if (num != -1)
			{
				Xml child = console_xml.getChild(num);
				int value = child.getIntData();
				xmlSetChildValue(console_xml, "materials_preload", value == 1);
				xmlSetChildValue(console_xml, "shaders_preload", value == 2);
				console_xml.removeChild("materials_loading_mode");
			}
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
