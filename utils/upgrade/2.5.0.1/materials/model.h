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

#ifndef __MIGRATION_MATERIALS_MODEL_H__
#define __MIGRATION_MATERIALS_MODEL_H__

#include <utils.h>

/**************************************************************************\
*
* Material libraries
*
\**************************************************************************/

class Blend {
	
	Xml element;
	
	Blend(Xml xml) {
		element = xml;
	}
	
	string getSrc() {
		return element.getArg("src");
	}
	
	void setSrc(string src) {
		element.setArg("src",src);
	}
	
	string getDest() {
		return element.getArg("dest");
	}
	
	void setDest(string dest) {
		element.setArg("dest",dest);
	}
};

/*
 */
class MaterialSetting {
	
	Xml element;
	
	MaterialSetting(Xml xml) {
		element = xml;
	}
	
	string getName() {
		return element.getArg("name");
	}
	
	void set_name(string name) {
		element.setArg("name",name);
	}
	
	string getValue() {
		return element.getData();
	}
	
	void setValue(string value) {
		element.setData(value);
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
		return (element.isArg("format") ? element.getArg("format") : "");
	}
	
	void removeFormat() {
		element.removeArg("format");
	}
	
	string getShader() {
		return (element.isArg("shader") ? element.getArg("shader") : "");
	}
	
	void setShader(string value) {
		element.setArg("shader",value);
	}
	
}; /* class Texture */

/*
 */
class Parameter : MaterialSetting {
	
	Parameter(Xml xml) : MaterialSetting(xml) {
	}
	
	//
	string getFormat() {
		return (element.isArg("format") ? element.getArg("format") : "");
	}
	
	void removeFormat() {
		element.removeArg("format");
	}
	
	//
	void getFlags(string flags[]) {
		
		flags.clear();
		
		if(!element.isArg("flags")) return;
		
		strsplit(element.getArg("flags"),",",flags);
		
		forloop(int i = 0; i < flags.size(); i++) {
			flags[i] = trim(flags[i]);
			if(flags[i] == "") {
				flags.remove(i);
				i--;
			}
		}
	}
	
	void setFlags(string flags[]) {
		element.setArg("flags",strjoin(flags,","));
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
		} else {
			return false;
		}
	}
	
}; /* class Parameter */

/*
 */
class Material {
	
	Xml element;
	Xml options_element;
	Blend blend; 
	State states[];
	Texture textures[];
	Parameter parameters[];
	
	Material(Xml xml) {
		
		element = xml;
		
		options_element = element.find("options");
		
		Xml blend_element = element.find("blend");
		if(blend_element != NULL) {
			blend = new Blend(blend_element);
		}
		
		forloop(int i = 0; element.getNumChildren()) {
			
			Xml child = element.getChild(i);
			
			if(child.getName() == "state" && child.isArg("name")) {
				State state = new State(child);
				states.append(state.getName(),state);
			} else if(child.getName() == "texture" && child.isArg("name")) {
				Texture texture = new Texture(child);
				textures.append(texture.getName(),texture);
			} else if(child.getName() == "parameter" && child.isArg("name")) {
				Parameter parameter = new Parameter(child);
				parameters.append(parameter.getName(),parameter);
			}
		}
	}
	
	~Material() {
		delete blend;
		states.delete();
		textures.delete();
		parameters.delete();
	}
	
	int isEmpty() {
		return (element.getNumChildren() == 0 && element.getNumArgs() == 0);
	}
	
	string getName() {
		return (element.isArg("name") ? element.getArg("name") : "");
	}
	
	string getParent() {
		return (element.isArg("parent") ? element.getArg("parent") : "");
	}
	
	string setParent(string name) {
		element.setArg("parent",name);
	}
	
	int isHidden() {
		return (element.isArg("hidden") && element.getArg("hidden") == "1");
	}
	
	//
	int removeBlend() {
		
		if(blend != NULL) {
			delete element.removeChild(blend.element);
			delete blend;
			return true;
		} else {
			return false;
		}
	}
	
	//
	void addBlend() {
		
		if(blend != NULL) return;
		
		Xml blend_element = element.addChild("blend");
		
		blend = new Blend(blend_element);
	}
	
	//
	string hasOption(string name) {
		return (options_element != NULL && options_element.isArg(name));
	}
	
