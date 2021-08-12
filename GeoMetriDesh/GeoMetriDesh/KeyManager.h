#pragma once
#ifndef __KEY_MANAGER_H__
#define __KEY_MANAGER_H__

class KeyManager
{
	DECLARE_SINGLETON(KeyManager)
public:

	static void KeyPressing();
	static void KeyDown();
	static void KeyUp();


private:
	bool keyState[VK_MAX];
};


#endif // !__KEY_MANAGER_H__
