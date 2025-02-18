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

#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__
namespace FileSystem {
	
	#define FILESYSTEM_GUIDS_DB_MAGIC 0x5dfc55fb
	
	string data_path;
	
	class FileSystemPath {
		string path;
		string compare_path;
		UGUID guid;
		
		void setPath(FileSystemPath p) {
			path = p.path;
			compare_path = p.compare_path;
		}
		
		FileSystemPath(string path_in) {
			path = replace(path_in, "\\", "/");
			path = relname(FileSystem::data_path, path);
			compare_path = lower(path);
			guid = new UGUID();
			guid.generate();
		}
		
		FileSystemPath(string path_in, UGUID guid_in) {
			path = replace(path_in, "\\", "/");
			path = relname(FileSystem::data_path, path);
			compare_path = lower(path);
			guid = guid_in;
		}
		
		int operator==(FileSystemPath p0, FileSystemPath p1) {
			return p0.compare_path == p1.compare_path;
		}
		
		int operator<(FileSystemPath p0, FileSystemPath p1) {
			
			string s0 = p0.compare_path;
			string s1 = p1.compare_path;
			
			string l0 = strlen(s0);
			string l1 = strlen(s1);
			
			int size = -min(l0, l1);
			for(int i = 0; i > size; i--) {
				int c0 = s0[l0 + i - 1];
				int c1 = s1[l1 + i - 1];
				if(c0 != c1)
					return c0 < c1;
			}
			
			int c0 = (size > -l0) ? s0[l0 + size - 1] : '\0';
			int c1 = (size > -l1) ? s1[l1 + size - 1] : '\0';
			return c0 < c1;
		}
		
		int operator>(FileSystemPath p0, FileSystemPath p1) {
			if(p0 == p1)
				return 0;
			if(p0 < p1)
				return 0;
			return 1;
		}
		
		int isEqualPath(FileSystemPath fs_path) {
			string k0 = compare_path;
			string k1 = fs_path.compare_path;
			
			string l0 = strlen(k0);
			string l1 = strlen(k1);
			
			int size = -min(l0, l1);
			
			for(int i = 0; i > size; i--) {
				int c0 = k0[l0 + i - 1];
				int c1 = k1[l1 + i - 1];
				if(c0 != c1)
					return 0;
			}
			
			int c0 = (size > -l0) ? k0[l0 + size - 1] : '\0';
			int c1 = (size > -l1) ? k1[l1 + size - 1] : '\0';
			
			if(c0 == '\0' && c1 == '\0')
				return 1;
			if(c0 == '/' || c1 == '/')
				return 1;
			return 0;
		}
	};
	
	
	FileSystemPath paths[0];
	UGUID pathes_fast[];
	
	string getLocalPath(string path) {
		path = replace(path, "\\", "/");
		return relname(data_path, path);
	}
	
	string getAbsPath(string path) {
		path = getLocalPath(path);
		return absname(data_path, path);
	}
	
	void sortPathes() {
		paths.sort();
		pathes_fast.clear();
		for(int i = 0; i < paths.size(); i++) {
			FileSystemPath fs_path = paths[i];
			pathes_fast.append(fs_path.compare_path, fs_path.guid);
		}
		
	}
	
	int isKnownFile(string path) {
		return paths.find(new FileSystemPath(path)) != -1;
	}
	
	void addKnownFile(string path, UGUID guid) {
		FileSystemPath fs_path = new FileSystemPath(path, guid);
		int id = paths.find(fs_path);
		if(id == -1)
			paths.append(fs_path);
	}
	
	void addKnownFile(string path) {
		UGUID guid = new UGUID();
		guid.generate();
		addKnownFile(path, guid);
	}
	
	void setGUID(string path, UGUID guid) {
		FileSystemPath fs_path = new FileSystemPath(path, guid);
		
		int id = paths.find(fs_path);
		if(id != -1)
			paths[id] = fs_path;
		else
			paths.append(fs_path);
	}
	
	UGUID getFastGUID(string path) {
		
		string compare_path = replace(path, "\\", "/");
		compare_path = relname(FileSystem::data_path, compare_path);
		compare_path = lower(compare_path);
		
		if(pathes_fast.check(compare_path))
			return pathes_fast[compare_path];
		
		return NULL;
	}
	
	UGUID getGUID(string path, int strict = true) {
		
		if(!strict) {
			if(strchr(path, '.') == -1 || extension(path) == "")
				return NULL;
			
			int is_path = false;
			for(int i = 0; i < strlen(path) && !is_path; i++) {
				int c = path[i];
				is_path = (c < '0' || c > '9') && c != '.';
			}
			if(!is_path)
				return NULL;
		}
		
		FileSystemPath fs_path = new FileSystemPath(path);
		
		int id = paths.find(fs_path);
		if(id != -1)
			return paths[id].guid;
		
		if(strict)
			return NULL;
		
		for(int i = 0; i < paths.size(); i++) {
			FileSystemPath fs_path_i = paths[i];
			if(fs_path_i.isEqualPath(fs_path))
				return fs_path_i.guid;
		}
		
		return NULL;
	}
	
