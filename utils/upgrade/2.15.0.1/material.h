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

#ifndef __MIGRATION_MATERIAL_H__
#define __MIGRATION_MATERIAL_H__

/*
 */
class Blend {
	
	Xml xml;
	
	Blend(Xml xml_in) {
		xml = xml_in;
	}
	
	string getSrc() {
		return xml.getArg("src");
	}
	
	void setSrc(string src) {
		xml.setArg("src", src);
	}
	
	string getDest() {
		return xml.getArg("dest");
	}
	
	void setDest(string dest) {
		xml.setArg("dest", dest);
	}
};

/*
 */
class MaterialSetting {
	
	Xml xml;
	
	MaterialSetting(Xml xml_in) {
		xml = xml_in;
	}
	
	string getName() {
		return xml.getArg("name");
	}
	
	void set_name(string name) {
		xml.setArg("name", name);
	}
	
	string getValue() {
		return xml.getData();
	}
	
	void setValue(string value) {
		xml.setData(value);
	}
	
}; /* class MaterialSetting */

/*
 */
class State : MaterialSetting {
	State(Xml xml) : MaterialSetting(xml) {
	}
}; /* class State */

/*
 */
class Texture : MaterialSetting {
	
	Texture(Xml xml) : MaterialSetting(xml) {
	}
	
	//
	string getFormat() {
		return xml.isArg("format") ? xml.getArg("format") : "";
	}
	
	void removeFormat() {
		xml.removeArg("format");
	}
	
	string getShader() {
		return xml.isArg("shader") ? xml.getArg("shader") : "";
	}
	
	void setShader(string value) {
		xml.setArg("shader", value);
	}
	
}; /* class Texture */

/*
 */
class Parameter : MaterialSetting {
	
