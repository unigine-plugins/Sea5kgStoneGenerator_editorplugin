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

namespace Process {
	/******************************************************************************\
	*
	* Materials
	*
	\******************************************************************************/
	
	void material(Material m) {
		// clouds upgrade
		if(m.getBaseMaterial() == "clouds_base")
		{
			float base_size_value 	= 0.45f; // clouds_base default settings
			float detail_size_value = 3.0f;
			
			int no_base_size_param		= true;
			int no_detail_size_param	= true;
			
			if(m.hasParameter("base_size")) 
			{
				base_size_value		= float(m.getParameterValue("base_size"));
				no_base_size_param	= false;
			}
			
			if(m.hasParameter("detail_size")) 
			{
				detail_size_value		= float(m.getParameterValue("detail_size"));
				no_detail_size_param	= false;
			}
			
			if(no_base_size_param || no_detail_size_param)
			{
				string parent_guid = m.getParentGUID();
				while(parent_guid != "") 
				{
					Material par_material;
					
					if(Materials::materials.check(parent_guid)) 
					{
						par_material = Materials::materials[parent_guid];
					} else
					{
						if(strcmp(parent_guid, "f66b5ab8f8048a185b25441e6bc246b19d4fa918") == 0) // clouds_nimbostratus
						{
							if(no_base_size_param) 
							{
								no_base_size_param = false;
								base_size_value    = 0.5f;
							}
							
							if(no_detail_size_param) 
							{
								no_detail_size_param = false;
								detail_size_value    = 4.0f;
							}
						} else if(strcmp(parent_guid, "a14673df389231255ca078cc836dd9b06c62bd83") == 0) // clouds_altocumulus
						{
							if(no_base_size_param) 
							{
								no_base_size_param = false;
								base_size_value    = 0.4f;
							}
							
							if(no_detail_size_param) 
							{
								no_detail_size_param = false;
								detail_size_value    = 2.0f;
							}
						} else if(strcmp(parent_guid, "c520ef3e45dffdee57ac856b394873f0c97b0e57") == 0) // clouds_cumulus
						{
							if(no_base_size_param) 
							{
								no_base_size_param = false;
								base_size_value    = 0.5f;
							}
							
							if(no_detail_size_param) 
							{
								no_detail_size_param = false;
								detail_size_value    = 4.0f;
							}
						} else if(strcmp(parent_guid, "67987fe0e6348ae9e7861f8c0182572e6cdd9c4a") == 0) // clouds_stratocumulus
						{
							if(no_detail_size_param) 
							{
								no_detail_size_param = false;
								detail_size_value    = 4.0f;
							}
						} else if(strcmp(parent_guid, "f965ad3f1d012fc2e5378aba49034ec730c9a24c") == 0) // clouds_stratus
						{
							if(no_base_size_param) 
							{
								no_base_size_param = false;
								base_size_value    = 0.300000012f;
							}
							
							if(no_detail_size_param) 
							{
								no_detail_size_param = false;
								detail_size_value    = 4.0f;
							}
						} else 
						{
							log.error("Process::material(): Failed to load parent material! (name=%s; guid=%s)\n", m.getParentName(), m.getParentGUID());
						}
						
						break;
					}
					
					if(no_base_size_param && par_material.hasParameter("base_size")) 
					{
						no_base_size_param	= false;
						base_size_value		= float(par_material.getParameterValue("base_size"));
					}
					
					if(no_detail_size_param && par_material.hasParameter("detail_size")) 
					{
						no_detail_size_param 	= false;
						detail_size_value		= float(par_material.getParameterValue("detail_size"));
					}
					
					if((no_base_size_param == false) && (no_detail_size_param == false))
						break;
					
					parent_guid = par_material.getParentGUID();
				}
			}
			
			if(base_size_value > 0.0f && detail_size_value > 0.0f) 
			{
				m.setParameterValue("detail_size", string(detail_size_value * base_size_value));
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
	
	void calc_tangents(vec2 prev, vec2 next, vec2 curr, vec2 &left, vec2 &right)
	{
		left = (prev - curr) / 3.0f;
		right = (next - curr) / 3.0f;
		left = (left - right) / 2.0f;
		right = -left;
	}

	void create_curve_damping(Xml xml, float damping, float multiply, float lifetime)
	{
		Xml keys = xml.addChild("keys");
		float times[12] = (0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 0.999f, 1.0f);

		for(int i = 0; i < 12; i++)
		{
			float time = times[i];
			float value = 0.0f;
			if(time != 1.0f)
				value = exp(-time * damping) * multiply;
			vec2 key_value = vec2(time / lifetime, value);

			Xml key = keys.addChild("key");
			key.setVec2Arg("point", key_value);
			key.setVec2Arg("left_tangent", vec2(0.0f, 0.0f));
			key.setVec2Arg("right_tangent", vec2(0.0f, 0.0f));
		}
		
		// calc tangents
		for(int i = 0; i < 12; i++)
		{
			Xml key = keys.getChild(i);
			int index_prev = clamp(i - 1, 0, 11);
			int index_next = clamp(i + 1, 0, 11);
			vec2 key_prev = keys.getChild(index_prev).getVec2Arg("point");
			vec2 key_curr = key.getVec2Arg("point");
			vec2 key_next = keys.getChild(index_next).getVec2Arg("point");

			vec2 left, right;
			calc_tangents(key_prev, key_curr, key_next, left, right);
			key.setVec2Arg("left_tangent", left);
			key.setVec2Arg("right_tangent", right);
		}
	}
	
	void convert_dampimg_to_curve(Xml xml, string param_name, string param_damping, float default_min, float default_max)
	{
		if(!xml.isChild(param_damping))
			return;

		string modifier_name = param_name + "_modifier";
		int mode = 0;
		if(abs(default_max - default_min) >= 0.000001f)
			mode = 1;

		Xml x_modifier;
		if(xml.isChild(modifier_name))
		{
			x_modifier = xml.getChild(modifier_name);
			if(!x_modifier.isArg("curve_scale"))
			{
				float scale = x_modifier.getFloatArg("value_max", default_max);
				x_modifier.setFloatArg("curve_scale", scale);
			}
			mode = x_modifier.getIntArg("mode", mode);
		} else
		{
			x_modifier = xml.addChild(modifier_name);
			x_modifier.setFloatArg("value", default_max);
			x_modifier.setFloatArg("value_min", default_min);
			x_modifier.setFloatArg("value_max", default_max);
			x_modifier.setFloatArg("curve_scale", default_max);
		}
		
		float lifetime = 0.0f;
		lifetime += xml.getChildData("life_mean", 1.0f);
		lifetime += xml.getChildData("life_spread", 0.5f);
	
		float damping = xml.getChildData(param_damping, 0.0f);

		// curve mode
		mode += 1;
		x_modifier.setIntArg("mode", mode);

		float multiply = default_min / default_max;

		if(!x_modifier.isChild("curve_min"))
		{
			Xml curve_min = x_modifier.addChild("curve_min");
			create_curve_damping(curve_min, damping, multiply, lifetime);
		}
		
		if(!x_modifier.isChild("curve_max"))
		{
			Xml curve_max = x_modifier.addChild("curve_max");
			create_curve_damping(curve_max, damping, 1.0f, lifetime);
		}
	}

	void convert_parameter_to_modifier_gravity(Xml xml)
	{
		string param_name = "gravity";
		string param_modifier = "gravity_modifier";

		if(xml.isChild(param_name))
		{
			vec3 value = vec3(0.0f, 0.0f, 0.0f);
			value = xml.getChildData(param_name, value);

			xmlDeleteChild(xml, param_name);
			if(value == vec3(0.0f, 0.0f, 0.0f))
				return;
			
			Xml x_modifier = xml.addChild(param_modifier);
			x_modifier.setVec3Arg("value", value);
			x_modifier.setVec3Arg("value_min", value);
			x_modifier.setVec3Arg("value_max", value);
			float scale = max(max(abs(value.x), abs(value.y)), abs(value.z));
			x_modifier.setFloatArg("curve_scale", scale);
			x_modifier.setIntArg("mode", 0);
		}
	}

	void node(Xml xml) {
		string type = xml.getArg("type","unknown");
		
		// particles upgrade
		if (type == "ObjectParticles") {
			convert_parameter_to_modifier_gravity(xml);

			convert_dampimg_to_curve(xml, "rotation", "angular_damping", 0.0f, 0.0f);
			convert_dampimg_to_curve(xml, "growth", "growth_damping", 0.0f, 0.0f);

			xmlDeleteChild(xml, "angular_damping");
			xmlDeleteChild(xml, "growth_damping");
			
			xmlRenameChild(xml, "emitter_limit", "emitter_limit_per_spawn");
		}
	}
	
	void surface(Xml xml) {
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
	void meta(Xml xml, string file_name) {
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
