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

#ifndef __MIGRATION_PROPERTY_H__
#define __MIGRATION_PROPERTY_H__

namespace Properties {
	
/*
 */
class Parameter {
	
	Xml xml;
	
	Parameter(Xml xml_in) {
		xml = xml_in;
	}
	
	string getName() {
		return xml.getArg("name");
	}
	
	void setName(string name) {
		xml.setArg("name", name);
	}
	
	string getValue() {
		return xml.getData();
	}
	
	void setValue(string value) {
		xml.setData(value);
	}
	
	string getType() {
		return xml.getArg("type", "int");
	}
	
	//
	string getFormat() {
		return xml.isArg("format") ? xml.getArg("format") : "";
	}
	
	void removeFormat() {
		xml.removeArg("format");
	}
	
	//
	void getFlags(string flags[]) {
		
		flags.clear();
		
		if(!xml.isArg("flags")) return;
		
		strsplit(xml.getArg("flags"), ", ", flags);
		
		forloop(int i = 0; i < flags.size(); i++) {
			flags[i] = trim(flags[i]);
			if(flags[i] == "") {
				flags.remove(i);
				i--;
			}
		}
	}
	
	void setFlags(string flags[]) {
		xml.setArg("flags", strjoin(flags, ", "));
	}
	
	int hasFlag(string flag) {
		
		string flags[0] = ();
		getFlags(flags);
		
		return (flags.find(flag) != -1);
	}
	
	int removeFlag(string flag) {
		
		string flags[0] = ();
		getFlags(flags);
		
		int index = flags.find(flag);
		
		if(index != -1) {
			flags.remove(index);
			setFlags(flags);
			return true;
		}
		return false;
	}
	
}; /* class Parameter */

/*
 */
class Property {
	
	string path;
	string path2 = "";
	Xml xml;
	Parameter parameters[];
	
	// relationship
	Property parent = NULL;
	Property children[0];
	
	Property(string path_in, Xml xml_in) {
		path = path_in;
		xml = xml_in;
		
		forloop(int i = 0; xml.getNumChildren()) {
			Xml child = xml.getChild(i);
			
			////////////////////////////////////////////////////////////////////////////////////////////
			// property parameters migration
			////////////////////////////////////////////////////////////////////////////////////////////
			
			// convert <string> + flags = "file" to <file>
			if(child.isArg("type") && child.getArg("type") == "string" &&
				child.isArg("flags") && child.getArg("flags") == "file") {
				
				child.setArg("type", "file");
				child.removeArg("flags");
				
				// convert path to guid if it possible
				string path = child.getData();
				if(strlen(path) > 1) {
					UGUID guid = FileSystem::getFastGUID(path);
					if(guid == NULL)
						guid = FileSystem::getGUID(path, false);
					
					if(guid != NULL && !guid.isEmpty())
						child.setData(guid.getFileSystemString());
				}
			}
			
			// convert <asset> to <file>
			if(child.isArg("type") && child.getArg("type") == "asset") {
				child.setArg("type", "file");
				
				string old_guid = child.getData();
				if(strlen(old_guid) > 0) {
					string new_guid = "guid://" + old_guid;
					child.setData(new_guid);
				}
			}
			
			////////////////////////////////////////////////////////////////////////////////////////////
			
			if(child.getName() == "parameter" && child.isArg("name")) {
				Parameter parameter = new Parameter(child);
				parameters.append(parameter.getName(), parameter);
			}
		}
	}
	
	~Property() {
		parameters.delete();
	}
	
	Property load(string file) {
		Xml xml = new Xml();
		if(!xml.load(file)) {
			delete xml;
			return NULL;
		}
		return new Property(file, xml);
	}
	
	int save() {
		int result = 0;
		if(path != "")
			result |= xml.save(path);
		if(path2 != "")
			result |= xml.save(path2);
		return result;
	}

	string getPath() {
		return path;
	}
	
	void setPath(string path_in) {
		path = path_in;
	}
	
	int isEditable() {
		return !xml.isArg("editable") || xml.getArg("editable") != "0";
	}
	
	int isHidden() {
		return xml.isArg("hidden") && xml.getArg("hidden") == "1";
	}
	
	int isManual() {
		return xml.isArg("manual") && xml.getArg("manual") == "1";
	}
	
	void setManual(int manual)
	{
		if(!manual && xml.isArg("manual"))
		{
			xml.removeArg("manual");
			if(xml.isArg("parent_name"))
			{
				xml.setArg("parent", xml.getArg("parent_name"));
				xml.removeArg("parent_name");
			}
		}
		
		if(manual)
		{
			xml.setArg("manual", "1");
			if(xml.isArg("parent"))
			{
				xml.setArg("parent_name", xml.getArg("parent"));
				xml.removeArg("parent");
			}
		}
	}
	
	void setManualAllParents(int manual)
	{
		setManual(manual);
		if(parent != NULL)
			parent.setManualAllParents(manual);
	}

	string getVersion() {
		return xml.isArg("version") ? xml.getArg("version") : "";
	}
	
	void setVersion(string version) {
		xml.setArg("version", version);
	}
	
