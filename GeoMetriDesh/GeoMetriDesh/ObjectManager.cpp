#include "framework.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "CollisionMgr.h"
#include "Object.h"

IMPLEMENT_SINGLETON(ObjectManager)
ObjectManager::~ObjectManager()
{
    Release();
}

HRESULT ObjectManager::Intialize()
{
    keyMgr = KeyManager::GetInstance();
    collisionMgr = CollisionMgr::GetInstance();

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

            if (!rObj->GetDeadCheck()) {
                rObj->UpdateObject();
            }
        }
    }

    collisionMgr->CollisionObject( objList[PLAYER], objList[TERRAIN] );


    KeyChecking();
}

void ObjectManager::LateUpdate()
{
    for (int i = 0; i < OBJECT_ID_END; i++) {
        for (auto& rObject : objList[i]) {
            if (!rObject->GetDeadCheck()) {
                rObject->LateUpdateObject();
            }
        }
    }
}

void ObjectManager::Render()
{
    for (int i = 0; i < OBJECT_ID_END; i++) {
        for (auto& rObject : objList[i]) {
            if (!rObject->GetDeadCheck()) {
                rObject->RenderObject();
            }
        }
    }

}

void ObjectManager::Release()
{
    for (int i = 0; i < OBJECT_ID_END; i++) {
        for_each(objList[i].begin(),  objList[i].end(), Safe_Delete<Object*> );
        objList[i].clear(); 
    }

    SAFE_DELETE(keyMgr);
    SAFE_DELETE(collisionMgr);
}

void ObjectManager::ReleaseObject(OBJECT_ID _ID)
{
    for_each(objList[_ID].begin(), objList[_ID].end(), Safe_Delete<Object*>);
    objList[_ID].clear();
}

void ObjectManager::KeyChecking()
{
    if (keyMgr->KeyPressing('L')) {
        SetShowLineCheck(true);
    }
    if (keyMgr->KeyPressing('K')) {
        SetShowLineCheck(false);
    }

}