	string getOption(string name) {
		return (hasOption(name) ? options_element.getArg(name) : "");
	}
	
	void setOption(string name,string value) {
		
		if(options_element == NULL) {
			options_element = element.addChild("options");
		}
		
		options_element.setArg(name,value);
	}
	
	int removeOption(string name) {
		
		if(options_element == NULL || !options_element.isArg(name)) {
			return false;
		}
		
		options_element.removeArg(name);
		if(options_element.getNumArgs() == 0) {
			delete element.removeChild(options_element);
		}
		
		return true;
	}
	
	//
	int removeState(string name) {
		
		State state = states.check(name,NULL);
		
		if(state != NULL) {
			states.remove(name);
			delete element.removeChild(state.element);
			delete state;
			return true;
		} else {
			return false;
		}
	}
	
	State addState(string name,string value = "") {
		
		if(states.check(name)) {
			return states[name];
		}
		
		Xml state_element = element.addChild("state");
		
		State state = new State(state_element);
		state.set_name(name);
		state.setValue(value);
		
		states.append(name,state);
		
		return state;
	}
	
	int hasState(string name) {
		return states.check(name);
	}
	
	string getStateValue(string name,string default = "") {
		State state = states.check(name,NULL);
		return (state != NULL ? state.getValue() : default);
	}
	
	void setStateValue(string name,string value) {
		
		State state = states.check(name,NULL);
		
		if(state != NULL) {
			state.setValue(value);
		} else {
			addState(name,value);
		}
	}
	
	void renameState(string from,string to) {
		State state = states.check(from,NULL);
		if(state != NULL) {
			state.set_name(to);
			states.remove(from);
			states.append(to,state);
		}
	}
	
	//
	int removeTexture(string name) {
		
		Texture texture = textures.check(name,NULL);
		
		if(texture != NULL) {
			textures.remove(name);
			delete element.removeChild(texture.element);
			delete texture;
			return true;
		} else {
			return false;
		}
	}
	
	Texture addTexture(string name,string value = "") {
		
		if(textures.check(name)) {
			return textures[name];
		}
		
		Xml texture_element = element.addChild("texture");
		
		Texture texture = new Texture(texture_element);
		texture.set_name(name);
		texture.setValue(value);
		
		textures.append(name,texture);
		
		return texture;
	}
	
	int hasTexture(string name) {
		return textures.check(name);
	}
	
	void renameTexture(string from,string to) {
		Texture texture = textures.check(from,NULL);
		if(texture != NULL) {
			texture.set_name(to);
			textures.remove(from);
			textures.append(to,texture);
		}
	}
	
	string getTextureValue(string name) {
		Texture texture = textures.check(name,NULL);
		return (texture != NULL ? texture.getValue() : "");
	}
	
	void setTextureValue(string name,string value) {
		
		Texture texture = textures.check(name,NULL);
		
		if(texture != NULL) {
			texture.setValue(value);
		} else {
			addTexture(name,value);
		}
	}
	
	//
	int removeParameter(string name) {
		
		Parameter parameter = parameters.check(name,NULL);
		
		if(parameter != NULL) {
			parameters.remove(name);
			delete element.removeChild(parameter.element);
			delete parameter;
			return true;
		} else {
			return false;
		}
	}
	
	Parameter addParameter(string name,string value = "") {
		
		if(parameters.check(name)) {
			return parameters[name];
		}
		
		Xml parameter_element = element.addChild("parameter");
		
		Parameter parameter = new Parameter(parameter_element);
		parameter.set_name(name);
		parameter.setValue(value);
		
		parameters.append(name,parameter);
		
		return parameter;
	}
	
	int hasParameter(string name) {
		return parameters.check(name);
	}
	
	string getParameterValue(string name,string default = "") {
		Parameter parameter = parameters.check(name,NULL);
		return (parameter != NULL ? parameter.getValue() : default);
	}
	
	void setParameterValue(string name,string value) {
		
		Parameter parameter = parameters.check(name,NULL);
		if(parameter != NULL) {
			parameter.setValue(value);
		} else {
			addParameter(name,value);
		}
	}
	
	void renameParameter(string from,string to) {
		Parameter parameter = parameters.check(from,NULL);
		if(parameter != NULL) {
			parameter.set_name(to);
			parameters.remove(from);
			parameters.append(to,parameter);
		}
	}
	
}; /* class Material */

