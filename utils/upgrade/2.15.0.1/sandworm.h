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

#ifndef __MIGRATION_SANDWORM_H__
#define __MIGRATION_SANDWORM_H__

/*
 */
namespace Sandworm {

	enum
	{
		ERROR_STRING = -1,
		INT = 0,
		LONG,
		FLOAT,
		DOUBLE,
		VEC2,
		VEC3,
		VEC4,
		DVEC2,
		DVEC3,
		DVEC4,
		IVEC2,
		IVEC3,
		IVEC4,
		MAT4,
		DMAT4,
		QUAT,
		STRING,
		GUID,
		USER_CLASS,
		EXTERN_CLASS,
	};

	enum
	{
		None,
		Begin,
		Elevation = Begin,
		Imagery,
		Vector,
		Mask,
		Size,
	};

	class Object
	{
		Json json;
		string name;
		int enabled;
		string slot_id;
		string type;
		string node;

		Object(Json doc)
		{
			json = doc;
			Json name_json = doc.getChild("name");
			if (name_json != NULL)
				name = name_json.getString();
			Json enabled_json = doc.getChild("enabled");
			if (enabled_json != NULL)
				enabled = enabled_json.getBool();
			Json type_json = doc.getChild("type");
			if (type_json!= NULL)
				type = type_json.getString();
			Json node_json = doc.getChild("node");
			if (node_json != NULL)
				node = node_json.getString();
		}