	int isEmpty() {
		return xml.getNumChildren() == 0 && xml.getNumArgs() == 0;
	}
	
	string getName() {
		return xml.isArg("name") ? xml.getArg("name") : "";
	}
	
	void setName(string name) {
		return xml.setArg("name", name);
	}
	
	string getGUID() {
		
		// return
		if(xml.isArg("guid"))
			return xml.getArg("guid");
		
		// manual? create it by name
		if(isManual())
			return stringToGUID(getName());
		
		return "";
	}
	
	string setGUID(string guid) {
		return xml.setArg("guid", guid);
	}
	
	// xml relationships
	
	string getParentGUID() {
		
		// return
		if(xml.isArg("parent"))
			return xml.getArg("parent");
		
		// manual? create it by name
		if(isManual() && xml.isArg("parent_name"))
			return stringToGUID(getParentName());
		
		return "";
	}
	
	string getParentName() {
		return xml.isArg("parent_name") ? xml.getArg("parent_name") : "";
	}
	
	int isBaseProperty() {
		return !xml.isArg("parent") && !xml.isArg("parent_name");
	}
	
	string setParentGUID(string guid) {
		if(xml.isArg("parent_name"))
			xml.removeArg("parent_name");
		xml.setArg("parent", guid);
	}
	
	void setParentName(string name) {
		if(xml.isArg("parent"))
			xml.removeArg("parent");
		xml.setArg("parent_name", name);
	}
	
	// class relationships
	
	void addChild(Property prop) {
		//if(children.check(prop.getName()))
		//	return;
		children.append(prop);
	}
	
	void removeChild(Property prop) {
		//if(!children.check(prop.getName()))
		//	return;
		children.remove(prop);
	}
	
	int getNumChildren() {
		return children.size();
	}
	
	void setParent(Property prop) {
		if(parent != NULL)
			parent.removeChild(this);
		parent = prop;
		if(parent != NULL)
			parent.addChild(this);
	}
	
	Property getParent() {
		return parent;
	}
	
	/////////////////////////////////////////
	
	int removeParameter(string name) {
		
		Parameter parameter = parameters.check(name, NULL);
		
		if(parameter != NULL) {
			parameters.remove(name);
			delete xml.removeChild(parameter.xml);
			delete parameter;
			return true;
		}
		return false;
	}
	
	Parameter addParameter(string name, string value = "") {
		
		if(parameters.check(name))
			return parameters[name];
		
		Xml parameter_xml = xml.addChild("parameter");
		
		Parameter parameter = new Parameter(parameter_xml);
		parameter.setName(name);
		parameter.setValue(value);
		
		parameters.append(name, parameter);
		
		return parameter;
	}
	
	int hasParameter(string name) {
		return parameters.check(name);
	}
	
	int hasParameterInParent(string name, int root) {
		// find in current
		if(hasParameter(name) && !root)
			return 1;
		
		// find in parent
		if(parent != NULL)
			return parent.hasParameterInParent(name, 0);
		
		return 0;
	}
	
	int hasUniqueParameters() {
		int has_unique = 0;
		foreach(Parameter param; parameters) {
			if(!hasParameterInParent(param.getName(), 1))
				has_unique = 1;
		}
		return has_unique;
	}
	
	string getRecursiveParameterValue(string name, string default = "") {
		Parameter parameter = parameters.check(name, NULL);
		if(parameter != NULL)
			return parameter.getValue();
		
		if(parent != NULL)
			return parent.getRecursiveParameterValue(name, default);
		return default;
	}
	
	string getParameterValue(string name, string default = "") {
		Parameter parameter = parameters.check(name, NULL);
		return parameter != NULL ? parameter.getValue() : default;
	}
	
	void setParameterValue(string name, string value) {
		
		Parameter parameter = parameters.check(name, NULL);
		if(parameter != NULL)
			parameter.setValue(value);
		else
			addParameter(name, value);
	}
	
	void renameParameter(string from, string to) {
		Parameter parameter = parameters.check(from, NULL);
		if(parameter != NULL) {
			parameter.setName(to);
			parameters.remove(from);
			parameters.append(to, parameter);
		}
	}
	
	string getParameterType(string name, int root = 1) {
		// find in current
		Parameter parameter = parameters.check(name, NULL);
		if(parameter != NULL && !root)
			return parameter.getType();
		
		// find in parent
		if(parent != NULL)
			return parent.getParameterType(name, 0);
		
		return "";
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////
	// property parameters migration
	////////////////////////////////////////////////////////////////////////////////////////////
	
	void migrateProperty() {
		foreach(Parameter p; parameters) {
			
			// change path to guid of inherited parameters
			if(getParameterType(p.getName()) == "file") {
				
				string path = p.getValue();
				if(strlen(path) > 1) {
					UGUID guid = FileSystem::getFastGUID(path);
					if(guid == NULL)
						guid = FileSystem::getGUID(path, false);
					
					if(guid != NULL && !guid.isEmpty())
						p.setValue(guid.getFileSystemString());
				}
			}
		}
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////
	
}; /* class Property */

} /* namespace Properties */

#endif /* __MIGRATION_PROPERTY_H__ */
