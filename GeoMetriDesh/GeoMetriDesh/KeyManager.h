#pragma once
#ifndef __KEY_MANAGER_H__
#define __KEY_MANAGER_H__

class KeyManager
{
	DECLARE_SINGLETON(KeyManager)
private:
	explicit KeyManager() {};
	virtual ~KeyManager() {};
public:
	bool KeyPressing(int _key);
	bool KeyDown(int _key);
	bool KeyUp(int _key);
private:
	bool keyState[VK_MAX];
};


#endif // !__KEY_MANAGER_H__
