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
#pragma once


#include <editor/UnigineRenderWindow.h>

#include <UnigineGui.h>


////////////////////////////////////////////////////////////////////////////////
// Forward decl.
////////////////////////////////////////////////////////////////////////////////
namespace UnigineEditor { struct EngineGuiWindowPrivate; }


namespace UnigineEditor
{
////////////////////////////////////////////////////////////////////////////////
// EngineGuiWindow.
////////////////////////////////////////////////////////////////////////////////
/// <summary>This class is used to represent a window widget to which an image
/// can be rendered by the Engine with inputs handling by the Engine GUI. For
/// example, to create a curve or a node graph editor of your own. By default
/// EngineGuiWindow creates a Shortcuts exclusive context to process mouse and
/// keyboard events for this window exclusively, without sending them to the
/// common Editor's Shortcuts handling system.
/// </summary>
class UNIGINE_EDITOR_API EngineGuiWindow : public RenderWindow
{
	Q_OBJECT
	Q_DISABLE_COPY(EngineGuiWindow)

public:
	explicit EngineGuiWindow(QWidget *parent = nullptr);
	~EngineGuiWindow() override;

	/// <summary>Returns the current Engine GUI for the window. You can use it to manage UI and user inputs.</summary>
	Unigine::GuiPtr getGui() const;

	/// <summary>Returns the ID of the Shortcuts exclusive context for the Engine
	/// GUI window. By default EngineGuiWindow creates a Shortcuts exclusive context
	/// to process mouse and keyboard events for this window exclusively, without
	/// sending them to the common Editor's Shortcuts handling system.</summary>
	const char *getShortcutsExclusiveContextId() const;
	/// <summary>Creates a new Shortcuts exclusive context for the Engine GUI window.
	/// This context is used to process mouse and keyboard events for this window
	/// exclusively, without sending them to the common Editor's Shortcuts handling
	/// system.
	/// </summary>
	/// <returns> <b>true</b> if the context is created successfully; otherwise, <b>false</b>.</returns>
	bool createShortcutsExclusiveContext(const char *context_id);
	/// <summary>Removes the Shortcuts exclusive context from the window. This
	/// context is used to process mouse and keyboard events for this window
	/// exclusively, without sending them to the common Editor's Shortcuts
	/// handling system.
	/// </summary>
	/// <returns> <b>true</b> if the context is removed successfully; otherwise, <b>false</b>.</returns>
	bool removeShortcutsExclusiveContext();
	/// <summary>Returns a value indicating if the window has its own Shortcuts
	/// exclusive context. This context is used to process mouse and keyboard
	/// events for this window exclusively, without sending them to the common
	/// Editor's Shortcuts handling system.
	/// </summary>
	/// <returns> <b>true</b> if the window has its own Shortcuts exclusive context; otherwise, <b>false</b>.</returns>
	bool hasShortcutsExclusiveContext() const;

protected:
	/// <summary>You can inherit your class from EngineGuiWindow and override
	/// this method to define your custom actions
	/// to be performed on Engine::update().
	/// </summary>
	void onUpdate() override;
	/// <summary>You can inherit your class from EngineGuiWindow and override
	/// this method to define your custom actions
	/// to be performed on Engine::render().
	/// </summary>
	void onRender() override;

	/// <summary>You can inherit your class from EngineGuiWindow and
	/// override this method to define actions to be performed on
	/// losing focus, i.e., receiving the corresponding
	/// focus event (QFocusEvent). Focus events are sent to widgets
	/// when the keyboard input focus changes. Focus events occur
	/// due to mouse actions, key presses (such as Tab or Backtab),
	/// the window system, popup menus, keyboard shortcuts, or other
	/// application-specific reasons. The reason for a particular
	/// focus event is returned by reason() in the appropriate event
	/// handler. For more details please refer to Qt documentation.
	/// </summary>
	void focusOutEvent(QFocusEvent *event) override;
	/// <summary>You can inherit your class from EngineGuiWindow and
	/// override this method to define actions to be performed on
	/// getting focus, i.e., receiving the corresponding focus
	/// event (QFocusEvent). Focus events are sent to widgets
	/// when the keyboard input focus changes. Focus events occur
	/// due to mouse actions, key presses (such as Tab or Backtab),
	/// the window system, popup menus, keyboard shortcuts, or other
	/// application-specific reasons. The reason for a particular
	/// focus event is returned by reason() in the appropriate event
	/// handler. For more details please refer to Qt documentation.
	/// </summary>
	void focusInEvent(QFocusEvent *event) override;

private:
	void update_gui();

	::UnigineEditor::EngineGuiWindowPrivate *const d;
};

} // namespace UnigineEditor
