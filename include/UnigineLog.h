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

#pragma once

#include "UnigineBase.h"

namespace Unigine
{

template<typename ...Args> class Event;

namespace Math
{
struct vec4;
}
}

using LogEvent = Unigine::Event<const char *>;

namespace Unigine
{

class Log
{
public:

	// Prints a message to the console and the log file.
	static UNIGINE_API void message(const char *format, ...) UNIGINE_PRINTF(1, 2);
	static UNIGINE_API void message(const Unigine::Math::vec4 &color, const char *format, ...);

	// Prints a warning to the console and the log file.
	static UNIGINE_API void warning(const char *format, ...) UNIGINE_PRINTF(1, 2);

	// Prints an error message to the console and the log file.
	static UNIGINE_API void error(const char *format, ...) UNIGINE_PRINTF(1, 2);

	// Prints a fatal error message to the log file and immediately quit the engine.
	static UNIGINE_API void fatal(const char *format, ...) UNIGINE_PRINTF(1, 2);

	static UNIGINE_API void setDialogFatalEnabled(bool enabled);
	static UNIGINE_API bool isDialogFatalEnabled();

	static UNIGINE_API LogEvent &getEventMessage();
	static UNIGINE_API LogEvent &getEventWarning();
	static UNIGINE_API LogEvent &getEventError();
	static UNIGINE_API LogEvent &getEventFatal();
};

} // namespace Unigine
