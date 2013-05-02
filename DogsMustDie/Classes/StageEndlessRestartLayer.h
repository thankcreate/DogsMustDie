#ifndef StageEndlessRestartLayer_h__
#define StageEndlessRestartLayer_h__

#include "cocos2d.h"
#include "StageBaseScene.h"
#include "StageEndlessNavigatorLayer.h"


using namespace cocos2d;

class StageEndlessRestartLayer : public StageEndlessNavigatorLayer
{
public:
	StageEndlessRestartLayer();
	~StageEndlessRestartLayer();

	CREATE_FUNC(StageEndlessRestartLayer);
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
	void setRound( int round );
};

#endif // StageEndlessRestartLayer_h__