/*
 */
class Library {
	
	string path;
	Xml xml;
	Material materials[];
	
	Library(string path_,Xml xml_) {
		path = path_;
		xml = xml_;
	}
	
	~Library() {
		materials.delete();
		delete xml;
	}
	
	Library load(string file) {
		
		Xml xml = new Xml();
		if(!xml.load(file)) {
			delete xml;
			return NULL;
		}
		
		Library lib = new Library(file,xml);
		
		forloop(int i = 0; xml.getNumChildren()) {
			Material material = new Material(xml.getChild(i));
			lib.materials.append(material.getName(),material);
		}
		
		return lib;
	}
	
	int save() {
		return xml.save(path);
	}
	
	//
	int isEditable() {
		return (!xml.isArg("editable") || xml.getArg("editable") != "0");
	}
	
	string getVersion() {
		return (xml.isArg("version") ? xml.getArg("version") : "");
	}
	
	void setVersion(string version) {
		xml.setArg("version",version);
	}
	
	//
	int remove(string name) {
		
		Material material = materials.check(name,NULL);
		
		if(material == NULL) return false;
		
		materials.remove(name);
		delete xml.removeChild(material.element);
		delete material;
	}
	
}; /* class Library */

/**************************************************************************\
*
* Nodes
*
\**************************************************************************/

int last_override_id = 0;

/*
 */
class OverrideMaterialProxy : Material {
	
	Override override;
	int id;
	
	OverrideMaterialProxy(Override override_,Xml xml) : Material(xml) {
		override = override_;
		id = last_override_id++;
	}
	
	string getParent() {
		return override.getMaterialName();
	}
	
	void setParent(string parent) {
		override.setMaterialName(parent);
	}
	
	void getName() {
		// we want unique name for every anonymous material
		return format("*override %s %d*",override.getName(),id);
	}
};

/*
 */
class Override {
	
	Xml material_element;
	Xml element;
	OverrideMaterialProxy material;
	int is_surface;
	
	Override(Xml xml) {
		
		element = xml;
		
		is_surface = (element.getName() == "surface");
		
		if(is_surface) {
			material_element = element.find("material");
		} else {
			material_element = element;
		}
		
		material = new OverrideMaterialProxy(this,material_element);
	}
	
	~Override() {
		delete material;
	}
	
	string getName() {
		return element.getArg("name");
	}
	
	string getMaterialName() {
		if(is_surface) {
			return (element.isArg("material") ? element.getArg("material") : "");
		} else {
			return (material_element.isArg("name") ? material_element.getArg("name") : "");
		}
	}
	
	void setMaterialName(string name) {
		if(is_surface) {
			element.setArg("material",name);
		} else {
			material_element.setArg("name",name);
		}
	}
	
	void removeMaterialData() {
		
		if(material != NULL) {
			delete element.removeChild(material.element);
			delete material;
		}
	}
	
}; /* class Override */

/*
 */
class NodeFile {
	
	string path;
	Xml xml;
	Override overrides[0];
	
	NodeFile(string path_,Xml xml_) {
		path = path_;
		xml = xml_;
	}
	
	~NodeFile() {
		overrides.delete();
		delete xml;
	}
	
	//
	void find_surfaces() {
		
		//
		void _visit_element(Xml element) {
			
			if(element.getName() == "surface") {
				if(element.isChild("material")) {
					overrides.append(new Override(element));
				}
				return; // there is not point to descend into the surface element
			}
			
			if(element.getName() == "node") {
				Xml material_element = element.find("material");
				if(material_element != NULL && material_element.isArg("name")) {
					overrides.append(new Override(material_element));
				}
			}
			
			forloop(int i = 0; element.getNumChildren()) {
				_visit_element(element.getChild(i));
			}
		}
		
		//
		_visit_element(xml);
	}
	
	string getVersion() {
		return (xml.isArg("version") ? xml.getArg("version") : "");
	}
	
	//
	NodeFile load(string file) {
		
		Xml xml = new Xml();
		if(!xml.load(file)) {
			delete xml;
			return NULL;
		}
		
		NodeFile node_file = new NodeFile(file,xml);
		node_file.find_surfaces();
		
		return node_file;
	}
	
	int save() {
		return xml.save(path);
	}
	
}; /* class NodeFile */

#endif
