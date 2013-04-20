#ifndef AdViewManager_h__
#define AdViewManager_h__

#include "cocos2d.h"
#include "CCAdView.h"

using namespace cocos2d;


class AdViewManager
{
public:
	static AdViewManager* sharedInstance();
	~AdViewManager();
	

	void show(CCNode* parent);
	void hide();

	CC_SYNTHESIZE_RETAIN(CCAdView*, m_pAdView, AdView);

private:
	AdViewManager();

	static AdViewManager* m_pInstance;
};

#endif // AdViewManager_h__
