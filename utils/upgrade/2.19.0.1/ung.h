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


#ifndef __MIGRATION_UNG_H__
#define __MIGRATION_UNG_H__

namespace Ung
{
	int UNG_MAGIC_3 = 'a' | ('r' << 8) | ('0' << 16) | ('3' << 24);
	int UNG_MAGIC_4 = 'a' | ('r' << 8) | ('0' << 16) | ('4' << 24);

	enum
	{
		COMPRESSION_NONE = 0,
		COMPRESSION_BEST_SPEED,
		COMPRESSION_BEST_SIZE
	};

	string compressionTypeToText(int type)
	{
		switch(type)
		{
			case COMPRESSION_NONE: return "none";
			case COMPRESSION_BEST_SPEED: return "speed";
			case COMPRESSION_BEST_SIZE: return "size";
		}

		return "";
	}

	void processPath(string data_path)
	{
		string files[0] = ();
		findFilesByExt(files, data_path, ".ung");
		foreach(string file; files)
		{
			if(!skipFile(data_path, file))
				processFile(pathname(data_path), pathname(file) + basename(file));
		}
	}

	string getBinUscExtension()
	{
		string usc_path = replace(getArg(-1), "\\", "/");
		if(!is_absolute(usc_path))
			usc_path = absname(currdir() + "/",usc_path);

		return getExtension(usc_path);
	}

	string getBinUngDir()
	{
		string script_dir = pathname(replace(__FILE__,"\\","/"));
		if(!is_absolute(script_dir))
			script_dir = absname(currdir() + "/",script_dir);

		return script_dir + "bin/";
	}

	void getUngInfo(string file_path, int &magic, int &compression_type)
	{
		File file = new File();

		if(file.open(file_path, "rb"))
		{
			magic = file.readInt();
			compression_type = file.readInt();
			file.close();
		} else
		{
			magic = 0;
			compression_type = -1;
			Log::error("failed to open file \"%s\"", file_path);
		}

		delete file;
	}

	string quote(string str)
	{
		return "\"" + str + "\"";
	}

	int getFilesList(string root_dir_path, string &result)
	{
		if(!is_dir(root_dir_path))
		{
			Log::error("directory \"%s\" doesn't exist", root_dir_path);
			return false;
		}

		Dir dir = new Dir(root_dir_path);

		if(!dir.isOpened())
		{
			Log::error("failed to open directory \"%s\"", root_dir_path);
			delete dir;
			return false;
		}

		forloop(int i = 0; dir.getNumFiles())
			result += quote(relname(root_dir_path, dir.getFileName(i))) + " ";

		forloop(int i = 0; dir.getNumDirs())
			result += quote(relname(root_dir_path, dir.getDirName(i))) + " ";

		trim(result);
		delete dir;
		return true;
	}

	void processFile(string data_path, string file)
	{
		int magic;
		int compresion_type;
		getUngInfo(file, magic, compresion_type);

		if(magic == 0 || compresion_type < 0)
			return;

		if(magic != UNG_MAGIC_3 && magic != UNG_MAGIC_4)
			return;

		Log::info("upgrading \"%s\"", file);

		string bin_ext = getBinUscExtension();
		string bin_dir = getBinUngDir();

		string old_archiver_path = bin_dir + "ung_2.18.0.1_x64" + bin_ext;
		string new_archiver_path = bin_dir + "ung_2.19.0.1_x64" + bin_ext;

		// save curr dir
		string old_curr_dir = currdir();
		string unpack_dir = data_path + format("temp_unpack_%s/", withoutExtension(basename(file)));

		mkdir(unpack_dir);
		chdir(unpack_dir);

		string ung_files_list;
		int unpack_result = 1;
		int pack_result = 1;

		// unpack old archive
		{
			Log::info("unpacking \"%s\"", file);

			string cmd_unpack = format("%s -e %s", old_archiver_path, file);
			unpack_result = system(cmd_unpack, 1);

			if(unpack_result == 0)
			{
				getFilesList(unpack_dir, ung_files_list);
			} else
			{
				log.error("Command finished with error: %s\n", cmd_unpack);
			}
		}

		int ung_files_num = strlen(ung_files_list);

		// pack new archive
		if((unpack_result == 0) && (ung_files_num > 0))
		{
			remove_file(file);
			Log::info("packing \"%s\"", file);

			string compression_type_text = compressionTypeToText(compresion_type);
			string cmd_pack = format("%s -c %s -o %s %s", new_archiver_path, compression_type_text, file, ung_files_list);

			pack_result = system(cmd_pack, 1);

			if(pack_result != 0)
				log.error("Command finished with error: %s\n", cmd_pack);
		}

		// restore curr dir
		chdir(old_curr_dir);

		// remove temp dir
		if((pack_result == 0) || (ung_files_num == 0))
			remove_directory(unpack_dir);
	}

} /* namespace Ung */

#endif /* __MIGRATION_UNG_H__ */