		void save(Json doc)
		{
			UGUID guid = new UGUID();
			guid.generate();
			doc.addChild("id", guid.getString());
			doc.addChild("name", name);
			doc.addChild("enabled").setBool(enabled);
			doc.addChild("slot_id", slot_id);
			doc.addChild("type", type);
			doc.addChild("node", node);

			if (type == "ObjectRoad")
			{
				Json forward_json = json.getChild("forward_axis");
				if (forward_json != NULL)
					doc.addChild("forward_axis", int(forward_json.getNumber()));
				Json decal_json = json.getChild("decal_texture_resolution");
				if (decal_json != NULL)
					doc.addChild("decal_texture_resolution", int(decal_json.getNumber()));
				Json is_split_json = json.getChild("is_split_segmnets");
				if (is_split_json != NULL)
					doc.addChild("is_split_segmnets").setBool(int(is_split_json.getNumber()));
				Json split_segment_json = json.getChild("split_segmnet_length");
				if (split_segment_json != NULL)
					doc.addChild("split_segmnet_length", split_segment_json.getNumber());
				Json split_spline_json = json.getChild("split_spline_length");
				if (split_spline_json != NULL)
					doc.addChild("split_spline_length", split_spline_json.getNumber());
				Json adjust_json = json.getChild("adjust_terrain");
				if (adjust_json != NULL)
					doc.addChild("adjust_terrain").setBool(int(adjust_json.getNumber()));
				Json modify_json = json.getChild("modify_width");
				if (modify_json != NULL)
					doc.addChild("modify_width", modify_json.getNumber());
			} else if (type == "ObjectPoint")
			{
				Json is_fence_json = json.getChild("is_fence");
				if (is_fence_json != NULL)
					doc.addChild("is_fence").setBool(int(is_fence_json.getNumber()));
				Json auto_size_json = json.getChild("auto_size");
				if (auto_size_json!= NULL)
					doc.addChild("auto_size").setBool(int(auto_size_json.getNumber()));
				Json step_json = json.getChild("step");
				if (step_json != NULL)
					doc.addChild("step", step_json.getNumber());
				Json start_json = json.getChild("start_offset");
				if (start_json != NULL)
					doc.addChild("start_offset", start_json.getNumber());
				Json end_json = json.getChild("end_offset");
				if (end_json != NULL)
					doc.addChild("end_offset", end_json.getNumber());
				Json fit_to_size_json = json.getChild("fit_to_size");
				if (fit_to_size_json != NULL)
					doc.addChild("fit_to_size").setBool(int(fit_to_size_json.getNumber()));
				Json collider_json = json.getChild("collider");
				if (collider_json != NULL)
					doc.addChild("collider").setBool(int(collider_json.getNumber()));
				Json drop_to_groun_json = json.getChild("drop_to_ground");
				if (drop_to_groun_json != NULL)
					doc.addChild("drop_to_ground").setBool(int(drop_to_groun_json.getNumber()));
				Json height_offset_json = json.getChild("height_offset");
				if (height_offset_json != NULL)
					doc.addChild("height_offset", height_offset_json.getNumber());
				Json bake_to_cluster = json.getChild("bake_to_cluster");
				if (bake_to_cluster != NULL)
					doc.addChild("bake_to_cluster").setBool(int(bake_to_cluster.getNumber()));
				Json forward_json = json.getChild("forward_axis");
				if (forward_json != NULL)
					doc.addChild("forward_axis", int(forward_json.getNumber()));
				Json split_billboard_json = json.getChild("split_billboards_length");
				if (split_billboard_json != NULL)
					doc.addChild("split_billboards_length", split_billboard_json.getNumber());
			} else if (type == "ObjectBuilding")
			{
				doc.addChild("auto_mode").setBool(1);
				doc.addChild("material_mode", 0);
				doc.addChild("material_attributes", "building:material");
				Json materials_json = doc.addChild("materials");
				materials_json.setArray();
				Json material_json = materials_json.addChild(NULL);
				material_json.addChild("guid", "c5908b31f2339aa994b3ce440a51e0c21b7f048b");
				material_json.addChild("enabled").setBool(1);
				material_json.addChild("probability", 1);

				doc.addChild("column_size", 3.0);
				doc.addChild("texture_column_number", 4);
				Json floor_height_json = json.getChild("floor_height");
				if (floor_height_json != NULL)
					doc.addChild("row_size", floor_height_json.getNumber());
				Json floors_per_texture_json = json.getChild("floors_per_texture");
				if (floors_per_texture_json != NULL)
					doc.addChild("texture_row_number", int(floors_per_texture_json.getNumber()));
				doc.addChild("floor_mode", 0);
				Json floor_count_filter = json.getChild("floor_count_filter");
				if (floor_count_filter == NULL)
					doc.addChild("floor_attributes", "building:levels,floor");
				else
					doc.addChild("floor_attributes", floor_count_filter.getString());
				doc.addChild("min_floor", 1);
				doc.addChild("max_floor", 5);

				doc.addChild("use_vertex_color").setBool(0);
				doc.addChild("roof_unit_size", 6.0);
				doc.addChild("roof_type_mode", 0);
				doc.addChild("roof_type_attributes", "roof:shape");
				Json roof_types_json = doc.addChild("roof_types");
				roof_types_json.setArray();
				for (int i = 0; i < 4; i++)
				{
					Json roof_type_json = roof_types_json.addChild(NULL);
					roof_type_json.addChild("type", i);
					int probability = 2;
					// 1 - skillion
					if (i == 1)
						probability = 1;
					roof_type_json.addChild("probability", probability);
				}

				doc.addChild("roof_height_mode", 0);
				doc.addChild("roof_height_attributes", "roof:height");
				Json roof_heights_json = doc.addChild("roof_heights");
				roof_heights_json.setArray();
				for (int i = 0; i < 4; i++)
				{
					Json roof_height_json = roof_heights_json.addChild(NULL);
					roof_height_json.addChild("type", i);
					// flat
					float min = 0.3;
					float max = 0.3;
					// skillion
					if (i == 1)
					{
						min = 1.0;
						max = 3.0;
					// gabled
					} else if (i == 2)
					{
						min = 2.0;
						max = 6.0;
					// hipped
					} else if (i == 3)
					{
						min = 2.0;
						max = 4.0;
					}
					roof_height_json.addChild("min", min);
					roof_height_json.addChild("max", max);
				}

				doc.addChild("roof_material_mode", 0);
				doc.addChild("roof_material_attributes", "roof:material");
				Json roof_materials_json = doc.addChild("roof_materials");
				roof_materials_json.setArray();
				for (int i = 0; i < 4; i++)
				{
					Json roof_material_json = roof_materials_json.addChild(NULL);
					roof_material_json.addChild("type", i);

					Json materials_json = roof_material_json.addChild("materials");
					materials_json.setArray();
					{
						Json material_json = materials_json.addChild(NULL);
						// asphalt guid
						string guid = "8280d46f7d3d3e29734ccf6bac05699d4552d7f5";
						int enabled = 0;
						if (i == 0)
							enabled = 1;
						material_json.addChild("guid", guid);
						material_json.addChild("enabled").setBool(enabled);
						material_json.addChild("probability", 1);
					}
					{
						Json material_json = materials_json.addChild(NULL);
						// asbestos guid
						int enabled = 1;
						if (i == 0)
							enabled = 0;
						string guid = "bb5424b2d000dfbdf8e726c6fc915ccf2b68159f";
						material_json.addChild("guid", guid);
						material_json.addChild("enabled").setBool(enabled);
						material_json.addChild("probability", 1);
					}
				}

				Json ground_floor_offset_json = json.getChild("ground_floor_offset");
				if (ground_floor_offset_json != NULL)
					doc.addChild("underground_offset", ground_floor_offset_json.getNumber());
				doc.addChild("basement_offset", 0.7);
				Json split_length_json = json.getChild("split_length");
				if (split_length_json != NULL)
					doc.addChild("split_length", split_length_json.getNumber());
				Json min_visibility_json = json.getChild("min_visibiluty");
				if (min_visibility_json != NULL)
					doc.addChild("min_visibility", min_visibility_json.getNumber());
				Json max_visibility_json = json.getChild("max_visibiluty");
				if (max_visibility_json != NULL)
					doc.addChild("max_visibility", max_visibility_json.getNumber());
				Json min_fade_json = json.getChild("min_fade");
				if (min_fade_json != NULL)
					doc.addChild("min_fade", min_fade_json.getNumber());
				Json max_fade_json = json.getChild("max_fade");
				if (max_fade_json != NULL)
					doc.addChild("max_fade", max_fade_json.getNumber());
			}
		}

