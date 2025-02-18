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

#ifndef __MIGRATION_TERRAIN_H__
#define __MIGRATION_TERRAIN_H__

/*
 */
namespace Terrain {
	
	/*
	 */
	int TERRAIN_MAGIC = 't' | ('r' << 8) | ('0' << 16) | ('9' << 24);
	int TERRAIN_DATA_MAGIC = 't' | ('d' << 8) | ('0' << 16) | ('9' << 24);
	
	int TERRAIN_OLD_MAGIC = 't' | ('r' << 8) | ('0' << 16) | ('8' << 24);
	int TERRAIN_OLD_DATA_MAGIC = 't' | ('d' << 8) | ('0' << 16) | ('8' << 24);
	
	int TERRAIN_FILE_SIZE = 8;
	int TERRAIN_PATCH_SIZE = 17;
	int TERRAIN_SURFACE_SIZE = 257;
	int TERRAIN_SURFACE_SHIFT = 8;
	
	int TERRAIN_FILE_SIZE2 = TERRAIN_FILE_SIZE * TERRAIN_FILE_SIZE;
	int TERRAIN_PATCH_SIZE2 = TERRAIN_PATCH_SIZE * TERRAIN_PATCH_SIZE;
	int TERRAIN_SURFACE_SIZE2 = TERRAIN_SURFACE_SIZE * TERRAIN_SURFACE_SIZE;
	
	/*
	 */
	float common_scale = 1.0f;
	
	/*
	 */
	void processFile(string file) {
		
		int magic = getMagic(file);
		
		if(magic == TERRAIN_OLD_MAGIC) {
			Log::info("upgrading \"%s\"",file);
			upgrade_terrain(file);
		}
		
		forloop(int i = 0; 128) {
			
			string data_file = replace(file,".ter",format(".ter%04x",i));
			
			if(!is_file(data_file)) {
				break;
			}
			
			magic = getMagic(data_file);
			
			if(magic == TERRAIN_OLD_DATA_MAGIC) {
				Log::info("upgrading \"%s\"",data_file);
				upgrade_terrain_data(data_file);
			}
		}
	}
	
