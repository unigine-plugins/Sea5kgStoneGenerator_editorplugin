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

#ifndef __MIGRATION_LOG_H__
#define __MIGRATION_LOG_H__

/*
 */
namespace Log {
	
	string LOG_HEADER = "<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
"	<title>Migration log file</title>\n"
"	<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n"
"	<style type=\"text/css\">\n"
"		body {\n"
"			background: #1a242a;\n"
"			color: #ececec;\n"
"			margin: 20px;\n"
"			font-size: 14px;\n"
"			font-family: 'Courier New', Courier, monospace;\n"
"			counter-reset: lognum;\n"
"			tab-size: 4;\n"
"		}\n"
"		\n"
"		.m, .w, .e {\n"
"			padding: 3px;\n"
"			white-space: pre-wrap;\n"
"			line-height: 16px;\n"
"		}\n"
"		\n"
"		.m:before, .w:before, .e:before {\n"
"			counter-increment: lognum;\n"
"			content: counter(lognum) \". \";\n"
"		}\n"
"		\n"
"		.m {\n"
"			color: #ececec;\n"
"		}\n"
"		\n"
"		.w {\n"
"			background-color: #FCF8E3;\n"
"			color: #8A6D3B;\n"
"		}\n"
"		\n"
"		.e {\n"
"			background-color: #d64500;\n"
"			color: #fff;\n"
"		}\n"
"	</style>\n"
"</head>\n"
"<body>\n";
	
	string LOG_FOOTER = "</body>\n"
"</html>";
	
	//
	enum {
		INFO = 30, 
		WARN = 20, 
		ERROR = 10, 
	};
	
	//
	int level = INFO;
	File file;
	
	void init(string file_name) {
		
		if(file_name == "") return;
		
		if(is_file(file_name)) {
			file = new File(file_name, "rb+");
			string contents = file.gets();
			int pos = strstr(contents, "</body>");
			if(pos != -1) {
				file.seekSet(pos);
			} else {
				file.seekSet(0);
				file.puts(LOG_HEADER);
			}
		} else {
			file = new File(file_name, "wb");
			file.puts(LOG_HEADER);
		}
	}
	
	void shutdown() {
		if(file != NULL) {
			file.puts(LOG_FOOTER);
			file.close();
		}
		delete file;
	}
	
	//
	void setLevel(int level_) {
		level = clamp(level_, ERROR, INFO);
	}
	
	//
	int info(string message) {
		if(level >= INFO) {
			log.message("info: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"m\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	int info(string fmt, int arg0) {
		if(level >= INFO) {
			string message = format(fmt, arg0);
			log.message("info: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"m\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	int info(string fmt, int arg0, int arg1) {
		if(level >= INFO) {
			string message = format(fmt, arg0, arg1);
			log.message("info: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"m\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	int info(string fmt, int arg0, int arg1, int arg2) {
		if(level >= INFO) {
			string message = format(fmt, arg0, arg1, arg2);
			log.message("info: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"m\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	//
	int warning(string message) {
		if(level >= WARN) {
			log.warning("warning: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"w\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	int warning(string fmt, int arg0) {
		if(level >= WARN) {
			string message = format(fmt, arg0);
			log.warning("warning: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"w\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	int warning(string fmt, int arg0, int arg1) {
		if(level >= WARN) {
			string message = format(fmt, arg0, arg1);
			log.warning("warning: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"w\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	int warning(string fmt, int arg0, int arg1, int arg2) {
		if(level >= WARN) {
			string message = format(fmt, arg0, arg1, arg2);
			log.warning("warning: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"w\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	//
	int error(string message) {
		if(level >= ERROR) {
			log.error("error: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"e\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	int error(string fmt, int arg0) {
		if(level >= ERROR) {
			string message = format(fmt, arg0);
			log.error("error: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"e\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	int error(string fmt, int arg0, int arg1) {
		if(level >= ERROR) {
			string message = format(fmt, arg0, arg1);
			log.error("error: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"e\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	int error(string fmt, int arg0, int arg1, int arg2) {
		if(level >= ERROR) {
			string message = format(fmt, arg0, arg1, arg2);
			log.error("error: %s\n", message);
			if(file != NULL) {
				file.puts(format("<div class=\"e\">%s</div>\n", escape(message)));
				file.flush();
			}
		}
	}
	
	//
	string escape(string str) {
		str = replace(str, "<", "&lt;");
		str = replace(str, ">", "&gt;");
		return str;
	}
	
} /* namespace Log */

#endif /* __MIGRATION_LOG_H__ */
