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
		xml.setArg("name",name);
	}
	
	string getValue() {
		return xml.getData();
	}
	
	void setValue(string value) {
		xml.setData(value);
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
		
		strsplit(xml.getArg("flags"),",",flags);
		
		forloop(int i = 0; i < flags.size(); i++) {
			flags[i] = trim(flags[i]);
			if(flags[i] == "") {
				flags.remove(i);
				i--;
			}
		}
	}
	
	void setFlags(string flags[]) {
		xml.setArg("flags",strjoin(flags,","));
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
	
	string lib;
	string path;
	string path2 = "";
	Xml xml;
	Parameter parameters[];
	
	// relationship
	Property parent = NULL;
	Property children[0];
	
	Property(string path_in,Xml xml_in) {
		lib = "";
		path = path_in;
		xml = xml_in;
		
		forloop(int i = 0; xml.getNumChildren()) {
			Xml child = xml.getChild(i);
			
			// rename "state" to "parameter"
			if(child.getName() == "state" && child.isArg("name")) {
				child.setName("parameter");
				if(!child.isArg("type"))
					child.setArg("type", "toggle");
			}
			
			// convert "options" to "parameter"-s
			if(child.getName() == "options") {
				if(child.isArg("intersection")) {
					Xml new_param = xml.addChild("parameter");
					new_param.setName("parameter");
					new_param.setArg("name", "intersection");
					new_param.setData(child.getArg("intersection"));
				}
				
				if(child.isArg("collision")) {
					Xml new_param = xml.addChild("parameter");
					new_param.setName("parameter");
					new_param.setArg("name", "collision");
					new_param.setData(child.getArg("collision"));
				}
				
				xml.removeChild(child);
				i--;
				continue;
			}
			
			if(child.getName() == "parameter" && child.isArg("name")) {
				Parameter parameter = new Parameter(child);
				parameters.append(parameter.getName(),parameter);
			}
			
			// check forbidden argument names
			if(child.isArg("name")) {
				string param_name = child.getArg("name");
				if(param_name == "guid") Log::error("Property \"%s\": please change the argument name \"guid\" to something else. The given name is reserved", getName());
				if(param_name == "parent_name") Log::error("Property \"%s\": please change the argument name \"parent_name\" to something else. The given name is reserved", getName());
				if(param_name == "manual") Log::error("Property \"%s\": please change the argument name \"manual\" to something else. The given name is reserved", getName());
				if(param_name == "title") Log::error("Property \"%s\": please change the argument name \"title\" to something else. The given name is reserved", getName());
				if(param_name == "tooltip") Log::error("Property \"%s\": please change the argument name \"tooltip\" to something else. The given name is reserved", getName());
				if(param_name == "group") Log::error("Property \"%s\": please change the argument name \"group\" to something else. The given name is reserved", getName());
				if(param_name == "filter") Log::error("Property \"%s\": please change the argument name \"filter\" to something else. The given name is reserved", getName());
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
		return new Property(file,xml);
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
	
	void setManual(int manual) {
		if(!manual && xml.isArg("manual")) {
			xml.removeArg("manual");
			if(xml.isArg("parent_name")) {
				xml.setArg("parent", xml.getArg("parent_name"));
				xml.removeArg("parent_name");
			}
		}
		
		if(manual) {
			xml.setArg("manual", "1");
			if(xml.isArg("parent")) {
				xml.setArg("parent_name", xml.getArg("parent"));
				xml.removeArg("parent");
			}
		}
	}
	
	void setManualAllParents(int manual) {
		setManual(manual);
		if(parent != NULL)
			parent.setManualAllParents(manual);
	}
	
	string getVersion() {
		return xml.isArg("version") ? xml.getArg("version") : "";
	}
	
	void setVersion(string version) {
		xml.setArg("version",version);
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
		return xml.isArg("guid") ? xml.getArg("guid") : "";
	}
	
	string setGUID(string guid) {
		return xml.setArg("guid", guid);
	}
	
	// xml relationships
	
	string getParentGUID() {
		return xml.isArg("parent") ? xml.getArg("parent") : "";
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
		xml.setArg("parent",guid);
	}
	
	void setParentName(string name) {
		if(xml.isArg("parent"))
			xml.removeArg("parent");
		xml.setArg("parent_name",name);
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
		
		Parameter parameter = parameters.check(name,NULL);
		
		if(parameter != NULL) {
			parameters.remove(name);
			delete xml.removeChild(parameter.xml);
			delete parameter;
			return true;
		}
		return false;
	}
	
	Parameter addParameter(string name,string value = "") {
		
		if(parameters.check(name))
			return parameters[name];
		
		Xml parameter_xml = xml.addChild("parameter");
		
		Parameter parameter = new Parameter(parameter_xml);
		parameter.setName(name);
		parameter.setValue(value);
		
		parameters.append(name,parameter);
		
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
	
	string getParameterValue(string name,string default = "") {
		Parameter parameter = parameters.check(name,NULL);
		return parameter != NULL ? parameter.getValue() : default;
	}
	
	void setParameterValue(string name,string value) {
		
		Parameter parameter = parameters.check(name,NULL);
		if(parameter != NULL)
			parameter.setValue(value);
		else
			addParameter(name,value);
	}
	
	void renameParameter(string from,string to) {
		Parameter parameter = parameters.check(from,NULL);
		if(parameter != NULL) {
			parameter.setName(to);
			parameters.remove(from);
			parameters.append(to,parameter);
		}
	}
	
	
}; /* class Property */

} /* namespace Properties */

#endif /* __MIGRATION_PROPERTY_H__ */
