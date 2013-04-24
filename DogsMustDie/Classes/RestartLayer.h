#ifndef RestartLayer_h__
#define RestartLayer_h__

#include "cocos2d.h"
#include "StageBaseScene.h"
#include "NavigatorLayer.h"


using namespace cocos2d;

class RestartLayer : public NavigatorLayer
{
public:
	RestartLayer();
	~RestartLayer();
	
	CREATE_FUNC(RestartLayer);
	bool init();	
	

	CC_SYNTHESIZE(CCSprite* , m_pHappyDog, HappyDog);		
	CC_SYNTHESIZE_RETAIN(CCAction*, m_pFlickerAction, FlickerAction);

	CCString* getTitle();
	void backCallback(CCObject* pOb);
	void restartCallback(CCObject* pOb);


	void restore();			
	void show();

	void dogFunc1();
	void dogFunc2();

};

#endif // RestartLayer_h__