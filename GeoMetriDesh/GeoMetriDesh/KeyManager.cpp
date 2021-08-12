#include "framework.h"
#include "KeyManager.h"

IMPLEMENT_SINGLETON(KeyManager)
bool KeyManager::KeyPressing(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000) {
		return true;
	}
	return false;
}


bool KeyManager::KeyDown(int _key)
{
	if (!keyState[_key] && (GetAsyncKeyState(_key) & 0x8000)) {
		keyState[_key] = !keyState[_key];
		return true;
	}

	if (keyState[_key] && !(GetAsyncKeyState(_key) & 0x8000)) {
		keyState[_key] = !keyState[_key];
	}

	return false;
}

bool KeyManager::KeyUp(int _key)
{
	if (!keyState[_key] && (GetAsyncKeyState(_key) & 0x8000)) {
		keyState[_key] = !keyState[_key];
	}

	return false;

}
