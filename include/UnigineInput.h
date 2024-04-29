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

#include "UnigineBase.h"
#include "UnigineImage.h"
#include "UniginePtr.h"
#include "UnigineMathLib.h"
#include "UnigineMaterial.h"

namespace Unigine
{

class InputGamePad;
class InputVRDevice;
class InputVRHead;
class InputVRController;
class InputVRTracker;
class InputVRBaseStation;
class InputJoystick;
class InputEvent;
class InputEventMouseButton;
class InputEventKeyboard;
class InputEventTouch;
class InputEventPadButton;
class InputEventPadTouchMotion;
class InputEventJoyButton;
class InputEventJoyPovMotion;
class InputEventVRButton;
class InputEventVRButtonTouch;
int inputEventsFilterFunc(Ptr<InputEvent> &e);
//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Input
{
public:
	static int isInitialized();

	enum MOUSE_HANDLE
	{
		MOUSE_HANDLE_GRAB = 0,
		MOUSE_HANDLE_SOFT,
		MOUSE_HANDLE_USER,
	};

	enum MOUSE_BUTTON
	{
		MOUSE_BUTTON_UNKNOWN = 0,
		MOUSE_BUTTON_LEFT,
		MOUSE_BUTTON_MIDDLE,
		MOUSE_BUTTON_RIGHT,
		MOUSE_BUTTON_DCLICK,
		MOUSE_BUTTON_AUX_0,
		MOUSE_BUTTON_AUX_1,
		MOUSE_BUTTON_AUX_2,
		MOUSE_BUTTON_AUX_3,
		MOUSE_NUM_BUTTONS,
	};

	enum MODIFIER
	{
		MODIFIER_LEFT_SHIFT = 0,
		MODIFIER_RIGHT_SHIFT,
		MODIFIER_LEFT_CTRL,
		MODIFIER_RIGHT_CTRL,
		MODIFIER_LEFT_ALT,
		MODIFIER_RIGHT_ALT,
		MODIFIER_LEFT_CMD,
		MODIFIER_RIGHT_CMD,
		MODIFIER_NUM_LOCK,
		MODIFIER_CAPS_LOCK,
		MODIFIER_SCROLL_LOCK,
		MODIFIER_ALT_GR,
		MODIFIER_ANY_SHIFT,
		MODIFIER_ANY_CTRL,
		MODIFIER_ANY_ALT,
		MODIFIER_ANY_CMD,
		MODIFIER_NONE,
		NUM_MODIFIERS,
	};

	enum
	{
		NUM_TOUCHES = 16,
	};

	enum KEY : unsigned int
	{
		KEY_UNKNOWN = 0,
		KEY_ESC,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_PRINTSCREEN,
		KEY_SCROLL_LOCK,
		KEY_PAUSE,
		KEY_BACK_QUOTE,
		KEY_DIGIT_1,
		KEY_DIGIT_2,
		KEY_DIGIT_3,
		KEY_DIGIT_4,
		KEY_DIGIT_5,
		KEY_DIGIT_6,
		KEY_DIGIT_7,
		KEY_DIGIT_8,
		KEY_DIGIT_9,
		KEY_DIGIT_0,
		KEY_MINUS,
		KEY_EQUALS,
		KEY_BACKSPACE,
		KEY_TAB,
		KEY_Q,
		KEY_W,
		KEY_E,
		KEY_R,
		KEY_T,
		KEY_Y,
		KEY_U,
		KEY_I,
		KEY_O,
		KEY_P,
		KEY_LEFT_BRACKET,
		KEY_RIGHT_BRACKET,
		KEY_ENTER,
		KEY_CAPS_LOCK,
		KEY_A,
		KEY_S,
		KEY_D,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_SEMICOLON,
		KEY_QUOTE,
		KEY_BACK_SLASH,
		KEY_LEFT_SHIFT,
		KEY_LESS,
		KEY_Z,
		KEY_X,
		KEY_C,
		KEY_V,
		KEY_B,
		KEY_N,
		KEY_M,
		KEY_COMMA,
		KEY_DOT,
		KEY_SLASH,
		KEY_RIGHT_SHIFT,
		KEY_LEFT_CTRL,
		KEY_LEFT_CMD,
		KEY_LEFT_ALT,
		KEY_SPACE,
		KEY_RIGHT_ALT,
		KEY_RIGHT_CMD,
		KEY_MENU,
		KEY_RIGHT_CTRL,
		KEY_INSERT,
		KEY_DELETE,
		KEY_HOME,
		KEY_END,
		KEY_PGUP,
		KEY_PGDOWN,
		KEY_UP,
		KEY_LEFT,
		KEY_DOWN,
		KEY_RIGHT,
		KEY_NUM_LOCK,
		KEY_NUMPAD_DIVIDE,
		KEY_NUMPAD_MULTIPLY,
		KEY_NUMPAD_MINUS,
		KEY_NUMPAD_DIGIT_7,
		KEY_NUMPAD_DIGIT_8,
		KEY_NUMPAD_DIGIT_9,
		KEY_NUMPAD_PLUS,
		KEY_NUMPAD_DIGIT_4,
		KEY_NUMPAD_DIGIT_5,
		KEY_NUMPAD_DIGIT_6,
		KEY_NUMPAD_DIGIT_1,
		KEY_NUMPAD_DIGIT_2,
		KEY_NUMPAD_DIGIT_3,
		KEY_NUMPAD_ENTER,
		KEY_NUMPAD_DIGIT_0,
		KEY_NUMPAD_DOT,
		KEY_ANY_SHIFT,
		KEY_ANY_CTRL,
		KEY_ANY_ALT,
		KEY_ANY_CMD,
		KEY_ANY_UP,
		KEY_ANY_LEFT,
		KEY_ANY_DOWN,
		KEY_ANY_RIGHT,
		KEY_ANY_ENTER,
		KEY_ANY_DELETE,
		KEY_ANY_INSERT,
		KEY_ANY_HOME,
		KEY_ANY_END,
		KEY_ANY_PGUP,
		KEY_ANY_PGDOWN,
		KEY_ANY_DIGIT_1,
		KEY_ANY_DIGIT_2,
		KEY_ANY_DIGIT_3,
		KEY_ANY_DIGIT_4,
		KEY_ANY_DIGIT_5,
		KEY_ANY_DIGIT_6,
		KEY_ANY_DIGIT_7,
		KEY_ANY_DIGIT_8,
		KEY_ANY_DIGIT_9,
		KEY_ANY_DIGIT_0,
		KEY_ANY_MINUS,
		KEY_ANY_EQUALS,
		KEY_ANY_DOT,
		NUM_KEYS,
	};

	enum DEVICE
	{
		DEVICE_UNKNOWN = 0,
		DEVICE_GAME_CONTROLLER,
		DEVICE_WHEEL,
		DEVICE_ARCADE_STICK,
		DEVICE_FLIGHT_STICK,
		DEVICE_DANCE_PAD,
		DEVICE_GUITAR,
		DEVICE_DRUM_KIT,
		DEVICE_VR,
	};

	enum GAMEPAD_BUTTON
	{
		GAMEPAD_BUTTON_A = 0,
		GAMEPAD_BUTTON_B,
		GAMEPAD_BUTTON_X,
		GAMEPAD_BUTTON_Y,
		GAMEPAD_BUTTON_BACK,
		GAMEPAD_BUTTON_START,
		GAMEPAD_BUTTON_DPAD_UP,
		GAMEPAD_BUTTON_DPAD_DOWN,
		GAMEPAD_BUTTON_DPAD_LEFT,
		GAMEPAD_BUTTON_DPAD_RIGHT,
		GAMEPAD_BUTTON_THUMB_LEFT,
		GAMEPAD_BUTTON_THUMB_RIGHT,
		GAMEPAD_BUTTON_SHOULDER_LEFT,
		GAMEPAD_BUTTON_SHOULDER_RIGHT,
		GAMEPAD_BUTTON_GUIDE,
		GAMEPAD_BUTTON_MISC1,
		GAMEPAD_BUTTON_TOUCHPAD,
		NUM_GAMEPAD_BUTTONS,
	};

	enum GAMEPAD_AXIS
	{
		GAMEPAD_AXIS_LEFT_X = 0,
		GAMEPAD_AXIS_LEFT_Y,
		GAMEPAD_AXIS_RIGHT_X,
		GAMEPAD_AXIS_RIGHT_Y,
		GAMEPAD_AXIS_LEFT_TRIGGER,
		GAMEPAD_AXIS_RIGHT_TRIGGER,
		NUM_GAMEPAD_AXES,
	};

	enum VR_BUTTON
	{
		VR_BUTTON_SYSTEM_LEFT,
		VR_BUTTON_SYSTEM_RIGHT,
		VR_BUTTON_A,
		VR_BUTTON_B,
		VR_BUTTON_X,
		VR_BUTTON_Y,
		VR_BUTTON_GRIP_LEFT,
		VR_BUTTON_AXIS_0_LEFT,
		VR_BUTTON_AXIS_1_LEFT,
		VR_BUTTON_AXIS_2_LEFT,
		VR_BUTTON_AXIS_3_LEFT,
		VR_BUTTON_AXIS_4_LEFT,
		VR_BUTTON_GRIP_RIGHT,
		VR_BUTTON_AXIS_0_RIGHT,
		VR_BUTTON_AXIS_1_RIGHT,
		VR_BUTTON_AXIS_2_RIGHT,
		VR_BUTTON_AXIS_3_RIGHT,
		VR_BUTTON_AXIS_4_RIGHT,
		VR_BUTTON_DPAD_UP,
		VR_BUTTON_DPAD_DOWN,
		VR_BUTTON_DPAD_LEFT,
		VR_BUTTON_DPAD_RIGHT,
		VR_BUTTON_PROXIMITY_SENSOR,
		VR_BUTTON_APPLICATION,
		NUM_VR_BUTTONS,
	};

	enum JOYSTICK_POV
	{
		JOYSTICK_POV_NOT_PRESSED = 0,
		JOYSTICK_POV_UP,
		JOYSTICK_POV_UP_RIGHT,
		JOYSTICK_POV_RIGHT,
		JOYSTICK_POV_DOWN_RIGHT,
		JOYSTICK_POV_DOWN,
		JOYSTICK_POV_DOWN_LEFT,
		JOYSTICK_POV_LEFT,
		JOYSTICK_POV_UP_LEFT,
	};
	static bool isModifierEnabled(Input::MODIFIER modifier);
	static const char *getModifierName(Input::MODIFIER modifier);
	static Input::MODIFIER getModifierByName(const char *name);
	static bool isKeyPressed(Input::KEY key);
	static bool isKeyDown(Input::KEY key);
	static bool isKeyUp(Input::KEY key);
	static bool isKeyText(Input::KEY key);
	static Ptr<InputEventKeyboard> getKeyEvent(Input::KEY key);
	static int getKeyEvents(Input::KEY key, Vector<Ptr<InputEventKeyboard>> &events);
	static const char *getKeyLocalName(Input::KEY key);
	static const char *getKeyName(Input::KEY key);
	static Input::KEY getKeyByName(const char *name);
	static unsigned int keyToUnicode(Input::KEY key);
	static Input::KEY unicodeToKey(unsigned int unicode);
	static bool isMouseButtonDown(Input::MOUSE_BUTTON button);
	static bool isMouseButtonPressed(Input::MOUSE_BUTTON button);
	static bool isMouseButtonUp(Input::MOUSE_BUTTON button);
	static Ptr<InputEventMouseButton> getMouseButtonEvent(Input::MOUSE_BUTTON button);
	static int getMouseButtonEvents(Input::MOUSE_BUTTON button, Vector<Ptr<InputEventMouseButton>> &events);
	static Math::ivec2 getForceMousePosition();
	static void setMousePosition(const Math::ivec2 &position);
	static Math::ivec2 getMousePosition();
	static Math::ivec2 getMouseDeltaPosition();
	static Math::ivec2 getMouseDeltaRaw();
	static int getMouseWheel();
	static int getMouseWheelHorizontal();
	static const char *getMouseButtonName(Input::MOUSE_BUTTON button);
	static Input::MOUSE_BUTTON getMouseButtonByName(const char *name);
	static void setMouseHandle(Input::MOUSE_HANDLE handle);
	static Input::MOUSE_HANDLE getMouseHandle();
	static bool isTouchDown(int index);
	static bool isTouchPressed(int index);
	static bool isTouchUp(int index);
	static Math::ivec2 getTouchPosition(int index);
	static Math::ivec2 getTouchDelta(int index);
	static Ptr<InputEventTouch> getTouchEvent(int index);
	static int getTouchEvents(int index, Vector<Ptr<InputEventTouch>> &events);
	static int getNumGamePads();
	static Ptr<InputGamePad> getGamePad(int num);
	static int getNumVRDevices();
	static Ptr<InputVRDevice> getVRDevice(int num);
	static Ptr<InputVRHead> getVRHead();
	static Ptr<InputVRController> getVRControllerLeft();
	static Ptr<InputVRController> getVRControllerRight();
	static Ptr<InputVRController> getVRControllerTreadmill();
	static int getNumJoysticks();
	static Ptr<InputJoystick> getJoystick(int num);
	static bool isEmptyClipboard();
	static void setClipboard(const char *clipboard);
	static const char *getClipboard();
	static void setMouseGrab(bool grab);
	static bool isMouseGrab();
	static void setMouseCursorHide(bool hide);
	static bool isMouseCursorHide();
	static void setMouseCursorSystem(bool system);
	static bool isMouseCursorSystem();
	static void setMouseCursorNeedUpdate(bool update);
	static bool isMouseCursorNeedUpdate();
	static void setMouseCursorSkinCustom(const Ptr<Image> &image);
	static void setMouseCursorSkinSystem();
	static void setMouseCursorSkinDefault();
	static void setMouseCursorCustom(const Ptr<Image> &image, int x = 0, int y = 0);
	static void clearMouseCursorCustom();
	static void updateMouseCursor();
	static Event<Input::MOUSE_BUTTON> &getEventMouseDown();
	static Event<Input::MOUSE_BUTTON> &getEventMouseUp();
	static Event<int> &getEventMouseWheel();
	static Event<int> &getEventMouseWheelHorizontal();
	static Event<int, int> &getEventMouseMotion();
	static Event<Input::KEY> &getEventKeyDown();
	static Event<Input::KEY> &getEventKeyUp();
	static Event<unsigned int> &getEventKeyRepeat();
	static Event<unsigned int> &getEventTextPress();
	static Event<int> &getEventTouchDown();
	static Event<int> &getEventTouchUp();
	static Event<int> &getEventTouchMotion();
	static Event<int> &getEventGamepadConnected();
	static Event<int> &getEventGamepadDisconnected();
	static Event<int, Input::GAMEPAD_BUTTON> &getEventGamepadButtonDown();
	static Event<int, Input::GAMEPAD_BUTTON> &getEventGamepadButtonUp();
	static Event<int, Input::GAMEPAD_AXIS> &getEventGamepadAxisMotion();
	static Event<int, int, int> &getEventGamepadTouchDown();
	static Event<int, int, int> &getEventGamepadTouchUp();
	static Event<int, int, int> &getEventGamepadTouchMotion();
	static Event<int> &getEventVrDeviceConnected();
	static Event<int> &getEventVrDeviceDisconnected();
	static Event<int, Input::VR_BUTTON> &getEventVrDeviceButtonDown();
	static Event<int, Input::VR_BUTTON> &getEventVrDeviceButtonUp();
	static Event<int, Input::VR_BUTTON> &getEventVrDeviceButtonTouchDown();
	static Event<int, Input::VR_BUTTON> &getEventVrDeviceButtonTouchUp();
	static Event<int, int> &getEventVrDeviceAxisMotion();
	static Event<int> &getEventJoyConnected();
	static Event<int> &getEventJoyDisconnected();
	static Event<int, int> &getEventJoyButtonDown();
	static Event<int, int> &getEventJoyButtonUp();
	static Event<int, int> &getEventJoyAxisMotion();
	static Event<int, Input::JOYSTICK_POV> &getEventJoyPovMotion();
	static Event<const Ptr<InputEvent> &> &getEventImmediateInput();
	static int getEventsBuffer(int frame, Vector<Ptr<InputEvent>> &events);
	static void sendEvent(const Ptr<InputEvent> &e);
	static void setEventsFilter(int (*func)(Ptr<InputEvent> &e));
};


class UNIGINE_API InputGamePad : public APIInterface
{
public:

