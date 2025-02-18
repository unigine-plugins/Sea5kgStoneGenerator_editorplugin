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

#ifndef __MIGRATION_MATERIALS_H__
#define __MIGRATION_MATERIALS_H__

namespace Materials {
	
	string data_paths[0];
	string remove_files[0];
	
	Material materials[0];
	
	void processPaths(string paths[]) {
		
		data_paths.copy(paths);
		
		foreach(string data_path; data_paths) {
			string files[0] = ();
			if(!findFilesByExt(files,data_path,".mat"))
				continue;
			
			foreach(string file; files) {
				if(skipFile(data_path,file))
					continue;
				
				Xml xml = new Xml();
				if(!xml.load(file)) {
					delete xml;
					continue;
				}
				
				Material mat = new Material(file, xml);
				if(mat.isBaseMaterial())
					continue;
				if(mat.isManualMaterial())
					continue;
				materials.append(mat);
			}
		}
		
		Log::info("update materials ...");
		foreach(Material m; materials) {
			Process::material(m);
		}
		
		foreach(Material m; materials) {
			
			m.setVersion(ENGINE_VERSION);
			
			add_dir(m.getPath());
			if(!m.save())
				Log::error("failed to save \"%s\"", m.path);
		}
		
		foreach(string file; remove_files)
			remove_file(file);
		
		cleanup();
	}
	
	void cleanup() {
		materials.delete();
	}

} /* namespace Materials */

#endif /* __MIGRATION_MATERIALS_H__ */
