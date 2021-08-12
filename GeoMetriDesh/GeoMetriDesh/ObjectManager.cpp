#include "framework.h"
#include "ObjectManager.h"
#include "Object.h"

IMPLEMENT_SINGLETON(ObjectManager)
ObjectManager::~ObjectManager()
{
    Release();
}

HRESULT ObjectManager::Intialize()
{
    /// <summary>
    /// 여기다 뭐 넣을까?
    /// </summary>
    /// <returns></returns>

    return S_OK;
}

void ObjectManager::Update()
{
    for (int i = 0; i < OBJECT_ID_END; i++) {

        //auto iter = objList[i].begin();
        //for (; iter != objList[i].end();) {
        //    int eventVal =  (*iter)->UpdateObject();

        //    if (OBJDEAD == eventVal) {
        //        SAFE_DELETE(*iter);
        //        iter = objList[i].erase(iter);
        //    }
        //    else {
        //        iter++;
        //    }
        //}

        for (auto& rObj : objList[i]) {
            rObj->UpdateObject();
        }

    }
}

void ObjectManager::LateUpdate()
{
    for (int i = 0; i < OBJECT_ID_END; i++) {
        for (auto& rObject : objList[i]) {
            rObject->LateUpdateObject();
        }
    }
}

void ObjectManager::Render()
{
    for (int i = 0; i < OBJECT_ID_END; i++) {
        for (auto& rObject : objList[i]) {
            rObject->RenderObject();
        }
    }
}

void ObjectManager::Release()
{
    for (int i = 0; i < OBJECT_ID_END; i++) {
        for_each(objList[i].begin(),  objList[i].end(), Safe_Delete<Object*> );
        objList[i].clear(); 
    }

}
