#pragma once
#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

class CollisionMgr
{
public:
	DECLARE_SINGLETON(CollisionMgr)
private:
	explicit CollisionMgr() {};
public:
	virtual ~CollisionMgr() {};

	static void CollisionObject(list<Object*>& _Dst, list<Object*>& _Src);
	static void CollisionPotal(list<Object*>& _Dst, list<Object*>& _Src);
};


#endif // !__COLLISION_MANAGER_H__