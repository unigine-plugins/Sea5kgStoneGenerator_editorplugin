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

	void migrate_texture_painter_metadata(Xml xml)
	{
		Xml data_xml = xmlGetChild(xml, "data");
		if (data_xml == NULL)
			return;
		Xml editor_xml = xmlGetChild(data_xml, "unigine_editor");
		if (editor_xml == NULL)
			return;
		Xml body_xml = xmlGetChild(editor_xml, "body");
		if (body_xml == NULL)
			return;
		Xml texture_painter_xml = xmlGetChild(body_xml, "texture_painter");
		if (texture_painter_xml == NULL)
			return;
		Xml surfaces_xml = xmlGetChild(texture_painter_xml, "surfaces");
		if (surfaces_xml == NULL)
			return;
		for (int i = 0; i < surfaces_xml.getNumChildren(); i++)
		{
			Xml surface_xml = surfaces_xml.getChild(i);
			string surface_name = surface_xml.getName();
			string surface_texture = surface_xml.getData();
			surface_xml.setData("");
			surface_xml.setName("surface");
			surface_xml.setArg("name", surface_name);
			surface_xml.setArg("texture", surface_texture);
		}
	}

	void node(Xml xml)
	{
		migrate_texture_painter_metadata(xml);
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
	void reset_env_preset(Xml xml, int preset_index)
	{
		string prefix = "environment_preset_" + string(preset_index);
		Xml x = xmlGetChild(xml, prefix + "_sun_angular_size");
		if (x != NULL) x.setFloatData(50.0f);

		x = xmlGetChild(xml, prefix + "_sun_texture_name");
		if (x != NULL) x.setData("core/textures/world_light/celestial_body_sun.png");
		x = xmlGetChild(xml, prefix + "_moon_texture_name");
		if (x != NULL) x.setData("core/textures/world_light/celestial_body_moon.png");

		x = xmlGetChild(xml, prefix + "_scattering_base_lut_texture_name");
		if (x != NULL) x.setData("core/textures/scattering_lut/preset_" + string(preset_index) + "/base.tif");
		x = xmlGetChild(xml, prefix + "_scattering_mie_lut_texture_name");
		if (x != NULL) x.setData("core/textures/scattering_lut/preset_" + string(preset_index) + "/mie.tif");
		x = xmlGetChild(xml, prefix + "_scattering_light_color_lut_texture_name");
		if (x != NULL) x.setData("core/textures/scattering_lut/preset_" + string(preset_index) + "/light_color.tif");
	}

	void render(Xml xml)
	{
		reset_env_preset(xml, 0);
		reset_env_preset(xml, 1);
		reset_env_preset(xml, 2);

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
		int console_id = xml.findChild("console");
		if (console_id != -1)
		{
			string console_removed[] = (
				"gl_render_skip_errors": 1,
				"video_quad_buffer": 1,
			);

			Xml console = xml.getChild(console_id);
			for (int i = 0; i < console.getNumChildren(); i++)
			{
				Xml child = console.getChild(i);
				if (console_removed.check(child.getName()))
				{
					delete console.removeChild(child);
					i--;
				}
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