	enum MODEL_TYPE
	{
		MODEL_TYPE_UNKNOWN = 0,
		MODEL_TYPE_XBOX_360,
		MODEL_TYPE_XBOX_ONE,
		MODEL_TYPE_PS3,
		MODEL_TYPE_PS4,
		MODEL_TYPE_PS5,
	};
	bool isAvailable() const;
	int getNumber() const;
	int getPlayerIndex() const;
	const char *getName() const;
	Input::DEVICE getDeviceType() const;
	InputGamePad::MODEL_TYPE getModelType() const;
	void setFilter(float filter);
	float getFilter() const;
	Math::vec2 getAxesLeft() const;
	Math::vec2 getAxesLeftDelta() const;
	Math::vec2 getAxesRight() const;
	Math::vec2 getAxesRightDelta() const;
	float getTriggerLeft() const;
	float getTriggerLeftDelta() const;
	float getTriggerRight() const;
	float getTriggerRightDelta() const;
	bool isButtonPressed(Input::GAMEPAD_BUTTON button) const;
	bool isButtonDown(Input::GAMEPAD_BUTTON button) const;
	bool isButtonUp(Input::GAMEPAD_BUTTON button) const;
	int getNumTouches() const;
	int getNumTouchFingers(int touch) const;
	bool isTouchPressed(int touch, int finger) const;
	bool isTouchDown(int touch, int finger) const;
	bool isTouchUp(int touch, int finger) const;
	Math::vec2 getTouchPosition(int touch, int finger) const;
	Math::vec2 getTouchDelta(int touch, int finger) const;
	float getTouchPressure(int touch, int finger) const;
	Ptr<InputEventPadButton> getButtonEvent(Input::GAMEPAD_BUTTON button) const;
	int getButtonEvents(Input::GAMEPAD_BUTTON button, Vector<Ptr<InputEventPadButton>> &events);
	void setVibration(float low_frequency, float high_frequency, float duration_ms = 100.0f);
};
typedef Ptr<InputGamePad> InputGamePadPtr;


class UNIGINE_API InputVRDevice : public APIInterface
{
public:
	static bool convertible(InputVRDevice *obj) { return obj != nullptr; }

