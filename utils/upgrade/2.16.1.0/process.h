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
		if (type != "ObjectDynamic")
			return;

		for (int i = 0; i < xml.getNumChildren(); i++)
		{
			Xml child = xml.getChild(i);
			if (child.getName() == "vertex")
			{
				if (child.isArg("type") == 0 || child.isArg("num_vertex") == 0 || child.isArg("size") == 0)
				{
					log.error("Process::node(): can't find vertex attributes in ObjectDynamic %s\n", xml.getArg("name"));
					return 0;
				}

				if (child.getArg("type") == "double")
					child.setArg("type", "float");
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
	void update_lut_to_tiff(Xml xml, string name)
	{
		Xml lut;
		int num = xml.findChild(name);
		if (num == -1)
			return;
		lut = xml.getChild(num);
		
		string data = lut.getData();
		if (strrstr(data, "core/textures/scattering_lut/") == 0)
		{
			data = replace(data, ".tga", ".tif");
			lut.setData(data);
		}
	}
	
	void render(Xml xml)
	{
		xmlRenameChild(xml, "environment_preset_0_haze_scattering_mie_intensity", "environment_preset_0_haze_scattering_mie_front_side_intensity");
		xmlRenameChild(xml, "environment_preset_0_haze_scattering_mie_fresnel_intensity", "environment_preset_0_haze_scattering_mie_intensity");
		xmlRenameChild(xml, "environment_preset_1_haze_scattering_mie_intensity", "environment_preset_1_haze_scattering_mie_front_side_intensity");
		xmlRenameChild(xml, "environment_preset_1_haze_scattering_mie_fresnel_intensity", "environment_preset_1_haze_scattering_mie_intensity");
		xmlRenameChild(xml, "environment_preset_2_haze_scattering_mie_intensity", "environment_preset_2_haze_scattering_mie_front_side_intensity");
		xmlRenameChild(xml, "environment_preset_2_haze_scattering_mie_fresnel_intensity", "environment_preset_2_haze_scattering_mie_intensity");
		
		update_lut_to_tiff(xml, "environment_preset_0_scattering_base_lut_texture_name");
		update_lut_to_tiff(xml, "environment_preset_0_scattering_mie_lut_texture_name");
		update_lut_to_tiff(xml, "environment_preset_0_scattering_light_color_lut_texture_name");
		
		update_lut_to_tiff(xml, "environment_preset_1_scattering_base_lut_texture_name");
		update_lut_to_tiff(xml, "environment_preset_1_scattering_mie_lut_texture_name");
		update_lut_to_tiff(xml, "environment_preset_1_scattering_light_color_lut_texture_name");
		
		update_lut_to_tiff(xml, "environment_preset_2_scattering_base_lut_texture_name");
		update_lut_to_tiff(xml, "environment_preset_2_scattering_mie_lut_texture_name");
		update_lut_to_tiff(xml, "environment_preset_2_scattering_light_color_lut_texture_name");
		
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
