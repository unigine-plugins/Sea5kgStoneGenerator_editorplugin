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

#include <editor/UnigineEditorGlobal.h>

#include <UnigineCallback.h>

#include <QWidget>


////////////////////////////////////////////////////////////////////////////////
// Forward decl.
////////////////////////////////////////////////////////////////////////////////
namespace UnigineEditor { struct RenderWindowPrivate; }

namespace UnigineEditor
{

////////////////////////////////////////////////////////////////////////////////
// RenderWindow.
////////////////////////////////////////////////////////////////////////////////
/// <summary> This class is used to represent a window widget to which an image
/// can be rendered by the Engine. For example, to render node or texture
/// previews, frame sequences, etc.
/// </summary>
class UNIGINE_EDITOR_API RenderWindow : public QWidget
{
	Q_OBJECT
	Q_DISABLE_COPY(RenderWindow)

public:
	/// <summary> Rendering policy for the window that defines when it should be
	/// rendered depending on its visibility and focus status.
	/// </summary>
	enum RENDERING_POLICY
	{
		/// <summary> The window is rendered only when visible.</summary>
		RENDERING_POLICY_WINDOW_VISIBLE = 0,
		/// <summary> The window is rendered only when it is visible and focused.</summary>
		RENDERING_POLICY_WINDOW_VISIBLE_AND_FOCUSED,
		/// <summary> The window is always rendered regardless of its visibility and focus status.</summary>
		RENDERING_POLICY_ALWAYS,
	};

public:
	explicit RenderWindow(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	~RenderWindow() override;
	/// <summary> Event triggered for the Render Window
	/// on Engine::update(). As an alternative you can inherit your
	/// class from the RenderWindow and override
	/// the <see cref="onUpdate"/>() method.
	/// </summary>
	Unigine::Event<> &getEventUpdate();
	/// <summary> Event triggered for the Render Window
	/// on Engine::render(). As an alternative you can inherit your
	/// class from the RenderWindow and override
	/// the <see cref="onRender"/>() method.
	/// </summary>
	Unigine::Event<> &getEventRender();
	/// <summary> Event triggered for the Render Window
	/// on Engine::swap(). As an alternative you can inherit your
	/// class from the RenderWindow and override
	/// the <see cref="onSwap"/>() method.
	/// </summary>
	Unigine::Event<> &getEventSwap();
	/// <summary> Event triggered when the focus
	/// of the Render Window changes.
	/// </summary>
	Unigine::Event<> &getEventFocusChanged();
	/// <summary> Event triggered when the Render Window
	/// becomes focused. As an alternative you
	/// can inherit your class from the RenderWindow and override
	/// the <see cref="focusInEvent"/>() method.
	/// </summary>
	Unigine::Event<> &getEventFocusIn();
	/// <summary> Event triggered when the Render Window
	/// loses focus. As an alternative you can inherit your class
	/// from the RenderWindow and override
	/// the <see cref="focusOutEvent"/>() method.</summary>
	Unigine::Event<> &getEventFocusOut();
	/// <summary> Event triggered when something is dragged
	/// into the Render Window. The event handler function receives
	/// a QDragEnterEvent instance. For more details please
	/// refer to Qt documentation. As an alternative you can inherit
	/// your class from the RenderWindow and override
	/// the <see cref="dragEnterEvent"/>() method.
	/// </summary>
	Unigine::Event<QDragEnterEvent *> &getEventDragEnter();
	/// <summary> Event triggered when something is
	/// dragged within the Render Window. The event handler function
	/// receives a QDragMoveEvent instance. For more details
	/// please refer to Qt documentation. As an alternative you
	/// can inherit your class from the RenderWindow and override
	/// the <see cref="dragMoveEvent"/>() method.
	/// </summary>
	Unigine::Event<QDragMoveEvent *> &getEventDragMove();
	/// <summary> Event triggered when something is
	/// dragged out of the Render Window. The event handler function
	/// receives a QDragLeaveEvent instance. For more details
	/// please refer to Qt documentation. As an alternative you
	/// can inherit your class from the RenderWindow and override
	/// the <see cref="dragLeaveEvent"/>() method.
	/// </summary>
	Unigine::Event<QDragLeaveEvent *> &getEventDragLeave();
	/// <summary>Event triggered when the user drops
	/// something within the Render Window. The event handler function
	/// receives a QDropEvent instance, that contains a proposed
	/// action, available from proposedAction(), for the widget
	/// to either accept or ignore. If the action can be handled
	/// by the widget, you should call the acceptProposedAction()
	/// function. Since the proposed action can be a combination
	/// of Qt::DropAction values, it may be useful to either
	/// select one of these values as a default action or ask
	/// the user to select their preferred action.
	/// If the proposed drop action is not suitable, perhaps
	/// because your custom widget does not support that action,
	/// you can replace it with any of the possible drop actions
	/// by calling setDropAction() with your preferred action.
	/// If you set a value that is not present in the bitwise OR
	/// combination of values returned by possibleActions(), the
	/// default copy action will be used. Once a replacement drop
	/// action has been set, call accept() instead of
	/// acceptProposedAction() to complete the drop operation.
	/// For more details please refer to Qt documentation.
	/// As an alternative you can inherit your class from the
	/// RenderWindow and override
	/// the <see cref="dropEvent"/>() method.
	/// </summary>
	Unigine::Event<QDropEvent *> &getEventDrop();
	/// <summary>Sets rendering policy for the Render Window.
	/// This policy defines when the window should be rendered
	/// depending on its visibility and focus status.
	/// </summary>
	/// <param name="rendering_policy">New rendering policy to be set.</param>
	void setRenderingPolicy(RENDERING_POLICY rendering_policy);
	/// <summary>Returns the current rendering policy for the
	/// Render Window. This policy defines when the window should be
	/// rendered depending on its visibility and focus status
	/// (See <see cref="RENDERING_POLICY"/>).
	/// </summary>
	RENDERING_POLICY getRenderingPolicy() const;

	/// <summary>Sets a value indicating if render buffers are to be
	/// cleared every time the <see cref="do_render"/> method is called.
	/// </summary>
	/// <param name="v"> <b>true</b> to clear render buffers every time the <see cref="do_render"/> method is called; <b>false</b> - not to clear.</param>
	void setClearRenderBuffers(bool v);
	/// <summary>Returns a value indicating if render buffers are to be
	/// cleared every time the <see cref="do_render"/> method is called.
	/// </summary>
	bool isClearRenderBuffers() const;

	QPaintEngine *paintEngine() const final override { return nullptr; }

signals:
	/// <summary> This signal is emitted when the focus has changed
	/// because the user pressed the tab-key, clicked into a widget
	/// or changed the active window.
	/// </summary>
	void focusChanged();

protected:
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define your custom actions to be
	/// performed on Engine::update(). As an alternative to
	/// overriding this method you can use
	/// the Update event (<see cref="getEventUpdate"/>).
	/// </summary>
	virtual void onUpdate() {}
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define your custom actions to be
	/// performed on Engine::render(). As an alternative to
	/// overriding this method you can use
	/// the Render event (<see cref="getEventRender"/>).
	/// </summary>
	virtual void onRender() {}
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define your custom actions to be
	/// performed on Engine::swap(). As an alternative to
	/// overriding this method you can use
	/// the Swap event (<see cref="getEventSwap"/>).
	/// </summary>
	virtual void onSwap() {}

	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define your custom actions to be
	/// performed on receiving various events (QEvent). As an
	/// alternative to overriding this method you can use
	/// the Update event (<see cref="getEventUpdate"/>).
	/// </summary>
	bool event(QEvent *event) override;
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define actions to be performed on
	/// receiving a paint event (QPaintEvent). Paint events are
	/// sent to widgets that need to update themselves. For
	/// more details please refer to Qt documentation.
	/// </summary>
	void paintEvent(QPaintEvent *) final override {}
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define actions to be performed on
	/// receiving a resize event (QResizeEvent). Resize events are
	/// sent to widgets that have been resized. For more details
	/// please refer to Qt documentation. As an alternative to
	/// overriding this method you can use
	/// the Update event (<see cref="getEventUpdate"/>).
	/// </summary>
	void resizeEvent(QResizeEvent *event) override;
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define actions to be performed on
	/// receiving a close event (QCloseEvent). Close events are
	/// sent to widgets that have been closed. For more details
	/// please refer to Qt documentation.
	/// </summary>
	void closeEvent(QCloseEvent *event) override;
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define actions to be performed on
	/// getting focus, i.e., receiving the corresponding focus
	/// event (QFocusEvent). Focus events are sent to widgets
	/// when the keyboard input focus changes. Focus events occur
	/// due to mouse actions, key presses (such as Tab or Backtab),
	/// the window system, popup menus, keyboard shortcuts, or other
	/// application-specific reasons. The reason for a particular
	/// focus event is returned by reason() in the appropriate event
	/// handler. For more details please refer to Qt documentation.
	/// As an alternative to overriding this method you can use
	/// the FocusIn event (<see cref="getEventFocusIn"/>).
	/// </summary>
	void focusInEvent(QFocusEvent *event) override;
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define actions to be performed on
	/// losing focus, i.e., receiving the corresponding
	/// focus event (QFocusEvent). Focus events are sent to widgets
	/// when the keyboard input focus changes. Focus events occur
	/// due to mouse actions, key presses (such as Tab or Backtab),
	/// the window system, popup menus, keyboard shortcuts, or other
	/// application-specific reasons. The reason for a particular
	/// focus event is returned by reason() in the appropriate event
	/// handler. For more details please refer to Qt documentation.
	/// As an alternative to overriding this method you can use
	/// the FocusOut event (<see cref="getEventFocusOut"/>).
	/// </summary>
	void focusOutEvent(QFocusEvent *event) override;
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define actions to be performed
	/// when a drag-and-drop action enters
	/// the Render Window (QDragEnterEvent). The drag enter event
	/// is always immediately followed by a drag move event.
	/// For more details please refer to Qt documentation. As an
	/// alternative to overriding this method you can use
	/// the DragEnter event (<see cref="getEventDragEnter"/>).
	/// </summary>
	void dragEnterEvent(QDragEnterEvent *event) override;
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define actions to be performed when
	/// a drag-and-drop action is in progress (QDragMoveEvent).
	/// The drag move event always immediately follows a drag enter
	/// event. For more details please refer to Qt documentation.
	/// As an alternative to overriding this method you can use
	/// the DragMove event (<see cref="getEventDragMove"/>).
	/// </summary>
	void dragMoveEvent(QDragMoveEvent *event) override;
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define actions to be performed when
	/// a drag-and-drop action leaves the Render Window (QDragLeaveEvent).
	/// For more details please refer to Qt documentation. As an
	/// alternative to overriding this method you can use
	/// the DragLeave event (<see cref="getEventDragLeave"/>).
	/// </summary>
	void dragLeaveEvent(QDragLeaveEvent *event) override;
	/// <summary>You can inherit your class from RenderWindow and
	/// override this method to define actions to be performed when
	/// a drag-and-drop action is completed (QDropEvent). For more
	/// details please refer to Qt documentation. As an alternative
	/// to overriding this method you can use
	/// the Drop event (<see cref="getEventDrop"/>).
	/// </summary>
	void dropEvent(QDropEvent *event) override;

protected:
	bool is_rendering() const;

private:
	void do_update();
	void do_render();
	void do_swap();

private:
	friend struct ::UnigineEditor::RenderWindowPrivate;
	::UnigineEditor::RenderWindowPrivate *d;
};

} // namespace UnigineEditor
