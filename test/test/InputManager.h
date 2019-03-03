#pragma once

#define InputMan InputManager::Instance()

class InputManager
{
public:
	static InputManager* Instance();

	///Initialization
	void OnInitialize();
	///Cleanup
	void OnDeinitialize();


private:
	InputManager() {};
	InputManager(const InputManager&);
	InputManager& operator = (const InputManager&);
	~InputManager() {};

	bool currentKeyState[1024] = { false };
	bool oldKeyState[1024] = { false };
	bool keyPressRelease[1024] = { false };
	bool oldKeyPressRelease[1024] = { false };
	bool currentKeyRepeat[1024] = { false };
};
