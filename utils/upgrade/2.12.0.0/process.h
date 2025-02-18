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
		// particles upgrade
		if(m.getBaseMaterial() == "particles_base")
		{
			m.renameTexture("diffuse", "albedo");
			m.renameParameter("diffuse_color", "albedo_color");
			m.removeTexture("attenuation");
			if(m.hasParameter("animation_transform"))
			{
				Parameter parameter = m.parameters["animation_transform"];
				vec4 value = parameter.xml.getVec4Data();
				m.removeParameter("animation_transform");
				
				Parameter p_animation_size = m.addParameter("animation_size");
				p_animation_size.xml.setVec2Data(vec2(value.x, value.y));
				
				Parameter p_animation_scale = m.addParameter("animation_scale");
				p_animation_scale.xml.setFloatData(value.z);
			}
			if(m.hasParameter("emission_scale"))
			{
				Parameter parameter = m.parameters["emission_scale"];
				float value = parameter.xml.getFloatData();
				if(value > 0.0f)
				{
					m.setStateValue("emission", "1");
					if(m.hasTexture("albedo"))
						m.setTextureValue("emission", m.getTextureValue("albedo"));
					if(m.hasParameter("albedo_color"))
					{
						m.setParameterValue("emission_color", m.getParameterValue("albedo_color"));	
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
	
	void convert_parameter_to_modifier_length(Xml xml, string param_name)
	{
		string arg_modifier = param_name + "_modifier";
		
		if(xml.isChild(param_name))
		{
			float value;
			value = xml.getChildData(param_name, value);
			
			xmlDeleteChild(xml, param_name);
			
			Xml x_modifier = xml.addChild(arg_modifier);
			x_modifier.setFloatArg("value", value);
			x_modifier.setIntArg("mode", 0);
		}
	}
	
	void convert_parameter_to_modifier_scalar(Xml xml, string param_name)
	{
		string arg_mean = param_name + "_mean";
		string arg_spread = param_name + "_spread";
		string arg_modifier = param_name + "_modifier";
		
		if(xml.isChild(arg_mean) || xml.isChild(arg_spread))
		{
			float value_mean, value_spread;
			value_mean = xml.getChildData(arg_mean, value_mean);
			value_spread = xml.getChildData(arg_spread, value_spread);
			
			xmlDeleteChild(xml, arg_mean);
			xmlDeleteChild(xml, arg_spread);
			
			Xml x_modifier = xml.addChild(arg_modifier);
			float value_min = value_mean - value_spread;
			float value_max = value_mean + value_spread;
			x_modifier.setFloatArg("value", value_max);
			x_modifier.setFloatArg("value_min", value_min);
			x_modifier.setFloatArg("value_max", value_max);
			x_modifier.setIntArg("mode", 1);
		}
	}
	
	void convert_parameter_to_modifier_direction(Xml xml)
	{
		string arg_mean = "emitter_direction";
		string arg_spread = "emitter_spread";
		string arg_modifier = "direction_modifier";
		
		if(xml.isChild(arg_mean) || xml.isChild(arg_spread))
		{
			vec3 value_mean = vec3(0.0f, 0.0f, 0.0f);
			vec3 value_spread = vec3(1.0f, 1.0f, 1.0f);
			value_mean = xml.getChildData(arg_mean, value_mean);
			value_spread = xml.getChildData(arg_spread, value_spread);
			
			xmlDeleteChild(xml, arg_mean);
			xmlDeleteChild(xml, arg_spread);
			
			Xml x_modifier = xml.addChild(arg_modifier);
			vec3 value_min = value_mean - value_spread;
			vec3 value_max = value_mean + value_spread;
			x_modifier.setVec3Arg("value", value_max);
			x_modifier.setVec3Arg("value_min", value_min);
			x_modifier.setVec3Arg("value_max", value_max);
			x_modifier.setIntArg("mode", 1);
		}
	}
	void node(Xml xml) {
		string type = xml.getArg("type","unknown");
		
		// particles upgrade
		if (type == "ObjectParticles") {
			convert_parameter_to_modifier_scalar(xml, "angle");
			convert_parameter_to_modifier_scalar(xml, "rotation");
			convert_parameter_to_modifier_scalar(xml, "radius");
			convert_parameter_to_modifier_scalar(xml, "growth");
			convert_parameter_to_modifier_scalar(xml, "velocity");
			
			convert_parameter_to_modifier_length(xml, "length_stretch");
			convert_parameter_to_modifier_length(xml, "length_flattening");
			
			convert_parameter_to_modifier_direction(xml);
			
			if(!xml.isChild("gravity"))
				xml.setChildData("gravity", vec3(0.0));
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
		string removed[] = (
			"node.object.particles.angleMean": 0,
			"node.object.particles.angleSpread": 0,
			"node.object.particles.rotationMean": 0,
			"node.object.particles.rotationSpread": 0,
			"node.object.particles.radiusMean": 0,
			"node.object.particles.radiusSpread": 0,
			"node.object.particles.growthMean": 0,
			"node.object.particles.growthSpread": 0,
			"node.object.particles.emitterDirection": 0,
			"node.object.particles.emitterSpread": 0,
			"node.object.particles.velocityMean": 0,
			"node.object.particles.velocitySpread": 0,
		);
		
		for(int i = 0; i < xml.getNumChildren(); i++) {
			
			Xml x = xml.getChild(i);
			
			if(x.getName() != "parameter" || !x.isArg("type")) continue;
			
			if(removed.check(x.getArg("type"))) {
				delete xml.removeChild(x);
				i--;
			}
		}
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
