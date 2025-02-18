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

#ifndef __MATERIAL_GRAPH_H__
#define __MATERIAL_GRAPH_H__

class MaterialGraphParameter
{
	Json json;

	MaterialGraphParameter(Json json_in)
	{
		json = json_in;
	}

	string getType() { return jsonGetString(json, "type"); }
	void setType(string v) { jsonSetString(json, "type", v); }

	string getGuid() { return jsonGetString(json, "guid"); }
	void setGuid(string v) { jsonSetString(json, "guid", v); }
};


class MaterialGraphInput
{
	Json json;

	MaterialGraphInput(Json json_in)
	{
		json = json_in;
	}

	string getLabel() { return jsonGetString(json, "label"); }
	void setLabel(string v) { jsonSetString(json, "label", v); }

	string getType() { return jsonGetString(json, "type"); }
	void setType(string v) { jsonSetString(json, "type", v); }

	int getID() { return jsonGetInt(json, "id"); }
	void setID(int v) { jsonSetInt(json, "id", v); }
};
class MaterialGraphOutput
{
	Json json;

	MaterialGraphOutput(Json json_in)
	{
		json = json_in;
	}

	string getLabel() { return jsonGetString(json, "label"); }
	void setLabel(string v) { jsonSetString(json, "label", v); }

	string getType() { return jsonGetString(json, "type"); }
	void setType(string v) { jsonSetString(json, "type", v); }

	int getID() { return jsonGetInt(json, "id"); }
	void setID(int v) { jsonSetInt(json, "id", v); }
};
class MaterialGraphNode
{
	Json json;

	MaterialGraphInput inputs[0];
	MaterialGraphOutput outputs[0];

	MaterialGraphNode(Json json_in)
	{
		json = json_in;

		{
			Json j = json.getChild("inputs");
			if(j != NULL)
			{
				for (int i = 0; i < j.getNumChildren(); i++)
				{
					Json child = j.getChild(i);
					inputs.append(new MaterialGraphInput(child));
				}
			}
		}

		{
			Json j =json.getChild("outputs");
			if(j != NULL)
			{
				for (int i = 0; i < j.getNumChildren(); i++)
				{
					Json child = j.getChild(i);
					outputs.append(new MaterialGraphOutput(child));
				}
			}
		}
	}

	string getName() { return json.getName(); }
	void setName(string v) { json.setName(v); }

	void addWarning(string str)
	{
		str = jsonGetString(json, "warning") + str;
		jsonSetString(json, "warning", str);
	}

	string getGuid() { return jsonGetString(json, "guid"); }
	void setGuid(string v) { jsonSetString(json, "guid", v); }

	int getX() { return jsonGetInt(json, "x"); }
	void setX(int v) { jsonSetInt(json, "x", v); }

	int getY() { return jsonGetInt(json, "y"); }
	void setY(int v) { jsonSetInt(json, "y", v); }
};


class MaterialGraphAnchor
{
	Json json;

	MaterialGraphAnchor(Json json_in)
	{
		json = json_in;
	}


	string getInputNodeGUID() { return jsonGetString(json, "input_node"); }
	void setInputNodeGUID(string v) { jsonSetString(json, "input_node", v); }

	int getInputIndex() { return jsonGetInt(json, "input_index"); }
	void setInputIndex(int v) { jsonSetInt(json, "input_index", v); }

	int getInputID() { return jsonGetInt(json, "input_id"); }
	void setInputID(int v) { jsonSetInt(json, "input_id", v); }


	string getOutputNodeGUID() { return jsonGetString(json, "output_node"); }
	void setOutputNodeGUID(string v) { jsonSetString(json, "output_node", v); }

	int getOutputIndex() { return jsonGetInt(json, "output_index"); }
	void setOutputIndex(int v) { jsonSetInt(json, "output_index", v); }

	int getOutputID() { return jsonGetInt(json, "output_id"); }
	void setOutputID(int v) { jsonSetInt(json, "output_id", v); }
};


class MaterialGraph
{
	Json json;
	Json material_json;
	Json parameters_json;
	Json nodes_json;
	Json anchors_json;

	MaterialGraphParameter parameters[0];
	MaterialGraphNode nodes[0];
	MaterialGraphAnchor anchors[0];

	string path;

	MaterialGraph(string path_in, Json json_in)
	{
		json = json_in;
		path = path_in;

		material_json = json.getChild("material");
		parameters_json = json.getChild("parameters");
		nodes_json = json.getChild("nodes");
		anchors_json = json.getChild("anchors");

		if (parameters_json != NULL)
		{
			for (int i = 0; i < parameters_json.getNumChildren(); i++)
			{
				Json child = parameters_json.getChild(i);
				parameters.append(new MaterialGraphParameter(child));
			}
		}
		if (nodes_json != NULL)
		{
			for (int i = 0; i < nodes_json.getNumChildren(); i++)
			{
				Json child = nodes_json.getChild(i);
				nodes.append(new MaterialGraphNode(child));
			}
		}
		if (anchors_json != NULL)
		{
			for (int i = 0; i < anchors_json.getNumChildren(); i++)
			{
				Json child = anchors_json.getChild(i);
				anchors.append(new MaterialGraphAnchor(child));
			}
		}
	}

	int save()
	{
		return json.save(path);
	}

	MaterialGraphNode findNodeByGUID(string guid)
	{
		foreach(MaterialGraphNode node; nodes)
		{
			if (node.getGuid() == guid)
				return node;
		}

		return NULL;
	}

	string getVersion() { return jsonGetString(json, "version"); }
	void setVersion(string v) { jsonSetString(json, "version", v); }
};

namespace MaterialGraphs
{
	string data_path;
	string remove_files[0];

	MaterialGraph graphs[0];

	void processPath(string paths)
	{
		data_path = paths;

		{
			string files[0] = ();
			findFilesByExt(files, data_path, ".mgraph|.msubgraph");

			foreach(string file; files)
			{
				if(skipFile(data_path, file))
					continue;

				Json json = new Json();
				if(!json.load(file))
				{
					delete json;
					continue;
				}

				graphs.append(new MaterialGraph(file, json));
			}
		}

		Log::info("update material graphs ...");
		foreach(MaterialGraph g; graphs)
			Process::materialGraph(g);

		foreach(MaterialGraph g; graphs)
		{
			g.setVersion(ENGINE_VERSION);

			string dir_mat = dirname(g.path);
			if(!is_dir(dir_mat))
				mkdir(dir_mat);

			if(!g.save())
				Log::error("failed to save \"%s\"", g.path);
		}

		foreach(string file; remove_files)
			remove_file(file);

		cleanup();
	}

	void cleanup()
	{
		graphs.delete();
	}

}





#endif /* __MATERIAL_GRAPH_H__ */
