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

#ifndef __MIGRATION_UTILS_H__
#define __MIGRATION_UTILS_H__

/**************************************************************************\
*
* String utils
*
\**************************************************************************/

int versionLessOrEqual(string left_version, string right_version)
{
	if (left_version == right_version)
		return 1;
	
	int _arrayLexicographicalLess(int left[], int right[])
	{
		for (int i = 0; i < left.size(); i++)
		{
			if (left[i] != right[i])
				return left[i] < right[i];
		}
		return 0;
	}
	int left[4];
	sscanf(left_version, "%d.%d.%d.%d", left);
	int right[4];
	sscanf(right_version, "%d.%d.%d.%d", right);
	return _arrayLexicographicalLess(left, right);
}

string rtrim(string str, string symbols) {
	
	if(strlen(str) == 0 || strlen(str) == 1) return str;
	
	string res = str;
	while(strlen(res) > 1 && strlen(res) >= strlen(symbols)) {
		if(substr(res, strlen(res) - strlen(symbols), strlen(symbols)) == symbols) {
			res = substr(res, 0, strlen(res) - strlen(symbols));
		} else break;
	}
	
	return res;
}

string strjoin(string parts[], string delimiter) {
	
	string result = "";
	
	forloop(int i = 0; parts.size()) {
		result += parts[parts.key(i)];
		if(i < parts.size() - 1) result += delimiter;
	}
	
	return result;
}

string startsWith(string str, string prefix) {
	return (substr(str, 0, strlen(prefix)) == prefix);
}

string endsWith(string str, string suffix) {
	return (substr(str, strlen(str) - strlen(suffix)) == suffix);
}

string capitalize(string str) {
	
	if(str == "") return str;
	
	return upper(substr(str, 0, 1)) + substr(str, 1);
}

