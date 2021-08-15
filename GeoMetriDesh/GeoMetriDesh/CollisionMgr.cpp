#include "framework.h"
#include "CollisionMgr.h"
#include "Object.h"

IMPLEMENT_SINGLETON(CollisionMgr)

void CollisionMgr::CollisionObject(list<Object*>& _Dst, list<Object*>& _Src)
{
	for (auto& p_Dst : _Dst) {
		for (auto& p_Src : _Src) {
			RECT rc = {};
			RECT rc1 = p_Dst->GetRect();
			RECT rc2 = p_Src->GetRect();
			if (IntersectRect(&rc, &p_Dst->GetRect(), &p_Src->GetRect())) {
				// 플레이어죽음
				p_Dst->SetDeadCheck(true);
			}
		}
	}
}
