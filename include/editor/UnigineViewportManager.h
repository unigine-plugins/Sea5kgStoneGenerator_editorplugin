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

#include <UniginePlayers.h>
#include <UnigineGui.h>
#include <UnigineVector.h>
#include <UnigineViewport.h>
#include <UnigineNode.h>
#include <UnigineObjects.h>

#include "UnigineEditorGlobal.h"

namespace UnigineEditor
{

class ViewportWindow;
//////////////////////////////////////////////////////////////////////////

/// <summary> Viewport manager class. This class is used to create, manage, and remove all viewports in the Editor.</summary>
class UNIGINE_EDITOR_API ViewportManager
{
public:
	static bool isInitialized();
	/// <summary> Creates a new viewport window with the specified name.</summary>
	/// <param name='name'>Title of the viewport window.</param>
	/// <returns> Created viewport.</returns>
	static Unigine::Ptr<ViewportWindow> createViewportWindow(const char *name);
	/// <summary> Removes the viewport window with the specified name.</summary>
	/// <param name='name'>Name of the viewport window to be removed.</param>
	/// <returns> <b>true</b> if the viewport window with the specified name was successfully removed; otherwise, <b>false</b>.</returns>
	static bool removeViewportWindow(const char *name);
	/// <summary> Collects all existing viewport windows and puts them to the specified output vector.</summary>
	/// <param name='viewports'>Output vector to receive the list of viewport windows.</param>
	static void getViewports(Unigine::Vector<Unigine::Ptr<ViewportWindow>> &viewports);
	/// <summary> Returns the viewport window with the specified name if it exists; otherwise <b>nullptr</b>.</summary>
	/// <param name='name'>Name of the viewport window.</param>
	static Unigine::Ptr<ViewportWindow> getViewportWindow(const char *name);
	/// <summary> Returns the last viewport window hovered by the mouse cursor. Can be used for implementation of Drag&amp;Drop operations</summary>
	static Unigine::Ptr<ViewportWindow> getLastHoveredViewportWindow();
	/// <summary> Returns the viewport window that is currently active.</summary>
	static Unigine::Ptr<ViewportWindow> getActiveViewportWindow();
	/// <summary> Sets a value indicating if rectangular selection for viewport windows is enabled.</summary>
	/// <param name='enable'><b>true</b> to enable rectangular selection for viewport windows; <b>false</b> - to disable it.</param>
	static void setEnabledRectangleSelection(bool enable);
	/// <summary> Returns a value indicating if rectangular selection for viewport windows is enabled.</summary>
	/// <returns> <b>true</b> if rectangular selection for viewport windows is enabled; otherwise, <b>false</b>.</returns>
	static bool isEnabledRectangleSelection();
	/// <summary> Renders an effect of wireframe warming, a temporary wireframe fading in and out for the current selection (such effect can be seen when selecting a node or a group of nodes in the Editor).</summary>
	static void forceWireframeWarming();
	/// <summary> Activates placement mode for the specified node. The node is to be placed at the location within the viewport where the left mouse button is clicked. If the Esc key is pressed before clicking within the viewport the current node placement operation will be cancelled. This behavior can be observed in the Editor, when the user creates a node via the <b>Create</b> menu. This function will automatically create all necessary Undo Actions (for adding nodes to the world and for selecting them).</summary>
	/// <param name='node'>The node to be placed at the point within the viewport clicked by the user.</param>
	static void placeNode(const Unigine::Ptr<Unigine::Node> &node);
	/// <summary> Activates placement mode for the specified nodes. The nodes are to be placed at the location within the viewport where the left mouse button is clicked. If the Esc key is pressed before clicking within the viewport the current node placement operation will be cancelled. This behavior can be observed in the Editor, when the user creates a node via the <b>Create</b> menu. This function will automatically create all necessary Undo Actions (for adding nodes to the world and for selecting them).</summary>
	/// <param name='nodes'>Vector containing nodes to be placed at the point within the viewport clicked by the user.</param>
	static void placeNodeList(const Unigine::Vector<Unigine::Ptr<Unigine::Node>> &nodes);
	/// <summary> Returns a value indicating if selection is enabled for the specified node type.</summary>
	/// <returns> <b>true</b> if selection for specified node type is enabled; otherwise, <b>false</b>.</returns>
	static bool isNodeTypeSelectable(Unigine::Node::TYPE node_type);
};


/// <summary> This class is used to manage viewport windows in the Editor.</summary>
class UNIGINE_EDITOR_API ViewportWindow : public Unigine::APIInterface
{
public:
	/// <summary> Shows the viewport window.</summary>
	void show();
	/// <summary> Hides the viewport window.</summary>
	void hide();
	/// <summary> Returns the name of the viewport window.</summary>
	const char *getName() const;
	/// <summary> Sets a new main player (camera) whose current view is to be rendered to the viewport window.</summary>
	/// <param name='player'>Player to be used as the main camera for the viewport window.</param>
	void setPlayer(const Unigine::Ptr<Unigine::Player> &player);
	/// <summary> Returns a new main player (camera) whose current view is to be rendered to the viewport window.</summary>
	Unigine::Ptr<Unigine::Player> getPlayer() const;
	/// <summary> Returns the Engine Viewport instance for the viewport window.</summary>
	Unigine::Ptr<Unigine::Viewport> getViewport() const;
	/// <summary> Returns the Gui instance for the viewport window. You can use it to add and manage your UI elements.</summary>
	Unigine::Ptr<Unigine::Gui> getGui() const;
	/// <summary> Returns the X coordinate of the mouse position relative to the viewport window. While the mouse cursor is within the window the coordinate is in the [0, getWidth() - 1] range, otherwise the value can be negative or greater than window width (depending on the mouse cursor position relative to the window).</summary>
	int getMousePosX() const;
	/// <summary> Returns the Y coordinate of the mouse position relative to the viewport window. While the mouse cursor is within the window the coordinate is in the [0, getHeight() - 1] range, otherwise the value can be negative or greater than window height (depending on the mouse cursor position relative to the window).</summary>
	int getMousePosY() const;
	/// <summary> Returns the coordinates of the mouse position relative to the viewport window. Coordinates are returned as a two-component vector (X, Y). While the mouse cursor is within the window the coordinates are within the following ranges: X - [0, getWidth() - 1]; Y - [0, getHeight() - 1]. Otherwise the values can be negative or greater than window height and width (depending on the mouse cursor position relative to the window).</summary>
	Unigine::Math::ivec2 getMousePos() const;
	/// <summary> Returns the current width (in pixels) of the viewport window.</summary>
	int getWidth() const;
	/// <summary> Returns the current height (in pixels) of the viewport window.</summary>
	int getHeight() const;
	/// <summary> Returns the current size of the viewport window. The value is returned as a two-component vector (Width, Height).</summary>
	Unigine::Math::ivec2 getSize() const;
	/// <summary> Sets the camera focus for the viewport window on the specified node.</summary>
	/// <param name='node'>Node to be focused on.</param>
	void focusOnNode(const Unigine::Ptr<Unigine::Node> &node);
	/// <summary> Sets the camera focus for the viewport window on the specified nodes (the viewport will be adjusted to display all the specified nodes).</summary>
	/// <param name='nodes'>Vector containing nodes to be focused on.</param>
	void focusOnNodeList(const Unigine::Vector<Unigine::Ptr<Unigine::Node>> &nodes);
	/// <summary> Sets the current camera focus for the viewport window on the specified node based on its bounds (the viewport will be adjusted to display the specified node with its bounds).</summary>
	/// <param name='node'>Node to be focused on.</param>
	void focusOnNodeBoundBased(const Unigine::Ptr<Unigine::Node> &node);
	/// <summary> Sets the current camera focus for the viewport window on the specified nodes based on their bounds (the viewport will be adjusted to display the specified nodes with their bounds).</summary>
	/// <param name='nodes'>List of nodes to be focused on.</param>
	void focusOnNodeListBoundBased(const Unigine::Vector<Unigine::Ptr<Unigine::Node>> &nodes);
	/// <summary> Sets the camera focus for the viewport window on the specified surface of the specified object (the viewport will be adjusted to display the specified surface).</summary>
	/// <param name='object'>Object to be focused on.</param>
	/// <param name='surface'>The number of the surface of the specified object to be focused on.</param>
	void focusOnSurface(const Unigine::Ptr<Unigine::Object> &object, int surface);
	/// <summary> Sets the camera focus for the viewport window on the specified surfaces of the specified object (the viewport will be adjusted to display all the specified surfaces).</summary>
	/// <param name='object'>Object to be focused on.</param>
	/// <param name='surfaces'>Vector containing the numbers of surfaces of the specified object to be focused on.</param>
	void focusOnSurfaceList(const Unigine::Ptr<Unigine::Object> &object, const Unigine::Vector<int> &surfaces);
	/// <summary> Sets the camera focus for the viewport window on an imaginary sphere with the specified center point and radius.</summary>
	/// <param name='center'>Coordinates of the center of an imaginary sphere to be focused on.</param>
	/// <param name='radius'>Radius of an imaginary sphere to be focused on.</param>
	void focusOnCenter(const Unigine::Math::Vec3 &center, float radius);
};
typedef Unigine::Ptr<ViewportWindow> ViewportWindowPtr;

} // namespace UnigineEditor
