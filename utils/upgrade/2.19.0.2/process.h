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
		xmlRenameChild(xml, "render_direct_lighting_catmull_resampling", "render_direct_lighting_interleaved_catmull_resampling");
		xmlRenameChild(xml, "render_direct_lighting_color_clamping", "render_direct_lighting_interleaved_color_clamping");

		xmlRenameChild(xml, "render_indirect_lighting_catmull_resampling", "render_indirect_lighting_interleaved_catmull_resampling");
		xmlRenameChild(xml, "render_indirect_lighting_color_clamping", "render_indirect_lighting_interleaved_color_clamping");

		xmlRenameChild(xml, "render_direct_lighting_samples", "render_direct_lighting_interleaved_samples");
		xmlRenameChild(xml, "render_indirect_lighting_samples", "render_indirect_lighting_interleaved_samples");

		xmlRenameChild(xml, "render_indirect_lighting_color_clamping_intensity", "render_indirect_lighting_interleaved_color_clamping_intensity");
		xmlRenameChild(xml, "render_indirect_lighting_color_clamping_velocity_threshold", "render_indirect_lighting_interleaved_color_clamping_velocity_threshold");


		xmlRenameChild(xml, "render_streaming_vram_usage_limit", "render_streaming_usage_limit_vram");

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

	// Ed-8106
	void migrate_dds_meta(Xml xml)
	{
		// just in case
		Xml type = xmlGetChild(xml, "type");
		if (type == NULL || type.getData() != "texture")
			return;

		Xml parameters = xmlGetChild(xml, "parameters");
		if (parameters == NULL)
			return;

		forloop(int i = 0; parameters.getNumChildren())
		{
			Xml parameter = parameters.getChild(i);
			if (parameter.getName() != "parameter")
				continue;

			string name = xmlGetArg(parameter, "name");
			if (name != "unchanged")
				continue;

			parameter.setData("0");
			break;
		}
	}

	void meta(Xml xml, string file_name)
	{
		string name_elements[0] = ();
		strsplit(file_name, ".", name_elements);
		int num_elements = name_elements.size();
		if (num_elements > 2)
		{
			string asset_ext = name_elements[num_elements - 2];
			if (lower(asset_ext) == "dds")
				migrate_dds_meta(xml);
		}
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