		string getFilterHash()
		{
			string filter_hash;
			if (json != NULL)
			{
				Json filter_hash_json = json.getChild("filter_hash");
				if (filter_hash_json != NULL)
					filter_hash = filter_hash_json.getString();
			}
			return filter_hash;
		}

		string getFilterName()
		{
			string filter_name;
			if (json != NULL)
			{
				Json filter_name_json = json.getChild("filter_name");
				if (filter_name_json != NULL)
					filter_name = filter_name_json.getString();
			}
			return filter_name;
		}
	};

	class Filter
	{
		Json json;
		string id;
		string name;
		string type;

		Filter(Json doc)
		{
			json = doc;
			Json name_json = doc.getChild("name");
			if (name_json != NULL)
				name = name_json.getString();
			Json type_json = doc.getChild("type");
			if (type_json != NULL)
				type = type_json.getString();
		}

		void save(Json doc)
		{
			doc.addChild("name", name);
			doc.addChild("type", type);
			if (type == "FilterPixelChannel")
			{
				Json channel = json.getChild("channel");
				if(channel != NULL)
					doc.addChild("channel", int(channel.getNumber()));
			} else if (type == "FilterPixelColor")
			{
				Json colors_parameter = doc.addChild("colors");
				colors_parameter.setArray();
				Json colors = json.getChild("color");
				if (colors != NULL)
					for (int i = 0; i < colors.getNumChildren(); i++)
						colors_parameter.addChild(NULL, int(colors.getChild(i).getNumber()));

				Json thresholds_parameter = doc.addChild("thresholds");
				thresholds_parameter.setArray();
				Json threshold = json.getChild("threshold");
				if (threshold != NULL)
					thresholds_parameter.addChild(NULL, int(threshold.getNumber()));
			} else if (type == "FilterPixelIndex")
			{
				Json rules_json = doc.addChild("rules");
				rules_json.setArray();
				Json first_value = json.getChild("first_value");
				if (first_value != NULL)
					rules_json.addChild(NULL, first_value.getNumber());
				Json second_value = json.getChild("second_value");
				if (second_value != NULL)
					rules_json.addChild(NULL, second_value.getNumber());
			} else if (type == "FilterAttribute")
			{
				Json rules_json = doc.addChild("rules");
				rules_json.setArray();

				Json rule_json = rules_json.addChild(NULL);
				rule_json.addChild("op_type", "AND");

				Json condition_type = json.getChild("condition_type");
				if (condition_type != NULL)
					rule_json.addChild("condition_type", condition_type.getString());
				Json attribute = json.getChild("attribute");
				if (attribute != NULL)
				{
					Json attribute_json = rule_json.addChild("attribute");
					Json name_attribute = attribute.getChild("name");
					if (name_attribute != NULL)
						attribute_json.addChild("name", name_attribute.getString());
					Json type_attribute = attribute.getChild("type");
					if (type_attribute != NULL)
						attribute_json.addChild("type", type_attribute.getString());
					Json value_attribute = attribute.getChild("value");
					if (value_attribute != NULL)
						attribute_json.addChild("value", value_attribute.getString());
				}
			}
		}
	};

