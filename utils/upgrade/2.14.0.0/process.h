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

#include <fbx_reader.h>

namespace Process
{
	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/
	
	void material(Material m)
	{
		if(m.getBaseMaterial() == "landscape_terrain_detail_base")
		{
			if (m.getParameterValue("height_scale") == "" && m.getParentGUID() == "")
			{
				m.setParameterValue("height_scale", "1");
			}
		} else if(m.getBaseMaterial() == "clouds_base")
		{
			if(m.hasParameter("detail_affect"))
			{
				float detail_affect = float(m.getParameterValue("detail_affect"));
				detail_affect /= 2.0f;
				m.setParameterValue("detail_affect", string(detail_affect));
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
		forloop(int i = 0; xml.getNumChildren())
		{
			if(xml.getChild(i).getName() == "surface")
				surface(xml.getChild(i));
		}
	}
	
	void surface(Xml xml)
	{
		string bake_gi = xmlGetArg(xml, "bake_to_gi", "1");
		string bake_env = xmlGetArg(xml, "bake_to_env_probe", "1");
		string shadow_mode = xmlGetArg(xml, "shadow_mode", "0");
		string lightmap_enabled = xmlGetArg(xml, "lightmap_enabled", "0");
		
		if (bake_gi != "0" && bake_env != "0" && shadow_mode == "0")
		{
			xml.setIntArg("lighting_mode", 0);
		} else if (bake_gi == "0" && bake_env == "0" && lightmap_enabled == "0" && shadow_mode != "0")
		{
			xml.setIntArg("lighting_mode", 1);
		} else
		{
			xml.setIntArg("lighting_mode", 2);
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
		Xml xml_new = new Xml();
		string path_render = pathname(replace(__FILE__, "\\", "/")) + "render.xml";
		if(xml_new.load(path_render)) 
		{
			for(int i = 0; i < xml.getNumChildren(); i++) 
			{
				Xml x = xml.getChild(i);
				
				// TODO: remove in next version after fix En-7009
				if (x.getName() == "scriptable_materials")
					continue;
				
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
	
}

#endif /* __MIGRATION_PROCESS_H__ */
