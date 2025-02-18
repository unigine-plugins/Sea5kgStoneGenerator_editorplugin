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
	}
	
	void surface(Xml xml)
	{
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