	Parameter(Xml xml) : MaterialSetting(xml) {
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
class Material {
	
	string path;
	Xml xml;
	Xml options_xml;
	Blend blend; 
	State states[];
	Texture textures[];
	Parameter parameters[];
	
	Material(string path_in, Xml xml_in) {
		path = path_in;
		xml = xml_in;
		
		options_xml = xml.find("options");
		
		Xml blend_xml = xml.find("blend");
		if(blend_xml != NULL)
			blend = new Blend(blend_xml);
		
		void parser(Xml xml) {
			forloop(int i = 0; xml.getNumChildren()) {
				
				Xml child = xml.getChild(i);
				
				if(child.getName() == "state" && child.isArg("name")) {
					State state = new State(child);
					states.append(state.getName(), state);
				} else if(child.getName() == "texture" && child.isArg("name")) {
					Texture texture = new Texture(child);
					textures.append(texture.getName(), texture);
				} else if(child.getName() == "parameter" && child.isArg("name")) {
					Parameter parameter = new Parameter(child);
					parameters.append(parameter.getName(), parameter);
				} else
					parser(child);
			}
		}
		
		parser(xml);
	}
	
	~Material() {
		delete blend;
		states.delete();
		textures.delete();
		parameters.delete();
	}
	
	
	Material load(string file) {
		
		Xml xml = new Xml();
		if(!xml.load(file)) {
			delete xml;
			return NULL;
		}
		return new Material(file, xml);
	}
	
	string getPath() {
		return path;
	}
	
	void setPath(string path_in) {
		path = path_in;
	}
	
	int save() {
		if(path != "")
			return xml.save(path);
		return 1;
	}
	
	int isEditable() {
		return !xml.isArg("editable") || xml.getArg("editable") != "0";
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
		return xml.isArg("guid") ? xml.getArg("guid") : "";
	}
	
	string setGUID(string guid) {
		return xml.setArg("guid", guid);
	}
	
	string getParentGUID() {
		return xml.isArg("parent") ? xml.getArg("parent") : "";
	}
	
	string getParentName() {
		return xml.isArg("parent_name") ? xml.getArg("parent_name") : "";
	}
	
	int isBaseMaterial() {
		return xml.getName() == "base_material";
	}
	
	int isBrushMaterial() {
		return xml.getName() == "brush_material";
	}
	
	int isManualMaterial() {
		return xml.isArg("manual") && xml.getArg("manual") == "1";
	}
	
	string setParentGUID(string guid) {
		xml.setArg("parent", guid);
	}
	
	string getBaseMaterial() {
		return xml.isArg("base_material") ? xml.getArg("base_material") : "";
	}
	
	string setBaseMaterial(string name) {
		xml.setArg("base_material", name);
	}
	
	int isHidden() {
		return xml.isArg("hidden") && xml.getArg("hidden") == "1";
	}
	
	//
	int removeBlend() {
		
		if(blend != NULL) {
			delete xml.removeChild(blend.xml);
			delete blend;
			return true;
		}
		return false;
	}
	
	//
	void addBlend() {
		if(blend == NULL)
			blend = new Blend(xml.addChild("blend"));
	}
	
	//
	string hasOption(string name) {
		return options_xml != NULL && options_xml.isArg(name);
	}
	
	string getOption(string name) {
		return hasOption(name) ? options_xml.getArg(name) : "";
	}
	
	void setOption(string name, string value) {
		if(options_xml == NULL)
			options_xml = xml.addChild("options");
		options_xml.setArg(name, value);
	}
	
	int removeOption(string name) {
		
		if(options_xml == NULL || !options_xml.isArg(name))
			return false;
		
		options_xml.removeArg(name);
		if(options_xml.getNumArgs() == 0)
			delete xml.removeChild(options_xml);
		
		return true;
	}
	
	void renameOption(string from, string to) {
		if(options_xml != NULL)
			xmlRenameArg(options_xml, from, to);
	}
	
	//
	int removeState(string name) {
		
		State state = states.check(name, NULL);
		if(state != NULL) {
			states.remove(name);
			delete xml.removeChild(state.xml);
			delete state;
			return true;
		}
		return false;
	}
	
	State addState(string name, string value = "") {
		
		if(states.check(name))
			return states[name];
		
		Xml state_xml = xml.addChild("state");
		
		State state = new State(state_xml);
		state.set_name(name);
		state.setValue(value);
		
		states.append(name, state);
		
		return state;
	}
	
	int hasState(string name) {
		return states.check(name);
	}
	
	string getStateValue(string name, string default = "") {
		State state = states.check(name, NULL);
		return state != NULL ? state.getValue() : default;
	}
	
	void setStateValue(string name, string value) {
		
		State state = states.check(name, NULL);
		if(state != NULL)
			state.setValue(value);
		else
			addState(name, value);
	}
	
	void renameState(string from, string to) {
		State state = states.check(from, NULL);
		if(state != NULL) {
			state.set_name(to);
			states.remove(from);
			states.append(to, state);
		}
	}
	
	//
	int removeTexture(string name) {
		
		Texture texture = textures.check(name, NULL);
		
		if(texture != NULL) {
			textures.remove(name);
			delete xml.removeChild(texture.xml);
			delete texture;
			return true;
		}
		return false;
	}
	
	Texture addTexture(string name, string value = "") {
		
		if(textures.check(name)) {
			return textures[name];
		}
		
		Xml texture_xml = xml.addChild("texture");
		
		Texture texture = new Texture(texture_xml);
		texture.set_name(name);
		texture.setValue(value);
		
		textures.append(name, texture);
		
		return texture;
	}
	
	int hasTexture(string name) {
		return textures.check(name);
	}
	
	void renameTexture(string from, string to) {
		Texture texture = textures.check(from, NULL);
		if(texture != NULL) {
			texture.set_name(to);
			textures.remove(from);
			textures.append(to, texture);
		}
	}
	
	string getTextureValue(string name) {
		Texture texture = textures.check(name, NULL);
		return texture != NULL ? texture.getValue() : "";
	}
	
	void setTextureValue(string name, string value) {
		
		Texture texture = textures.check(name, NULL);
		
		if(texture != NULL)
			texture.setValue(value);
		else
			addTexture(name, value);
	}
	
	//
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
		parameter.set_name(name);
		parameter.setValue(value);
		
		parameters.append(name, parameter);
		
		return parameter;
	}
	
	int hasParameter(string name) {
		return parameters.check(name);
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
			parameter.set_name(to);
			parameters.remove(from);
			parameters.append(to, parameter);
		}
	}
	
}; /* class Material */

#endif /* __MIGRATION_MATERIAL_H__ */