	class Layer
	{
		Json json;
		string id;
		string proj;
		int type;
		int filters[0];
		int objects[0];

		Layer(Json doc)
		{
			json = doc;
			Json type_json = doc.getChild("type");
			if (type_json != NULL)
				type = int(type_json.getNumber());
			Json parameters = doc.getChild("parameters");
			if (parameters != NULL)
			{
				Json filters_json = parameters.getChild("filters");
				if (filters_json != NULL)
					for (int i = 0; i < filters_json.getNumChildren(); i++)
					{
						Json filter_json = filters_json.getChild(i);
						Filter filter = new Filter(filter_json);
						filters.append(filter);
					}
				Json objects_json = parameters.getChild("objects");
				if (objects_json != NULL)
					for (int i = 0; i < objects_json.getNumChildren(); i++)
					{
						Json object_json = objects_json.getChild(i);
						Object object = new Object(object_json);
						objects.append(object);
					}
			}
		}

		~Layer()
		{
			filters.delete();
			objects.delete();
		}

		void save()
		{
			if (strlen(id) != 0)
				json.addChild("id", id);
			// TMS
			if (type == 2)
			{
				Json parameters = json.getChild("parameters");
				if (parameters != NULL)
				{
					Json area_json = parameters.getChild("area");
					if (area_json != NULL)
						area_json.setName("polygon");
					Json polygon_projection = parameters.getChild("polygon_projection");
					if (polygon_projection != NULL)
						polygon_projection.setString(proj);
				}
			}
		}

		void removeFilters()
		{
			Json parameters = json.getChild("parameters");
			if (parameters != NULL)
				if (parameters.isChild("filters"))
					parameters.removeChild("filters");
		}

		void removeObjects()
		{
			Json parameters = json.getChild("parameters");
			if (parameters != NULL)
				if (parameters.isChild("objects"))
					parameters.removeChild("objects");
		}
	};

	class ObjectFilter
	{
		string layer_id;
		int filters_id[0];
	};

	class Slot
	{
		string id;
		string name;
		int filters[0];
		int objects_filters[];

		void save(Json doc)
		{
			doc.addChild("id", id);
			doc.addChild("name", name);

			if (filters.size())
			{
				Json filters_json = doc.addChild("filters");
				filters_json.setObject();
				for (int i = 0; i < filters.size(); i++)
				{
					Filter filter = filters[i];
					Json filter_json = filters_json.addChild(filter.id);
					filter.save(filter_json);
				}
			}
			if (objects_filters.size())
			{
				Json objects_filters_json = doc.addChild("objects_filters");
				objects_filters_json.setObject();
				forloop (int i = 0; objects_filters.size()) {
					ObjectFilter obj_filter = objects_filters.get(i);
					Json object_filter_json = objects_filters_json.addChild(objects_filters.key(i));
					object_filter_json.setArray();
					for (int j = 0; j < obj_filter.filters_id.size(); j++)
					{
						Json filter_json = object_filter_json.addChild(NULL);
						filter_json.setString(obj_filter.filters_id[j]);
					}
				}
			}
		}
	};

