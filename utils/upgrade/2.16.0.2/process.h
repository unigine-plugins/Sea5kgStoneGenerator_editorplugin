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
	
	string buildings_materials[]=
	(
		"6dca988129020bcc992340c90aa40624c002d724", // buildings_preset_0
		"b24c7365f34362a0d496a39e61bfef94d761efcf", // buildings_preset_0_basement
		"cc05e12b42c1a72a8c01e6b4366f63a68d27d2fa", // buildings_preset_0_level_1_blank
		"37c4ad7eba9822eeb88f90ece9df5fb6fbb0ab43", // buildings_preset_0_level_2_blank
		"6cb81c3b644ae5db056367918a3f7ba804dd81bc", // buildings_preset_0_level_2_complex
		"2b560d46e5114aa310666617fe622e04831077f5", // buildings_preset_0_roof

		"fef14d56fea01cf681d8e8b894e69d6144e88d76", // buildings_preset_1
		"19dce819db8d4eeeae052c757e29f635b4aa0d17", // buildings_preset_1_basement
		"c33b573f9fc358100117ceed204da0832446855b", // buildings_preset_1_level_1_blank
		"ef7c2701293c2c51a2d41513276e0cb397f8e750", // buildings_preset_1_level_2_blank
		"c727f5762dbcf951c149bb23ac9f1ce7e3777a62", // buildings_preset_1_level_2_complex
		"7b61915ec31f620cd816cc04a18018b6a4c0363d"  // buildings_preset_1_roof
	);

	// Unigine::mesh_base
	string mesh_base = "4dfec30f491f753f6e89094db6d3d695e89f9d6f";

	void material(Material m)
	{
		string parent = m.getParentGUID();
		string base_mat = m.getBaseMaterial();

		if (parent != "" && base_mat == mesh_base)
		{
			if (buildings_materials.find(parent) != -1)
				m.setParentGUID("");
		}

		// post_color_correction
		if (base_mat == "cd5191db211d8e38e53f2449eeb749c9135f6b82")
			Materials::removeMaterial(m);
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
		Json json_connector = node.json.getChild("conector");
		if (json_connector != NULL)
			json_connector.setName("collapsed");
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
		
		if (type == "LightWorld" || type == "LightOmni" || type == "LightProj" || type == "LightEnvironmentProbe" || type == "LightPlanarProbe" || type == "LightVoxelProbe")
		{
			// default to zero 
			xmlDeleteChild(xml, "shadow_screen_space_view_bias");

			// set to default and rename
			if (xml.findChild("shadow_screen_space_translucent_depth") == -1)
			{
				xmlSetChildValue(xml, "shadow_screen_space_noise_translucent", 0.03f);
				xmlRenameChild(xml, "shadow_screen_space_noise_translucent", "shadow_screen_space_translucent_depth");
			}
		}

		for (int i = 0; i < xml.getNumChildren(); i++)
		{
			Xml child = xml.getChild(i);
			if (child.getName() == "surface")
			{
				if (child.isArg("material"))
				{
					string mat = child.getArg("material");

					if (buildings_materials.find(mat) != -1)
						child.setArg("material", mesh_base);
				}
				
				// En-8093
				if (type == "ObjectMeshStatic" && child.findChild("lightmap_enabled") == -1)
				{
					child.removeChild("lightmap_compression");
					child.removeChild("lightmap_quality");
					child.removeChild("lightmap_mode");
					child.removeChild("lightmap_texture_surface");
					child.removeChild("lightmap_texture_path");
				}
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
	void render(Xml xml)
	{
		// reset custom motion blur settings to medium from quality_presets.json
		xmlUpdateChildValue(xml, "render_motion_blur_camera_velocity", "1");
		xmlUpdateChildValue(xml, "render_motion_blur_velocity_scale", "0.75");
		xmlUpdateChildValue(xml, "render_motion_blur_max_velocity", "1.0");
		xmlUpdateChildValue(xml, "render_motion_blur_noise_intensity", "0.5");
		xmlUpdateChildValue(xml, "render_motion_blur_num_steps", "8");
		xmlUpdateChildValue(xml, "render_motion_blur_velocity_blur_samples", "8");
		xmlUpdateChildValue(xml, "render_motion_blur_velocity_blur_radius", "0.2");
		xmlUpdateChildValue(xml, "render_motion_blur_depth_threshold_near", "0.0");
		xmlUpdateChildValue(xml, "render_motion_blur_depth_threshold_far", "0.5");
		xmlDeleteChild(xml, "render_motion_blur_neat_silhouettes");
		
		// reset custom ssr settings to medium from quality_presets.json
		xmlUpdateChildValue(xml, "render_ssr_increased_accuracy", "0");
		xmlUpdateChildValue(xml, "render_ssr_alpha_accumulation_mode", "0");
		xmlUpdateChildValue(xml, "render_ssr_num_rays", "4");
		xmlUpdateChildValue(xml, "render_ssr_num_steps", "8");
		xmlUpdateChildValue(xml, "render_ssr_step_size", "0.3");
		xmlUpdateChildValue(xml, "render_ssr_non_linear_step_size", "1.0");
		xmlUpdateChildValue(xml, "render_ssr_perspective_compensation", "1.0");
		xmlUpdateChildValue(xml, "render_ssr_visibility_roughness_min", "0.35");
		xmlUpdateChildValue(xml, "render_ssr_visibility_roughness_max", "0.45");
		xmlUpdateChildValue(xml, "render_ssr_roughness_mip_offset", "4.0");
		xmlUpdateChildValue(xml, "render_ssr_threshold", "1.5");
		xmlUpdateChildValue(xml, "render_ssr_threshold_occlusion", "1.5");
		xmlUpdateChildValue(xml, "render_ssr_view_bias", "1.0");
		xmlUpdateChildValue(xml, "render_ssr_normal_bias", "1.0");
		xmlUpdateChildValue(xml, "render_ssr_color_clamping_intensity", "0.1");
		xmlUpdateChildValue(xml, "render_ssr_color_clamping_velocity_threshold", "100.0");
		xmlUpdateChildValue(xml, "render_ssr_tonemapping_gamma", "2.0");
		xmlDeleteChild(xml, "render_ssr_fast_tracing");
		xmlDeleteChild(xml, "render_ssr_noise_ray");
		xmlDeleteChild(xml, "render_ssr_noise_step");
		
		
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
		int console_id = xml.findChild("console");
		if (console_id != -1)
		{
			Xml console = xml.getChild(console_id);

			int width = 0;
			int height = 0;

			for (int i = 0; i < console.getNumChildren(); i++)
			{
				Xml child = console.getChild(i);
				if (child.getName() == "video_main_window")
				{
					child.setName("main_window");
				} else if (child.getName() == "video_resizable")
				{
					child.setName("main_window_resizable");
				} else if (child.getName() == "video_width")
				{
					width = child.getIntData();
					delete console.removeChild(child);
					i--;
				} else if (child.getName() == "video_height")
				{
					height = child.getIntData();
					delete console.removeChild(child);
					i--;
				} else if (child.getName() == "video_fullscreen")
				{
					child.setName("main_window_fullscreen");
				} else if (child.getName() == "video_vsync")
				{
					delete console.removeChild(child);
					i--;
				} else if (child.getName() == "video_mode")
				{
					delete console.removeChild(child);
					i--;
				} else if (child.getName() == "video_surround")
				{
					delete console.removeChild(child);
					i--;
				} else if (child.getName() == "video_surround_border")
				{
					delete console.removeChild(child);
					i--;
				}
			}

			if (console.findChild("main_window_size") == -1)
			{
				Xml window_size = console.addChild("main_window_size");
				window_size.setIVec2Data(ivec2(width, height));
			}

			if (console.findChild("main_window_auto_restart") == -1)
				console.addChild("main_window_auto_restart").setBoolData(true);
			if (console.findChild("main_window_borders") == -1)
				console.addChild("main_window_borders").setBoolData(true);
			if (console.findChild("main_window_fullscreen_display") == -1)
				console.addChild("main_window_fullscreen_display").setIntData(0);
			if (console.findChild("main_window_fullscreen_display_mode") == -1)
				console.addChild("main_window_fullscreen_display_mode").setIntData(0);
		}
	}

	int need_convert_console_key = 0;
	string STATE_NAME[32] = (
		"FORWARD",
		"BACKWARD",
		"MOVE_LEFT",
		"MOVE_RIGHT",
		"TURN_UP",
		"TURN_DOWN",
		"TURN_LEFT",
		"TURN_RIGHT",
		"CROUCH",
		"JUMP",
		"RUN",
		"USE",
		"FIRE",
		"SAVE",
		"RESTORE",
		"SCREENSHOT",
		"AUX_0",
		"AUX_1",
		"AUX_2",
		"AUX_3",
		"AUX_4",
		"AUX_5",
		"AUX_6",
		"AUX_7",
		"AUX_8",
		"AUX_9",
		"AUX_A",
		"AUX_B",
		"AUX_C",
		"AUX_D",
		"AUX_E",
		"AUX_F",
	);

	enum
	{
		OLD_APP_BUTTON_LEFT = 1 << 0,
		OLD_APP_BUTTON_MIDDLE = 1 << 1,
		OLD_APP_BUTTON_RIGHT = 1 << 2,
		OLD_APP_BUTTON_DCLICK = 1 << 3,
		OLD_APP_BUTTON_AUX_0 = 1 << 4,
		OLD_APP_BUTTON_AUX_1 = 1 << 5,
		OLD_APP_BUTTON_AUX_2 = 1 << 6,
		OLD_APP_BUTTON_AUX_3 = 1 << 7,
	};

	enum
	{
		OLD_APP_KEY_SPACE = ' ',
		OLD_APP_KEY_EXCLAIM = '!',
		OLD_APP_KEY_HASH = '#',
		OLD_APP_KEY_DOLLAR = '$',
		OLD_APP_KEY_PERCENT = '%',
		OLD_APP_KEY_AMPERSAND = '&',
		OLD_APP_KEY_QUOTE = '\'',
		OLD_APP_KEY_APOSTROPHE = OLD_APP_KEY_QUOTE,
		OLD_APP_KEY_LEFT_PAREN = '(',
		OLD_APP_KEY_RIGHT_PAREN = ')',
		OLD_APP_KEY_ASTERISK = '*',
		OLD_APP_KEY_PLUS = '+',
		OLD_APP_KEY_COMMA = ',',
		OLD_APP_KEY_MINUS = '-',
		OLD_APP_KEY_DOT = '.',
		OLD_APP_KEY_SLASH = '/',
		OLD_APP_KEY_COLON = ':',
		OLD_APP_KEY_SEMICOLON = ';',
		OLD_APP_KEY_LESS = '<',
		OLD_APP_KEY_EQUALS = '=',
		OLD_APP_KEY_GREATER = '>',
		OLD_APP_KEY_QUESTION = '?',
		OLD_APP_KEY_AT = '@',
		OLD_APP_KEY_LEFT_BRACKET = '[',
		OLD_APP_KEY_BACK_SLASH = '\\',
		OLD_APP_KEY_RIGHT_BRACKET = ']',
		OLD_APP_KEY_CARET = '^',
		OLD_APP_KEY_UNDERSCORE = '_',
		OLD_APP_KEY_BACK_QUOTE = '`',
		OLD_APP_KEY_DIGIT_0 = '0',
		OLD_APP_KEY_DIGIT_1 = '1',
		OLD_APP_KEY_DIGIT_2 = '2',
		OLD_APP_KEY_DIGIT_3 = '3',
		OLD_APP_KEY_DIGIT_4 = '4',
		OLD_APP_KEY_DIGIT_5 = '5',
		OLD_APP_KEY_DIGIT_6 = '6',
		OLD_APP_KEY_DIGIT_7 = '7',
		OLD_APP_KEY_DIGIT_8 = '8',
		OLD_APP_KEY_DIGIT_9 = '9',
		OLD_APP_KEY_A = 'a',
		OLD_APP_KEY_B = 'b',
		OLD_APP_KEY_C = 'c',
		OLD_APP_KEY_D = 'd',
		OLD_APP_KEY_E = 'e',
		OLD_APP_KEY_F = 'f',
		OLD_APP_KEY_G = 'g',
		OLD_APP_KEY_H = 'h',
		OLD_APP_KEY_I = 'i',
		OLD_APP_KEY_J = 'j',
		OLD_APP_KEY_K = 'k',
		OLD_APP_KEY_L = 'l',
		OLD_APP_KEY_M = 'm',
		OLD_APP_KEY_N = 'n',
		OLD_APP_KEY_O = 'o',
		OLD_APP_KEY_P = 'p',
		OLD_APP_KEY_Q = 'q',
		OLD_APP_KEY_R = 'r',
		OLD_APP_KEY_S = 's',
		OLD_APP_KEY_T = 't',
		OLD_APP_KEY_U = 'u',
		OLD_APP_KEY_V = 'v',
		OLD_APP_KEY_W = 'w',
		OLD_APP_KEY_X = 'x',
		OLD_APP_KEY_Y = 'y',
		OLD_APP_KEY_Z = 'z',
		OLD_APP_KEY_ESC = 256,
		OLD_APP_KEY_TAB,
		OLD_APP_KEY_BACKSPACE,
		OLD_APP_KEY_RETURN,
		OLD_APP_KEY_DELETE,
		OLD_APP_KEY_INSERT,
		OLD_APP_KEY_HOME,
		OLD_APP_KEY_END,
		OLD_APP_KEY_PGUP,
		OLD_APP_KEY_PGDOWN,
		OLD_APP_KEY_LEFT,
		OLD_APP_KEY_RIGHT,
		OLD_APP_KEY_UP,
		OLD_APP_KEY_DOWN,
		OLD_APP_KEY_SHIFT,
		OLD_APP_KEY_CTRL,
		OLD_APP_KEY_ALT,
		OLD_APP_KEY_CMD,
		OLD_APP_KEY_SCROLL,
		OLD_APP_KEY_CAPS,
		OLD_APP_KEY_NUM,
		OLD_APP_KEY_F1,
		OLD_APP_KEY_F2,
		OLD_APP_KEY_F3,
		OLD_APP_KEY_F4,
		OLD_APP_KEY_F5,
		OLD_APP_KEY_F6,
		OLD_APP_KEY_F7,
		OLD_APP_KEY_F8,
		OLD_APP_KEY_F9,
		OLD_APP_KEY_F10,
		OLD_APP_KEY_F11,
		OLD_APP_KEY_F12,
		OLD_APP_KEY_NUM_KEYS,
	};

	enum
	{
		NEW_INPUT_KEY_UNKNOWN = 0,
		NEW_INPUT_KEY_ESC,
		NEW_INPUT_KEY_F1,
		NEW_INPUT_KEY_F2,
		NEW_INPUT_KEY_F3,
		NEW_INPUT_KEY_F4,
		NEW_INPUT_KEY_F5,
		NEW_INPUT_KEY_F6,
		NEW_INPUT_KEY_F7,
		NEW_INPUT_KEY_F8,
		NEW_INPUT_KEY_F9,
		NEW_INPUT_KEY_F10,
		NEW_INPUT_KEY_F11,
		NEW_INPUT_KEY_F12,
		NEW_INPUT_KEY_PRINTSCREEN,
		NEW_INPUT_KEY_SCROLL_LOCK,
		NEW_INPUT_KEY_PAUSE,
		NEW_INPUT_KEY_BACK_QUOTE,
		NEW_INPUT_KEY_DIGIT_1,
		NEW_INPUT_KEY_DIGIT_2,
		NEW_INPUT_KEY_DIGIT_3,
		NEW_INPUT_KEY_DIGIT_4,
		NEW_INPUT_KEY_DIGIT_5,
		NEW_INPUT_KEY_DIGIT_6,
		NEW_INPUT_KEY_DIGIT_7,
		NEW_INPUT_KEY_DIGIT_8,
		NEW_INPUT_KEY_DIGIT_9,
		NEW_INPUT_KEY_DIGIT_0,
		NEW_INPUT_KEY_MINUS,
		NEW_INPUT_KEY_EQUALS,
		NEW_INPUT_KEY_BACKSPACE,
		NEW_INPUT_KEY_TAB,
		NEW_INPUT_KEY_Q,
		NEW_INPUT_KEY_W,
		NEW_INPUT_KEY_E,
		NEW_INPUT_KEY_R,
		NEW_INPUT_KEY_T,
		NEW_INPUT_KEY_Y,
		NEW_INPUT_KEY_U,
		NEW_INPUT_KEY_I,
		NEW_INPUT_KEY_O,
		NEW_INPUT_KEY_P,
		NEW_INPUT_KEY_LEFT_BRACKET,
		NEW_INPUT_KEY_RIGHT_BRACKET,
		NEW_INPUT_KEY_ENTER,
		NEW_INPUT_KEY_CAPS_LOCK,
		NEW_INPUT_KEY_A,
		NEW_INPUT_KEY_S,
		NEW_INPUT_KEY_D,
		NEW_INPUT_KEY_F,
		NEW_INPUT_KEY_G,
		NEW_INPUT_KEY_H,
		NEW_INPUT_KEY_J,
		NEW_INPUT_KEY_K,
		NEW_INPUT_KEY_L,
		NEW_INPUT_KEY_SEMICOLON,
		NEW_INPUT_KEY_QUOTE,
		NEW_INPUT_KEY_BACK_SLASH,
		NEW_INPUT_KEY_LEFT_SHIFT,
		NEW_INPUT_KEY_LESS,
		NEW_INPUT_KEY_Z,
		NEW_INPUT_KEY_X,
		NEW_INPUT_KEY_C,
		NEW_INPUT_KEY_V,
		NEW_INPUT_KEY_B,
		NEW_INPUT_KEY_N,
		NEW_INPUT_KEY_M,
		NEW_INPUT_KEY_COMMA,
		NEW_INPUT_KEY_DOT,
		NEW_INPUT_KEY_SLASH,
		NEW_INPUT_KEY_RIGHT_SHIFT,
		NEW_INPUT_KEY_LEFT_CTRL,
		NEW_INPUT_KEY_LEFT_CMD,
		NEW_INPUT_KEY_LEFT_ALT,
		NEW_INPUT_KEY_SPACE,
		NEW_INPUT_KEY_RIGHT_ALT,
		NEW_INPUT_KEY_RIGHT_CMD,
		NEW_INPUT_KEY_MENU,
		NEW_INPUT_KEY_RIGHT_CTRL,
		NEW_INPUT_KEY_INSERT,
		NEW_INPUT_KEY_DELETE,
		NEW_INPUT_KEY_HOME,
		NEW_INPUT_KEY_END,
		NEW_INPUT_KEY_PGUP,
		NEW_INPUT_KEY_PGDOWN,
		NEW_INPUT_KEY_UP,
		NEW_INPUT_KEY_LEFT,
		NEW_INPUT_KEY_DOWN,
		NEW_INPUT_KEY_RIGHT,
		NEW_INPUT_KEY_NUM_LOCK,
		NEW_INPUT_KEY_NUMPAD_DIVIDE,
		NEW_INPUT_KEY_NUMPAD_MULTIPLY,
		NEW_INPUT_KEY_NUMPAD_MINUS,
		NEW_INPUT_KEY_NUMPAD_DIGIT_7,
		NEW_INPUT_KEY_NUMPAD_DIGIT_8,
		NEW_INPUT_KEY_NUMPAD_DIGIT_9,
		NEW_INPUT_KEY_NUMPAD_PLUS,
		NEW_INPUT_KEY_NUMPAD_DIGIT_4,
		NEW_INPUT_KEY_NUMPAD_DIGIT_5,
		NEW_INPUT_KEY_NUMPAD_DIGIT_6,
		NEW_INPUT_KEY_NUMPAD_DIGIT_1,
		NEW_INPUT_KEY_NUMPAD_DIGIT_2,
		NEW_INPUT_KEY_NUMPAD_DIGIT_3,
		NEW_INPUT_KEY_NUMPAD_ENTER,
		NEW_INPUT_KEY_NUMPAD_DIGIT_0,
		NEW_INPUT_KEY_NUMPAD_DOT,
		NEW_INPUT_KEY_ANY_SHIFT,
		NEW_INPUT_KEY_ANY_CTRL,
		NEW_INPUT_KEY_ANY_ALT,
		NEW_INPUT_KEY_ANY_CMD,
		NUM_NEW_INPUT_KEYS,
	};

	string convert_app_mouse_button_name(int old_app_button)
	{
		switch (old_app_button)
		{
			case OLD_APP_BUTTON_LEFT:   return "LEFT";
			case OLD_APP_BUTTON_MIDDLE: return "MIDDLE";
			case OLD_APP_BUTTON_RIGHT:  return "RIGHT";
			case OLD_APP_BUTTON_DCLICK: return "DCLICK";
			case OLD_APP_BUTTON_AUX_0:  return "AUX_0";
			case OLD_APP_BUTTON_AUX_1:  return "AUX_1";
			case OLD_APP_BUTTON_AUX_2:  return "AUX_2";
			case OLD_APP_BUTTON_AUX_3:  return "AUX_3";
		}

		return "UNKNOWN";
	}

	string convert_app_key_name(int old_app_key)
	{
		switch (old_app_key)
		{
			case OLD_APP_KEY_SPACE: return "SPACE";
			case OLD_APP_KEY_EXCLAIM: return "UNKNOWN";
			case OLD_APP_KEY_HASH: return "UNKNOWN";
			case OLD_APP_KEY_DOLLAR: return "UNKNOWN";
			case OLD_APP_KEY_PERCENT: return "UNKNOWN";
			case OLD_APP_KEY_AMPERSAND: return "UNKNOWN";
			case OLD_APP_KEY_QUOTE: return "QUOTE";
			case OLD_APP_KEY_APOSTROPHE: return "UNKNOWN";
			case OLD_APP_KEY_LEFT_PAREN: return "UNKNOWN";
			case OLD_APP_KEY_RIGHT_PAREN: return "UNKNOWN";
			case OLD_APP_KEY_ASTERISK: return "UNKNOWN";
			case OLD_APP_KEY_PLUS: return "EQUALS";
			case OLD_APP_KEY_COMMA: return "COMMA";
			case OLD_APP_KEY_MINUS: return "MINUS";
			case OLD_APP_KEY_DOT: return "DOT";
			case OLD_APP_KEY_SLASH: return "SLASH";
			case OLD_APP_KEY_COLON: return "UNKNOWN";
			case OLD_APP_KEY_SEMICOLON: return "SEMICOLON";
			case OLD_APP_KEY_LESS: return "LESS";
			case OLD_APP_KEY_EQUALS: return "EQUALS";
			case OLD_APP_KEY_GREATER: return "UNKNOWN";
			case OLD_APP_KEY_QUESTION: return "UNKNOWN";
			case OLD_APP_KEY_AT: return "UNKNOWN";
			case OLD_APP_KEY_LEFT_BRACKET: return "LEFT_BRACKET";
			case OLD_APP_KEY_BACK_SLASH: return "BACK_SLASH";
			case OLD_APP_KEY_RIGHT_BRACKET: return "RIGHT_BRACKET";
			case OLD_APP_KEY_CARET: return "UNKNOWN";
			case OLD_APP_KEY_UNDERSCORE: return "UNKNOWN";
			case OLD_APP_KEY_BACK_QUOTE: return "BACK_QUOTE";
			case OLD_APP_KEY_DIGIT_0: return "DIGIT_0";
			case OLD_APP_KEY_DIGIT_1: return "DIGIT_1";
			case OLD_APP_KEY_DIGIT_2: return "DIGIT_2";
			case OLD_APP_KEY_DIGIT_3: return "DIGIT_3";
			case OLD_APP_KEY_DIGIT_4: return "DIGIT_4";
			case OLD_APP_KEY_DIGIT_5: return "DIGIT_5";
			case OLD_APP_KEY_DIGIT_6: return "DIGIT_6";
			case OLD_APP_KEY_DIGIT_7: return "DIGIT_7";
			case OLD_APP_KEY_DIGIT_8: return "DIGIT_8";
			case OLD_APP_KEY_DIGIT_9: return "DIGIT_9";
			case OLD_APP_KEY_A: return "A";
			case OLD_APP_KEY_B: return "B";
			case OLD_APP_KEY_C: return "C";
			case OLD_APP_KEY_D: return "D";
			case OLD_APP_KEY_E: return "E";
			case OLD_APP_KEY_F: return "F";
			case OLD_APP_KEY_G: return "G";
			case OLD_APP_KEY_H: return "H";
			case OLD_APP_KEY_I: return "I";
			case OLD_APP_KEY_J: return "J";
			case OLD_APP_KEY_K: return "K";
			case OLD_APP_KEY_L: return "L";
			case OLD_APP_KEY_M: return "M";
			case OLD_APP_KEY_N: return "N";
			case OLD_APP_KEY_O: return "O";
			case OLD_APP_KEY_P: return "P";
			case OLD_APP_KEY_Q: return "Q";
			case OLD_APP_KEY_R: return "R";
			case OLD_APP_KEY_S: return "S";
			case OLD_APP_KEY_T: return "T";
			case OLD_APP_KEY_U: return "U";
			case OLD_APP_KEY_V: return "V";
			case OLD_APP_KEY_W: return "W";
			case OLD_APP_KEY_X: return "X";
			case OLD_APP_KEY_Y: return "Y";
			case OLD_APP_KEY_Z: return "Z";
			case OLD_APP_KEY_ESC: return "ESC";
			case OLD_APP_KEY_TAB: return "TAB";
			case OLD_APP_KEY_BACKSPACE: return "BACKSPACE";
			case OLD_APP_KEY_RETURN: return "ENTER";
			case OLD_APP_KEY_DELETE: return "DELETE";
			case OLD_APP_KEY_INSERT: return "INSERT";
			case OLD_APP_KEY_HOME: return "HOME";
			case OLD_APP_KEY_END: return "END";
			case OLD_APP_KEY_PGUP: return "PGUP";
			case OLD_APP_KEY_PGDOWN: return "PGDOWN";
			case OLD_APP_KEY_LEFT: return "LEFT";
			case OLD_APP_KEY_RIGHT: return "RIGHT";
			case OLD_APP_KEY_UP: return "UP";
			case OLD_APP_KEY_DOWN: return "DOWN";
			case OLD_APP_KEY_SHIFT: return "LEFT_SHIFT";
			case OLD_APP_KEY_CTRL: return "LEFT_CTRL";
			case OLD_APP_KEY_ALT: return "LEFT_ALT";
			case OLD_APP_KEY_CMD: return "LEFT_CMD";
			case OLD_APP_KEY_SCROLL: return "SCROLL_LOCK";
			case OLD_APP_KEY_CAPS: return "CAPS_LOCK";
			case OLD_APP_KEY_NUM: return "NUM_LOCK";
			case OLD_APP_KEY_F1: return "F1";
			case OLD_APP_KEY_F2: return "F2";
			case OLD_APP_KEY_F3: return "F3";
			case OLD_APP_KEY_F4: return "F4";
			case OLD_APP_KEY_F5: return "F5";
			case OLD_APP_KEY_F6: return "F6";
			case OLD_APP_KEY_F7: return "F7";
			case OLD_APP_KEY_F8: return "F8";
			case OLD_APP_KEY_F9: return "F9";
			case OLD_APP_KEY_F10: return "F10";
			case OLD_APP_KEY_F11: return "F11";
			case OLD_APP_KEY_F12: return "F12";
		}

		return "UNKNOWN";
	}

	int convert_app_key_to_input_key(int old_app_key)
	{
		switch (old_app_key)
		{
			case OLD_APP_KEY_SPACE: return NEW_INPUT_KEY_SPACE;
			case OLD_APP_KEY_EXCLAIM: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_HASH: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_DOLLAR: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_PERCENT: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_AMPERSAND: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_QUOTE: return NEW_INPUT_KEY_QUOTE;
			case OLD_APP_KEY_APOSTROPHE: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_LEFT_PAREN: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_RIGHT_PAREN: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_ASTERISK: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_PLUS: return NEW_INPUT_KEY_EQUALS;
			case OLD_APP_KEY_COMMA: return NEW_INPUT_KEY_COMMA;
			case OLD_APP_KEY_MINUS: return NEW_INPUT_KEY_MINUS;
			case OLD_APP_KEY_DOT: return NEW_INPUT_KEY_DOT;
			case OLD_APP_KEY_SLASH: return NEW_INPUT_KEY_SLASH;
			case OLD_APP_KEY_COLON: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_SEMICOLON: return NEW_INPUT_KEY_SEMICOLON;
			case OLD_APP_KEY_LESS: return NEW_INPUT_KEY_LESS;
			case OLD_APP_KEY_EQUALS: return NEW_INPUT_KEY_EQUALS;
			case OLD_APP_KEY_GREATER: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_QUESTION: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_AT: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_LEFT_BRACKET: return NEW_INPUT_KEY_LEFT_BRACKET;
			case OLD_APP_KEY_BACK_SLASH: return NEW_INPUT_KEY_BACK_SLASH;
			case OLD_APP_KEY_RIGHT_BRACKET: return NEW_INPUT_KEY_RIGHT_BRACKET;
			case OLD_APP_KEY_CARET: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_UNDERSCORE: return NEW_INPUT_KEY_UNKNOWN;
			case OLD_APP_KEY_BACK_QUOTE: return NEW_INPUT_KEY_BACK_QUOTE;
			case OLD_APP_KEY_DIGIT_0: return NEW_INPUT_KEY_DIGIT_0;
			case OLD_APP_KEY_DIGIT_1: return NEW_INPUT_KEY_DIGIT_1;
			case OLD_APP_KEY_DIGIT_2: return NEW_INPUT_KEY_DIGIT_2;
			case OLD_APP_KEY_DIGIT_3: return NEW_INPUT_KEY_DIGIT_3;
			case OLD_APP_KEY_DIGIT_4: return NEW_INPUT_KEY_DIGIT_4;
			case OLD_APP_KEY_DIGIT_5: return NEW_INPUT_KEY_DIGIT_5;
			case OLD_APP_KEY_DIGIT_6: return NEW_INPUT_KEY_DIGIT_6;
			case OLD_APP_KEY_DIGIT_7: return NEW_INPUT_KEY_DIGIT_7;
			case OLD_APP_KEY_DIGIT_8: return NEW_INPUT_KEY_DIGIT_8;
			case OLD_APP_KEY_DIGIT_9: return NEW_INPUT_KEY_DIGIT_9;
			case OLD_APP_KEY_A: return NEW_INPUT_KEY_A;
			case OLD_APP_KEY_B: return NEW_INPUT_KEY_B;
			case OLD_APP_KEY_C: return NEW_INPUT_KEY_C;
			case OLD_APP_KEY_D: return NEW_INPUT_KEY_D;
			case OLD_APP_KEY_E: return NEW_INPUT_KEY_E;
			case OLD_APP_KEY_F: return NEW_INPUT_KEY_F;
			case OLD_APP_KEY_G: return NEW_INPUT_KEY_G;
			case OLD_APP_KEY_H: return NEW_INPUT_KEY_H;
			case OLD_APP_KEY_I: return NEW_INPUT_KEY_I;
			case OLD_APP_KEY_J: return NEW_INPUT_KEY_J;
			case OLD_APP_KEY_K: return NEW_INPUT_KEY_K;
			case OLD_APP_KEY_L: return NEW_INPUT_KEY_L;
			case OLD_APP_KEY_M: return NEW_INPUT_KEY_M;
			case OLD_APP_KEY_N: return NEW_INPUT_KEY_N;
			case OLD_APP_KEY_O: return NEW_INPUT_KEY_O;
			case OLD_APP_KEY_P: return NEW_INPUT_KEY_P;
			case OLD_APP_KEY_Q: return NEW_INPUT_KEY_Q;
			case OLD_APP_KEY_R: return NEW_INPUT_KEY_R;
			case OLD_APP_KEY_S: return NEW_INPUT_KEY_S;
			case OLD_APP_KEY_T: return NEW_INPUT_KEY_T;
			case OLD_APP_KEY_U: return NEW_INPUT_KEY_U;
			case OLD_APP_KEY_V: return NEW_INPUT_KEY_V;
			case OLD_APP_KEY_W: return NEW_INPUT_KEY_W;
			case OLD_APP_KEY_X: return NEW_INPUT_KEY_X;
			case OLD_APP_KEY_Y: return NEW_INPUT_KEY_Y;
			case OLD_APP_KEY_Z: return NEW_INPUT_KEY_Z;
			case OLD_APP_KEY_ESC: return NEW_INPUT_KEY_ESC;
			case OLD_APP_KEY_TAB: return NEW_INPUT_KEY_TAB;
			case OLD_APP_KEY_BACKSPACE: return NEW_INPUT_KEY_BACKSPACE;
			case OLD_APP_KEY_RETURN: return NEW_INPUT_KEY_ENTER;
			case OLD_APP_KEY_DELETE: return NEW_INPUT_KEY_DELETE;
			case OLD_APP_KEY_INSERT: return NEW_INPUT_KEY_INSERT;
			case OLD_APP_KEY_HOME: return NEW_INPUT_KEY_HOME;
			case OLD_APP_KEY_END: return NEW_INPUT_KEY_END;
			case OLD_APP_KEY_PGUP: return NEW_INPUT_KEY_PGUP;
			case OLD_APP_KEY_PGDOWN: return NEW_INPUT_KEY_PGDOWN;
			case OLD_APP_KEY_LEFT: return NEW_INPUT_KEY_LEFT;
			case OLD_APP_KEY_RIGHT: return NEW_INPUT_KEY_RIGHT;
			case OLD_APP_KEY_UP: return NEW_INPUT_KEY_UP;
			case OLD_APP_KEY_DOWN: return NEW_INPUT_KEY_DOWN;
			case OLD_APP_KEY_SHIFT: return NEW_INPUT_KEY_LEFT_SHIFT;
			case OLD_APP_KEY_CTRL: return NEW_INPUT_KEY_LEFT_CTRL;
			case OLD_APP_KEY_ALT: return NEW_INPUT_KEY_LEFT_ALT;
			case OLD_APP_KEY_CMD: return NEW_INPUT_KEY_LEFT_CMD;
			case OLD_APP_KEY_SCROLL: return NEW_INPUT_KEY_SCROLL_LOCK;
			case OLD_APP_KEY_CAPS: return NEW_INPUT_KEY_CAPS_LOCK;
			case OLD_APP_KEY_NUM: return NEW_INPUT_KEY_NUM_LOCK;
			case OLD_APP_KEY_F1: return NEW_INPUT_KEY_F1;
			case OLD_APP_KEY_F2: return NEW_INPUT_KEY_F2;
			case OLD_APP_KEY_F3: return NEW_INPUT_KEY_F3;
			case OLD_APP_KEY_F4: return NEW_INPUT_KEY_F4;
			case OLD_APP_KEY_F5: return NEW_INPUT_KEY_F5;
			case OLD_APP_KEY_F6: return NEW_INPUT_KEY_F6;
			case OLD_APP_KEY_F7: return NEW_INPUT_KEY_F7;
			case OLD_APP_KEY_F8: return NEW_INPUT_KEY_F8;
			case OLD_APP_KEY_F9: return NEW_INPUT_KEY_F9;
			case OLD_APP_KEY_F10: return NEW_INPUT_KEY_F10;
			case OLD_APP_KEY_F11: return NEW_INPUT_KEY_F11;
			case OLD_APP_KEY_F12: return NEW_INPUT_KEY_F12;
		}

		return NEW_INPUT_KEY_UNKNOWN;
	}

	void configControls(Xml xml)
	{
		// for all
		int remove_grab_key_id = xml.findChild("remove_grab_key");
		if (remove_grab_key_id == -1)
		{
			Xml remove_grab_key = xml.addChild("remove_grab_key");
			remove_grab_key.setData("ESC");
		}

		// from 2.15.1.0
		int keys_id = xml.findChild("keys");
		int buttons_id = xml.findChild("buttons");

		// from 2.16.0.1
		int codes_id = xml.findChild("codes");
		int mouse_buttons_id = xml.findChild("mouse_buttons");

		if (keys_id != -1 && buttons_id != -1)
		{
			need_convert_console_key = 1;

			Xml keys = xml.getChild(keys_id);
			for (int i = 0; i < keys.getNumChildren() && i < 32; i++)
			{
				Xml child = keys.getChild(i);
				int old_app_key = int(child.getName());

				string new_input_key_name = convert_app_key_name(old_app_key);

				child.setName(STATE_NAME[i]);
				child.setData(new_input_key_name);
			}

			Xml buttons = xml.getChild(buttons_id);
			buttons.setName("mouse_buttons");

			for (int i = 0; i < buttons.getNumChildren() && i < 32; i++)
			{
				Xml child = buttons.getChild(i);
				int old_app_button = int(child.getName());

				string new_input_button_name = convert_app_mouse_button_name(old_app_button);

				child.setName(STATE_NAME[i]);
				child.setData(new_input_button_name);
			}
		}

		if (codes_id != -1 && mouse_buttons_id != -1)
		{
			Xml codes = xml.getChild(codes_id);
			codes.setName("keys");

			for (int i = 0; i < codes.getNumChildren() && i < 32; i++)
			{
				Xml child = codes.getChild(i);
				string key_name = child.getData();
				if (key_name == "RETURN")
					child.setData("ENTER");
			}
		}

		// fix bug with default left button
		if (mouse_buttons_id != -1)
		{
			Xml mouse_buttons = xml.getChild(mouse_buttons_id);
			for (int i = 0; i < mouse_buttons.getNumChildren() && i < 32; i++)
			{
				Xml child = mouse_buttons.getChild(i);
				string button_name = child.getData();

				if (button_name == "LEFT" && STATE_NAME[i] != "FIRE")
					child.setData("UNKNOWN");
			}
		}
	}

	void configUser(Xml xml)
	{
		// from 2.15.1.0
		if (need_convert_console_key)
		{
			int console_key_id = xml.findChild("console_key");
			if (console_key_id != -1)
			{
				Xml console_key = xml.getChild(console_key_id);
				int old_app_key = console_key.getIntData();

				int new_input_key = convert_app_key_to_input_key(old_app_key);
				
				console_key.setIntData(new_input_key);
			}
		}

		// from 2.16.0.1
		int console_code_id = xml.findChild("console_code");
		if (console_code_id != -1)
		{
			Xml console_code = xml.getChild(console_code_id);
			console_code.setName("console_key");
		}

		int video_extension_id = xml.findChild("video_extension");
		if (video_extension_id != -1)
		{
			Xml video_extension = xml.getChild(video_extension_id);
			if (xml.findChild("screenshot_extension") != -1)
			{
				delete xml.removeChild(video_extension);
			} else
			{
				video_extension.setName("screenshot_extension");

				if (video_extension.getIntData() == 0)
				{
					video_extension.setData("tga");
				} else if (video_extension.getIntData() == 1)
				{
					video_extension.setData("dds");
				} else if (video_extension.getIntData() == 2)
				{
					video_extension.setData("png");
				} else if (video_extension.getIntData() == 3)
				{
					video_extension.setData("jpg");
				}
			}
		}
	}

	/******************************************************************************\
	*
	* Editor's hotkey preset
	*
	\******************************************************************************/
	enum
	{
		KEY_OLD_SPACE = ' ',
		KEY_OLD_EXCLAIM = '!',
		KEY_OLD_DOUBLE_QUOTE = '"',
		KEY_OLD_HASH = '#',
		KEY_OLD_DOLLAR = '$',
		KEY_OLD_PERCENT = '%',
		KEY_OLD_AMPERSAND = '&',
		KEY_OLD_QUOTE = '\'',
		KEY_OLD_APOSTROPHE = KEY_OLD_QUOTE,
		KEY_OLD_LEFT_PAREN = '(',
		KEY_OLD_RIGHT_PAREN = ')',
		KEY_OLD_ASTERISK = '*',
		KEY_OLD_PLUS = '+',
		KEY_OLD_COMMA = ',',
		KEY_OLD_MINUS = '-',
		KEY_OLD_DOT = '.',
		KEY_OLD_SLASH = '/',
		KEY_OLD_COLON = ':',
		KEY_OLD_SEMICOLON = ';',
		KEY_OLD_LESS = '<',
		KEY_OLD_EQUALS = '=',
		KEY_OLD_GREATER = '>',
		KEY_OLD_QUESTION = '?',
		KEY_OLD_AT = '@',
		KEY_OLD_LEFT_BRACKET = '[',
		KEY_OLD_BACK_SLASH = '\\',
		KEY_OLD_RIGHT_BRACKET = ']',
		KEY_OLD_CARET = '^',
		KEY_OLD_UNDERSCORE = '_',
		KEY_OLD_BACK_QUOTE = '`',
		KEY_OLD_DIGIT_0 = '0',
		KEY_OLD_DIGIT_1 = '1',
		KEY_OLD_DIGIT_2 = '2',
		KEY_OLD_DIGIT_3 = '3',
		KEY_OLD_DIGIT_4 = '4',
		KEY_OLD_DIGIT_5 = '5',
		KEY_OLD_DIGIT_6 = '6',
		KEY_OLD_DIGIT_7 = '7',
		KEY_OLD_DIGIT_8 = '8',
		KEY_OLD_DIGIT_9 = '9',
		KEY_OLD_A = 'a',
		KEY_OLD_B = 'b',
		KEY_OLD_C = 'c',
		KEY_OLD_D = 'd',
		KEY_OLD_E = 'e',
		KEY_OLD_F = 'f',
		KEY_OLD_G = 'g',
		KEY_OLD_H = 'h',
		KEY_OLD_I = 'i',
		KEY_OLD_J = 'j',
		KEY_OLD_K = 'k',
		KEY_OLD_L = 'l',
		KEY_OLD_M = 'm',
		KEY_OLD_N = 'n',
		KEY_OLD_O = 'o',
		KEY_OLD_P = 'p',
		KEY_OLD_Q = 'q',
		KEY_OLD_R = 'r',
		KEY_OLD_S = 's',
		KEY_OLD_T = 't',
		KEY_OLD_U = 'u',
		KEY_OLD_V = 'v',
		KEY_OLD_W = 'w',
		KEY_OLD_X = 'x',
		KEY_OLD_Y = 'y',
		KEY_OLD_Z = 'z',
		KEY_OLD_ESC = 256,
		KEY_OLD_TAB,
		KEY_OLD_BACKSPACE,
		KEY_OLD_RETURN,
		KEY_OLD_DELETE,
		KEY_OLD_INSERT,
		KEY_OLD_HOME,
		KEY_OLD_END,
		KEY_OLD_PGUP,
		KEY_OLD_PGDOWN,
		KEY_OLD_LEFT,
		KEY_OLD_RIGHT,
		KEY_OLD_UP,
		KEY_OLD_DOWN,
		KEY_OLD_SHIFT,
		KEY_OLD_CTRL,
		KEY_OLD_ALT,
		KEY_OLD_CMD,
		KEY_OLD_SCROLL,
		KEY_OLD_CAPS,
		KEY_OLD_NUM,
		KEY_OLD_F1,
		KEY_OLD_F2,
		KEY_OLD_F3,
		KEY_OLD_F4,
		KEY_OLD_F5,
		KEY_OLD_F6,
		KEY_OLD_F7,
		KEY_OLD_F8,
		KEY_OLD_F9,
		KEY_OLD_F10,
		KEY_OLD_F11,
		KEY_OLD_F12,
		KEY_OLD_NUM_KEYS,
	};

	enum
	{
		KEY_NEW_UNKNOWN = 0,
		KEY_NEW_ESC,
		KEY_NEW_F1,
		KEY_NEW_F2,
		KEY_NEW_F3,
		KEY_NEW_F4,
		KEY_NEW_F5,
		KEY_NEW_F6,
		KEY_NEW_F7,
		KEY_NEW_F8,
		KEY_NEW_F9,
		KEY_NEW_F10,
		KEY_NEW_F11,
		KEY_NEW_F12,
		KEY_NEW_PRINTSCREEN,
		KEY_NEW_SCROLL_LOCK,
		KEY_NEW_PAUSE,
		KEY_NEW_BACK_QUOTE,
		KEY_NEW_DIGIT_1,
		KEY_NEW_DIGIT_2,
		KEY_NEW_DIGIT_3,
		KEY_NEW_DIGIT_4,
		KEY_NEW_DIGIT_5,
		KEY_NEW_DIGIT_6,
		KEY_NEW_DIGIT_7,
		KEY_NEW_DIGIT_8,
		KEY_NEW_DIGIT_9,
		KEY_NEW_DIGIT_0,
		KEY_NEW_MINUS,
		KEY_NEW_EQUALS,
		KEY_NEW_BACKSPACE,
		KEY_NEW_TAB,
		KEY_NEW_Q,
		KEY_NEW_W,
		KEY_NEW_E,
		KEY_NEW_R,
		KEY_NEW_T,
		KEY_NEW_Y,
		KEY_NEW_U,
		KEY_NEW_I,
		KEY_NEW_O,
		KEY_NEW_P,
		KEY_NEW_LEFT_BRACKET,
		KEY_NEW_RIGHT_BRACKET,
		KEY_NEW_ENTER,
		KEY_NEW_CAPS_LOCK,
		KEY_NEW_A,
		KEY_NEW_S,
		KEY_NEW_D,
		KEY_NEW_F,
		KEY_NEW_G,
		KEY_NEW_H,
		KEY_NEW_J,
		KEY_NEW_K,
		KEY_NEW_L,
		KEY_NEW_SEMICOLON,
		KEY_NEW_QUOTE,
		KEY_NEW_BACK_SLASH,
		KEY_NEW_LEFT_SHIFT,
		KEY_NEW_LESS,
		KEY_NEW_Z,
		KEY_NEW_X,
		KEY_NEW_C,
		KEY_NEW_V,
		KEY_NEW_B,
		KEY_NEW_N,
		KEY_NEW_M,
		KEY_NEW_COMMA,
		KEY_NEW_DOT,
		KEY_NEW_SLASH,
		KEY_NEW_RIGHT_SHIFT,
		KEY_NEW_LEFT_CTRL,
		KEY_NEW_LEFT_CMD,
		KEY_NEW_LEFT_ALT,
		KEY_NEW_SPACE,
		KEY_NEW_RIGHT_ALT,
		KEY_NEW_RIGHT_CMD,
		KEY_NEW_MENU,
		KEY_NEW_RIGHT_CTRL,
		KEY_NEW_INSERT,
		KEY_NEW_DELETE,
		KEY_NEW_HOME,
		KEY_NEW_END,
		KEY_NEW_PGUP,
		KEY_NEW_PGDOWN,
		KEY_NEW_UP,
		KEY_NEW_LEFT,
		KEY_NEW_DOWN,
		KEY_NEW_RIGHT,
		KEY_NEW_NUM_LOCK,
		KEY_NEW_NUMPAD_DIVIDE,
		KEY_NEW_NUMPAD_MULTIPLY,
		KEY_NEW_NUMPAD_MINUS,
		KEY_NEW_NUMPAD_DIGIT_7,
		KEY_NEW_NUMPAD_DIGIT_8,
		KEY_NEW_NUMPAD_DIGIT_9,
		KEY_NEW_NUMPAD_PLUS,
		KEY_NEW_NUMPAD_DIGIT_4,
		KEY_NEW_NUMPAD_DIGIT_5,
		KEY_NEW_NUMPAD_DIGIT_6,
		KEY_NEW_NUMPAD_DIGIT_1,
		KEY_NEW_NUMPAD_DIGIT_2,
		KEY_NEW_NUMPAD_DIGIT_3,
		KEY_NEW_NUMPAD_ENTER,
		KEY_NEW_NUMPAD_DIGIT_0,
		KEY_NEW_NUMPAD_DOT,
		KEY_NEW_ANY_SHIFT,
		KEY_NEW_ANY_CTRL,
		KEY_NEW_ANY_ALT,
		KEY_NEW_ANY_CMD,
		NUM_NEW_KEYS,
	};

	int KEY_MAP[KEY_OLD_NUM_KEYS];
	int KEY_MAP_INITIALIZED = 0;
	void initialize_key_map()
	{
		if (KEY_MAP_INITIALIZED == 1)
			return;

		for (int i = 0; i < KEY_OLD_NUM_KEYS; i++)
			KEY_MAP[i] = 0;

		KEY_MAP[KEY_OLD_SPACE] = KEY_NEW_SPACE;
		KEY_MAP[KEY_OLD_EXCLAIM] = KEY_NEW_DIGIT_1;
		KEY_MAP[KEY_OLD_DOUBLE_QUOTE] = KEY_NEW_DIGIT_2;
		KEY_MAP[KEY_OLD_HASH] = KEY_NEW_DIGIT_3;
		KEY_MAP[KEY_OLD_DOLLAR] = KEY_NEW_DIGIT_4;
		KEY_MAP[KEY_OLD_PERCENT] = KEY_NEW_DIGIT_5;
		KEY_MAP[KEY_OLD_AMPERSAND] = KEY_NEW_DIGIT_7;
		KEY_MAP[KEY_OLD_QUOTE] = KEY_NEW_QUOTE;
		KEY_MAP[KEY_OLD_LEFT_PAREN] = KEY_NEW_DIGIT_9;
		KEY_MAP[KEY_OLD_RIGHT_PAREN] = KEY_NEW_DIGIT_0;
		KEY_MAP[KEY_OLD_ASTERISK] = KEY_NEW_NUMPAD_MULTIPLY;
		KEY_MAP[KEY_OLD_PLUS] = KEY_NEW_NUMPAD_PLUS;
		KEY_MAP[KEY_OLD_COMMA] = KEY_NEW_COMMA;
		KEY_MAP[KEY_OLD_MINUS] = KEY_NEW_MINUS;
		KEY_MAP[KEY_OLD_DOT] = KEY_NEW_DOT;
		KEY_MAP[KEY_OLD_SLASH] = KEY_NEW_SLASH;
		KEY_MAP[KEY_OLD_COLON] = KEY_NEW_SEMICOLON;
		KEY_MAP[KEY_OLD_SEMICOLON] = KEY_NEW_SEMICOLON;
		KEY_MAP[KEY_OLD_LESS] = KEY_NEW_LESS;
		KEY_MAP[KEY_OLD_EQUALS] = KEY_NEW_EQUALS;
		KEY_MAP[KEY_OLD_GREATER] = KEY_NEW_DOT;
		KEY_MAP[KEY_OLD_QUESTION] = KEY_NEW_SLASH;
		KEY_MAP[KEY_OLD_AT] = KEY_NEW_DIGIT_2;
		KEY_MAP[KEY_OLD_LEFT_BRACKET] = KEY_NEW_LEFT_BRACKET;
		KEY_MAP[KEY_OLD_BACK_SLASH] = KEY_NEW_BACK_SLASH;
		KEY_MAP[KEY_OLD_RIGHT_BRACKET] = KEY_NEW_RIGHT_BRACKET;
		KEY_MAP[KEY_OLD_CARET] = KEY_NEW_NUMPAD_DIGIT_6;
		KEY_MAP[KEY_OLD_UNDERSCORE] = KEY_NEW_MINUS;
		KEY_MAP[KEY_OLD_BACK_QUOTE] = KEY_NEW_BACK_QUOTE;
		KEY_MAP[KEY_OLD_DIGIT_0] = KEY_NEW_DIGIT_0;
		KEY_MAP[KEY_OLD_DIGIT_1] = KEY_NEW_DIGIT_1;
		KEY_MAP[KEY_OLD_DIGIT_2] = KEY_NEW_DIGIT_2;
		KEY_MAP[KEY_OLD_DIGIT_3] = KEY_NEW_DIGIT_3;
		KEY_MAP[KEY_OLD_DIGIT_4] = KEY_NEW_DIGIT_4;
		KEY_MAP[KEY_OLD_DIGIT_5] = KEY_NEW_DIGIT_5;
		KEY_MAP[KEY_OLD_DIGIT_6] = KEY_NEW_DIGIT_6;
		KEY_MAP[KEY_OLD_DIGIT_7] = KEY_NEW_DIGIT_7;
		KEY_MAP[KEY_OLD_DIGIT_8] = KEY_NEW_DIGIT_8;
		KEY_MAP[KEY_OLD_DIGIT_9] = KEY_NEW_DIGIT_9;
		KEY_MAP[KEY_OLD_A] = KEY_NEW_A;
		KEY_MAP[KEY_OLD_B] = KEY_NEW_B;
		KEY_MAP[KEY_OLD_C] = KEY_NEW_C;
		KEY_MAP[KEY_OLD_D] = KEY_NEW_D;
		KEY_MAP[KEY_OLD_E] = KEY_NEW_E;
		KEY_MAP[KEY_OLD_F] = KEY_NEW_F;
		KEY_MAP[KEY_OLD_G] = KEY_NEW_G;
		KEY_MAP[KEY_OLD_H] = KEY_NEW_H;
		KEY_MAP[KEY_OLD_I] = KEY_NEW_I;
		KEY_MAP[KEY_OLD_J] = KEY_NEW_J;
		KEY_MAP[KEY_OLD_K] = KEY_NEW_K;
		KEY_MAP[KEY_OLD_L] = KEY_NEW_L;
		KEY_MAP[KEY_OLD_M] = KEY_NEW_M;
		KEY_MAP[KEY_OLD_N] = KEY_NEW_N;
		KEY_MAP[KEY_OLD_O] = KEY_NEW_O;
		KEY_MAP[KEY_OLD_P] = KEY_NEW_P;
		KEY_MAP[KEY_OLD_Q] = KEY_NEW_Q;
		KEY_MAP[KEY_OLD_R] = KEY_NEW_R;
		KEY_MAP[KEY_OLD_S] = KEY_NEW_S;
		KEY_MAP[KEY_OLD_T] = KEY_NEW_T;
		KEY_MAP[KEY_OLD_U] = KEY_NEW_U;
		KEY_MAP[KEY_OLD_V] = KEY_NEW_V;
		KEY_MAP[KEY_OLD_W] = KEY_NEW_W;
		KEY_MAP[KEY_OLD_X] = KEY_NEW_X;
		KEY_MAP[KEY_OLD_Y] = KEY_NEW_Y;
		KEY_MAP[KEY_OLD_Z] = KEY_NEW_Z;
		KEY_MAP[KEY_OLD_ESC] = KEY_NEW_ESC;
		KEY_MAP[KEY_OLD_TAB] = KEY_NEW_TAB;
		KEY_MAP[KEY_OLD_BACKSPACE] = KEY_NEW_BACKSPACE;
		KEY_MAP[KEY_OLD_RETURN] = KEY_NEW_ENTER;
		KEY_MAP[KEY_OLD_DELETE] = KEY_NEW_DELETE;
		KEY_MAP[KEY_OLD_INSERT] = KEY_NEW_INSERT;
		KEY_MAP[KEY_OLD_HOME] = KEY_NEW_HOME;
		KEY_MAP[KEY_OLD_END] = KEY_NEW_END;
		KEY_MAP[KEY_OLD_PGUP] = KEY_NEW_PGUP;
		KEY_MAP[KEY_OLD_PGDOWN] = KEY_NEW_PGDOWN;
		KEY_MAP[KEY_OLD_LEFT] = KEY_NEW_LEFT;
		KEY_MAP[KEY_OLD_RIGHT] = KEY_NEW_RIGHT;
		KEY_MAP[KEY_OLD_UP] = KEY_NEW_UP;
		KEY_MAP[KEY_OLD_DOWN] = KEY_NEW_DOWN;
		KEY_MAP[KEY_OLD_SHIFT] = KEY_NEW_ANY_SHIFT;
		KEY_MAP[KEY_OLD_CTRL] = KEY_NEW_ANY_CTRL;
		KEY_MAP[KEY_OLD_ALT] = KEY_NEW_ANY_ALT;
		KEY_MAP[KEY_OLD_CMD] = KEY_NEW_ANY_CMD;
		KEY_MAP[KEY_OLD_SCROLL] = KEY_NEW_SCROLL_LOCK;
		KEY_MAP[KEY_OLD_CAPS] = KEY_NEW_CAPS_LOCK;
		KEY_MAP[KEY_OLD_NUM] = KEY_NEW_NUM_LOCK;
		KEY_MAP[KEY_OLD_F1] = KEY_NEW_F1;
		KEY_MAP[KEY_OLD_F2] = KEY_NEW_F2;
		KEY_MAP[KEY_OLD_F3] = KEY_NEW_F3;
		KEY_MAP[KEY_OLD_F4] = KEY_NEW_F4;
		KEY_MAP[KEY_OLD_F5] = KEY_NEW_F5;
		KEY_MAP[KEY_OLD_F6] = KEY_NEW_F6;
		KEY_MAP[KEY_OLD_F7] = KEY_NEW_F7;
		KEY_MAP[KEY_OLD_F8] = KEY_NEW_F8;
		KEY_MAP[KEY_OLD_F9] = KEY_NEW_F9;
		KEY_MAP[KEY_OLD_F10] = KEY_NEW_F10;
		KEY_MAP[KEY_OLD_F11] = KEY_NEW_F11;
		KEY_MAP[KEY_OLD_F12] = KEY_NEW_F12;

		KEY_MAP_INITIALIZED = 1;
	}

	int convert_key_value(int key_value) {
		if (key_value < 0 || key_value >= KEY_OLD_NUM_KEYS) {
			Log::error("Failed to convert key value - %d", key_value);
			return 0;
		}

		initialize_key_map();
		return KEY_MAP[key_value];
	}
	void editorHotkeyPreset(Json json)
	{
		Json controls = json.getChild("controls");
		if (controls == NULL || !controls.isArray()) {
			Log::error("Failed, there is no `controls` array");
			return;
		}

		for (int i = 0; i < controls.getNumChildren(); i++) {
			Json control = controls.getChild(i);
			if (!control.isObject()) {
				Log::error("Failed, a child is not an object");
				continue;
			}
			Json key = control.getChild("key");
			if (key == NULL) {
				Log::error("Failed to find a key");
				continue;
			}
			if (!key.isNumber()) {
				Log::error("Failed, a key is not a number");
				continue;
			}
			int old_key_value = key.getInt();
			int new_key_value = convert_key_value(old_key_value);
			key.setInt(new_key_value);
		}
	}

}

#endif /* __MIGRATION_PROCESS_H__ */
