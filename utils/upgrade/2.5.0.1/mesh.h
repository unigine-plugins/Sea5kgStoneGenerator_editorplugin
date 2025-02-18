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

#ifndef __MIGRATION_MESH_H__
#define __MIGRATION_MESH_H__

/*
 */
namespace Mesh {
	
	/*
	 */
	int MESH_MAGIC = 'm' | ('s' << 8) | ('1' << 16) | ('1' << 24);
	int ANIM_MAGIC = 'a' | ('n' << 8) | ('1' << 16) | ('0' << 24);
	
	/*
	 */
	void processPath(string path) {
		
		string files[0] = ();
		if(!findFilesByExt(files,path,".mesh|.anim|.smesh|.sanim")) {
			// error is already logged
			return;
		}
		
		foreach(string file; files) {
			if(skipFile(path,file)) continue;
			process_file(file);
		}
	}
	
	/*
	 */
	void process_file(string file) {
		
		int magic = getMagic(file);
		
		if(magic == 0) {
			return;
		}
		
		if(magic == MESH_MAGIC || magic == ANIM_MAGIC) {
			return;
		}
		
		Log::info("upgrading \"%s\"",file);
		
		Mesh mesh = new Mesh();
		
		if(!mesh.load(file)) {
			Log::error("failed to load \"%s\"",file);
			delete mesh;
			return;
		}
		
		forloop(int i = 0; mesh.getNumAnimations()) {
			string n = basename(file);
			n = replace(n,".mesh","");
			n = replace(n,".anim","");
			mesh.setAnimationName(i,n);
		}
		
		// create tangent space
		forloop(int i = 0; mesh.getNumSurfaces()) {
			forloop(int j = 0; mesh.getNumSurfaceTargets(i)) {
				if(mesh.getNumTangents(i,j) == 0) mesh.createTangents(i,j);
			}
		}
		
		string ext = lower(getExtension(file));
		
		string new_name;
		
		if(ext == ".smesh") {
			new_name = getUniqueFileName(setExtension(file,".mesh"));
		} else if(ext == ".sanim") {
			new_name = getUniqueFileName(setExtension(file,".anim"));
		} else {
			new_name = file;
		}
		
		if(!mesh.save(new_name)) {
			Log::error("failed to edit file \"%s\"",new_name);
			delete mesh;
			return;
		}
		
		if(file != new_name) {
			Log::info("\"%s\" is renamed to \"%s\"",file,new_name);
			renamed_files.append(file,new_name);
			remove(file);
		}
		
		delete mesh;
	}
	
} /* namespace Mesh */

#endif /* __MIGRATION_MESH_H__ */
