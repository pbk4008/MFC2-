#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__


#define WINCX 800
#define WINCY 600

#define VK_MAX 0xFF

#define DECLARE_SINGLETON(CLASSNAME)				\
	public:																	    \
		static CLASSNAME* GetInstance() {						\
			if (!mInstance) {												\
				mInstance = new CLASSNAME;					\
			}																		\
				return mInstance;											\
		}																			\
																					\
		static void DestroyInstance() {								\
			if (mInstance) {													\
				delete mInstance;										\
				mInstance = nullptr;										\
			}																		\
		}																			\
																					\
	private:																	    \
		static CLASSNAME* mInstance;

#define IMPLEMENT_SINGLETON(CLASSNAME)			\
	CLASSNAME* CLASSNAME::mInstance = nullptr;


#define SAFE_DELETE(p) if(&p) {delete p; p = nullptr;}


#define NOEVENT 0
#define OBJDEAD 1


#endif // !__DEFINE_H__
