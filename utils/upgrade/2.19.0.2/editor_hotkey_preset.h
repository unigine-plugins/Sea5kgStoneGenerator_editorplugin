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

#ifndef __EDITOR_HOTKEY_PRESET_H__
#define __EDITOR_HOTKEY_PRESET_H__

namespace EditorHotkeyPreset {

	void processPath(string data_path) {
		string files[0] = ();
		findFilesByExt(files, data_path, ".preset");
		foreach(string file; files)
			if(!skipFile(data_path, file))
				processFile(file);
	}

	void processFile(string file) {
		Json json = new Json();

		if(!json.load(file)) {
			Log::error("failed to load \"%s\"", file);
			delete json;
			return;
		}

		Log::info("upgrading \"%s\"", file);

		Process::editorHotkeyPreset(json);

		json.save(file);
		delete json;
	}
}

#endif /* __EDITOR_HOTKEY_PRESET_H__ */
