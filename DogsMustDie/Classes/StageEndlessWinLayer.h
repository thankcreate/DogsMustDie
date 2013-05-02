#ifndef StageEndlessWinLayer_h__
#define StageEndlessWinLayer_h__

#include "cocos2d.h"
#include "StageBaseScene.h"
#include "StageEndlessNavigatorLayer.h"


using namespace cocos2d;

class StageEndlessWinLayer : public StageEndlessNavigatorLayer
{
public:
	StageEndlessWinLayer();
	~StageEndlessWinLayer();

	CREATE_FUNC(StageEndlessWinLayer);
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
	void setRound( int round );
	
	
private:	
	
};

#endif // StageEndlessWinLayer_h__