	enum TYPE
	{
		INPUT_VR_UNKNOWN,
		INPUT_VR_DEVICE,
		INPUT_VR_HEAD,
		INPUT_VR_CONTROLLER,
		INPUT_VR_TRACKER,
		INPUT_VR_BASE_STATION,
		NUM_TYPES,
	};
	bool isAvailable() const;
	int getNumber() const;
	const char *getName() const;
	Input::DEVICE getDeviceType() const;
	InputVRDevice::TYPE getType() const;
	const char *getDeviceModelName() const;
	bool hasYawDrift() const;
	bool isCharging() const;
	bool hasBattery() const;
	bool canReportBatteryValue() const;
	float getBatteryValue() const;
	String getModelNumber() const;
	String getSerialNumber() const;
	String getManufacturerName() const;
	unsigned long long getHardwareRevision() const;
	unsigned long long getFirmwareVersion() const;
	Math::Mat4 getWorldTransform() const;
	Math::mat4 getTransform() const;
	Math::vec3 getLinearVelocity() const;
	Math::vec3 getAngularVelocity() const;
	Math::vec3 getAngularAcceleration() const;
	bool isTransformValid() const;
	int getNumModels() const;
	Math::mat4 getModelTransform(int num) const;
	Math::Mat4 getModelWorldTransform(int num) const;
	Ptr<Mesh> getModelMesh(int num);
	Ptr<Texture> getModelTexture(int num);
	const char *getModelName(int num);
	Ptr<Mesh> getCombinedModelMesh() const;
	Ptr<Texture> getCombinedModelTexture() const;
	const char *getCombinedModelName() const;
};
typedef Ptr<InputVRDevice> InputVRDevicePtr;


class UNIGINE_API InputVRHead : public InputVRDevice
{
public:
	static bool convertible(InputVRDevice *obj) { return obj && obj->getType() == InputVRDevice::INPUT_VR_HEAD; }

