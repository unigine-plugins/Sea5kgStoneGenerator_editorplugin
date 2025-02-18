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

#ifndef __MIGRATION_PATH_H__
#define __MIGRATION_PATH_H__

/*
 */
namespace Path {
	
	/*
	 */
	int PATH_MAGIC = 'p' | ('t' << 8) | ('0' << 16) | ('4' << 24);
	int SPLINE_MAGIC = 's' | ('p' << 8) | ('0' << 16) | ('2' << 24);
	
	/*
	 */
	void processFile(string file) {
		
		int magic = getMagic(file);
		
		if(magic == 0) {
			return;
		}
		
		if(magic == PATH_MAGIC) {
			return;
		}
		
		Log::info("upgrading \"%s\"",file);
		
		if(magic != SPLINE_MAGIC) {
			Log::error("can't upgrade \"%s\" - unknown format",file);
			return;
		}
		
		File source = new File();
		if(!source.open(file,"rb")) {
			Log::error("failed to open file \"%s\"",file);
			return;
		}
		
		Path path = new Path();
		
		source.readInt(); // skipping magic
		
		vec3 xyz;
		quat rot;
		vec3 scale;
		path.setNumFrames(source.readInt());
		forloop(int i = 0; path.getNumFrames()) {
			int flags = source.readUShort();
			float time = source.readFloat();
			if(flags & (1 << 0)) xyz.x = source.readFloat();
			if(flags & (1 << 1)) xyz.y = source.readFloat();
			if(flags & (1 << 2)) xyz.z = source.readFloat();
			if(flags & (1 << 3)) rot.x = (float(source.readUShort()) / 65535.0f) * 2.0f - 1.0f;
			if(flags & (1 << 4)) rot.y = (float(source.readUShort()) / 65535.0f) * 2.0f - 1.0f;
			if(flags & (1 << 5)) rot.z = (float(source.readUShort()) / 65535.0f) * 2.0f - 1.0f;
			if(flags & (1 << 6)) rot.w = (float(source.readUShort()) / 65535.0f) * 2.0f - 1.0f;
			if(flags & (1 << 7)) scale.x = source.readFloat();
			if(flags & (1 << 8)) scale.y = source.readFloat();
			if(flags & (1 << 9)) scale.z = source.readFloat();
			if(flags & 0x78) rot = normalize(rot);
			path.setFrameTime(i,time);
			path.setFramePosition(i,xyz);
			path.setFrameRotation(i,rot);
			path.setFrameScale(i,scale);
		}
		
		source.close();
		delete source;
		
		string new_name;
		
		if(lower(getExtension(file)) == ".spline") {
			new_name = setExtension(file,".path");
		} else {
			new_name = file;
		}
		
		if(new_name != file && is_file(new_name)) {
			Log::error("file \"%s\" already exists",new_name);
			delete path;
			return;
		}
		
		if(!path.save(new_name)) {
			Log::error("failed to edit file \"%s\"",new_name);
			delete path;
			return;
		}
		
		if(file != new_name) {
			remove(file);
		}
		
		delete path;
	}
	
} /* namespace Path */

#endif /* __MIGRATION_PATH_H__ */
