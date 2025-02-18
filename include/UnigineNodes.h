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
// DO NOT EDIT DIRECTLY. This is an auto-generated file. Your changes will be lost.

#pragma once

#include "UnigineNode.h"
#include "UnigineAnimation.h"

namespace Unigine
{

class AnimationPlayback;
//////////////////////////////////////////////////////////////////////////

class UNIGINE_API NodeAnimationPlayback : public Node
{
public:
	static Node::TYPE type() { return Node::NODE_ANIMATION_PLAYBACK; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<NodeAnimationPlayback> create();
	void play();
	void pause();
	void stop();
	bool isPlaying() const;
	void setTime(float time, float from = -1.0f, float to = -1.0f);
	float getTime() const;
	void setTimeTo(float to);
	float getTimeTo() const;
	void setTimeFrom(float from);
	float getTimeFrom() const;
	void setLoop(bool loop);
	bool isLoop() const;
	void setSpeed(float speed);
	float getSpeed() const;
	void setTrackFileGUID(const UGUID &trackfileguid);
	UGUID getTrackFileGUID() const;
	void setTrackPath(const char *path);
	const char *getTrackPath() const;
	void setPlayOnEnable(bool enable);
	bool isPlayOnEnable() const;
	void setRestartOnEnable(bool enable);
	bool isRestartOnEnable() const;
};
typedef Ptr<NodeAnimationPlayback> NodeAnimationPlaybackPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API NodeDummy : public Node
{
public:
	static Node::TYPE type() { return Node::NODE_DUMMY; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<NodeDummy> create();
};
typedef Ptr<NodeDummy> NodeDummyPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API NodeLayer : public Node
{
public:
	static Node::TYPE type() { return Node::NODE_LAYER; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<NodeLayer> create(const char *path);
	void setNodePath(const char *path);
	const char *getNodePath() const;
};
typedef Ptr<NodeLayer> NodeLayerPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API NodeReference : public Node
{
public:
	static Node::TYPE type() { return Node::NODE_REFERENCE; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<NodeReference> create(const char *path);
	Ptr<Node> getReference() const;
	Ptr<Node> detachReference() const;
	void setNodePath(const char *path);
	const char *getNodePath() const;
	static bool canBeReference(const char *path, const Ptr<Node> &node);
};
typedef Ptr<NodeReference> NodeReferencePtr;

class NodeTrigger;
template class UNIGINE_API EventHolder<EventInterfaceInvoker<const Ptr<NodeTrigger> &>>;
template class UNIGINE_API EventInterfaceConnection<EventInterfaceInvoker<const Ptr<NodeTrigger> &>>;
//////////////////////////////////////////////////////////////////////////

class UNIGINE_API NodeTrigger : public Node
{
public:
	static Node::TYPE type() { return Node::NODE_TRIGGER; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<NodeTrigger> create();
	const char *getEnabledCallbackName() const;
	void setEnabledCallbackName(const char *name);
	const char *getPositionCallbackName() const;
	void setPositionCallbackName(const char *name);
	Event<const Ptr<NodeTrigger> &> &getEventEnabled();
	Event<const Ptr<NodeTrigger> &> &getEventPosition();

private:

	EventHolder<EventInterfaceInvoker<const Ptr<NodeTrigger> &>> event_enabled;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<NodeTrigger> &>> event_enabled_connection;
	EventHolder<EventInterfaceInvoker<const Ptr<NodeTrigger> &>> event_position;
	EventInterfaceConnection<EventInterfaceInvoker<const Ptr<NodeTrigger> &>> event_position_connection;
};
typedef Ptr<NodeTrigger> NodeTriggerPtr;

class NodeExternBase;
//////////////////////////////////////////////////////////////////////////

class UNIGINE_API NodeExtern : public Node
{
public:
	static Node::TYPE type() { return Node::NODE_EXTERN; }
	static bool convertible(Node *node) { return (node && node->getType() == type()); }

	static Ptr<NodeExtern> create(int class_id);
	int getClassID();
	NodeExternBase *getNodeExtern() const;
};
typedef Ptr<NodeExtern> NodeExternPtr;


class UNIGINE_API  NodeExternBase : public virtual Base
{
public:
	NodeExternBase();
	NodeExternBase(void * object);
	virtual ~NodeExternBase();
	virtual int getClassID() = 0;
	Ptr<Node> getNode() const;
	Ptr<NodeExtern> getNodeExtern() const;
	typedef NodeExternBase *(*ConstructorFunc)(void *object);
	static void addClassID(int class_id, ConstructorFunc func);
	template <class Type> static void addClassID(int class_id) { addClassID(class_id, constructor<Type>); }
	virtual void updateEnabled();
	virtual void updateTransform();
	virtual const Math::BoundBox &getBoundBox();
	virtual const Math::BoundSphere &getBoundSphere();
	virtual void renderHandler();
	virtual void renderVisualizer();
	virtual void copy(NodeExternBase *node, int is_root);
	virtual void swap(NodeExternBase *node);
	virtual int loadWorld(const Ptr<Xml> &xml);
	virtual int saveWorld(const Ptr<Xml> &xml);
	virtual int saveState(const Ptr<Stream> &stream);
	virtual int restoreState(const Ptr<Stream> &stream);
	static void savePointer(const StreamPtr &stream, NodeExternBase *node);
	static NodeExternBase *restorePointer(const StreamPtr &stream);
private:
	template <class Type> static NodeExternBase *constructor(void *object) { return new Type(object); }
	struct NodeExternData;
	NodeExternData *data;
};
typedef Ptr<NodeExternBase> NodeExternBasePtr;

} // namespace Unigine
