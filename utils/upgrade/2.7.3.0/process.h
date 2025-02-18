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
	void material(Material m) {
		if(m.getBaseMaterial() == "mesh_base") {
			if (m.hasState("bevel")) {
				m.addState("procedural_effects", 1);
				m.renameTexture("bevel", "procedural_effects");
			}
			
			// refraction
			
			if (m.hasState("refraction"))
				m.addState("refraction_front_side", 0);
			
			if(m.hasParameter("refraction_shape")) {
				float refraction_shape = float(m.getParameterValue("refraction_shape"));
				float ior = refraction_shape * 0.05f + 1.0f; // [0, 10] -> [1, 1.5]
				m.setParameterValue("refraction_shape",string(ior));
				m.renameParameter("refraction_shape", "refraction_ior");
			}
			
			m.removeParameter("refraction_power");
			
			
			// animation leaves
			
			if(m.hasParameter("animation_leaf_noise")) {
				float animation_leaf_noise = float(m.getParameterValue("animation_leaf_noise"));
				animation_leaf_noise = animation_leaf_noise / 10.0f;
				m.setParameterValue("animation_leaf_noise", string(animation_leaf_noise));
			}
			
			if(m.hasParameter("animation_leaf_offset")) {
				float animation_leaf_offset = float(m.getParameterValue("animation_leaf_offset"));
				animation_leaf_offset = animation_leaf_offset * 5.0f;
				m.setParameterValue("animation_leaf_offset", string(animation_leaf_offset));
			}
			
			if(m.hasParameter("animation_leaf_scale")) {
				float animation_leaf_scale = float(m.getParameterValue("animation_leaf_scale"));
				animation_leaf_scale = animation_leaf_scale / 8.0f;
				m.setParameterValue("animation_leaf_scale", string(animation_leaf_scale));
			}
		}
		
		if(m.getBaseMaterial() == "particles_base") {
			if(m.hasParameter("refraction_power"))
				m.removeParameter("refraction_power");
		}
		
		if(m.getBaseMaterial() == "clouds_base") {
			if(m.hasParameter("ambient_intensity")) {
				float ambient_intensity = float(m.getParameterValue("ambient_intensity"));
				m.addParameter("ambient_intensity_top", string(ambient_intensity));
				m.addParameter("ambient_intensity_bottom", string(ambient_intensity));
				m.removeParameter("ambient_intensity");
			}
		}
	}
	
	/******************************************************************************\
	*
	* Property
	*
	\******************************************************************************/
	void property(Xml xml) {
		if(xml.isArg("parent") && xml.getArg("parent") == "d99ebc8ef5769d70b1e46992309cc3e7d1aa2faa")
			xml.setArg("parent", "1c613bbca0afd78c1ef165fc8e419352c5903d9e");
		
		if(xml.isArg("parent_name") && xml.getArg("parent_name") == "surface_base")
			xml.setArg("parent_name", "node_base");
		
		if(!xml.isArg("manual") || xml.getArg("manual") == "0") {
			for(int i = 0; i < xml.getNumChildren(); i++) {
					Xml parameter = xml.getChild(i);
					string name = parameter.getArg("name");
					if(name == "intersection") {
						delete xml.removeChild(parameter);
						i--;
					} else if(name == "collision") {
						delete xml.removeChild(parameter);
						i--;
					} else if(name == "friction") {
						delete xml.removeChild(parameter);
						i--;
					} else if(name == "restitution") {
						delete xml.removeChild(parameter);
						i--;
					} else if(name == "occlusion") {
						delete xml.removeChild(parameter);
						i--;
					}
				}
		}
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
		
		string type = xml.getArg("type","unknown");
		
		// for box projection:	new attenuation_power = old attenuation_power * 4
		if (type == "LightEnvironmentProbe") {
			
			if(xml.isChild("is_box_projection")) {
				Xml is_box_projection = xml.getChild("is_box_projection");
				int is_box = is_box_projection.getIntData();
				
				if(xml.isChild("attenuation_power") && is_box) {
					Xml attenuation_power = xml.getChild("attenuation_power");
					float value = attenuation_power.getFloatData();	
					value = value * 4.0f;
					attenuation_power.setData(value);
				}
			}
		}
	}
	
	void surface(Xml xml) {
		if(xml.isArg("property") && xml.getArg("property") == "d99ebc8ef5769d70b1e46992309cc3e7d1aa2faa") {
			xml.removeArg("property");
			xmlDeleteChild(xml, "property");
		} else {
			for(int i = 0; i < xml.getNumChildren(); i++)
				if(xml.getChild(i).getName() == "property" && xml.getChild(i).getNumChildren() == 0)
				{
					xmlDeleteChild(xml, "property");
					break;
				}
		}
	}
	
	void surfaceProperty(Xml xml_surface, Xml xml_prop, Properties::Property prop) {
		if(prop == NULL)
			return;
		if(xml_surface == NULL)
			return;
		
		if (xml_prop != NULL) {
			for(int i = 0; i < xml_prop.getNumChildren(); i++) {
				Xml parameter = xml_prop.getChild(i);
				string name = parameter.getArg("name");
				string data = parameter.getData();
				
				if(name == "intersection") {
					if(!xml_surface.isArg("intersection"))
						xml_surface.setArg("intersection", data);
					delete xml_prop.removeChild(parameter);
					i--;
				} else if(name == "collision") {
					if(!xml_surface.isArg("collision"))
						xml_surface.setArg("collision", data);
					delete xml_prop.removeChild(parameter);
					i--;
				} else if(name == "friction") {
					xml_surface.setArg("physics_friction", data);
					delete xml_prop.removeChild(parameter);
					i--;
				} else if(name == "restitution") {
					xml_surface.setArg("physics_restitution", data);
					delete xml_prop.removeChild(parameter);
					i--;
				} else if(name == "occlusion") {
					xml_surface.setArg("sound_occlusion", data);
					delete xml_prop.removeChild(parameter);
					i--;
				}
			}
		}
		
		if(!xml_surface.isArg("intersection")) {
			string data = prop.getRecursiveParameterValue("intersection","1");
			if(data != "1")
				xml_surface.setArg("intersection", data);
		}
		
		if(!xml_surface.isArg("collision")) {
			string data = prop.getRecursiveParameterValue("collision","1");
			if(data != "1")
				xml_surface.setArg("collision", data);
		}
		
		if(!xml_surface.isArg("physics_friction")) {
			string data = prop.getRecursiveParameterValue("friction","0.5");
			if(data != "0.5")
				xml_surface.setArg("physics_friction", data);
		}
		
		if(!xml_surface.isArg("physics_restitution")) {
			string data = prop.getRecursiveParameterValue("restitution","0.5");
			if(data != "0.5")
				xml_surface.setArg("physics_restitution", data);
		}
		
		if(!xml_surface.isArg("sound_occlusion")) {
			string data = prop.getRecursiveParameterValue("occlusion","0.5");
			if(data != "0.5")
				xml_surface.setArg("sound_occlusion", data);
		}
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
		xmlDeleteChild(xml, "environment_preset_0_scattering_ground_lut_texture_name");
		xmlDeleteChild(xml, "environment_preset_1_scattering_ground_lut_texture_name");
		xmlDeleteChild(xml, "environment_preset_2_scattering_ground_lut_texture_name");
		xmlDeleteChild(xml, "environment_preset_0_scattering_ground_color");
		xmlDeleteChild(xml, "environment_preset_1_scattering_ground_color");
		xmlDeleteChild(xml, "environment_preset_2_scattering_ground_color");
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
		Xml type = xmlGetChild(xml, "type");
		if(type != NULL && type.getData() == "fbx") {
			Xml parameters = xmlGetChild(xml, "parameters");
			if(parameters != NULL) {
				int joints_reorientation_found = 0;
				int front_axis_found = 0;
				int front_axis_changed = 0;
				forloop(int i = 0; parameters.getNumChildren()) {
					Xml parameter = parameters.getChild(i);
					if(parameter.getName() == "parameter") {
						if(xmlGetArg(parameter, "name") == "front_axis") {
							front_axis_found = 1;
							if(parameter.getData() == "0") {
								front_axis_changed = 1;
								parameter.setData("4");
							}
						} else if(xmlGetArg(parameter, "name") == "overwrite_materials")
							xmlSetArg(parameter, "name", "import_materials_mode");
						else if(xmlGetArg(parameter, "name") == "joints_reorientation")
							joints_reorientation_found = 1;
					}
				}
				forloop(int i = 0; parameters.getNumChildren()) {
					Xml parameter = parameters.getChild(i);
					if(parameter.getName() == "parameter") {
						if(xmlGetArg(parameter, "name") == "up_axis" && front_axis_changed) {
							if(parameter.getData() != "0") {
								parameter.setData("0");
							}
						}
					}
				}
				if(joints_reorientation_found == 0) {
					Xml new_param = parameters.addChild("parameter");
					new_param.setArg("type", "bool");
					new_param.setArg("name", "joints_reorientation");
					new_param.setData("0");
				}
				if(front_axis_found == 0) {
					Xml new_param = parameters.addChild("parameter");
					new_param.setArg("type", "int");
					new_param.setArg("name", "front_axis");
					new_param.setData("4");
				}
			}
		}
	}
	
}

#endif /* __MIGRATION_PROCESS_H__ */
