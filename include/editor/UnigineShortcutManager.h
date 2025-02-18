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

#include <UnigineEvent.h>
#include <UnigineCallback.h>
#include <UnigineInput.h>
#include <UniginePtr.h>

#include "UnigineEditorGlobal.h"

namespace UnigineEditor
{


/// <summary>This class is used to manage shortcuts (hotkeys). The shortcut can be set up to contain all the key presses necessary to describe a keyboard and mouse input combination, including the states of modifier keys such as Shift, Ctrl, Alt, Cmd as well as mouse buttons.</summary>
class UNIGINE_EDITOR_API Shortcut : public Unigine::APIInterface
{
public:

	/// <summary>Modifier match type to be used to activate a shortcut (hotkey combination).</summary>
	enum MODIFIER_MATCH_TYPE
	{
		/// <summary>Exact match - a shortcut (hotkey combination) will be activated only if the specified key/button combination is pressed, while all other buttons and keys are not.</summary>
		MODIFIER_MATCH_TYPE_EXACT = 0,
		/// <summary>Partial match - a shortcut (hotkey combination) will be activated if the specified key/button combination is pressed, other buttons and keys can be also pressed (e.g. the 'Shift' modifier combined with arrow keys increases movement speed in UnigineEditor, but you can also press RMB to rotate the camera).</summary>
		MODIFIER_MATCH_TYPE_PARTIAL,
	};

	/// <summary>Mouse wheel actions.</summary>
	enum MOUSE_WHEEL
	{
		/// <summary>No wheel action.</summary>
		MOUSE_WHEEL_NONE = 0,
		/// <summary>Mouse wheel upward scrolling (vertical).</summary>
		MOUSE_WHEEL_UP,
		/// <summary>Mouse wheel downward scrolling (vertical).</summary>
		MOUSE_WHEEL_DOWN,
		/// <summary>Mouse wheel right scrolling (horizontal).</summary>
		MOUSE_WHEEL_RIGHT,
		/// <summary>Mouse wheel left scrolling (horizontal).</summary>
		MOUSE_WHEEL_LEFT,
	};

	/// <summary>Modifier mask used to identify a set of modifiers.</summary>
	enum MODIFIER_MASK
	{
		/// <summary>Shift key.</summary>
		MODIFIER_MASK_SHIFT = 1 << 0,
		/// <summary>Ctrl key.</summary>
		MODIFIER_MASK_CTRL = 1 << 1,
		/// <summary>Alt key.</summary>
		MODIFIER_MASK_ALT = 1 << 2,
		/// <summary>Command key.</summary>
		MODIFIER_MASK_CMD = 1 << 3,
		/// <summary>Left mouse button.</summary>
		MODIFIER_MASK_MOUSE_LEFT = 1 << 4,
		/// <summary>Right mouse button.</summary>
		MODIFIER_MASK_MOUSE_RIGHT = 1 << 5,
		/// <summary>Middle mouse button.</summary>
		MODIFIER_MASK_MOUSE_MIDDLE = 1 << 6,
		/// <summary>First extra mouse button.</summary>
		MODIFIER_MASK_MOUSE_AUX_0 = 1 << 7,
		/// <summary>Second extra mouse button.</summary>
		MODIFIER_MASK_MOUSE_AUX_1 = 1 << 8,
		/// <summary>Third extra mouse button.</summary>
		MODIFIER_MASK_MOUSE_AUX_2 = 1 << 9,
		/// <summary>Fourth extra mouse button.</summary>
		MODIFIER_MASK_MOUSE_AUX_3 = 1 << 10,
	};