	UGUID getStringGUID(string path) {
		return getGUID(path).getString();
	}
	
	void remove(string path) {
		FileSystemPath fs_path = new FileSystemPath(path);
		int id = paths.find(fs_path);
		if(id != -1)
			paths.remove(id);
	}
	
	void renameKnownFile(string path, string new_path) {
		FileSystemPath fs_path = new FileSystemPath(path);
		FileSystemPath fs_path_new = new FileSystemPath(new_path);
		
		if(fs_path == fs_path_new)
			return;
		
		int id = paths.find(fs_path_new);
		if(id != -1)
			paths.remove(id);
		
		id = paths.find(fs_path);
		if(id != -1)
			paths[id].setPath(fs_path_new);
		else {
			paths.append(fs_path_new);
		}
	}
	
	void save() {
		Json json = new Json();
		
		for(int i = 0; i < paths.size(); i++) {
			FileSystemPath fs_path = paths.get(i);
			string path = fs_path.path;
			if(strrstr(path, ".runtimes/") != -1)
				continue;
			
			UGUID guid = fs_path.guid;
			if(guid == NULL || guid.isEmpty()) {
				Log::error("Invalid guid %s", path);
				continue;
			}
			
			json.addChild(guid.getString(), path);
		}
		
		json.save(data_path + "/guids.db");
	}
	
	void load(string path) {
		
		data_path = path;
		string file_name = data_path + "/guids.db";

		if (is_file(file_name))
		{
			Json json = new Json();
			if(!json.load(file_name))
				Log::error("FileSystem::load(): failed to load \"%s\"", file_name);
			else {
				for(int i = 0; i < json.getNumChildren(); i++) {

					Json child = json.getChild(i);
					if(!child.isString())
						continue;

					string guid_str = child.getName();
					string path_str = child.getString();

					UGUID guid = new UGUID();
					guid.setString(guid_str);
					addKnownFile(path_str, guid);
				}
			}

			delete json;
		}

		{
			string files[0] = ();
			findFiles(files, data_path);
			foreach(string file; files)
				if(!skipFile(data_path, file))
					addKnownFile(file);
		}
		
		// load assets guid
		log.message("Load assets guid\n");
		{
			string path = pathname(replace(__FILE__, "\\", "/")) + "assets.xml";
			Xml xml = new Xml();
			if(xml.load(path)) {
				forloop(int i = 0; xml.getNumChildren()) {
					Xml xml_asset = xml.getChild(i);
					path = xml_asset.getArg("path");
					Xml runtime_xml = xml_asset.find("runtimes").getChild(0);
					UGUID guid = new UGUID();
					guid.setString(runtime_xml.getArg("id"));
					setGUID(path, guid);
				}
			}
			delete xml;
		}
	}
	
	int loadBin(string path) {
		
		data_path = path;
		string file_name = data_path + "/guids.db";
		
		File file = new File();
		if(!file.open(file_name, "rb")) {
			return 1;
		}
		
		// read header
		long magic = file.readLong();
		if(magic != FILESYSTEM_GUIDS_DB_MAGIC) {
			Log::error("FileSystem::loadGuids(): error reading file \"%s\", wrong magic\n", file_name);
			file.close();
			return 0;
		}
		
		int version = file.readUChar();
		if(version < 1) {
			Log::error("FileSystem::loadGuids(): error reading file \"%s\", version mismatch\n", file_name);
			file.close();
			return 0;
		}
		
		long guids_num = file.readLong();
		if(file.isError()) {
			Log::error("FileSystem:loadGuids(): error reading file \"%s\", invalid GUID count\n", file_name);
			file.close();
			return 0;
		}
		
		// read guids
		for(int i = 0; i < guids_num; i++) {
			int guid_size = file.readUInt();
			int path_size = file.readUInt();
			
			int guids_buf[guid_size];
			int paths_buf[path_size];
			
			file.read(guids_buf, guid_size);
			file.read(paths_buf, path_size);
			
			guids_buf.append(0);
			paths_buf.append(0);
			
			string guid_str = unicodeToUtf8(guids_buf);
			string path_str = unicodeToUtf8(paths_buf);
			
			UGUID guid = new UGUID();
			guid.setString(guid_str);
			addKnownFile(path_str, guid);
			
			if(file.isError()) {
				Log::error("FileSystem:load_guids(): error reading file \"%s\", can't read GUID\n", file_name);
				file.close();
				return 0;
			}
		}
		
		file.close();
		return 1;
	}
	
}
#endif /* __FILE_SYSTEM_H__ */
