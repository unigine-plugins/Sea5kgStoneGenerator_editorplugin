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

#include <UnigineVector.h>
#include <UnigineNode.h>

#include "UnigineEditorGlobal.h"

namespace UnigineEditor
{

//////////////////////////////////////////////////////////////////////////

/// <summary>This class allows configuring the widget that controls objects selection and positioning in the scene.</summary>
class UNIGINE_EDITOR_API ObjectMode
{
public:
	static bool isInitialized();

	/// <summary>Type of transformation applied to the node selected by the manipulator.</summary>
	enum TRANSFORM_TYPE
	{
		/// <summary>Node selection.</summary>
		TRANSFORM_TYPE_SELECT = 0,
		/// <summary>Node positioning.</summary>
		TRANSFORM_TYPE_TRANSLATE,
		/// <summary>Node rotation.</summary>
		TRANSFORM_TYPE_ROTATE,
		/// <summary>Node scaling.</summary>
		TRANSFORM_TYPE_SCALE,
		/// <summary>Total number of transformation types.</summary>
		TRANSFORM_TYPE_NUM,
	};

	/// <summary>Type of the coordinate system used.</summary>
	enum BASIS_TYPE
	{
		/// <summary>World coordinate system.</summary>
		BASIS_TYPE_WORLD = 0,
		/// <summary>Parent node coordinate system.</summary>
		BASIS_TYPE_PARENT,
		/// <summary>Local coordinate system of the last selected node.</summary>
		BASIS_TYPE_LOCAL_LAST_SELECTED,
		/// <summary>Individual local coordinate system for each node in selection.</summary>
		BASIS_TYPE_LOCAL_INDEPENDENT,
		/// <summary>Total number of basis types.</summary>
		BASIS_TYPE_NUM,
	};

	/// <summary>Type of the pivot used for rotation of the selected nodes.</summary>
	enum PIVOT_TYPE
	{
		/// <summary>Pivot point is in the center of selection.</summary>
		PIVOT_TYPE_CENTER = 0,
		/// <summary>Pivot point is set to the center of the last selected node.</summary>
		PIVOT_TYPE_OBJECT,
		/// <summary>Total number of pivot types.</summary>
		PIVOT_TYPE_NUM,
	};

	/// <summary>Type of node positioning: moving over the grid with a given step or with a step equal to the dimensions of node's bounding box.</summary>
	enum GRID_MODE
	{
		/// <summary>Node positioning is performed with a step equal to the dimensions of node's bounding box.</summary>
		GRID_MODE_BOUND_BOX = 0,
		/// <summary>Node positioning is performed by moving over the grid with a given step.</summary>
		GRID_MODE_UNIFORM,
		/// <summary>Total number of positioning types.</summary>
		GRID_MODE_NUM,
	};