	enum MODEL_TYPE
	{
		MODEL_TYPE_UNKNOWN,
		MODEL_TYPE_OCULUS_BEGIN,
		MODEL_TYPE_OCULUS_DK2 = MODEL_TYPE_OCULUS_BEGIN,
		MODEL_TYPE_OCULUS_CB,
		MODEL_TYPE_OCULUS_OTHER,
		MODEL_TYPE_OCULUS_E3_2015,
		MODEL_TYPE_OCULUS_ES06,
		MODEL_TYPE_OCULUS_ES09,
		MODEL_TYPE_OCULUS_ES11,
		MODEL_TYPE_OCULUS_RIFT,
		MODEL_TYPE_OCULUS_RIFT_S,
		MODEL_TYPE_OCULUS_END = MODEL_TYPE_OCULUS_RIFT_S,
		MODEL_TYPE_VARJO_BEGIN,
		MODEL_TYPE_VARJO_VR_1 = MODEL_TYPE_VARJO_BEGIN,
		MODEL_TYPE_VARJO_XR_1,
		MODEL_TYPE_VARJO_VR_2,
		MODEL_TYPE_VARJO_VR_2_PRO,
		MODEL_TYPE_VARJO_VR_3,
		MODEL_TYPE_VARJO_XR_3,
		MODEL_TYPE_VARJO_AERO,
		MODEL_TYPE_VARJO_END = MODEL_TYPE_VARJO_AERO,
		MODEL_TYPE_OPENVR_BEGIN,
		MODEL_TYPE_OPENVR_HTC_VIVE = MODEL_TYPE_OPENVR_BEGIN,
		MODEL_TYPE_OPENVR_HTC_VIVE_PRO,
		MODEL_TYPE_OPENVR_HTC_FOCUS,
		MODEL_TYPE_OPENVR_VALVE_INDEX,
		MODEL_TYPE_OPENVR_END = MODEL_TYPE_OPENVR_VALVE_INDEX,
		NUM_MODEL_TYPES,
	};
	InputVRHead::MODEL_TYPE getModelType() const;
	bool hasButtons() const;
	void setTrackingPositionEnabled(bool enabled);
	bool isTrackingPositionEnabled() const;
	void setTrackingRotationEnabled(bool enabled);
	bool isTrackingRotationEnabled() const;
	bool isButtonPressed(Input::VR_BUTTON button) const;
	bool isButtonDown(Input::VR_BUTTON button) const;
	bool isButtonUp(Input::VR_BUTTON button) const;
	Ptr<InputEventVRButton> getButtonEvent(Input::VR_BUTTON button) const;
	int getButtonEvents(Input::VR_BUTTON button, Vector<Ptr<InputEventVRButton>> &events);
};
typedef Ptr<InputVRHead> InputVRHeadPtr;


class UNIGINE_API InputVRTracker : public InputVRDevice
{
public:
	static bool convertible(InputVRDevice *obj) { return obj && obj->getType() == InputVRDevice::INPUT_VR_TRACKER; }

