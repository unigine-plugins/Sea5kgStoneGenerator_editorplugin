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

#ifndef __FBX_READER_H__
#define __FBX_READER_H__

string const_unit_scale = "UnitScaleFactor";
int const_unit_scale_size = strlen(const_unit_scale);
string const_original_unit_scale = "OriginalUnitScaleFactor";
int const_original_unit_scale_size = strlen(const_original_unit_scale);

int compare_buff(int b0[], int offset, string b1, int size, int buffer_size) {
	for(int i = 0; i < size && (i + offset) < buffer_size; i++) {
		if(b0[i + offset] != b1[i]) return 0;
	}
	return 1;
}

int read_int(int buffer[], int offset) {
	int v = 0;
	v |= (buffer[offset + 3] & 0xFF) << 24;
	v |= (buffer[offset + 2] & 0xFF) << 16;
	v |= (buffer[offset + 1] & 0xFF) << 8;
	v |= (buffer[offset + 0] & 0xFF) << 0;
	return v;
}

double read_double(int buffer[], int offset) {
	int buff[0];
	for(int i = offset; i < offset + 8; i++) {
		buff.append(buffer[i]);
	}
	
	Blob blob = new Blob();
	blob.write(buff, buff.size());
	blob.seekSet(0);
	double v = blob.readDouble();
	delete blob;
	return v;
}

double read_property_bin(int buffer[], int offset) {
	int value_pos = 0;
	for(int i = offset; i < offset + 64 && i < buffer.size(); i++) {
		if(buffer[i] == 'D') {
			value_pos = i + 1;
			break;
		}
	}
	
	if(value_pos == 0)
		return -666.0;
	
	return read_double(buffer, value_pos);
}

double read_property_text(int buffer[], int offset) {
	int pos_value = offset;
	int num_comma = 0;
	for(int i = offset; i < buffer.size() && buffer[i] != '\n' && buffer[i] != '\r' && num_comma != 4; i++) {
		if(buffer[i] == ',') num_comma++;
		pos_value++;
	}
	
	int buff[0];
	for(int i = pos_value;  i < buffer.size() && buffer[i] != '\r' && buffer[i] != '\n'; i++)
		buff.append(buffer[i]);
	
	Blob blob = new Blob();
	blob.writeInt(buff.size() + 1);
	for(int i = 0; i < buff.size(); i++)
		blob.writeChar(buff[i]);
	blob.writeChar(0);
	blob.seekSet(0);
	string v = blob.readString();
	delete blob;
	return double(v);
}

int process_bin(int buffer[], double &unit_scale, double &original_unit_scale) {
	int found = 0;
	int buffer_size = buffer.size();
	for(int i = 0; i < buffer_size && found < 2; i++) {
		if(compare_buff(buffer, i, const_unit_scale, const_unit_scale_size, buffer_size) == 1) {
			if((buffer_size - i) > 128) {
				unit_scale = read_property_bin(buffer, i);
				found++;
			}
			continue;
		}
		if(compare_buff(buffer, i, const_original_unit_scale, const_original_unit_scale_size, buffer_size) == 1) {
			if((buffer_size - i) > 128) {
				original_unit_scale = read_property_bin(buffer, i);
				found++;
			}
			continue;
		}
	}
	return found == 2;
}

int process_text(int buffer[], double &unit_scale, double &original_unit_scale) {
	int found = 0;
	int buffer_size = buffer.size();
	for(int i = 0; i < buffer_size && found < 2; i++) {
		if(compare_buff(buffer, i, const_unit_scale, const_unit_scale_size, buffer_size) == 1) {
			if((buffer_size - i) > 128) {
				unit_scale = read_property_text(buffer, i);
				found++;
			}
			continue;
		}
		if(compare_buff(buffer, i, const_original_unit_scale, const_original_unit_scale_size, buffer_size) == 1) {
			if((buffer_size - i) > 128) {
				original_unit_scale = read_property_text(buffer, i);
				found++;
			}
			continue;
		}
	}
	return found == 2;
}

int read_fbx(string filepath, double &unit_scale, double &original_unit_scale) {
	File file = new File();
	if(!file.open(filepath, "rb")) {
		log.error("read_fbx: can't open file %s\n", filepath);
		return 0;
	}
	
	string binary_magic = "Kaydara FBX Binary";

	int BUFFER_SIZE = 8192;
	int buffer[0];
	file.read(buffer, BUFFER_SIZE);
	
	int is_binary = compare_buff(buffer, 0, binary_magic, strlen(binary_magic), buffer.size());
	int ret = 0;
	int read = 0;
	
	do {
		if(is_binary) {
			ret = process_bin(buffer, unit_scale, original_unit_scale);
		} else {
			ret = process_text(buffer, unit_scale, original_unit_scale);
		}
		if(ret == 1) break;
		if(file.eof()) break;
		buffer.clear();
		file.seekSet(file.tell() - 1024);
		read = file.read(buffer, BUFFER_SIZE);
	} while(read > 0);

	file.close();
	delete file;
	
	if(ret == 0) {
		log.error("read_fbx: can't parse %s file\n", filepath);
		return 0;
	}
	
	if(compare(unit_scale, -666.0)) {
		log.error("read_fbx: can't get unit_scale.\n");
		return 0;
	}
	
	if(compare(original_unit_scale, -666.0)) {
		log.error("read_fbx: can't get original_unit_scale.\n");
		return 0;
	}
	
	return 1;
}

#endif /* __FBX_READER_H__ */
