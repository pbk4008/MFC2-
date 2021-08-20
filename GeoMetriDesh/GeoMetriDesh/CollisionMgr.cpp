#include "framework.h"
#include "CollisionMgr.h"
#include "Object.h"
#include "Player.h"
#include "Potal.h"

IMPLEMENT_SINGLETON(CollisionMgr)

void CollisionMgr::CollisionObject(list<Object*>& _Dst, list<Object*>& _Src)
{
	for (auto& p_Dst : _Dst) {
		for (auto& p_Src : _Src) {
			RECT rc = {};
			RECT rc1 = p_Dst->GetRect();
			RECT rc2 = p_Src->GetRect();
			if (IntersectRect(&rc, &p_Dst->GetRect(), &p_Src->GetRect())) {
				// �÷��̾�����
				p_Dst->SetDeadCheck(true);
			}
		}
	}
}

void CollisionMgr::CollisionPotal(list<Object*>& _Dst, list<Object*>& _Src)
{
	for (auto& p_Dst : _Dst) {
		for (auto& p_Src : _Src) {
			RECT rc = {};
			RECT rc1 = p_Dst->GetRect();
			RECT rc2 = p_Src->GetRect();
			if (IntersectRect(&rc, &p_Dst->GetRect(), &p_Src->GetRect())) {
				// �÷��̾�����
				if(dynamic_cast<CPotal*>(p_Src)->iIndex==0)
					dynamic_cast<Player*>(p_Dst)->setFly(true);
				else
					dynamic_cast<Player*>(p_Dst)->setEnd(true);

			}
		}
	}
}