	class Source
	{
		Json json;
		int type;
		int layers[0];
		int slots[];
		string proj;

		Source(Json doc)
		{
			json = doc;
			Json type_json = doc.getChild("type");
			if (type_json != NULL)
				type = int(type_json.getNumber());
			Json layers_json = doc.getChild("layers");
			if (layers_json != NULL)
				for (int i = 0; i < layers_json.getNumChildren(); i++)
				{
					Json layer_json = layers_json.getChild(i);
					Layer layer = new Layer(layer_json);
					layers.append(layer);
				}
		}

		~Source()
		{
			layers.delete();
		}

		void save()
		{
			if (slots.size())
			{
				Json slots_json = json.addChild("slots");
				slots_json.setArray();
				forloop (int i = 0; slots.size())
				{
					Slot slot = slots.get(i);
					Json slot_json = slots_json.addChild("");
					slot.save(slot_json);
				}
			}
			foreach (Layer layer; layers)
			{
				layer.proj = proj;
				layer.save();
				layer.removeFilters();
				layer.removeObjects();
			}
		}
	};

	class ExportSceneParameters
	{
		Json parameters;

		ExportSceneParameters(Json doc)
		{
			parameters = doc;
		}

		int getParameter(string name)
		{
			for (int i = 0; i < parameters.getNumChildren(); i++)
			{
				Json parameter = parameters.getChild(i);
				if (parameter != NULL)
				{
					Json name_json = parameter.getChild("name");
					if (name_json != NULL)
						if (name_json.getString() == name)
						{
							int type = int(parameter.getChild("type").getNumber());
							switch (type)
							{
							case INT: return int(parameter.getChild("value").getNumber());
							default: return -1;
							}
						}
				}
			}
			return -1;
		}
	};

	class GenerationSceneParameters
	{
		Json parameters;

		GenerationSceneParameters(Json doc)
		{
			parameters = doc;
		}

		void addParameter(string name, int type, int value)
		{
			Json parameter_json = parameters.addChild("");
			parameter_json.addChild("name", name);
			parameter_json.addChild("type", int(type));

			switch (type)
			{
			case STRING: parameter_json.addChild("value", value); break;
			}
		}
	};

	class SceneParameters
	{
		Json json;
		ExportSceneParameters export_parameters;
		GenerationSceneParameters generation_parameters;

		SceneParameters(Json doc)
		{
			json = doc;
			Json export_parameters_json = doc.getChild("export_parameters");
			if (export_parameters_json != NULL)
				export_parameters = new ExportSceneParameters(export_parameters_json);
			Json generation_parameters_json = doc.getChild("generation_parameters");
			if (generation_parameters_json != NULL)
				generation_parameters = new GenerationSceneParameters(generation_parameters_json);
		}

		~SceneParameters()
		{
			delete export_parameters;
			delete generation_parameters;
		}
	};

	class Scene
	{
		SceneParameters parameters;
		int sources[0];
		int objects[0];
		Json json;

		Scene(Json file)
		{
			Json doc = new Json();
			if (!doc.load(file))
				return;
			restore(doc);
			json = doc;
		}

		~Scene()
		{
			sources.delete();
			delete parameters;
			delete json;
		}

		int save(string path)
		{
			Json objects_json = json.addChild("objects");
			objects_json.setArray();
			foreach (Object object; objects)
			{
				Json object_json = objects_json.addChild(NULL);
				object.save(object_json);
			}
			
			Json proj_json = parameters.json.getChild("projection");
			string proj = "";
			if (proj_json != NULL)
				proj = proj_json.getString();

			foreach (Source source; sources)
			{
				source.proj = proj;
				source.save();
			}
			return json.save(path);
		}

