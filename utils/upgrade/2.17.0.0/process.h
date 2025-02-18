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

	int is_force_already_exist(Xml xml_parent, Xml xml_force, float p_mass)
	{
		for (int i = 0; i < xml_parent.getNumChildren(); i++)
		{
			Xml child = xml_parent.getChild(i);
			if ((child.getName() != "node") || (child.getArg("type") != "PhysicalForce"))
				continue;
			if (child.getChildData("enabled", 1) != xml_force.getChildData("enabled", 1))
				continue;
			if (child.getChildData("transform", mat4_identity) != xml_force.getChildData("transform", mat4_identity))
				continue;
			if (child.getChildData("radius", 1.0f) != xml_force.getChildData("radius", 1.0f))
				continue;
			if (child.getChildData("attenuation", 1.0f) != xml_force.getChildData("attenuation", 1.0f))
				continue;
			if (child.getChildData("attractor", 0.0f) != xml_force.getChildData("attractor", 0.0f) * p_mass)
				continue;
			if (child.getChildData("rotator", 0.0f) != xml_force.getChildData("rotator", 0.0f) * p_mass)
				continue;
			return 1;
		}
		return 0;
	}

	int is_noise_already_exist(Xml xml_parent, Xml xml_noise, float p_mass)
	{
		for (int i = 0; i < xml_parent.getNumChildren(); i++)
		{
			Xml child = xml_parent.getChild(i);
			if ((child.getName() != "node") || (child.getArg("type") != "PhysicalNoise"))
				continue;
			if (child.getChildData("enabled", 1) != xml_noise.getChildData("enabled", 1))
				continue;
			if (child.getChildData("transform", mat4_identity) != xml_noise.getChildData("transform", mat4_identity))
				continue;
			if (child.getChildData("offset", vec3(0.0f)) != xml_noise.getChildData("offset", vec3(0.0f)))
				continue;
			if (child.getChildData("step", vec3(1.0f)) != xml_noise.getChildData("step", vec3(1.0f)))
				continue;
			if (child.getChildData("force", 1.0f) != xml_noise.getChildData("force", 1.0f) * p_mass)
				continue;
			if (child.getChildData("scale", 0.5f) != xml_noise.getChildData("scale", 0.5f))
				continue;
			if (child.getChildData("image_size", 16) != xml_noise.getChildData("size", 16))
				continue;
			return 1;
		}
		return 0;
	}

	int is_deflector_already_exist(Xml xml_parent, Xml xml_deflector, int deflector_type)
	{
		string node_name = deflector_type == 0 ? "ParticlesFieldDeflector" : "ParticlesFieldSpacer";
		float size_z = deflector_type == 0 ? 0.0f : 1.0f;

		for (int i = 0; i < xml_parent.getNumChildren(); i++)
		{
			Xml child = xml_parent.getChild(i);
			if ((child.getName() != "node") || (child.getArg("type") != node_name))
				continue;
			if (child.getChildData("enabled", 1) != xml_deflector.getChildData("enabled", 1))
				continue;
			if (child.getChildData("transform", mat4_identity) != xml_deflector.getChildData("transform", mat4_identity))
				continue;

			vec3 deflector_size = xml_deflector.getChildData("size", vec3(0.5f, 0.5f, 0.0f)) * 2.0f;
			deflector_size = deflector_type == 0 ? deflector_size : max(deflector_size, vec3(0.05f));
			if (child.getChildData("size", vec3(1.0f, 1.0f, size_z)) != deflector_size)
				continue;

			if (deflector_type == 0)
			{
				if (child.getChildData("restitution", 0.85f) != xml_deflector.getChildData("restitution", 0.85f))
					continue;
				if (child.getChildData("roughness", 0.0f) != xml_deflector.getChildData("roughness", 0.0f))
					continue;
			}
			return 1;
		}
		return 0;
	}

	void node(Xml xml, Xml xml_base)
	{
		// particles migration
		string type = xml.getArg("type");
		if (type == "ObjectParticles")
		{
			float p_mass = xml.getChildData("physical_mass", 0.0f);
			int surface_num = -1;

			int p_type = xml.getChildData("particles_type", 0);

			for (int i = 0; i < xml.getNumChildren(); i++)
			{
				Xml child = xml.getChild(i);

				if (child.getName() == "radius_modifier" || child.getName() == "growth_modifier")
				{
					if (p_type == 0 || p_type == 1)
					{
						float sqrt2 = 1.414213562f;
						child.setFloatArg("value", child.getFloatArg("value") * sqrt2);
						child.setFloatArg("value_min", child.getFloatArg("value_min") * sqrt2);
						child.setFloatArg("value_max", child.getFloatArg("value_max") * sqrt2);

						// upgrade curves
						for (int j = 0; j < child.getNumChildren(); j++)
						{
							Xml curve_xml = child.getChild(j);
							Xml keys_xml = xmlGetChild(curve_xml, "keys");
							if (keys_xml != NULL)
							{
								for (int k = 0; k < keys_xml.getNumChildren(); k++)
								{
									Xml key_xml = keys_xml.getChild(k);
									vec2 point = key_xml.getVec2Arg("point");
									point.y *= sqrt2;
									key_xml.setVec2Arg("point", point);
								}
							}
						}
					}
				}

				if (child.getName() == "surface")
				{
					surface_num = i;
					continue;
				}

				if (child.getName() == "noise")
				{
					Xml xml_parent;
					if (child.getChildData("attached", 0) == 1)
						xml_parent = xml;
					else
						xml_parent = xml_base;

					if (p_mass == 0.0f)
						p_mass = 1.0f;

					// add physical noise
					if (!is_noise_already_exist(xml_parent, child, p_mass))
					{
						Xml x_noise = xml_parent.addChild("node");

						// type
						x_noise.setArg("type", "PhysicalNoise");
						// name
						x_noise.setArg("name", "PhysicalNoise");
						// enabled
						if (child.getChildData("enabled", 1) == 0)
							x_noise.setArg("enabled", 0);

						// transform
						x_noise.setChildData("transform", child.getChildData("transform", mat4_identity));
						// offset
						x_noise.setChildData("offset", child.getChildData("offset", vec3(0.0f)));
						// step
						x_noise.setChildData("step", child.getChildData("step", vec3(1.0f)));
						// force
						x_noise.setChildData("force", child.getChildData("force", 1.0f) * p_mass);
						// scale
						x_noise.setChildData("scale", child.getChildData("scale", 0.5f));
						// frequency
						x_noise.setChildData("frequency", child.getChildData("frequency", 4));
						// image_size
						x_noise.setChildData("image_size", child.getChildData("size", 16));
					}
					// delete old particle noise
					xml.removeChild(child);
					i--;
				}

				if (child.getName() == "force")
				{
					Xml xml_parent;
					if (child.getChildData("attached", 0) == 1)
						xml_parent = xml;
					else
						xml_parent = xml_base;

					if (p_mass == 0.0f)
						p_mass = 1.0f;

					if (!is_force_already_exist(xml_parent, child, p_mass))
					{

						Xml x_force = xml_parent.addChild("node");

						// type
						x_force.setArg("type", "PhysicalForce");
						// name
						x_force.setArg("name", "PhysicalForce");
						// enabled
						if (child.getChildData("enabled", 1) == 0)
							x_force.setArg("enabled", 0);

						// transform
						x_force.setChildData("transform", child.getChildData("transform", mat4_identity));
						// attenuation
						x_force.setChildData("attenuation", child.getChildData("attenuation", 1.0f));
						// radius
						x_force.setChildData("radius", child.getChildData("radius", 1.0f));
						// attractor
						x_force.setChildData("attractor", child.getChildData("attractor", 0.0f) * p_mass);
						// rotator
						x_force.setChildData("rotator", child.getChildData("rotator", 0.0f) * p_mass);
					}

					// delete old particle force
					xml.removeChild(child);
					i--;
				}

				if (child.getName() == "deflector")
				{
					Xml xml_parent;
					if (child.getChildData("attached", 0) == 1)
						xml_parent = xml;
					else
						xml_parent = xml_base;

					int deflector_type = child.getChildData("type", 0);
					if (!is_deflector_already_exist(xml_parent, child, deflector_type))
					{
						Xml x_field = xml_parent.addChild("node");

						// reflector
						if (deflector_type == 0)
						{
							// type
							x_field.setArg("type", "ParticlesFieldDeflector");
							// name
							x_field.setArg("name", "ParticlesFieldDeflector");
							// enabled
							if (child.getChildData("enabled", 1) == 0)
								x_field.setArg("enabled", 0);

							// transform
							x_field.setChildData("transform", child.getChildData("transform", mat4_identity));
							// size
							vec3 size = child.getChildData("size", vec3(0.5f, 0.5f, 0.0f)) * 2.0f;
							x_field.setChildData("size", vec2(size.x, size.y));
							// restitution
							x_field.setChildData("restitution", child.getChildData("restitution", 0.85f));
							// roughness
							x_field.setChildData("roughness", child.getChildData("roughness", 0.0f));

						// clipper
						} else
						{
							// type
							x_field.setArg("type", "ParticlesFieldSpacer");
							// name
							x_field.setArg("name", "ParticlesFieldSpacer");
							// enabled
							if (child.getChildData("enabled", 1) == 0)
								x_field.setArg("enabled", 0);

							// transform
							x_field.setChildData("transform", child.getChildData("transform", mat4_identity));
							// size
							vec3 size = child.getChildData("size", vec3(0.5f, 0.5f, 0.0f)) * 2.0f;
							size = max(size, vec3(0.05f));
							x_field.setChildData("size", size);
						}
					}

					// delete old particle deflector
					xml.removeChild(child);
					i--;
				}
			}

			if(surface_num != -1)
			{
				Xml xml_surface = xml.getChild(surface_num);
				if (xml_surface.isArg("physics_intersection_mask"))
				{
					int mask = xml_surface.getArg("physics_intersection_mask");
					xml.addChild("physics_intersection_mask").setData(mask);
				}

				if (xml_surface.isArg("collision_mask"))
				{
					int mask = xml_surface.getArg("collision_mask");
					xml.addChild("collision_mask").setData(mask);
				}

				xml_surface.removeArg("physics_intersection");
				xml_surface.removeArg("intersection");
				xml_surface.removeArg("collision");
				xml_surface.removeArg("physics_intersection_mask");
				xml_surface.removeArg("intersection_mask");
				xml_surface.removeArg("collision_mask");
			}

			xmlSetChildValue(xml, "physical_mass", p_mass);
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
		Xml render_textures_max_resolution = xmlGetChild(xml, "render_textures_max_resolution");
		if (render_textures_max_resolution != NULL)
		{
			int value = render_textures_max_resolution.getIntData();
			render_textures_max_resolution.setIntData(value + 1);
		}

		/*Xml xml_new = new Xml();
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
		delete xml_new;*/
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
