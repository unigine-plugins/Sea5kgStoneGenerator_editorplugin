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

namespace Process {
	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/
	
	int isDigit(string value)
	{
		int is_digit(string value)
		{
			int check_range(string value, int begin, int end)
			{
				for(int i = 0; i < strlen(value); i++)
				{
					if (value[i] < begin || value[i] > end)
						return false;
				}
				
				return true;
			}
			
			value = lower(value);
			value = replace(value, " ", "");
			int len = strlen(value);
			if (strlen(value) == 0)
				return false;
			
			// sign
			if (strchr(value,'-') > 0 || strchr(value,'+') > 0)
				return false;
			len = strlen(value);
			value = replace(value, "+", "");
			value = replace(value, "-", "");
			if ((len - strlen(value)) > 1)
				return false;
			
			// int 0x
			if(strstr(value, "0x") == 0)
			{
				value = replace(value, "0x", "");
				
				// 0-9 a-f
				for(int i = 0; i < strlen(value); i++)
				{
					if ((value[i] < '0' || value[i] > '9') && (value[i] < 'a' || value[i] > 'f'))
						return false;
				}
				
				return true;
			}
			
			// int 0b
			if(strstr(value, "0b") == 0)
			{
				value = replace(value, "0b", "");
				return check_range(value, '0', '1');
			}
			
			// int 0o
			if(strstr(value, "0o") == 0)
			{
				value = replace(value, "0o", "");
				return check_range(value, '0', '8');
			}
			
			// float to int
			value = replace(value, ".", "");
			if ((len - strlen(value)) > 1)
				return false;
			
			// int
			return check_range(value, '0', '9');
		}
		if (is_digit(value))
			return true;
		
		string elements[0] = ();
		strsplit(value," ", elements);
		foreach(string element; elements)
		{
			if (!is_digit(element))
				return false;
		}
		return true;
	}
	
