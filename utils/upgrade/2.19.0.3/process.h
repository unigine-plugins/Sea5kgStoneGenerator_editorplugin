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

	void convert_linear_damping_parameter_to_modifier(Xml xml)
	{
		string param_name = "linear_damping";
		string param_modifier = "linear_damping_modifier";

		if(xml.isChild(param_name))
		{
			float value = 0.0f;
			value = xml.getChildData(param_name, value);

			xmlDeleteChild(xml, param_name);
			if(value == 0.0f)
				return;

			Xml x_modifier = xml.addChild(param_modifier);
			x_modifier.setFloatArg("value", value);
			x_modifier.setFloatArg("value_min", value);
			x_modifier.setFloatArg("value_max", value);
			float scale = abs(value);
			x_modifier.setFloatArg("curve_scale", scale);
			x_modifier.setIntArg("mode", 0);
		}
	}

	void node(Xml xml)
	{
		string type = xml.getArg("type","unknown");

		// particles upgrade
		if (type == "ObjectParticles")
		{
			convert_linear_damping_parameter_to_modifier(xml);
		}

		// shadow near clipping
		if (type == "LightProj")
		{
			float znear = xml.getChildData("znear", 0.01f);
			xmlDeleteChild(xml, "znear");
			xmlAddChild(xml, "shadow_near_clipping_distance").setData(znear);

			int shape_type = xml.getChildData("shape_type", 0);
			if (shape_type > 0)
				xmlDeleteChild(xml, "baked_depth_texture");
		} else if (type == "LightOmni")
		{
			float attenuation_distance = xml.getChildData("attenuation_distance", 1.0f);
			int shape_type = xml.getChildData("shape_type", 0);
			vec3 shape = xml.getChildData("shape", vec3(2.0f, 1.0f, 0.2f));

			vec3 size = vec3(attenuation_distance);
			if (shape_type >= 1)
				size += vec3(shape.z);
			if (shape_type >= 2)
				size.x += shape.x * 0.5f;
			if (shape_type >= 3)
				size.y += shape.y * 0.5f;
			float max_size = max(max(size.x, size.y), size.z);
			xmlAddChild(xml, "shadow_near_clipping_distance").setData(max_size / 500.0f);
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
		xmlDeleteChild(xml, "render_quadro_sync");

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