	enum MODEL_TYPE
	{
		MODEL_TYPE_UNKNOWN = 0,
		MODEL_TYPE_HTC_VIVE,
		NUM_MODEL_TYPES,
	};
	InputVRTracker::MODEL_TYPE getModelType() const;
};
typedef Ptr<InputVRTracker> InputVRTrackerPtr;


class UNIGINE_API InputVRBaseStation : public InputVRDevice
{
public:
	static bool convertible(InputVRDevice *obj) { return obj && obj->getType() == InputVRDevice::INPUT_VR_BASE_STATION; }

	enum MODEL_TYPE
	{
		MODEL_TYPE_UNKNOWN = 0,
		MODEL_TYPE_HTC_VIVE,
		MODEL_TYPE_VALVE,
		NUM_MODEL_TYPES,
	};
	InputVRBaseStation::MODEL_TYPE getModelType() const;
};
typedef Ptr<InputVRBaseStation> InputVRBaseStationPtr;


class UNIGINE_API InputVRController : public InputVRDevice
{
public:
	static bool convertible(InputVRDevice *obj) { return obj && obj->getType() == InputVRDevice::INPUT_VR_CONTROLLER; }

	enum MODEL_TYPE
	{
		MODEL_TYPE_UNKNOWN = 0,
		MODEL_TYPE_HTC_VIVE,
		MODEL_TYPE_OCULUS_RIFT,
		MODEL_TYPE_VALVE_KNUCKLES,
		NUM_MODEL_TYPES,
	};
	InputVRController::MODEL_TYPE getModelType() const;
	void setFilter(float filter);
	float getFilter() const;

	enum CONTROLLER_TYPE
	{
		CONTROLLER_TYPE_UNKNOWN,
		CONTROLLER_TYPE_HAND_LEFT,
		CONTROLLER_TYPE_HAND_RIGHT,
		CONTROLLER_TYPE_TREADMILL,
		NUM_CONTROLLER_TYPES,
	};
	InputVRController::CONTROLLER_TYPE getControllerType() const;