		int restore(Json doc)
		{
			sources.clear();
			Json scene_parameters = doc.getChild("parameters");
			if (scene_parameters != NULL)
				parameters = new SceneParameters(scene_parameters);
			Json sources_json = doc.getChild("sources");
			if (sources_json != NULL)
			{
				for (int i = 0; i < sources_json.getNumChildren(); i++)
				{
					Json source_json = sources_json.getChild(i);
					sources.append(new Source(source_json));
				}
			}

			return 1;
		}

		Source findSource(int type)
		{
			foreach (Source source; sources)
			{
				if (source.type == type)
					return source;
			}
			return NULL;
		}

		void process(Source source)
		{
			if (source == NULL)
				return;

			UGUID id = new UGUID();
			for (int i = 0; i < source.layers.size(); i++)
			{
				Layer layer = source.layers[i];
				id.generate();
				layer.id = id.getString();
				for (int j = 0; j < layer.objects.size(); j++)
				{
					Object object = layer.objects[j];
					string filter_hash = object.getFilterHash();
					if (source.slots.check(filter_hash))
					{
						Slot slot = source.slots[filter_hash];
						if (slot != NULL)
						{
							string filter_name = object.getFilterName();
							int contains = 0;
							foreach (Filter filter; slot.filters)
							{
								if (filter.name == filter_name)
								{
									contains = 1;
									object.slot_id = slot.id;
									if (!slot.objects_filters.check(layer.id))
									{
										ObjectFilter obj_filter = new ObjectFilter();
										obj_filter.layer_id = layer.id;
										obj_filter.filters_id.append(filter.id);
										slot.objects_filters[layer.id] = obj_filter;
									}
								}
							}
							if(contains == 0)
							{
								Slot slot = new Slot();

								id.generate();
								slot.id = id.getString();

								id.generate();
								slot.name = id.getString();

								string filter_name = object.getFilterName();
								object.slot_id = slot.id;
								foreach (Filter filter; layer.filters)
								{
									if (filter.name == filter_name)
									{
										id.generate();
										filter.id = id.getString();
										slot.filters.append(filter);
										if (slot.objects_filters.check(layer.id))
										{
											ObjectFilter obj_filter = slot.objects_filters[layer.id];
											obj_filter.filters_id.append(filter.id);
										} else
										{
											ObjectFilter obj_filter = new ObjectFilter();
											obj_filter.layer_id = layer.id;
											obj_filter.filters_id.append(filter.id);
											slot.objects_filters[layer.id] = obj_filter;
										}
									}
								}
								id.generate();
								source.slots.append(id.getString(), slot);
							}
						}
					}
					else
					{
						Slot slot = new Slot();

						id.generate();
						slot.id = id.getString();

						id.generate();
						slot.name = id.getString();

						string filter_name = object.getFilterName();
						object.slot_id = slot.id;
						foreach (Filter filter; layer.filters)
						{
							if (filter.name == filter_name)
							{
								id.generate();
								filter.id = id.getString();
								slot.filters.append(filter);
								if (slot.objects_filters.check(layer.id))
								{
									ObjectFilter obj_filter = slot.objects_filters[layer.id];
									obj_filter.filters_id.append(filter.id);
								} else
								{
									ObjectFilter obj_filter = new ObjectFilter();
									obj_filter.layer_id = layer.id;
									obj_filter.filters_id.append(filter.id);
									slot.objects_filters[layer.id] = obj_filter;
								}
							}
						}
						source.slots.append(filter_hash, slot);
					}
					objects.append(object);
				}
			}
		}
	};

	void processPath(string data_path) {
		string files[0] = ();
		findFilesByExt(files, data_path, ".sworm");
		foreach (string file; files)
			if (!skipFile(data_path, file))
				processFile(file);
	}

	void processFile(string file) {

		Log::info("upgrading \"%s\"", file);

		Scene scene = new Scene(file);
		Process::sandworm(scene);
		if (!scene.save(file))
			Log::error("failed to save \"%s\"", file);
		delete scene;
	}

} /* namespace Sandworm */

#endif /* __MIGRATION_SANDWORM_H__ */
