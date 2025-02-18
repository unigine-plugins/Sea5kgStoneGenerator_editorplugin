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
	string process_texture_filepath(string filepath)
	{
		if (strlen(filepath) == 0)
			return filepath;

		if (!startsWith(filepath, "core/") && !startsWith(filepath, "editor2/"))
			return filepath;

		if (extension(filepath) == "meta")
		{
			string tmp = extension(filepath, "");
			if (extension(tmp) == "dds")
				return extension(tmp, "texture.meta");

			return filepath;
		}

		if (extension(filepath) != "dds")
			return filepath;

		return extension(filepath, "texture");
	}
	
	void process_core_textures_xml(Xml xml)
	{
		int num_children = xml.getNumChildren();
		for (int i = 0; i < num_children; i++)
			process_core_textures_xml(xml.getChild(i));

		string new_filepath = process_texture_filepath(xml.getData());
		if (new_filepath != xml.getData())
			xml.setData(new_filepath);
	}

	void process_core_textures_json(Json json)
	{
		int num_children = json.getNumChildren();
		for (int i = 0; i < num_children; i++)
			process_core_textures_json(json.getChild(i));

		if (!json.isString())
			return;

		string new_filepath = process_texture_filepath(json.getString());
		if (new_filepath != json.getString())
			json.setString(new_filepath);
	}
	
	void process_core_textures_mat(Material mat)
	{
		foreachkey(string name; mat.textures)
		{
			string new_filepath = process_texture_filepath(mat.getTextureValue(name));
			if (new_filepath != mat.getTextureValue(name))
				mat.setTextureValue(name, new_filepath);
		}
	}

	void sort_meta_parameters(Xml parameters, string file_name)
	{
		Xml sorted_parameters[];
		for (int i = parameters.getNumChildren() - 1; i >= 0; i--)
		{
			Xml param = parameters.getChild(i);
			string name = xmlGetArg(param, "name");
			if (name != "")
			{
				param = parameters.removeChild(param);
				sorted_parameters.append(name, param);
			}
			else
			{
				Log::error("invalid meta parameters: \"%s\"", file_name);
			}
		}

		foreach (Xml param; sorted_parameters)
		{
			parameters.addChild(param);
			class_remove(param);
		}
		sorted_parameters.clear();
	}

	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/
	
	void material(Material m)
	{
		process_core_textures_mat(m);
	}
	
	/******************************************************************************\
	*
	* MaterialGraphs
	*
	\******************************************************************************/
	
	void materialGraph(MaterialGraph graph)
	{
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
		process_core_textures_xml(xml);
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
		process_core_textures_xml(xml);
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
		process_core_textures_xml(xml);
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
		process_core_textures_xml(xml);

		string tmp = extension(file_name, "");
		string asset_extension = extension(tmp);
		if (asset_extension == "world")
		{
			Xml parameters = xmlGetChild(xml, "parameters");
			if (parameters != NULL)
			{
				forloop(int i = 0; parameters.getNumChildren())
				{
					Xml param = parameters.getChild(i);
					if (xmlGetArg(param, "name") != "viewports")
						continue;
					if (param.getNumChildren() == 0)
						continue;

					Xml viewports_xml = param.getChild(0);
					string value = viewports_xml.getFormattedSubTree();
					param.removeChild(viewports_xml);
					param.setData(value);

					xmlSetArg(param, "type", "string");
				}
			}
		}

		// Sort asset/runtimes parameters
		Xml asset_parameters = xmlGetChild(xml, "parameters");
		if (asset_parameters != NULL)
		{
			sort_meta_parameters(asset_parameters, file_name);
		}
		Xml runtimes = xmlGetChild(xml, "runtimes");
		if (runtimes != NULL)
		{
			forloop (int i = 0; runtimes.getNumChildren())
			{
				Xml rt = runtimes.getChild(i);
				if (rt.getName() != "runtime")
					continue;

				Xml runtime_parameters = xmlGetChild(rt, "parameters");
				if (runtime_parameters != NULL)
				{
					sort_meta_parameters(runtime_parameters, file_name);
				}
			}
		}
	}

	/******************************************************************************\
	*
	* guids.db
	*
	\******************************************************************************/
	
	void guidsDB(string file_name)
	{
		if (!is_file(file_name))
			return;

		Json json = new Json();
		if (json.load(file_name))
		{
			process_core_textures_json(json);
			json.save(file_name);
		}

		delete json;
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
}

#endif /* __MIGRATION_PROCESS_H__ */