	enum AXIS_TYPE
	{
		AXIS_TYPE_NONE,
		AXIS_TYPE_TRACK_PAD,
		AXIS_TYPE_JOYSTICK,
		AXIS_TYPE_TRIGGER,
		NUM_AXIS_TYPES,
	};
	int getNumAxes() const;
	InputVRController::AXIS_TYPE getAxisType(int axis) const;
	float getAxis(int axis) const;
	float getAxisDelta(int axis) const;
	bool isButtonPressed(Input::VR_BUTTON button) const;
	bool isButtonDown(Input::VR_BUTTON button) const;
	bool isButtonUp(Input::VR_BUTTON button) const;
	bool isButtonTouchPressed(Input::VR_BUTTON touch) const;
	bool isButtonTouchDown(Input::VR_BUTTON touch) const;
	bool isButtonTouchUp(Input::VR_BUTTON touch) const;
	Ptr<InputEventVRButton> getButtonEvent(Input::VR_BUTTON button) const;
	int getButtonEvents(Input::VR_BUTTON button, Vector<Ptr<InputEventVRButton>> &events);
	Ptr<InputEventVRButtonTouch> getButtonTouchEvent(Input::VR_BUTTON button) const;
	int getButtonTouchEvents(Input::VR_BUTTON button, Vector<Ptr<InputEventVRButtonTouch>> &events);
	void setVibration(unsigned short duration_ms = 100);
};
typedef Ptr<InputVRController> InputVRControllerPtr;


class UNIGINE_API InputJoystick : public APIInterface
{
public:
	int getNumber() const;
	int getPlayerIndex() const;
	bool isAvailable() const;
	const char *getName() const;
	Input::DEVICE getDeviceType() const;
	void setFilter(float filter);
	float getFilter() const;
	int getNumAxes() const;
	float getAxis(unsigned int axis) const;
	float getAxisDelta(unsigned int axis) const;
	const char *getAxisName(unsigned int axis) const;
	int getNumPovs() const;
	Input::JOYSTICK_POV getPov(unsigned int pov) const;
	const char *getPovName(unsigned int pov) const;
	int getNumButtons() const;
	bool isButtonPressed(unsigned int key) const;
	bool isButtonDown(unsigned int key) const;
	bool isButtonUp(unsigned int key) const;
	const char *getButtonName(unsigned int button) const;
	Ptr<InputEventJoyButton> getButtonEvent(int button) const;
	int getButtonEvents(int button, Vector<Ptr<InputEventJoyButton>> &events) const;
	Ptr<InputEventJoyPovMotion> getPovEvent(int pov) const;
	int getPovEvents(int pov, Vector<Ptr<InputEventJoyPovMotion>> &events) const;
	const char *getGuid() const;
	int getVendor() const;
	int getProduct() const;
	int getProductVersion() const;
};
typedef Ptr<InputJoystick> InputJoystickPtr;


class UNIGINE_API InputEvent : public APIInterface
{
public:
	static bool convertible(InputEvent *obj) { return obj != nullptr; }

	enum TYPE
	{
		INPUT_EVENT = 0,
		INPUT_EVENT_MOUSE_BUTTON,
		INPUT_EVENT_MOUSE_WHEEL,
		INPUT_EVENT_MOUSE_MOTION,
		INPUT_EVENT_KEYBOARD,
		INPUT_EVENT_TEXT,
		INPUT_EVENT_TOUCH,
		INPUT_EVENT_JOY_DEVICE,
		INPUT_EVENT_JOY_BUTTON,
		INPUT_EVENT_JOY_AXIS_MOTION,
		INPUT_EVENT_JOY_POV_MOTION,
		INPUT_EVENT_PAD_DEVICE,
		INPUT_EVENT_PAD_BUTTON,
		INPUT_EVENT_PAD_AXIS_MOTION,
		INPUT_EVENT_PAD_TOUCH_MOTION,
		INPUT_EVENT_VR_DEVICE,
		INPUT_EVENT_VR_BUTTON,
		INPUT_EVENT_VR_BUTTON_TOUCH,
		INPUT_EVENT_VR_AXIS_MOTION,
		INPUT_EVENT_SYSTEM,
		NUM_INPUT_EVENTS,
	};
	InputEvent::TYPE getType() const;
	const char *getTypeName() const;
	unsigned long long getFrame() const;
	void setTimestamp(unsigned long long timestamp);
	unsigned long long getTimestamp() const;
	void setMousePosition(const Math::ivec2 &position);
	Math::ivec2 getMousePosition() const;
};
typedef Ptr<InputEvent> InputEventPtr;


class UNIGINE_API InputEventMouseButton : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_MOUSE_BUTTON; }

	enum ACTION
	{
		ACTION_DOWN = 0,
		ACTION_UP,
	};
	static Ptr<InputEventMouseButton> create();
	static Ptr<InputEventMouseButton> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventMouseButton> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, InputEventMouseButton::ACTION action, Input::MOUSE_BUTTON button);
	void setAction(InputEventMouseButton::ACTION action);
	InputEventMouseButton::ACTION getAction() const;
	void setButton(Input::MOUSE_BUTTON button);
	Input::MOUSE_BUTTON getButton() const;
};
typedef Ptr<InputEventMouseButton> InputEventMouseButtonPtr;


class UNIGINE_API InputEventMouseWheel : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_MOUSE_WHEEL; }
	static Ptr<InputEventMouseWheel> create();
	static Ptr<InputEventMouseWheel> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventMouseWheel> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, int wheel, int wheel_h);
	void setWheel(int wheel);
	int getWheel() const;
	void setWheelHorizontal(int horizontal);
	int getWheelHorizontal() const;
};
typedef Ptr<InputEventMouseWheel> InputEventMouseWheelPtr;


class UNIGINE_API InputEventMouseMotion : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_MOUSE_MOTION; }
	static Ptr<InputEventMouseMotion> create();
	static Ptr<InputEventMouseMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventMouseMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, const Math::ivec2 &delta);
	void setDelta(const Math::ivec2 &delta);
	Math::ivec2 getDelta() const;
};
typedef Ptr<InputEventMouseMotion> InputEventMouseMotionPtr;


