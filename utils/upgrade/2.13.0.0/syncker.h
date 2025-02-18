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

#ifndef __MIGRATION_SYNCKER_H__
#define __MIGRATION_SYNCKER_H__

/*
 */
namespace Syncker {
	
	void processPath(string data_path) {
		string files[0] = ();
		findFilesByExt(files, data_path, ".sync");
		foreach(string file; files)
			if(!skipFile(data_path, file))
				processFile(file);
	}
	
	void processFile(string file) {
		
		Xml xml = new Xml();
		if(!xml.load(file)) {
			Process::synckerBinary(file);
			delete xml;
			return;
		}
		
		Log::info("upgrading \"%s\"", file);
		
		xml.setArg("version", ENGINE_VERSION);
		
		Process::syncker(xml);
		
		xml.save(file);
		delete xml;
	}
	
} /* namespace Syncker */

#endif /* __MIGRATION_SYNCKER_H__ */
