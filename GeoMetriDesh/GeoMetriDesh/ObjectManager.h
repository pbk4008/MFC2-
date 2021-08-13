#pragma once
#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__


class Object;
class ObjectManager
{
	DECLARE_SINGLETON(ObjectManager)
public:
	enum OBJECT_ID {BACKGROUND, PLAYER, TERRAIN, EFFECT, OBJECT_ID_END};
private:
	explicit ObjectManager() {};
public:
	virtual ~ObjectManager();

	HRESULT Intialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

	template<typename T>
	void InsertObject(OBJECT_ID _typeID)
	{
		for (auto& rObj : objList[_typeID]) {
			if (rObj->GetDeadCheck()) {
				rObj->SetDeadCheck(false);
				return;
			}
		}
		objList[_typeID].emplace_back(AbstractFactory<T>::Create());
	}


	inline Object* GetPlayer() { return objList[PLAYER].back(); };

	
	list<Object*> objList[OBJECT_ID_END];
};





#endif // !__OBJECT_MANAGER_H__