#ifndef AdViewManager_h__
#define AdViewManager_h__

#include "cocos2d.h"


using namespace cocos2d;


class AdViewManager
{
public:
	static AdViewManager* sharedInstance();

	void show();
	void hide();

	enum
	{
		VIEW_VISIBLE = 1,
		VIEW_INVISIBLE = 2
	};

private:
	AdViewManager();
	static AdViewManager* m_pInstance;
};

#endif // AdViewManager_h__
