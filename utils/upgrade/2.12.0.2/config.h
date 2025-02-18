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

#ifndef __MIGRATION_CONFIG_H__
#define __MIGRATION_CONFIG_H__

/*
 */
namespace Config {
	
	void processPath(string data_path) {
		string files[0] = ();
		findFilesByExt(files, data_path, ".cfg");
		foreach(string file; files)
			if(!skipFile(data_path, file))
				processFile(file);
	}
	
	void processFile(string file) {
		
		string name = basename(file);
		
		Xml xml = new Xml();
		if(!xml.load(file)) {
			if (name == "app_projection.cfg")
				Process::projectionBinary(file);
			else if (name == "syncker.cfg")
				Process::synckerBinary(file);
			else {
				Log::error("failed to load \"%s\"", file);
			}
			delete xml;
			return;
		}
		
		Log::info("upgrading \"%s\"", file);
		
		xml.setArg("version", ENGINE_VERSION);
		
		if (name == "app_projection.cfg")
			Process::projection(xml);
		else if (name == "syncker.cfg")
			Process::syncker(xml);
		else
			Process::config(xml);
		
		if(name == "app_projection.cfg" || name == "syncker.cfg")
			xml.save(file);
		else
			remove_file(file);
		
		delete xml;
	}
	
} /* namespace Config */

#endif /* __MIGRATION_CONFIG_H__ */