	void upgrade_terrain(string file) {
		
		//
		string temp_file = getUniqueFileName(file + ".temp");
		
		File original = new File();
		File upgraded = new File();
		
		//
		void cleanup() {
			
			if(original != NULL && original.isOpened()) {
				original.close();
			}
			delete original;
			
			if(upgraded != NULL && upgraded.isOpened()) {
				upgraded.close();
			}
			delete upgraded;
			
			if(is_file(temp_file)) {
				remove(temp_file);
			}
		}
		
		//
		if(!original.open(file,"rb")) {
			Log::error("failed to read file \"%s\"",file);
			cleanup();
			return;
		}
		
		if(!upgraded.open(temp_file,"wb")) {
			Log::error("failed to create file \"%s\"",temp_file);
			cleanup();
			return;
		}
		
		// magic
		original.readInt();
		upgraded.writeInt(TERRAIN_MAGIC);
		
		// terrain size
		int size_x = original.readInt();
		int size_y = original.readInt();
		upgraded.writeInt(size_x);
		upgraded.writeInt(size_y);
		
		// terrain step
		upgraded.writeFloat(original.readFloat());
		
		// terrain height
		float height = original.readFloat();
		common_scale = height / 32767.0f;
		
		// lod threshold
		float process_threshold(int threshold) {
			return (threshold >= 0 ? threshold * height / 65535.0f : -1.0f);
		}
		
		// level of detail
		upgraded.writeFloat(original.readFloat());
		upgraded.writeFloat(original.readFloat());
		upgraded.writeFloat(process_threshold(original.readInt()));
		
		// terrain coarse tree
		void process_coarse(int x,int y,int x0,int y0,int x1,int y1) {
			upgraded.writeStream(original,4 * 6);
			if(x1 - x0 > TERRAIN_SURFACE_SIZE && y1 - y0 > TERRAIN_SURFACE_SIZE) {
				int x01 = (x0 + x1 - 1) / 2;
				int y01 = (y0 + y1 - 1) / 2;
				process_coarse(x * 2 + 0,y * 2 + 0,x0,y0,x01 + 1,y01 + 1);
				process_coarse(x * 2 + 1,y * 2 + 0,x01,y0,x1,y01 + 1);
				process_coarse(x * 2 + 0,y * 2 + 1,x0,y01,x01 + 1,y1);
				process_coarse(x * 2 + 1,y * 2 + 1,x01,y01,x1,y1);
			} else if(x1 - x0 > TERRAIN_SURFACE_SIZE) {
				int x01 = (x0 + x1 - 1) / 2;
				process_coarse(x * 2 + 0,y,x0,y0,x01 + 1,y1);
				process_coarse(x * 2 + 1,y,x01,y0,x1,y1);
			} else if(y1 - y0 > TERRAIN_SURFACE_SIZE) {
				int y01 = (y0 + y1 - 1) / 2;
				process_coarse(x,y * 2 + 0,x0,y0,x1,y01 + 1);
				process_coarse(x,y * 2 + 1,x0,y01,x1,y1);
			} else {
				upgraded.writeUChar(original.readUChar());
				upgraded.writeFloat(process_threshold(original.readInt()));
			}
		}
		process_coarse(0,0,0,0,size_x,size_y);
		
		// second magic
		upgraded.writeInt(TERRAIN_MAGIC);
		
		// terrain coarse heights
		int surfaces_x = (size_x - 1) >> TERRAIN_SURFACE_SHIFT;
		int surfaces_y = (size_y - 1) >> TERRAIN_SURFACE_SHIFT;
		forloop(int i = 0; (surfaces_x + 1) * (surfaces_y + 1)) {
			upgraded.writeFloat(original.readUShort() * height / 65535.0f);
		}
		
		// third magic
		upgraded.writeInt(TERRAIN_MAGIC);
		
		// check terrain
		if(original.tell() != original.getSize()) {
			Log::error("failed to parse \"%s\"",file);
		}
		
		//
		original.close();
		upgraded.close();
		
		if(remove(file))
			rename(temp_file,file);
		else
			Log::error("failed to rewrite \"%s\"",file);
		
		cleanup();
	}
	
