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

#ifndef __MIGRATION_ASSET_H__
#define __MIGRATION_ASSET_H__

enum {
	LINK_SOURCE,
	LINK_PRIMARY,
	LINK_AUXILIARY
};

class AssetRuntime {
	
	Asset asset;
	Xml xml;
	
	AssetRuntime(Asset asset_in, Xml xml_in) {
		asset = asset_in;
		xml = xml_in;
	}
	
	string getName() {
		return xml.getArg("name");
	}
	void setName(string name) {
		xml.setArg("name", basename(name));
	}
	
	int getLink() {
		return xml.getIntArg("link");
	}
	void setLink(int link) {
		
		if(link == LINK_SOURCE)
			asset.setGUID(getGUID());
		
		xml.setArg("link", link);
	}
	
	string getGUID() {
		return xml.getArg("id");
	}
	void setGUID(string guid) {
		xml.setArg("id", guid);
	}
	
	string getFile() {
		return dirname(asset.getPath()) + getName();
	}
	
};

class Asset {
	
	string path;
	Xml xml;
	Xml parameters_xml;
	
	Xml runtimes_xml;
	AssetRuntime runtimes[0];
	
	Asset(string path_in, Xml xml_in) {
		path = path_in;
		xml = xml_in;
		parameters_xml = xml.find("parameters");
		runtimes_xml = xml.find("runtimes");
		
		if(parameters_xml == NULL)
			parameters_xml = xml.addChild("parameters");
		if(runtimes_xml == NULL)
			runtimes_xml = xml.addChild("parameters");
		
		forloop(int i = 0; runtimes_xml.getNumChildren()) {
			Xml x = runtimes_xml.getChild(i);
			AssetRuntime runtime = new AssetRuntime(this, x);
			runtimes.append(runtime);
		}
	}
	
	~Asset() {
		runtimes.delete();
	}
	
	void clearRuntimes() {
		runtimes_xml.clearChildren();
		runtimes.clear();
	}
	
	Asset load(string file) {
		Xml xml = new Xml();
		if(!xml.load(file)) {
			delete xml;
			return NULL;
		}
		return new Asset(file, xml);
	}
	
	Asset create(string file, string type) {
		
		Xml xml = new Xml();
		xml.setName("asset");
		xml.setArg("version", ENGINE_VERSION);
		
		UGUID guid = new UGUID();
		guid.clear();
		guid.generate();
		xmlSetChildValue(xml, "guid", guid.getString());
		xmlSetChildValue(xml, "type", type);
		xmlSetChildValue(xml, "hash", "");
		xml.addChild("parameters");
		xml.addChild("runtimes");
		
		return new Asset(file, xml);
	}
	
	string getPath() {
		return path;
	}
	
	void setPath(string path_in) {
		path = path_in;
	}
	
	string getType() {
		return xml.getChildData("type", "");
	}
	
	void setType(string type) {
		xmlSetChildValue(xml, "type", type);
	}
	
	string getGUID() {
		return xml.getChildData("guid", "");
	}
	
	void setGUID(string guid) {
		xmlSetChildValue(xml, "guid", guid);
	}
	
	string getXml() {
		return xml;
	}
	
	int save() {
		
		xml.setArg("version", ENGINE_VERSION);
		if(path == "")
			return 1;
		
		if(parameters_xml != NULL && parameters_xml.getNumChildren() == 0)
			delete xml.removeChild(parameters_xml);
		if(runtimes_xml != NULL && runtimes_xml.getNumChildren() == 0)
			delete xml.removeChild(runtimes_xml);
		
		Log::info("Asset::save \"%s\"", path);
		if(xml.save(path))
			return 1;
		
		parameters_xml = xml.find("parameters");
		runtimes_xml = xml.find("runtimes");
		if(parameters_xml == NULL)
			parameters_xml = xml.addChild("parameters");
		if(runtimes_xml == NULL)
			runtimes_xml = xml.addChild("parameters");
		
		Log::error("Asset::save failed to save \"%s\"", path);
		return 0;
	}
	
	void addRuntime(string file, int link) {
		FileSystem::addKnownFile(file);
		
		Xml x = runtimes_xml.addChild("runtime");
		AssetRuntime runtime = new AssetRuntime(this, x);
		runtimes.append(runtime);
		
		string guid = FileSystem::getStringGUID(file);
		
		runtime.setGUID(guid);
		runtime.setName(file);
		runtime.setLink(link);
	}
	
	void addParameter(string type, string name, int data) {
		Xml x = parameters_xml.addChild("parameter");
		x.setArg("type", type);
		x.setArg("name", name);
		x.setData(data);
	}
	
}; /* class Asset */

#endif /* __MIGRATION_ASSET_H__ */