	void material(Material m) {
		
		for(int i = 0; i < m.parameters.size(); i++) {
			Parameter parameter = m.parameters.get(i);
			xmlRenameArg(parameter.xml, "use_expression", "expression");
			
			if (parameter.getName() == "material_mask")
			{
				// hex -> int
				int val[1];
				string name = m.getParameterValue("material_mask");
				sscanf(name, "%d", val);
				log.message("Material %s : param= %s int=%d\n", m.getName(), m.getParameterValue("material_mask"), val[0]);
				m.setParameterValue("material_mask", format("%d", val[0]));
				
				Parameter parameter = m.parameters.check("material_mask", NULL);
				parameter.xml.setArg("expression", "0");
			} else {
				string value = parameter.getValue();
				if (isDigit(value))
				{
					parameter.xml.setArg("expression", "0");
				} else
				{
					value = lower(value);
					value = replace(value, " ", "");
					value = replace(value, "\t", "");
					value = replace(value, "\r", "");
					value = replace(value, "\n", "");
					
					int channels = 1;
					if (strstr(value, "vec4(") != -1)
						channels = 4;
					else if (strstr(value, "vec3(") != -1)
						channels = 3;
					else if (strstr(value, "vec2(") != -1)
						channels = 2;
					else if (strstr(value, "ivec4(") != -1)
						channels = 4;
					else if (strstr(value, "ivec3(") != -1)
						channels = 3;
					else if (strstr(value, "ivec2(") != -1)
						channels = 2;
					
					value = replace(value, "vec4(", "");
					value = replace(value, "vec3(", "");
					value = replace(value, "vec2(", "");
					value = replace(value, "ivec4(", "");
					value = replace(value, "ivec3(", "");
					value = replace(value, "ivec2(", "");
					
					value = replace(value, "ff", "FF");
					value = replace(value, "Ff", "FF");
					value = replace(value, "f,", ",");
					value = replace(value, ",", " ");
					value = replace(value, "f)", "");
					value = replace(value, ")", "");
					
					if (isDigit(value))
					{
						string elements[0] = ();
						strsplit(value," ", elements);
						if (channels == elements.size())
						{
							parameter.setValue(value);
							parameter.xml.setArg("expression", "0");
						} else if (channels > elements.size())
						{
							value = elements[0];
							for (int i = 1; i < elements.size(); i++)
								value += " " + elements[i];
							
							for (int i = elements.size(); i < channels; i++)
								value += " " + elements[elements.size() - 1];
							
							parameter.setValue(value);
							parameter.xml.setArg("expression", "0");
						} else {
							parameter.xml.setArg("expression", "1");
						}
						
					} else {
						parameter.xml.setArg("expression", "1");
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
	void propertyFile(Xml xml) {
	}

	// global changes that related to another properties
	void property(Properties::Property p) {
	}
	
	/******************************************************************************\
	*
	* Nodes
	*
	\******************************************************************************/
	void node(Xml xml) {
		forloop(int i = 0; xml.getNumChildren())
			if(xml.getChild(i).getName() == "surface")
				surface(xml.getChild(i));
		
		Xml body = xmlGetChild(xml, "body");
		if (body != NULL)
			if (xmlGetArg(body, "type") == "BodyRagDoll")
				xmlSetArg(body, "type", "BodyRagdoll");
		
		xmlRemoveArg(xml, "folded");
		
		string type = xml.getArg("type","unknown");
		
		if (type == "ObjectTerrain") {
			xml.removeChild("terrain_name");
			xml.removeChild("lod_distance");
			xml.removeChild("lod_progression");
			xml.removeChild("lod_threshold");
			xml.removeChild("lod_terrain_left");
			xml.removeChild("lod_terrain_right");
			xml.removeChild("lod_terrain_bottom");
			xml.removeChild("lod_terrain_top");
			xml.removeChild("visible_distance");
			xml.removeChild("shadow_distance");
			xml.removeChild("material");
			while (xml.findChild("surface") != -1)
				xml.removeChild("surface");
			
			xml.setArg("type", "ObjectDummy");
		}
		
		if (type == "WorldOccluderTerrain") {
			xml.removeChild("size");
			xml.removeChild("radius");
			xml.removeChild("distance");
			xml.removeChild("heights_image");
			xml.setArg("type", "NodeDummy");
		}
	}
	
	void surface(Xml xml) {
		if(!xml.isArg("collision")) {
			xml.setArg("collision", "1");
		}
		xmlRemoveArg(xml, "folded");
	}
	
	void surfaceProperty(Xml xml_surface, Xml xml_prop, Properties::Property prop) {
	}
	
	/******************************************************************************\
	*
	* Bodies
	*
	\******************************************************************************/
	void body(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Shapes
	*
	\******************************************************************************/
	void shape(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Joints
	*
	\******************************************************************************/
	void joint(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Render
	*
	\******************************************************************************/
	void render(Xml xml) {
		
		xmlRenameChild(xml, "render_terrain_triplanar", "render_terrain_global_triplanar");
		xmlRenameChild(xml, "render_terrain_displacement", "render_terrain_global_displacement");
		xmlRenameChild(xml, "render_terrain_displacement_normal", "render_terrain_global_displacement_normal");
		xmlRenameChild(xml, "render_terrain_holes", "render_terrain_global_holes");
		xmlRenameChild(xml, "render_terrain_anisotropy", "render_terrain_global_anisotropy");
		
		xmlDeleteChild(xml, "render_streaming_check_duration");
		xmlDeleteChild(xml, "render_terrain_refined_albedo");
		xmlDeleteChild(xml, "render_terrain_refined_normal");
		xmlDeleteChild(xml, "render_terrain_refined_mask");
		
		Xml xml_new = new Xml();
		string path_render = pathname(replace(__FILE__, "\\", "/")) + "render.xml";
		if(xml_new.load(path_render)) {
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
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
	void sound(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Physics
	*
	\******************************************************************************/
	void physics(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* World
	*
	\******************************************************************************/
	void world(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Track
	*
	\******************************************************************************/
	void track(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Config
	*
	\******************************************************************************/
	void config(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Meta
	*
	\******************************************************************************/
	void meta(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* AppProjection
	*
	\******************************************************************************/
	void projectionBinary(string file_name) {
		
	}
	
	void projection(Xml xml) {
	}
	
	/******************************************************************************\
	*
	* Syncker
	*
	\******************************************************************************/
	void synckerBinary(string file_name) {
	}
	
	void syncker(Xml xml) {
	}
}

#endif /* __MIGRATION_PROCESS_H__ */