class UNIGINE_API InputEventKeyboard : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_KEYBOARD; }

	enum ACTION
	{
		ACTION_DOWN = 0,
		ACTION_REPEAT,
		ACTION_UP,
	};
	static Ptr<InputEventKeyboard> create();
	static Ptr<InputEventKeyboard> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventKeyboard> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, InputEventKeyboard::ACTION action, Input::KEY code);
	void setAction(InputEventKeyboard::ACTION action);
	InputEventKeyboard::ACTION getAction() const;
	void setKey(Input::KEY key);
	Input::KEY getKey() const;
};
typedef Ptr<InputEventKeyboard> InputEventKeyboardPtr;


class UNIGINE_API InputEventText : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_TEXT; }
	static Ptr<InputEventText> create();
	static Ptr<InputEventText> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventText> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, unsigned int unicode);
	void setUnicode(unsigned int unicode);
	unsigned int getUnicode() const;
};
typedef Ptr<InputEventText> InputEventTextPtr;


class UNIGINE_API InputEventTouch : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_TOUCH; }

	enum ACTION
	{
		ACTION_DOWN = 0,
		ACTION_MOTION,
		ACTION_UP,
	};
	static Ptr<InputEventTouch> create();
	static Ptr<InputEventTouch> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventTouch> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, InputEventTouch::ACTION action, long long device_id, long long touch_id);
	static Ptr<InputEventTouch> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, InputEventTouch::ACTION action, long long device_id, long long touch_id, const Math::ivec2 &position, const Math::ivec2 &delta, float pressure);
	void setAction(InputEventTouch::ACTION action);
	InputEventTouch::ACTION getAction() const;
	void setDeviceID(long long deviceid);
	long long getDeviceID() const;
	void setTouchID(long long touchid);
	long long getTouchID() const;
	void setPosition(const Math::ivec2 &position);
	Math::ivec2 getPosition() const;
	void setDelta(const Math::ivec2 &delta);
	Math::ivec2 getDelta() const;
	void setPressure(float pressure);
	float getPressure() const;
};
typedef Ptr<InputEventTouch> InputEventTouchPtr;


class UNIGINE_API InputEventJoyDevice : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_JOY_DEVICE; }

	enum ACTION
	{
		ACTION_CONNECTED = 0,
		ACTION_DISCONNECTED,
	};
	static Ptr<InputEventJoyDevice> create();
	static Ptr<InputEventJoyDevice> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventJoyDevice> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, InputEventJoyDevice::ACTION action, int connection_id, int player_index, const char *model_guid);
	void setAction(InputEventJoyDevice::ACTION action);
	InputEventJoyDevice::ACTION getAction() const;
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setPlayerIndex(int index);
	int getPlayerIndex() const;
	void setModelGUID(const char *modelguid);
	const char *getModelGUID() const;
};
typedef Ptr<InputEventJoyDevice> InputEventJoyDevicePtr;


class UNIGINE_API InputEventJoyButton : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_JOY_BUTTON; }

	enum ACTION
	{
		ACTION_DOWN = 0,
		ACTION_UP,
	};
	static Ptr<InputEventJoyButton> create();
	static Ptr<InputEventJoyButton> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventJoyButton> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, InputEventJoyButton::ACTION action, int connection_id, Input::JOYSTICK_POV button);
	void setAction(InputEventJoyButton::ACTION action);
	InputEventJoyButton::ACTION getAction() const;
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setButton(Input::JOYSTICK_POV button);
	Input::JOYSTICK_POV getButton() const;
};
typedef Ptr<InputEventJoyButton> InputEventJoyButtonPtr;


class UNIGINE_API InputEventJoyAxisMotion : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_JOY_AXIS_MOTION; }
	static Ptr<InputEventJoyAxisMotion> create();
	static Ptr<InputEventJoyAxisMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventJoyAxisMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, int connection_id, int axis, float value);
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setAxis(int axis);
	int getAxis() const;
	void setValue(float value);
	float getValue() const;
};
typedef Ptr<InputEventJoyAxisMotion> InputEventJoyAxisMotionPtr;


class UNIGINE_API InputEventJoyPovMotion : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_JOY_POV_MOTION; }
	static Ptr<InputEventJoyPovMotion> create();
	static Ptr<InputEventJoyPovMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventJoyPovMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, int connection_id, int pov, int value);
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setPov(int pov);
	int getPov() const;
	void setValue(int value);
	int getValue() const;
};
typedef Ptr<InputEventJoyPovMotion> InputEventJoyPovMotionPtr;


class UNIGINE_API InputEventPadDevice : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_PAD_DEVICE; }

	enum ACTION
	{
		ACTION_CONNECTED = 0,
		ACTION_DISCONNECTED,
	};
	static Ptr<InputEventPadDevice> create();
	static Ptr<InputEventPadDevice> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventPadDevice> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, InputEventPadDevice::ACTION action, int connection_id, int player_index, const char *model_guid);
	void setAction(InputEventPadDevice::ACTION action);
	InputEventPadDevice::ACTION getAction() const;
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setPlayerIndex(int index);
	int getPlayerIndex() const;
	void setModelGUID(const char *modelguid);
	const char *getModelGUID() const;
};
typedef Ptr<InputEventPadDevice> InputEventPadDevicePtr;


class UNIGINE_API InputEventPadButton : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_PAD_BUTTON; }

	enum ACTION
	{
		ACTION_DOWN = 0,
		ACTION_UP,
	};
	static Ptr<InputEventPadButton> create();
	static Ptr<InputEventPadButton> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventPadButton> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, InputEventJoyButton::ACTION action, int connection_id, Input::GAMEPAD_BUTTON button);
	void setAction(InputEventPadButton::ACTION action);
	InputEventPadButton::ACTION getAction() const;
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setButton(Input::GAMEPAD_BUTTON button);
	Input::GAMEPAD_BUTTON getButton() const;
};
typedef Ptr<InputEventPadButton> InputEventPadButtonPtr;


