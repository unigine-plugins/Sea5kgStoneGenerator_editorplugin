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
		m.removeState("material_shadow_shafts");
		m.removeState("material_backface_shadow_shafts");
	}
	
	/******************************************************************************\
	*
	* MaterialGraphs
	*
	\******************************************************************************/
	
	void materialGraph(MaterialGraph graph)
	{
		foreach(MaterialGraphAnchor anchor; graph.anchors)
		{
			// input
			{
				string guid = anchor.getInputNodeGUID();
				MaterialGraphNode node = graph.findNodeByGUID(guid);
				if (node != NULL && node.getName() == "_branch")
					anchor.setInputID(anchor.getInputIndex());
			}
			
			// output
			{
				string guid = anchor.getOutputNodeGUID();
				MaterialGraphNode node = graph.findNodeByGUID(guid);
				if (node != NULL && node.getName() == "_branch")
					anchor.setOutputID(anchor.getOutputIndex());
			}
		}
		
		foreach(MaterialGraphNode node; graph.nodes)
		{
			materialNode(node);
		}
	}
	
	void materialNode(MaterialGraphNode node)
	{
		string name = node.getName();
		
		for (int i = 0; i < node.inputs.size(); i++)
		{
			MaterialGraphInput input = node.inputs[i];
			string type = input.getType();
			if (type == "add")
			{
				node.inputs.remove(node.inputs.find(input));
				input.json.clear();
				delete input;
				i--;
			}
		}
		
		if (name == "Inputs" || name == "Outputs" || name == "LoopBegin")
		{
			for (int i = 0; i < node.inputs.size(); i++)
			{
				MaterialGraphInput input = node.inputs[i];
				string type = input.getType();
				if (type == "uint")
					input.setType("int");
				if (type == "uint2")
					input.setType("int2");
				if (type == "uint3")
					input.setType("int3");
				if (type == "uint4")
					input.setType("int4");
			}
			for (int i = 0; i < node.outputs.size(); i++)
			{
				MaterialGraphOutput output = node.outputs[i];
				string type = output.getType();
				if (type == "uint")
					output.setType("int");
				if (type == "uint2")
					output.setType("int2");
				if (type == "uint3")
					output.setType("int3");
				if (type == "uint4")
					output.setType("int4");
			}
		}
		
		
		
		if (name == "_branch")
		{
			for (int i = 0; i < node.inputs.size(); i++)
				node.inputs[i].setID(i);
			
			for (int i = 0; i < node.outputs.size(); i++)
				node.outputs[i].setID(i);
		}
		
		if (name == "SampleTexture")
		{
			Json child = node.json.getChild("texture_type");
			if (child != NULL)
				child.setInt(child.getInt() - 2);
		}
		
		{
			Json json = new Json();
			string path = pathname(replace(__FILE__, "\\", "/")) + "mat_graph.json";
			if(json.load(path)) 
			{
				Json json_rename = json.getChild("rename");
				if (json_rename != NULL)
				{
					if (json_rename.isChild(name))
						node.setName(json_rename.getChild(name).getString());
				}
				
				Json json_warnings = json.getChild("warnings");
				if (json_warnings != NULL)
				{
					if (json_warnings.isChild(name))
						node.addWarning(json_warnings.getChild(name).getString());
					
					if (name == "SubGraph")
					{
						Json json_props = node.json.getChild("props");
						if (json_props != NULL && json_props.getNumChildren() != 0)
						{
							string asset = jsonGetString(json_props.getChild(0), "asset");
							if (json_warnings.isChild(asset))
								node.addWarning(json_warnings.getChild(asset).getString());
						}
					}
				}
			}
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
		string type = xml.getArg("type");
		if (type == "ObjectWaterGlobal")
		{
			// now it's normal
			xmlDeleteChild(xml, "distant_waves_height_texture_path");
			
			xmlRenameChild(xml, "distant_waves_distance_fade_end", "distant_waves_blend_distance_end");
			xmlRenameChild(xml, "distant_waves_distance_fade_start", "distant_waves_blend_distance_start");
			xmlRenameChild(xml, "distant_waves_distance_fade_min_value", "distant_waves_blend_min");
			xmlRenameChild(xml, "distant_waves_height_scale", "distant_waves_intensity");
			
			xmlSetChildValue(xml, "distant_waves_intensity", 1.0f);
			
			xmlRenameChild(xml, "normal_waves_intensity", "normal_geometry_intensity");
			xmlRenameChild(xml, "normal_additional_blur", "normal_texture_blur");
			xmlRenameChild(xml, "normal_additional_intensity", "normal_texture_intensity");
		}
		if (type == "DecalProj" || type == "DecalOrtho" || type == "DecalMesh")
		{
			xmlDeleteChild(xml, "init_time");
			xmlDeleteChild(xml, "life_time");
			xmlDeleteChild(xml, "fade_time");
			xmlDeleteChild(xml, "texcoord");
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
		string source_filepath = extension(file_name, "");
		
		if(lower(extension(source_filepath)) == "fbx")
		{
			Xml index_max_count_lods_node = xml.find("* name=\"index_max_count_lods\"");
			if (index_max_count_lods_node != NULL)
			{
				int index_max_lods = int(index_max_count_lods_node.getData());
				index_max_count_lods_node.setArg("name", "num_lods");
				index_max_count_lods_node.setData(string(index_max_lods + 2));
			}
			
			Xml combine_by_lods_node = xml.find("* name=\"combine_by_lods\"");
			if (combine_by_lods_node != NULL)
			{
				string value = combine_by_lods_node.getData();
				combine_by_lods_node.setArg("name", "lods_mode");
				combine_by_lods_node.setArg("type", "string");
				if (value == "1")
					combine_by_lods_node.setData("by_postfix");
				else
					combine_by_lods_node.setData("off");
			}

			Xml lods_node = xml.find("* name=\"lods\"");
			if (lods_node != NULL)
			{
				string lods_parameters[0];
				lods_parameters.clear();
				int num = strsplit(lods_node.getData(), ",", lods_parameters);
				class Lod
				{
					string postfix;
					float min_visibility;
					float max_visibility;
					float min_fade;
					float max_fade;
					float quality;
					float normals_weight;
					int recalculate_normals;
					float recalculate_normals_angle;
				};
				
				Lod lods[0];
				lods.clear();
				for (int i = 0; i < num - 1; i += 2)
				{
					Lod lod = new Lod();
					lod.postfix = lods_parameters[i];
					lod.min_visibility = float(lods_parameters[i + 1]);
					lod.min_fade = 0.0f;
					lod.max_fade = 0.0f;
					lod.quality = i == 0 ? 100.0f : 20.0f;
					lod.normals_weight = 0.01f;
					lod.recalculate_normals = i == 0 ? 0 : 1;
					lod.recalculate_normals_angle = 60.0f;
					lods.append(lod);
				}
				
				for (int i = 0; i < lods.size() - 1; i++)
				{
					lods[i].max_visibility = lods[i + 1].min_visibility;
				}
				
				if (lods.size() != 0)
					lods[lods.size() - 1].max_visibility = INFINITY;
				
				string result = "";
				for (int i = 0; i < lods.size(); i++)
				{
					result += lods[i].postfix;
					result += ",";
					result += string(lods[i].min_visibility);
					result += ",";
					result += string(lods[i].max_visibility);
					result += ",";
					result += string(lods[i].min_fade);
					result += ",";
					result += string(lods[i].max_fade);
					result += ",";
					result += string(lods[i].quality);
					result += ",";
					result += string(lods[i].normals_weight);
					result += ",";
					result += string(lods[i].recalculate_normals);
					result += ",";
					result += string(lods[i].recalculate_normals_angle);
					if (i != lods.size() - 1)
						result += ";";
				}
				lods_node.setData(result);
				
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
