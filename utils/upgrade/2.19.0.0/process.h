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
		string base_material = m.getBaseMaterial();

		if (base_material == "4dfec30f491f753f6e89094db6d3d695e89f9d6f") base_material = "Unigine::mesh_base";
		else if (base_material == "ee4cbd68892b61a53e7ded930b825d0f53ac250e") base_material = "Unigine::billboards_base";
		else if (base_material == "f039bcf66841add1ac854e081275cc4e0d16a198") base_material = "Unigine::billboards_cloud_base";
		else if (base_material == "1f14ce52ff2d0d126d21be317e860a4a76477183") base_material = "Unigine::gui_base";
		else if (base_material == "b7c07dfd4ce80edac55fcbfdd0befa02ccd20b88") base_material = "Unigine::particles_base";
		else if (base_material == "35a276124c303849f0e072ef632908545149b6fb") base_material = "Unigine::sky_base";

		// Unigine::mesh_base
		if (base_material == "Unigine::mesh_base")
		{
			if (m.hasState("deferred") || m.getParentGUID() == "")
			{
				string value = m.getStateValue("deferred", "1");
				m.setStateValue("transparent_opacity_depth", value);
				m.setStateValue("transparent_velocity", value);
				m.setStateValue("transparent_material_mask", value);
				m.removeState("deferred");
			}
		}
		if (base_material == "Unigine::particles_base")
		{
			if (m.hasState("deferred_buffers") || m.getParentGUID() == "")
			{
				string value = m.getStateValue("deferred_buffers", "1");
				m.setStateValue("transparent_opacity_depth", value);
				m.setStateValue("transparent_velocity", value);
				m.setStateValue("transparent_material_mask", value);
				m.removeState("deferred_buffers");
			}
		}

		if (
			   base_material == "Unigine::mesh_base"
			|| base_material == "Unigine::billboards_base"
			|| base_material == "Unigine::billboards_cloud_base"
			|| base_material == "Unigine::gui_base"
			|| base_material == "Unigine::particles_base"
			|| base_material == "Unigine::sky_base"
		)
		{
			if (m.hasOption("depth_mask"))
			{
				m.setStateValue("transparent_scene_depth", m.getOption("depth_mask"));
			}
		}

		m.removeOption("depth_mask");
	}

	/******************************************************************************\
	*
	* MaterialGraphs
	*
	\******************************************************************************/

	void materialGraph(MaterialGraph graph)
	{
		if (graph.material_json != NULL)
		{
			jsonRenameChild(graph.material_json, "depth_write", "scene_depth_write");

			if (graph.material_json.isChild("gbuffer"))
			{
				Json gbuffer = graph.material_json.getChild("gbuffer");
				int value = gbuffer.getBool();
				jsonSetBool(graph.material_json, "opacity_depth_write", value);
				jsonSetBool(graph.material_json, "velocity_write", value);
				jsonSetBool(graph.material_json, "material_mask_write", value);
				graph.material_json.removeChild("gbuffer");
			}
		}

		// En-9317
		UGUID guid_gen = new UGUID();
		foreach(MaterialGraphNode node; graph.nodes)
		{
			if (node.getName() == "screenUVToViewDirection")
			{
				// create new nodes: Multiply and Float3(-1)
				MaterialGraphNode mul_node = new MaterialGraphNode(new Json("_multiply"));
				mul_node.json.addChild("label", "Multiply");
				guid_gen.generate();
				mul_node.setGuid(guid_gen.makeString());
				mul_node.setX(node.getX() + 300);
				mul_node.setY(node.getY() + 145);
				mul_node.json.addChild("collapsed").setBool(false);
				mul_node.json.addChild(new Json("props"));
				mul_node.json.addChild(new Json("inputs"));
				mul_node.json.addChild(new Json("outputs"));

				MaterialGraphInput inputA = new MaterialGraphInput(new Json("input"));
				inputA.setLabel("A");
				inputA.setType("float3");
				inputA.setID(-1822151033);
				mul_node.json.getChild("inputs").addChild(inputA.json);
				mul_node.inputs.append(inputA);

				MaterialGraphInput inputB = new MaterialGraphInput(new Json("input"));
				inputB.setLabel("B");
				inputB.setType("float3");
				inputB.setID(291415938);
				mul_node.json.getChild("inputs").addChild(inputB.json);
				mul_node.inputs.append(inputB);

				MaterialGraphOutput output = new MaterialGraphOutput(new Json("output"));
				output.setLabel("");
				output.setType("float3");
				output.setID(1723312480);
				mul_node.json.getChild("outputs").addChild(output.json);
				mul_node.outputs.append(output);

				graph.json.getChild("nodes").addChild(mul_node.json);
				graph.nodes.append(mul_node);

				MaterialGraphNode factor_node = new MaterialGraphNode(new Json("float"));
				factor_node.json.addChild("type", "float");
				factor_node.json.addChild("label", "float");
				guid_gen.generate();
				factor_node.setGuid(guid_gen.makeString());
				factor_node.setX(mul_node.getX() - 200);
				factor_node.setY(mul_node.getY());
				factor_node.json.addChild("collapsed").setBool(true);
				factor_node.json.addChild(new Json("props"));
				factor_node.json.addChild(new Json("inputs"));
				factor_node.json.addChild(new Json("outputs"));

				Json prop = new Json("prop");
				prop.addChild("label", "");
				prop.addChild("widget", "float");
				prop.addChild("x", -1);
				factor_node.json.getChild("props").addChild(prop);

				output = new MaterialGraphOutput(new Json("output"));
				output.setLabel("-1.0");
				output.setType("float");
				output.setID(0);
				factor_node.json.getChild("outputs").addChild(output.json);
				factor_node.outputs.append(output);

				graph.json.getChild("nodes").addChild(factor_node.json);
				graph.nodes.append(factor_node);

				// reroute existing anchors taking output from screenUVToViewDirection to Multiply
				MaterialGraphInput tmp_in;
				MaterialGraphOutput tmp_out;
				foreach(MaterialGraphAnchor anchor; graph.anchors)
				{
					if (anchor.getOutputNodeGUID() == node.getGuid())
					{
						anchor.setOutputNodeGUID(mul_node.getGuid());
						anchor.setOutputIndex(0);
						tmp_out = mul_node.outputs[0];
						anchor.setOutputID(tmp_out.getID());
					}
				}

				// connect screenUVToViewDirection and Float3(-1) to Multiply
				MaterialGraphAnchor anchor_node_to_mul_A = new MaterialGraphAnchor(new Json("anchor"));
				anchor_node_to_mul_A.setOutputNodeGUID(node.getGuid());
				anchor_node_to_mul_A.setOutputIndex(0);
				tmp_out = node.outputs[0];
				anchor_node_to_mul_A.setOutputID(tmp_out.getID());
				anchor_node_to_mul_A.setInputNodeGUID(mul_node.getGuid());
				anchor_node_to_mul_A.setInputIndex(0);
				tmp_in = mul_node.inputs[0];
				anchor_node_to_mul_A.setInputID(tmp_in.getID());
				graph.json.getChild("anchors").addChild(anchor_node_to_mul_A.json);
				graph.anchors.append(anchor_node_to_mul_A);

				MaterialGraphAnchor anchor_factor_to_mul_B = new MaterialGraphAnchor(new Json("anchor"));
				anchor_factor_to_mul_B.setOutputNodeGUID(factor_node.getGuid());
				anchor_factor_to_mul_B.setOutputIndex(0);
				tmp_out = factor_node.outputs[0];
				anchor_factor_to_mul_B.setOutputID(tmp_out.getID());
				anchor_factor_to_mul_B.setInputNodeGUID(mul_node.getGuid());
				anchor_factor_to_mul_B.setInputIndex(1);
				tmp_in = mul_node.inputs[1];
				anchor_factor_to_mul_B.setInputID(tmp_in.getID());
				graph.json.getChild("anchors").addChild(anchor_factor_to_mul_B.json);
				graph.anchors.append(anchor_factor_to_mul_B);
			}
		}

		foreach(MaterialGraphNode node; graph.nodes)
		{
			materialNode(node);
		}
	}

	void materialNode(MaterialGraphNode node)
	{
		// En-9605
		if (node.json.getName() == "Indirect Diffuse")
		{
			node.json.setName("Indirect Diffuse Final");
			jsonSetString(node.json, "label", "Texture Buffer Indirect Diffuse Final");
		} else if (node.json.getName() == "Indirect Specular")
		{
			node.json.setName("Indirect Specular Final");
			jsonSetString(node.json, "label", "Texture Buffer Indirect Specular Final");
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

	int is_light(string type)
	{
		return type == "LightWorld" || type == "LightProj" || type == "LightOmni"
			|| type == "LightVoxelProbe" || type == "LightEnvironmentProbe" || type == "LightPlanarProbe";
	}

	void add_replace(Xml xml, string child_name)
	{
		int num = xml.findChild(child_name);
		if (num < 0)
			return;
		Xml child = xml.getChild(num);

		if (child.isArg("replace"))
			return;

		UGUID guid = new UGUID();
		guid.generate();

		child.setArg("replace", guid.makeString());
	}

	void add_surfaces_replace(Xml xml)
	{
		for (int i = 0; i < xml.getNumChildren(); i++)
		{
			Xml child = xml.getChild(i);
			if (child.getName() != "surface")
				continue;

			add_replace(child, "lightmap_texture_path");
		}
	}

	void node(Xml xml)
	{
		xmlDeleteChild(xml, "streaming_mode_vram");
		xmlDeleteChild(xml, "streaming_mode_ram");

		string type = xml.getArg("type");

		if (is_light(type))
		{
			add_replace(xml, "baked_depth_texture");
			add_replace(xml, "texture");
		} else if (type == "ObjectMeshStatic")
		{
			add_surfaces_replace(xml);
		}

		// En-9298
		if (type == "LightOmni" || type == "LightProj")
		{
			float shadow_distance = xml.getChildData("shadow_distance", 0.0f);
			float fade_distance = xml.getChildData("fade_distance", 0.0f);
			xmlAddChild(xml, "shadow_fade_distance").setData(fade_distance);
			if (xml.findChild("shadow_distance") != -1)
			{
				xmlGetChild(xml, "shadow_distance").setData(max(0.0f, shadow_distance - fade_distance));
			}
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
		// En-9568
		xmlRenameChild(xml, "exposure_min_luminance", "render_exposure_min_luminance");
		xmlRenameChild(xml, "exposure_max_luminance", "render_exposure_max_luminance");

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
		int console_id = xml.findChild("console");
		if (console_id != -1)
		{
			string console_removed[] = (
				"gl_async_buffer": 1,
				"gl_async_buffer_indices": 1,
				"gl_async_buffer_synchronization": 1,
				"gl_use_debug_info": 1,
				"textures_cache_preload": 1,
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