	/// <summary>Direction of dropping the node.</summary>
	enum DROP_DIRECTION
	{
		/// <summary>Node is placed onto the closest surface above it.</summary>
		DROP_DIRECTION_UP = 0,
		/// <summary>Node is placed onto the closest surface below it.</summary>
		DROP_DIRECTION_DOWN,
		/// <summary>Node is placed onto the closest surface either above or below it.</summary>
		DROP_DIRECTION_UP_AND_DOWN,
		/// <summary>Total number of dropping direction types.</summary>
		DROP_DIRECTION_NUM,
	};
	/// <summary>Returns the value indicating if the object mode is enabled.</summary>
	static bool isEnabled();
	// Manipulators
	/// <summary>Returns the value indicating if the manipulators are enabled.</summary>
	static void setManipulatorsEnabled(bool enabled);
	/// <summary>Returns the value indicating if the manipulators are enabled.</summary>
	static bool isManipulatorsEnabled();
	/// <summary>Returns the value indicating if the specified type of transformation is enabled.</summary>
	/// <param name='type'>Type of transformation (see <see cref='TRANSFORM_TYPE'/>).</param>
	static bool isTransformTypeEnabled(ObjectMode::TRANSFORM_TYPE type);
	/// <summary>Returns the value indicating if the basis is enabled.</summary>
	static bool isBasisEnabled();
	/// <summary>Sets the type of transformation applied to the node(s) selected by the manipulator.</summary>
	/// <param name='type'>Type of transformation to be set (see <see cref='TRANSFORM_TYPE'/>).</param>
	static void setTransformType(ObjectMode::TRANSFORM_TYPE type);
	/// <summary>Returns the type of transformation applied to the node(s) selected by the manipulator.</summary>
	static ObjectMode::TRANSFORM_TYPE getTransformType();
	/// <summary>Sets the type of basis applied to the node(s) selected by the manipulator.</summary>
	/// <param name='type'>Type of basis to be set (see <see cref='BASIS_TYPE'/>).</param>
	static void setBasisType(ObjectMode::BASIS_TYPE type);
	/// <summary>Returns the type of basis applied to the node(s) selected by the manipulator.</summary>
	static ObjectMode::BASIS_TYPE getBasisType();
	/// <summary>Sets the type of pivot applied to the node(s) selected by the manipulator.</summary>
	/// <param name='type'>Type of pivot to be set (see <see cref='PIVOT_TYPE'/>).</param>
	static void setPivotType(ObjectMode::PIVOT_TYPE type);
	/// <summary>Returns the type of pivot applied to the node(s) selected by the manipulator.</summary>
	static ObjectMode::PIVOT_TYPE getPivotType();
	/// <summary>Sets the value indicating if the position snapping is enabled.</summary>
	/// <param name='enabled'>Value indicating if the position snapping is enabled.</param>
	static void setPositionSnappingEnabled(bool enabled);
	/// <summary>Returns the value indicating if the position snapping is enabled.</summary>
	static bool isPositionSnappingEnabled();
	/// <summary>Sets the mode of position snapping applied to the node(s) selected by the manipulator.</summary>
	/// <param name='mode'>Mode of position snapping to be set (see <see cref='GRID_MODE'/>).</param>
	static void setPositionSnappingMode(ObjectMode::GRID_MODE mode);
	/// <summary>Returns the mode of position snapping applied to the node(s) selected by the manipulator.</summary>
	static ObjectMode::GRID_MODE getPositionSnappingMode();
	/// <summary>Sets the step value for position snapping, if the mode is set to grid (see <see cref='PositionSnappingMode'/>).</summary>
	/// <param name='step'>The position step, in units.</param>
	static void setPositionSnappingByGridStep(float step);
	/// <summary>Returns the step value for position snapping, if the mode is set to grid (see <see cref='PositionSnappingMode'/>).</summary>
	static float getPositionSnappingByGridStep();
	/// <summary>Sets the value indicating if the rotation snapping is enabled.</summary>
	/// <param name='enabled'>Value indicating if the rotation snapping is enabled.</param>
	static void setRotationSnappingEnabled(bool enabled);
	/// <summary>Returns the value indicating if the rotation snapping is enabled.</summary>
	static bool isRotationSnappingEnabled();
	/// <summary>Sets the step value for rotation snapping (see <see cref='RotationSnappingEnabled'/>).</summary>
	/// <param name='step'>Rotation step, angle in degrees.</param>
	static void setRotationSnappingStep(float step);
	/// <summary>Returns the step value for rotation snapping (see <see cref='RotationSnappingEnabled'/>).</summary>
	static float getRotationSnappingStep();
	/// <summary>Sets the value indicating if scale snapping is enabled.</summary>
	/// <param name='enabled'>Value indicating if scale snapping is enabled.</param>
	static void setScaleSnappingEnabled(bool enabled);
	/// <summary>Returns the value indicating if scale snapping is enabled.</summary>
	static bool isScaleSnappingEnabled();
	/// <summary>Sets the step value for scale snapping (see <see cref='ScaleSnappingEnabled'/>).</summary>
	/// <param name='step'>Scale step.</param>
	static void setScaleSnappingStep(float step);
	/// <summary>Returns the step value for scale snapping (see <see cref='ScaleSnappingEnabled'/>).</summary>
	static float getScaleSnappingStep();
	// Snap to Surface
	/// <summary>Returns the value indicating if snapping to surface is enabled.</summary>
	static bool isSnapToSurfaceEnabled();
	/// <summary>Sets the offset applied when snapping a node to the surface (see <see cref='isSnapToSurfaceEnabled'/>).</summary>
	/// <param name='offset'>Distance from the node's pivot point to the surface (in units).</param>
	static void setSnapToSurfaceOffset(float offset);
	/// <summary>Returns the offset applied when snapping a node to the surface (see <see cref='isSnapToSurfaceEnabled'/>).</summary>
	static float getSnapToSurfaceOffset();
	/// <summary>Sets the value indicating if the node should be oriented by the surface normal, when snapping a node to the surface (see <see cref='isSnapToSurfaceEnabled'/>).</summary>
	/// <param name='normal'>Value indicating if the node should be oriented by the surface normal.</param>
	static void setSnapToSurfaceOrientByNormal(bool normal);
	/// <summary>Returns the value indicating if the node should be oriented by the surface normal, when snapping a node to the surface (see <see cref='isSnapToSurfaceEnabled'/>).</summary>
	static bool isSnapToSurfaceOrientByNormal();
	/// <summary>Sets the value indicating if the node should be snapped to the surface with the Intersection parameter enabled.</summary>
	/// <param name='intersection'>Value indicating if the node is snapped to the surface with Intersection enabled.</param>
	static void setSnapToSurfaceToNodesWithEnabledIntersection(bool intersection);
	/// <summary>Returns the value indicating if the node should be snapped to the surface with the Intersection parameter enabled.</summary>
	static bool isSnapToSurfaceToNodesWithEnabledIntersection();
	/// <summary>Snaps the specified node to surface.</summary>
	/// <param name='node'>Node to be snapped to surface.</param>
	static void snapToSurfaceNode(const Unigine::Ptr<Unigine::Node> &node);
	/// <summary>Snaps the nodes from the specified list to surface.</summary>
	/// <param name='nodes'>List of nodes to be snapped to surface.</param>
	static void snapToSurfaceNodeList(const Unigine::Vector<Unigine::Ptr<Unigine::Node>> &nodes);
	// Drop to Ground
	/// <summary>Sets the direction of dropping applied to the node(s) selected by the manipulator.</summary>
	/// <param name='direction'>Direction of dropping to be set (see <see cref='DROP_DIRECTION'/>).</param>
	static void setDropToGroundDirection(ObjectMode::DROP_DIRECTION direction);
	/// <summary>Returns the direction of dropping applied to the node(s) selected by the manipulator.</summary>
	static ObjectMode::DROP_DIRECTION getDropToGroundDirection();
	/// <summary>Sets the offset applied when dropping a node to the ground.</summary>
	/// <param name='offset'>Distance from the node's pivot point to the ground (in units).</param>
	static void setDropToGroundOffset(float offset);
	/// <summary>Returns the offset applied when dropping a node to the ground.</summary>
	static float getDropToGroundOffset();
	/// <summary>Sets the value indicating if the node should be oriented by the ground normal, when dropped to the ground.</summary>
	/// <param name='normal'>Value indicating if the node should be oriented by the ground normal.</param>
	static void setDropToGroundOrientByNormal(bool normal);
	/// <summary>Returns the value indicating if the node should be oriented by the ground normal, when dropped to the ground.</summary>
	static bool isDropToGroundOrientByNormal();
	/// <summary>Sets the intersection mask that defines whether the selected node(s) will be positioned on the surface to which this node(s) is dropped.</summary>
	/// <param name='mask'>Intersection mask that should match the surface intersection mask for the node to be dropped onto that surface.</param>
	static void setDropToGroundMask(int mask);
	/// <summary>Returns the intersection mask that defines whether the selected node(s) will be positioned on the surface to which this node(s) is dropped.</summary>
	static int getDropToGroundMask();
	/// <summary>Sets the value indicating if the node should be dropped to the ground if it has the Intersection parameter enabled.</summary>
	/// <param name='intersection'>Value indicating if the node is snapped to the ground if it has the Intersection parameter enabled.</param>
	static void setDropToGroundToNodesWithEnabledIntersection(bool intersection);
	/// <summary>Returns the value indicating if the node should be dropped to the ground if it has the Intersection parameter enabled.</summary>
	static bool isDropToGroundToNodesWithEnabledIntersection();
	/// <summary>Drops the specified node to the ground.</summary>
	/// <param name='node'>Node to be dropped to the ground.</param>
	static void dropToGroundNode(const Unigine::Ptr<Unigine::Node> &node);
	/// <summary>Drops the nodes from the specified list to the ground.</summary>
	/// <param name='nodes'>List of nodes to be dropped to the ground.</param>
	static void dropToGroundNodeList(const Unigine::Vector<Unigine::Ptr<Unigine::Node>> &nodes);
};

} // namespace UnigineEditor
