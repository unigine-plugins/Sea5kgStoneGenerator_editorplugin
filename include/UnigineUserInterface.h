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
// DO NOT EDIT DIRECTLY. This is an auto-generated file. Your changes will be lost.

#pragma once

#include "UnigineGui.h"
#include "UnigineWidgets.h"
#include "UnigineCallback.h"

namespace Unigine
{


class UNIGINE_API UserInterface : public APIInterface
{
public:

	enum EVENT_TYPE
	{
		EVENT_SHOW = 0,
		EVENT_HIDE,
		EVENT_FOCUS_IN,
		EVENT_FOCUS_OUT,
		EVENT_CHANGED,
		EVENT_CLICKED,
		EVENT_DOUBLE_CLICKED,
		EVENT_PRESSED,
		EVENT_RELEASED,
		EVENT_KEY_PRESSED,
		EVENT_TEXT_PRESSED,
		EVENT_ENTER,
		EVENT_LEAVE,
		EVENT_DRAG_MOVE,
		EVENT_DRAG_DROP,
		EVENT_REMOVE,
		NUM_EVENTS,
	};
	static Ptr<UserInterface> create(const Ptr<Gui> &gui, const char *name, const char *prefix = 0);
	void setGui(const Ptr<Gui> &gui);
	Ptr<Gui> getGui() const;
	void setLifetime(Widget::LIFETIME lifetime);
	Widget::LIFETIME getLifetime() const;
	void updateWidgets() const;
	int getNumWidgets() const;
	int findWidget(const char *name) const;
	Ptr<Widget> getWidget(int num) const;
	Ptr<Widget> getWidgetByName(const char *name) const;
	const char *getWidgetName(int num) const;
	const char *getWidgetNext(int num) const;
	int getWidgetExport(int num) const;
	int getNumCallbacks(int num) const;
	UserInterface::EVENT_TYPE getCallback(int num, int callback) const;
	const char *getCallbackName(int num, int callback) const;
	Ptr<Widget> getCallbackWidgetData(int num, int callback) const;
	const char *getCallbackStringData(int num, int callback) const;
	const char *getCallbackVariableData(int num, int callback) const;
	const char *getCallbackInstanceData(int num, int callback) const;
};
typedef Ptr<UserInterface> UserInterfacePtr;

} // namespace Unigine
