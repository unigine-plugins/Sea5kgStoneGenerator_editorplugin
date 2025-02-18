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
	* Materials
	*
	\******************************************************************************/
	
	void material(Material m)
	{
		for(int i = 0; i < m.textures.size(); i++) 
		{
			Texture texture = m.textures.get(i);
			xmlRemoveArg(texture.xml, "min");
			xmlRemoveArg(texture.xml, "max");
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

	string samplerTypeToString(int type)
	{
		switch (type)
		{
			case 0: return "Default";
			case 1: return "Mip";
			case 2: return "Mip offset";
			case 3: return "Grad";
			case 4: return "Fetch";
			case 5: return "Point";
			case 6: return "Catmull";
			case 7: return "Cubic";
			case 8: return "Manual linear";
		}

		return "Default";
	}

	string textureDataToString(int type)
	{
		switch (type)
		{
			case  0: return "Color";
			case  1: return "Asset";
			case  2: return "GBuffer Albedo";
			case  3: return "GBuffer Shading";
			case  4: return "GBuffer Normal";
			case  5: return "GBuffer Material Mask";
			case  6: return "GBuffer Features";
			case  7: return "GBuffer Velocity";
			case  8: return "Native Depth";
			case  9: return "Linear Depth";
			case 10: return "Unpack Normal";
			case 11: return "Bent Normal";
			case 12: return "SSAO";
			case 13: return "DoF Mask";
			case 14: return "Auto Exposure";
			case 15: return "Curvature";
			case 16: return "Refraction Mask";
			case 17: return "Transparent Blur";
		}

		return "Color";
	}

	string normalSpaceToString(int type)
	{
		switch (type)
		{
			case 0: return "Tangent Space for UV0";
			case 1: return "Tangent Space for UV1";
			case 2: return "Tangent Space Auto Calculated";
			case 3: return "Object Space";
		}

		return "Tangent Space for UV0";
	}

	void materialNode(MaterialGraphNode node)
	{
		string name = node.getName();
		if (name == "SampleTexture")
		{
			Json texture_type = node.json.getChild("texture_type");
			Json sampler_type = node.json.getChild("sampler_type");
			Json texture_data = node.json.getChild("texture_data");
			Json normal_space = node.json.getChild("normal_space");

			MaterialGraphInput input = node.inputs[0];
			string type = input.getType();
			texture_type.setString(type);

			sampler_type.setString(samplerTypeToString(sampler_type.getInt()));
			texture_data.setString(textureDataToString(texture_data.getInt()));
			normal_space.setString(normalSpaceToString(normal_space.getInt()));
		}
		
		string var_node_names[0] = (
			"parameter",
			"float",
			"float2",
			"float3",
			"float4",
			"color (float3)",
			"color (float4)",
			"int",
			"int2",
			"int3",
			"int4",
			"bool",
			"texture2d",
			"texture2dint",
			"texturecube",
			"texture3d",
			"texture2darray",
		);

		// MatNodeVariable
		if (var_node_names.find(lower(name)) != -1)
		{
			Json props_json = node.json.getChild("props");
			
			// read value
			Json value_json = node.json.getChild("value");
			string type = jsonGetString(value_json, "type");
			jsonSetString(node.json, "type", type);
			
			if (props_json.getNumChildren() == 0)
			{
				string texture_types[0] = (
					"texture2d",
					"texture2dint",
					"texturecube",
					"texture3d",
					"texture2darray",
				);
				
				string lower_type = lower(type);
				
				// if texture
				if (texture_types.find(lower_type) != -1)
				{
					// path
					Json prop_json = props_json.addChild("prop");
					jsonSetString(prop_json, "label", "Path");
					jsonSetString(prop_json, "widget", type);
					jsonSetString(prop_json, "asset", jsonGetString(value_json, "asset"));
					
					string combobox_items[0] = (
						"Repeat",
						"Clamp",
						"Border",
					);
					
					// wrap x
					prop_json = props_json.addChild("prop");
					jsonSetString(prop_json, "label", "Wrap X");
					jsonSetString(prop_json, "widget", "Combobox");
					Json combobox_items_json = prop_json.addChild("combobox_items");
					combobox_items_json.setArray(combobox_items);
					jsonSetInt(prop_json, "x", jsonGetInt(value_json, "wrap_x"));
					
					// wrap y
					prop_json = props_json.addChild("prop");
					jsonSetString(prop_json, "label", "Wrap Y");
					jsonSetString(prop_json, "widget", "Combobox");
					combobox_items_json = prop_json.addChild("combobox_items");
					combobox_items_json.setArray(combobox_items);
					jsonSetInt(prop_json, "x", jsonGetInt(value_json, "wrap_y"));
					
					// wrap z
					prop_json = props_json.addChild("prop");
					jsonSetString(prop_json, "label", "Wrap Z");
					jsonSetString(prop_json, "widget", "Combobox");
					combobox_items_json = prop_json.addChild("combobox_items");
					combobox_items_json.setArray(combobox_items);
					jsonSetInt(prop_json, "x", jsonGetInt(value_json, "wrap_z"));
					
					// anisotropy
					prop_json = props_json.addChild("prop");
					jsonSetString(prop_json, "label", "Anisotropy");
					jsonSetString(prop_json, "widget", "Toggle");
					Json value_x_json = value_json.getChild("anisotropy");
					int value_x = value_x_json != NULL? int(value_x_json.getBool()) : 0;
					jsonSetInt(prop_json, "x", value_x);
					
					// manual_filtering
					prop_json = props_json.addChild("prop");
					jsonSetString(prop_json, "label", "Manual Filtering");
					jsonSetString(prop_json, "widget", "Toggle");
					value_x_json = value_json.getChild("manual_filtering");
					value_x = value_x_json != NULL? int(value_x_json.getBool()) : 0;
					jsonSetInt(prop_json, "x", value_x);
					
					// force_streaming
					prop_json = props_json.addChild("prop");
					jsonSetString(prop_json, "label", "Force Streaming");
					jsonSetString(prop_json, "widget", "Toggle");
					value_x_json = value_json.getChild("force_streaming");
					value_x = value_x_json != NULL? int(value_x_json.getBool()) : 0;
					jsonSetInt(prop_json, "x", value_x);
				// if numeric
				} else
				{
					Json prop_json = props_json.addChild("prop");
					jsonSetString(prop_json, "label", "");
					jsonSetString(prop_json, "widget", type);
					
					if (startsWith(lower_type, "int") || startsWith(lower_type, "bool"))
					{
						int num_channels = int(substr(lower_type, strlen("int"), strlen(lower_type)));
						if (num_channels >= 0)
						{
							int value_x = value_json.getChild("value_x").getInt();
							prop_json.addChild("x").setInt(value_x);
						}
						if (num_channels >= 2)
						{
							int value_y = value_json.getChild("value_y").getInt();
							prop_json.addChild("y").setInt(value_y);
						}
						if (num_channels >= 3)
						{
							int value_z = value_json.getChild("value_z").getInt();
							prop_json.addChild("z").setInt(value_z);
						}
						if (num_channels == 4)
						{
							int value_w = value_json.getChild("value_w").getInt();
							prop_json.addChild("w").setInt(value_w);
						}
					}
					
					if (startsWith(lower_type, "float"))
					{
						int num_channels = int(substr(lower_type, strlen("float"), strlen(lower_type)));
						if (num_channels >= 0)
						{
							int value_x = value_json.getChild("value_x").getNumber();
							prop_json.addChild("x").setNumber(value_x);
						}
						if (num_channels >= 2)
						{
							int value_y = value_json.getChild("value_y").getNumber();
							prop_json.addChild("y").setNumber(value_y);
						}
						if (num_channels >= 3)
						{
							int value_z = value_json.getChild("value_z").getNumber();
							prop_json.addChild("z").setNumber(value_z);
						}
						if (num_channels == 4)
						{
							int value_w = value_json.getChild("value_w").getNumber();
							prop_json.addChild("w").setNumber(value_w);
						}
					}
					
				}
			}
			
			node.json.removeChild("value");
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
		xmlRenameChild(xml, "render_shadow_shafts", "render_screen_space_shadow_shafts_mode");
		xmlDeleteChild(xml, "render_shadow_shafts_exposure");

		Xml xml_shadow_shafts_length = xmlGetChild(xml, "render_shadow_shafts_length");
		if (xml_shadow_shafts_length != NULL)
		{
			float length = xml_shadow_shafts_length.getFloatData() * 3.0f;
			xml_shadow_shafts_length.setFloatData(length);

			xmlRenameChild(xml, "render_shadow_shafts_length", "render_screen_space_shadow_shafts_length");
		}
		
		Xml xml_color_correction = xmlGetChild(xml, "color_correction");
		if (xml_color_correction != NULL)
		{
			xmlRemoveArg(xml_color_correction, "value_min");
			xmlRemoveArg(xml_color_correction, "value_max");
		}
		
		Xml xml_tonemapper_mode = xmlAddChild(xml, "render_tonemapper_mode");
		
		Xml xml_tonemapper = xmlGetChild(xml, "render_tonemapper");
		if (xml_tonemapper != NULL)
		{
			int value = xml_tonemapper.getIntData();
			if (value > 0)
				xml_tonemapper_mode.setIntData(value - 1);
			else
				xml_tonemapper_mode.setIntData(0);

			xml_tonemapper.setIntData(value != 0);
		}
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
		string tmp = extension(file_name, "");
		string asset_extension = extension(tmp);
		if (asset_extension == "mat" || asset_extension == "mgraph")
		{
			xmlDeleteChild(xml, "parameters");
		}
		else if (asset_extension == "lmap")
		{
			Xml asset_parameters = xmlGetChild(xml, "parameters");
			if (asset_parameters != NULL)
			{
				for (int i = asset_parameters.getNumChildren() - 1; i >= 0; i--)
				{
					Xml param = asset_parameters.getChild(i);
					string name = xmlGetArg(param, "name");
					if (name == "need_regenerate" || name == "compress_type")
					{
						delete asset_parameters.removeChild(param);
					}
				}
			}
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
}

#endif /* __MIGRATION_PROCESS_H__ */
