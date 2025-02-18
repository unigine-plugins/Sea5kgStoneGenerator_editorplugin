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


#ifndef __MIGRATION_UMOUNT_H__
#define __MIGRATION_UMOUNT_H__

namespace Umount
{
	void processPath(string data_path)
	{
		string files[0] = ();
		findFilesByExt(files, data_path, ".umount");
		foreach(string file; files)
		{
			if(!skipFile(data_path, file))
				processFile(pathname(data_path), pathname(file) + basename(file));
		}
	}

	string convertPath(string path)
	{
		if(strlen(path) == 0)
			return path;

		if(!endsWith(path, "/*"))
		{
			if(path[strlen(path) - 1] != '/')
				path += "/*";
			else
				path += "*";
		}

		return path;
	}

	void processFile(string data_path, string file)
	{
		Json json = new Json();

		if(!json.load(file))
		{
			Log::error("failed to load \"%s\"", file);
			delete json;
			return;
		}

		Log::info("upgrading \"%s\"", file);

		Json version_json = json.find("version");
		if(version_json != NULL)
			json.removeChild(version_json);

		Json json_filteres = json.find("ignore_filters");

		if(json_filteres == NULL || !json_filteres.isArray())
		{
			json.save(file);
			return;
		}

		int num = json_filteres.getNumChildren();

		Json remove_childs[0] = ();

		// convert the path. added "/*" to the end of the path
		for(int i = 0; i < num; i++)
		{
			Json child = json_filteres.getChild(i);
			if(!child.isString())
				continue;

			string data = child.getString();
			if(startsWith(data, ".thumbnails"))
			{
				remove_childs.append(child);
				continue;
			}
			child.setString(convertPath(data));
		}

		// remove ".thumbnails" paths
		foreach(Json child; remove_childs)
			json_filteres.removeChild(child);

		json.save(file);
		delete json;
	}

} /* namespace Umount */

#endif /* __MIGRATION_UMOUNT_H__ */
