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

#ifndef __MIGRATION_LANDSCAPE_H__
#define __MIGRATION_LANDSCAPE_H__

namespace LandscapeMapFile {
	
	int LANDSCAPE_FILE_MAGIC_11 = ('l' | ('f' << 8) | ('1' << 16) | ('1' << 24));
	int LANDSCAPE_FILE_MAGIC_12 = ('l' | ('f' << 8) | ('1' << 16) | ('2' << 24));
	int LANDSCAPE_FILE_MAGIC_13 = ('l' | ('f' << 8) | ('1' << 16) | ('3' << 24));
	int LANDSCAPE_FILE_NUM_TYPES = 13;

	long desc_size = 664;
	long injection_size = 280;
	long injection_start = 4 + desc_size - injection_size;
	long blob_size = 1024 * 1024 * 32;

	void processPath(string data_path) {
		string files[0] = ();
		findFilesByExt(files, data_path, ".lmap");
		foreach(string file; files)
		{
			processFile(file);
		}
	}
	
	void processFile(string file_name) {
		File file = new File();
		file.open(file_name, "r+b");

		if (!file.isOpened())
		{
			Log::info("can't open \"%s\"", file_name);
			return;
		}

		long original_size;
		int version;
		long pos;
		int num_tiles;
		int num_lods;
		ivec2 map_size;

		version = file.readInt();
		if (version != LANDSCAPE_FILE_MAGIC_11 && version != LANDSCAPE_FILE_MAGIC_12)
		{
			file.close();
			return;
		}

		Log::info("upgrading \"%s\"", file_name);

		original_size = file.getSize();
		
		Blob buffer;
		buffer = new Blob();
		buffer.allocate(blob_size);

		pos = original_size;
		while (pos > injection_start)
		{
			long size;

			size = min(pos - injection_start, blob_size);
			pos -= size;

			file.seekSet(pos);
			buffer.seekSet(0);
			buffer.writeStream(file, size);

			file.seekSet(pos + injection_size);
			buffer.seekSet(0);
			file.writeStream(buffer, size);
		}

		delete buffer;

		file.seekSet(injection_start);
		forloop (int i = 0; injection_size)
			file.writeUChar(0);

		file.seekSet(4);
		map_size = file.readIVec2();
		file.seekSet(4 + 116);
		num_lods = file.readInt();
		file.seekSet(4 + 120);
		num_tiles = file.readInt();

		int lod_offsets[64];
		forloop(int i = 0; 64)
			lod_offsets[i] = file.readInt();

		pos = 4 + desc_size + 8 + long(num_tiles) * 8 * 2;
		forloop (int i = 0; LANDSCAPE_FILE_NUM_TYPES)
		{
			forloop (int j = 0; num_tiles)
			{
				long offset;

				file.seekSet(pos);
				offset = file.readLong();

				if (offset != 0)
				{
					offset += long(injection_size);

					file.seekSet(pos);
					file.writeLong(offset);
				}
				pos += 8;
			}
		}

		void update_extremum(long offset)
		{
			forloop(int tile_id = 0; lod_offsets[1])
			{
				ivec3 coord;
				coord.z = num_lods - 1;
				while (coord.z >= 0)
				{
					int local_index;
					local_index = tile_id - lod_offsets[coord.z];

					if (local_index >= 0)
					{
						coord.y = (local_index / map_size.x);
						coord.x = local_index - (coord.y * map_size.x);
						break;
					}
					coord.z--;
				}

				if (coord.z != 0)
					continue;

				ivec3 lod_coord;
				lod_coord = coord;

				lod_coord.x /= 2;
				lod_coord.y /= 2;
				lod_coord.z++;

				while (lod_coord.z < num_lods)
				{
					ivec2 prev_map_size;
					ivec2 next_map_size;

					prev_map_size = map_size >> (lod_coord.z - 1);
					next_map_size = map_size >> lod_coord.z;

					vec2 height;
					height = vec2(INFINITY, -INFINITY);

					lod_coord.x = max(lod_coord.x, 0);
					lod_coord.y = max(lod_coord.y, 0);
					lod_coord.x = min(lod_coord.x, next_map_size.x - 1);
					lod_coord.y = min(lod_coord.y, next_map_size.y - 1);

					forloop(int x = 0; 2)
					{
						forloop(int y = 0; 2)
						{
							ivec2 tc = ivec2(lod_coord.x * 2 + x, lod_coord.y * 2 + y);
							if (tc.x >= prev_map_size.x || tc.y >= prev_map_size.y || tc.x < 0 || tc.y < 0)
								continue;

							int child_id;
							child_id = lod_offsets[lod_coord.z - 1] + tc.x + tc.y * (map_size.x >> (lod_coord.z - 1));

							file.seekSet(offset + child_id * 8);
							vec2 child;
							child = file.readVec2();

							height.x = min(height.x, child.x);
							height.y = max(height.y, child.y);
						}
					}

					int parent_id;
					parent_id = lod_offsets[lod_coord.z] + lod_coord.x + lod_coord.y * (map_size.x >> lod_coord.z);

					file.seekSet(offset + parent_id * 8);
					file.writeVec2(height);

					lod_coord.x /= 2;
					lod_coord.y /= 2;
					lod_coord.z++;
				}
			}
		}

		update_extremum(4 + desc_size + 8);
		update_extremum(4 + desc_size + 8 + long(num_tiles) * 8);

		file.seekSet(0);
		file.writeInt(LANDSCAPE_FILE_MAGIC_13);
		file.seekSet(4 + desc_size);
		file.writeLong(original_size + injection_size);

		file.close();
	}
}

#endif /* __MIGRATION_LANDSCAPE_H__ */