string isAlpha(int c) {
	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

string isNum(int c) {
	return (c >= '0' && c <= '9');
}

string isAlphaNum(int c) {
	return (isAlpha(c) || isNum(c));
}

string stringToGUID(string str) {
	UGUID guid = new UGUID();
	guid.clear();
	guid.generate(str);
	return guid.getString();
}

string getRandomGUID() {
	UGUID guid = new UGUID();
	guid.clear();
	guid.generate();
	return guid.getString();
}

/**************************************************************************\
*
* File system utils
*
\**************************************************************************/

string getDirPath(string path) {
	
	if(strlen(path) > 0 && path[strlen(path) - 1] != '/')
		path += "/";
	
	return path;
}

string getAbsPath(string path) {
	if(is_absolute(path)) return path;
	return currdir() + "/" + path;
}

string getExtension(string path) {
	
	string file = basename(path);
	
	if(file == "." || file == "..") return "";
	
	if(extension(file) != "")								// "foo.bar"
		return "." + extension(file);
	else if(strlen(file) && file[strlen(file) - 1] == '.')	// "foo.""
		return ".";
	else													// "foo"
		return "";
}

string withoutExtension(string path) {
	string ext = getExtension(path);
	return substr(path, 0, strlen(path) - strlen(ext));
}

string setExtension(string path, string ext) {
	return withoutExtension(path) + ext;
}

int pathExtensionCompare(string path, string ext) {
	return extensionCompare(getExtension(path), ext);
}

int extensionCompare(string path, string ext) {
	return lower(path) == lower(ext);
}

string findFile(string path, string name) {
	
	if(name == "") return "";
	
	if(!is_dir(path)) {
		Log::error("directory \"%s\" doesn't exist", path);
		return "";
	}
	
	Dir dir = new Dir(path);
	if(!dir.isOpened()) {
		Log::error("failed to open directory \"%s\"", path);
		delete dir;
		return "";
	}
	
	forloop(int i = 0; dir.getNumFiles()) {
		string f = dir.getFileName(i);
		if(endsWith(f, name)) {
			dir.close();
			delete dir;
			return f;
		}
	}
	
	forloop(int i = 0; dir.getNumDirs()) {
		
		string d = dir.getDirName(i);
		if(startsWith(d, ".")) continue;
		
		string f = findFile(d, name);
		if(f != "") {
			dir.close();
			delete dir;
			return f;
		}
	}
	
	dir.close();
	delete dir;
	return "";
}

int getFiles(string files[], string path, int predicate = 0) {
	
	if(predicate == 0) predicate = [](string _) { return true; };
	
	files.clear();
	
	if(!is_dir(path)) {
		Log::error("directory \"%s\" doesn't exist", path);
		return false;
	}
	
	Dir dir = new Dir(path);
	if(!dir.isOpened()) {
		Log::error("failed to open directory \"%s\"", path);
		delete dir;
		return false;
	}
	
	forloop(int i = 0; dir.getNumFiles()) {
		
		string f = dir.getFileName(i);
		
		if(!startsWith(basename(f), ".") && call(predicate, f)) {
			files.append(f);
		}
	}
	
	dir.close();
	delete dir;
	return true;
}

int matchExtension(string ext, string pattern) {
	
	while(true) {
		int to = strchr(pattern, '|');
		string guess = substr(pattern, 0, to);
		if(ext == guess) return true;
		if(to == -1) return false;
		pattern = substr(pattern, to + 1);
	}
}

int getFilesWithExt(string files[], string path, string pattern) {
	return getFiles(files, path, [](string f) { return matchExtension(getExtension(f), pattern); });
}

int findFiles(string files[], string path, int predicate = 0) {
	
	//
	int _walk_directory(string files[], string path, int predicate) {
	
		if(!is_dir(path)) {
			Log::error("directory \"%s\" doesn't exist", path);
			return false;
		}
		
		Dir dir = new Dir(path);
		if(!dir.isOpened()) {
			Log::error("failed to open directory \"%s\"", path);
			delete dir;
			return false;
		}
		
		forloop(int i = 0; dir.getNumFiles()) {
			
			string f = dir.getFileName(i);
			
			if(!startsWith(basename(f), ".") && call(predicate, f)) {
				files.append(f);
			}
		}
		
		forloop(int i = 0; dir.getNumDirs()) {
			
			string d = dir.getDirName(i);
			
			if(startsWith(basename(d), ".")) continue;
			
			if(!_walk_directory(files, d, predicate)) {
				dir.close();
				delete dir;
				return false;
			}
		}
		
		dir.close();
		delete dir;
		return true;
	}
	
	//
	files.clear();
	
	if(predicate == 0) predicate = [](string _) { return true; };
	
	return _walk_directory(files, path, predicate);
}

int findFilesByExt(string files[], string path, string pattern) {
	return findFiles(files, path, [](string f) { return matchExtension(getExtension(f), pattern); });
}

string getUniqueFileName(string base, string sep = ".") {
	
	string name = base;
	int num = 1;
	
	while(is_file(name) || is_dir(name)) {
		name = format("%s%s%d%s", withoutExtension(base), sep, num, getExtension(base));
		num++;
	}
	
	return name;
}

void remove_file(string file) {
	remove(file);
	Log::info(" Remove %s", file);
}

/**************************************************************************\
*
* Misc utils
*
\**************************************************************************/

int getMagic(string file_name) {
	
	int magic;
	
	File file = new File();
	
	if(file.open(file_name, "rb")) {
		magic = file.readInt();
		file.close();
	} else {
		magic = 0;
		Log::error("failed to open file \"%s\"", file_name);
	}
	
	delete file;
	return magic;
}


/**************************************************************************\
*
* Xml utils
*
\**************************************************************************/

void xmlDeleteChild(Xml xml, string name) {
	if(xml.isChild(name))
		delete xml.removeChild(name);
}

void xmlUpdateChildValue(Xml xml, string name, string value) {
	int num = xml.findChild(name);
	if(num != -1)
		xml.getChild(num).setData(value);
}

void xmlSetChildValue(Xml xml, string name, string value) {
	
	int num = xml.findChild(name);
	if(num != -1)
		xml.getChild(num).setData(value);
	else
		xml.setChildData(name, value);
}

void xmlRenameChild(Xml xml, string from, string to) {
	int num = xml.findChild(from);
	if(num != -1)
		xml.getChild(num).setName(to);
}

void xmlRemoveArg(Xml xml, string arg) {
	if(xml.isArg(arg))
		xml.removeArg(arg);
}

void xmlMergeChildren(Xml xml_src, Xml xml_dest) {
	for(int i = 0; i < xml_src.getNumChildren(); i++) {
		Xml x = xml_src.getChild(i);
		if (xml_dest.findChild(x.getName()) == -1)
			xml_dest.addChild(x.getName()).copy(x);
	}
}

Xml xmlGetChild(Xml xml, string name) {
	int num = xml.findChild(name);
	return num == -1 ? NULL : xml.getChild(num);
}

string xmlGetArg(Xml xml, string name, string default_value = "") {
	int num = xml.findArg(name);
	return num == -1 ? default_value : xml.getArgValue(num);
}

void xmlSetArg(Xml xml, string name, string value) {
	int num = xml.findArg(name);
	if(num != -1)
		xml.setArgValue(num, value);
}

#endif /* __MIGRATION_UTILS_H__ */