	/// <summary>Mouse mask used to identify mouse buttons currently pressed.</summary>
	enum MOUSE_MASK
	{
		/// <summary>Left mouse button.</summary>
		MOUSE_MASK_LEFT = 1 << 0,
		/// <summary>Middle mouse button.</summary>
		MOUSE_MASK_MIDDLE = 1 << 1,
		/// <summary>Right mouse button.</summary>
		MOUSE_MASK_RIGHT = 1 << 2,
		/// <summary>Mouse double-click.</summary>
		MOUSE_MASK_DCLICK = 1 << 3,
		/// <summary>First auxiliary mouse mask (used for extra buttons).</summary>
		MOUSE_MASK_AUX_0 = 1 << 4,
		/// <summary>Second auxiliary mouse mask (used for extra buttons).</summary>
		MOUSE_MASK_AUX_1 = 1 << 5,
		/// <summary>Third auxiliary mouse mask (used for extra buttons).</summary>
		MOUSE_MASK_AUX_2 = 1 << 6,
		/// <summary>Fourth auxiliary mouse mask (used for extra buttons).</summary>
		MOUSE_MASK_AUX_3 = 1 << 7,
	};
		/// <summary>Returns the ID of the shortcut, that is used to refer to it (e.g., from the ShortcutManager).</summary>
	const char *getID() const;
	/// <summary>Sets the value indicating if the shortcut is enabled (taken into account in the framework of input processing). You can set this value to 'false' to temporarily ignore a specific shortcut without disabling the whole context (<see cref='ShortcutContext::setEnabled'/>).</summary>
	/// <param name='enabled'><b>true</b> to enable the shortcut; <b>false</b> - to make it ignored.</param>
	void setEnabled(bool enabled);
	/// <summary>Returns the value indicating if the shortcut is enabled (taken into account in the framework of input processing). You can set this value to 'false' to temporarily ignore a specific shortcut without disabling the whole context (<see cref='ShortcutContext::setEnabled'/>).</summary>
	bool isEnabled() const;
	/// <summary>Sets the title to be displayed for the shortcut in UnigineEditor.</summary>
	/// <param name='title'>Title text to be set.</param>
	void setTitle(const char *title);
	/// <summary>Returns the title to be displayed for the shortcut in UnigineEditor.</summary>
	const char *getTitle() const;
	/// <summary>Sets the tooltip to be displayed for the shortcut in UnigineEditor.</summary>
	/// <param name='tooltip'>Tooltip text to be set.</param>
	void setTooltip(const char *tooltip);
	/// <summary>Returns the tooltip to be displayed for the shortcut in UnigineEditor.</summary>
	const char *getTooltip() const;
	/// <summary>Sets the key for the shortcut.</summary>
	/// <param name='key'>Key to be set.</param>
	void setKey(Unigine::Input::KEY key);
	/// <summary>Returns the key for the shortcut.</summary>
	Unigine::Input::KEY getKey() const;
	// 'mask' should be MOUSE_MASK::<>
	/// <summary>Sets the mask that defines mouse inputs combination for the shortcut.</summary>
	/// <param name='mask'>Mouse mask to be set (see <see cref='MOUSE_MASK'/>).</param>
	void setMouseButtonMask(int mask);
	/// <summary>Returns the mask that defines mouse inputs combination for the shortcut.</summary>
	int getMouseButtonMask() const;
	/// <summary>Sets the mask that defines the mouse wheel combination for the shortcut <see cref='MOUSE_WHEEL'/>.</summary>
	/// <param name='wheel'>Mask to be set.</param>
	void setMouseWheel(Shortcut::MOUSE_WHEEL wheel);
	/// <summary>Returns the mask that defines the mouse wheel combination for the shortcut <see cref='MOUSE_WHEEL'/>.</summary>
	Shortcut::MOUSE_WHEEL getMouseWheel() const;
	// 'mask' should be made from MODIFIER_MASK::<>
	/// <summary>Sets the modifier mask that defines the set of modifiers to be used for the shortcut <see cref='MODIFIER_MASK'/>.</summary>
	/// <param name='mask'>Mask to be set.</param>
	void setModifierMask(int mask);
	/// <summary>Returns the modifier mask that defines the set of modifiers to be used for the shortcut <see cref='MODIFIER_MASK'/>.</summary>
	int getModifierMask() const;
	/// <summary>Sets the modifier match type to be used for the shortcut (see <see cref='MODIFIER_MATCH_TYPE'/>). It defines whether the shortcut is tolerant to other keys, modifiers, and buttons (will be activated even if they are pressed in addition to the shortcut combination). For example, the 'Shift' modifier combined with arrow keys increases movement speed in UnigineEditor, but you can also press RMB to rotate the camera (because these shortcuts use the PARTIAL type). The default type is EXACT (to activate a shortcut nothing else should be pressed in addition to its combination).</summary>
	/// <param name='type'>Match type to be set.</param>
	void setModifierMatchType(Shortcut::MODIFIER_MATCH_TYPE type);
	/// <summary>Returns the modifier match type to be used for the shortcut (see <see cref='MODIFIER_MATCH_TYPE'/>). It defines whether the shortcut is tolerant to other keys, modifiers, and buttons (will be activated even if they are pressed in addition to the shortcut combination). For example, the 'Shift' modifier combined with arrow keys increases movement speed in UnigineEditor, but you can also press RMB to rotate the camera (because these shortcuts use the PARTIAL type). The default type is EXACT (to activate a shortcut nothing else should be pressed in addition to its combination).</summary>
	Shortcut::MODIFIER_MATCH_TYPE getModifierMatchType() const;
	/// <summary>Sets the value indicating if the shortcut is 'transparent' for input events that have triggered it (passes them further through the Input system). The default value is 'false'.</summary>
	/// <param name='transparent'><b>true</b> to make the shortcut 'transparent' for input events (pass them further); <b>false</b> - to make the shortcut consume input events without passing them further.</param>
	void setTransparent(bool transparent);
	/// <summary>Returns the value indicating if the shortcut is 'transparent' for input events that have triggered it (passes them further through the Input system). The default value is 'false'.</summary>
	bool isTransparent() const;
	/// <summary>Sets the value indicating if the shortcut is to be displayed in UnigineEditor (Windows - Settings - Hotkeys). The default value is 'true'.</summary>
	/// <param name='visible'><b>true</b> to make it displayed in UnigineEditor (Windows - Settings - Hotkeys); <b>false</b> - to make it hidden.</param>
	void setVisible(bool visible);
	/// <summary>Returns the value indicating if the shortcut is to be displayed in UnigineEditor (Windows - Settings - Hotkeys). The default value is 'true'.</summary>
	bool isVisible() const;
	/// <summary>Sets the value indicating if the shortcut is to act like a modifier (e.g., can be used to define how to interpret the 'Ctrl' key).</summary>
	/// <param name='enabled'><b>true</b> to make the shortcut act like a modifier; <b>false</b> - to make it act like a shortcut.</param>
	void setModeModifierEnabled(bool enabled);
	/// <summary>Returns the value indicating if the shortcut is to act like a modifier (e.g., can be used to define how to interpret the 'Ctrl' key).</summary>
	bool isModeModifierEnabled() const;
	/// <summary>Adds a shortcut with the specified ID as a friend for the shortcut. Friends can be activated together with the shortcut (in case of identical concurrent shortcuts the context priority decides - see <see cref='ShortcutContext::setPriority'/>).</summary>
	/// <param name='friend_shortcut'>ID of the friend shortcut to be added as a friend.</param>
	bool addFriend(const Unigine::Ptr<Shortcut> &friend_shortcut);
	/// <summary>Removes a shortcut with the specified ID from the list of friends. Friends can be activated together with the shortcut (in case of identical concurrent shortcuts the context priority decides - see <see cref='ShortcutContext::setPriority'/>).</summary>
	/// <param name='friend_shortcut'>ID of the friend shortcut to be removed.</param>
	bool removeFriend(const Unigine::Ptr<Shortcut> &friend_shortcut);
	/// <summary>Returns the shortcut combination as a text string (e.g., 'Ctrl + A').</summary>
	Unigine::String toString() const;
	/// <summary>Returns a value indicating if the shortcut is currently pressed and held down.</summary>
	bool isPressed() const;
	/// <summary>Returns a value indicating if the shortcut has been pressed.</summary>
	bool isDown() const;
	/// <summary>Returns a value indicating if the shortcut has been released.</summary>
	bool isUp() const;
	/// <summary>Event triggered on changing the shortcut (e.g., setting a new combination in UnigineEditor).</summary>
	Unigine::Event<> &getEventChanged();
	/// <summary>Event triggered when the shortcut is pressed.</summary>
	Unigine::Event<> &getEventPressed();
	/// <summary>Event triggered on pressing the shortcut combination.</summary>
	Unigine::Event<> &getEventDown();
	/// <summary>Event triggered on releasing the shortcut combination.</summary>
	Unigine::Event<> &getEventUp();
};
typedef Unigine::Ptr<Shortcut> ShortcutPtr;


/// <summary>This class is used to manage a shortcut context (add, remove shortcuts, define interaction with other contexts).</summary>
class UNIGINE_EDITOR_API ShortcutContext : public Unigine::APIInterface
{
public:

	/// <summary>Context type, defines the way the shortcuts of this and other contexts are processed when this context is active.</summary>
	enum TYPE
	{
		/// <summary>Shared context, when active this type of context does not block shortcuts from other contexts.</summary>
		TYPE_SHARED = 0,
		/// <summary>Exclusive context, when active this type of context grabs shortcuts processing blocking shortcuts of other contexts.</summary>
		TYPE_EXCLUSIVE,
	};
	// Shortcut
	/// <summary>Creates a new shortcut with the given ID in the context and returns the created shortcut.</summary>
	/// <param name='shortcut_id'>ID of the shortcut to be created.</param>
	Unigine::Ptr<Shortcut> createShortcut(const char *shortcut_id);
	/// <summary>Removes the shortcut with the given ID from the context.</summary>
	/// <param name='shortcut_id'>ID of the shortcut to be removed.</param>
	/// <returns>true if the shortcut was removed successfully.</returns>
	bool removeShortcut(const char *shortcut_id);
	/// <summary>Returns a value indicating if a shortcut with the given ID exists in the context.</summary>
	/// <param name='shortcut_id'>ID of the shortcut to be checked.</param>
	bool hasShortcut(const char *shortcut_id);
	/// <summary>Returns the shortcut with the given ID.</summary>
	/// <param name='shortcut_id'>ID of the shortcut to be retrieved.</param>
	Unigine::Ptr<Shortcut> getShortcut(const char *shortcut_id);
	/// <summary>Collects all shortcuts of the context and puts them to the specified output vector.</summary>
	/// <param name='shortcuts'>Output vector, to receive the list of shortcuts.</param>
	void getShortcuts(Unigine::Vector<Unigine::Ptr<Shortcut>> &shortcuts);