	void upgrade_terrain_data(string file) {
		
		//
		string temp_file = getUniqueFileName(file + ".temp");
		
		File original = new File();
		File upgraded = new File();
		
		Blob data = new Blob();
		Blob patch = new Blob();
		Blob surface = new Blob();
		
		//
		void cleanup() {
			
			delete data;
			delete patch;
			delete surface;
			
			if(original != NULL && original.isOpened()) {
				original.close();
			}
			delete original;
			
			if(upgraded != NULL && upgraded.isOpened()) {
				upgraded.close();
			}
			delete upgraded;
			
			if(is_file(temp_file)) {
				remove(temp_file);
			}
		}
		
		//
		if(!original.open(file,"rb")) {
			Log::error("failed to read file \"%s\"",file);
			cleanup();
			return;
		}
		
		if(!upgraded.open(temp_file,"wb")) {
			Log::error("failed to create file \"%s\"",temp_file);
			cleanup();
			return;
		}
		
		// magic
		original.readInt();
		upgraded.writeInt(TERRAIN_DATA_MAGIC);
		
		// reserve space, real values will be written later
		forloop(int i = 0; TERRAIN_FILE_SIZE2) upgraded.writeInt(0);
		forloop(int i = 0; TERRAIN_FILE_SIZE2) upgraded.writeInt(0);
		forloop(int i = 0; TERRAIN_FILE_SIZE2) upgraded.writeInt(0);
		forloop(int i = 0; TERRAIN_FILE_SIZE2) upgraded.writeInt(0);
		
		// read offsets
		int surface_offset[TERRAIN_FILE_SIZE2];
		int surface_size[TERRAIN_FILE_SIZE2];
		int patch_offset[TERRAIN_FILE_SIZE2];
		int patch_size[TERRAIN_FILE_SIZE2];
		
		forloop(int i = 0; TERRAIN_FILE_SIZE2) surface_offset[i] = original.readInt();
		forloop(int i = 0; TERRAIN_FILE_SIZE2) surface_size[i] = original.readInt();
		forloop(int i = 0; TERRAIN_FILE_SIZE2) patch_offset[i] = original.readInt();
		forloop(int i = 0; TERRAIN_FILE_SIZE2) patch_size[i] = original.readInt();
		
		// process height
		int process_height(int data) {
			int ret = as_int((data & 0x7fff) * common_scale) & ~0x01;
			ret |= (data & 0x8000) >> 15;
			return ret;
		}
		
		// process heights
		forloop(int i = 0; TERRAIN_FILE_SIZE2) {
			
			// surface
			surface.clear();
			surface.writeInt(TERRAIN_SURFACE_SIZE2 * 2);
			surface.writeInt(surface_size[i]);
			if(surface_offset[i] && surface_size[i] && original.seekSet(surface_offset[i])) {
				if(original.readStream(surface,surface_size[i]) != surface_size[i]) {
					Log::error("can't read %d surface in \"%s\"",i,file);
					surface_offset[i] = 0;
					surface_size[i] = 0;
					continue;
				}
				surface.seekSet(0);
				if(data.decompress(surface) == 0) {
					Log::error("can't decompress %d surface in \"%s\"",i,file);
					surface_offset[i] = 0;
					surface_size[i] = 0;
					continue;
				}
				surface.clear();
				forloop(int j = 0; TERRAIN_SURFACE_SIZE2) {
					surface.writeInt(process_height(data.readUShort()));
				}
				data.clear();
				surface.compress(data,1);
				data.seekSet(8);
				surface_offset[i] = upgraded.tell();
				upgraded.writeStream(data,data.getSize() - 8);
				surface_size[i] = upgraded.tell() - surface_offset[i];
			}
			
			// patch
			patch.clear();
			patch.writeInt(TERRAIN_PATCH_SIZE2 * 2);
			patch.writeInt(patch_size[i]);
			if(patch_offset[i] && patch_size[i] && original.seekSet(patch_offset[i])) {
				if(original.readStream(patch,patch_size[i]) != patch_size[i]) {
					Log::error("can't read %d patch in \"%s\"",i,file);
					patch_offset[i] = 0;
					patch_size[i] = 0;
				}
				patch.seekSet(0);
				if(data.decompress(patch) == 0) {
					Log::error("can't decompress %d patch in \"%s\"",i,file);
					patch_offset[i] = 0;
					patch_size[i] = 0;
					continue;
				}
				patch.clear();
				forloop(int j = 0; TERRAIN_PATCH_SIZE2) {
					patch.writeInt(process_height(data.readUShort()));
				}
				data.clear();
				patch.compress(data,1);
				data.seekSet(8);
				patch_offset[i] = upgraded.tell();
				upgraded.writeStream(data,data.getSize() - 8);
				patch_size[i] = upgraded.tell() - patch_offset[i];
			}
		}
		
		// update offsets
		upgraded.seekSet(4);
		
		forloop(int i = 0; TERRAIN_FILE_SIZE2) upgraded.writeInt(surface_offset[i]);
		forloop(int i = 0; TERRAIN_FILE_SIZE2) upgraded.writeInt(surface_size[i]);
		forloop(int i = 0; TERRAIN_FILE_SIZE2) upgraded.writeInt(patch_offset[i]);
		forloop(int i = 0; TERRAIN_FILE_SIZE2) upgraded.writeInt(patch_size[i]);
		
		//
		original.close();
		upgraded.close();
		
		if(remove(file))
			rename(temp_file,file);
		else
			Log::error("failed to rewrite \"%s\"",file);
		
		cleanup();
	}
	
} /* namespace Terrain */

#endif /* __MIGRATION_TERRAIN_H__ */
