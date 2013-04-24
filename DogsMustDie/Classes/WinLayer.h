#ifndef WinLayer_h__
#define WinLayer_h__

#include "cocos2d.h"
#include "StageBaseScene.h"
#include "NavigatorLayer.h"


using namespace cocos2d;

class WinLayer : public NavigatorLayer
{
public:
	WinLayer();
	~WinLayer();

	CREATE_FUNC(WinLayer);
	bool init();	
	
	CC_SYNTHESIZE(CCSprite* , m_pHappyCat, HappyCat);	
	CC_SYNTHESIZE_RETAIN(CCAction*, m_pFlickerAction, FlickerAction);

	void show();
	void restore();
	
	CCString* getTitle();
	void backCallback(CCObject* pOb);
	void nextCallback(CCObject* pOb);

	void catFunc1();
	void catFunc2();
};

#endif // WinLayer_h__