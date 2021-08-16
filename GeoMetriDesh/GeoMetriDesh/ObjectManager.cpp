#include "framework.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "CollisionMgr.h"
#include "Object.h"
#include "Obstacle.h"

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

void ObjectManager::SaveObject()
{
    HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (INVALID_HANDLE_VALUE == hFile)
    {
        MessageBox(g_hWnd, L"저장 실패", L"실패", MB_OK);
        return;
    }
    DWORD dwByte = 0;
    for (auto& pObj : objList[OBSTACLE])
    {
        OBSTACLEINFO argInfo = dynamic_cast<CObstacle*>(pObj)->getObstacleInfo();
        WriteFile(hFile, &argInfo, sizeof(OBSTACLEINFO), &dwByte, nullptr);
    }

    CloseHandle(hFile);
}