class UNIGINE_API InputEventPadAxisMotion : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_PAD_AXIS_MOTION; }
	static Ptr<InputEventPadAxisMotion> create();
	static Ptr<InputEventPadAxisMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventPadAxisMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, int connection_id, int axis, float value);
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setAxis(Input::GAMEPAD_AXIS axis);
	Input::GAMEPAD_AXIS getAxis() const;
	void setValue(float value);
	float getValue() const;
};
typedef Ptr<InputEventPadAxisMotion> InputEventPadAxisMotionPtr;


class UNIGINE_API InputEventPadTouchMotion : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_PAD_TOUCH_MOTION; }

	enum ACTION
	{
		ACTION_DOWN = 0,
		ACTION_MOTION,
		ACTION_UP,
	};
	static Ptr<InputEventPadTouchMotion> create();
	static Ptr<InputEventPadTouchMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventPadTouchMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, int connection_id, InputEventPadTouchMotion::ACTION action, int touch, int finger, float pressure, const Math::vec2 &position);
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setAction(InputEventPadTouchMotion::ACTION action);
	InputEventPadTouchMotion::ACTION getAction() const;
	void setTouch(int touch);
	int getTouch() const;
	void setTouchFinger(int finger);
	int getTouchFinger() const;
	void setPosition(const Math::vec2 &position);
	Math::vec2 getPosition() const;
	void setPressure(float pressure);
	float getPressure() const;
};
typedef Ptr<InputEventPadTouchMotion> InputEventPadTouchMotionPtr;


class UNIGINE_API InputEventVRDevice : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_VR_DEVICE; }

	enum ACTION
	{
		ACTION_CONNECTED = 0,
		ACTION_DISCONNECTED,
	};
	static Ptr<InputEventVRDevice> create();
	static Ptr<InputEventVRDevice> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventVRDevice> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, InputEventVRDevice::ACTION action, int connection_id, InputVRDevice::TYPE type);
	void setAction(InputEventVRDevice::ACTION action);
	InputEventVRDevice::ACTION getAction() const;
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setType(InputEventVRDevice::TYPE type);
	InputEventVRDevice::TYPE getType() const;
};
typedef Ptr<InputEventVRDevice> InputEventVRDevicePtr;


class UNIGINE_API InputEventVRButton : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_VR_BUTTON; }

	enum ACTION
	{
		ACTION_DOWN = 0,
		ACTION_UP,
	};
	static Ptr<InputEventVRButton> create();
	static Ptr<InputEventVRButton> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventVRButton> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, InputEventVRButton::ACTION action, int connection_id, Input::VR_BUTTON button);
	void setAction(InputEventVRButton::ACTION action);
	InputEventVRButton::ACTION getAction() const;
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setButton(Input::VR_BUTTON button);
	Input::VR_BUTTON getButton() const;
};
typedef Ptr<InputEventVRButton> InputEventVRButtonPtr;


class UNIGINE_API InputEventVRButtonTouch : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_VR_BUTTON_TOUCH; }

	enum ACTION
	{
		ACTION_DOWN = 0,
		ACTION_UP,
	};
	static Ptr<InputEventVRButtonTouch> create();
	static Ptr<InputEventVRButtonTouch> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventVRButtonTouch> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, InputEventVRButtonTouch::ACTION action, int connection_id, Input::VR_BUTTON button);
	void setAction(InputEventVRButtonTouch::ACTION action);
	InputEventVRButtonTouch::ACTION getAction() const;
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setButton(Input::VR_BUTTON button);
	Input::VR_BUTTON getButton() const;
};
typedef Ptr<InputEventVRButtonTouch> InputEventVRButtonTouchPtr;


class UNIGINE_API InputEventVRAxisMotion : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_VR_AXIS_MOTION; }
	static Ptr<InputEventVRAxisMotion> create();
	static Ptr<InputEventVRAxisMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventVRAxisMotion> create(unsigned long long timestamp, const Math::ivec2 &mouse_pos, int connection_id, int axis, float value);
	void setConnectionID(int connectionid);
	int getConnectionID() const;
	void setAxis(int axis);
	int getAxis() const;
	void setValue(float value);
	float getValue() const;
};
typedef Ptr<InputEventVRAxisMotion> InputEventVRAxisMotionPtr;


class UNIGINE_API InputEventSystem : public InputEvent
{
public:
	static bool convertible(InputEvent *obj) { return obj && obj->getType() == InputEvent::INPUT_EVENT_SYSTEM; }

	enum ACTION
	{
		ACTION_KEYBOARD_LAYOUT_CHANGED = 0,
	};
	static Ptr<InputEventSystem> create();
	static Ptr<InputEventSystem> create(unsigned int timestamp, const Math::ivec2 &mouse_pos);
	static Ptr<InputEventSystem> create(unsigned int timestamp, const Math::ivec2 &mouse_pos, InputEventSystem::ACTION action);
	void setAction(InputEventSystem::ACTION action);
	InputEventSystem::ACTION getAction() const;
};
typedef Ptr<InputEventSystem> InputEventSystemPtr;

} // namespace Unigine