	/// <summary>Sets the value indicating if the context is enabled and can become active. This parameter (unlike the <see cref='setActive'/>) can be changed from anywhere (not only by the context creator). For example, from a plugin to use the same shortcuts as the Editor by simply disabling the unwanted context (you can also disable unwanted shortcuts individually via <see cref='Shortcut::setEnabled'/>).</summary>
	/// <param name='enabled'>Value indicating if the context is enabled.</param>
	void setEnabled(bool enabled);
	/// <summary>Returns the value indicating if the context is enabled and can become active. This parameter (unlike the <see cref='setActive'/>) can be changed from anywhere (not only by the context creator). For example, from a plugin to use the same shortcuts as the Editor by simply disabling the unwanted context (you can also disable unwanted shortcuts individually via <see cref='Shortcut::setEnabled'/>).</summary>
	bool isEnabled() const;
	/// <summary>Sets the value indicating if the context is currently active (its shortcuts are taken into account in the framework of input processing). This parameter can only be changed by the context creator.</summary>
	/// <param name='active'>Value indicating if the context is active.</param>
	void setActive(bool active);
	/// <summary>Returns the value indicating if the context is currently active (its shortcuts are taken into account in the framework of input processing). This parameter can only be changed by the context creator.</summary>
	bool isActive() const;
	/// <summary>Returns the ID of the context.</summary>
	const char *getID() const;
	/// <summary>Returns the title of the context to be displayed in UnigineEditor.</summary>
	const char *getTitle() const;
	/// <summary>Returns the type of the context, defining the way the shortcuts of this and other contexts are processed when this context is active.</summary>
	ShortcutContext::TYPE getType() const;
	/// <summary>Returns the priority of the context. The priority defines which of the identical shortcuts of several active concurring contexts are to be processed (a context with a higher priority value takes precedence over others).</summary>
	int getPriority() const;
};
typedef Unigine::Ptr<ShortcutContext> ShortcutContextPtr;

//////////////////////////////////////////////////////////////////////////

/// <summary>This class is used to manage all shortcuts (hotkeys and combinations) and shortcut contexts that you usually see in Windows - Settings - Hotkeys.</summary>
class UNIGINE_EDITOR_API ShortcutManager
{
public:
	static bool isInitialized();
	// Context
	/// <summary>Creates a new context using the given parameters (ID, title, type, and priority).</summary>
	/// <param name='context_id'>ID of the context to be created.</param>
	/// <param name='title'>Title of the context to be displayed in UnigineEditor.</param>
	/// <param name='context_type'>Type of the context (shared or exclusive).</param>
	/// <param name='priority'>Priority of the context (a context with a higher priority value takes precedence over others).</param>
	static Unigine::Ptr<ShortcutContext> createContext(const char *context_id, const char *title, ShortcutContext::TYPE context_type = ShortcutContext::TYPE_SHARED, int priority = 0);
	// It also removes all the associated shortcuts with it.
	/// <summary>Removes the context with the given ID (all its shortcuts are removed as well).</summary>
	/// <param name='context_id'>ID of the context to be removed.</param>
	/// <returns>true if the context was removed successfully.</returns>
	static bool removeContext(const char *context_id);
	/// <summary>Returns a value indicating if a context with the given ID exists.</summary>
	/// <param name='context_id'>ID of the context to be checked.</param>
	static bool hasContext(const char *context_id);
	/// <summary>Returns the context with the given ID.</summary>
	/// <param name='context_id'>ID of the context to be retrieved.</param>
	static Unigine::Ptr<ShortcutContext> getContext(const char *context_id);
	/// <summary>Collects all registered contexts and puts them to the specified output vector.</summary>
	/// <param name='contexts'>Output vector, to receive the list of contexts.</param>
	static void getContexts(Unigine::Vector<Unigine::Ptr<ShortcutContext>> &contexts);
	// Events
	/// <summary>Event triggered on context creation.</summary>
	static Unigine::Event<const Unigine::Ptr<ShortcutContext> &> &getEventContextCreated();
	/// <summary>Event triggered on context removal.</summary>
	static Unigine::Event<const char *> &getEventContextRemoved();
	/// <summary>Event triggered on shortcut creation.</summary>
	static Unigine::Event<const Unigine::Ptr<ShortcutContext> &, const Unigine::Ptr<Shortcut> &> &getEventShortcutCreated();
	/// <summary>Event triggered on shortcut removal.</summary>
	static Unigine::Event<const char *, const char *> &getEventShortcutRemoved();
	/// <summary>Event triggered on changing keyboard layout.</summary>
	static Unigine::Event<> &getEventKeyboardLayoutChanged();
};

} // namespace UnigineEditor
template class UNIGINE_EDITOR_API Unigine::EventHolder<Unigine::EventInterfaceInvoker<const Unigine::Ptr<UnigineEditor::ShortcutContext> &>>;
template class UNIGINE_EDITOR_API Unigine::EventInterfaceConnection<Unigine::EventInterfaceInvoker<const Unigine::Ptr<UnigineEditor::ShortcutContext> &>>;
template class UNIGINE_EDITOR_API Unigine::EventHolder<Unigine::EventInterfaceInvoker<const Unigine::Ptr<UnigineEditor::ShortcutContext> &, const Unigine::Ptr<UnigineEditor::Shortcut> &>>;
template class UNIGINE_EDITOR_API Unigine::EventInterfaceConnection<Unigine::EventInterfaceInvoker<const Unigine::Ptr<UnigineEditor::ShortcutContext> &, const Unigine::Ptr<UnigineEditor::Shortcut> &>>;
