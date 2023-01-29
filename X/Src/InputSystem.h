//====================================================================================================
// Filename:	InputSystem.h
// Created by:	Peter Chan
//====================================================================================================

#ifndef INCLUDED_XENGINE_INPUTSYSTEM_H
#define INCLUDED_XENGINE_INPUTSYSTEM_H

namespace X {

class InputSystem
{
public:
	static void StaticInitialize(HWND window);
	static void StaticTerminate();
	static InputSystem* Get();

public:
	InputSystem();
	~InputSystem();

	InputSystem(const InputSystem&) = delete;
	InputSystem& operator=(const InputSystem&) = delete;

	void Initialize(HWND window);
	void Terminate();

	void Update();

	bool IsKeyDown(uint32_t key) const;
	bool IsKeyPressed(uint32_t key) const;

	bool IsMouseDown(uint32_t button) const;
	bool IsMousePressed(uint32_t button) const;

	int GetMouseMoveX() const;
	int GetMouseMoveY() const;
	int GetMouseMoveZ() const;

	int GetMouseScreenX() const;
	int GetMouseScreenY() const;

	bool IsMouseLeftEdge() const;
	bool IsMouseRightEdge() const;
	bool IsMouseTopEdge() const;
	bool IsMouseBottomEdge() const;

	void ShowSystemCursor(bool show);
	void SetMouseClipToWindow(bool clip);
	bool IsMouseClipToWindow() const;

	bool IsGamePadButtonDown(uint32_t button) const;
	bool IsGamePadButtonPressed(uint32_t button) const;

	bool IsDPadUp() const;
	bool IsDPadDown() const;
	bool IsDPadLeft() const;
	bool IsDPadRight() const;

	float GetLeftAnalogX() const;
	float GetLeftAnalogY() const;
	float GetRightAnalogX() const;
	float GetRightAnalogY() const;

private:
	friend BOOL CALLBACK EnumGamePadCallback(const DIDEVICEINSTANCE* pDIDeviceInstance, VOID* pContext);
	friend LRESULT CALLBACK InputSystemMessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

	void UpdateGamePad();

	HWND mWindow;

	IDirectInput8* mDirectInput;
	IDirectInputDevice8* mGamePadDevice;

	DIJOYSTATE mCurrGamePadState;
	DIJOYSTATE mPrevGamePadState;

	bool mCurrKeys[512];
	bool mPrevKeys[512];
	bool mPressedKeys[512];

	bool mClipMouseToWindow;

	int mCurrMouseX;
	int mCurrMouseY;
	int mPrevMouseX;
	int mPrevMouseY;
	int mMouseMoveX;
	int mMouseMoveY;

	int mMouseWheel;

	bool mCurrMouseButtons[3];
	bool mPrevMouseButtons[3];
	bool mPressedMouseButtons[3];

	bool mMouseLeftEdge;
	bool mMouseRightEdge;
	bool mMouseTopEdge;
	bool mMouseBottomEdge;

	bool mInitialized;
};

} // namespace X

#endif // #ifndef INCLUDED_XENGINE_INPUTSYSTEM_H
