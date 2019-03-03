#include "InputManager.h"
#include <iostream>

InputManager* InputManager::Instance()
{
	static InputManager instance;
	return &instance;
}
void InputManager::OnInitialize()
{

}
void InputManager::OnDeinitialize()
{

}