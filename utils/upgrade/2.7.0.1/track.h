/* Copyright (C) 2005-2024, UNIGINE. All rights reserved.
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

#ifndef __MIGRATION_TRACK_H__
#define __MIGRATION_TRACK_H__

namespace Track {
	
	void processFile(string file) {
		
		Xml xml = new Xml();
		
		if(!xml.load(file)) {
			Log::error("failed to load \"%s\"",file);
			delete xml;
			return;
		}
		
		Log::info("upgrading \"%s\"",file);
		
		xml.setArg("version",ENGINE_VERSION);
		
		Process::track(xml);
		
		xml.save(file);
		
		delete xml;
	}
}

#endif /* __MIGRATION_TRACK_H__ */
