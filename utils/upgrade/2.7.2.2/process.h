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
			m.removeParameter("parallax_shadow_min_layers");
			m.removeParameter("parallax_shadow_max_layers");
			m.removeParameter("parallax_shadow_noise");
			m.removeParameter("parallax_shadow_intensity");
			m.removeParameter("parallax_shadow_softness");
			m.removeParameter("parallax_shadow_visible");
			m.removeParameter("parallax_shadow_angle_visible");
			m.removeParameter("parallax_shadow_angle_visible_threshold");
		}
		
		if(m.getBaseMaterial() == "sky_base") {
			m.removeState("surface");
			m.removeState("inscattering");
			m.removeState("ambient");
			m.removeState("light_world");
			m.removeState("volume");
			m.removeState("turbulence");
			m.removeState("geodetic");
			m.removeParameter("volume_transform");
			m.removeParameter("noise_transform");
			m.removeParameter("volume_0_color");
			m.removeParameter("volume_1_color");
			m.removeParameter("volume_01_scale");
			m.removeParameter("volume_alpha");
			m.removeParameter("volume_turbulence");
			m.removeParameter("volume_scale");
			m.removeParameter("shadow_scale");
		}
	}
	
	/******************************************************************************\
	*
	* Nodes
	*
	\******************************************************************************/
	void node(Xml xml) {
		
		string type = xml.getArg("type","unknown");
		if(type == "ObjectSky") {
			xmlDeleteChild(xml, "simulation");
			xmlDeleteChild(xml, "size");
			xmlDeleteChild(xml, "min_slices");
			xmlDeleteChild(xml, "max_slices");
			xmlDeleteChild(xml, "distribute");
			xmlDeleteChild(xml, "humidity");
			xmlDeleteChild(xml, "transition");
			xmlDeleteChild(xml, "extinction");
			xmlDeleteChild(xml, "density_image");
			xmlDeleteChild(xml, "density_velocity");
			xmlDeleteChild(xml, "density_offset");
			xmlDeleteChild(xml, "density_layer");
			
			for(int i = 0; i < xml.getNumChildren(); i++) {
				Xml x = xml.getChild(i);
				if(x.getName() == "surface" && (x.getArg("name") == "volume" || x.getArg("name") == "shadow")) {
					i--;
					delete xml.removeChild(x);
				}
			}
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
		xmlDeleteChild(xml, "enabled");
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
	
}

#endif /* __MIGRATION_PROCESS_H__ */
